#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>


int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Prepare server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(23232); // Port number
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    // Connect to server
    if(connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error connecting" << std::endl;
        return 1;
    }

    // Send data to server
    const char* message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);

    // Receive response from server
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if(bytesRead > 0)
    {
        std::cout << "Server response: " << buffer << std::endl;
    }

    // Close socket
    close(clientSocket);

    return 0;
}
