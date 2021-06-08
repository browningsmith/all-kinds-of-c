#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

#include "rbtimpl.h"

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

int rbtIsEmpty(RBT tree)
{
    if (tree.head == NULL)
    {
        return 1;
    }

    return 0;
}

RBTStatusStruct rbtFind(RBT tree, void* query, void** returnedContent)
{
    // Initialize result
    RBTStatusStruct result = { .node = NULL };

    // Check that query is not null
    if (query == NULL)
    {
        *returnedContent = NULL;
        result.status = NULL_CONTENT;
        return result;
    }

    // If the tree is empty, return not found
    if (tree.head == NULL)
    {
        *returnedContent = NULL;
        result.status = NOT_FOUND;
        return result;
    }

    // Perform search
    result = rbtGetNodeFromStart__(tree.head, query, tree.compareFunction);

    if (result.status == SUCCESS)
    {
        *returnedContent = result.node->content;
        // result.status is SUCCESS and result.node is equal to the found node
    }
    else if (result.status == NOT_FOUND)
    {
        *returnedContent = NULL;
        // result.status is NOT_FOUND and result.node is equal to the last node searched
    }
    else if (result.status == EMPTY_NODE_ENCOUNTERED)
    {
        *returnedContent = NULL;
        // result.status is EMPTY_NODE_ENCOUNTERED and result.node is equal to the erroneous node
    }

    return result;
}

RBTStatusStruct rbtInsert(RBT* tree, void* content)
{
    // Initialize result
    RBTStatusStruct result = { .node = NULL };

    // Check that content is not null
    if (content == NULL)
    {
        result.status = NULL_CONTENT;
        return result;
    }

    // Create new node
    RBTNode* newNode = malloc(sizeof(RBTNode));
    if (newNode == NULL) // rbt returns NULL on error
    {
        result.status = NO_MEMORY;
        return result;
    }
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->content = content;

    // If tree is empty, insert new node as head and color it black, return SUCCESS and the new node
    if (tree->head == NULL)
    {
        tree->head = newNode;
        newNode->isRed = 0;

        result.status = SUCCESS;
        result.node = newNode;
        return result;
    }

    // Tree was not empty, color new node red
    newNode->isRed = 1;

    // Search for area to insert new node
    RBTNode* currentNode = tree->head;

    while (
        ( result = rbtGetNodeFromStart__(
            currentNode,
            content,
            tree->compareFunction
        )).status != NOT_FOUND
    )
    {
        // EMPTY_NODE_ENCOUNTERED, free memory allocated for new node and return proper error
        if (result.status == EMPTY_NODE_ENCOUNTERED)
        {
            free(newNode);

            // result.status is EMPTY_NODE_ENCOUNTERED and result.node is the offending node
            return result;
        }

        // SUCCESS means an equivalent node was found, attempt to insert to the right
        if (result.status == SUCCESS)
        {
            currentNode = result.node;

            // If right child is null, insert there
            if (currentNode->right == NULL)
            {
                currentNode->right = newNode;
                newNode->parent = currentNode;

                result.status = SUCCESS;
                result.node = newNode;
                return result;
            }
            // Otherwise, recurse search for new place to insert
            else
            {
                currentNode = currentNode->right;
                continue;
            }
        }
    }

    // At this point, result.status is NOT_FOUND which means we can insert here

    // Compare newNode's content with content of current node
    currentNode = result.node;
    int compareResult = tree->compareFunction(content, currentNode->content);

    // If new node is less than current node, insert to the left
    if (compareResult < 0)
    {
        currentNode->left = newNode;
        newNode->parent = currentNode;

        result.status = SUCCESS;
        result.node = newNode;
    }
    // If new node is greater than current node, insert to the right
    else
    {
        currentNode->right = newNode;
        newNode->parent = currentNode;

        result.status = SUCCESS;
        result.node = newNode;
    }

    return result;
}

// Implementation only definitions

RBTStatusStruct rbtGetNodeFromStart__(RBTNode* start, void* query, int (*compareFunction) (void* a, void* b))
{
    // Initialize result
    RBTStatusStruct result = { .node = NULL };

    RBTNode* currentNode = start;
    int compareResult;

    // Search algorithm
    while (1)
    {
        // Check that currentNode is not empty
        if (currentNode->content == NULL)
        {
            result.status = EMPTY_NODE_ENCOUNTERED;
            result.node = currentNode;
            break;
        }

        // Compare query with content of currentNode
        compareResult = compareFunction(query, currentNode->content);

        // If query matches currentNode's content, return SUCCESS and currentNode
        if (compareResult == 0)
        {
            result.status = SUCCESS;
            result.node = currentNode;
            break;
        }

        // If query is less than currentNode's content
        if (compareResult < 0)
        {
            // If currentNode's left child is NULL, search is over, return NOT_FOUND, and last node searched
            if (currentNode->left == NULL)
            {
                result.status = NOT_FOUND;
                result.node = currentNode;
                break;
            }
            else
            {
                currentNode = currentNode->left;
                continue;
            }
        }

        // Here, query has to be greater than currentNode's content
        {
            // If currentNode's right child is NULL, search is over, return NOT_FOUND, and last node searched
            if (currentNode->right == NULL)
            {
                result.status = NOT_FOUND;
                result.node = currentNode;
                break;
            }
            else
            {
                currentNode = currentNode->right;
                continue;
            }
        }
    }

    return result;
}

int rbtRotateRight__(RBT* tree, RBTNode* leftChild)
{
    RBTNode* parent;
    RBTNode* grandParent;
    RBTNode* leftChildsRightChild;

    // If leftChild is the head, can't do a right rotation
    if (leftChild->parent == NULL)
    {
        return -1;
    }

    parent = leftChild->parent;

    // If leftChild is not a left child, can't do
    if (leftChild != parent->left)
    {
        return -2;
    }

    grandParent = parent->parent;
    leftChildsRightChild = leftChild->right;

    // Set left child's parent to the grandParent
    leftChild->parent = grandParent;

    // If leftChild's parent is now NULL, leftChild is now the head
    if (leftChild->parent == NULL)
    {
        tree->head = leftChild;
    }
    else
    {
        // If parent was Grandparent's left child
        if (parent == grandParent->left)
        {
            grandParent->left = leftChild;
        }
        else // If parent was Grandparen't right child
        {
            grandParent->right = leftChild;
        }
    }

    // Left child's right becomes parent
    leftChild->right = parent;
    parent->parent = leftChild;

    // Parent's left becomes leftChildsRightChild
    parent->left = leftChildsRightChild;
    leftChildsRightChild->parent = parent;

    return 0;
}