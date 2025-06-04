#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <Networking/server.h>
#include <Networking/proxy.h>

int main(int argc, char *argv[])
{
    int proxy_port = 8080;
    char target_host[256] = "httpbin.org";
    int target_port = 80;

    // Parse command line arguments
    if (argc > 1)
    {
        proxy_port = atoi(argv[1]);
        if (proxy_port <= 0 || proxy_port > 65535)
        {
            printf("Invalid proxy port number. Using default port 8080.\n");
            proxy_port = 8080;
        }
    }

    if (argc > 2)
    {
        strncpy(target_host, argv[2], sizeof(target_host) - 1);
        target_host[sizeof(target_host) - 1] = '\0';
    }

    if (argc > 3)
    {
        target_port = atoi(argv[3]);
        if (target_port <= 0 || target_port > 65535)
        {
            printf("Invalid target port number. Using default port 80.\n");
            target_port = 80;
        }
    }

    printf("Starting Reverse Proxy Server\n");
    printf("Listening on port: %d\n", proxy_port);
    printf("Forwarding to: %s:%d\n", target_host, target_port);
    printf("Usage: curl http://localhost:%d/get\n", proxy_port);
    printf("Press Ctrl+C to stop the server.\n\n");

    // Create proxy configuration
    g_proxy_config = proxy_config_create(PROXY_REVERSE, target_host, target_port);
    if (!g_proxy_config)
    {
        printf("Failed to create proxy configuration\n");
        return 1;
    }

    // Enable logging
    proxy_config_set_logging(g_proxy_config, 1, "reverse_proxy.log");

    // Create and start server
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, proxy_port, 10, launch_reverse_proxy);
    server.launch(&server);

    // Cleanup
    proxy_config_destroy(g_proxy_config);

    return 0;
}
