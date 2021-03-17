#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

RBTNode* rbtNewNode(void* content)
{
    // Allocate space for the new node
    RBTNode* newNode = malloc(sizeof(RBTNode));
    if (newNode == NULL) // malloc returns NULL on error
    {
        return NULL;
    }

    // Initialize values
    newNode->isRed = 0; // Set new node to black
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->content = content;

    return newNode;
}

RBT* rbtNewTree(void)
{
    // Allocate space for the new RBT
    RBT* newTree = malloc(sizeof(RBT));
    if (newTree == NULL) // malloc returns NULL on error
    {
        return NULL;
    }

    // Initialize head
    newTree->head = NULL;

    return newTree;
}