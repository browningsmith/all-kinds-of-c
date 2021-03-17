#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("rbtest startup\n");

    // Test creating a new RBT
    RBT tree;
    rbtInit(&tree);
    
    printf("Testing that new init tree is empty: ");
    // Test rbtIsTreeEmpty to be true before any nodes are inserted
    if (!rbtIsTreeEmpty(tree)) // rbtIsTreeEmpty returns 1 if tree is empty
    {
        printf("Tree is not empty!\n");
        return -1;
    }
    printf("Tree is empty!\n");

    printf("Testing manually adding new node to tree: ");
    // Manually add a new node to the tree using rbtNewNode
    tree.head = rbtNewNode(NULL);
    if (rbtIsTreeEmpty(tree)) // rbtNewNode returns NULL on error, so if rbtIsTreeEmpty is 1, there was an error
    {
        perror("Error creating new node for tree");
        return -1;
    }
    printf("Manually created new node for tree\n");

    return 0;
}