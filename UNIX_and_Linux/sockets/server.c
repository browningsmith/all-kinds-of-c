#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int serverSocketFD;
    struct sockaddr_in serverAddress;
    in_port_t serverPort;

    // Get port number from command line
    if (argc < 2)
    {
        printf(
            "  ERROR: Port number not specified!\n"
            "  Usage: ./server <port>\n"
            "Example: ./server 8080\n"
        );
        return -1;
    }
    serverPort = atoi(argv[1]);
    
    printf("Server startup\n");
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

    //Close server socket
    printf("Attempting to close server socket...\n");
    if (close(serverSocketFD) < 0) // close returns -1 on error
    {
        perror("Unable to close server socket");
        // non fatal
    }
    printf("Closed server socket\n");

    return 0;
}
