#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

const char* rbtStatusText(RBTStatus status)
{
    const char* result;
    
    switch (status)
    {
        case SUCCESS:
            result = "SUCCESS";
            break;
        case NO_MEMORY:
            result = "NO_MEMORY";
            break;
        case NULL_CONTENT:
            result = "NULL_CONTENT";
            break;
        case EMPTY_NODE_ENCOUNTERED:
            result = "EMPTY_NODE_ENCOUNTERED";
            break;
        case NOT_FOUND:
            result = "NOT_FOUND";
            break;
    }

    return result;
}

void rbtInit(RBT* tree, int (*compareFunction) (void*, void*))
{
    // Initialize values
    tree->head = NULL;
    tree->compareFunction = compareFunction;
}

int rbtIsTreeEmpty(RBT tree)
{
    if (tree.head == NULL)
    {
        return 1;
    }

    return 0;
}

RBTNode* rbtNewNode(void* content)
{
    // Allocate space for the new node
    RBTNode* newNode = malloc(sizeof(RBTNode));
    if (newNode == NULL) // malloc returns NULL on error
    {
        return NULL;
    }

    // Initialize values
    newNode->isRed = 1; // set new node to red
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->content = content;

    return newNode;
}

int rbtIsNodeEmpty(RBTNode node)
{
    if (node.content == NULL)
    {
        return 1;
    }

    return 0;
}

int rbtIsRed(RBTNode node)
{
    if (node.isRed)
    {
        return 1;
    }

    return 0;
}

void rbtSetRed(RBTNode* node)
{
    node->isRed = 1;
}

void rbtSetBlack(RBTNode* node)
{
    node->isRed = 0;
}

RBTStatusStruct rbtGetNodeFromStartingNode(RBTNode* start, void* query, int (*compareFunction) (void* a, void* b))
{
    RBTStatusStruct result = { .node = NULL };

    return result;
}