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

PLine* rbtNewPLine__(void);
int rbtDeletePLine__(void* line);

#endif /* RBTPRINTIMPL_H */