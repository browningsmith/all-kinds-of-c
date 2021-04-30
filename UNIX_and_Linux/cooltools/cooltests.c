#define _DEFAULT_SOURCE

#include "cooltools.h"

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int main()
{
    printf("Running tests on cooltools\n");
    
    // Test itoa
    printf("Testing itoa\n");
    {
        // Test calling itoa with a NULL value
        if (itoa(NULL, 72) != NULL)
        {
            printf("itoa: Error, did not return NULL when passed a NULL value\n");
            return -1;
        }

        char itoabuff[12];
        char sprintfbuff[12];
        // Test from -1000000 to 1000000 (passes through the zero edge case)
        for (int32_t i = -1000000; i <= 1000000; i++)
        {
            itoa(itoabuff, i);
            sprintf(sprintfbuff, "%i", i);
            if (strcmp(itoabuff, sprintfbuff) != 0)
            {
                printf("itoa: Error, itoa output did not match sprintf output on %i\n", i);
                printf("itoa: itoa: %s vs. sprintf: %s\n", itoabuff, sprintfbuff);
                return -1;
            }
        }

        // Test from 2146483648 to -2146483648 (passes through overflow edge case)
        {
            int32_t j = 2146483648;
            for (int32_t i = -1000000; i <= 1000000; i++)
            {
                itoa(itoabuff, j);
                sprintf(sprintfbuff, "%i", j);
                if (strcmp(itoabuff, sprintfbuff) != 0)
                {
                    printf("itoa: Error, itoa output did not match sprintf output on %i\n", j);
                    printf("itoa: itoa: %s vs. sprintf: %s\n", itoabuff, sprintfbuff);
                    return -1;
                }

                j++;
            }
        }
        
        // Speed tests
        printf("sprintf vs. itoa:\ntimed over 2,000,000 large integers per test\n");
        for (int i = 0; i < 10; i++)
        {
            struct timeval sprintftime;
            struct timeval itoatime;
            struct timeval start;
            struct timeval end;
            char buffer[12];

            gettimeofday(&start, NULL);
            int32_t j = 2146483648;
            for (int k = -1000000; k <= 1000000; k++)
            {
                sprintf(buffer, "%i", j);
                j++;
            }
            gettimeofday(&end, NULL);
            timersub(&end, &start, &sprintftime);

            gettimeofday(&start, NULL);
            j = 2146483648;
            for (int k = -1000000; k <= 1000000; k++)
            {
                itoa(buffer, j);
                j++;
            }
            gettimeofday(&end, NULL);
            timersub(&end, &start, &itoatime);

            printf("%lis %lius vs. %lis %lius\n", sprintftime.tv_sec, sprintftime.tv_usec, itoatime.tv_sec, itoatime.tv_usec);
        }
    }
    printf("Completed itoa\n");

    printf("Tests complete\n");

    return 0;
}
