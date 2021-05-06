#ifndef RBTPRINTIMPL_H
#define RBTPRINTIMPL_H

/*****************************************
 * Implementation only declarations for
 * rbtprint API
 *
 * NOT TO BE INCLUDED OUTSIDE OF rbtprint.c
 * OR rbtestprint.c
 *****************************************/

#include "rbtprint.h"

typedef struct {

	size_t capacity;
	size_t cursor;
	char* text;
	
} PLine;

PLine* rbtNewPLine__(void);
int rbtDeletePLine__(void* line); // void* instead of PLine* to be compatible with dllClear
int rbtPLineIncreaseCapacity__(PLine* line);
int rbtPLineAdvanceCursor__(PLine* line, size_t amount);

#endif /* RBTPRINTIMPL_H */