#include <Networking/proxy.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/select.h>

// Global proxy configuration
struct ProxyConfig *g_proxy_config = NULL;

// Create a new proxy configuration
struct ProxyConfig *proxy_config_create(ProxyType type, const char *target_host, int target_port)
{
    struct ProxyConfig *config = malloc(sizeof(struct ProxyConfig));
    if (!config)
    {
        perror("Failed to allocate proxy config");
        return NULL;
    }

    config->type = type;
    config->target_port = target_port;
    config->enable_logging = 0;
    strcpy(config->log_file, "proxy.log");

    if (target_host)
    {
        strncpy(config->target_host, target_host, sizeof(config->target_host) - 1);
        config->target_host[sizeof(config->target_host) - 1] = '\0';
    }
    else
    {
        config->target_host[0] = '\0';
    }

    return config;
}

// Destroy proxy configuration
void proxy_config_destroy(struct ProxyConfig *config)
{
    if (config)
    {
        free(config);
    }
}

// Set logging configuration
void proxy_config_set_logging(struct ProxyConfig *config, int enable, const char *log_file)
{
    if (!config)
        return;

    config->enable_logging = enable;
    if (log_file)
    {
        strncpy(config->log_file, log_file, sizeof(config->log_file) - 1);
        config->log_file[sizeof(config->log_file) - 1] = '\0';
    }
}

// Parse HTTP request from raw data
int parse_http_request(const char *raw_request, struct HttpRequest *request)
{
    if (!raw_request || !request)
        return -1;

    // Initialize request structure
    memset(request, 0, sizeof(struct HttpRequest));

    // Parse request line (METHOD URL VERSION)
    const char *line_end = strstr(raw_request, "\r\n");
    if (!line_end)
        line_end = strstr(raw_request, "\n");
    if (!line_end)
        return -1;

    // Extract method, URL, and version
    sscanf(raw_request, "%15s %1023s %15s", request->method, request->url, request->version);

    // Parse headers
    const char *headers_start = line_end + (strstr(raw_request, "\r\n") ? 2 : 1);
    const char *body_start = strstr(headers_start, "\r\n\r\n");
    if (!body_start)
        body_start = strstr(headers_start, "\n\n");

    if (body_start)
    {
        size_t headers_len = body_start - headers_start;
        if (headers_len < sizeof(request->headers))
        {
            strncpy(request->headers, headers_start, headers_len);
            request->headers[headers_len] = '\0';
        }

        // Extract Host header
        const char *host_header = strstr(request->headers, "Host:");
        if (host_header)
        {
            sscanf(host_header, "Host: %255s", request->host);
        }

        // Extract Content-Length
        const char *content_len = strstr(request->headers, "Content-Length:");
        if (content_len)
        {
            sscanf(content_len, "Content-Length: %d", &request->content_length);
        }

        // Copy body if present
        body_start += (strstr(headers_start, "\r\n\r\n") ? 4 : 2);
        if (request->content_length > 0 && (size_t)request->content_length < sizeof(request->body))
        {
            strncpy(request->body, body_start, request->content_length);
            request->body[request->content_length] = '\0';
        }
    }

    return 0;
}

// Build HTTP response from structure
void build_http_response(const struct HttpResponse *response, char *output, size_t max_size)
{
    snprintf(output, max_size,
             "HTTP/1.1 %d %s\r\n"
             "%s"
             "Content-Length: %d\r\n"
             "\r\n"
             "%s",
             response->status_code,
             response->status_text,
             response->headers,
             response->content_length,
             response->body);
}

// Extract host and port from URL
void extract_host_port(const char *url, char *host, int *port)
{
    *port = 80; // Default HTTP port

    // Handle full URLs
    const char *start = url;
    if (strncmp(url, "http://", 7) == 0)
    {
        start = url + 7;
        *port = 80;
    }
    else if (strncmp(url, "https://", 8) == 0)
    {
        start = url + 8;
        *port = 443;
    }

    // Find port separator
    const char *port_sep = strchr(start, ':');
    const char *path_sep = strchr(start, '/');

    if (port_sep && (!path_sep || port_sep < path_sep))
    {
        // Extract host
        size_t host_len = port_sep - start;
        strncpy(host, start, host_len);
        host[host_len] = '\0';

        // Extract port
        *port = atoi(port_sep + 1);
    }
    else
    {
        // No port specified, extract host until path or end
        const char *end = path_sep ? path_sep : start + strlen(start);
        size_t host_len = end - start;
        strncpy(host, start, host_len);
        host[host_len] = '\0';
    }
}

// Create connection to target server
int create_connection(const char *host, int port)
{
    struct sockaddr_in server_addr;
    struct hostent *server;
    int sock_fd;

    // Create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        perror("Socket creation failed");
        return -1;
    }

    // Get server address
    server = gethostbyname(host);
    if (!server)
    {
        printf("Failed to resolve host: %s\n", host);
        close(sock_fd);
        return -1;
    }

    // Setup server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);

    // Connect to server
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed");
        close(sock_fd);
        return -1;
    }

    return sock_fd;
}

