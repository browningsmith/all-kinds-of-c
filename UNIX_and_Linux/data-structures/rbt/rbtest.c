#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbtimpl.h"

int compareInt(void* a, void* b);

int main()
{
    RBT tree;
    
    printf("Running tests on rbt\n");

    // Test rbtStatusAsText
    printf("Testing rbtStatusAsText\n");
    {
        RBTStatus status = SUCCESS;
        if (strcmp(rbtStatusAsText(status), "SUCCESS") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "SUCCESS");
            return -1;
        }
        status = NO_MEMORY;
        if (strcmp(rbtStatusAsText(status), "NO_MEMORY") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "NO_MEMORY");
            return -1;
        }
        status = NULL_CONTENT;
        if (strcmp(rbtStatusAsText(status), "NULL_CONTENT") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "NULL_CONTENT");
            return -1;
        }
        status = EMPTY_NODE_ENCOUNTERED;
        if (strcmp(rbtStatusAsText(status), "EMPTY_NODE_ENCOUNTERED") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "EMPTY_NODE_ENCOUNTERED");
            return -1;
        }
        status = NOT_FOUND;
        if (strcmp(rbtStatusAsText(status), "NOT_FOUND") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "NOT_FOUND");
            return -1;
        }
    }
    printf("Completed rbtStatusAsText\n");

    // Test rbtInit
    printf("Testing rbtInit\n");
    {
        tree.head = (RBTNode*) 17;
        tree.compareFunction = NULL;

        rbtInit(&tree, compareInt);

        if (tree.head != NULL)
        {
            printf("rbtInit: Error, tree.head not set to NULL\n");
            return -1;
        }
        if (tree.compareFunction != compareInt)
        {
            printf("rbtInit: Error, tree.head not set given compareFunction\n");
            return -1;
        }
    }
    printf("Completed rbtInit\n");

    // Test rbtIsTreeEmpty
    printf("Testing rbtIsTreeEmpty\n");
    {
        // Test if tree is not empty
        RBTNode node;
        tree.head = &node;
        if (rbtIsTreeEmpty(tree) != 0)
        {
            printf("rbtIsTreeEmpty: Error, tree returned as empty when the head definitely points to a node\n");
            return -1;
        }

        // Test if tree is empty after rbtInit
        rbtInit(&tree, compareInt);
        if (rbtIsTreeEmpty(tree) == 0)
        {
            printf("rbtIsTreeEmpty: Error, tree returned as not empty after rbtInit\n");
            return -1;
        }
    }
    printf("Completed rbtIsTreeEmpty\n");

    printf("Tests complete\n");

    return 0;
}

int compareInt(void* a, void* b)
{
    int derefA = *((int*) a);
    int derefB = *((int*) b);

    //printf("Comparing integers A: %i and B: %i\n", derefA, derefB);

    if (derefA == derefB)
    {
        //printf("A is equal to B\n");
        return 0;
    }
    else if (derefA < derefB)
    {
        //printf("A is less than B\n");
        return -1;
    }
    else
    {
       // printf("A is greater than B\n");
        return 1;
    }
}

