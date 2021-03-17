#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("rbtest startup\n");

    // Test creating a new RBT
    RBT tree;
    rbtInit(&tree);
    
    // Test rbtIsTreeEmpty to be true before any nodes are inserted
    printf("Testing that new init tree is empty: ");
    if (!rbtIsTreeEmpty(tree)) // rbtIsTreeEmpty returns 1 if tree is empty
    {
        printf("Tree is not empty!\n");
        return -1;
    }
    printf("Tree is empty!\n");

    // Manually add a new node to the tree using rbtNewNode
    printf("Testing manually adding new empty node to tree: ");
    tree.head = rbtNewNode(NULL);
    if (rbtIsTreeEmpty(tree)) // rbtNewNode returns NULL on error, so if rbtIsTreeEmpty is 1, there was an error
    {
        perror("Error creating new empty node for tree");
        return -1;
    }
    printf("Manually created new empty node for tree\n");

    // Test that this new node is empty
    printf("Testing that this new node is empty: ");
    if (!rbtIsNodeEmpty(*tree.head)) // rbtIsNodeEmpty returns 1 if the node's content is empty
    {
        printf("Error, node is apparently not empty\n");
        return -1;
    }
    printf("Node is empty\n");

    return 0;
}