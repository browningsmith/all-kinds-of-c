#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("rbtest startup\n");

    // Test creating a new RBT
    RBT tree;

    // Test what head looks like before and after rbtInit
    printf("RBT head before init: %lu\n", tree.head);
    rbtInit(&tree);
    printf("RBT head after init: %lu\n", tree.head);
    

    return 0;
}