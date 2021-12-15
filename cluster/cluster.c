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
	
	Node*** nodes = alloc_nodes(&h);
	int hasSourcesReceivers = readNodes(nodes, &h, inFile);

	printf("%d, %d, %d @ %ld\n", h.x, h.y, h.z, h.frequency);

	if ((hasSourcesReceivers & 1) == 1)
		readSample();

	while (1) // ! lastIteration
	{
		if ((hasSourcesReceivers & 1) == 1)
			injectSample();

		scatter();

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

	for (int x = 0; x < h->x; x++)
		for (int y = 0; y < h->y; y++)
			for (int z = 0; z < h->z; z++)
			{
				printf("%d %d %d\n", x, y, z);
				fread(&c, sizeof(char), 1, inFile);
				// Copy the clear node to nodes
				nodes[x][y][z] = n;
				// set node type
				nodes[x][y][z].type = c;
			}
	
	for (int x = 0; x < h->x; x++)
		for (int y = 0; y < h->y; y++)
			for (int z = 0; z < h->z; z++)
				printf("%d, ", nodes[x][y][z].type);
	printf("\n");

	return 0; // should return 1 if sources are found
}

void readSample() {}

void injectSample() {}

void scatter() {}

void delay() {}

void writeExcitation() {}
