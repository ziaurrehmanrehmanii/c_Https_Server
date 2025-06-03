#ifndef server_h
#define server_h
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
struct Server
{
    int domain;                 // Domain of the socket (AF_INET for IPv4, AF_INET6 for IPv6)
    int service;                // Service type (SOCK_STREAM for TCP, SOCK_DGRAM for UDP)
    int protocol;               // Protocol (0 for default)
    u_long interface;           // Interface to bind to (INADDR_ANY for all interfaces)
    int port;                   // Port number to bind to
    int backlog;                // Backlog for the socket (number of connections to queue)
    struct sockaddr_in address; // Address structure to hold the socket address
    int socket;                 // Socket file descriptor
    void (*launch)(void);       // Function pointer to launch the server
};

// Function prototype for creating a server instance
// This function initializes a server structure with the provided parameters
// and returns a server instance that can be used to set up and run the server.
struct Server server_constructor(int domain,
                                 int service,
                                 int protocol,
                                 u_long interface,
                                 int port,
                                 int backlog,
                                 void (*launch)(void)); // Constructor for the server structure

#endif
