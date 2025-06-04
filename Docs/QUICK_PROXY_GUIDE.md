# Quick Proxy Setup Guide

## 🚀 Quick Start

### 1. Build the Examples
```bash
cd examples
make -f Makefile_proxy all
```

### 2. Test Forward Proxy (5 minutes)
```bash
# Terminal 1: Start forward proxy
./bin/forward_proxy 3128

# Terminal 2: Test with curl
curl --proxy http://localhost:3128 http://httpbin.org/get
```

### 3. Test Reverse Proxy (5 minutes)
```bash
# Terminal 1: Start reverse proxy
./bin/reverse_proxy 8080 httpbin.org 80

# Terminal 2: Test requests
curl http://localhost:8080/get
curl http://localhost:8080/json
```

### 4. Multi-Mode Server
```bash
# Basic HTTP server
./bin/multi_mode_server server 8000

# Forward proxy
./bin/multi_mode_server forward 3128

# Reverse proxy to Google
./bin/multi_mode_server reverse 8080 google.com 80
```

## 🔧 Browser Setup for Forward Proxy

### Firefox Quick Setup
1. Type `about:preferences` in address bar
2. Search for "proxy"
3. Click "Settings..."
4. Select "Manual proxy configuration"
5. HTTP Proxy: `localhost`, Port: `3128`
6. Click "OK"

### Chrome Quick Setup
```bash
google-chrome --proxy-server="http://localhost:3128"
```

## ✅ Quick Tests

### Forward Proxy Test
```bash
# Start proxy
./bin/forward_proxy 3128

# Test various sites
curl --proxy http://localhost:3128 http://httpbin.org/ip
curl --proxy http://localhost:3128 http://httpbin.org/user-agent
curl --proxy http://localhost:3128 http://httpbin.org/headers
```

### Reverse Proxy Test
```bash
# Start reverse proxy to httpbin.org
./bin/reverse_proxy 8080 httpbin.org 80

# Test API endpoints
curl http://localhost:8080/get
curl http://localhost:8080/json
curl -X POST http://localhost:8080/post -d "test=data"
curl http://localhost:8080/status/200
curl http://localhost:8080/delay/2
```

### Load Balancing Test (Manual)
```bash
# Terminal 1: Reverse proxy to server 1
./bin/multi_mode_server reverse 8081 httpbin.org 80

# Terminal 2: Reverse proxy to server 2
./bin/multi_mode_server reverse 8082 postman-echo.com 80

# Terminal 3: Test both
curl http://localhost:8081/get  # httpbin.org
curl http://localhost:8082/get  # postman-echo.com
```

## 📊 Monitoring

### View Logs
```bash
# Forward proxy logs
tail -f forward_proxy.log

# Reverse proxy logs
tail -f reverse_proxy.log
```

### Monitor Connections
```bash
# Watch active connections
watch "netstat -tulpn | grep :8080"

# Monitor proxy traffic
sudo tcpdump -i lo port 8080
```

## 🐛 Troubleshooting

### Common Commands
```bash
# Check if port is in use
sudo lsof -i :8080

# Kill process using port
sudo fuser -k 8080/tcp

# Test connectivity
telnet httpbin.org 80
nc -zv httpbin.org 80
```

### Quick Fixes
```bash
# Permission denied? Use higher port
./bin/reverse_proxy 8080 target.com 80

# Connection refused? Check target
ping target.com
curl http://target.com

# Build errors? Clean and rebuild
make -f Makefile_proxy clean
make -f Makefile_proxy all
```

## 🎯 Example Use Cases

### 1. Development API Gateway
```bash
# Proxy to local development server
./bin/multi_mode_server reverse 8080 localhost 3000
```

### 2. Web Scraping Proxy
```bash
# Forward proxy for scraping
./bin/forward_proxy 3128
# Use in your scraping tools
```

### 3. Load Testing
```bash
# Reverse proxy to test server
./bin/reverse_proxy 8080 your-test-server.com 80
# Run load tests against localhost:8080
```

### 4. API Mocking
```bash
# Proxy to mock service
./bin/reverse_proxy 8080 jsonplaceholder.typicode.com 80
# Test: curl http://localhost:8080/posts/1
```

## 📈 Next Steps

1. **Add Authentication**: Modify proxy.c to add basic auth
2. **Enable Caching**: Add response caching for better performance
3. **Add SSL Support**: Implement HTTPS proxy capabilities
4. **Load Balancing**: Extend reverse proxy for multiple backends
5. **Monitoring**: Add metrics and health checks
