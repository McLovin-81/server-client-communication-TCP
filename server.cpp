#include <iostream>
#include <cstring> // For C-style string manipulation functions (memset: Used to fill memory with a particular value).
#include <unistd.h> // For POSIX operating system API (System calls like 'close').
#include <arpa/inet.h> // For functions to manipulate IP addresses (Define the 'struct sockaddr_in' structure and functions like 'inet_addr').

int main()
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);
    char buffer[1024];

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Prepare server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(23232); // Port number
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces

    // Bind socket to address and port
    if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error binding" << std::endl;
        return 1;
    }
    
    // Listen for incoming connection
    if(listen(serverSocket, 5) == -1)
    {
        std::cerr << "Error listening" << std::endl;
        return 1;
    }
    std::cout << "Server listening on port 23232..." << std::endl;

/*
    // Accept connection from client
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
    }

    // Receive data from client
    ssize_t bytesRead;
    while((bytesRead = recv(newSocket, buffer, sizeof(buffer), 0)) > 0)
    {
        std::cout << "Received: " << buffer << std::endl;
        send(newSocket, buffer, bytesRead, 0); // Echo data back to client
        memset(buffer, 0, sizeof(buffer)); // Clear buffer
    }

    // Close sockets
    close(newSocket);
    close(serverSocket);

    return 0;
}