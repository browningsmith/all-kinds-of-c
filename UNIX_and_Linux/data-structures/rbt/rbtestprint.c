#include "rbtprint.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbt.h"
#include "rbtprintimpl.h"

int compareInt(void* a, void* b);
RBTNode* newIntNode(int num);
void constructTree(RBT* tree);
void eraseTree(RBT* tree);

int main()
{
    printf("Running tests on rbtprint\n");

    // Test rbtNewPLine__
    printf("Testing rbtNewPLine__\n");
    {
        PLine* line = rbtNewPLine__();
        if (line == NULL)
        {
            perror("rbtNewPLine__: Error creating new PLine");
            return -1;
        }
        if (line->text == NULL)
        {
            printf("rbtNewPLine__: Error, line->text was set to NULL\n");
            return -1;
        }
        if (line->capacity != 100)
        {
            printf("rbtNewPLine__: Error, line->capacity was not set to 100\n");
            return -1;
        }
        if (line->usage != 0)
        {
            printf("rbtNewPLine__: Error, line->usage was not set to 0\n");
            return -1;
        }

        free(line->text);
        free(line);
    }
    printf("Completed rbtNewPLine__\n");

    // Test rbtDeletePLine__
    printf("Testing rbtDeletePLine__\n");
    {
        PLine* line = rbtNewPLine__();
        if (line == NULL)
        {
            perror("rbtDeletePLine__: Unable to create line");
            return -1;
        }

        rbtDeletePLine__(line);
    }
    printf("Completed rbtDeletePLine__\n");

    // Test rbtPLineIncreaseCapacity__
    printf("Testing rbtPLineIncreaseCapacity__\n");
    {
        // Create new PLine
        PLine* line = rbtNewPLine__();
        if (line == NULL)
        {
            perror("rbtPLineIncreaseCapacity__: Unable to create new line");
            return -1;
        }

        // Fill first 100 chars with 1-100
        for (char i = 1; i < 101; i++)
        {
            line->text[i-1] = i;
        }

        // Test
        char* formerTextPointer = line->text;
        if (rbtPLineIncreaseCapacity__(line) < 0)
        {
            perror("rbtPLineIncreaseCapacity__: Unable to allocate more space for line->text");
            
            if (line->text != formerTextPointer)
            {
                printf("rbtPLineIncreaseCapacity__: Error, function did not leave line->text as the originally allocated pointer\n");
            }

            return -1;
        }
        if (line->capacity != 200)
        {
            printf("rbtPLineIncreaseCapacity__: Did not properly increase capacity\n");
            return -1;
        }
        for (char i = 1; i < 101; i++)
        {
            if (line->text[i-1] != i)
            {
                printf("rbtPLineIncreaseCapacity__: Contents of line->text was changed at index %i\n", i);
            }
        }
        // Test for possible segfaults
        for (char i = 1; i < 101; i++)
        {
            line->text[101 - 1] = i;
        }

        rbtDeletePLine__(line);
    }
    printf("Completed rbtPLineIncreaseCapacity__\n");

    // Test printing a tree
    {
        RBT tree;
        constructTree(&tree);

        rbtPrint(tree, NULL);

        eraseTree(&tree);
    }

    printf("Tests Complete\n");

    return 0;
}

int compareInt(void* a, void* b)
{
    int derefA = *((int*) a);
    int derefB = *((int*) b);

    //printf("Comparing integers A: %i and B: %i\n", derefA, derefB);

    if (derefA == derefB)
    {
        //printf("A is equal to B\n");
        return 0;
    }
    else if (derefA < derefB)
    {
        //printf("A is less than B\n");
        return -1;
    }
    else
    {
       // printf("A is greater than B\n");
        return 1;
    }
}

RBTNode* newIntNode(int num)
{
    void* content = malloc(sizeof(int));
    if (content == NULL)
    {
        printf("Unable to allocate space for int %i: %s\n", num, strerror(errno));
        exit(-1);
    }
    *(int*) content = num;

    RBTNode* newNode = malloc(sizeof(RBTNode));
    if (newNode == NULL)
    {
        printf("Unable to allocate space for node %i: %s\n", num, strerror(errno));
        exit(-1);
    }

    newNode->content = content;
    newNode->isRed = 1;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void constructTree(RBT* tree)
{
    rbtInit(tree, compareInt);

    // 400 Node (black)
    RBTNode* node400 = newIntNode(400);
    node400->isRed = 0;
    tree->head = node400;

    // 200 Node (black)
    RBTNode* node200 = newIntNode(200);
    node200->isRed = 0;
    node400->left = node200;
    node200->parent = node400;

    // 600 Node (black)
    RBTNode* node600 = newIntNode(600);
    node600->isRed = 0;
    node400->right = node600;
    node600->parent = node400;

    // 100 Node (red)
    RBTNode* node100 = newIntNode(100);
    node200->left = node100;
    node100->parent = node200;

    // 300 Node (red)
    RBTNode* node300 = newIntNode(300);
    node200->right = node300;
    node300->parent = node200;

    // 500 Node (red)
    RBTNode* node500 = newIntNode(500);
    node600->left = node500;
    node500->parent = node600;

    // 700 Node (red)
    RBTNode* node700 = newIntNode(700);
    node600->right = node700;
    node700->parent = node600;

    // printf("Node 400:\n");
    // displayNode(*node400);
    // printf("\nNode 200:\n");
    // displayNode(*node200);
    // printf("\nNode 600:\n");
    // displayNode(*node600);
    // printf("\nNode 100:\n");
    // displayNode(*node100);
    // printf("\nNode 300:\n");
    // displayNode(*node300);
    // printf("\nNode 500:\n");
    // displayNode(*node500);
    // printf("\nNode 700:\n");
    // displayNode(*node700);
}

void eraseTree(RBT* tree)
{
    if (tree->head == NULL)
    {
        return;
    }

    RBTNode* currentNode = tree->head;
    int state = -1; // -1 go left, 1 go right, 0 clear this

    while (1)
    {
        if (state == -1) // Go left
        {
            if (currentNode->left == NULL) // If no left child
            {
                state = 1; // Go right
                continue;
            }

            currentNode = currentNode->left; // Recurse left
            // State is already -1
        }
        else if (state == 1) // Go right
        {
            if (currentNode->right == NULL) // If no right child
            {
                state = 0; // Clear this
                continue;
            }

            currentNode = currentNode->right; // Recurse right
            state = -1; // Set to go left
        }
        else
        {
            RBTNode* parent = currentNode->parent;
            
            if (parent != NULL)
            {
                // If we are left child, set state to 1
                if (currentNode == parent->left)
                {
                    state = 1;
                }
            }
            // Otherwise state is already 0

            free(currentNode->content);
            free(currentNode);

            if (parent == NULL)
            {
                break;
            }

            currentNode = parent;
        }
    }

    tree->head = NULL;
}