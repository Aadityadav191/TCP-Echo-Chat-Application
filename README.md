# Simple TCP Echo Chat Application
**Course:** Network Programming  
**Platform:** Unix/Linux/macOS (Sockets)  
**Language:** C++

## 1. Project Overview
This project is a small-scale networking application demonstrating the core concepts of **TCP/IP Sockets**. It follows a Client-Server architecture where:
- The **Server** creates a socket, binds to a port, and listens for incoming connections.
- The **Client** connects to the server and sends text messages.
- The **Server** receives the data and "echoes" it back to the client to confirm a successful two-way communication link.

## 2. Key Networking Concepts Demonstrated
* **Socket Creation:** `socket(AF_INET, SOCK_STREAM, 0)`
* **Addressing:** Using `sockaddr_in` and `htons` for network byte ordering.
* **Passive Open:** Server-side `bind()` and `listen()`.
* **Active Open:** Client-side `connect()`.
* **Data Transfer:** `send()` and `recv()` for buffered communication.

---

## 3. Build & Run Instructions

### Prerequisites
- A C++ compiler (G++ recommended).
- A terminal (Terminal.app on macOS or Bash on Linux).

### Step 1: Compilation
Open your terminal and run the following commands to compile the source files into executables:

```bash
# Compile the Server
g++ server.cpp -o server

# Compile the Client
g++ client.cpp -o client