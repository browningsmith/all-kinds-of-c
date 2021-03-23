#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

int compareInt(void* a, void* b);

int main(int argc, char** argv)
{
    
    printf("rbtest startup\n");

    // Init new tree
    RBT tree;
    rbtInit(&tree);

    // Test attempting to search with NULL content
    printf("Checking result of searching with NULL content\n");
    RBTStatusStruct result = rbtGetNode(tree, NULL, compareInt);
    if (result.status == NULL_CONTENT)
    {
        printf("Correct response received for attempting to search for NULL content\n");
    }
    else
    {
        printf("Incorrect response for searching with NULL content\n");
        return -1;
    }

    // Test searching an empty tree
    printf("Checking result of searching an empty tree\n");
    int a = 7000;
    result = rbtGetNode(tree, (void*) &a, compareInt);
    if (result.status == NOT_FOUND && result.node == NULL)
    {
        printf("Correct response received for attempting to search empty tree\n");
    }
    else
    {
        printf("Incorrect response received for searching empty tree\n");
        return -1;
    }

    return 0;
}

int compareInt(void* a, void* b)
{
    int derefA = *((int*) a);
    int derefB = *((int*) b);

    printf("Comparing integers A: %i and B: %i\n", derefA, derefB);

    if (derefA == derefB)
    {
        printf("A is equal to B\n");
        return 0;
    }
    else if (derefA < derefB)
    {
        printf("A is less than B\n");
        return -1;
    }
    else
    {
        printf("A is greater than B\n");
        return 1;
    }
}
