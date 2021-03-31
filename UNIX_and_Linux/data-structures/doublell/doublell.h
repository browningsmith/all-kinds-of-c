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

// Helper functions
DLLNode* dllNewNode__(void* content);

#endif /* DOUBLELL_H */