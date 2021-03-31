#ifndef DOUBLELLIMPL_H
#define DOUBLELLIMPL_H

/*****************************************
 * Implementation only declarations for
 * doublell API
 *
 * NOT TO BE INCLUDED OUTSIDE OF doublell.c
 * OR dlltest.c
 *****************************************/

#include "doublell.h"

DLLNode* dllNewNode__(void* content);
void* dllDeleteNode__(DLLNode* node);

#endif /* DOUBLELLIMPL_H */