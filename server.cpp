#include <iostream>
#include <cstring> // For C-style string manipulation functions (memset: Used to fill memory with a particular value).
#include <unistd.h> // For POSIX operating system API (System calls like 'close').
#include <arpa/inet.h> // For functions to manipulate IP addresses (Define the 'struct sockaddr_in' structure and functions like 'inet_addr').
#include <thread>
#include <vector>


// Function prototypes
void clientHandler(int client_socket, char clientIP[INET_ADDRSTRLEN]);


int main()
{
    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == -1)
    {
        std::cerr << "Error: Could not create socket" << std::endl;
        return 1;
    }

    // Prepare server address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(54000);  // Port number
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_socket, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "Error: Could not bind socket to IP/Port" << std::endl;
        close(server_socket);
        return 2;
    }

    // Listen
    if (listen(server_socket, SOMAXCONN) == -1)
    {
        std::cerr << "Error: Could not listen for connections" << std::endl;
        close(server_socket);
        return 3;
    }

    // Accept and handle multiple clients
    while (true)
    {
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket == -1)
        {
            std::cerr << "Error: Could not accept client connection" << std::endl;
            continue;
        }

        // Get client ip
        struct sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);
        if (getpeername(client_socket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressSize) == -1)
        {
            std::cerr << "Error: Could not get client address" << std::endl;
            close(client_socket);
            continue;
        }
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddress.sin_addr, clientIP, INET_ADDRSTRLEN);

        std::cout << "Connected with: " << clientIP << std::endl;

        // Create new thread to handle client
        std::thread client_thread(clientHandler, client_socket, clientIP);
        client_thread.detach(); // Detach thread to allow it to run independently
    }

    // Close server socket
    close(server_socket);

    return 0;
}


// Function to handle client requests
void clientHandler(int client_socket, char clientIP[INET_ADDRSTRLEN])
{
    char buffer[4096];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received == -1)
        {
            std::cerr << "Error: Could not receive message from client" << std::endl;
            break;
        }
        else if (bytes_received == 0)
        {
            std::cout << "Client " << clientIP << " disconnected" << std::endl;
            break;
        }

        std::string clientMessage = std::string(buffer, 0, bytes_received);

        if (clientMessage == "send")
        {
            std::string response = "take data";
            int sendResponse = send(client_socket, response.c_str(), response.size(), 0);
        }

        std::cout << "Client " << clientIP << ": " << clientMessage << std::endl;
    }

    close(client_socket);
}

// How to compile: g++ server.cpp -o server -lpthread -std=c++20 
