#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/cooltools.h"
#include "rbt.h"
#include "rbtprint.h"

int compareInt(void* a, void* b);
int testitoa(char* buffer, void* content);

int main()
{
    RBT tree;
    rbtInit(&tree, compareInt);

    char inBuffer[13];
    while (1)
    {
        bzero(inBuffer, 13);
        
        printf("Enter a number: ");
        if (fgets(inBuffer, 13, stdin) != NULL)
        {
            int i = atoi(inBuffer);
            printf("Entered %i\n", i);

            void* newContent = malloc(sizeof(int));
            if (newContent == NULL)
            {
                perror("Unable to allocate space for new int");
                return -1;
            }
            *(int*) newContent = i;

            RBTStatusStruct result = rbtInsert(&tree, newContent);

            rbtPrint(tree, testitoa);
        }
    }

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

int testitoa(char* buffer, void* content)
{
    itoa(buffer, *(int32_t*) content);
    
    return strlen(buffer);
}