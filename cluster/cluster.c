#include "cluster.h"

/*void readHeader(FILE* f, Header* h)
{
	int x;
	int y;
	int z;
	long fr;

	fread(&x, 4, 1, f);
	fread(&y, 4, 1, f);
	fread(&z, 4, 1, f);
	fread(&fr, 8, 1, f);

	h->x = x >> 16 | x & 0xFF;
	h->y = y;
	h->z = z;
	h->frequency = fr;

	// printf("(%d, %d, %d) @ %ld\n", x, y, z, fr);
}*/

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
	
	int node[h.x][h.y][h.z];
	int hasSourcesReceivers = readNode(node, &h, inFile);

	printf("%d, %d, %d @ %ld\n", h.x, h.y, h.z, h.frequency);

	if (hasSourcesReceivers & 1 == 1)
		readSample();

	while (1) // ! lastIteration
	{
		if (hasSourcesReceivers & 1 == 1)
			injectSample();

		scatter();

		if (hasSourcesReceivers & 2 == 2)
			readSample(); // ------

		delay();
	}

	if (hasSourcesReceivers & 2 == 2)
		writeExcitation();

	return EXIT_SUCCESS;
}

int readNode(int ***node, Header *h, FILE *inFile) 
{
	printf("ROOM: %d %d %d\n", h->x, h->y, h->z);

	for (int x = 0; x < h->x; x++)
		for (int y = 0; y < h->y; y++)
			for (int z = 0; z < h->z; z++)
			{
				printf("%d %d %d\n", x, y, z);
				fread(&(node[x][y][z]), 4, 1, inFile);
			}
	
	for (int x = 0; x < h->x; x++)
		for (int y = 0; y < h->y; y++)
			for (int z = 0; z < h->z; z++)
				printf("%d, ", node[x][y][z]);
	printf("\n");

	return 0; // should return 1 if sources are found
}

void readSample() {}

void injectSample() {}

void scatter() {}

void delay() {}

void writeExcitation() {}
