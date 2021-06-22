#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_LEN 1024
#define HTML_ALT_PORT 8080
#define BACKLOG 10
#define ERROR_LIMIT 100

void checkErrorLimit(int* errLimit);

int main()
{
    int errLimit = ERROR_LIMIT;
    
    int listenSocket, clientSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr clientAddress;
    socklen_t clientAddressSize;

    char buffer[BUFF_LEN + 1];
    
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
        clientAddressSize = sizeof(struct sockaddr); // man page for accept essentially says addrlen field should be initialized to sizeof(struct sockaddr) before accept() call

        printf("Waiting for new connection...\n");

        clientSocket = accept(listenSocket, &clientAddress, &clientAddressSize);
        if (clientSocket < 0)
        {
            perror("Error on accept() call:");
            checkErrorLimit(&errLimit);
        }
        printf("webserver accepted new connection\n");

        // Begin reading data from client
        while (1)
        {
            // Clear the buffer
            bzero(buffer, BUFF_LEN);
            printf("Waiting for new message\n");

            int receivedBytes = recv(clientSocket, buffer, BUFF_LEN, 0);
            if (receivedBytes < 1) // Either controlled shutdown (0) or error (-1)
            {
                if (receivedBytes == 0) // controlled shutdown
                {
                    printf("Client closed the connection\n");
                }
                else //error
                {
                    perror("webserver received error on call to recv()");
                    checkErrorLimit(&errLimit);
                }

                if (close(clientSocket) < 0)
                {
                    perror("unable to properly close client socket");
                    checkErrorLimit(&errLimit);
                }
                printf("Closed client socket\n");

                break;
            }
            else
            {
                printf("Message received:\n");
                
                for (int i=0; i<receivedBytes; i++)
                {
                    putchar(buffer[i]);
                }

                fflush(stdout);

                send(
                    clientSocket,
                    "HTTP/1.1 200 OK\r\n<html><head>Hello</head><body>hello</body></html>\r\n",
                    strlen("HTTP/1.1 200 OK\r\n<html><head>Hello</head><body>hello</body></html>\r\n"),
                    0
                );

                if (close(clientSocket) < 0)
                {
                    perror("unable to properly close client socket");
                    checkErrorLimit(&errLimit);
                }
                printf("Closed client socket\n");

                break;
            }
        }
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

void checkErrorLimit(int* errLimit)
{
    (*errLimit)--;

    if (*errLimit < 1)
    {
        printf("Error limit reached, exiting\n");
        exit(-1);
    }

    return;
}