#ifndef RBTIMPL_H
#define RBTIMPL_h

/*****************************************
 * Implementation only declarations for
 * rbt API
 *
 * NOT TO BE INCLUDED OUTSIDE OF rbt.c
 * OR rbtest.c
 *****************************************/

#include "rbt.h"

RBTStatusStruct rbtGetNodeFromStart__(RBTNode* start, void* query, int (*compareFunction) (void* a, void* b));

#endif /* RBTIMPL_H */