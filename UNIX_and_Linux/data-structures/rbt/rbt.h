#ifndef RBT_H
#define RBT_H

typedef struct RBTNode_struct {

    char isRed; // zero if black, non-zero if red

    struct RBTNode_struct* parent;
    struct RBTNode_struct* left;
    struct RBTNode_struct* right;

    void* content;

} RBTNode;

typedef struct {

    RBTNode* head;

} RBT;

/***************************************************************
 * rbtNewNode
 * 
 * Inputs: void* content
 * Returns: RBTNode*
 * 
 * Creates a new empty RBTNode. This node is set to black (isRed = 0)
 * and sets parent, left, and right to NULL. Set's the new node's
 * content equal to the pointer passed in content
 * 
 * Failure returns NULL and sets errno, success returns a pointer
 * to a new RBTNode
 ***************************************************************/

RBTNode* rbtNewNode(void* content);

/***************************************************************
 * rbtNewTree
 * 
 * Inputs: None
 * Returns: RBT*
 * 
 * Creates a new empty RBT. head is initially set to NULL
 * 
 * Failure returns NULL and sets errno, success returns a pointer
 * to a new RBT
 ***************************************************************/

RBT* rbtNewTree(void);

/***************************************************************
 * rbtIsEmpty
 * 
 * Inputs: None
 * Returns: RBT*
 * 
 * Creates a new empty RBT. head is initially set to NULL
 * 
 * Failure returns NULL and sets errno, success returns a pointer
 * to a new RBT
 ***************************************************************/

#endif /* RBT_H */