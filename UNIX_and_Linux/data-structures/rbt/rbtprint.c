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
    newLine->cursor = 0;

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

int rbtPLineAdvanceCursor__(PLine* line, size_t amount)
{
    line->cursor += amount;

    while (line->cursor >= line->capacity)
    {
        if (rbtPLineIncreaseCapacity__(line) != 0)
        {
            line->cursor -= amount;
            return -1;
        }
    }

    return 0;
}

int rbtPrintAdvanceAll__(DLL* list, size_t amount)
{
    if (dllIsEmpty(*list) == 1)
    {
        return 0;
    }

    DLLIterator iter;
    dllToHead(&iter, list);

    PLine* line;
    dllGetThis(&iter, (void*) &line);
    do
    {
        if (rbtPLineAdvanceCursor__(line, amount) != 0)
        {
            return -1;
        }
    }
    while (dllGetNext(&iter, (void*) &line) == 0);

    return 0;
}
