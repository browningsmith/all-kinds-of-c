#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

int compareInt(void* a, void* b);

int main(int argc, char** argv)
{
    
    printf("rbtest startup\n");

    RBT tree;
    rbtInit(&tree);

    void* a = malloc(sizeof(int));
    if (a == NULL)
    {
        perror("unable to allocate space for int");
	return -1;
    }
    *((int*) a) = 3000;

    printf("Attempting to insert NULL to tree: ");
    RBTInsertStatusStruct status = rbtInsert(&tree, NULL);
    if (status.status == SUCCESS)
    {
        printf("Error, success returned!\n");
	return -1;
    }
    else if (status.status == NULL_INSERT_ATTEMPT)
    {
        printf("Correct error on null insert attempt\n");
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
