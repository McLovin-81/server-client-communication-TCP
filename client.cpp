#include <iostream>
#include <unistd.h> // For POSIX operating system API (System calls like 'close').
#include <arpa/inet.h> // For functions to manipulate IP addresses (Define the 'struct sockaddr_in' structure and functions like 'inet_addr').


int main()
{
    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == -1)
    {
        std::cerr << "Error: Could not create socket" << std::endl;
        return 1;
    }

    // Prepare server address structure
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(54000);  // Port number
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    // Connect to server
    if (connect(client_socket, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "Error: Could not connect to server" << std::endl;
        return 2;
    }

    // Send messages to server
    std::string message;
    while (true)
    {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);

        if (message == "exit")
        {
            break;
        }

        int send_result = send(client_socket, message.c_str(), message.size(), 0);
        if (send_result == -1)
        {
            std::cerr << "Error: Could not send message to server" << std::endl;
            break;
        }
    }

    // Close socket
    close(client_socket);

    return 0;
}
