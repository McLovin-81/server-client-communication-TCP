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
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    // Connect to server.
    std::cout << "Connecting.." << std::endl;
    int connectionStatus = connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr));
    while (connectionStatus == -1)
    {
        // If connection failed, retry until successful.
        connectionStatus = connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr));
    }

    std::cout << "Connection successful" << std::endl;

    while(true)
    {
        // Get message from the user.
        std::cout << "Enter your message: ";
        std::string userMessage;
        std::getline(std::cin, userMessage);

        // Send data to the server.
        // const char* message = "Hello, server -> From client zero!";
        uint32_t msgLeng = htonl(userMessage.length()); // Convert message length to nertwork byte order

        // Send message length and then the message content.
        send(clientSocket, &msgLeng, sizeof(msgLeng), 0);
        send(clientSocket, userMessage.c_str(), userMessage.length(), 0);

        // Receive response from server.
        uint32_t responseLength = 0;

        ssize_t bytesRead = recv(clientSocket, &responseLength, sizeof(responseLength), 0);
        if(bytesRead <= 0)
        {
            std::cerr << "Error receiving message length" << std::endl;
            break;
        }

        responseLength = ntohl(responseLength); // Convert network byte order to host byte order

        // Receive Response (echo)
        bytesRead = recv(clientSocket, buffer, responseLength, 0);
        if(bytesRead <= 0)
        {
            std::cerr << "Error receiving message" << std::endl;
            break;
        }

        std::cout << "Response from server " << inet_ntoa(serverAddr.sin_addr) << ": " << buffer << std::endl;

        // sleep(1); // Delay between messages (optional)
    }

    // Close socket
    close(clientSocket);

    return 0;
}
