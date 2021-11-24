#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"app.h"
#include"types.h"

int main(void)
{
	/*
	 * Get from user:
	 * 	- width, depth, height (int)
	 * 	- update freq (48000Hz, 44100Hz, 22050Hz, 16000Hz, 11025Hz, 8000Hz)
	 */

	int w, h, d;
	int f = -1;
	const int c = 343;

	printf("width: ");
	scanf("%d", &w);
	printf("\n");

	printf("height: ");
	scanf("%d", &h);
	printf("\n");

	printf("depth: ");
	scanf("%d", &d);
	printf("\n");


	while (f >= 6 || f < 0)
	{
		printf("Possible frequency values:\n");
		printf("1) 48000\n");
		printf("2) 44100\n");
		printf("3) 22050\n");
		printf("4) 16000\n");
		printf("5) 11025\n");
		printf("6) 8000\n");
		printf("frequency: ");
		scanf("%d", &f);
		printf("\n");
	}
	const int freqs[] = { 48000, 44100, 22050, 16000, 11025, 8000 };

	f = freqs[f - 1];

	Header header = { getNodes(f, w, c),  getNodes(f, d, c), getNodes(f, h, c), f};

	//inform user if the room size slightly changed
	//to-do

	Node*** nodeMatrix = alloc_nodes(&header);
	if (!nodeMatrix) return EXIT_FAILURE;

	/*
	 * Customize room
	 */

	customizeRoom(&header, nodeMatrix);

	write_dwm_file("room.dwm", &header, nodeMatrix);
	
	//clean-up
	free_nodes(&header, nodeMatrix);
}

int getNodes(int f, int dim, int c)
{
	return (f * dim) / (c * sqrt(3));
}

void customizeRoom(const Header* header, Node*** nodes)
{
	char choice = 0;

	while (
		choice != 'S' &&
		choice != 'C' &&
		choice != 's' &&
		choice != 'r' &&
		choice != 'q'
		)
	{
		printf("Sphere: 'S'\n");
		printf("Cuboid: 'C'\n");
		printf("Source: 's'\n");
		printf("Receiver: 'r'\n");
		printf("QUIT: 'q'\n");
		printf("Select one... ");

		scanf("%c", &choice);
		printf("\n");
	}

	switch (choice)
	{
	case C_QUIT:
		return;
	case C_SPHERE:
		buildSphere(header, nodes);
		break;
	case C_CUBOID:
		buildCuboid(header, nodes);
		break;
	case C_SRC:
		//TODO: only one source allowed, check for this
		//		maybe store the source's last state and reset it whenever a new source is set. 
		setSource(nodes);
		break;
	case C_RCVR:
		setReceiver(nodes);
		break;
	}
}

void setReceiver(Node*** nodes)
{
	int x, y, z;
	Node n = { RCVR_NODE };

	printf("receiver x: ");
	scanf("%d", &x);
	printf("\n");

	printf("receiver y: ");
	scanf("%d", &y);
	printf("\n");

	printf("receiver z: ");
	scanf("%d", &z);
	printf("\n");

	// set receiver
	nodes[x][y][z] = n;
}

void setSource(Node*** nodes)
{
	int x, y, z;
	Node n = { SRC_NODE };

	printf("source x: ");
	scanf("%d", &x);
	printf("\n");

	printf("source y: ");
	scanf("%d", &y);
	printf("\n");

	printf("source z: ");
	scanf("%d", &z);
	printf("\n");

	// set source
	nodes[x][y][z] = n;
}

void buildSphere(const Header* header, Node*** nodes)
{
	int x, y, z;
	double r;

	printf("centre x: ");
	scanf("%d", &x);
	printf("\n");

	printf("centre y: ");
	scanf("%d", &y);
	printf("\n");

	printf("centre z: ");
	scanf("%d", &z);
	printf("\n");

	printf("radious: ");
	scanf("%lf", &r);
	printf("\n");

	Node n = { showOpts() };

	// taking the radious, center a cube arround the centre
	// run through each point and aply to those whose distance is <= than the redious
	// populate with n
	for (int x2 = 0; x2 <= header->x; x2++)
	{
		for (int y2 = 0; y2 <= header->y; y2++)
		{
			for (int z2 = 0; z2 <= header->z; z2++)
			{
				if (dist(x, x2, y, y2, z, z2) <= r)
				{
					nodes[x2][y2][z2] = n;
				}
			}
		}
	}
}

double dist(int x1, int x2, int y1, int y2, int z1, int z2)
{
	int xDist = (x1 - x2) * (x1 - x2);
	int yDist = (y1 - y2) * (y1 - y2);
	int zDist = (z1 - z2) * (z1 - z2);

	return sqrt((double)(xDist + yDist + zDist));
}

