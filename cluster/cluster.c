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
	if (!inFile) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	Header h = { 0 };
	fread(&h, sizeof(Header), 1, inFile);

	printf("%d, %d, %d @ %ld\n", h.x, h.y, h.z, h.frequency);

	return EXIT_SUCCESS;
}

