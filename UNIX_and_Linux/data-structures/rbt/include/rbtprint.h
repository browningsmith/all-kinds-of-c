#ifndef RBTPRINT_H
#define RBTPRINT_H

#include "rbt.h"

/*****************************************************************
 * rbtPrint
 * 
 * Inputs: RBT tree, int (*textFunction) (char* buffer, void* content)
 * Returns: int
 * 
 * Prints a depiction of the given RBT to standard output.
 * 
 * Returns 0 on success
 * 
 * Returns -1 on failure, and doesn't print anything to standard
 * output
 * 
 * rbtPrint uses the given textFunction to convert the content of
 * each node into text, by passing a character array of length 51
 * to buffer, and the content of each node to content
 * 
 * The textFunction must behave in the following way:
 * 	- rbtPrint will pass a character array of length 51 to the
 *    buffer argument. Whatever textFunction places into this array
 *    will be what rbtPrint uses to print the content of the node
 *  - textFunction should not put a newLine character into the
 *    buffer, in order for the tree to display properly
 *  - textFunction must place a null terminating character
 *    on the end of the desired text placed in to buffer
 *  - textFunction must return an int equal to the length of the
 *    text placed in to buffer, not including the null
 *    terminating character
 *****************************************************************/
int rbtPrint(RBT tree, int (*textFunction) (char* buffer, void* content));

#endif /* RBTPRINT_H */
