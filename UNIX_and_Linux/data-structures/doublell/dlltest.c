#include <stdio.h>

#include "doublell.h"

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

    

    printf("Tests complete\n");
    return 0;
}