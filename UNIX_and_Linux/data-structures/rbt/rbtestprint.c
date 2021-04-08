#include "rbtprint.h"

#include <stdio.h>
#include <stdlib.h>

#include "rbtprintimpl.h"

int main()
{
    printf("Running tests on rbtprint\n");

    // Test rbtNewPLine__
    printf("Testing rbtNewPLine__\n");
    {
        PLine* line = rbtNewPLine__();
        if (line == NULL)
        {
            perror("rbtNewPLine__: Error creating new PLine");
            return -1;
        }
        if (line->text == NULL)
        {
            printf("rbtNewPLine__: Error, line->text was set to NULL\n");
            return -1;
        }
        if (line->capacity != 100)
        {
            printf("rbtNewPLine__: Error, line->capacity was not set to 100\n");
            return -1;
        }
        if (line->usage != 0)
        {
            printf("rbtNewPLine__: Error, line->usage was not set to 0\n");
            return -1;
        }

        free(line->text);
        free(line);
    }
    printf("Completed rbtNewPLine__\n");

    // Test rbtDeletePLine__
    printf("Testing rbtDeletePLine__\n");
    {
        PLine* line = rbtNewPLine__();
        if (line == NULL)
        {
            perror("rbtDeletePLine__: Unable to create line");
            return -1;
        }

        rbtDeletePLine__(line);
    }
    printf("Completed rbtDeletePLine__\n");

    // Test rbtPLineIncreaseCapacity__
    printf("Testing rbtPLineIncreaseCapacity__\n");
    {
        // Create new PLine
        PLine* line = rbtNewPLine__();
        if (line == NULL)
        {
            perror("rbtPLineIncreaseCapacity__: Unable to create new line");
            return -1;
        }

        // Fill first 100 chars with 1-100
        for (char i = 1; i < 101; i++)
        {
            line->text[i-1] = i;
        }

        // Test
        char* formerTextPointer = line->text;
        if (rbtPLineIncreaseCapacity__(line) < 0)
        {
            perror("rbtPLineIncreaseCapacity__: Unable to allocate more space for line->text");
            
            if (line->text != formerTextPointer)
            {
                printf("rbtPLineIncreaseCapacity__: Error, function did not leave line->text as the originally allocated pointer\n");
            }

            return -1;
        }
        if (line->capacity != 200)
        {
            printf("rbtPLineIncreaseCapacity__: Did not properly increase capacity\n");
            return -1;
        }
        for (char i = 1; i < 101; i++)
        {
            if (line->text[i-1] != i)
            {
                printf("rbtPLineIncreaseCapacity__: Contents of line->text was changed at index %i\n", i);
            }
        }
        // Test for possible segfaults
        for (char i = 1; i < 101; i++)
        {
            line->text[101 - 1] = i;
        }

        rbtDeletePLine__(line);
    }
    printf("Completed rbtPLineIncreaseCapacity__\n");

    printf("Tests Complete\n");

    return 0;
}