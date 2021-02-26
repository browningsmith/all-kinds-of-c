#include "lg.h"

#include <stdio.h>

int lg_init(void)
{
    lg_init_tried_ = 1;
    lg_init_success_ = 1;

    return 0;
}

void lg(const char* string)
{
    if (lg_init_success_)
    {
        printf("%s", string);
    }
    else
    {
        printf("Unable to log\n");
    }
}
