#include <stdio.h>
#include <stdlib.h>

#include "doublell.h"
#include "doublellimpl.h"

void makeList(DLL* list);
int clearInt(void* number);

int main(int argc, char** argv)
{
    printf("Running tests on doublell\n");

    DLL list;
    DLLIterator iterator;

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
        makeList(&list);
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
            printf("dllClear: Error clearing list with no clearing function specified\n");
            return -1;
        }
        if (!dllIsEmpty(list))
        {
            printf("dllClear: Error, list is not empty after call with no specified clearingFunction\n");
            return -1;
        }

        // Test attempting to clear a broken list
        makeList(&list);
        DLLNode* leftBehindNode = list.head->next->next->next; // Should be node 9
        DLLNode* nextNode = leftBehindNode->next; // Should be node 8
        list.head->next->next->next->next = NULL; // Node 9 should be left behind without content
        result = dllClear(&list, clearInt);
        if (result == 0)
        {
            printf("dllClear: Error clearing broken list\n");
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
        makeList(&list);
        result = dllClear(&list, clearInt);
        if (result != 0)
        {
            printf("dllClear: Error clearing list with no clearing function specified on fifth test\n");
            return -1;
        }
        if (!dllIsEmpty(list))
        {
            printf("dllClear: Error, list is not empty after call with no specified clearingFunction on fifth test\n");
            return -1;
        }
    }

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