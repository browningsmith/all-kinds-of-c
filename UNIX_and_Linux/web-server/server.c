#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BACKLOG 10

int main(int argc, char** argv)
{
    int serverSocketFD, clientSocketFD;
    struct sockaddr_in serverAddress;
    uint16_t serverPort;
    struct sockaddr clientAddress;
    socklen_t clientAddressLength;

    // Retrieve port from command line
    if (argc < 2)
    {
        printf("ERROR: Port number not specified.\n");
        printf("Usage: ./server port\n");
        return -1;
    }
    serverPort = atoi(argv[1]);

    printf("Server startup\n");
    printf("Specified port is %i\n", serverPort);

    // Create server socket
    printf("Creating socket\n");
    serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFD < 0) // socket returns -1 on error
    {
        perror("Unable to create socket");
        return -1;
    }
    printf("Socket created\n");

    // Bind server to specified port
    printf("Binding to port %i\n", serverPort);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocketFD, (struct sockaddr*) &serverAddress, sizeof(serverAddress))) // bind returns -1 on error
    {
        perror("Unable to bind to port");
        return -1;
    }
    printf("Bound to port %i\n", serverPort);

    // Set server to listen to incoming connections, with a queue of BACKLOG waiting connections
    printf("Begin listening on server socket\n");
    if (listen(serverSocketFD, BACKLOG)) // listen returns -1 on error
    {
        perror("Unable to listen on socket");
        return -1;
    }
    printf("Server listening for incoming connections...\n");

    // Accept first connection
    clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressLength);
    if (clientSocketFD < 0) // accept returns -1 on error
    {
        perror("Failed to accept connection");
        return -1;
    }
    printf("Accepted new connection to client!\n");

    // Close client socket
    printf("Closing client socket\n");
    if (close(clientSocketFD)) // close returns -1 on error
    {
        perror("Unable to close client socket");
        // Non fatal
    }
    else
    {
        printf("Closed client socket\n");
    }

    // Close server socket
    printf("Closing server socket\n");
    if (close(serverSocketFD)) // close returns -1 on error
    {
        perror("Unable to close server socket");
        // Non fatal
    }
    else
    {
        printf("Closed server socket\n");
    }

    return 0;
}