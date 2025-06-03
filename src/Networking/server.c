#include <Networking/server.h>

struct Server server_constructor(int domain,
                                 int service,
                                 int protocol,
                                 u_long interface,
                                 int port,
                                 int backlog,
                                 void (*launch)(void))
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

    return server; // Return the initialized server structure
}
