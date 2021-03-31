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

    printf("Tests complete\n");
    return 0;
}