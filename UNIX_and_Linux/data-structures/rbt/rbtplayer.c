#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "include/cooltools.h"
#include "rbt.h"
#include "rbtprint.h"

int compareInt(void* a, void* b);
int testitoa(char* buffer, void* content);
char decodeCommand(char* buffer);

int main()
{
    RBT tree;
    rbtInit(&tree, compareInt);

    char inBuffer[13];

    while (1)
    {
        bzero(inBuffer, 13);
        char command = 'x';
        
        printf("Enter a command (f = find, i = insert, d = delete): ");
        if (fgets(inBuffer, 13, stdin) != NULL)
        {
            command = decodeCommand(inBuffer);
            switch (command)
            {
                case 'f':
                    printf("You chose to find!\n");

                    printf("Enter a number to find: ");
                    if (fgets(inBuffer, 13, stdin) != NULL)
                    {
                        int i = atoi(inBuffer);
                        printf("Finding %i\n", i);
                        rbtPrint(tree, testitoa);

                        void* returnedContent;
                        RBTStatus result = rbtFind(tree, (void*) &i, &returnedContent);
                        if (result == SUCCESS)
                        {
                            printf("%i was found!\n", *(int*) returnedContent);
                        }
                        else if (result == NOT_FOUND)
                        {
                            printf("%i was not found\n", i);
                        }
                        else
                        {
                            printf("rbtFind returned with %s\n", rbtStatusAsText(result));
                            perror("");
                        }
                    }

                    break;
                case 'i':
                    printf("You chose to insert!\n");

                    printf("Enter a number to insert: ");
                    if (fgets(inBuffer, 13, stdin) != NULL)
                    {
                        int i = atoi(inBuffer);
                        printf("Inserting %i\n", i);

                        void* newContent = malloc(sizeof(int));
                        if (newContent == NULL)
                        {
                            perror("Unable to allocate space for new int");
                            return -1;
                        }
                        *(int*) newContent = i;

                        RBTStatusStruct result = rbtInsert(&tree, newContent);
                        if (result.status != SUCCESS)
                        {
                            printf("rbtInsert returned with %s\n", rbtStatusAsText(result.status));
                            perror("");
                        }

                        rbtPrint(tree, testitoa);
                    }

                    break;
                case 'd':

                    printf("You chose to delete!\n");

                    printf("Enter a number to delete: ");
                    if (fgets(inBuffer, 13, stdin) != NULL)
                    {
                        int i = atoi(inBuffer);
                        printf("Deleting %i\n", i);

                        void* returnedContent;
                        RBTStatusStruct result = rbtDelete(&tree, (void*) &i, &returnedContent);
                        rbtPrint(tree, testitoa);
                        if (result.status == SUCCESS)
                        {
                            printf("%i was deleted!\n", *(int*) returnedContent);
                            free(returnedContent);
                        }
                        else if (result.status == NOT_FOUND)
                        {
                            printf("%i was not found\n", i);
                        }
                        else
                        {
                            printf("rbtDelete returned with %s\n", rbtStatusAsText(result.status));
                            perror("");
                        }
                    }

                    break;
                default:
                    printf("Invalid command!\n");
                    break;
            }
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

char decodeCommand(char* buffer)
{
    for (int i=0; i<13; i++)
    {
        switch (buffer[i])
        {
            case 'f':
                return 'f';
            case 'i':
                return 'i';
            case 'd':
                return 'd';
            default:
                break;
        }
    }

    return 'x';
}