#include "doublell.h"

#include <stdio.h>
#include <stdlib.h>

//Include implementation-only declarations
#include "doublellimpl.h"

void dllInit(DLL* list)
{
    list->head = NULL;
    list->tail = NULL;
}

int dllIsEmpty(DLL list)
{
    if (list.head == NULL)
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
        list->head = newNode;
        list->tail = newNode;

        return 0;
    }

    DLLNode* next = list->head;
    newNode->next = next;
    next->prev = newNode;
    list->head = newNode;

    return 0;
}

int dllPushTail(DLL* list, void* content)
{
    DLLNode* newNode = dllNewNode__(content);
    if (newNode == NULL)
    {
        return -1;
    }

    if (dllIsEmpty(*list))
    {
        list->head = newNode;
        list->tail = newNode;

        return 0;
    }

    DLLNode* prev = list->tail;
    newNode->prev = prev;
    prev->next = newNode;
    list->tail = newNode;

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