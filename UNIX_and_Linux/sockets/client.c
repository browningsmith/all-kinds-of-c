#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "myitoa.h"

#define BUFFLEN 1024

int main(int argc, char** argv)
{
    
    char lineBuffer[BUFFLEN + 2]; // Additional two bytes, one for newline and one for null term
    uint16_t messageLength;
    char lengthBuffer[5];
    int serverSocketFD;
    struct sockaddr_in serverAddress;
    in_port_t serverPort;
    
    // Get IP and port number from command line
    if (argc < 3)
    {
        printf(
            "  ERROR: IP address/port not specified!\n"
            "  Usage: ./client <IP address> <port>\n"
            "Example: ./client 127.0.0.1 8080\n"
        );
        return -1;
    }
    serverPort = atoi(argv[2]);
    
    printf("Client startup\n");
    printf("Specified IP: %s\n", argv[1]);
    printf("Specified port: %i\n", serverPort);

    // Create socket
    printf("Attempting to create socket...\n");
    serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFD < 0) // socket returns -1 on error
    {
        perror("Unable to create socket");
        return -1;
    }
    printf("Created socket\n");

    // Connect to server
    printf("Attempting to connect with server\n");
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddress.sin_port = htons(serverPort);
    if (connect(serverSocketFD, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) // connect returns -1 on error
    {
        perror("Unable to connect");
        return -1;
    }
    printf("Connection established with server!\n");

    //Send lines from stdin to server
    printf(
        "Type a message and hit ENTER to send a message to the server.\n"
        "Type CTRL+D to close connection\n"
        "Message: "
    );
    while (fgets(lineBuffer, BUFFLEN + 2, stdin) != NULL) // fgets returns NULL on error or EOF (CTRL+D)
    {
        messageLength = strlen(lineBuffer) - 1;
        myitoa(lengthBuffer, messageLength);
        lengthBuffer[4] = (char) 0;
        printf("Message length: %s\n", lengthBuffer);
        printf("Message: ");
    }
    printf("\n");

    // Close socket
    printf("Attempting to close socket...\n");
    if (close(serverSocketFD) < 0) // close returns -1 on error
    {
        perror("Unable to close socket");
        // non fatal
    }
    printf("Closed socket\n");

    return 0;
}
