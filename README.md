# C++ HTTPS Server

A C++20-based HTTP/HTTPS server implementation for learning purposes.

## Project Structure

```
c_Https_Server/
├── main.cpp           # Main entry point
├── include/            # Header files (.h, .hpp)
│   └── ...            # Organized in subdirectories as needed
├── src/               # Source files (.cpp, .cxx, .cc)
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

- G++ compiler (with C++20 support)
- CMake (3.16 or higher)
- OpenSSL development libraries (optional, for HTTPS support)
- GDB (for debugging)
- Valgrind (optional, for memory debugging)

### Install dependencies on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential cmake libssl-dev gdb valgrind g++-10
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

- All header files should go in the `include/` directory (.h, .hpp)
- All source files should go in the `src/` directory (.cpp, .cxx, .cc)
- Subdirectories are automatically included in the build
- CMake will automatically find and compile all C++ files in `src/`
- The project uses C++20 standard
- Debug builds include `-g -Wall -Wextra -Wpedantic -O0`
- Release builds include `-O3 -DNDEBUG`

## Optional Features

- **OpenSSL Support**: If OpenSSL is found, HTTPS support will be enabled
- **Threading**: pthread library is linked for multi-threading support
- **Math Library**: libm is linked for mathematical operations

## Getting Started

1. Start by implementing your main function in `main.cpp`
2. Create header files in `include/` for your class declarations and function prototypes
3. Implement your classes and functions in source files under `src/`
4. Use the build tasks to compile and test your code
5. Use the debugger to step through your code when needed

Take advantage of C++20 features like:
- Modules (when compiler support is available)
- Concepts
- Ranges
- Coroutines
- std::format
- And much more!

Happy coding! 🚀