// Relay data between two sockets
void relay_data(int from_socket, int to_socket)
{
    char buffer[4096];
    fd_set read_fds;
    int max_fd = (from_socket > to_socket) ? from_socket : to_socket;
    struct timeval timeout;

    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(from_socket, &read_fds);
        FD_SET(to_socket, &read_fds);

        timeout.tv_sec = 30; // 30 second timeout
        timeout.tv_usec = 0;

        int activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);

        if (activity < 0)
        {
            perror("Select error");
            break;
        }
        else if (activity == 0)
        {
            printf("Connection timeout\n");
            break;
        }

        // Check from_socket for data
        if (FD_ISSET(from_socket, &read_fds))
        {
            ssize_t bytes = recv(from_socket, buffer, sizeof(buffer), 0);
            if (bytes <= 0)
                break;

            if (send(to_socket, buffer, bytes, 0) != bytes)
            {
                perror("Send failed");
                break;
            }
        }

        // Check to_socket for data
        if (FD_ISSET(to_socket, &read_fds))
        {
            ssize_t bytes = recv(to_socket, buffer, sizeof(buffer), 0);
            if (bytes <= 0)
                break;

            if (send(from_socket, buffer, bytes, 0) != bytes)
            {
                perror("Send failed");
                break;
            }
        }
    }
}

// Get client IP address
char *get_client_ip(int socket_fd)
{
    static char ip_str[INET_ADDRSTRLEN];
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    if (getpeername(socket_fd, (struct sockaddr *)&addr, &addr_len) == 0)
    {
        inet_ntop(AF_INET, &addr.sin_addr, ip_str, INET_ADDRSTRLEN);
        return ip_str;
    }

    return "unknown";
}

// Log HTTP request
void log_request(const struct HttpRequest *request, const char *client_ip, const char *log_file)
{
    FILE *log = fopen(log_file, "a");
    if (!log)
        return;

    time_t now;
    time(&now);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Remove newline

    fprintf(log, "[%s] %s %s %s from %s\n",
            time_str, request->method, request->url, request->version, client_ip);

    fclose(log);
}

// Handle proxy request
void handle_proxy_request(int client_socket, struct ProxyConfig *config)
{
    char buffer[8192];
    struct HttpRequest request;
    char target_host[256];
    int target_port;

    // Read client request
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0)
    {
        close(client_socket);
        return;
    }
    buffer[bytes_received] = '\0';

    // Parse HTTP request
    if (parse_http_request(buffer, &request) < 0)
    {
        const char *error_response =
            "HTTP/1.1 400 Bad Request\r\n"
            "Content-Length: 26\r\n"
            "\r\n"
            "<h1>400 Bad Request</h1>";
        send(client_socket, error_response, strlen(error_response), 0);
        close(client_socket);
        return;
    }

    // Log request if enabled
    if (config->enable_logging)
    {
        log_request(&request, get_client_ip(client_socket), config->log_file);
    }

    // Determine target based on proxy type
    if (config->type == PROXY_REVERSE)
    {
        // Reverse proxy: use configured target
        strcpy(target_host, config->target_host);
        target_port = config->target_port;
    }
    else
    {
        // Forward proxy: extract from request
        if (strcmp(request.method, "CONNECT") == 0)
        {
            // HTTPS tunneling
            extract_host_port(request.url, target_host, &target_port);
        }
        else
        {
            // Regular HTTP request
            if (strlen(request.host) > 0)
            {
                extract_host_port(request.host, target_host, &target_port);
            }
            else
            {
                extract_host_port(request.url, target_host, &target_port);
            }
        }
    }

    printf("Proxying request to %s:%d\n", target_host, target_port);

    // Create connection to target server
    int target_socket = create_connection(target_host, target_port);
    if (target_socket < 0)
    {
        const char *error_response =
            "HTTP/1.1 502 Bad Gateway\r\n"
            "Content-Length: 25\r\n"
            "\r\n"
            "<h1>502 Bad Gateway</h1>";
        send(client_socket, error_response, strlen(error_response), 0);
        close(client_socket);
        return;
    }

    // Handle CONNECT method (for HTTPS tunneling)
    if (strcmp(request.method, "CONNECT") == 0)
    {
        const char *connect_response = "HTTP/1.1 200 Connection Established\r\n\r\n";
        send(client_socket, connect_response, strlen(connect_response), 0);

        // Start tunneling
        relay_data(client_socket, target_socket);
    }
    else
    {
        // Forward the request to target server
        send(target_socket, buffer, bytes_received, 0);

        // Relay data between client and server
        relay_data(client_socket, target_socket);
    }

    close(target_socket);
    close(client_socket);
}

// Forward proxy launch function
void launch_forward_proxy(struct Server *server)
{
    printf("Starting Forward Proxy on port %d\n", server->port);

    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_socket = accept(server->socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0)
        {
            perror("Accept failed");
            continue;
        }

        printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

        // Handle request in a simple way (could be threaded for better performance)
        handle_proxy_request(client_socket, g_proxy_config);
    }
}

// Reverse proxy launch function
void launch_reverse_proxy(struct Server *server)
{
    printf("Starting Reverse Proxy on port %d -> %s:%d\n",
           server->port, g_proxy_config->target_host, g_proxy_config->target_port);

    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_socket = accept(server->socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0)
        {
            perror("Accept failed");
            continue;
        }

        printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

        // Handle request
        handle_proxy_request(client_socket, g_proxy_config);
    }
}
