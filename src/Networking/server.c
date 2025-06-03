#include <Networking/server.h>

struct server server_contrector(int domain,
                                int service,
                                int protocol,
                                u_long interface,
                                int port,
                                int backlog,
                                void (*launch)(void))
{
    struct server srv;

    srv.domain = domain;       // Set the domain of the socket
    srv.service = service;     // Set the service type (TCP/UDP)
    srv.protocol = protocol;   // Set the protocol (0 for default)
    srv.interface = interface; // Set the interface to bind to
    srv.port = port;           // Set the port number
    srv.backlog = backlog;     // Set the backlog for the socket

    // Initialize the address structure
    srv.address.sin_family = domain;                // Set the address family
    srv.address.sin_port = htons(port);             // Convert port to network byte order
    srv.address.sin_addr.s_addr = htonl(interface); // Convert interface to network byte order

    srv.launch = launch; // Assign the launch function pointer

    return srv; // Return the initialized server structure
}
