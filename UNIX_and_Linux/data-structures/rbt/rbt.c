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
        printf("Tree was empty, setting as the head, setting to black, returning SUCCESS and new node\n");
        tree->head = newNode;
        rbtSetBlack(newNode);

        result.status = SUCCESS;
        result.node = newNode;
        return result;
    }
    
    // Use rbtGetNode_fromNode to search for spot to insert
    printf("Tree was not empty, beginning search at head\n");
    RBTNode* currentNode = tree->head;
    while (

        (result = rbtGetNode_fromNode(

            currentNode,
            newNode->content,
            compareFunction

        )).status != NOT_FOUND
    )
    {
        // If an empty node is encountered, return result, which should already include the
        // offending node. Also make sure to free the space allocated for newNode
        if (result.status == EMPTY_NODE_ENCOUNTERED)
        {
            printf("Empty node encountered on insert, freeing newNode's allocated memory\n");
            free(newNode);
            return result;
        }

        // If success is returned, then that means we have found an equivalent node
        // we will attempt to insert the new node into the currentNode's left subtree
        if (result.status == SUCCESS)
        {
            printf("Equivalent node found, attempting to insert new node into its left subtree\n");

            // Set currentNode to result.node
            currentNode = result.node;

            // If the currentNode's left child is null, we insert there, return success
            if (currentNode->left == NULL)
            {
                printf("Able to insert new node as current node's left child\n");
                newNode->parent = currentNode;
                currentNode->left = newNode;

                result.status = SUCCESS;
                result.node = newNode;
                return result;
            }

            // Otherwise repeat search at currentNode's left child
            printf("Starting search again at currentNode's left child\n");
            currentNode = currentNode->left;
        }
    }

    // At this point, result.status is NOT_FOUND, and result.node is the last node searched
    printf("No equivalent node found, inserting somewhere here\n");

    // Set currentNode to result.node
    currentNode = result.node;
    // If newNode's content is less than result nodes content, insert new node to the left
    if (compareFunction(newNode->content, currentNode->content) < 0)
    {
        printf("Inserting new node to the left\n");
        newNode->parent = currentNode;
        currentNode->left = newNode;
    }
    // Otherwise insert to the right
    else
    {
        printf("Inserting new node to the right\n");
        newNode->parent = currentNode;
        currentNode->right = newNode;
    }

    // Return success and newNode
    result.status = SUCCESS;
    result.node = newNode;
    return result;
}
