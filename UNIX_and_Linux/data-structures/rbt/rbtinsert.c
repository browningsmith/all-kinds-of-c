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

    rbtPrint(tree, testitoa);

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