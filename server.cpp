#include <iostream>
#include <cstring> // For C-style string manipulation functions (memset: Used to fill memory with a particular value).
#include <unistd.h> // For POSIX operating system API (System calls like 'close').
#include <arpa/inet.h> // For functions to manipulate IP addresses (Define the 'struct sockaddr_in' structure and functions like 'inet_addr').

int main()
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);
    char buffer[1024]; // Declare a character array (buffer) to store data sent and received.

    // Create socket using IPv4 address and TCP protocol
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Prepare server address structure.
    serverAddr.sin_family = AF_INET; // Use IPv4
    serverAddr.sin_port = htons(23232); // Port number (converted to network byte)
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces

    // Bind socket to the specified address and port.
    if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) // Casts the pointer to the serverAddr structure to a pointer of type struct sockaddr*. This is necessary because the bind function expects a pointer to a sockaddr structure as its second argument.
    {
        std::cerr << "Error binding" << std::endl;
        return 1;
    }
    
    // Listen for incoming connections on the socket,
    // with a maximum backlog of 5 pending connections.
    if(listen(serverSocket, 5) == -1)
    {
        std::cerr << "Error listening" << std::endl;
        return 1;
    }
    std::cout << "Server listening on port 23232..." << std::endl;

    // Stay on and accept client connections in a loop
    while(true)
    {
        // newSocket = Client connection.
        newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
        if(newSocket == -1)
        {
            std::cerr << "Error accepting connection" << std::endl;
            return 1;
        }

        // Get the client's IP address and port
        char clientIP[INET_ADDRSTRLEN];  // INET_ADDRSTRLEN is a constant for IPv4 address length
        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
    
        // Receive and process messages from the client.
        uint32_t msgLength = 0;
        ssize_t bytesRead = recv(newSocket, &msgLength, sizeof(msgLength), 0);

        if(bytesRead <= 0)
        {
            std::cerr << "Error receiving message length" << std::endl;
            return 1;
        }

        msgLength = ntohl(msgLength); // Convert network byte order to host byte order.

        // Receive the actual message.
        bytesRead = recv(newSocket, buffer, msgLength, 0);
        if(bytesRead <= 0)
        {
            std::cerr << "Error receiving message" << std::endl;
            return 1;
        }

        std::cout << "Received from client " << clientIP << ": " << buffer << std::endl;

        // Echo message
        const char* echoMessage = "Hello Back";
        uint32_t echoLength = htonl(strlen(echoMessage)); // Convert echo message length to network byte order.

        // Send echo back to client.
        send(newSocket, &echoLength, sizeof(echoLength), 0); // Send the length first
        send(newSocket, echoMessage, strlen(echoMessage), 0); // Send the echo message itself

        // Clear the 'buffer' array for the next iteration.
        memset(buffer, 0, sizeof(buffer));
    }

    // Close sockets. Currently never reached!
    close(newSocket); // Close this client connection.
    close(serverSocket);

    return 0;
}
