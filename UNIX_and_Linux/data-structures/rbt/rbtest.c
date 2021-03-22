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

    // Test inserting NULL node
    printf("Attempting to insert NULL to tree: ");
    RBTInsertStatusStruct status = rbtInsert(&tree, NULL);
    if (status.status == SUCCESS)
    {
        printf("Error, success returned!\n");
	return -1;
    }
    else if (status.status == NULL_INSERT_ATTEMPT)
    {
        printf("Correct error thrown on null insert attempt\n");
    }
    
    // Test inserting a non empty node into empty tree
    void* a = malloc(sizeof(int));
    if (a == NULL)
    {
        perror("unable to allocate space for int");
	return -1;
    }
    *((int*) a) = 3000;

    printf("attempting to insert %i into tree: ", *((int*) a));
    status = rbtInsert(&tree, a);
    if (status.status != SUCCESS)
    {
        perror("Some error encountered");
	return -1;
    }
    printf("%i inserted properly!\n", *((int*) tree.head->content));

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
