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
    printf("Testing rbtDeletePLine__\n");

    printf("Tests Complete\n");

    return 0;
}