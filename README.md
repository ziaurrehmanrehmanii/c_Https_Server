# C HTTPS Server

A C-based HTTP/HTTPS server implementation with **Forward and Reverse Proxy** capabilities for learning purposes.

## 🌟 Features

- **Basic HTTP Server**: Serves static content (original functionality)
- **Forward Proxy**: Client → Proxy → Internet (web filtering, monitoring)
- **Reverse Proxy**: Client → Proxy → Backend Server (load balancing, API gateway)
- **Request Logging**: Monitor all proxy traffic
- **Multi-Mode Support**: Single binary with multiple operation modes

## 🚀 Quick Start

### Basic HTTP Server (Original)
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/bin/c_https_server
# Visit: http://localhost:8080
```

### Proxy Examples
```bash
cd examples
make -f Makefile_proxy all

# Forward Proxy
./bin/forward_proxy 3128

# Reverse Proxy
./bin/reverse_proxy 8080 httpbin.org 80

# Multi-mode server
./bin/multi_mode_server server 8000    # Basic server
./bin/multi_mode_server forward 3128   # Forward proxy
./bin/multi_mode_server reverse 8080 google.com 80  # Reverse proxy
```

📖 **See [Quick Proxy Guide](Docs/QUICK_PROXY_GUIDE.md) for 5-minute setup**

📚 **See [Proxy Documentation](Docs/PROXY_DOCUMENTATION.md) for complete reference**

## Project Structure

```
c_Https_Server/
├── main.c              # Main entry point
├── include/            # Header files (.h)
│   └── ...            # Organized in subdirectories as needed
├── src/               # Source files (.c)
│   └── ...            # Organized in subdirectories as needed
├── build/             # Build output (generated)
├── CMakeLists.txt     # CMake configuration
└── .vscode/           # VS Code configuration
    ├── tasks.json     # Build and run tasks
    ├── launch.json    # Debug configuration
    ├── c_cpp_properties.json  # IntelliSense configuration
    └── settings.json  # Workspace settings
```

## Prerequisites

Make sure you have the following installed:

- GCC compiler
- CMake (3.16 or higher)
- OpenSSL development libraries (optional, for HTTPS support)
- GDB (for debugging)
- Valgrind (optional, for memory debugging)

### Install dependencies on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential cmake libssl-dev gdb valgrind
```

## Building the Project

### Using VS Code Tasks (Recommended)

1. Open the project in VS Code
2. Use `Ctrl+Shift+P` and run "Tasks: Run Task"
3. Select "Build Debug" to build in debug mode
4. Or select "Build Release" for optimized release build

### Using Command Line

```bash
# Configure the project
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# Build the project
cmake --build build -j4

# The executable will be in build/bin/c_https_server
```

## Running the Server

### Using VS Code Task

1. Use `Ctrl+Shift+P` and run "Tasks: Run Task"
2. Select "Run HTTP Server"

### Using Command Line

```bash
./build/bin/c_https_server
```

## Debugging

### Using VS Code

1. Set breakpoints in your code
2. Press `F5` or use "Run and Debug" panel
3. Select "Debug HTTP Server" configuration

### Memory Debugging with Valgrind

Use the "Run with Valgrind" task or run manually:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./build/bin/c_https_server
```

## Available VS Code Tasks

- **Configure Debug**: Configure CMake for debug build
- **Configure Release**: Configure CMake for release build
- **Build Debug**: Build the project in debug mode (default)
- **Build Release**: Build the project in release mode
- **Clean**: Remove build directory
- **Run HTTP Server**: Build and run the server
- **Run with Valgrind**: Build and run with memory checking

## Development Notes

- All header files should go in the `include/` directory
- All source files should go in the `src/` directory
- Subdirectories are automatically included in the build
- CMake will automatically find and compile all `.c` files in `src/`
- The project uses C99 standard
- Debug builds include `-g -Wall -Wextra -Wpedantic -O0`
- Release builds include `-O3 -DNDEBUG`

## Optional Features

- **OpenSSL Support**: If OpenSSL is found, HTTPS support will be enabled
- **Threading**: pthread library is linked for multi-threading support
- **Math Library**: libm is linked for mathematical operations

## Getting Started

1. Start by implementing your main function in `main.c`
2. Create header files in `include/` for your function declarations
3. Implement your functions in source files under `src/`
4. Use the build tasks to compile and test your code
5. Use the debugger to step through your code when needed

Happy coding! 🚀
