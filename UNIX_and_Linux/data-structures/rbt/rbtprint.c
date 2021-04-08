#include "rbtprint.h"

#include <stdlib.h>

#include "include/doublell.h"
#include "rbtprintimpl.h"

// Implementation only definitions

PLine* rbtNewPLine__(void)
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

int rbtDeletePLine__(void* line)
{
    PLine* castLine = (PLine*) line;

    free(castLine->text);
    free(castLine);

    return 0;
}
