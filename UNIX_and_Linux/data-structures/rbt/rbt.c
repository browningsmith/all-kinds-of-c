#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

void rbtInit(RBT* tree)
{
    // Initialize values
    tree->head = NULL;
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

int rbtCompare(RBTNode a, RBTNode b, int (*compareFunction) (void*, void*))
{
    return compareFunction(a.content, b.content);
}

RBTStatusStruct rbtInsert(RBT* tree, void* content, int (*compareFunction) (void*, void*))
{
    RBTStatusStruct result;
    result.errNode = NULL;

    // Check that content is not null pointer
    if (content == NULL)
    {
        result.status = NULL_INSERT_ATTEMPT;
        return result;
    }

    // Create new node
    RBTNode* newNode = rbtNewNode(content);
    if (newNode == NULL) // rbtNewNode returns NULL on error
    {
        result.status = NO_MEMORY;
        return result;
    }

    // If tree is empty, set this node as the head
    if (rbtIsTreeEmpty(*tree))
    {
        tree->head = newNode;
    }
    else
    {
        
    }

    // At this point, return success
    result.status = SUCCESS;
    return result;
}
