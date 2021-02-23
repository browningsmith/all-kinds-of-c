#include <stdint.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    FILE* file;

    // Get filename from command line
    if (argc < 2)
    {
        printf(
            "ERROR: filename not specified!\n"
            "Usage: ./main <filename>\n"
        );
        return -1;
    }

    printf("main startup\n");

    // Open file for appending, create if it doesn't exist
    printf("Attempting to open \"%s\"...\n", argv[1]);
    file = fopen(argv[1], "a+");
    if (file == NULL) // fopen returns NULL on error
    {
        perror("Unable to open file");
        return -1;
    }
    printf("Opened the file \"%s\"\n", argv[1]);

    printf("sizeof int8_t: %i\n", sizeof(int8_t));


    return 0;
}

