#include <Networking/server.h>
#include <string.h>
#include <unistd.h>

struct Server server_constructor(int domain,
                                 int service,
                                 int protocol,
                                 unsigned long interface,
                                 int port,
                                 int backlog,
                                 void (*launch)(struct Server *server))
{
    struct Server server;

    server.domain = domain;       // Set the socket domain (AF_INET for IPv4, AF_INET6 for IPv6)
    server.service = service;     // Set the service type (SOCK_STREAM for TCP, SOCK_DGRAM for UDP)
    server.protocol = protocol;   // Set the protocol (0 for default)
    server.interface = interface; // Set the interface to bind to (INADDR_ANY for all interfaces)
    server.port = port;           // Set the port number to bind to
    server.backlog = backlog;     // Set the backlog for the socket (number of connections to queue)

    server.address.sin_family = domain;                // Set the address family (AF_INET or AF_INET6)
    server.address.sin_port = htons(port);             // Set the port number in network byte order
    server.address.sin_addr.s_addr = htonl(interface); // Set the interface address in network byte order

    server.socket = socket(domain, service, protocol); // Create the socket with the specified parameters

    if (server.socket < 0)
    {
        perror("Failed to create socket"); // Print error message if socket creation fails
        exit(EXIT_FAILURE);                // Exit the program with failure status
    }

    // Bind the socket to the specified address and port
    if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
    {
        perror("Failed to bind socket"); // Print error message if binding fails
        close(server.socket);            // Close the socket before exiting
        exit(EXIT_FAILURE);              // Exit the program with failure status
    }
    // Set the server yo listening for incoming connections
    if (listen(server.socket, server.backlog) < 0)
    {
        perror("Failed to listen on socket"); // Print error message if listening fails
        close(server.socket);                 // Close the socket before exiting
        exit(EXIT_FAILURE);                   // Exit the program with failure status
    }

    server.launch = launch; // Assign the launch function pointer to the server structure

    return server; // Return the initialized server structure
}

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
        const char *hello = "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Length: 92\nContent-Type: text/html\n\n<html><body><h1>Hello from Zia</h1></body></html>";
        write(new_socket, hello, strlen(hello));
        printf("Hello message sent\n");
        close(new_socket);
    }
}
