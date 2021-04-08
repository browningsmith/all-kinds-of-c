#include "rbtprint.h"

#include <stdlib.h>

#include "include/doublell.h"

PLine* newPLine(void)
{
    PLine* newLine = malloc(sizeof(PLine));
    if (newLine == NULL)
    {
        return newLine;
    }

    newLine->text = malloc(sizeof(100));
    if (newLine->text == NULL)
    {
        free(newLine);
	return NULL;
    }

    newLine->capacity = 100;
    newLine->usage = 0;

    return newLine;
}
