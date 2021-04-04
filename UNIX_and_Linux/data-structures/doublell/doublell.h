#ifndef DOUBLELL_H
#define DOUBLELL_H

typedef struct DLLNode_struct {

    struct DLLNode_struct* prev;
    struct DLLNode_struct* next;

    void* content;

} DLLNode;

typedef struct {

    DLLNode* head;
    DLLNode* tail;

} DLL;

typedef struct {
    
    DLL* list;
    DLLNode* currentNode;

} DLLIterator;

/*****************************************************************
 * dllInit
 * 
 * Inputs: DLL* list
 * Returns: None
 * 
 * Initializes the given doubly linked list as a new
 * empty doubly linked list
 * 
 * If a pointer to an already existing DLL is passed, all data
 * within the list will be lost to a memory leak, as this function
 * does not clear out an already existing list
 *****************************************************************/
void dllInit(DLL* list);

/*****************************************************************
 * dllIsEmpty
 * 
 * Inputs: DLL list
 * Returns: int
 * 
 * Checks to see if the given DLL is empty. It does so by checking
 * whether the start of the list is NULL, and assumes that the
 * end of the list is also NULL.
 *
 * Returns 1 if list is empty, 0 otherwise
 *****************************************************************/
int dllIsEmpty(DLL list);

/*****************************************************************
 * dllPush
 * 
 * Inputs: DLL* list, void* content
 * Returns: int
 * 
 * Creates a new DLL node and inserts it at the start of the list,
 * containing the given content.
 * 
 * Returns 0 on success, -1 on error. Error is caused by an error
 * with malloc, therefore errno will be set
 *****************************************************************/
int dllPush(DLL* list, void* content);

/*****************************************************************
 * dllPushTail
 * 
 * Inputs: DLL* list, void* content
 * Returns: int
 * 
 * Creates a new DLL node and inserts it at the end of the list,
 * containing the given content.
 * 
 * Returns 0 on success, -1 on error. Error is caused by an error
 * with malloc, therefore errno will be set
 *****************************************************************/
int dllPushTail(DLL* list, void* content);

/*****************************************************************
 * dllGetHead
 * 
 * Inputs: DLL* list, void** returnedContent
 * Returns: int
 * 
 * Gets the content of the node at the head of the list, if it
 * exists.
 * 
 * Returns 0 on success, and places the content of the node into
 * returnedContent
 *
 * Returns -1 on failure, meaning the list is empty, and places
 * NULL into returnedContent
 *****************************************************************/
int dllGetHead(DLL list, void** returnedContent);

/*****************************************************************
 * dllGetTail
 * 
 * Inputs: DLL* list, void** returnedContent
 * Returns: int
 * 
 * Gets the content of the node at the tail of the list, if it
 * exists.
 * 
 * Returns 0 on success, and places the content of the node into
 * returnedContent
 *
 * Returns -1 on failure, meaning the list is empty, and places
 * NULL into returnedContent
 *****************************************************************/
int dllGetTail(DLL list, void** returnedContent);

/*****************************************************************
 * dllPop
 * 
 * Inputs: DLL* list, void** returnedContent
 * Returns: int
 * 
 * Removes the current head of the list, if it exists.
 * 
 * Returns 0 on success, and places the content of the popped node
 * into returnedContent
 *
 * Returns -1 on failure, meaning the list is empty or broken, and
 * places NULL into returnedContent
 *****************************************************************/
int dllPop(DLL* list, void** returnedContent);

/*****************************************************************
 * dllPopTail
 * 
 * Inputs: DLL* list, void** returnedContent
 * Returns: int
 * 
 * Removes the current tail of the list, if it exists.
 * 
 * Returns 0 on success, and places the content of the popped node
 * into returnedContent
 *
 * Returns -1 on failure, meaning the list is empty or broken, and
 * places NULL into returnedContent
 *****************************************************************/
int dllPopTail(DLL* list, void** returnedContent);

/*****************************************************************
 * dllClear
 * 
 * Inputs: DLL* list, int (*clearingFunction) (void* content)
 * Returns: int
 * 
 * Deletes all nodes in the given list, starting from the head and
 * and clears the contents of each node using the given
 * clearingFunction
 *
 * If clearingFunction is NULL, dllClear will not worry about
 * clearing the content of each node
 * 
 * Returns 0 on success, meaning the clearingFunction did not run
 * in to an error.
 *
 * Returns -1 on failure, meaning the clearingFunction ran in to
 * an error on one of the nodes, or that it ran in to an other error
 * such as the list being broken somewhere in the middle and will
 * leave the remainder of the list intact.
 *****************************************************************/
int dllClear(DLL* list, int (*clearingFunction) (void*));

/*****************************************************************
 * IMPORTANT
 *
 * DLLIterator methods
 *
 * All above methods affect elements on a DLL without considering
 * that a DLLIterator may exist attached to the list. If not
 * careful, it is possible to remove a node that the DLLiterator
 * is currently sitting on.
 *
 * If an existing DLLIterator is used after one or more of the
 * above methods are called, dllToHead or dllToTail should be called
 * to place the iterator back on the valid start of a list
 *****************************************************************/

