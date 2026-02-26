#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 1. Create Socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Connect to Server (localhost)
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Connection Failed" << std::endl;
        return -1;
    }

    // 3. Chat Loop
    char buffer[1024];
    std::string message;
    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);
        if (message == "exit") break;

        send(sock, message.c_str(), message.length(), 0);
        
        memset(buffer, 0, 1024);
        recv(sock, buffer, 1024, 0);
        std::cout << "Server echoed: " << buffer << std::endl;
    }

    close(sock);
    return 0;
}