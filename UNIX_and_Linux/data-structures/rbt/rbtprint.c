#include "rbtprint.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "include/doublell.h"
#include "rbt.h"
#include "rbtprintimpl.h"

int rbtPrint(RBT tree, int (*textFunction) (char* buffer, void* content))
{
    if (rbtIsEmpty(tree) == 1)
    {
        printf("[TREE EMPTY]\n");
        return 0;
    }

    DLL list;
    DLLIterator iter;
    RBTNode* currentNode = tree.head;

    dllInit(&list);

    // Add head node line
    PLine* line = rbtNewPLine__();
    if (line == NULL)
    {
        perror("Failed to print, rbtNewPLine__ error on first line");
        return -1;
    }
    if (dllPush(&list, (void*) line) != 0)
    {
        perror("Failed to print, dllPush error on first line");
        rbtDeletePLine__((void*) line);
        return -1;
    }

    // Iterate through tree and print nodes
    // State 0: recurse left
    // State 1: print this
    // State 2: recurse right
    int state = 0;
    char buffer[51];
    dllToHead(&iter, &list);
    while (1)
    {
        if (state == 0)
        {
            // Add two lines if needed
            if (dllGetNext(&iter, NULL) != 0)
            {
                for (int i=0; i<2; i++)
                {
                    if (rbtPrintAddPLine__(&iter) != 0)
                    {
                        perror("Error adding new line");
                        dllClear(&list, rbtDeletePLine__);
                        return -1;
                    }
                    dllGetNext(&iter, NULL);
                }
            }

            break;
        }
    }

    // Add null terminator to all lines
    rbtPrintAdvanceAll__(&list, 1);
    {
        dllToHead(&iter, &list);
        PLine* currentLine;
        dllGetThis(&iter, (void*) &currentLine);
        do
        {
            currentLine->text[currentLine->cursor - 1] = '\0';
        }
        while (dllGetNext(&iter, (void*) &currentLine) == 0);   
    }

    //Print all lines
    {
        dllToHead(&iter, &list);
        PLine* currentLine;
        dllGetThis(&iter, (void*) &currentLine);
        int level = 1;
        do
        {
            printf("L%i: %s\n", level, currentLine->text);

            level++;
        }
        while (dllGetNext(&iter, (void*) &currentLine) == 0);   
    }

    dllClear(&list, rbtDeletePLine__);
    
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
    size_t oldCursor = line->cursor;
    line->cursor += amount;

    while (line->cursor >= line->capacity)
    {   
        if (rbtPLineIncreaseCapacity__(line) != 0)
        {
            line->cursor = oldCursor;
            return -1;
        }
    }

    while (oldCursor < line->cursor)
    {
        line->text[oldCursor] = ' ';

        oldCursor++;
    }

    return 0;
}

int rbtPrintAddPLine__(DLLIterator* iter)
{
    PLine* currentLine;
    dllGetThis(iter, (void*) &currentLine);
    if (currentLine == NULL)
    {
        return -1;
    }

    PLine* newLine = rbtNewPLine__();
    if (newLine == NULL)
    {
        return -1;
    }

    if (rbtPLineAdvanceCursor__(newLine, currentLine->cursor) != 0)
    {
        rbtDeletePLine__(newLine);
        return -1;
    }

    if (dllInsertNext(iter, (void*) newLine) != 0)
    {
        rbtDeletePLine__(newLine);
        return -1;
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
