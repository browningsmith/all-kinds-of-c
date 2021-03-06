#include <stdio.h>

#define BUFFLEN 1024

int main(int argc, char** argv)
{
    FILE* file;
    char buffer[BUFFLEN + 1];

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

    // Read lines from stdin and write to file
    printf("Enter text to write to the file.\n");
    printf("Press CTRL+D when you are done: ");
    while (fgets(buffer, BUFFLEN + 1, stdin))
    {
        if (fputs(buffer, file) == EOF) // fputs returns EOF on error
        {
            perror("Error writing line to file");
            return -1;
        }
    }

    // Close file
    printf("Attempting to close file \"%s\"...\n", argv[1]);
    if (fclose(file) == EOF) // fclose returns EOF on error
    {
        perror("Unable to close file");
        // non fatal
    }
    else
    {
        printf("Closed the file \"%s\"\n", argv[1]);
    }

    return 0;
}

