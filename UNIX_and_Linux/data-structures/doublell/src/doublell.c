#include "../include/doublell.h"

#include <stdio.h>
#include <stdlib.h>

//Include implementation-only declarations
#include "../include/doublellimpl.h"

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
    DLLNode* newNode;

    if (list->head == NULL)
    {
        newNode = dllInsertNode__(content, NULL, NULL);
        if (newNode == NULL)
        {
            return -1;
        }
        
        list->head = newNode;
        list->tail = newNode;

        return 0;
    }

    newNode = dllInsertNode__(content, NULL, list->head);
    if (newNode == NULL)
    {
        return -1;
    }
    list->head = newNode;

    return 0;
}

int dllPushTail(DLL* list, void* content)
{
    DLLNode* newNode;

    if (list->tail == NULL)
    {
        newNode = dllInsertNode__(content, NULL, NULL);
        if (newNode == NULL)
        {
            return -1;
        }
        
        list->head = newNode;
        list->tail = newNode;

        return 0;
    }

    newNode = dllInsertNode__(content, list->tail, NULL);
    if (newNode == NULL)
    {
        return -1;
    }
    list->tail = newNode;

    return 0;
}

int dllGetHead(DLL list, void** returnedContent)
{
    if (list.head == NULL)
    {
        return -1;
    }

    *returnedContent = list.head->content;
    return 0;
}

int dllGetTail(DLL list, void** returnedContent)
{
    if (list.tail == NULL)
    {
        return -1;
    }

    *returnedContent = list.tail->content;
    return 0;
}

