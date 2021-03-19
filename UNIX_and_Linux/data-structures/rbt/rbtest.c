#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

int compareInt(void* a, void* b);

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("ERROR: Need to enter two numbers to compare\n");
        printf("Usage: ./rbtest <numberA> <numberB>\n");
        return -1;
    }
    
    printf("rbtest startup\n");

    // Test creating a new RBT
    RBT tree;
    rbtInit(&tree);
    
    // Test creating two nodes that contain integers
    printf("Creating nodeA: ");
    RBTNode* nodeA = rbtNewNode(malloc(sizeof(int)));
    if (nodeA == NULL)
    {
        perror("Unable to create nodeA");
        return -1;
    }
    else if (rbtIsNodeEmpty(*nodeA))
    {
        perror("Created nodeA, but was unable to create content");
        return -1;
    }
    printf("Created nodeA\n");
    *((int*) nodeA->content) = atoi(argv[1]);
    printf("Filled nodeA with %i\n", *((int*) nodeA->content));

    printf("Creating nodeB: ");
    RBTNode* nodeB = rbtNewNode(malloc(sizeof(int)));
    if (nodeB == NULL)
    {
        perror("Unable to create nodeB");
        return -1;
    }
    else if (rbtIsNodeEmpty(*nodeB))
    {
        perror("Created nodeB, but was unable to create content");
        return -1;
    }
    printf("Created nodeB\n");
    *((int*) nodeB->content) = atoi(argv[2]);
    printf("Filled nodeB with %i\n", *((int*) nodeB->content));

    // Test using custom compare function to compare the two integers
    printf("rbtCompare result: %i\n", rbtCompare(*nodeA, *nodeB, compareInt));

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