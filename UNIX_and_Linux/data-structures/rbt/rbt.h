#ifndef RBT_H
#define RBT_H

typedef struct RBTNode_struct {

    short isRed; // zero if black, non-zero if red

    struct RBTNode_struct* parent;
    struct RBTNode_struct* left;
    struct RBTNode_struct* right;

    void* content;

} RBTNode;

#endif /* RBT_H */