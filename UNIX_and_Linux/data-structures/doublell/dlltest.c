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

        list.start = &testNode;
        list.end = &testNode;

        if (list.start == NULL)
        {
            printf("dllInit: Error, list.start is NULL before dllInit\n");
            return -1;
        }
        if (list.end == NULL)
        {
            printf("dllInit: Error, list.end is NULL before dllInit\n");
            return -1;
        }

        dllInit(&list);

        if (list.start != NULL)
        {
            printf("dllInit: Error, list.start is not NULL after dllInit\n");
            return -1;
        }
        if (list.end != NULL)
        {
            printf("dllInit: Error, list.end is not NULL after dllInit\n");
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
            printf("dllIsEmpty: Error, list is not returning as empty\n");
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
        if (list.start == NULL)
        {
            printf("dllPush: Error, start of list is still NULL\n");
            return -1;
        }
        if (list.end == NULL)
        {
            printf("dllPush: Error, end of list is still NULL\n");
            return -1;
        }
        if (list.start != list.end)
        {
            printf("dllPush: Error, start and end of list are not the same after insert to empty list\n");
            return -1;
        }
        if (*(int*) list.start->content != 5)
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
        if (list.start == NULL)
        {
            printf("dllPush: Error, start of list is NULL after second node inserted\n");
            return -1;
        }
        if (list.start->next == NULL)
        {
            printf("dllPush: Error, next node is NULL after second insert\n");
            return -1;
        }
        if (list.start->next->prev == NULL)
        {
            printf("dllPush: Error, prev node of next is NULL after second insert\n");
            return -1;
        }
        if (list.start != list.start->next->prev)
        {
            printf("dllPush: Error, prev and next node do not point to each other\n");
            return -1;
        }
        if (list.end == NULL)
        {
            printf("dllPush: Error, end of list no longer attached after second insert\n");
            return -1;
        }
        if (list.start->next != list.end)
        {
            printf("dllPush: Error, next node in a list of only two is not also the end\n");
            return -1;
        }
        if (*(int*) list.start->content != 12)
        {
            printf("dllPush: Error, content is incorrect after second insert\n");
            return -1;
        }

        free(list.start->next);
        free(list.start);
    }

    // Test dllPushBack
    {
        dllInit(&list);

        // Test pushing onto empty list
        int num1 = 5;
        if (dllPushBack(&list, (void*) &num1) < 0)
        {
            perror("dllPushBack: Unable to create space for node");
            return -1;
        }
        if (list.start == NULL)
        {
            printf("dllPushBack: Error, start of list is still NULL\n");
            return -1;
        }
        if (list.end == NULL)
        {
            printf("dllPushBack: Error, end of list is still NULL\n");
            return -1;
        }
        if (list.start != list.end)
        {
            printf("dllPushBack: Error, start and end of list are not the same after insert to empty list\n");
            return -1;
        }
        if (*(int*) list.start->content != 5)
        {
            printf("dllPushBack: Error, content of first inserted node is incorrect\n");
            return -1;
        }

        // Test pushing onto non empty list
        int num2 = 12;
        if (dllPushBack(&list, (void*) &num2) < 0)
        {
            perror("dllPushBack: Unable to create space for second node");
            return -1;
        }
        if (list.start == NULL)
        {
            printf("dllPushBack: Error, start of list is NULL after second node inserted\n");
            return -1;
        }
        if (list.start->next == NULL)
        {
            printf("dllPushBack: Error, next node is NULL after second insert\n");
            return -1;
        }
        if (list.start->next->prev == NULL)
        {
            printf("dllPushBack: Error, prev node of next is NULL after second insert\n");
            return -1;
        }
        if (list.start != list.start->next->prev)
        {
            printf("dllPushBack: Error, prev and next node do not point to each other\n");
            return -1;
        }
        if (list.end == NULL)
        {
            printf("dllPushBack: Error, end of list no longer attached after second insert\n");
            return -1;
        }
        if (list.start->next != list.end)
        {
            printf("dllPushBack: Error, next node in a list of only two is not also the end\n");
            return -1;
        }
        if (*(int*) list.end->content != 12)
        {
            printf("dllPushBack: Error, content is incorrect after second insert\n");
            return -1;
        }

        free(list.start->next);
        free(list.start);
    }

    printf("Tests complete\n");
    return 0;
}