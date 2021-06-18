#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "include/cooltools.h"
#include "rbtimpl.h"
#include "rbtprint.h"

int compareInt(void* a, void* b);
RBTNode* newIntNode(int num);
void displayNode(RBTNode node);
void constructTree(RBT* tree);
int testitoa(char* buffer, void* content);
int testclear(void* content);
int badclear(void* content);

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

    // Test rbtClear
    printf("Testing rbtClear\n");
    {
        // Test clearing empty tree
        rbtInit(&tree, compareInt);
        int result = rbtClear(&tree, testclear);
        if (result != 0)
        {
            printf("rbtClear: Returned with incorrect result on test 1: %i\n", result);
            return -1;
        }
        if (tree.head != NULL)
        {
            printf("rbtClear: Head of tree is not NULL on test 1\n");
            return -1;
        }

        // Test clearing non empty tree
        constructTree(&tree);
        result = rbtClear(&tree, testclear);
        if (result != 0)
        {
            printf("rbtClear: Returned with incorrect result on test 2: %i\n", result);
        }
        if (tree.head != NULL)
        {
            printf("rbtClear: Head of tree is not NULL on test 2\n");
            return -1;
        }

        // Test clearing non empty tree with bad clearing function
        constructTree(&tree);
        result = rbtClear(&tree, badclear);
        if (result == 0)
        {
            printf("rbtClear: Returned with success even with a clearing function that does not clear contents\n");
            return -1;
        }
        if (result != -1)
        {
            if (result == -2)
            {
                perror("rbtClear: Returned with status -2, meaning tree of uncleared nodes could not be fully constructed");
            }
            else
            {
                printf("rbtClear: Returned with unexpected status on test 3: %i\n", result);
                return -1;
            }
        }
        else
        {
            if (tree.head == NULL)
            {
                printf("rbtClear: Tree returned as empty even on status code -1, on test 3\n");
                return -1;
            }
        }

        // Test clearing the same tree (rbtClear should be able to clear all trees)
        result = rbtClear(&tree, testclear);
        if (result != 0)
        {
            printf("rbtClear: Returned with incorrect result on test 4: %i\n", result);
        }
        if (tree.head != NULL)
        {
            printf("rbtClear: Head of tree is not NULL on test 4\n");
            return -1;
        }
    }
    printf("Completed rbtClear\n");

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

        rbtClear(&tree, testclear);
    }
    printf("Completed rbtGetNodeFromStart__\n");

    // Test rbtFind
    printf("Testing rbtFind\n");
    {
        rbtInit(&tree, compareInt);
        int query;
        void* content;
        RBTStatusStruct status;

        // Test searching on an empty tree
        query = 43;
        content = (void*) 72;
        status = rbtFind(tree, (void*) &query, &content);
        if (status.status != NOT_FOUND)
        {
            printf("rbtFind: Error, status returned with %s instead of NOT_FOUND, when tree is empty\n", rbtStatusAsText(status.status));
            return -1;
        }
        if (status.node != NULL)
        {
            printf("rbtFind: Error, non NULL node returned when tree is empty\n");
            return -1;
        }
        if (content != (void*) 72)
        {
            printf("rbtFind: Error, content argument was altered when tree is empty\n");
            return -1;
        }

        // Construct a small tree
        constructTree(&tree);

        // Test trying to search with a NULL query
        status = rbtFind(tree, NULL, &content);
        content = (void*) 33;
        if (status.status != NULL_CONTENT)
        {
            printf("rbtFind: Error, status returned with %s instead of NULL_CONTENT, when a NULL query was given\n", rbtStatusAsText(status.status));
            return -1;
        }
        if (status.node != NULL)
        {
            printf("rbtFind: Error, non NULL node returned when NULL query was given\n");
            return -1;
        }
        if (content != (void*) 33)
        {
            printf("rbtFind: Error, content argument was altered when NULL query was given\n");
            return -1;
        }

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
        content = (void*) 99;
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
        if (content != (void*) 99)
        {
            printf("rbtFind: Error, content argument altered when query of %i was not found on a non-empty list\n", query);
            return -1;
        }

        // Test searching for a node that does not exist beyond 700
        query = 800;
        content = (void*) 232;
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
        if (content != (void*) 232)
        {
            printf("rbtFind: Error, content argument was altered when query of %i was not found on a non-empty list\n", query);
            return -1;
        }

        // Break tree by making 300 an empty node
        void* content300 = tree.head->left->right->content;
        tree.head->left->right->content = NULL;

        // Test EMPTY_NODE_ENCOUNTERED error
        query = 300;
        content = (void*) 17;
        status = rbtFind(tree, (void*) &query, &content);
        if (status.status != EMPTY_NODE_ENCOUNTERED)
        {
            printf("rbtFind: Error, status returned with %s instead of EMPTY_NODE_ENCOUNTERED, when the 300 node was set to have NULL content\n", rbtStatusAsText(status.status));
            return -1;
        }
        if (status.node == NULL)
        {
            printf("rbtFind: Error, NULL node returned when the 300 node was set to have NULL content\n");
            return -1;
        }
        if (status.node != tree.head->left->right)
        {
            printf("rbtFind: Error, incorrect node returned when the 300 node was set to have NULL content\n");
            return -1;
        }
        if (content != (void*) 17)
        {
            printf("rbtFind: Error, content argument was altered when the 300 node was set to have NULL content\n");
            return -1;
        }

        // Fix tree
        tree.head->left->right->content = content300;

        rbtClear(&tree, testclear);
    }
    printf("Completed rbtFind\n");

    // Test rbtRotateRight__
    printf("Testing rbtRotateRight__\n");
    {
        int result;
        constructTree(&tree);

        // Test trying to rotate if tree is NULL
        RBTNode* node = tree.head;
        result = rbtRotateRight__(NULL, node);
        if (result == 0)
        {
            printf("rbtRotateRight__: Returned success when tested while tree is NULL, should have been error\n");
            return -1;
        }

        // Test trying to rotate if leftChild is NULL
        result = rbtRotateRight__(&tree, NULL);
        if (result == 0)
        {
            printf("rbtRotateRight__: Returned success when tested while leftChild is NULL, should have been error\n");
            return -1;
        }

        // Test trying to rotate if both tree and leftChild are NULL
        result = rbtRotateRight__(NULL, NULL);
        if (result == 0)
        {
            printf("rbtRotateRight__: Returned success when tested while both tree and leftChild are NULL, should have been error\n");
            return -1;
        }

        // Test trying to rotate left child if tree.head is NULL
        RBTNode* head = tree.head;
        node = tree.head->left;
        tree.head = NULL;
        result = rbtRotateRight__(&tree, node);
        if (result == 0)
        {
            printf("rbtRotateRight__: Returned success when tested while head of tree is NULL, should have been error\n");
            return -1;
        }
        tree.head = head;

        // Test trying to rotate the head
        node = tree.head;
        //printf("rbtRotateRight__: Tree before rotation on head\n");
        //rbtPrint(tree, testitoa);
        result = rbtRotateRight__(&tree, node);
        //printf("rbtRotateRight__: Tree after rotation on head\n");
        //rbtPrint(tree, testitoa);
        if (result == 0)
        {
            printf("rbtRotateRight__: Returned success when attempting to rotate head, should have been error\n");
            return -1;
        }

        // Test trying to rotate right child
        node = tree.head->right;
        //printf("rbtRotateRight__: Tree before rotation on head's right\n");
        //rbtPrint(tree, testitoa);
        result = rbtRotateRight__(&tree, node);
        //printf("rbtRotateRight__: Tree after rotation on head's right\n");
        //rbtPrint(tree, testitoa);
        if (result == 0)
        {
            printf("rbtRotateRight__: Returned success when attempting to rotate head's right, should have been error\n");
            return -1;
        }

        // Test rotating left child
        node = tree.head->left;
        //printf("rbtRotateRight__: Tree before rotation on head's left\n");
        //rbtPrint(tree, testitoa);
        result = rbtRotateRight__(&tree, node);
        //printf("rbtRotateRight__: Tree after rotation on head's left\n");
        //rbtPrint(tree, testitoa);
        if (result != 0)
        {
            printf("rbtRotateRight__: Returned error when attempting to rotate head's left, should have been success: %i\n", result);
            return -1;
        }
        if (tree.head != node)
        {
            printf("rbtRotateRight__: Head's former left child did not replace head of list\n");
            return -1;
        }
        rbtClear(&tree, testclear);
        constructTree(&tree);

        // Test rotating left child's left child
        node = tree.head->left->left;
        //printf("rbtRotateRight__: Tree before rotation on head's left's left\n");
        //rbtPrint(tree, testitoa);
        result = rbtRotateRight__(&tree, node);
        //printf("rbtRotateRight__: Tree after rotation on head's left's left\n");
        //rbtPrint(tree, testitoa);
        if (result != 0)
        {
            printf("rbtRotateRight__: Returned error when attempting to rotate head's left's left, should have been success: %i\n", result);
            return -1;
        }

        rbtClear(&tree, testclear);
    }
    printf("Completed rbtRotateRight__\n");

    // Test rbtRotateLeft__
    printf("Testing rbtRotateLeft__\n");
    {
        int result;
        constructTree(&tree);

        // Test trying to rotate if tree is NULL
        RBTNode* node = tree.head;
        result = rbtRotateLeft__(NULL, node);
        if (result == 0)
        {
            printf("rbtRotateLeft__: Returned success when tested while tree is NULL, should have been error\n");
            return -1;
        }

        // Test trying to rotate if rightChild is NULL
        result = rbtRotateLeft__(&tree, NULL);
        if (result == 0)
        {
            printf("rbtRotateLeft__: Returned success when tested while rightChild is NULL, should have been error\n");
            return -1;
        }

        // Test trying to rotate if both tree and rightChild are NULL
        result = rbtRotateLeft__(NULL, NULL);
        if (result == 0)
        {
            printf("rbtRotateLeft__: Returned success when tested while both tree and rightChild are NULL, should have been error\n");
            return -1;
        }

        // Test trying to rotate right child if tree.head is NULL
        RBTNode* head = tree.head;
        node = tree.head->right;
        tree.head = NULL;
        result = rbtRotateLeft__(&tree, node);
        if (result == 0)
        {
            printf("rbtRotateLeft__: Returned success when tested while head of tree is NULL, should have been error\n");
            return -1;
        }
        tree.head = head;

        // Test trying to rotate the head
        node = tree.head;
        //printf("rbtRotateLeft__: Tree before rotation on head\n");
        //rbtPrint(tree, testitoa);
        result = rbtRotateLeft__(&tree, node);
        //printf("rbtRotateLeft__: Tree after rotation on head\n");
        //rbtPrint(tree, testitoa);
        if (result == 0)
        {
            printf("rbtRotateLeft__: Returned success when attempting to rotate head, should have been error\n");
            return -1;
        }

        // Test trying to rotate left child
        node = tree.head->left;
        //printf("rbtRotateLeft__: Tree before rotation on head's left\n");
        //rbtPrint(tree, testitoa);
        result = rbtRotateLeft__(&tree, node);
        //printf("rbtRotateLeft__: Tree after rotation on head's left\n");
        //rbtPrint(tree, testitoa);
        if (result == 0)
        {
            printf("rbtRotateLeft__: Returned success when attempting to rotate head's left, should have been error\n");
            return -1;
        }

        // Test rotating right child
        node = tree.head->right;
        //printf("rbtRotateLeft__: Tree before rotation on head's right\n");
        //rbtPrint(tree, testitoa);
        result = rbtRotateLeft__(&tree, node);
        //printf("rbtRotateLeft__: Tree after rotation on head's right\n");
        //rbtPrint(tree, testitoa);
        if (result != 0)
        {
            printf("rbtRotateLeft__: Returned error when attempting to rotate head's right, should have been success: %i\n", result);
            return -1;
        }
        if (tree.head != node)
        {
            printf("rbtRotateLeft__: Head's former right child did not replace head of list\n");
            return -1;
        }
        rbtClear(&tree, testclear);
        constructTree(&tree);

        // Test rotating right child's right child
        node = tree.head->right->right;
        //printf("rbtRotateLeft__: Tree before rotation on head's right's right\n");
        //rbtPrint(tree, testitoa);
        result = rbtRotateLeft__(&tree, node);
        //printf("rbtRotateLeft__: Tree after rotation on head's right's right\n");
        //rbtPrint(tree, testitoa);
        if (result != 0)
        {
            printf("rbtRotateLeft__: Returned error when attempting to rotate head's right's right, should have been success: %i\n", result);
            return -1;
        }

        rbtClear(&tree, testclear);
    }
    printf("Completed rbtRotateLeft__\n");

    // Test rbtGetPrev__
    printf("Testing rbtGetPrev__\n");
    {
        rbtInit(&tree, compareInt);

        // Insert the numbers 1-100 into the tree
        for (int i=1; i<101; i++)
        {
            void* content = malloc(sizeof(int));
            if (content == NULL)
            {
                printf("rbtGetPrev__: Error allocating space to store %i\n", i);
                perror("");
                return -1;
            }
            *(int*) content = i;

            RBTStatusStruct status = rbtInsert(&tree, content);
            if (status.status != SUCCESS)
            {
                printf("rbtGetPrev__: Error inserting %i. rbtInsert returned with %s\n", i, rbtStatusAsText(status.status));
                perror("");
                return -1;
            }
        }

        // Move to node 100
        RBTNode* node = tree.head;
        while (node->right != NULL)
        {
            node = node->right;
        }
        if (*(int*) node->content != 100)
        {
            printf("rbtGetPrev__: Attempt to get the node at the rightmost end of the tree failed, content is %i\n", *(int*) node->content);
            return -1;
        }

        // For 99-1, check that predecessor matches that value
        for (int i=99; i>0; i--)
        {
            node = rbtGetPrev__(node);

            if (node == NULL)
            {
                printf("rbtGetPrev__: Returned NULL when it should have found the previous node: %i\n", i);
                return -1;
            }
            if (i != *(int*) node->content)
            {
                printf("rbtGetPrev__: Previous node %i does not match expected %i\n", *(int*) node->content, i);
                return -1;
            }
        }

        // Check that one more call to rbtGetPrev__ returns NULL
        node = rbtGetPrev__(node);
        if (node != NULL)
        {
            printf("rbtGetPrev__: Error, did not return NULL even though there was no previous node\n");
            return -1;
        }

        rbtClear(&tree, testclear);
    }
    printf("Completed rbtGetPrev__\n");

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

int testitoa(char* buffer, void* content)
{
    itoa(buffer, *(int32_t*) content);
    
    return strlen(buffer);
}

int testclear(void* content)
{
    free(content);

    return 0;
}

int badclear(void* content)
{
    return 1;
}