/*****************************************************************
 * dllToHead
 * 
 * Inputs: DLLIterator* iterator, DLL* list
 * Returns: int
 * 
 * Moves the given DLLIterator to the start of the given list, as
 * long as the given list is not empty
 * 
 * Returns 0 on success
 *
 * Returns -1 on failure, meaning the list is empty
 *****************************************************************/
int dllToHead(DLLIterator* iterator, DLL* list);

/*****************************************************************
 * dllToTail
 * 
 * Inputs: DLLIterator* iterator, DLL* list
 * Returns: int
 * 
 * Moves the given DLLIterator to the end of the given list, as
 * long as the given list is not empty
 * 
 * Returns 0 on success
 *
 * Returns -1 on failure, meaning the list is empty
 *****************************************************************/
int dllToTail(DLLIterator* iterator, DLL* list);

/*****************************************************************
 * dllGetThis
 * 
 * Inputs: DLLIterator* iterator, void** content
 * Returns: int
 * 
 * Attempts to place the content from the iterator's current node
 * into the given content parameter
 * 
 * Returns 0 on success
 *
 * Returns -1 on failure, meaning the list is empty, and places
 * NULL into content
 *****************************************************************/
int dllGetThis(DLLIterator* iterator, void** content);

/*****************************************************************
 * dllGetPrev
 * 
 * Inputs: DLLIterator* iterator, void** content
 * Returns: int
 * 
 * Attempts to move the iterator to the previous node, and then
 * place that node's content into the given content parameter
 * 
 * Returns 0 on success
 *
 * Returns -1 on failure, meaning the list is empty, or that the
 * node the iterator is on has no previous node
 *****************************************************************/
int dllGetPrev(DLLIterator* iterator, void** content);

/*****************************************************************
 * dllGetNext
 * 
 * Inputs: DLLIterator* iterator, void** content
 * Returns: int
 * 
 * Attempts to move the iterator to the next node, and then
 * place that node's content into the given content parameter
 * 
 * Returns 0 on success
 *
 * Returns -1 on failure, meaning the list is empty, or that the
 * node the iterator is on has no previous node
 *****************************************************************/
int dllGetNext(DLLIterator* iterator, void** content);

/*****************************************************************
 * dllInsertPrev
 * 
 * Inputs: DLLIterator* iterator, void* content
 * Returns: int
 * 
 * Attempts to insert a new node as the previous node of the node
 * that the iterator is currently on.
 * 
 * Returns 0 on success
 *
 * Returns -1 on failure. Failure can be caused by:
 *  - If the list is empty, no node will be inserted. User should
 *    instead call dllPush or dllPushTail on an empty list
 *  - If the node could not be created due to not being able to
 *    allocate memory, errno will be set
 *****************************************************************/
int dllInsertPrev(DLLIterator* iterator, void* content);

/*****************************************************************
 * dllInsertNext
 * 
 * Inputs: DLLIterator* iterator, void* content
 * Returns: int
 * 
 * Attempts to insert a new node as the next node of the node
 * that the iterator is currently on.
 * 
 * Returns 0 on success
 *
 * Returns -1 on failure. Failure can be caused by:
 *  - If the list is empty, no node will be inserted. User should
 *    instead call dllPush or dllPushTail on an empty list
 *  - If the node could not be created due to not being able to
 *    allocate memory, errno will be set
 *****************************************************************/
int dllInsertNext(DLLIterator* iterator, void* content);

/*****************************************************************
 * dllDeletePrev
 * 
 * Inputs: DLLIterator* iterator, void** content
 * Returns: int
 * 
 * Deletes the node that is previous to the node that the given
 * iterator is currently on, and places the content of that node
 * into the given content parameter
 * 
 * Returns 0 on success, with the content of the deleted node being
 * placed into the given content argument
 * 
 * Returns -1 on failure, with NULL being placed into the given
 * content argument
 * Failure can be caused by:
 *  - If the list is empty, and no node can be deleted
 *  - If the iterator's node has no prev node to delete
 *  - If the node to delete is the head, but the head's pointer
 *    to next is NULL, meaning the list is broken
 *****************************************************************/
int dllDeletePrev(DLLIterator* iterator, void** content);

/*****************************************************************
 * dllDeleteNext
 * 
 * Inputs: DLLIterator* iterator, void** content
 * Returns: int
 * 
 * Deletes the node that is next to the node that the given
 * iterator is currently on, and places the content of that node
 * into the given content parameter
 * 
 * Returns 0 on success, with the content of the deleted node being
 * placed into the given content argument
 * 
 * Returns -1 on failure, with NULL being placed into the given
 * content argument
 * Failure can be caused by:
 *  - If the list is empty, and no node can be deleted
 *  - If the iterator's node has no next node to delete
 *  - If the node to delete is the tail, but the tail's pointer
 *    to prev is NULL, meaning the list is broken
 *****************************************************************/
int dllDeleteNext(DLLIterator* iterator, void** content);

#endif /* DOUBLELL_H */