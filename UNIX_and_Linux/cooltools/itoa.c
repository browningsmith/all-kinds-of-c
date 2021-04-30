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
    int isNeg = 0;
    if (num < 0)
    {
        // check if num is lowest possible negative 32 bit integer
	if (num == -2147483648)
	{
	    buf[0] = '-';
	    buf[1] = '2';
	    buf[2] = '1';
	    buf[3] = '4';
	    buf[4] = '7';
	    buf[5] = '4';
	    buf[6] = '8';
	    buf[7] = '3';
	    buf[8] = '6';
	    buf[9] = '4';
	    buf[10] = '8';
	    buf[11] = 0;
	    return buf;
        }

	buf[0] = '-';
	num *= -1;
	isNeg = 1;
    }

    char revBuf[10];
    int index = 0;

    while (num > 0)
    {
        revBuf[index] = (char) ((num % 10) + 48);
	num = num / 10;
	index++;
    }

    int revIndex = index - 1;
    index = isNeg;

    for ( ; revIndex > -1; revIndex--)
    {
        buf[index] = revBuf[revIndex];
	index++;
    }

    buf[index] = 0;

    return buf;
}
