#include "cluster.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Missing argument <file> <runtime>\n");
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

	int iterationCnt = (int)ceil(atof(argv[2]) * h.frequency);
	if (!iterationCnt)
	{
		printf("Failed to parse <runtime>. Exiting.");
		exit(EXIT_FAILURE);
	}
	
	printf("%d, %d, %d @ %ld\n", h.x, h.y, h.z, h.frequency);

	Node*** nodes = allocNodes(&h);
	readNodes(nodes, &h, inFile);

	Node** sources;
	int sourceCnt = getAllNodesOfType(&sources, &h, nodes, SRC_NODE);

	if (sourceCnt == 0)
	{
		printf("No sources found. Exiting.\n");
		exit(EXIT_FAILURE);
	}

	Node** receivers;
	int receiverCnt = getAllNodesOfType(&receivers, &h, nodes, RCVR_NODE);

	if (receiverCnt == 0)
	{
		printf("No receivers found. Exiting.\n");
		exit(EXIT_FAILURE);
	}

	float** receiversData = allocReceiversMemory(receiverCnt, iterationCnt);

	injectSamples(sources, sourceCnt);
	for (int i = 0; i < iterationCnt; i++) // ! lastIteration
	{
		scatterPass(&h, nodes);

		readSamples(receivers, receiversData, receiverCnt, i);

		delayPass(&h, nodes);
	}

	//if ((hasSourcesReceivers & 2) == 2)
	//	writeExcitation();

	freeNodes(&h, nodes);
	freeAllNodesOfType(&receivers);
	freeAllNodesOfType(&sources);
	freeReceiversMemory(&receiversData, receiverCnt);

	return EXIT_SUCCESS;
}

void readNodes(Node ***nodes, Header *h, FILE *inFile) 
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
				fread(&c, sizeof(char), 1, inFile);
				// Copy the clear node to nodes
				nodes[x][y][z] = n;
				// set node type
				nodes[x][y][z].type = c;
			}
}

void readSamples(const Node** n, float** buf, const int receiverCount, const int iteration) 
{
	for (int i = 0; i < receiverCount; i++)
	{
		buf[i][iteration] = n[i]->p;
	}
}

void injectSamples(Node** n, const int sourceCount)
{
	const float f = 100000000.0f / 2;
	for (int i = 0; i < sourceCount; i++)
	{
		n[i]->pUpI = f;
		n[i]->pDownI = f;
		n[i]->pRightI = f;
		n[i]->pLeftI = f;
		n[i]->pFrontI = f;
		n[i]->pBackI = f;
	}
}

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

				if (n->type == AIR_NODE || n->type == RCVR_NODE || n->type == SRC_NODE)
				{
					n->p = (n->pUpI + n->pDownI + n->pRightI + n->pLeftI + n->pFrontI + n->pBackI) / 3;
					
					n->pUpO = n->p - n->pUpI;
					n->pDownO = n->p - n->pDownI;
					n->pRightO = n->p - n->pRightI;
					n->pLeftO = n->p - n->pLeftI;
					n->pFrontO = n->p - n->pFrontI;
					n->pBackO = n->p - n->pBackI;
				} 
				else 
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
				if (x < h->x-1) // front
				{
					ns[x + 1][y][z].pFrontI = n->pFrontO;
				}

				if (y != 0)	// left
				{
					ns[x][y - 1][z].pLeftI = n->pLeftO;
				}
				if (y < h->y-1) // right
				{
					ns[x][y + 1][z].pRightI = n->pRightO;
				}

				if (z != 0)	// down
				{
					ns[x][y][z - 1].pDownI = n->pDownO;
				}
				if (z < h->z-1) // up
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
