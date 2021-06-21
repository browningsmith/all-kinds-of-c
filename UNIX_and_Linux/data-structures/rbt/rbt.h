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

    RBTNode* root;
    int (*compareFunction) (void*, void*);

} RBT;

typedef struct {

    RBT* tree;
    RBTNode* node;

} RBTIterator;

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
 * Returns 1 if the root of the given tree is NULL, otherwise
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
 * If the search is successful, returns SUCCESS. Also places the
 * content of the found node into returnedContent
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
 * Returns: RBTStatus
 * 
 * Attempts to insert a new node with the provided content into
 * the given RBT* tree
 * 
 * If the new node is successfully inserted, method returns
 * SUCCESS
 * 
 * If the caller attempts to provide content that is NULL, the
 * method returns with NULL_CONTENT
 * 
 * If the method is unable to create the new node before inserting
 * returns with NO_MEMORY
 * 
 * If the method encounters an empty node, it does not insert a
 * new node, instead returns EMPTY_NODE_ENCOUNTERED
 ***************************************************************/
RBTStatus rbtInsert(RBT* tree, void* content);

/***************************************************************
 * rbtDelete
 * 
 * Inputs: RBT* tree, void* query, void** returnedContent
 * Returns: RBTStatus result
 * 
 * Searches for a node within tree based on the given query object,
 * and if it exists removes it from the tree
 * 
 * If the deletion is successful, returns with a status of SUCCESS
 * Also places the content of the deleted node into returnedContent
 * 
 * If the search fails due to the node not being found, returns
 * NOT_FOUND. Does not alter returnedContent or delete any nodes
 * 
 * If the search fails due to an empty node being encountered in
 * the tree, returns EMPTY_NODE_ENCOUNTERED Does not alter
 * returnedContent or delete any nodes
 * 
 * If the user attempts to search using a query that is NULL, returns
 * NULL_CONTENT. Does not alter returnedContent or deleteany nodes
 ***************************************************************/
RBTStatus rbtDelete(RBT* tree, void* query, void** returnedContent);

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
 * Returns 0 on success, and sets the root of the tree to NULL
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

/*****************************************************************
 * IMPORTANT
 *
 * RBTIterator methods
 *
 * All above methods affect elements on an RBT without considering
 * that an RBTIterator may exist attached to the tree. If not
 * careful, it is possible to remove a node that the RBTiterator
 * is currently attached to.
 *
 * If an existing RBTIterator is used after one or more of the
 * above methods are called, rbtToStart, rbtToEnd or rbtToRoot
 * should be called to place the iterator back onto a valid node
 * of the tree
 *****************************************************************/

/***************************************************************
 * rbtToRoot
 * 
 * Inputs: RBTIterator* iterator, RBT* tree
 * Returns: int
 * 
 * This method moves the given RBTIterator on to the root of the
 * given tree. Can also be used to attach a newly created
 * RBTIterator to the root of a tree
 * 
 * Returns 0 on success
 * 
 * Returns -1 on failure, meaning the provided tree is empty,
 * and does not associate the iterator with that tree
 ***************************************************************/
int rbtToRoot(RBTIterator* iterator, RBT* tree);

/***************************************************************
 * rbtToStart
 * 
 * Inputs: RBTIterator* iterator, RBT* tree
 * Returns: int
 * 
 * This method moves the given RBTIterator on to the start of the
 * given tree, meaning the lowest comparable value stored in the
 * tree currently. Can also be used to attach a newly created
 * RBTIterator to the start of a tree
 * 
 * Returns 0 on success
 * 
 * Returns -1 on failure, meaning the provided tree is empty,
 * and does not associate the iterator with that tree
 ***************************************************************/
int rbtToStart(RBTIterator* iterator, RBT* tree);

/***************************************************************
 * rbtToEnd
 * 
 * Inputs: RBTIterator* iterator, RBT* tree
 * Returns: int
 * 
 * This method moves the given RBTIterator on to the end of the
 * given tree, meaning the highest comparable value stored in the
 * tree currently. Can also be used to attach a newly created
 * RBTIterator to the end of a tree
 * 
 * Returns 0 on success
 * 
 * Returns -1 on failure, meaning the provided tree is empty,
 * and does not associate the iterator with that tree
 ***************************************************************/
int rbtToEnd(RBTIterator* iterator, RBT* tree);

#endif /* RBT_H */
