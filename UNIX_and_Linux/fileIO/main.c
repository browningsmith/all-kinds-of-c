#include <stdio.h>

int main(int argc, char** argv)
{
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

    return 0;
}
