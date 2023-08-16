#include <iostream> // Library for basic input and output operations.
#include <cstring> // C-style string manipulation functions.
#include <unistd.h> // For POSIX operating system API functions.
#include <arpa/inet.h> // For functions to manipulate IP addresses.


int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr; // Declare a structure to hold the server address information.
    char buffer[1024]; // Declare a character array (buffer) to store data sent and received.

    // Create a socket using the IPv4 address and TCP protocol.
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Prepare server address structure.
    serverAddr.sin_family = AF_INET; // Use IPv4
    serverAddr.sin_port = htons(23232); // Port number (converted to network byte order)
    serverAddr.sin_addr.s_addr = inet_addr("10.127.220.29"); // Server IP address // new: 10.127.220.54 // old: "127.0.0.1" 

    // Connect to server or show error.
    if(connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error connecting" << std::endl;
        return 1;
    }

    // Send data to the server.
    const char* message = "Hello, server(0)!";
    send(clientSocket, message, strlen(message), 0);

    // Receive response from server.
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if(bytesRead > 0)
    {
        std::cout << "Server response: " << buffer << std::endl;
    }

    // Close socket
    close(clientSocket);

    return 0;
}
