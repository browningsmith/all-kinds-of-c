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
 * rbtStatusAsText
 * 
 * Inputs: RBTStatus status
 * Returns: const char*
 * 
 * Returns a string representation of the given RBTStatus
 ***************************************************************/
const char* rbtStatusAsText(RBTStatus status);

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
int rbtIsEmpty(RBT tree);

/***************************************************************
 * rbtFind
 * 
 * Inputs: RBT tree, void* query, void** returnedContent
 * Returns: RBTStatus
 * 
 * Searches for a node within tree based on the given query object
 * 
 * If the search is successful, returns SUCCESS. Also sets
 * returnedContent equal to the content of the found node
 * 
 * If the search fails due to the node not being found, returns
 * NOT_FOUND. Does not alter returnedContent
 * 
 * If the search fails due to an empty node being encountered in
 * the tree, returns EMPTY_NODE_ENCOUNTERED. Does not alter
 * returnedContent
 * 
 * If the user attempts to search using a query that is NULL,
 * returns NULL_CONTENT, and result.node. Does not alter
 * returnedContent
 ***************************************************************/
RBTStatus rbtFind(RBT tree, void* query, void** returnedContent);

/***************************************************************
 * rbtInsert
 * 
 * Inputs: RBT* tree, void* content
 * Returns: RBTStatusStruct result
 * 
 * Attempts to insert a new node with the provided content into
 * the given RBT* tree
 * 
 * If the new node is successfully inserted, method returns
 * with result.status as SUCCESS, and result.node equal to
 * the newly created node.
 * 
 * If the caller attempts to provide content that is NULL, the
 * method returns with result.status as NULL_CONTENT, and
 * result.node as NULL
 * 
 * If the method is unable to create the new node before inserting
 * returns with result.status as NO_MEMORY and result.node as NULL
 * 
 * If the method encounters an empty node, it does not insert a
 * new node, instead returns result.status as EMPTY_NODE_ENCOUNTERED
 * and result.node as NULL
 ***************************************************************/
RBTStatusStruct rbtInsert(RBT* tree, void* content);

/***************************************************************
 * rbtDelete
 * 
 * Inputs: RBT* tree, void* query, void** returnedContent
 * Returns: RBTStatusStruct result
 * 
 * Searches for a node within tree based on the given query object,
 * and if it exists removes it from the tree
 * 
 * If the deletion is successful, returns RBTStatusStruct with a
 * status of SUCCESS, result.node set to NULL.
 * Also sets returnedContent equal to the content of the deleted node
 * 
 * If the search fails due to the node not being found, returns
 * result with result.status being NOT_FOUND, and result.node being
 * equal to the last node searched, or NULL if the tree is empty
 * Does not alter returnedContent or delete any nodes
 * 
 * If the search fails due to an empty node being encountered in
 * the tree, returns result with result.status being
 * EMPTY_NODE_ENCOUNTERED, and result.node being set to the node
 * which caused the problem. Does not alter returnedContent or
 * delete any nodes
 * 
 * If the user attempts to search using a query that is NULL, returns
 * result with result.status being NULL_CONTENT, and result.node
 * being set to NULL. Does not alter returnedContent or delete
 * any nodes
 ***************************************************************/
RBTStatusStruct rbtDelete(RBT* tree, void* query, void** returnedContent);

/***************************************************************
 * rbtClear
 * 
 * Inputs: RBT* tree, int (*clearingFunction) (void*)
 * Returns: int
 * 
 * This function attempts to erase each node and the content of
 * each node within the given tree. It erases the content of
 * the node using the given clearingFunction
 * 
 * Returns 0 on success, and sets the head of the tree to NULL
 * 
 * Returns -1 on failure to delete all nodes. Failure is caused
 * if the given clearingFunction returns a nonzero result, meaning
 * it could not clear the content of one or more nodes. If that is
 * the ncase, tree will now contain all nodes that could not be
 * deleted
 * 
 * Returns -2 if the function was unable to delete the content
 * of all nodes, and at the same time was not able to fully
 * reconstruct the tree containing all non deleted nodes.
 * 
 * clearingFunction must behave in the following way:
 *   -return 0 if content is cleared successfully
 *   -return nonzero if content is not cleared successfully
 ***************************************************************/
int rbtClear(RBT* tree, int (*clearingFunction) (void*));

#endif /* RBT_H */
