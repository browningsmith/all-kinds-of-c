#include <stdio.h>
#include <stdlib.h>

#include "doublell.h"
#include "doublellimpl.h"

int main(int argc, char** argv)
{
    printf("Running tests on doublell\n");

    DLL list;

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

    // Test dllNewNode__
    {
        int testInt = 12;

        DLLNode* testNode = dllNewNode__((void*) &testInt);
        if (testNode == NULL)
        {
            perror("dllNewNode__: error creating new node");
            return -1;
        }

        if (testNode->prev != NULL)
        {
            printf("dllNewNode__: test node's prev is not NULL\n");
            return -1;
        }
        if (testNode->next != NULL)
        {
            printf("dllNewNode__: test node's next is not NULL\n");
            return -1;
        }
        if (testNode->content == NULL)
        {
            printf("dllNewNode__: test node's content is NULL\n");
            return -1;
        }
        if (*(int*) testNode->content != 12)
        {
            printf("dllNewNode__: content improperly stored\n");
            return -1;
        }

        free(testNode);
    }

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

        free(list.head->next);
        free(list.head);
    }

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

        free(list.head->next);
        free(list.head);
    }

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

    // Test dllGet
    {
        dllInit(&list);
        void* content = (void*) 17;

        // Test calling dllGet on an empty list
        int result = dllGet(list, &content);
        if (result != -1)
        {
            printf("dllGet: Error, returned success when called on empty list\n");
            return -1;
        }
        if (content != NULL)
        {
            printf("dllGet: Error, did not return NULL content when called on empty list\n");
            return -1;
        }

        // Test calling dllGet on non empty list
        int num1 = 17;
        if (dllPush(&list, (void*) &num1) < 0)
        {
            perror("dllGet: Error adding node to list\n");
            return -1;
        }
        content = NULL;
        result = dllGet(list, &content);
        if (result != 0)
        {
            printf("dllGet: Error, did not return with success\n");
            return -1;
        }
        if (*(int*) content != 17)
        {
            printf("dllGet: Error, did not return with proper content\n");
            return -1;
        }

        dllDeleteNode__(list.head);
    }

    // Test dllGetTail
    {
        dllInit(&list);
        void* content = (void*) 17;

        // Test calling dllGet on an empty list
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

    printf("Tests complete\n");
    return 0;
}