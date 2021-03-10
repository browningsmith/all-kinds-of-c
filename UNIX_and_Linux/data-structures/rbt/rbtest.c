#include "rbt.h"

#include <stdio.h>

int main()
{
    printf("rbtest startup\n");

    printf("Creating new RBTNode\n");
    RBTNode* newNode = newRBTNode(NULL);
    if (newNode == NULL)
    {
        perror("Unable to create new node");
    }
    else
    {
        printf("Created new node\n");
    }

    return 0;
}