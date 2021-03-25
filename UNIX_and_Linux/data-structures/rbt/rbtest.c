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

    // // Test creating a node that contains an int
    // printf("Creating newInt\n");
    // void* newInt = malloc(sizeof(int));
    // if (newInt == NULL)
    // {
    //     perror("Unable to allocate space for an integer");
    //     return -1;
    // }
    // *(int*) newInt = 4000;
    // printf("Created newInt with value %i\n", *((int*) newInt));
    
    // printf("Creating new node and setting it to the head of tree\n");
    // tree.head = rbtNewNode(newInt);
    // if (rbtIsTreeEmpty(tree)) // If tree is empty, that means rbtNewNode had an error
    // {
    //     perror("Unable to create new node for tree");
    //     return -1;
    // }
    // if (rbtIsNodeEmpty(*tree.head))
    // {
    //     perror("Node created, but the node itself is empty\n");
    //     return -1;
    // }
    // printf("Node created and added to tree with content %i\n", *(int*) tree.head->content);

    // printf("Test calling rbtGetNodeFromNode in its current state\n");
    // int query = 4000;
    // RBTStatusStruct result = rbtGetNodeFromStartingNode(tree.head, (void*) &query, tree.compareFunction);
    // if (result.node == NULL)
    // {
    //     printf("Call appears to be successful\n");
    // }
    // else
    // {
    //     printf("result.node is not NULL, call failed somehow\n");
    //     return -1;
    // }

    // Test printing the different enums
    for (RBTStatus status = 0; status < 5; status++)
    {
        printf("%s\n", rbtStatusText(status));
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
