#include "cluster.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Missing argument <file>\n");
		return EXIT_FAILURE;
	}

	FILE *inFile = fopen(argv[1], "rb");
	if (!inFile) 
	{
		perror("fopen");
		return EXIT_FAILURE;
	}

	Header h = { 0 };
	fread(&h, sizeof(Header), 1, inFile);

	fixHeaderEndian(&h);
	
	printf("%d, %d, %d @ %ld\n", h.x, h.y, h.z, h.frequency);

	Node*** nodes = allocNodes(&h);
	int hasSourcesReceivers = readNodes(nodes, &h, inFile);

	exit(0);

	if ((hasSourcesReceivers & 1) == 1)
		readSample();

	while (1) // ! lastIteration
	{
		if ((hasSourcesReceivers & 1) == 1)
			injectSample();

		scatterPass(&h, nodes);

		if ((hasSourcesReceivers & 2) == 2)
			readSample(); // ------

		delayPass(&h, nodes);
	}

	if ((hasSourcesReceivers & 2) == 2)
		writeExcitation();

	freeNodes(&h, nodes);

	return EXIT_SUCCESS;
}

int readNodes(Node ***nodes, Header *h, FILE *inFile) 
{
	printf("ROOM: %d %d %d\n", h->x, h->y, h->z);

	// Clear node
	Node n = { 0 };
	char c;

	int x, y, z;
	for (x = 0; x < h->x; x++)
		for (y = 0; y < h->y; y++)
			for (z = 0; z < h->z; z++)
			{
				printf("%d %d %d\n", x, y, z);
				fread(&c, sizeof(char), 1, inFile);
				// Copy the clear node to nodes
				nodes[x][y][z] = n;
				// set node type
				nodes[x][y][z].type = c;
			}

	for (x = 0; x < h->x; x++)
		for (y = 0; y < h->y; y++)
			for (z = 0; z < h->z; z++)
				printf("%d, ", nodes[x][y][z].type);
	printf("\n");

	return 0; // should return 1 if sources are found
}

void readSample() {}

void injectSample() {}

void scatterPass(const Header *h, Node ***ns) 
{
/*   up
 *    |z
 *    |
 *    |      y
 *   ,.------- right
 *  / 
 *x/ front
 */


	Node *n;
	int x, y, z;
	float k;
	for (x = 0; x < h->x; x++)
		for (y = 0; y < h->y; y++)
			for (z = 0; z < h->z; z++)
			{
				n = &(ns[x][y][z]);

				if (n->type == STD_NODE || 
					n->type == SRC_NODE || 
					n->type == RCVR_NODE)
				{
					n->p = (n->pUpI + n->pDownI + n->pRightI + n->pLeftI + n->pFrontI + n->pBackI) / 3;
					
					n->pUpO = n->p - n->pUpI;
					n->pDownO = n->p - n->pDownI;
					n->pRightO = n->p - n->pRightI;
					n->pLeftO = n->p - n->pLeftI;
					n->pFrontO = n->p - n->pFrontI;
					n->pBackO = n->p - n->pBackI;
				} else 
				{
					k = getNodeReflectionCoefficient(n);
					
					n->pUpO = k * n->pUpI;
					n->pDownO = k * n->pDownI;
					n->pRightO = k * n->pRightI;
					n->pLeftO = k * n->pLeftI;
					n->pFrontO = k * n->pFrontI;
					n->pBackO = k * n->pBackI;
				}
			}
}

void delayPass(const Header* h, Node*** ns)
{
/*   up
*    |z
*    |
*    |      y
*   ,.------- right
*  /
*x/ front
*/


	Node* n;
	int x, y, z;
	
	// this loop can be optimized to not have to do these ifs and only process nodes that have all neighbours but then we'd have to process all the others seperately.
	// its fine for now

	for (x = 0; x < h->x; x++)
	{
		for (y = 0; y < h->y; y++)
		{
			for (z = 0; z < h->z; z++)
			{
				n = &(ns[x][y][z]);

				if (x != 0)	// back
				{
					ns[x - 1][y][z].pBackI = n->pBackO;
				}
				if (x < h->x) // front
				{
					ns[x + 1][y][z].pFrontI = n->pFrontO;
				}

				if (y != 0)	// left
				{
					ns[x][y - 1][z].pLeftI = n->pLeftO;
				}
				if (y < h->y) // right
				{
					ns[x][y + 1][z].pRightI = n->pRightO;
				}

				if (z != 0)	// down
				{
					ns[x][y][z - 1].pDownI = n->pDownO;
				}
				if (z < h->z) // up
				{
					ns[x][y][z + 1].pUpI = n->pUpO;
				}
			}
		}
	}
}

void writeExcitation() {}

void fixHeaderEndian(Header *h)
{
#ifdef __linux__
	h->x = ((int) h->x & 0x000000ff) << 24u |
			((int) h->x & 0x0000ff00) << 8u |
			((int) h->x & 0x00ff0000) >> 8u |
			((int) h->x & 0xff000000) >> 24u;
	
	h->y = ((int) h->y & 0x000000ff) << 24u |
			((int) h->y & 0x0000ff00) << 8u |
			((int) h->y & 0x00ff0000) >> 8u |
			((int) h->y & 0xff000000) >> 24u;
	
	h->z = ((int) h->z & 0x000000ff) << 24u |
			((int) h->z & 0x0000ff00) << 8u |
			((int) h->z & 0x00ff0000) >> 8u |
			((int) h->z & 0xff000000) >> 24u;

	h->frequency = 
			(((int) (h->frequency >> 32) & 0x000000ff) << 24u |
			((int) (h->frequency >> 32) & 0x0000ff00) << 8u |
			((int) (h->frequency >> 32) & 0x00ff0000) >> 8u |
			((int) (h->frequency >> 32) & 0xff000000) >> 24u )|
			((int) h->frequency & 0x000000ff) << 24u |
			((int) h->frequency & 0x0000ff00) << 8u |
			((int) h->frequency & 0x00ff0000) >> 8u |
			((int) h->frequency & 0xff000000) >> 24u;
#endif
}

int fixInt(int i)
{
#ifdef __linux__
	return	((int) i & 0x000000ff) << 24u |
			((int) i & 0x0000ff00) << 8u |
			((int) i & 0x00ff0000) >> 8u |
			((int) i & 0xff000000) >> 24u;
	
#endif
}
