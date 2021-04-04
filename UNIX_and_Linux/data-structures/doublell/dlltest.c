#include <stdio.h>
#include <stdlib.h>

#include "doublell.h"
#include "doublellimpl.h"

void makeList(DLL* list);
int clearInt(void* number);

int main(int argc, char** argv)
{   
    printf("Running tests on doublell\n");
    printf("Sizeof DLLNode: %lu\n", sizeof(DLLNode));
    printf("Sizeof int: %lu\n", sizeof(int));
    printf("Sizeof DLLNode containing int: %lu\n", sizeof(DLLNode) + sizeof(int));

    DLL list;
    DLLIterator iterator;
    
    printf("Testing dllInit\n");
    // Test dllInit
    {
        int testInt = 5;

        DLLNode testNode = {

            .prev = NULL,
            .next = NULL,
            .content = (void*) &testInt
        };

        if (*(int*) testNode.content != 5)
        {
            printf("dllInit: Error manually creating new node on the stack\n");
            return -1;
        }

        list.head = &testNode;
        list.tail = &testNode;

        if (list.head == NULL)
        {
            printf("dllInit: Error, list.head is NULL before dllInit\n");
            return -1;
        }
        if (list.tail == NULL)
        {
            printf("dllInit: Error, list.tail is NULL before dllInit\n");
            return -1;
        }

        dllInit(&list);

        if (list.head != NULL)
        {
            printf("dllInit: Error, list.head is not NULL after dllInit\n");
            return -1;
        }
        if (list.tail != NULL)
        {
            printf("dllInit: Error, list.tail is not NULL after dllInit\n");
            return -1;
        }
    }
    printf("Completed dllInit\n");

    printf("Testing dllInsertNode__\n");
    // Test dllInsertNode__
    {
        // Test creating a new node with no neighbors
        int num2 = 2;
        DLLNode* node2 = dllInsertNode__((void*) &num2, NULL, NULL);
        if (node2 == NULL)
        {
            perror("dllInsertNode__: Unable to insert node on first test");
            return -1;
        }
        if (node2->prev != NULL)
        {
            printf("dllInsertNode__: node->prev is not NULL, but should have no neighbors\n");
            return -1;
        }
        if (node2->next != NULL)
        {
            printf("dllInsertNode__: node->next is not NULL, but should have no neighbors\n");
            return -1;
        }
        if (node2->content == NULL)
        {
            printf("dllInsertNode__: node->content is NULL on first test\n");
            return -1;
        }
        if (*(int*) node2->content != 2)
        {
            printf("dllInsertNode__: node->content is incorrect on first test\n");
            return -1;
        }

        // Test inserting a node to the left
        int num1 = 1;
        DLLNode* node1 = dllInsertNode__((void*) &num1, NULL, node2);
        if (node1 == NULL)
        {
            perror("dllInsertNode__: Unable to insert node on second test");
            return -1;
        }
        if (node1->prev != NULL)
        {
            printf("dllInsertNode__: node->prev is not NULL, but should have no left neighbor on the second test\n");
            return -1;
        }
        if (node1->next != node2)
        {
            printf("dllInsertNode__: node->next is not set to correct right neighbor on the second test\n");
            return -1;
        }
        if (node1->content == NULL)
        {
            printf("dllInsertNode__: node->content is NULL on second test\n");
            return -1;
        }
        if (*(int*) node1->content != 1)
        {
            printf("dllInsertNode__: node->content is incorrect on second test\n");
            return -1;
        }
        if (node2->prev != node1)
        {
            printf("dllInsertNode__: node2->prev is not set to correct left neighbor on the second test\n");
            return -1;
        }

        // Test inserting a node on the right
        int num4 = 4;
        DLLNode* node4 = dllInsertNode__((void*) &num4, node2, NULL);
        if (node4 == NULL)
        {
            perror("dllInsertNode__: Unable to insert node on third test");
            return -1;
        }
        if (node4->prev != node2)
        {
            printf("dllInsertNode__: node->prev is not set to correct left neighbor, on the third test\n");
            return -1;
        }
        if (node4->next != NULL)
        {
            printf("dllInsertNode__: node->next is not NULL, but should have no right neighbor on the third test\n");
            return -1;
        }
        if (node4->content == NULL)
        {
            printf("dllInsertNode__: node->content is NULL on third test\n");
            return -1;
        }
        if (*(int*) node4->content != 4)
        {
            printf("dllInsertNode__: node->content is incorrect on third test\n");
            return -1;
        }
        if (node2->next != node4)
        {
            printf("dllInsertNode__: node2->next is not set to correct right neighbor on the third test\n");
            return -1;
        }

        // Test inserting a node with two neighbors
        int num3 = 3;
        DLLNode* node3 = dllInsertNode__((void*) &num3, node2, node4);
        if (node3 == NULL)
        {
            perror("dllInsertNode__: Unable to insert node on fourth test");
            return -1;
        }
        if (node3->prev != node2)
        {
            printf("dllInsertNode__: node->prev is not set to correct left neighbor, on the fourth test\n");
            return -1;
        }
        if (node3->next != node4)
        {
            printf("dllInsertNode__: node->next is not set to correct right neighbor on the fourth test\n");
            return -1;
        }
        if (node3->content == NULL)
        {
            printf("dllInsertNode__: node->content is NULL on fourth test\n");
            return -1;
        }
        if (*(int*) node3->content != 3)
        {
            printf("dllInsertNode__: node->content is incorrect on fourth test\n");
            return -1;
        }
        if (node2->next != node3)
        {
            printf("dllInsertNode__: node2->next is not set to correct right neighbor on the fourth test\n");
            return -1;
        }
        if (node4->prev != node3)
        {
            printf("dllInsertNode__: node4->prev is not set to correct left neighbor on the fourth test\n");
            return -1;
        }
        //printf("Freeing %x\n", node1);
        free(node1);
        //printf("Freeing %x\n", node2);
        free(node2);
        //printf("Freeing %x\n", node3);
        free(node3);
        //printf("Freeing %x\n", node4);
        free(node4);
    }
    printf("Completed dllInsertNode__\n");

    printf("Testing dllIsEmpty\n");
    // Test dllIsEmpty
    {
        dllInit(&list);

        if (!dllIsEmpty(list))
        {
            printf("dllIsEmpty: Error, list is not returning as empty after init\n");
            return -1;
        }

        DLLNode node;

        // Test dllIsEmpty with only head node
        list.head = &node;
        if (!dllIsEmpty(list))
        {
            printf("dllIsEmpty: Error, list is not returning as empty when tail is empty\n");
            return -1;
        }

        // Test dllIsEmpty with only tail node
        list.head = NULL;
        list.tail = &node;
        if (!dllIsEmpty(list))
        {
            printf("dllIsEmpty: Error, list is not returning as empty when head is empty\n");
            return -1;
        }

        // Test dllIsEmpty with both head and tail
        list.head = &node;
        if (dllIsEmpty(list))
        {
            printf("dllIsEmpty: Error, list is returning as empty when head and tail do exist\n");
            return -1;
        }

    }
    printf("Completed dllIsEmpty\n");

    printf("Testing dllPush\n");
    // Test dllPush
    {
        dllInit(&list);

        // Test pushing onto empty list
        int num1 = 5;
        if (dllPush(&list, (void*) &num1) < 0)
        {
            perror("dllPush: Unable to create space for node");
            return -1;
        }
        if (list.head == NULL)
        {
            printf("dllPush: Error, head of list is still NULL\n");
            return -1;
        }
        if (list.tail == NULL)
        {
            printf("dllPush: Error, tail of list is still NULL\n");
            return -1;
        }
        if (list.head != list.tail)
        {
            printf("dllPush: Error, head and tail of list are not the same after insert to empty list\n");
            return -1;
        }
        if (*(int*) list.head->content != 5)
        {
            printf("dllPush: Error, content of first inserted node is incorrect\n");
            return -1;
        }

        // Test pushing onto non empty list
        int num2 = 12;
        if (dllPush(&list, (void*) &num2) < 0)
        {
            perror("dllPush: Unable to create space for second node");
            return -1;
        }
        if (list.head == NULL)
        {
            printf("dllPush: Error, head of list is NULL after second node inserted\n");
            return -1;
        }
        if (list.head->next == NULL)
        {
            printf("dllPush: Error, next node is NULL after second insert\n");
            return -1;
        }
        if (list.head->next->prev == NULL)
        {
            printf("dllPush: Error, prev node of next is NULL after second insert\n");
            return -1;
        }
        if (list.head != list.head->next->prev)
        {
            printf("dllPush: Error, prev and next node do not point to each other\n");
            return -1;
        }
        if (list.tail == NULL)
        {
            printf("dllPush: Error, tail of list no longer attached after second insert\n");
            return -1;
        }
        if (list.head->next != list.tail)
        {
            printf("dllPush: Error, next node in a list of only two is not also the tail\n");
            return -1;
        }
        if (*(int*) list.head->content != 12)
        {
            printf("dllPush: Error, content is incorrect after second insert\n");
            return -1;
        }

        //printf("Freeing %x\n", list.head->next);
        free(list.head->next);
        //printf("Freeing %x\n", list.head);
        free(list.head);
    }
    printf("Completed dllPush\n");

    printf("Testing dllPushTail\n");
    // Test dllPushTail
    {
        dllInit(&list);

        // Test pushing onto empty list
        int num1 = 5;
        if (dllPushTail(&list, (void*) &num1) < 0)
        {
            perror("dllPushTail: Unable to create space for node");
            return -1;
        }
        if (list.head == NULL)
        {
            printf("dllPushTail: Error, head of list is still NULL\n");
            return -1;
        }
        if (list.tail == NULL)
        {
            printf("dllPushTail: Error, tail of list is still NULL\n");
            return -1;
        }
        if (list.head != list.tail)
        {
            printf("dllPushTail: Error, head and tail of list are not the same after insert to empty list\n");
            return -1;
        }
        if (*(int*) list.head->content != 5)
        {
            printf("dllPushTail: Error, content of first inserted node is incorrect\n");
            return -1;
        }

        // Test pushing onto non empty list
        int num2 = 12;
        if (dllPushTail(&list, (void*) &num2) < 0)
        {
            perror("dllPushTail: Unable to create space for second node");
            return -1;
        }
        if (list.head == NULL)
        {
            printf("dllPushTail: Error, head of list is NULL after second node inserted\n");
            return -1;
        }
        if (list.head->next == NULL)
        {
            printf("dllPushTail: Error, next node is NULL after second insert\n");
            return -1;
        }
        if (list.head->next->prev == NULL)
        {
            printf("dllPushTail: Error, prev node of next is NULL after second insert\n");
            return -1;
        }
        if (list.head != list.head->next->prev)
        {
            printf("dllPushTail: Error, prev and next node do not point to each other\n");
            return -1;
        }
        if (list.tail == NULL)
        {
            printf("dllPushTail: Error, tail of list no longer attached after second insert\n");
            return -1;
        }
        if (list.head->next != list.tail)
        {
            printf("dllPushTail: Error, next node in a list of only two is not also the tail\n");
            return -1;
        }
        if (*(int*) list.tail->content != 12)
        {
            printf("dllPushTail: Error, content is incorrect after second insert\n");
            return -1;
        }

        //printf("Freeing %x\n", list.head->next);
        free(list.head->next);
        //printf("Freeing %x\n", list.head);
        free(list.head);
    }
    printf("Completed dllPushTail\n");

    printf("Testing dllDeleteNode__\n");
    // Test dllDeleteNode__
    {
        dllInit(&list);

        // Test that there are no errors on deleting one node
        int num1 = 5;
        if (dllPush(&list, (void*) &num1) < 0)
        {
            perror("dllDeleteNode__: Unable to insert single node");
            return -1;
        }
        void* result = dllDeleteNode__(list.head);
        if (*(int*) result != 5)
        {
            printf("dllDeleteNode__: Error, proper content was not returned on first delete\n");
            return -1;
        }

        // Test that there are no errors on deleting a node between two other nodes
        dllInit(&list);
        num1 = 3;
        if (dllPush(&list, (void*) &num1) < 0)
        {
            perror("dllDeleteNode__: Unable to insert first node");
            return -1;
        }
        int num2 = 2;
        if (dllPush(&list, (void*) &num2) < 0)
        {
            perror("dllDeleteNode__: Unable to insert second node");
            return -1;
        }
        int num3 = 3;
        if (dllPush(&list, (void*) &num3) < 0)
        {
            perror("dllDeleteNode__: Unable to insert third node");
            return -1;
        }

        result = dllDeleteNode__(list.head->next);
        if (*(int*) result != 2)
        {
            printf("dllDeleteNode__: Error, proper content was not returned on second delete\n");
            return -1;
        }
        if (list.head->next == NULL)
        {
            printf("dllDeleteNode__: Error, head of list's next is NULL\n");
            return -1;
        }
        if (list.tail->prev == NULL)
        {
            printf("dllDeleteNode__: Error, tail of list's prev is NULL\n");
            return -1;
        }
        if (list.head->next != list.tail)
        {
            printf("dllDeleteNode__: Delete operation did not attach adjacent nodes together\n");
            return -1;
        }
        if (list.tail->prev != list.head)
        {
            printf("dllDeleteNode__: Delete operation did not attach adjacent nodes together\n");
            return -1;
        }

        dllDeleteNode__(list.head);
        dllDeleteNode__(list.tail);
    }
    printf("Completed dllDeleteNode__\n");

    printf("Testing dllGetHead\n");
    // Test dllGetHead
    {
        dllInit(&list);
        void* content = (void*) 17;

        // Test calling dllGetHead on an empty list
        int result = dllGetHead(list, &content);
        if (result != -1)
        {
            printf("dllGetHead: Error, returned success when called on empty list\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllGetHead: Error, did not return NULL content when called on empty list\n");
            return -1;
        }

        // Test calling dllGetHead on non empty list
        int num1 = 17;
        if (dllPush(&list, (void*) &num1) < 0)
        {
            perror("dllGetHead: Error adding node to list\n");
            return -1;
        }
        content = NULL;
        result = dllGetHead(list, &content);
        if (result != 0)
        {
            printf("dllGetHead: Error, did not return with success\n");
            return -1;
        }
        if (*(int*) content != 17)
        {
            printf("dllGetHead: Error, did not return with proper content\n");
            return -1;
        }

        dllDeleteNode__(list.head);
    }
    printf("Completed dllGetHead\n");

    printf("Testing dllGetTail\n");
    // Test dllGetTail
    {
        dllInit(&list);
        void* content = (void*) 17;

        // Test calling dllGetTail on an empty list
        int result = dllGetTail(list, &content);
        if (result != -1)
        {
            printf("dllGetTail: Error, returned success when called on empty list\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllGetTail: Error, did not return NULL content when called on empty list\n");
            return -1;
        }

        // Test calling dllGetTail on a list with two nodes
        int num1 = 54;
        if (dllPush(&list, (void*) &num1) < 0)
        {
            perror("dllGetTail: Error inserting first node\n");
            return -1;
        }
        int num2 = 55;
        if (dllPush(&list, (void*) &num2) < 0)
        {
            perror("dllGetTail: Error inserting second node\n");
            return -1;
        }
        content = NULL;
        result = dllGetTail(list, &content);
        if (result != 0)
        {
            printf("dllGetTail: Error, did not return success when called on non empty list\n");
            return -1;
        }
        if (*(int*) content != 54)
        {
            printf("dllGetTail: Error, incorrect content returned from non empty list\n");
            return -1;
        }

        dllDeleteNode__(list.head->next);
        dllDeleteNode__(list.head);
    }
    printf("Completed dllGetTail\n");
    
    printf("Testing dllPop\n");
    // Test dllPop
    {
        dllInit(&list);
        void* content;
        int result;

        // Test dllPop on empty list
        content = (void*) 17;
        result = dllPop(&list, &content);
        if (result == 0)
        {
            printf("dllPop: Error, incorrect result on empty list\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllPop: Error, bad content returned when called on empty list\n");
            return -1;
        }
        if (!dllIsEmpty(list))
        {
            printf("dllPop: Error, list not empty after calling on already empty list\n");
        }

        // Test dllPop on list with only one element
        int num1 = 12;
        if (dllPush(&list, (void*) &num1) < 0)
        {
            perror("dllPop: Unable to push node for second test");
            return -1;
        }
        content = NULL;
        result = dllPop(&list, &content);
        if (result < 0)
        {
            printf("dllPop: Error, incorrect result when called on single element list\n");
            return -1;
        }
        if (content == NULL)
        {
            printf("dllPop: Error, NULL content returned when called on single element list\n");
            return -1;
        }
        if (*(int*) content != 12)
        {
            printf("dllPop: Error, incorrect content returned when called on single element list\n");
            return -1;
        }
        if (!dllIsEmpty(list))
        {
            printf("dllPop: Error, list is not empty even after pop operation\n");
            return -1;
        }

        // Test dllPop with a broken list
        num1 = 12;
        if (dllPush(&list, (void*) &num1) < 0)
        {
            perror("Unable to push on first node for third test\n");
            return -1;
        }
        int num2 = 14;
        if (dllPushTail(&list, (void*) &num2) < 0)
        {
            perror("Unable to push on second node for third test\n");
            return -1;
        }
        list.head->next = NULL;
        content = (void*) 50;
        result = dllPop(&list, &content);
        if (result == 0)
        {
            printf("dllPop: Error, incorrect result on list with broken head\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllPop: Error, incorrect content returned on list with broken head\n");
            return -1;
        }
        if (dllIsEmpty(list))
        {
            printf("dllPop: Error, list is empty even though no operation should have been performed with a broken head node\n");
            return -1;
        }
        // Fix list before deleting
        list.head->next = list.tail;
        dllDeleteNode__(list.tail);
        dllDeleteNode__(list.head);
        dllInit(&list);

        // Test dllPop on a list of two elements
        num1 = 45;
        if (dllPush(&list, (void*) &num1) < 0)
        {
            perror("dllPop: Unable to push first node for fourth test");
            return -1;
        }
        num2 = 47;
        if (dllPush(&list, (void*) &num2) < 0)
        {
            perror("dllPop: Unable to push second node for fourth test");
            return -1;
        }
        content = NULL;
        result = dllPop(&list, &content);
        if (result < 0)
        {
            printf("dllPop: Error, incorrect result on list with two nodes\n");
            return -1;
        }
        if (content == NULL)
        {
            printf("dllPop: Error, NULL content returned on list with two nodes\n");
            return -1;
        }
        if (*(int*) content != 47)
        {
            printf("dllPop: Error, incorrect content returned on list with two nodes\n");
            return -1;
        }
        if (dllIsEmpty(list))
        {
            printf("dllPop: Error, list is empty even though one node should be left\n");
            return -1;
        }
        if (*(int*) list.head->content != 45)
        {
            printf("dllPop: Error, next node did not replace head after pop\n");
            return -1;
        }

        dllPop(&list, &content);
    }
    printf("Completed dllPop\n");

    printf("Testing dllPopTail\n");
    // Test dllPopTail
    {
        dllInit(&list);
        void* content;
        int result;

        // Test dllPopTail on empty list
        content = (void*) 17;
        result = dllPop(&list, &content);
        if (result == 0)
        {
            printf("dllPopTail: Error, incorrect result on empty list\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllPopTail: Error, bad content returned when called on empty list\n");
            return -1;
        }

        // Test dllPopTail on list with only one element
        int num1 = 12;
        if (dllPushTail(&list, (void*) &num1) < 0)
        {
            perror("dllPopTail: Unable to push node for second test");
            return -1;
        }

        content = NULL;
        result = dllPopTail(&list, &content);
        if (result < 0)
        {
            printf("dllPopTail: Error, incorrect result when called on single element list\n");
            return -1;
        }
        if (content == NULL)
        {
            printf("dllPopTail: Error, NULL content returned when called on single element list\n");
            return -1;
        }
        if (*(int*) content != 12)
        {
            printf("dllPopTail: Error, incorrect content returned when called on single element list\n");
            return -1;
        }
        if (!dllIsEmpty(list))
        {
            printf("dllPopTail: Error, list is not empty even after pop operation\n");
            return -1;
        }

        // Test dllPopTail with a broken list
        num1 = 12;
        if (dllPushTail(&list, (void*) &num1) < 0)
        {
            perror("Unable to push on first node for third test\n");
            return -1;
        }
        int num2 = 14;
        if (dllPush(&list, (void*) &num2) < 0)
        {
            perror("Unable to push on second node for third test\n");
            return -1;
        }
        list.tail->prev = NULL;
        content = (void*) 50;
        result = dllPopTail(&list, &content);
        if (result == 0)
        {
            printf("dllPopTail: Error, incorrect result on list with broken head\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllPopTail: Error, incorrect content returned on list with broken head\n");
            return -1;
        }
        if (dllIsEmpty(list))
        {
            printf("dllPopTail: Error, list is empty even though no operation should have been performed with a broken head node\n");
            return -1;
        }
        // Fix list
        list.tail->prev = list.head;
        dllDeleteNode__(list.tail);
        dllDeleteNode__(list.head);
        dllInit(&list);

        // Test dllPopTail on a list of two elements
        num1 = 45;
        if (dllPushTail(&list, (void*) &num1) < 0)
        {
            perror("dllPopTail: Unable to push first node for fourth test");
            return -1;
        }
        num2 = 47;
        if (dllPushTail(&list, (void*) &num2) < 0)
        {
            perror("dllPopTail: Unable to push second node for fourth test");
            return -1;
        }
        content = NULL;
        result = dllPopTail(&list, &content);
        if (result < 0)
        {
            printf("dllPopTail: Error, incorrect result on list with two nodes\n");
            return -1;
        }
        if (content == NULL)
        {
            printf("dllPopTail: Error, NULL content returned on list with two nodes\n");
            return -1;
        }
        if (*(int*) content != 47)
        {
            printf("dllPopTail: Error, incorrect content returned on list with two nodes\n");
            return -1;
        }
        if (dllIsEmpty(list))
        {
            printf("dllPopTail: Error, list is empty even though one node should be left\n");
            return -1;
        }
        if (*(int*) list.tail->content != 45)
        {
            printf("dllPopTail: Error, next node did not replace tail after pop\n");
            return -1;
        }

        dllPopTail(&list, &content);
    }
    printf("Completed dllPopTail\n");
  
    printf("Testing dllClear\n");
    // Test dllClear
    {
        int result;

        // Test clearing empty list
        dllInit(&list);
        result = dllClear(&list, clearInt);
        if (result != 0)
        {
            printf("dllClear: Error clearing already empty list\n");
            return -1;
        }
        
        // Test clearing without clearingFunction
        int num1 = 1;
        if (dllPush(&list, (void*) &num1))
        {
            perror("dllClear: Unable to push on first node for second test\n");
            return -1;
        }
        int num2 = 2;
        if (dllPush(&list, (void*) &num2))
        {
            perror("dllClear: Unable to push on first node for second test\n");
            return -1;
        }
        int num3 = 3;
        if (dllPush(&list, (void*) &num3))
        {
            perror("dllClear: Unable to push on first node for second test\n");
            return -1;
        }
        result = dllClear(&list, NULL);
        if (result != 0)
        {
            printf("dllClear: Error clearing list with no clearing function specified\n");
            return -1;
        }
        if (!dllIsEmpty(list))
        {
            printf("dllClear: Error, list is not empty after call with no specified clearingFunction\n");
            return -1;
        }

        // Test clearing with clearingFunction
        makeList(&list);
        result = dllClear(&list, clearInt);
        if (result != 0)
        {
            printf("dllClear: Error clearing list with clearing function specified\n");
            return -1;
        }
        if (!dllIsEmpty(list))
        {
            printf("dllClear: Error, list is not empty after call with specified clearingFunction\n");
            return -1;
        }

        // Test attempting to clear a broken list
        makeList(&list);
        DLLNode* leftBehindNode = list.head; // Should be node 12
        DLLNode* nextNode = leftBehindNode->next; // Should be node 11
        leftBehindNode->next = NULL; // Node 12 should be left behind without content
        result = dllClear(&list, clearInt);
        if (result == 0)
        {
            printf("dllClear: Error, incorrect result on clearing broken list\n");
            return -1;
        }
        if (dllIsEmpty(list))
        {
            printf("dllClear: Error, list appears empty even though dllClear was called on a broken list, and shouldn't have cleared it\n");
            return -1;
        }
        if (list.head != leftBehindNode)
        {
            printf("dllClear: Wrong node left behind in broken list\n");
            return -1;
        }

        // Fix list (re-add content and reattach broken link)
        leftBehindNode->content = malloc(sizeof(int));
        if (leftBehindNode->content == NULL)
        {
            perror("dllClear: Unable to reallocate space for a new int to fix broken list\n");
            return -1;
        }
        leftBehindNode->next = nextNode;

        // Test clearing with clearingFunction
        result = dllClear(&list, clearInt);
        if (result != 0)
        {
            printf("dllClear: Error clearing list on fifth test\n");
            return -1;
        }
        if (!dllIsEmpty(list))
        {
            printf("dllClear: Error, list is not empty after call fifth test\n");
            return -1;
        }
    }
    printf("Completed dllClear\n");

    printf("Testing dllToHead\n");
    // Test dllToHead
    {
        dllInit(&list);
        int result;

        // Test calling dllToHead on empty list
        result = dllToHead(&iterator, &list);
        if (result == 0)
        {
            printf("dllToHead: Error, incorrect result when called on empty list\n");
            return -1;
        }
        if (iterator.currentNode != NULL)
        {
            printf("dllToHead: Error, currentNode not set to NULL when called on empty list\n");
            return -1;
        }
        if (iterator.list != &list)
        {
            printf("dllToHead: Error, iterator.list not set to the given list\n");
            return -1;
        }

        // Test calling dllToHead on small list
        makeList(&list);
        result = dllToHead(&iterator, &list);
        if (result < 0)
        {
            printf("dllToHead: Error, incorrect result when called on non-empty list\n");
            return -1;
        }
        if (iterator.currentNode != list.head)
        {
            printf("dllToHead: Error, iterator not moved to head node on non-empty list\n");
            return -1;
        }
        if (iterator.list != &list)
        {
            printf("dllToHead: Error, iterator.list not set to the given list on non-empty list\n");
            return -1;
        }

        dllClear(&list, clearInt);
    }
    printf("Completed dllToHead\n");

    printf("Testing dllToTail\n");
    // Test dllToTail
    {
        dllInit(&list);
        int result;

        // Test calling dllToTail on empty list
        result = dllToTail(&iterator, &list);
        if (result == 0)
        {
            printf("dllToTail: Error, incorrect result when called on empty list\n");
            return -1;
        }
        if (iterator.currentNode != NULL)
        {
            printf("dllToTail: Error, currentNode not set to NULL when called on empty list\n");
            return -1;
        }
        if (iterator.list != &list)
        {
            printf("dllToTail: Error, iterator.list not set to the given list\n");
            return -1;
        }

        // Test calling dllToTail on small list
        makeList(&list);
        result = dllToTail(&iterator, &list);
        if (result < 0)
        {
            printf("dllToTail: Error, incorrect result when called on non-empty list\n");
            return -1;
        }
        if (iterator.currentNode != list.tail)
        {
            printf("dllToTail: Error, iterator not moved to tail node on non-empty list\n");
            return -1;
        }
        if (iterator.list != &list)
        {
            printf("dllToTail: Error, iterator.list not set to the given list on non-empty list\n");
            return -1;
        }

        dllClear(&list, clearInt);
    }
    printf("Completed dllToTail\n");

    printf("Testing dllGetThis\n");
    // Test dllGetThis
    {
        dllInit(&list);
        int result;
        void* content;

        // Test on empty list
        dllToHead(&iterator, &list);
        content = (void*) 17;
        result = dllGetThis(&iterator, &content);
        if (result == 0)
        {
            printf("dllGetThis: Error, incorrect result when called on empty list iterator\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllGetThis: Error, content not NULL when called on empty list iterator\n");
            return -1;
        }

        // Test on non empty list
        makeList(&list);
        dllToHead(&iterator, &list);
        content = NULL;
        result = dllGetThis(&iterator, &content);
        if (result != 0)
        {
            printf("dllGetThis: Error, incorrect result when called on non empty list iterator\n");
            return -1;
        }
        if (content == NULL)
        {
            printf("dllGetThis: Error, NULL content when called on non empty list iterator\n");
            return -1;
        }
        if (*(int*) content != 12)
        {
            printf("dllGetThis: Error, incorrect content when called on non empty list iterator\n");
            return -1;
        }

        dllClear(&list, clearInt);
    }
    printf("Completed dllGetThis\n");

    printf("Testing dllGetPrev\n");
    // Test dllGetPrev
    {
        dllInit(&list);
        int result;
        void* content;

        // Test on empty list
        dllToHead(&iterator, &list);
        content = (void*) 23;
        result = dllGetPrev(&iterator, &content);
        if (result == 0)
        {
            printf("dllGetPrev: Error, incorrect result when called on empty list iterator\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllGetPrev: Error, content is not NULL when called on empty list iterator\n");
            return -1;
        }

        // Test on non empty list while at the head
        makeList(&list);
        dllToHead(&iterator, &list);
        content = (void*) 23;
        result = dllGetPrev(&iterator, &content);
        if (result == 0)
        {
            printf("dllGetPrev: Error, incorrect result when called on head of non empty list\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllGetPrev: Error, content is not NULL when called on head of non empty list\n");
            return -1;
        }
        if (iterator.currentNode != list.head)
        {
            printf("dllGetPrev: Error, iterator shifted to new node when called on head of list\n");
            return -1;
        }

        // Test a couple times starting from the tail
        dllToTail(&iterator, &list);
        content = NULL;
        result = dllGetPrev(&iterator, &content);
        if (result != 0)
        {
            printf("dllGetPrev: Error, incorrect result when called on tail of non empty list\n");
            return -1;
        }
        if (content == NULL)
        {
            printf("dllGetPrev: Error, content is NULL when called on tail of non empty list\n");
            return -1;
        }
        if (*(int*) content != 2)
        {
            printf("dllGetPrev: Error, content is incorrect when called on tail of non empty list\n");
            return -1;
        }
        if (iterator.currentNode != list.tail->prev)
        {
            printf("dllGetPrev: Error, iterator did not shift to correct node when called on tail of non empty list\n");
            return -1;
        }

        result = dllGetPrev(&iterator, &content);
        if (result != 0)
        {
            printf("dllGetPrev: Error, incorrect result when called again on non empty list\n");
            return -1;
        }
        if (content == NULL)
        {
            printf("dllGetPrev: Error, content is NULL when called again on non empty list\n");
            return -1;
        }
        if (*(int*) content != 3)
        {
            printf("dllGetPrev: Error, content is incorrect when called again on non empty list\n");
            return -1;
        }
        if (iterator.currentNode != list.tail->prev->prev)
        {
            printf("dllGetPrev: Error, iterator did not shift to correct node when called again on non empty list\n");
            return -1;
        }

        dllClear(&list, clearInt);
    }
    printf("Completed dllGetPrev\n");

    printf("Testing dllGetNext\n");
    // Test dllGetNext
    {
        dllInit(&list);
        int result;
        void* content;

        // Test on empty list
        dllToHead(&iterator, &list);
        content = (void*) 23;
        result = dllGetNext(&iterator, &content);
        if (result == 0)
        {
            printf("dllGetNext: Error, incorrect result when called on empty list iterator\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllGetNext: Error, content is not NULL when called on empty list iterator\n");
            return -1;
        }

        // Test on non empty list while at the tail
        makeList(&list);
        dllToTail(&iterator, &list);
        content = (void*) 23;
        result = dllGetNext(&iterator, &content);
        if (result == 0)
        {
            printf("dllGetNext: Error, incorrect result when called on tail of non empty list\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllGetNext: Error, content is not NULL when called on tail of non empty list\n");
            return -1;
        }
        if (iterator.currentNode != list.tail)
        {
            printf("dllGetNext: Error, iterator shifted to new node when called on tail of list\n");
            return -1;
        }

        // Test a couple times starting from the head
        dllToHead(&iterator, &list);
        content = NULL;
        result = dllGetNext(&iterator, &content);
        if (result != 0)
        {
            printf("dllGetNext: Error, incorrect result when called on head of non empty list\n");
            return -1;
        }
        if (content == NULL)
        {
            printf("dllGetNext: Error, content is NULL when called on head of non empty list\n");
            return -1;
        }
        if (*(int*) content != 11)
        {
            printf("dllGetNext: Error, content is incorrect when called on head of non empty list\n");
            return -1;
        }
        if (iterator.currentNode != list.head->next)
        {
            printf("dllGetNext: Error, iterator did not shift to correct node when called on head of non empty list\n");
            return -1;
        }

        result = dllGetNext(&iterator, &content);
        if (result != 0)
        {
            printf("dllGetNext: Error, incorrect result when called again on non empty list\n");
            return -1;
        }
        if (content == NULL)
        {
            printf("dllGetNext: Error, content is NULL when called again on non empty list\n");
            return -1;
        }
        if (*(int*) content != 10)
        {
            printf("dllGetNext: Error, content is incorrect when called again on non empty list\n");
            return -1;
        }
        if (iterator.currentNode != list.head->next->next)
        {
            printf("dllGetNext: Error, iterator did not shift to correct node when called again on non empty list\n");
            return -1;
        }

        dllClear(&list, clearInt);
    }
    printf("Completed dllGetNext\n");

    printf("Testing dllInsertPrev\n");
    // Test dllInsertPrev
    {
        dllInit(&list);
        void* newInt;
        int result;

        // Test on an empty list
        dllToHead(&iterator, &list);
        newInt = malloc(sizeof(int));
        if (newInt == NULL)
        {
            perror("dllInsertPrev: Unable to allocate space for int on first test");
            return -1;
        }
        *(int*) newInt = 35;
        result = dllInsertPrev(&iterator, &newInt);
        if (result == 0)
        {
            printf("dllInsertPrev: Error, incorrect result when called on empty list\n");
            return -1;
        }
        if (list.head != NULL || list.tail != NULL)
        {
            printf("dllInsertPrev: Error, head and tail of empty list were changed\n");
            return -1;
        }
        free(newInt);

        // Test inserting while iterator is on the head
        makeList(&list);
        dllToHead(&iterator, &list);
        newInt = malloc(sizeof(int));
        if (newInt == NULL)
        {
            perror("dllInsertPrev: Unable to allocate space for int on second test");
            return -1;
        }
        *(int*) newInt = 35;
        result = dllInsertPrev(&iterator, newInt);
        if (result != 0)
        {
            perror("dllInsertPrev: Error, did not insert to left of head");
            return -1;
        }
        if (iterator.currentNode->prev != list.head)
        {
            printf("dllInsertPrev: Error, new node did not get set as new head of list\n");
            return -1;
        }
        if (list.head->next != iterator.currentNode)
        {
            printf("dllInsertPrev: Error, new node did not properly connected to the current node\n");
            return -1;
        }

        // Test inserting between two nodes
        newInt = malloc(sizeof(int));
        if (newInt == NULL)
        {
            perror("dllInsertPrev: Unable to allocate space for int on third test");
            return -1;
        }
        *(int*) newInt = 37;
        result = dllInsertPrev(&iterator, newInt);
        if (result != 0)
        {
            perror("dllInsertPrev: Error, did not insert to left of currentNode on third test");
            return -1;
        }
        if (iterator.currentNode->prev != list.head->next)
        {
            printf("dllInsertPrev: Error, new node did not inserted into the correct spot (1)\n");
            return -1;
        }
        if (list.head->next->next != iterator.currentNode)
        {
            printf("dllInsertPrev: Error, new node did not properly connected to the current node (2)\n");
            return -1;
        }
        if (*(int*) list.head->content != 35)
        {
            printf("dllInsertPrev: Error, content of head node is incorrect\n");
            return -1;
        }
        if (*(int*) list.head->next->content != 37)
        {
            printf("dllInsertPrev: Error, content of next node is incorrect\n");
            return -1;
        }

        dllClear(&list, clearInt);
    }
    printf("Completed dllInsertPrev\n");

    printf("Testing dllInsertNext\n");
    // Test dllInsertNext
    {
        dllInit(&list);
        void* newInt;
        int result;

        // Test on an empty list
        dllToTail(&iterator, &list);
        newInt = malloc(sizeof(int));
        if (newInt == NULL)
        {
            perror("dllInsertNext: Unable to allocate space for int on first test");
            return -1;
        }
        *(int*) newInt = 35;
        result = dllInsertNext(&iterator, &newInt);
        if (result == 0)
        {
            printf("dllInsertNext: Error, incorrect result when called on empty list\n");
            return -1;
        }
        if (list.head != NULL || list.tail != NULL)
        {
            printf("dllInsertNext: Error, head and tail of empty list were changed\n");
            return -1;
        }
        free(newInt);

        // Test inserting while iterator is on the tail
        makeList(&list);
        dllToTail(&iterator, &list);
        newInt = malloc(sizeof(int));
        if (newInt == NULL)
        {
            perror("dllInsertNext: Unable to allocate space for int on second test");
            return -1;
        }
        *(int*) newInt = 35;
        result = dllInsertNext(&iterator, newInt);
        if (result != 0)
        {
            perror("dllInsertNext: Error, did not insert to right of tail");
            return -1;
        }
        if (iterator.currentNode->next != list.tail)
        {
            printf("dllInsertNext: Error, new node did not get set as new tail of list\n");
            return -1;
        }
        if (list.tail->prev != iterator.currentNode)
        {
            printf("dllInsertNext: Error, new node did not properly connected to the current node\n");
            return -1;
        }

        // Test inserting between two nodes
        newInt = malloc(sizeof(int));
        if (newInt == NULL)
        {
            perror("dllInsertNext: Unable to allocate space for int on third test");
            return -1;
        }
        *(int*) newInt = 37;
        result = dllInsertNext(&iterator, newInt);
        if (result != 0)
        {
            perror("dllInsertNext: Error, did not insert to right of currentNode on third test");
            return -1;
        }
        if (iterator.currentNode->next != list.tail->prev)
        {
            printf("dllInsertNext: Error, new node did not inserted into the correct spot (1)\n");
            return -1;
        }
        if (list.tail->prev->prev != iterator.currentNode)
        {
            printf("dllInsertNext: Error, new node did not properly connected to the current node (2)\n");
            return -1;
        }
        if (*(int*) list.tail->content != 35)
        {
            printf("dllInsertNext: Error, content of tail node is incorrect\n");
            return -1;
        }
        if (*(int*) list.tail->prev->content != 37)
        {
            printf("dllInsertNext: Error, content of prev node is incorrect\n");
            return -1;
        }

        dllClear(&list, clearInt);
    }
    printf("Completed dllInsertNext\n");

    printf("Tests complete\n");
    return 0;
}

void makeList(DLL* list)
{
    dllInit(list);

    for (int i=1; i<13; i++)
    {
        void* content = malloc(sizeof(int));
        if (content == NULL)
        {
            perror("makeList Unable to allocate space for new integer");
            exit(-1);
        }
        *(int*) content = i;
        if (dllPush(list, content) < 0)
        {
            perror("makeList unable to push on new node");
            exit(-1);
        }
    }
}

int clearInt(void* number)
{
    free(number);

    return 0;
}