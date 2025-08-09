
# Simple C Web Server (Windows)

This is a simple web server implemented in C using the WinSock2 API. It listens on port 80 and serves the contents of an `index.html` file to connected clients.

## Features

- Uses WinSock2 for networking on Windows.
- Accepts incoming TCP connections on port 80.
- Reads and sends the content of `index.html` as an HTTP response.
- Basic error handling and logging on the console.

## Requirements

- Windows OS
- A C compiler that supports WinSock2 (e.g., MSVC)
- `index.html` file in the same directory as the executable.

## How to Compile

If using Visual Studio Developer Command Prompt:

```bash
cl /W4 /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE main.c ws2_32.lib
```

## How to Use

1. Place your `index.html` file in the same directory as the compiled executable.
2. Run the executable (requires administrator privileges to bind to port 80).
3. Open a browser and navigate to `http://localhost/` to see the served page.
4. The server will print connection logs and errors in the console.

## Notes

- The server currently reads and sends up to 1024 bytes from the file.
- This is a minimal example intended for learning or simple testing.
- No support for multiple simultaneous clients or persistent connections.
- Make sure port 80 is free and you run with appropriate permissions.

## License

This project is open source under the MIT License.

