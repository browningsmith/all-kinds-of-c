#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

int compareInt(void* a, void* b);

int main(int argc, char** argv)
{
    
    printf("rbtest startup\n");

    // Init new tree
    RBT tree;
    rbtInit(&tree, compareInt);

    void* a = malloc(sizeof(int));
    if (a == NULL)
    {
        perror("Could not allocate space for a");
        return -1;
    }
    *((int*) a) = 4000;

    void* b = malloc(sizeof(int));
    if (b == NULL)
    {
        perror("Could not allocate space for b");
        return -1;
    }
    *((int*) b) = 6000;

    int result = tree.compareFunction(a, b);
    printf("Result: %i\n", result);

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
