#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h> // Do i need this?

int main() {
    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0); // Replace 0 with IPPROTO_TCP
    if (server_socket == -1) {
        std::cerr << "Error: Could not create socket\n";
        return 1;
    }

    // Prepare server address structure
    sockaddr_in server_address; // Add struct
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(54000);  // Port number
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_socket, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) == -1) {
        std::cerr << "Error: Could not bind socket to IP/Port\n";
        return 2;
    }

    // Listen
    if (listen(server_socket, SOMAXCONN) == -1) {
        std::cerr << "Error: Could not listen for connections\n";
        return 3;
    }

    // Accept a client
    int client_socket = accept(server_socket, nullptr, nullptr);
    if (client_socket == -1) {
        std::cerr << "Error: Could not accept client connection\n";
        return 4;
    }

    // Receive and print messages from client
    char buffer[4096];
    while (true) {
        memset(buffer, 0, sizeof(buffer));

        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received == -1) {
            std::cerr << "Error: Could not receive message from client\n";
            break;
        } else if (bytes_received == 0) {
            std::cout << "Client disconnected\n";
            break;
        }
        
        std::cout << "Client: " << std::string(buffer, 0, bytes_received) << std::endl;
    }

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
