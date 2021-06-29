#ifndef RBTIMPL_H
#define RBTIMPL_H

/*****************************************
 * Implementation only declarations for
 * rbt API
 *
 * NOT TO BE INCLUDED OUTSIDE OF rbt.c
 * OR rbtest.c
 *****************************************/

#include "rbt.h"

typedef struct {

    RBTStatus status;
    RBTNode* node;

} RBTStatusStruct;

RBTStatusStruct rbtGetNodeFromStart__(RBTNode* start, void* query, int (*compareFunction) (void* a, void* b));

void rbtRotateRight__(RBT* tree, RBTNode* leftChild);

void rbtRotateLeft__(RBT* tree, RBTNode* rightChild);

void rbtFixRedViolations__(RBT* tree, RBTNode* node);

void rbtFixBlackViolations__(RBT* tree, RBTNode* node);

RBTNode* rbtGetPrev__(RBTNode* node);

RBTNode* rbtGetNext__(RBTNode* node);

#endif /* RBTIMPL_H */