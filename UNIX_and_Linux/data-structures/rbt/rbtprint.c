#include "rbtprint.h"

#include <stdlib.h>

#include "include/doublell.h"
#include "rbt.h"
#include "rbtprintimpl.h"

int rbtPrint(RBT tree, int (*textFunction) (char* buffer, void* content))
{
    return 0;
}

// Implementation only definitions

PLine* rbtNewPLine__(void)
{
    PLine* newLine = malloc(sizeof(PLine));
    if (newLine == NULL)
    {
        return newLine;
    }

    newLine->text = malloc(100);
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

int rbtPLineIncreaseCapacity__(PLine* line)
{
    char* increased = (char*) realloc((void*) line->text, line->capacity + 100);
    if (increased == NULL)
    {
        return -1;
    }

    line->text = increased;
    line->capacity = line->capacity + 100;

    return 0;
}
