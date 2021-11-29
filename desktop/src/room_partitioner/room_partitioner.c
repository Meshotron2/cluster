#include "room_partitioner.h"

int main(void)
{
	FILE* file = getDWMFile();
    
	Header header = { 0 };

	fread(&header, sizeof(Header), 1, file);

	Node*** nodeMatrix = alloc_nodes(&header);
	
	fillNodeMatrix(file, &header, nodeMatrix);

	int Xg, Yg, Zg;
	getRooms(&Xg, &Yg, &Zg);

	if (file)
    {
        fclose(file);
    }

    return 0;
}

void room_partitioning(const char* filename){
	//char buf[6];
	File* f_ptr = fopen(filename, 'r');
	int x_g, y_g, z_g;
	/*
	fgets(buf, 6,f_ptr);
	//get width, depth and height from the file
	width = ;
	depth = ;
	height = ;
	*/
	printf("Specify the dimensions of the partitioning: ")

	printf("x_g: ");
	scanf("%d", &x_g);
	printf("\n");

	printf("y_g: ");
	scanf("%d", &y_g);
	printf("\n");

	printf("z_g: ");
	scanf("%d", &z_g);
	printf("\n");

	int N = x_g * y_g * z_g;
	int x, y, z, i = 0, index;
	//int x_blocks, y_blocks, z_blocks;
	//int block[];

	for(; i < N; i++){
		x = i / (y_g * z_g);
		y = (i % (y_g * z_g)) / z_g;
		z = (i % (y_g * z_g)) % z_g;
		index = x * y_g * z_g + y * z_g	+ z;
		//block[index] = 
	}

}

void fillNodeMatrix(FILE* file, const Header* header, Node*** nodeMatrix)
{	
	for (int x = 0; x < header->x; x++)
	{
		for (int y = 0; y < header->y; y++)
		{
			fread(&(nodeMatrix[x][y][0]), sizeof(Node), header->z, file);
		}
	}
}

Header* getRoomPartitionHeaders(const int Xg, const int Yg, const int Zg)
{
	int N = Xg * Yg * Zg;

	Header* headers = (Header*)malloc(sizeof(Header) * N);
	if (headers == NULL)
	{
		printf("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < N; i++)
	{

	}
}

void getRooms(int* Xg, int* Yg, int* Zg)
{
	char filename[256];
	printf("We now need to configure how to divide the room.\n");
	printf("Xg: ");
	scanf("%d", Xg);
	printf("Yg: ");
	scanf("%d", Yg);
	printf("Zg: ");
	scanf("%d", Zg);
}

FILE* getDWMFile()
{
	char filename[256];

	printf("Please input a DWM room file: ");

	FILE* file;
	fgets(filename, 256, stdin);
	filename[strcspn(filename, "\n")] = '\0';
	file = fopen(filename, "r");
	while (!file)
	{
		printf("Looks like that file doesn't exist.\nPlease try again with another file: ");
		if (fgets(filename, 256, stdin))
		{
			filename[strcspn(filename, "\n")] = '\0';
			file = fopen(filename, "r");
		}
	}
	return file;
}