#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

int compareInt(void* a, void* b);
void makeSmallTree(RBT* tree);

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        printf("USAGE: ./rbtest <int1> <int2> <int3>\n");
        return -1;
    }
    
    printf("rbtest startup\n");

    // Init new tree
    RBT tree;
    rbtInit(&tree, compareInt);

    // Test inserting four integers into new tree
    for (int i=1; i<argc; i++)
    {
        printf("Allocating space for %s\n", argv[i]);
        void* newInt = malloc(sizeof(int));
        if (newInt == NULL)
        {
            perror("Error allocating space");
            return -1;
        }
        *(int*) newInt = atoi(argv[i]);

        printf("Inserting %i\n", *(int*) newInt);
        RBTStatusStruct result = rbtInsert(&tree, newInt);
        printf("Insert returned with status %s\n", rbtStatusAsText(result.status));
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

void makeSmallTree(RBT* tree)
{
    // Construct tree with head as 200, left child as 100, and right child as 300
    //printf("Constructing a new balanced tree with three nodes, 100, 200, and 300\n");

    // Add 200 as head
    void* newInt = malloc(sizeof(int));
    if (newInt == NULL)
    {
        perror("Unable to allocate space for int 200");
        exit(-1);
    }
    *(int*) newInt = 200;
    tree->head = rbtNewNode(newInt);
    if (rbtIsTreeEmpty(*tree))
    {
        perror("Unable to create new node for 200");
        exit(-1);
    }
    rbtSetBlack(tree->head);
    //printf("Added 200 as head\n");

    // Add 100 as head's left child
    newInt = malloc(sizeof(int));
    if (newInt == NULL)
    {
        perror("Unable to allocate space for int 100");
        exit(-1);
    }
    *(int*) newInt = 100;
    tree->head->left = rbtNewNode(newInt);
    if (tree->head->left == NULL)
    {
        perror("Unable to create new node for 100");
        exit(-1);
    }
    tree->head->left->parent = tree->head;
    //printf("Added 100 as head's left child\n");

    // Add 300 as head's right child
    newInt = malloc(sizeof(int));
    if (newInt == NULL)
    {
        perror("Unable to allocate space for int 300");
        exit(-1);
    }
    *(int*) newInt = 300;
    tree->head->right = rbtNewNode(newInt);
    if (tree->head->right == NULL)
    {
        perror("Unable to create new node for 300");
        exit(-1);
    }
    tree->head->right->parent = tree->head;
    //printf("Added 300 as head's right child\n");

    // printf("Head is %i\n", *(int*) tree->head->content);
    // printf("Left child is %i\n", *(int*) tree->head->left->content);
    // printf("Left child's parent is %i\n", *(int*) tree->head->left->parent->content);
    // printf("Right child is %i\n", *(int*) tree->head->right->content);
    // printf("Right child's parent is %i\n", *(int*) tree->head->right->parent->content);
}
