#include "lg.h"

#include <stdio.h>

int main()
{
    lg_open();

    if (lg_exists())
    {
        printf("Log exists!\n");
    }
    else
    {
        printf("Log does not exist\n");
    }

    return 0;
}
