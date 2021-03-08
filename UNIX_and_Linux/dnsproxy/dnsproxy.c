#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXBACKLOG 10

int main(int argc, char** argv)
{
    int serverSocketFD, clientSocketFD;
    struct sockaddr_in serverAddress;
    in_port_t serverPort;
    struct sockaddr clientAddress;
    socklen_t clientAddressLength;
    

    // Get port number from command line
    if (argc < 2)
    {
        printf(
            "  ERROR: Port number not specified!\n"
            "  Usage: ./dnsproxy <port>\n"
            "Example: ./dnsproxy 8080\n"
        );
        return -1;
    }
    serverPort = atoi(argv[1]);
    
    printf("dnsproxy startup\n");
    printf("Specified port: %i\n", serverPort);

    // Create server socket
    printf("Attempting to create socket...\n");
    serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFD < 0) // socket returns -1 on error
    {
        perror("Unable to create socket");
        return -1;
    }
    printf("Created socket\n");

    // Bind socket to specified port
    printf("Attempting to bind to port %i\n", serverPort);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(serverPort);
    if (bind(serverSocketFD, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) // bind returns -1 on error
    {
        perror("Unable to bind to port");
        return -1;
    }
    printf("Successfully bound to port %i\n", serverPort);

    // Listen on socket for incoming connections
    if (listen(serverSocketFD, MAXBACKLOG) < 0) // listen 
    {
        perror("Server unable to listen");
        return -1;
    }
    printf("Listening for incoming connections...\n");

    // Accept an incoming connection
    clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressLength);
    if (clientSocketFD < 0) // accept returns -1 on error
    {
        perror("Unable to accept incoming connection");
        return -1;
    }
    printf("Connection established with client!\n");

    // Close server socket
    printf("Attempting to close server socket...\n");
    if (close(serverSocketFD) < 0) // close returns -1 on error
    {
        perror("Unable to close server socket");
        // non fatal
    }
    printf("Closed server socket\n");

    return 0;
}
