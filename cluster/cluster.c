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

	Node*** nodes = alloc_nodes(&h);
	int hasSourcesReceivers = readNodes(nodes, &h, inFile);
	
	exit(0);

	if ((hasSourcesReceivers & 1) == 1)
		readSample();

	while (1) // ! lastIteration
	{
		if ((hasSourcesReceivers & 1) == 1)
			injectSample();

		scatter(&h, nodes);

		if ((hasSourcesReceivers & 2) == 2)
			readSample(); // ------

		delay();
	}

	if ((hasSourcesReceivers & 2) == 2)
		writeExcitation();

	free_nodes(&h, nodes);

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

	int x, y, z;
	for (x = 0; x < h->x; x++)
		for (y = 0; y < h->y; y++)
			for (z = 0; z < h->z; z++)
				printf("%d, ", nodes[x][y][z].type);
	printf("\n");

	return 0; // should return 1 if sources are found
}

void readSample() {}

void injectSample() {}

void scatter(Header *h, Node ***ns) 
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
	for (x = 0; x < h->x; x++)
		for (y = 0; y < h->y; y++)
			for (z = 0; z < h->z; z++)
			{
				n = ns[x][y][z];
				n->p = (n->pUpI + n->pDownI + n->pRightI + n->pLeftI + n->pFrontI + n->pBackI)/3;

				if (n->type != ' ' && 
					n->type != 'S' && 
					n->type != 'R')
				{
					n->pUpO = n->p - n->pUpI;
					n->pDownO = n->p - n->pDownI;
					n->pRightO = n->p - n->pRightI;
					n->pLeftO = n->p - n->pLeftI;
					n->pFrontO = n->p - n->pFrontI;
					n->pBackO = n->p - n->pBackI;
				} else 
				{
					n->pUpO = n->p * n->pUpI;
					n->pDownO = n->p * n->pDownI;
					n->pRightO = n->p * n->pRightI;
					n->pLeftO = n->p * n->pLeftI;
					n->pFrontO = n->p * n->pFrontI;
					n->pBackO = n->p * n->pBackI;
				}
			}
}

void delay() {}

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
