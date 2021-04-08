#include "cooltools.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

char* itoa(char* buf, int32_t num)
{
    if (buf == NULL)
    {
        return buf;
    }

    // check if zero
    if (num == 0)
    {
        buf[0] = '0';
	buf[1] = 0;
	return buf;
    }

    // check if negative
    int isNegative = 0;
    if (num < 0)
    {
        buf[0] = '-';
	num *= -1;
	isNegative = 1;
    }

    char reverseBuf[10];
    int index = 0;

    while (num > 0)
    {
        reverseBuf[index] = (char) ((num % 10) + 48);
	num = num / 10;
	index++;
    }

    int size = isNegative + size;



    return buf;
}
