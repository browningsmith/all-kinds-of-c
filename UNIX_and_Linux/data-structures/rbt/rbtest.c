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

    // Test inserting the same int 3 times
    for (int i=0; i<3; i++)
    {
        void* a = malloc(sizeof(int));
        if (a == NULL) // malloc returns NULL on error
        {
            perror("Unable to allocate space for int");
            return -1;
        }
        *((int*) a) = 7000;

        // Insert a new node with a as content
        printf("Inserting %i into the tree\n", *((int*) a));
        RBTStatusStruct result = rbtInsert(&tree, a, compareInt);
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
