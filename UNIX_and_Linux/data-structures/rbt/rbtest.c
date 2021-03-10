#include "rbt.h"

#include <stdio.h>

int main()
{
    printf("rbtest startup\n");

    printf("Creating new RBT\n");
    RBT* tree = newRBT();
    if (tree == NULL)
    {
        perror("Unable to create new tree");
    }
    else
    {
        printf("Created new tree\n");
    }

    return 0;
}