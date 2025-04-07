# C++ Web Server

A simple web server implemented in C++ that handles HTTP requests and serves static files.

## Features

- TCP socket communication using Winsock2
- HTTP/1.1 protocol support
- GET request handling
- Static file serving (HTML, JPG, TXT)
- 404 error handling
- Proper connection management

## Project Structure

```
.
├── webserver.cpp    # Main server implementation
├── index.html       # Default landing page
├── duck/            # Directory containing duck images
│   └── duck selfie.jpg
└── plant/           # Directory containing plant-related files
    ├── my_plant.jpg
    └── word.txt
```

## Available Endpoints

- `/` - Main landing page with server information
- `/duck` - Duck selfie page
- `/plant/my_plant.jpg` - Plant image
- `/plant/word.txt` - Text file

## Technical Details

The server is built using:
- Windows Socket API (Winsock2)
- Standard C++ libraries

## How It Works

1. Initializes Winsock2 for network communication
2. Creates a TCP socket and binds it to port 8080
3. Listens for incoming connections
4. Accepts client connections
5. Processes HTTP requests
6. Serves requested files
7. Closes connections properly

## Building and Running

1. Compile the server:
```bash
make main
```

2. Run the server:
```bash
.\webserver.exe
```

3. Access the server using your browser (default port is 8080):
```
http://localhost:8080
```

## Requirements

- Windows operating system
- C++ compiler (g++ or compatible)
- Winsock2 library 