int dllPop(DLL* list, void** returnedContent)
{
    if (list->head == NULL)
    {
        return -1;
    }

    DLLNode* nodeToDelete = list->head;

    // If the head and tail are the same, then this is the only node to delete
    if (nodeToDelete == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    // Otherwise, head needs to be set to nodeToDelete->next
    else
    {
        // If the head has no next (broken list), cancel the pop operation
        if (nodeToDelete->next == NULL)
        {
            return -1;
        }

        list->head = nodeToDelete->next;
    }

    *returnedContent = dllDeleteNode__(nodeToDelete);
    return 0;
}

int dllPopTail(DLL* list, void** returnedContent)
{
    if (list->tail == NULL)
    {
        return -1;
    }

    DLLNode* nodeToDelete = list->tail;

    // If the head and tail are the same, then this is the only node to delete
    if (list->head == nodeToDelete)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    // Otherwise, tail needs to be set to nodeToDelete->prev
    else
    {
        // If the tail has no prev (broken list), cancel the pop operation
        if (nodeToDelete->prev == NULL)
        {
            return -1;
        }

        list->tail = nodeToDelete->prev;
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
            dllGetHead(*list, &content);

            // Attempt to clear content
            if (clearingFunction(content) != 0)
            {
                return -1;
            }

            if (dllPop(list, &content) < 0)
            {
                list->head->content = NULL; // If node does not get deleted, don't want to
                                            // keep a pointer to deleted content
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

int dllGetThis(DLLIterator* iterator, void** content)
{
    DLLNode* currentNode = iterator->currentNode;
    
    if (currentNode == NULL)
    {
        return -1;
    }

    *content = currentNode->content;
    return 0;
}

int dllGetPrev(DLLIterator* iterator, void** content)
{
    DLLNode* currentNode = iterator->currentNode;
    
    if (currentNode == NULL)
    {
        return -1;
    }
    if (currentNode->prev == NULL)
    {
        return -1;
    }

    iterator->currentNode = currentNode->prev;
    if (content != NULL)
    {
        *content = iterator->currentNode->content;
    }
    
    return 0;
}

int dllGetNext(DLLIterator* iterator, void** content)
{
    DLLNode* currentNode = iterator->currentNode;
    
    if (currentNode == NULL)
    {
        return -1;
    }
    if (currentNode->next == NULL)
    {
        return -1;
    }

    iterator->currentNode = currentNode->next;
    if (content != NULL)
    {
        *content = iterator->currentNode->content;
    }
    
    return 0;
}

int dllInsertPrev(DLLIterator* iterator, void* content)
{

    if (iterator->currentNode == NULL)
    {
        return -1;
    }

    DLLNode* currentNode = iterator->currentNode;
    DLLNode* newNode;

    // If currentNode is head, similar to dllPush, make sure list->head is updated
    if (currentNode == iterator->list->head)
    {
        newNode = dllInsertNode__(content, NULL, currentNode);
        if (newNode == NULL)
        {
            return -1;
        }
        iterator->list->head = newNode;

        return 0;
    }

    // Otherwise just perform normal insert
    newNode = dllInsertNode__(content, currentNode->prev, currentNode);
    if (newNode == NULL)
    {
        return -1;
    }

    return 0;
}

int dllInsertNext(DLLIterator* iterator, void* content)
{
    if (iterator->currentNode == NULL)
    {
        return -1;
    }

    DLLNode* currentNode = iterator->currentNode;
    DLLNode* newNode;

    // If currentNode is tail, similar to dllPushTail, make sure list->tail is updated
    if (currentNode == iterator->list->tail)
    {
        newNode = dllInsertNode__(content, currentNode, NULL);
        if (newNode == NULL)
        {
            return -1;
        }
        iterator->list->tail = newNode;

        return 0;
    }

    // Otherwise just perform normal insert
    newNode = dllInsertNode__(content, currentNode, currentNode->next);
    if (newNode == NULL)
    {
        return -1;
    }

    return 0;
}

int dllDeletePrev(DLLIterator* iterator, void** content)
{
    if (iterator->currentNode == NULL)
    {
        return -1;
    }

    if (iterator->currentNode->prev == NULL)
    {
        return -1;
    }

    DLLNode* nodeToDelete = iterator->currentNode->prev;

    // If nodeToDelete is the head, this is same as dllPop operation
    if (nodeToDelete == iterator->list->head)
    {
        // If list->head->next is NULL, we have broken list
        if (nodeToDelete->next == NULL)
        {
            return -1;
        }

        // Set list->head to currentNode
        iterator->list->head = iterator->currentNode;
    }

    *content = dllDeleteNode__(nodeToDelete);
    return 0;
}

int dllDeleteNext(DLLIterator* iterator, void** content)
{
    if (iterator->currentNode == NULL)
    {
        return -1;
    }

    if (iterator->currentNode->next == NULL)
    {
        return -1;
    }

    DLLNode* nodeToDelete = iterator->currentNode->next;

    // If nodeToDelete is the tail, this is same as dllPopTail operation
    if (nodeToDelete == iterator->list->tail)
    {
        // If list->tail->prev is NULL, we have broken list
        if (nodeToDelete->prev == NULL)
        {
            return -1;
        }

        // Set list->tail to currentNode
        iterator->list->tail = iterator->currentNode;
    }

    *content = dllDeleteNode__(nodeToDelete);
    return 0;
}

// Implementation-only definitions

DLLNode* dllInsertNode__(void* content, DLLNode* prev, DLLNode* next)
{
    //printf("INSERTING NODE\n");
    //printf("Allocating space for a new node, and placing inside newNode\n");
    DLLNode* newNode = malloc(sizeof(DLLNode));
    //printf("Address of allocated space placed in newNode: %x\n", newNode);
    if (newNode == NULL)
    {
        //printf("Unable to allocate space, NULL was returned by call to malloc\n");
        return NULL;
    }

    // Initialize values
    //printf("Setting newNode->prev equal to prev argument, which is %x\n", prev);
    newNode->prev = prev;
    //printf("newNode->prev is now %x\n", newNode->prev);
    //printf("Setting newNode->next equal to next argument, which is %x\n", next);
    newNode->next = next;
    //printf("newNode->next is now %x\n", newNode->next);
    //printf("Setting newNode->content equal to content argument, which is %x\n", content);
    newNode->content = content;
    //printf("newNode->content is now %x\n", newNode->content);

    // Attach outer nodes
    if (prev != NULL)
    {
        //printf("prev is not NULL, setting prev->next to newNode, which is %x\n", newNode);
        prev->next = newNode;
        //printf("prev->next is now %x\n", prev->next);
    }
    // else
    // {
    //     printf("prev is NULL, can't attach anything to it\n");
    // }
    if (next != NULL)
    {
        //printf("next is not NULL, setting next->prev to newNode, which is %x\n", newNode);
        next->prev = newNode;
        //printf("next->prev is now %x\n", next->prev);
    }
    // else
    // {
    //     printf("next is NULL, can't attach anything to it\n");
    // }

    //printf("Returning %x\n", newNode);
    return newNode;
}

void* dllDeleteNode__(DLLNode* node)
{
    //printf("DELETING NODE\n");
    //printf("Address of node being deleted: %x\n", node);
    void* returnContent = node->content;
    //printf("Address of previous node: %x\n", node->prev);
    DLLNode* prev = node->prev;
    //printf("Address of local variable prev: %x\n", node->prev);
    //printf("Address of next node: %x\n", node->next);
    DLLNode* next = node->next;
    //printf("Address of local variable next: %x\n", node->next);

    // If prev node is not null, set it's next to next
    if (prev != NULL)
    {
        //printf("Prev is not NULL, setting prev->next to next, which should be %x\n", next);
        prev->next = next;
        //printf("prev->next is now %x\n", prev->next);
    }
    // else
    // {
    //     printf("Prev is NULL, so can't attach anything to it\n");
    // }

    // If next node is not null, set it's prev to prev
    if (next != NULL)
    {
        //printf("Next is not NULL, setting next->prev to prev, which should be %x\n", prev);
        next->prev = prev;
        //printf("next->prev is now %x\n", next->prev);
    }
    // else
    // {
    //     printf("Next is NULL, so can't attach anything to it\n");
    // }

    //printf("Freeing node at address: %x\n", node);
    free(node);
    //printf("Freed node at address: %x\n", node);

    return returnContent;
}