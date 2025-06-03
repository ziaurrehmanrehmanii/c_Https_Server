#include <stdio.h>
#include <string.h>
#include <unistd.h>     // Add this for read(), write(), close()
#include <sys/socket.h> // Add this for accept()
#include <Networking/server.h>

int main()
{

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8000, 10, launch);
    server.launch(&server);

    return 0;
}
