#ifndef RBTPRINT_H
#define RBTPRINT_H

typedef struct {

	long capacity;
	long usage;
	char* text;
	
} PLine;

PLine* newPLine(void);

#endif /* RBTPRINT_H */