void buildCuboid(const Header* header, Node*** nodes)
{
	int x1, x2, y1, y2, z1, z2;


	printf("point 1 x: ");
	scanf("%d", &x1);
	printf("\n");

	printf("point 1 y: ");
	scanf("%d", &y1);
	printf("\n");

	printf("point 1 z: ");
	scanf("%d", &z1);
	printf("\n");

	printf("point 2 x: ");
	scanf("%d", &x2);
	printf("\n");

	printf("point 2 y: ");
	scanf("%d", &y2);
	printf("\n");

	printf("point 2 z: ");
	scanf("%d", &z2);
	printf("\n");

	Node n = { showOpts() };

	// for from x1 - x2, then y1 - y2, ...
	// populate with n
	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			for (int k = z1; k <= z2; k++)
			{
				nodes[i][j][k] = n;
			}
		}
	}
}

char showOpts()
{
	char opt = ' ';

	while (
		opt != STD_NODE &&
		opt != SRC_NODE &&
		opt != RCVR_NODE &&
		opt != RHO_1 &&
		!(RHO_0 <= opt && opt <= RHO_09) &&
		!(RHO_091 <= opt && opt <= RHO_099)
		)
	{
		printf("standard: ' '\n");
		printf("source: 'S'\n");
		printf("receiver: 'R'\n");
		printf("p=0: A");
		printf("p=0.1: B");
		printf("p=0.2: C");
		printf("p=0.3: D");
		printf("p=0.4: E");
		printf("p=0.5: F");
		printf("p=0.6: G");
		printf("p=0.7: H");
		printf("p=0.8: I");
		printf("p=0.9: J");
		printf("p=0.91: 1");
		printf("p=0.92: 2");
		printf("p=0.93: 3");
		printf("p=0.94: 4");
		printf("p=0.95: 5");
		printf("p=0.96: 6");
		printf("p=0.97: 7");
		printf("p=0.98: 8");
		printf("p=0.99: 9");
		printf("p=1: Z");

		printf("Configuration: ");
		scanf("%c", &opt);
		printf("\n");
	}
	return opt;
}

Node*** alloc_nodes(const Header* header)
{
	//https://web.archive.org/web/20210601072857/https://www.techiedelight.com/dynamically-allocate-memory-for-3d-array/
	//main website was down when i tried
	Node*** nodes = (Node***)malloc(header->x * sizeof(Node**));

	if (nodes == NULL)
	{
		fprintf(stderr, "Out of memory");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < header->x; i++)
	{
		nodes[i] = malloc(header->y * sizeof(Node*));

		if (nodes[i] == NULL)
		{
			fprintf(stderr, "Out of memory");
			exit(EXIT_FAILURE);
		}

		for (int j = 0; j < header->y; j++)
		{
			nodes[i][j] = malloc(header->z * sizeof(Node));
			if (nodes[i][j] == NULL)
			{
				fprintf(stderr, "Out of memory");
				exit(EXIT_FAILURE);
			}
		}
	}

	Node n = { STD_NODE };

	// assign values to the allocated memory
	for (int i = 0; i < header->x; i++)
	{
		for (int j = 0; j < header->y; j++)
		{
			for (int k = 0; k < header->z; k++) 
			{
				nodes[i][j][k] = n;
			}
		}
	}

	return nodes;
}

void free_nodes(const Header* header, Node*** nodes)
{
	for (int i = 0; i < header->x; i++)
	{
		for (int j = 0; j < header->y; j++) {
			free(nodes[i][j]);
		}
		free(nodes[i]);
	}
	free(nodes);
}

void write_dwm_file(const char* filename, const Header* header, Node*** nodes)
{
	FILE* f_ptr = fopen(filename, "r");
	if (f_ptr)
	{
		remove(filename);
	}
	f_ptr = fopen(filename, "w");
	fwrite(header, sizeof(Header), 1, f_ptr);
	for (int i = 0; i < header->x; i++)
	{
		for (int j = 0; j < header->y; j++)
		{
			for (int k = 0; k < header->z; k++)
			{
				fwrite(&(nodes[i][j][k]), sizeof(Node), 1, f_ptr);
			}
		}
	}
	fclose(f_ptr);
}

void room_partitioning(const char* filename){
	//char buf[6];
	File* f_ptr = fopen(filename, 'r');
	/*
	fgets(buf, 6,f_ptr);
	//get width, depth and height from the file
	width = ;
	depth = ;
	height = ;
	*/
	printf("Specify the dimensions of the partitioning: ")

	printf("x_g: ");
	scanf("%d", &x);
	printf("\n");

	printf("y_g: ");
	scanf("%d", &y);
	printf("\n");

	printf("z_g: ");
	scanf("%d", &z);
	printf("\n");

	int N = x_g * y_g * z_g;
	int x, y, z, i = 0, index;
	//int x_blocks, y_blocks, z_blocks;
	int block[];

	for(; i < N; i++){
		x = i / (y_g * z_g);
		y = (i % (y_g * z_g)) / z_g;
		z = (i % (y_g * z_g)) % z_g;
		index = x * y_g * z_g + y * z_g	+ z;
		//block[index] = 
	}

}