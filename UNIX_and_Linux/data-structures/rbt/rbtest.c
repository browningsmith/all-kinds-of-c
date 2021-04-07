#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "rbtimpl.h"

int compareInt(void* a, void* b);
RBTNode* newIntNode(int num);
void displayNode(RBTNode node);
void constructTree(RBT* tree);
void eraseTree(RBT* tree);

int main()
{
    RBT tree;
    
    printf("Running tests on rbt\n");
    printf("Sizeof int: %lu\n", sizeof(int));
    printf("Sizeof RBTNode: %lu\n", sizeof(RBTNode));
    printf("Sizeof RBTNode with int: %lu\n", sizeof(RBTNode) + sizeof(int));
    
    // Test rbtStatusAsText
    printf("Testing rbtStatusAsText\n");
    {
        RBTStatus status = SUCCESS;
        if (strcmp(rbtStatusAsText(status), "SUCCESS") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "SUCCESS");
            return -1;
        }
        status = NO_MEMORY;
        if (strcmp(rbtStatusAsText(status), "NO_MEMORY") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "NO_MEMORY");
            return -1;
        }
        status = NULL_CONTENT;
        if (strcmp(rbtStatusAsText(status), "NULL_CONTENT") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "NULL_CONTENT");
            return -1;
        }
        status = EMPTY_NODE_ENCOUNTERED;
        if (strcmp(rbtStatusAsText(status), "EMPTY_NODE_ENCOUNTERED") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "EMPTY_NODE_ENCOUNTERED");
            return -1;
        }
        status = NOT_FOUND;
        if (strcmp(rbtStatusAsText(status), "NOT_FOUND") != 0)
        {
            printf("rbtStatusAsText: Error, incorrect status %s vs %s\n", rbtStatusAsText(status), "NOT_FOUND");
            return -1;
        }
    }
    printf("Completed rbtStatusAsText\n");

    // Test rbtInit
    printf("Testing rbtInit\n");
    {
        tree.head = (RBTNode*) 17;
        tree.compareFunction = NULL;

        rbtInit(&tree, compareInt);

        if (tree.head != NULL)
        {
            printf("rbtInit: Error, tree.head not set to NULL\n");
            return -1;
        }
        if (tree.compareFunction != compareInt)
        {
            printf("rbtInit: Error, tree.head not set given compareFunction\n");
            return -1;
        }
    }
    printf("Completed rbtInit\n");

    // Test rbtIsEmpty
    printf("Testing rbtIsEmpty\n");
    {
        // Test if tree is not empty
        RBTNode node;
        tree.head = &node;
        if (rbtIsEmpty(tree) != 0)
        {
            printf("rbtIsEmpty: Error, tree returned as empty when the head definitely points to a node\n");
            return -1;
        }

        // Test if tree is empty after rbtInit
        rbtInit(&tree, compareInt);
        if (rbtIsEmpty(tree) == 0)
        {
            printf("rbtIsEmpty: Error, tree returned as not empty after rbtInit\n");
            return -1;
        }
    }
    printf("Completed rbtIsEmpty\n");

    // Test rbtGetNodeFromStart__
    printf("Testing rbtGetNodeFromStart__\n");
    {
        constructTree(&tree);
        RBTStatusStruct status;
        int query;

        // Test searching all nodes created by constructTree
        for (query = 100; query < 800; query += 100)
        {
            status = rbtGetNodeFromStart__(tree.head, (void*) &query, tree.compareFunction);
            if (status.status != SUCCESS)
            {
                printf("rbtGetNodeFromStart__: Error, status returned with %s instead of SUCCESS, when query of %i should have been matched\n", rbtStatusAsText(status.status), query);
                return -1;
            }
            if (status.node == NULL)
            {
                printf("rbtGetNodeFromStart__: Error, NULL node returned when query of %i should have been matched\n", query);
                return -1;
            }
            if (*(int*) status.node->content != query)
            {
                printf("rbtGetNodeFromStart__: Error, incorrect node returned when query of %i should have been matched\n", query);
                return -1;
            }
        }

        // Test searching for a node that does not exist between 300 and 400
        query = 305;
        status = rbtGetNodeFromStart__(tree.head, (void*) &query, tree.compareFunction);
        if (status.status != NOT_FOUND)
        {
            printf("rbtGetNodeFromStart__: Error, status returned with %s instead of NOT_FOUND, when query of %i should not have been matched\n", rbtStatusAsText(status.status), query);
            return -1;
        }
        if (status.node == NULL)
        {
            printf("rbtGetNodeFromStart__: Error, NULL returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }
        if (status.node != tree.head->left->right)
        {
            printf("rbtGetNodeFromStart__: Error, incorrect node returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }

        // Test searching for a node that does not exist beyond 700
        query = 800;
        status = rbtGetNodeFromStart__(tree.head, (void*) &query, tree.compareFunction);
        if (status.status != NOT_FOUND)
        {
            printf("rbtGetNodeFromStart__: Error, status returned with %s instead of NOT_FOUND, when query of %i should not have been matched\n", rbtStatusAsText(status.status), query);
            return -1;
        }
        if (status.node == NULL)
        {
            printf("rbtGetNodeFromStart__: Error, NULL returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }
        if (status.node != tree.head->right->right)
        {
            printf("rbtGetNodeFromStart__: Error, incorrect node returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }

        // Break tree by making 300 an empty node
        void* content300 = tree.head->left->right->content;
        tree.head->left->right->content = NULL;

        // Test EMPTY_NODE_ENCOUNTERED error
        query = 300;
        status = rbtGetNodeFromStart__(tree.head, (void*) &query, tree.compareFunction);
        if (status.status != EMPTY_NODE_ENCOUNTERED)
        {
            printf("rbtGetNodeFromStart__: Error, status returned with %s instead of EMPTY_NODE_ENCOUNTERED, when the 300 node was set to have NULL content\n", rbtStatusAsText(status.status));
            return -1;
        }
        if (status.node == NULL)
        {
            printf("rbtGetNodeFromStart__: Error, NULL node returned when the 300 node was set to have NULL content\n");
            return -1;
        }
        if (status.node != tree.head->left->right)
        {
            printf("rbtGetNodeFromStart__: Error, incorrect node returned when the 300 node was set to have NULL content\n");
            return -1;
        }

        // Fix tree
        tree.head->left->right->content = content300;

        eraseTree(&tree);
    }
    printf("Completed rbtGetNodeFromStart__\n");

    // Test rbtFind
    printf("Testing rbtFind\n");
    {
        constructTree(&tree);
        int query;
        void* content;
        RBTStatusStruct status;

        // Test searching all nodes created by constructTree
        for (query = 100; query < 800; query += 100)
        {
            status = rbtFind(tree, (void*) &query, &content);
            if (status.status != SUCCESS)
            {
                printf("rbtFind: Error, status returned with %s instead of SUCCESS, when query of %i should have been matched\n", rbtStatusAsText(status.status), query);
                return -1;
            }
            if (status.node == NULL)
            {
                printf("rbtFind: Error, NULL node returned when query of %i should have been matched\n", query);
                return -1;
            }
            if (content == NULL)
            {
                printf("rbtFind: Error, NULL content returned when query of %i should have been matched\n", query);
                return -1;
            }
            if (*(int*) status.node->content != *(int*) content)
            {
                printf("rbtFind: Error, incorrect content returned when query of %i should have been matched\n", query);
                return -1;
            }
        }

        // Test searching for a node that does not exist between 300 and 400
        query = 305;
        status = rbtFind(tree, (void*) &query, &content);
        if (status.status != NOT_FOUND)
        {
            printf("rbtFind: Error, status returned with %s instead of NOT_FOUND, when query of %i should not have been matched\n", rbtStatusAsText(status.status), query);
            return -1;
        }
        if (status.node == NULL)
        {
            printf("rbtFind: Error, NULL returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }
        if (status.node != tree.head->left->right)
        {
            printf("rbtFind: Error, incorrect node returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }
        if (content != NULL)
        {
            printf("rbtFind: Error, non NULL content was returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }

        // Test searching for a node that does not exist beyond 700
        query = 800;
        status = rbtFind(tree, (void*) &query, &content);
        if (status.status != NOT_FOUND)
        {
            printf("rbtFind: Error, status returned with %s instead of NOT_FOUND, when query of %i should not have been matched\n", rbtStatusAsText(status.status), query);
            return -1;
        }
        if (status.node == NULL)
        {
            printf("rbtFind: Error, NULL returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }
        if (status.node != tree.head->right->right)
        {
            printf("rbtFind: Error, incorrect node returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }
        if (content != NULL)
        {
            printf("rbtFind: Error, non NULL content was returned when query of %i was not found on a non-empty list\n", query);
            return -1;
        }

        eraseTree(&tree);
    }
    printf("Completed rbtFind\n");

    printf("Tests complete\n");

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

void displayNode(RBTNode node)
{
    printf("Color: ");
    if (node.isRed)
    {
        printf("RED\n");
    }
    else
    {
        printf("BLACK\n");
    }

    printf("Content: ");
    if (node.content == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%i\n", *(int*) node.content);
    }

    printf("Parent: ");
    if (node.parent == NULL)
    {
        printf("NULL\n");
    }
    else if (node.parent->content == NULL)
    {
        printf("NULL_CONTENT\n");
    }
    else
    {
        printf("%i\n", *(int*) node.parent->content);
    }

    printf("Left: ");
    if (node.left == NULL)
    {
        printf("NULL\n");
    }
    else if (node.left->content == NULL)
    {
        printf("NULL_CONTENT\n");
    }
    else
    {
        printf("%i\n", *(int*) node.left->content);
    }

    printf("Right: ");
    if (node.right == NULL)
    {
        printf("NULL\n");
    }
    else if (node.right->content == NULL)
    {
        printf("NULL_CONTENT\n");
    }
    else
    {
        printf("%i\n", *(int*) node.right->content);
    }
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