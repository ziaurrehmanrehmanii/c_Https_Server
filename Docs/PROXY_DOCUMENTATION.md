# HTTP Proxy Server Documentation

This C HTTP server implementation now includes both **Forward Proxy** and **Reverse Proxy** functionality while maintaining the original basic HTTP server capabilities.

## Table of Contents

1. [Overview](#overview)
2. [Proxy Types](#proxy-types)
3. [Building and Running](#building-and-running)
4. [Examples](#examples)
5. [Configuration](#configuration)
6. [API Reference](#api-reference)
7. [Troubleshooting](#troubleshooting)

## Overview

The HTTP server implementation provides three modes of operation:

- **Basic HTTP Server**: Serves static content (original functionality)
- **Forward Proxy**: Acts as an intermediary for client requests to the internet
- **Reverse Proxy**: Acts as an intermediary for servers, forwarding client requests to backend servers

## Proxy Types

### Forward Proxy

A forward proxy sits between clients and the internet, forwarding client requests to destination servers.

**Use Cases:**
- Web filtering and monitoring
- Caching frequently requested content
- Anonymizing client requests
- Bypassing geographical restrictions

**Flow:**
```
Client → Forward Proxy → Internet Server → Forward Proxy → Client
```

### Reverse Proxy

A reverse proxy sits between clients and backend servers, forwarding client requests to one or more backend servers.

**Use Cases:**
- Load balancing across multiple backend servers
- SSL termination
- Caching server responses
- API gateway functionality

**Flow:**
```
Client → Reverse Proxy → Backend Server → Reverse Proxy → Client
```

## Building and Running

### Prerequisites

```bash
sudo apt update
sudo apt install build-essential cmake libssl-dev gdb valgrind
```

### Build Options

#### Using CMake (Original Project)
```bash
# Build the basic HTTP server
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/bin/c_https_server
```

#### Using Makefile (Proxy Examples)
```bash
cd examples
make -f Makefile_proxy all
```

## Examples

### 1. Basic HTTP Server (Original Functionality)

```bash
# Start the basic server
./build/bin/c_https_server

# Test it
curl http://localhost:8080
# Returns: <html><body><h1>Hello from Zia</h1></body></html>
```

### 2. Forward Proxy Server

```bash
# Build and run forward proxy
cd examples
make -f Makefile_proxy all
./bin/forward_proxy 3128

# Configure your browser to use HTTP proxy: localhost:3128
# Or test with curl:
curl --proxy http://localhost:3128 http://httpbin.org/get
```

### 3. Reverse Proxy Server

```bash
# Run reverse proxy forwarding to httpbin.org
./bin/reverse_proxy 8080 httpbin.org 80

# Test the reverse proxy
curl http://localhost:8080/get
curl http://localhost:8080/json
curl -X POST http://localhost:8080/post -d '{"test": "data"}'
```

### 4. Multi-Mode Server

```bash
# Run in different modes
./bin/multi_mode_server server 8000          # Basic HTTP server
./bin/multi_mode_server forward 3128         # Forward proxy
./bin/multi_mode_server reverse 8080 google.com 80  # Reverse proxy
```

## Configuration

### Proxy Configuration Structure

```c
struct ProxyConfig {
    ProxyType type;          // PROXY_FORWARD or PROXY_REVERSE
    char target_host[256];   // Target host for reverse proxy
    int target_port;         // Target port for reverse proxy
    int enable_logging;      // Enable request logging
    char log_file[256];      // Log file path
};
```

### Creating a Proxy Configuration

```c
// Forward proxy
struct ProxyConfig* config = proxy_config_create(PROXY_FORWARD, NULL, 0);

// Reverse proxy
struct ProxyConfig* config = proxy_config_create(PROXY_REVERSE, "backend.example.com", 8080);

// Enable logging
proxy_config_set_logging(config, 1, "proxy_requests.log");
```

### Example Configuration Code

```c
#include <Networking/server.h>
#include <Networking/proxy.h>

int main() {
    // Create reverse proxy configuration
    g_proxy_config = proxy_config_create(PROXY_REVERSE, "httpbin.org", 80);
    proxy_config_set_logging(g_proxy_config, 1, "reverse_proxy.log");

    // Create and start server
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0,
                                            INADDR_ANY, 8080, 10,
                                            launch_reverse_proxy);
    server.launch(&server);

    // Cleanup
    proxy_config_destroy(g_proxy_config);
    return 0;
}
```

## API Reference

### Core Functions

#### `proxy_config_create(ProxyType type, const char* target_host, int target_port)`
Creates a new proxy configuration.

**Parameters:**
- `type`: `PROXY_FORWARD` or `PROXY_REVERSE`
- `target_host`: Target hostname (for reverse proxy only)
- `target_port`: Target port (for reverse proxy only)

**Returns:** Pointer to `ProxyConfig` structure or `NULL` on failure.

#### `proxy_config_set_logging(struct ProxyConfig* config, int enable, const char* log_file)`
Configures request logging.

**Parameters:**
- `config`: Proxy configuration
- `enable`: 1 to enable logging, 0 to disable
- `log_file`: Path to log file

#### `launch_forward_proxy(struct Server* server)`
Launch function for forward proxy mode.

#### `launch_reverse_proxy(struct Server* server)`
Launch function for reverse proxy mode.

### HTTP Parsing Functions

#### `parse_http_request(const char* raw_request, struct HttpRequest* request)`
Parses raw HTTP request data into structured format.

#### `extract_host_port(const char* url, char* host, int* port)`
Extracts hostname and port from URL.

#### `create_connection(const char* host, int port)`
Creates a TCP connection to the specified host and port.

### Utility Functions

#### `log_request(const struct HttpRequest* request, const char* client_ip, const char* log_file)`
Logs HTTP request to file.

#### `get_client_ip(int socket_fd)`
Gets client IP address from socket.

## Testing

### Test Forward Proxy

1. Start the forward proxy:
   ```bash
   ./bin/forward_proxy 3128
   ```

2. Configure your browser:
   - Set HTTP proxy to `localhost:3128`
   - Visit any website

3. Or test with curl:
   ```bash
   curl --proxy http://localhost:3128 http://httpbin.org/get
   ```

### Test Reverse Proxy

1. Start the reverse proxy:
   ```bash
   ./bin/reverse_proxy 8080 httpbin.org 80
   ```

2. Test with curl:
   ```bash
   curl http://localhost:8080/get
   curl http://localhost:8080/json
   curl -X POST http://localhost:8080/post -H "Content-Type: application/json" -d '{"name": "Zia"}'
   ```

### Browser Configuration for Forward Proxy

#### Firefox
1. Open Settings → Network Settings
2. Select "Manual proxy configuration"
3. Set HTTP Proxy: `localhost`, Port: `3128`
4. Click "OK"

#### Chrome
```bash
google-chrome --proxy-server="http://localhost:3128"
```

## Logging

Proxy requests are logged in the following format:
```
[Mon Jun  3 16:20:30 2025] GET http://httpbin.org/get HTTP/1.1 from 127.0.0.1
[Mon Jun  3 16:20:35 2025] POST http://httpbin.org/post HTTP/1.1 from 192.168.1.100
```

Log files:
- `forward_proxy.log` - Forward proxy requests
- `reverse_proxy.log` - Reverse proxy requests

## Troubleshooting

### Common Issues

1. **Port already in use**
   ```bash
   # Find and kill the process using the port
   sudo lsof -i :8080
   sudo kill -9 <PID>
   ```

2. **Permission denied on low ports**
   ```bash
   # Use ports > 1024 or run with sudo
   sudo ./bin/reverse_proxy 80 backend.com 80
   ```

3. **DNS resolution issues**
   ```bash
   # Test DNS resolution
   nslookup httpbin.org
   ping httpbin.org
   ```

4. **Connection timeout**
   - Check firewall settings
   - Verify target server is accessible
   - Increase timeout values in code

### Debug Mode

Build with debug flags and use GDB:
```bash
make -f Makefile_proxy clean
make -f Makefile_proxy CFLAGS="-g -DDEBUG" all
gdb ./bin/reverse_proxy
```

### Performance Tuning

For high-traffic scenarios:
1. Use threading for concurrent connections
2. Implement connection pooling
3. Add caching mechanisms
4. Use non-blocking I/O

## Security Considerations

1. **Input Validation**: Always validate HTTP headers and URLs
2. **Access Control**: Implement IP-based filtering for forward proxies
3. **Logging**: Monitor and log all proxy activities
4. **Rate Limiting**: Implement request rate limiting
5. **SSL/TLS**: Add HTTPS support for secure connections

## Future Enhancements

- Multi-threading support for concurrent connections
- HTTP/2 and WebSocket support
- SSL/TLS termination
- Load balancing algorithms
- Caching mechanisms
- Authentication and authorization
- Health checks for backend servers
