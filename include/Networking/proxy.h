#ifndef proxy_h
#define proxy_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "server.h"

// Proxy configuration types
typedef enum
{
    PROXY_FORWARD, // Forward proxy (client -> proxy -> internet)
    PROXY_REVERSE  // Reverse proxy (client -> proxy -> backend server)
} ProxyType;

// Proxy configuration structure
struct ProxyConfig
{
    ProxyType type;
    char target_host[256]; // Target host for reverse proxy
    int target_port;       // Target port for reverse proxy
    int enable_logging;    // Enable request logging
    char log_file[256];    // Log file path
};

// HTTP request structure for parsing
struct HttpRequest
{
    char method[16];    // GET, POST, etc.
    char url[1024];     // Request URL
    char version[16];   // HTTP version
    char host[256];     // Host header
    char headers[4096]; // All headers
    char body[8192];    // Request body
    int content_length; // Content length
};

// HTTP response structure
struct HttpResponse
{
    int status_code;      // HTTP status code
    char status_text[64]; // Status text (OK, Not Found, etc.)
    char headers[4096];   // Response headers
    char body[8192];      // Response body
    int content_length;   // Content length
};

// Function declarations for proxy functionality
struct ProxyConfig *proxy_config_create(ProxyType type, const char *target_host, int target_port);
void proxy_config_destroy(struct ProxyConfig *config);
void proxy_config_set_logging(struct ProxyConfig *config, int enable, const char *log_file);

// HTTP parsing functions
int parse_http_request(const char *raw_request, struct HttpRequest *request);
void build_http_response(const struct HttpResponse *response, char *output, size_t max_size);
void extract_host_port(const char *url, char *host, int *port);

// Proxy handler functions
void launch_forward_proxy(struct Server *server);
void launch_reverse_proxy(struct Server *server);
void handle_proxy_request(int client_socket, struct ProxyConfig *config);

// Utility functions
void log_request(const struct HttpRequest *request, const char *client_ip, const char *log_file);
int create_connection(const char *host, int port);
void relay_data(int from_socket, int to_socket);
char *get_client_ip(int socket_fd);

// Global proxy configuration
extern struct ProxyConfig *g_proxy_config;

#endif
