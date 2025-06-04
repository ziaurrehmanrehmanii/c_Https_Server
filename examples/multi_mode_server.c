#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <Networking/server.h>
#include <Networking/proxy.h>

// Original launch function for basic HTTP server
void launch_basic_server(struct Server *server)
{
    while (1)
    {
        char buffer[1024] = {0};
        printf("Basic HTTP Server is running on port %d\n", server->port);
        int address_length = sizeof(server->address);
        int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        read(new_socket, buffer, 1024);
        printf("Message received: %s\n", buffer);

        // write the hello message to the client
        const char *hello = "HTTP/1.1 200 OK\r\nDate: Mon, 27 Jul 2009 12:28:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\nContent-Length: 92\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello from Zia</h1></body></html>";
        write(new_socket, hello, strlen(hello));
        printf("Hello message sent\n");
        close(new_socket);
    }
}

void print_usage(const char *program_name)
{
    printf("Usage: %s [mode] [options]\n\n", program_name);
    printf("Modes:\n");
    printf("  server [port]                     - Basic HTTP server (default port: 8080)\n");
    printf("  forward [port]                    - Forward proxy server (default port: 8080)\n");
    printf("  reverse [port] [host] [target_port] - Reverse proxy server\n");
    printf("                                      (default: port=8080, host=httpbin.org, target_port=80)\n\n");
    printf("Examples:\n");
    printf("  %s server 8000                   - Start HTTP server on port 8000\n", program_name);
    printf("  %s forward 3128                  - Start forward proxy on port 3128\n", program_name);
    printf("  %s reverse 8080 google.com 80    - Reverse proxy to google.com:80\n", program_name);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    const char *mode = argv[1];

    if (strcmp(mode, "server") == 0)
    {
        // Basic HTTP server mode
        int port = 8080;
        if (argc > 2)
        {
            port = atoi(argv[2]);
            if (port <= 0 || port > 65535)
            {
                printf("Invalid port number. Using default port 8080.\n");
                port = 8080;
            }
        }

        printf("Starting Basic HTTP Server on port %d\n", port);
        printf("Visit: http://localhost:%d\n", port);

        struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, port, 10, launch_basic_server);
        server.launch(&server);
    }
    else if (strcmp(mode, "forward") == 0)
    {
        // Forward proxy mode
        int port = 8080;
        if (argc > 2)
        {
            port = atoi(argv[2]);
            if (port <= 0 || port > 65535)
            {
                printf("Invalid port number. Using default port 8080.\n");
                port = 8080;
            }
        }

        printf("Starting Forward Proxy Server on port %d\n", port);
        printf("Configure your browser to use HTTP proxy: localhost:%d\n", port);

        g_proxy_config = proxy_config_create(PROXY_FORWARD, NULL, 0);
        if (!g_proxy_config)
        {
            printf("Failed to create proxy configuration\n");
            return 1;
        }

        proxy_config_set_logging(g_proxy_config, 1, "forward_proxy.log");

        struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, port, 10, launch_forward_proxy);
        server.launch(&server);

        proxy_config_destroy(g_proxy_config);
    }
    else if (strcmp(mode, "reverse") == 0)
    {
        // Reverse proxy mode
        int proxy_port = 8080;
        char target_host[256] = "httpbin.org";
        int target_port = 80;

        if (argc > 2)
        {
            proxy_port = atoi(argv[2]);
            if (proxy_port <= 0 || proxy_port > 65535)
            {
                printf("Invalid proxy port. Using default port 8080.\n");
                proxy_port = 8080;
            }
        }

        if (argc > 3)
        {
            strncpy(target_host, argv[3], sizeof(target_host) - 1);
            target_host[sizeof(target_host) - 1] = '\0';
        }

        if (argc > 4)
        {
            target_port = atoi(argv[4]);
            if (target_port <= 0 || target_port > 65535)
            {
                printf("Invalid target port. Using default port 80.\n");
                target_port = 80;
            }
        }

        printf("Starting Reverse Proxy Server\n");
        printf("Listening on port: %d\n", proxy_port);
        printf("Forwarding to: %s:%d\n", target_host, target_port);
        printf("Test: curl http://localhost:%d/get\n", proxy_port);

        g_proxy_config = proxy_config_create(PROXY_REVERSE, target_host, target_port);
        if (!g_proxy_config)
        {
            printf("Failed to create proxy configuration\n");
            return 1;
        }

        proxy_config_set_logging(g_proxy_config, 1, "reverse_proxy.log");

        struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, proxy_port, 10, launch_reverse_proxy);
        server.launch(&server);

        proxy_config_destroy(g_proxy_config);
    }
    else
    {
        printf("Unknown mode: %s\n\n", mode);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
