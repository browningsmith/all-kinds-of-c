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
 * dllGet
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
int dllGet(DLL list, void** returnedContent);

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

#endif /* DOUBLELL_H */