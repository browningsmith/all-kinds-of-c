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

typedef struct {
    
    int fd;
    char* name;
    int exists;

} SocketData;

typedef struct {

    int errLimit;
    SocketData listenSocket, clientSocket;

} GlobalData;

void checkErrorLimit(GlobalData* globalData);
int closeSocket(SocketData* s);

int main()
{
    GlobalData globalData = {

        .errLimit = ERROR_LIMIT,

        .listenSocket = {

            .name = "listen",
            .exists = 0,
        },

        .clientSocket = {

            .name = "client",
            .exists = 0,
        }
    };

    struct sockaddr_in serverAddress;
    struct sockaddr clientAddress;
    socklen_t clientAddressSize;

    char buffer[BUFF_LEN + 1];
    
    printf("webserver startup\n");
    
    // Create socket
    globalData.listenSocket.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (globalData.listenSocket.fd < 0)
    {
        perror("unable to create listen socket");
        return -1;
    }
    printf("created listen socket\n");
    globalData.listenSocket.exists = 1;

    // Populate address info for the server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(HTML_ALT_PORT);

    // Bind the listenSocket to the port
    if (bind(globalData.listenSocket.fd, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("unable to bind the listen socket to port");

        return -1;
    }
    printf("bound listen socket to port %i\n", HTML_ALT_PORT);

    // Set socket to listen
    if (listen(globalData.listenSocket.fd, BACKLOG) < -1)
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

        globalData.clientSocket.fd = accept(globalData.listenSocket.fd, &clientAddress, &clientAddressSize);
        if (globalData.clientSocket.fd < 0)
        {
            perror("Error on accept() call:");
            checkErrorLimit(&globalData);
        }
        printf("webserver accepted new connection\n");
        globalData.clientSocket.exists = 1;

        // Begin reading data from client
        while (1)
        {
            // Clear the buffer
            bzero(buffer, BUFF_LEN);
            printf("Waiting for new message\n");

            int receivedBytes = recv(globalData.clientSocket.fd, buffer, BUFF_LEN, 0);
            if (receivedBytes < 1) // Either controlled shutdown (0) or error (-1)
            {
                if (receivedBytes == 0) // controlled shutdown
                {
                    printf("Client closed the connection\n");
                }
                else //error
                {
                    perror("webserver received error on call to recv()");
                    checkErrorLimit(&globalData);
                }

                if (closeSocket(&globalData.clientSocket) < 0)
                {
                    checkErrorLimit(&globalData);
                }

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
                    globalData.clientSocket.fd,
                    "HTTP/1.1 418 I'm a teapot!\r\n",
                    strlen("HTTP/1.1 418 I'm a teapot!\r\n"),
                    0
                );
            }
        }
    }

    // Close listen socket
    closeSocket(&globalData.listenSocket);

    return 0;
}

void checkErrorLimit(GlobalData* globalData)
{
    (globalData->errLimit)--;

    if (globalData->errLimit < 1)
    {
        printf("Error limit reached, exiting\n");
        closeSocket(&globalData->clientSocket);
        closeSocket(&globalData->listenSocket);
        exit(-1);
    }

    return;
}

int closeSocket(SocketData* s)
{
    if (s->exists != 0)
    {
        s->exists = 0;

        if (close(s->fd) < 0)
        {
            printf("Unable to properly close socket: %s\n", s->name);
            perror("");
            return -1;
        }

        printf("Closed socket: %s\n", s->name);
    }

    return 0;
}