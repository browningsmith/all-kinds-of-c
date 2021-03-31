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
    if (list.head == NULL || list.tail == NULL)
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

int dllGet(DLL list, void** returnedContent)
{
    if (dllIsEmpty(list))
    {
        *returnedContent = NULL;
        return -1;
    }

    *returnedContent = list.head->content;
    return 0;
}

int dllGetTail(DLL list, void** returnedContent)
{
    if (list.tail == NULL)
    {
        *returnedContent = NULL;
        return -1;
    }

    *returnedContent = list.tail->content;
    return 0;
}

int dllPop(DLL* list, void** returnedContent)
{
    if (dllIsEmpty(*list))
    {
        *returnedContent = NULL;
        return -1;
    }

    DLLNode* nodeToDelete = list->head;

    // If the head and tail are the same, then this is the only node to delete
    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    // Otherwise, head needs to be set to nodeToDelete->next
    else
    {
        if (list->head->next == NULL)
        {
            *returnedContent = NULL;
            return -1;
        }

        list->head = nodeToDelete->next;
        list->head->prev = NULL;
    }

    *returnedContent = nodeToDelete->content;
    free(nodeToDelete);
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