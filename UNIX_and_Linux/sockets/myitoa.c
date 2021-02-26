#include "myitoa.h"

#include <stdint.h>
#include <stdio.h>

char* myitoa(char* buffer, uint16_t i)
{
    uint16_t place = 1000;
    
    for (int index = 0; index < 4; index++)
    {
        buffer[index] = (char) (i / place + 48);
        i = i % place;
        place /= 10;
    }

    return buffer;
}