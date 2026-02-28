#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

int client_socket_global = -1;

//  Client 2
void receive_handler() {
    char buffer[1024];
    while (true) {
        if (client_socket_global != -1) {
            memset(buffer, 0, 1024);
            int bytes_received = recv(client_socket_global, buffer, 1024, 0);
            if (bytes_received <= 0) {
                std::cout << "\n[System] Client 2 disconnected." << std::endl;
                exit(0);
            }
            // Carriage return trick to keep the UI clean
            std::cout << "\r" << std::string(30, ' ') << "\r"; 
            std::cout << buffer << std::endl;
            std::cout << "[Client 1]: " << std::flush;
        }
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 1);

    std::cout << "--- Client 1 (Host) Started. Waiting for Client 2... ---" << std::endl;

    client_socket_global = accept(server_fd, NULL, NULL);
    std::cout << "[System] Connection established with Client 2!" << std::endl;

    // Start background thread to listen
    std::thread(receive_handler).detach();

    // MAIN THREAD: Send messages to Client 2
    std::string msg;
    while (true) {
        std::cout << "[Client 1]: " << std::flush;
        std::getline(std::cin, msg);
        if (msg == "exit") break;
        if (!msg.empty()) {
            std::string full_msg = "[Client 1]: " + msg;
            send(client_socket_global, full_msg.c_str(), full_msg.length(), 0);
        }
    }

    close(client_socket_global);
    close(server_fd);
    return 0;
}