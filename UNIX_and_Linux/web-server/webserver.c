#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define HTML_ALT_PORT 8080
#define BACKLOG 10

int main()
{
    int listenSocket, clientSocket;
    struct sockaddr_in serverAddress;
    
    printf("webserver startup\n");
    
    // Create socket
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket < 0)
    {
        perror("unable to create listen socket");
        return -1;
    }
    printf("created listen socket\n");

    // Populate address info for the server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(HTML_ALT_PORT);

    // Bind the listenSocket to the port
    if (bind(listenSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("unable to bind the listen socket to port");

        return -1;
    }
    printf("bound listen socket to port %i\n", HTML_ALT_PORT);

    // Set socket to listen
    if (listen(listenSocket, BACKLOG) < -1)
    {
        perror("listen() failed on listen socket");

        return -1;
    }
    printf("Set listen socket to listen for incoming connections\n");

    // Begin listening for connections
    while (1)
    {
        
    }

    // Close listen socket
    if (close(listenSocket) < 0)
    {
        perror("unable to properly close listen socket");
        // non fatal
    }
    printf("closed listen socket\n");

    return 0;
}