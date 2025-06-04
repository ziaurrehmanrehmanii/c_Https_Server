#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <Networking/server.h>
#include <Networking/proxy.h>

int main(int argc, char *argv[])
{
    int port = 8080;

    // Parse command line arguments
    if (argc > 1)
    {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535)
        {
            printf("Invalid port number. Using default port 8080.\n");
            port = 8080;
        }
    }

    printf("Starting Forward Proxy Server on port %d\n", port);
    printf("Usage: Set your browser's HTTP proxy to localhost:%d\n", port);
    printf("Press Ctrl+C to stop the server.\n\n");

    // Create proxy configuration
    g_proxy_config = proxy_config_create(PROXY_FORWARD, NULL, 0);
    if (!g_proxy_config)
    {
        printf("Failed to create proxy configuration\n");
        return 1;
    }

    // Enable logging
    proxy_config_set_logging(g_proxy_config, 1, "forward_proxy.log");

    // Create and start server
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, port, 10, launch_forward_proxy);
    server.launch(&server);

    // Cleanup
    proxy_config_destroy(g_proxy_config);

    return 0;
}
