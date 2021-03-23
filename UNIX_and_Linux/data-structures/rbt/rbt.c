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

RBTStatusStruct rbtGetNode(RBT tree, void* content, int (*compareFunction) (void*, void*))
{
    RBTStatusStruct result;
    result.node = NULL;

    // Check that content is not null pointer
    if (content == NULL)
    {
        result.status = NULL_CONTENT;
        return result;
    }

    // If tree is empty, return NOT_FOUND
    if (rbtIsTreeEmpty(tree))
    {
        printf("Tree is empty, returning NOT_FOUND\n");
        result.status = NOT_FOUND;
        return result;
    }

    // Begin search algorithm
    return rbtGetNode_fromNode(tree.head, content, compareFunction);
}

RBTStatusStruct rbtGetNode_fromNode(RBTNode* start, void* content, int (*compareFunction) (void*, void*))
{
    RBTStatusStruct result;
    result.node = NULL;

    // Check that content is not null pointer
    if (content == NULL)
    {
        result.status = NULL_CONTENT;
        return result;
    }

    // Begin search algorithm
    RBTNode* currentNode = start;
    int compareResult;
    
    while (1)
    {
        // If currentNode is empty, return EMPTY_NODE_ENCOUNTERED and currentNode in result
        if (rbtIsNodeEmpty(*currentNode))
        {
            printf("Empty node encountered during search, returning EMPTY_NODE_ENCOUNTERED\n");
            result.status = EMPTY_NODE_ENCOUNTERED;
            result.node = currentNode;
            return result;
        }

        compareResult = compareFunction(content, currentNode->content);

        // If content equals currentNode content, return SUCCESS and current node
        if (compareResult == 0)
        {
            printf("Matching node found, returning with SUCCESS and currentNode\n");
            result.status = SUCCESS;
            result.node = currentNode;
            return result;
        }

        // If content is less than currentNode content
        if (compareResult < 0)
        {
            printf("Content is less than current node\n");
            // If left child is null, return NOT_FOUND and currentNode
            if (currentNode->left == NULL)
            {
                printf("Current node has no left child, returning NOT_FOUND and currentNode\n");
                result.status = NOT_FOUND;
                result.node = currentNode;
                return result;
            }

            // otherwise recurse to left child
            printf("Setting currentNode to left child\n");
            currentNode = currentNode->left;
            continue;
        }

        // Otherwise content is greater than currentNode content
        {
            printf("Content is greater than current node\n");
            // If right child is null, return NOT_FOUND and currentNode
            if (currentNode->right == NULL)
            {
                printf("Current node has no right child, returning NOT_FOUND and currentNode\n");
                result.status = NOT_FOUND;
                result.node = currentNode;
                return result;
            }

            // otherwise recurse to right child
            printf("Setting currentNode to right child\n");
            currentNode = currentNode->right;
        }
    }
}

RBTStatusStruct rbtInsert(RBT* tree, void* content, int (*compareFunction) (void*, void*))
{
    RBTStatusStruct result;
    result.node = NULL;

    // Check that content is not null pointer
    if (content == NULL)
    {
        result.status = NULL_CONTENT;
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
