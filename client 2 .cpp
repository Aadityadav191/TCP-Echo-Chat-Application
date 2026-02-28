#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

// BACKGROUND THREAD: Listen for messages from Client 1
void receive_handler(int sock) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, 1024);
        int bytes = recv(sock, buffer, 1024, 0);
        if (bytes <= 0) {
            std::cout << "\n[System] Connection lost from Client 1." << std::endl;
            exit(0);
        }
        // Clear current line and print message
        std::cout << "\r" << std::string(30, ' ') << "\r";
        std::cout << buffer << std::endl;
        std::cout << "[Client 2]: " << std::flush;
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "[Error] Client 1 is not online!" << std::endl;
        return -1;
    }

    std::cout << "--- Client 2 Connected to Client 1 ---" << std::endl;

    // Start background thread to listen
    std::thread(receive_handler, sock).detach();

    // MAIN THREAD: Send messages to Client 1
    std::string msg;
    while (true) {
        std::cout << "[Client 2]: " << std::flush;
        std::getline(std::cin, msg);
        if (msg == "exit") break;
        if (!msg.empty()) {
            std::string full_msg = "[Client 2]: " + msg;
            send(sock, full_msg.c_str(), full_msg.length(), 0);
        }
    }

    close(sock);
    return 0;
}