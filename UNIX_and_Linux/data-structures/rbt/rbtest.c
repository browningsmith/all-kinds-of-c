#include "rbt.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "include/cooltools.h"
#include "rbtimpl.h"
#include "rbtprint.h"

// TODO: Finish testing rbtDelete

int compareInt(void* a, void* b); // Custom function for RBT to compare two ints
RBTNode* newIntNode(int num); // Creates a new RBT node containing an int in early tests
void displayNode(RBTNode node); // Displays the contents of a node
void constructTree(RBT* tree); // Constructs a small, valid, and balanced RBT without using RBTInsert
int testitoa(char* buffer, void* content); // Custom function used by rbtPrint to display the tree to the console
int testclear(void* content); // Custom function used by rbtClear to clear the contents of a node
int badclear(void* content); // Custom function that does nothing other than return nonzero, simulating if rbtClear received a clearing function that potentially could not clear a node's contents
int checkBlackHeight(RBT tree); // Helper function to test that the black height of the given tree is uniform throughout

int main()
{
    RBT tree;

    // Seed the random number generator with current system microseconds
    {
        struct timeval seed;
        gettimeofday(&seed, NULL);
        srand(seed.tv_usec);
    }
    
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
        RBTStatus status;

        // Test searching on an empty tree
        query = 43;
        content = (void*) 72;
        status = rbtFind(tree, (void*) &query, &content);
        if (status != NOT_FOUND)
        {
            printf("rbtFind: Error, status returned with %s instead of NOT_FOUND, when tree is empty\n", rbtStatusAsText(status));
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
        if (status != NULL_CONTENT)
        {
            printf("rbtFind: Error, status returned with %s instead of NULL_CONTENT, when a NULL query was given\n", rbtStatusAsText(status));
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
            if (status != SUCCESS)
            {
                printf("rbtFind: Error, status returned with %s instead of SUCCESS, when query of %i should have been matched\n", rbtStatusAsText(status), query);
                return -1;
            }
            if (content == NULL)
            {
                printf("rbtFind: Error, NULL content returned when query of %i should have been matched\n", query);
                return -1;
            }
        }

        // Test searching for a node that does not exist between 300 and 400
        query = 305;
        content = (void*) 99;
        status = rbtFind(tree, (void*) &query, &content);
        if (status != NOT_FOUND)
        {
            printf("rbtFind: Error, status returned with %s instead of NOT_FOUND, when query of %i should not have been matched\n", rbtStatusAsText(status), query);
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
        if (status != NOT_FOUND)
        {
            printf("rbtFind: Error, status returned with %s instead of NOT_FOUND, when query of %i should not have been matched\n", rbtStatusAsText(status), query);
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
        if (status != EMPTY_NODE_ENCOUNTERED)
        {
            printf("rbtFind: Error, status returned with %s instead of EMPTY_NODE_ENCOUNTERED, when the 300 node was set to have NULL content\n", rbtStatusAsText(status));
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
        constructTree(&tree);
        
        RBTNode* node;

        // Test rotating left child
        node = tree.head->left;
        //printf("rbtRotateRight__: Tree before rotation on head's left\n");
        //rbtPrint(tree, testitoa);
        rbtRotateRight__(&tree, node);
        //printf("rbtRotateRight__: Tree after rotation on head's left\n");
        //rbtPrint(tree, testitoa);
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
        rbtRotateRight__(&tree, node);
        //printf("rbtRotateRight__: Tree after rotation on head's left's left\n");
        //rbtPrint(tree, testitoa);

        rbtClear(&tree, testclear);
    }
    printf("Completed rbtRotateRight__\n");

    // Test rbtRotateLeft__
    printf("Testing rbtRotateLeft__\n");
    {
        constructTree(&tree);

        RBTNode* node;

        // Test rotating right child
        node = tree.head->right;
        //printf("rbtRotateLeft__: Tree before rotation on head's right\n");
        //rbtPrint(tree, testitoa);
        rbtRotateLeft__(&tree, node);
        //printf("rbtRotateLeft__: Tree after rotation on head's right\n");
        //rbtPrint(tree, testitoa);
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
        rbtRotateLeft__(&tree, node);
        //printf("rbtRotateLeft__: Tree after rotation on head's right's right\n");
        //rbtPrint(tree, testitoa);

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

            RBTStatus status = rbtInsert(&tree, content);
            if (status != SUCCESS)
            {
                printf("rbtGetPrev__: Error inserting %i. rbtInsert returned with %s\n", i, rbtStatusAsText(status));
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

    // Test rbtInsert
    printf("Testing rbtInsert\n");
    {
        RBTStatus status;
        void* content;
        
        rbtInit(&tree, compareInt);

        // Test trying to insert NULL content
        status = rbtInsert(&tree, NULL);
        if (status != NULL_CONTENT)
        {
            printf("rbtInsert: Error, returned with %s when attempting to insert NULL content\n", rbtStatusAsText(status));
            perror("");
            return -1;
        }
        if (rbtIsEmpty(tree) != 1)
        {
            printf("rbtInsert: Error, tree is not empty after attempted insert with NULL content\n");
            return -1;
        }

        // Test inserting into an empty tree
        content = malloc(sizeof(int));
        if (content == NULL)
        {
            perror("rbtInsert: Unable to allocate space for new int for inserting into an empty tree");
            return -1;
        }
        *(int*) content = 9000;
        status = rbtInsert(&tree, content);
        if (status != SUCCESS)
        {
            printf("rbtInsert: Error, returned with %s when attempting to insert into an empty tree\n", rbtStatusAsText(status));
            perror("");
            return -1;
        }
        if (rbtIsEmpty(tree) != 0)
        {
            printf("rbtInsert: Error, tree is empty after attempted insert into empty tree\n");
            return -1;
        }
        if (tree.head->isRed != 0)
        {
            printf("rbtInsert: Error, new node is not black when added to an empty tree\n");
            return -1;
        }
        if (*(int*) tree.head->content != 9000)
        {
            printf("rbtInsert: Error, int did not get added as head when inserted into an empty tree\n");
            return -1;
        }

        // Test attempting to insert into a broken tree
        rbtClear(&tree, testclear);
        constructTree(&tree);

        content = malloc(sizeof(int)); // Allocate space for new int
        if (content == NULL)
        {
            perror("rbtInsert: Unable to allocate space for new int on inserting into a broken tree test\n");
            return -1;
        }
        *(int*) content = 501; // Should try to insert this along path 400->600->500
        RBTNode* brokenNode = tree.head->right; // 660 node
        void* brokenContent = brokenNode->content; // Break this node
        brokenNode->content = NULL;
        status = rbtInsert(&tree, content);
        if (status != EMPTY_NODE_ENCOUNTERED)
        {
            printf("rbtInsert: Error, returned with %s when attempting to insert along a path that contained a NULL content node\n", rbtStatusAsText(status));
            perror("");
            return -1;
        }

        free(content);
        brokenNode->content = brokenContent; // Fix tree
        rbtClear(&tree, testclear);

        // Test that black height is uniform on a tree generated by random numbers
        for (int i=0; i<200000; i++)
        {
            int newInt = rand();

            content = malloc(sizeof(int));
            if (content == NULL)
            {
                perror("rbtInsert: Error, unable to allocate space for new int when testing randomly generated tree\n");
            }
            *(int*) content = newInt;
            status = rbtInsert(&tree, content);
            if (status != SUCCESS)
            {
                printf("rbtInsert: Error, rbtInsert returned with status %s when inserting %i\n", rbtStatusAsText(status), newInt);
                return -1;
            }
            content = NULL;
            status = rbtFind(tree, (void*) &newInt, &content);
            if (status != SUCCESS)
            {
                printf("rbtInsert: Error, rbtFind was unable to find the newly inserted integer %i\n", newInt);
                return -1;
            }
        }
        int height = checkBlackHeight(tree);
        if (height < 0)
        {
            printf("rbtInsert: Error, black height of the randomly constructed tree is not uniform across the tree\n");
            return -1;
        }
        
        printf("Black height: %i\n", height);

        rbtClear(&tree, testclear);
    }
    printf("Completed rbtInsert\n");

    // Test rbtDelete
    printf("Testing rbtDelete\n");
    {
        RBTStatus status;
        void* content;
        int query;
        void* returnedContent;

        rbtInit(&tree, compareInt);
        
        // Test trying to delete with a NULL query
        returnedContent = (void*) 92;
        status = rbtDelete(&tree, NULL, &returnedContent);
        if (status != NULL_CONTENT)
        {
            printf("rbtDelete: Error, returned with %s when attempting to delete with a NULL query\n", rbtStatusAsText(status));
            perror("");
            return -1;
        }
        if (returnedContent != (void*) 92)
        {
            printf("rbtDelete: returnedContent argument was altered when attempting to delete with a NULL query\n");
            return -1;
        }

        // Test trying to delete from an empty tree
        query = 45000;
        returnedContent = (void*) 66;
        status = rbtDelete(&tree, (void*) &query, &returnedContent);
        if (status != NOT_FOUND)
        {
            printf("rbtDelete: Error, returned with %s when attempting to delete from an empty tree\n", rbtStatusAsText(status));
            perror("");
            return -1;
        }
        if (returnedContent != (void*) 66)
        {
            printf("rbtDelete: returnedContent argument was altered when attempting to delete from an empty tree\n");
            return -1;
        }

        // Test deleting one node from the tree
        query = 9876;
        content = malloc(sizeof(int));
        if (content == NULL)
        {
            perror("rbtDelete: Unable to allocate space for new int when testing the deletion in a tree with one node\n");
            return -1;
        }
        *(int*) content = query;
        status = rbtInsert(&tree, content);
        if (status != SUCCESS)
        {
            printf("rbtDelete: rbtInsert returned with %s when attempting to insert, while testing the deletion in a tree with only one node\n", rbtStatusAsText(status));
            perror("");
            return -1;
        }
        status = rbtDelete(&tree, (void*) &query, &returnedContent);
        if (status != SUCCESS)
        {
            printf("rbtDelete: Error, returned with %s even though node to delete was queried correctly, when testing the deletion in a tree with only one node\n", rbtStatusAsText(status));
            perror("");
            return -1;
        }
        if (rbtIsEmpty(tree) == 0)
        {
            printf("rbtDelete: Tree is not registering as empty even though the only node in the tree should have been deleted\n");
            return -1;
        }
        if (query != *(int*) returnedContent)
        {
            printf("rbtDelete: Returned content does not match the query, when testing the deletion in a tree with only one node\n");
            return -1;
        }
        free(returnedContent);

        // Test attempting to delete a node from a broken tree
        constructTree(&tree);
        query = 100; // rbtDelete will search along 400->200->100 path
        RBTNode* brokenNode = tree.head->left; // 200 node
        void* brokenContent = brokenNode->content;
        brokenNode->content = NULL;
        returnedContent = (void*) 833;
        status = rbtDelete(&tree, (void*) &query, &returnedContent);
        if (status != EMPTY_NODE_ENCOUNTERED)
        {
            printf("rbtDelete: Returned with %s when attempting to delete a node along a path containing an empty node\n", rbtStatusAsText(status));
            perror("");
            return -1;
        }
        if (returnedContent != (void*) 833)
        {
            printf("rbtDelete: returnedContent argument was altered when attempting to delete a node along a path containing an empty node\n");
            return -1;
        }
        brokenNode->content = brokenContent;
        rbtClear(&tree, testclear);

        // Test inserting and deleting random numbers between 0 and 999
        // Since this will run for 200,000 iterations it ensures some numbers will be successfully inserted then deleted
        for (int i=0; i<200000; i++)
        {
            query = rand() % 1000;

            // Attempt to delete the number from the tree
            status = rbtDelete(&tree, (void*) &query, &returnedContent);
            if (status == SUCCESS)
            {
                if (*(int*) returnedContent != query)
                {
                    printf("rbtDelete: Returned content %i does not match the query %i when testing the insertion and deletion of random integers\n", *(int*) returnedContent, query);
                    return -1;
                }
                free(returnedContent);
            }
            // If number was not already in the tree, insert it
            else if (status == NOT_FOUND)
            {
                content = malloc(sizeof(int));
                if (content == NULL)
                {
                    perror("rbtDelete: Unable to allocate space for a new int while testing the insertion and deletion of random integers\n");
                    return -1;
                }
                *(int*) content = query;
                int status = rbtInsert(&tree, content);
                if (status != SUCCESS)
                {
                    printf("rbtDelete: rbtInsert returned with %s when attempting to insert a random int into the tree\n", rbtStatusAsText(status));
                    perror("");
                    return -1;
                }
            }
            else
            {
                printf("rbtDelete: Returned with %s when attempting to delete a random integer from a tree\n", rbtStatusAsText(status));
                perror("");
                return -1;
            }
        }
        int height = checkBlackHeight(tree);
        if (height < 0)
        {
            printf("rbtDelete: Error, black height of the randomly constructed tree is not uniform across the tree\n");
            return -1;
        }
        
        printf("Black height: %i\n", height);

        rbtClear(&tree, testclear);
    }
    printf("Testing rbtDelete\n");

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

int checkBlackHeight(RBT tree)
{
    int blackHeight = 0;
    int firstBlackHeight = -1;

    RBTNode* node = tree.head;
    if (node == NULL)
    {
        return 0;
    }

    int state = 1;
    // 1 = examine this node and recurse left
    // 2 = recurse right
    // 3 = return up

    while (1)
    {
        if (state == 1)
        {
            // If node is black, increment black height
            if (node->isRed == 0)
            {
                blackHeight++;
            }

            // If left node is NULL, record final black height
            if (node->left == NULL)
            {
                blackHeight++;

                if (blackHeight != firstBlackHeight)
                {
                    if (firstBlackHeight < 0)
                    {
                        firstBlackHeight = blackHeight;
                    }
                    else
                    {
                        return -1;
                    }
                }

                blackHeight--;
                state = 2;
                continue;
            }
            else
            {
                node = node->left;
                // state remains at 1
                continue;
            }
        }

        if (state == 2)
        {
            // If right node is NULL, record final black height
            if (node->right == NULL)
            {
                blackHeight++;

                if (blackHeight != firstBlackHeight)
                {
                    if (firstBlackHeight < 0)
                    {
                        firstBlackHeight = blackHeight;
                    }
                    else
                    {
                        return -1;
                    }
                }

                blackHeight--;
                state = 3;
                continue;
            }
            else
            {
                node = node->right;
                state = 1;
                continue;
            }
        }

        if (state == 3)
        {
            if (node->isRed == 0)
            {
                blackHeight--;
            }

            if (node->parent == NULL)
            {
                break;
            }

            // If we are a left child, set state to 2
            if (node == node->parent->left)
            {
                state = 2;
            }
            else
            {
                state = 3;
            }

            node = node->parent;
            continue;
        }
    }

    return firstBlackHeight;
}