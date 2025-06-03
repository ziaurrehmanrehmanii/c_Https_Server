#include <stdio.h>
#include <string.h>
#include <unistd.h>     // Add this for read(), write(), close()
#include <sys/socket.h> // Add this for accept()
#include <Networking/server.h>
void launch(struct Server *server)
{
    while (1)
    {

        char buffer[1024] = {0};
        printf("Server is running on port %d\n", server->port);
        int address_length = sizeof(server->address);
        int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        read(new_socket, buffer, 1024);
        printf("Message received: %s\n", buffer);
        // write the hello message to the client
        const char *hello = "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Length: 88\nContent-Type: text/html\n\n<html><body><h1>Hello World</h1></body></html>";
        write(new_socket, hello, strlen(hello));
        printf("Hello message sent\n");
        close(new_socket);
    }
}
int main()
{

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    server.launch(&server);

    return 0;
}
