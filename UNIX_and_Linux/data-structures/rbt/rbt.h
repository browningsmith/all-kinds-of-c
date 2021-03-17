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
 * rbtInit
 * 
 * Inputs: None
 * Returns: None
 * 
 * Initializes the values of the given RBT as a new empty RBT
 * 
 * If an existing RBT is passed to this fuction that has data in
 * it, the data will be lost to a memory leak, as this function
 * does not clear out an already existing tree.
 * 
 * Passing a pointer to anything other than an RBT results in
 * undefined behavior
 ***************************************************************/

void rbtInit(RBT* tree);

/***************************************************************
 * rbtIsTreeEmpty
 * 
 * Inputs: RBT tree
 * Returns: int
 * 
 * Returns 1 if the head of the given tree is NULL, otherwise
 * returns 0
 ***************************************************************/

int rbtIsTreeEmpty(RBT tree);

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

#endif /* RBT_H */