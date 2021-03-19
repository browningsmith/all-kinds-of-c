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
 * Creates a new RBTNode. This node is set to black (isRed = 0)
 * and sets parent, left, and right to NULL. Set's the new node's
 * content equal to the pointer passed in content
 * 
 * Failure returns NULL and sets errno, success returns a pointer
 * to a new RBTNode
 ***************************************************************/
RBTNode* rbtNewNode(void* content);

/***************************************************************
 * rbtIsNodeEmpty
 * 
 * Inputs: RBTNode node
 * Returns: int
 * 
 * Returns 1 if the content of the given node is NULL, otherwise
 * returns 0
 ***************************************************************/
int rbtIsNodeEmpty(RBTNode node);

/***************************************************************
 * rbtCompare
 * 
 * Inputs: RBTNode a, RBTNode b, int (*compareFunction) (void*, void*)
 * Returns: int
 * 
 * Compares the content of two nodes using given compareFunction
 * 
 * rbtCompare passes the content of node a to the first argument of
 * compareFunction, and the content of node b to the second
 * argument of compareFunction
 * 
 * Returns the result of executing compareFunction on these values
 * 
 * If either node's content is empty, behavior is undefined
 * 
 * compareFunction must behave in the following way:
 *     -if the object in the first argument is less than the
 *      object in the second argument, a negative int must be returned
 *     -if the object in the first argument is greater than the
 *      object in the second argument, a positive int must be returned
 *     -if the objects are equivalent, a 0 must be returned
 * 
 * If the given compareFunction does not behave this way, the operation
 * of the entire RBT will be undefined, and likely very very wrong
 * 
 ***************************************************************/
int rbtCompare(RBTNode a, RBTNode b, int (*compareFunction) (void*, void*));

#endif /* RBT_H */