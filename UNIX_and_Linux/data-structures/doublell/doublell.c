#include "doublell.h"

#include <stdio.h>
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

int dllPush(DLL* list, void* content)
{
    DLLNode* newNode = dllNewNode__(content);
    if (newNode == NULL)
    {
        return -1;
    }

    if (dllIsEmpty(*list))
    {
        list->start = newNode;
        list->end = newNode;

        return 0;
    }

    DLLNode* next = list->start;
    newNode->next = next;
    next->prev = newNode;
    list->start = newNode;

    return 0;
}

int dllPushBack(DLL* list, void* content)
{
    DLLNode* newNode = dllNewNode__(content);
    if (newNode == NULL)
    {
        return -1;
    }

    if (dllIsEmpty(*list))
    {
        list->start = newNode;
        list->end = newNode;

        return 0;
    }

    DLLNode* prev = list->end;
    newNode->prev = prev;
    prev->next = newNode;
    list->end = newNode;

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

void* dllDeleteNode__(DLLNode* node)
{
    void* returnContent = node->content;
    DLLNode* prev = node->prev;
    DLLNode* next = node->next;

    // If prev node is not null, set it's next to next
    if (prev != NULL)
    {
        prev->next = next;
    }

    // If next node is not null, set it's prev to prev
    if (next != NULL)
    {
        next->prev = prev;
    }

    free(node);

    return returnContent;
}