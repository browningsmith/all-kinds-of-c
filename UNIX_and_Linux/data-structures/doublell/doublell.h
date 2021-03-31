#ifndef DOUBLELL_H
#define DOUBLELL_H

typedef struct DLLNode_struct {

    struct DLLNode_struct* prev;
    struct DLLNode_struct* next;

    void* content;

} DLLNode;

typedef struct {

    DLLNode* start;
    DLLNode* end;

} DLL;

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

#endif /* DOUBLELL_H */