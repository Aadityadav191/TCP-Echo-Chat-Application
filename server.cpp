#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // 1. Create Socket (IPv4, TCP)
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 2. Bind to Port 8080
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept any IP
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    // 3. Listen for Clients
    listen(server_fd, 3);
    std::cout << "Server listening on port 8080..." << std::endl;

    // 4. Accept a Connection
    int client_socket = accept(server_fd, NULL, NULL);
    std::cout << "Client connected!" << std::endl;

    // 5. Chat Loop
    char buffer[1024];
    while (true) {
        memset(buffer, 0, 1024);
        int bytes_received = recv(client_socket, buffer, 1024, 0);
        if (bytes_received <= 0) break;

        std::cout << "Client says: " << buffer << std::endl;
        send(client_socket, buffer, bytes_received, 0); // Echo back
    }

    close(client_socket);
    close(server_fd);
    return 0;
}