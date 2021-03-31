#include "doublell.h"

#include <stdlib.h>

void dllInit(DLL* list)
{
    list->start = NULL;
    list->end = NULL;
}

// Helper functions
DLLNode* dllNewNode__(void* content)
{
    DLLNode* newNode = malloc(sizeof(DLLNode));
    if (newNode == NULL)
    {
        return NULL;
    }

    // Initialize values
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->content = content;

    return newNode;
}