#include "rbtprint.h"

#include <stdio.h>

#include "rbtprintimpl.h"

int main()
{
    printf("rbtestprint startup\n");

    PLine* line = newPLine();
    if (line == NULL)
    {
        perror("Unable to create line");
        return -1;
    }

    return 0;
}