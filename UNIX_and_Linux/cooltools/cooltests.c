#include "cooltools.h"

#include <stdint.h>
#include <stdio.h>

int main()
{
    char buffer[12];
    printf("Can we print 45? %s\n", itoa(buffer, 45));
    printf("Can we print the min possible int? %s\n", itoa(buffer, -2147483648));

    return 0;
}
