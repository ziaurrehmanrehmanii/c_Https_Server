#include <stdio.h>
#include <string.h>
#include <unistd.h>     // Add this for read(), write(), close()
#include <sys/socket.h> // Add this for accept()
#include <Networking/server.h>

int main()
{
    printf("Starting Basic HTTP Server (Original Functionality)\n");
    printf("For proxy features, check the examples/ directory\n");
    printf("Server running on: http://localhost:8080\n\n");

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    server.launch(&server);

    return 0;
}
