


#ifndef Run
    #define Run
    #define M 5

    #include <stdlib.h>
    #include <stdio.h>

typedef struct Node {
	struct Node* firstPtr;
	int nEntries;
	Entry entries[M-1];
} Node;


typedef struct Entry {
	int data;
	struct Node* right;
} Entry;



#endif