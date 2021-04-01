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

    if (list->head == NULL)
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

    if (list->tail == NULL)
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
    if (list.head == NULL)
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
    if (list->head == NULL)
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
        // If the head has no next (broken list), cancel the pop operation
        if (list->head->next == NULL)
        {
            *returnedContent = NULL;
            return -1;
        }

        list->head = nodeToDelete->next;
        list->head->prev = NULL;
    }

    *returnedContent = dllDeleteNode__(nodeToDelete);
    return 0;
}

int dllPopTail(DLL* list, void** returnedContent)
{
    if (list->tail == NULL)
    {
        *returnedContent = NULL;
        return -1;
    }

    DLLNode* nodeToDelete = list->tail;

    // If the head and tail are the same, then this is the only node to delete
    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    // Otherwise, tail needs to be set to nodeToDelete->prev
    else
    {
        // If the tail has no prev (broken list), cancel the pop operation
        if (list->tail->prev == NULL)
        {
            *returnedContent = NULL;
            return -1;
        }

        list->tail = nodeToDelete->prev;
        list->tail->next = NULL;
    }

    *returnedContent = dllDeleteNode__(nodeToDelete);
    return 0;
}

int dllClear(DLL* list, int (*clearingFunction) (void*))
{
    void* content;
    
    // If no clearingFunction specified, delete nodes without considering clearing content
    if (clearingFunction == NULL)
    {
        while (list->head != NULL)
        {
            if (dllPop(list, &content) < 0)
            {
                return -1;
            }
        }
    }
    // If a clearingFunction was specified, delete nodes and clear content
    else
    {
        while (list->head != NULL)
        {
            dllGet(*list, &content);

            // Attempt to clear content
            if (clearingFunction(content) != 0)
            {
                return -1;
            }

            if (dllPop(list, &content) < 0)
            {
                return -1;
            }
        }
    }

    return 0;
}

int dllToHead(DLLIterator* iterator, DLL* list)
{
    iterator->list = list;
    
    if (list->head == NULL)
    {
        iterator->currentNode = NULL;
        return -1;
    }

    iterator->currentNode = list->head;
    return 0;
}

int dllToTail(DLLIterator* iterator, DLL* list)
{
    iterator->list = list;
    
    if (list->tail == NULL)
    {
        iterator->currentNode = NULL;
        return -1;
    }

    iterator->currentNode = list->tail;
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