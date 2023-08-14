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
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
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
    if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
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

/*
    // Accept 1 connection from client
    newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
    if(newSocket == -1)
    {
        std::cerr << "Error accepting connection" << std::endl;
        return 1;
    }
*/

    // Stay on and accept client connections in a loop
    while(true)
    {
        newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr,&addrSize);
        if(newSocket == -1)
        {
            std::cerr << "Error accepting connection" << std::endl;
            return 1;
        }

        // Get the client's IP address and port
        char clientIP[INET_ADDRSTRLEN];  // INET_ADDRSTRLEN is a constant for IPv4 address length
        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
    
        // Receive data from the client into the 'buffer' array.
        ssize_t bytesRead;
        while((bytesRead = recv(newSocket, buffer, sizeof(buffer), 0)) > 0)
        {
<<<<<<< HEAD
            std::cout << "Received from client " << inet_ntoa(clientAddr.sin_addr) << ": " << buffer << std::endl;
=======
            std::cout << "Received from " << clientIP << ": " << buffer << std::endl;
>>>>>>> ea4371f7cdcf7b293b97aeae6437e0ff3c901004
            // Send the received data back to the client (echo).
            send(newSocket, /*buffer*/ "Hello back", bytesRead, 0);
            // Clear the 'buffer' array for the next iteration.
            memset(buffer, 0, sizeof(buffer));
        }
    }

    // Close sockets. Currently never reached!
    close(newSocket);
    close(serverSocket);

    return 0;
}