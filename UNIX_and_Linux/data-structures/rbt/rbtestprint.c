#include "rbtprint.h"

#include <stdio.h>
#include <stdlib.h>

#include "rbtprintimpl.h"

int main()
{
    printf("Running tests on rbtprint\n");

    // Test newPLine
    printf("Testing newPLine\n");
    {
        PLine* line = newPLine();
        if (line == NULL)
        {
            perror("newPLine: Error creating new PLine");
            return -1;
        }
        if (line->text == NULL)
        {
            printf("newPLine: Error, line->text was set to NULL\n");
            return -1;
        }
        if (line->capacity != 100)
        {
            printf("newPLine: Error, line->capacity was not set to 100\n");
            return -1;
        }
        if (line->usage != 0)
        {
            printf("newPLine: Error, line->usage was not set to 0\n");
            return -1;
        }

        free(line->text);
        free(line);
    }
    printf("Completed newPLine\n");

    printf("Tests Complete\n");

    return 0;
}