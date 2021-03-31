#include "doublell.h"

#include <stdlib.h>

//Include implementation-only declarations
#include "doublellimpl.h"

void dllInit(DLL* list)
{
    list->start = NULL;
    list->end = NULL;
}

int dllIsEmpty(DLL list)
{
    if (list.start == NULL)
    {
        return 1;
    }

    return 0;
}

// Implementation-only definitions
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