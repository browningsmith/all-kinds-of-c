#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

const char* rbtStatusAsText(RBTStatus status)
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
    // Initialize result
    RBTStatusStruct result = { .node = NULL };

    RBTNode* currentNode = start;
    int compareResult;

    // Search algorithm
    printf("Beginning search\n");
    while (1)
    {
        // Check that currentNode is not empty
        if (rbtIsNodeEmpty(*currentNode))
        {
            printf("Encountered empty node, returning EMPTY_NODE_ENCOUNTERED and currentNode\n");
            result.status = EMPTY_NODE_ENCOUNTERED;
            result.node = currentNode;
            break;
        }

        // Compare query with content of currentNode
        compareResult = compareFunction(query, currentNode->content);

        // If query matches currentNode's content, return SUCCESS and currentNode
        if (compareResult == 0)
        {
            printf("Node found, returning SUCCESS and currentNode\n");
            result.status = SUCCESS;
            result.node = currentNode;
            break;
        }

        // If query is less than currentNode's content
        if (compareResult < 0)
        {
            printf("Query is less than currentNode\n");

            // If currentNode's left child is NULL, search is over, return NOT_FOUND, and last node searched
            if (currentNode->left == NULL)
            {
                printf("No left child. Node not found, returning NOT_FOUND and currentNode\n");
                result.status = NOT_FOUND;
                result.node = currentNode;
                break;
            }
            else
            {
                printf("Recursing search into left subtree\n");
                currentNode = currentNode->left;
                continue;
            }
        }

        // Here, query has to be greater than currentNode's content
        {
            printf("Query is greater than currentNode\n");

            // If currentNode's right child is NULL, search is over, return NOT_FOUND, and last node searched
            if (currentNode->right == NULL)
            {
                printf("No right child. Node not found, returning NOT_FOUND and currentNode\n");
                result.status = NOT_FOUND;
                result.node = currentNode;
                break;
            }
            else
            {
                printf("Recursing search into right subtree\n");
                currentNode = currentNode->right;
                continue;
            }
        }
    }

    return result;
}