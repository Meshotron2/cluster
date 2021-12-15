#include "types.h"
#include<stdlib.h>
#include<stdio.h>

typedef struct Node {
	float pUpI;
	float pUpO;
	float pDownI;
	float pDownO;
	float pLeftI;
	float pLeftO;
	float pRightI;
	float pRightO;
	float pFrontI;
	float pFrontO;
	float pBackI;
	float pBackO;

	float p;
	char type;
} Node;

// Allocates a node 3D array with dimensions specified in the Header
// This function allocates memory that must be released by calling free_nodes()
Node*** alloc_nodes(const Header* header);
void free_nodes(const Header* header, Node*** nodes);