#ifndef RBT_H
#define RBT_H

typedef enum {

    SUCCESS,
    NO_MEMORY,
    NULL_CONTENT,
    EMPTY_NODE_ENCOUNTERED,
    NOT_FOUND

} RBTStatus;

typedef struct RBTNode_struct {

    char isRed; // zero if black, non-zero if red

    struct RBTNode_struct* parent;
    struct RBTNode_struct* left;
    struct RBTNode_struct* right;

    void* content;

} RBTNode;

typedef struct {

    RBTNode* head;
    int (*compareFunction) (void*, void*);

} RBT;

typedef struct {

    RBTStatus status;
    RBTNode* node;

} RBTStatusStruct;

/***************************************************************
 * rbtStatusText
 * 
 * Inputs: RBTStatus status
 * Returns: const char*
 * 
 * Returns a string representation of the given RBTStatus
 ***************************************************************/
const char* rbtStatusText(RBTStatus status);

/***************************************************************
 * rbtInit
 * 
 * Inputs: RBT* tree, int (*compareFunction) (void* a, void* b)
 * Returns: None
 * 
 * Initializes the values of the given RBT as a new empty RBT,
 * with the given compareFunction
 * 
 * If an existing RBT is passed to this fuction that has data in
 * it, the data will be lost to a memory leak, as this function
 * does not clear out an already existing tree.
 * 
 * The compareFunction is used by the tree to compare the content
 * of two different nodes on insertions, deletions, and searches.
 * Several methods in this API use the tree's compareFunction.
 * 
 * compareFunction must behave in the following way:
 *     -If object a is less than object b, return a negative int
 *     -If object a is greater than b, return a positive int
 *     -If objects a and b are equal, return 0
 * 
 * If the compareFunction does not behave this way, the behavior
 * of the entire RBT will be undefined, and likely very very wrong.
 ***************************************************************/
void rbtInit(RBT* tree, int (*compareFunction) (void* a, void* b));

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
 * Creates a new RBTNode. This node is set to red (isRed = 1)
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
 * rbtIsRed
 * 
 * Inputs: RBTNode node
 * Returns: int
 * 
 * Returns 1 if the given RBTNode is red, otherwise
 * returns 0
 ***************************************************************/
int rbtIsRed(RBTNode node);

/***************************************************************
 * rbtSetRed
 * 
 * Inputs: RBTNode* node
 * Returns: None
 * 
 * Sets the given RBTNode to red
 ***************************************************************/
void rbtSetRed(RBTNode* node);

/***************************************************************
 * rbtSetBlack
 * 
 * Inputs: RBTNode* node
 * Returns: None
 * 
 * Sets the given RBTNode to black
 ***************************************************************/
void rbtSetBlack(RBTNode* node);

// Helper functions
RBTStatusStruct rbtGetNodeFromStartingNode(RBTNode* start, void* query, int (*compareFunction) (void* a, void* b));

#endif /* RBT_H */
