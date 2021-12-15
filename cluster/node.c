#include "node.h"

Node*** alloc_nodes(const Header* header)
{
	//https://web.archive.org/web/20210601072857/https://www.techiedelight.com/dynamically-allocate-memory-for-3d-array/
	//main website was down when i tried
	Node*** nodes = NULL;

	if (header->x <= 0 || header->y <= 0 || header->z <= 0)
	{
		fprintf(stderr, "Invalid header! x,y and z cannot be <= 0!");
		exit(EXIT_FAILURE);
	}

	nodes = (Node***)malloc(header->x * sizeof(Node**));

	if (nodes == NULL)
	{
		fprintf(stderr, "Out of memory");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < header->x; i++)
	{
		nodes[i] = (Node**)malloc(header->y * sizeof(Node*));

		if (nodes[i] == NULL)
		{
			fprintf(stderr, "Out of memory");
			exit(EXIT_FAILURE);
		}

		for (int j = 0; j < header->y; j++)
		{
			nodes[i][j] = (Node*)malloc(header->z * sizeof(Node));
			if (nodes[i][j] == NULL)
			{
				fprintf(stderr, "Out of memory");
				exit(EXIT_FAILURE);
			}
		}
	}

	return nodes;
}

void free_nodes(const Header* header, Node*** nodes)
{
	if (header->x <= 0 || header->y <= 0 || header->z <= 0)
	{
		fprintf(stderr, "Invalid header! x,y and z cannot be <= 0!");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < header->x; i++)
	{
		for (int j = 0; j < header->y; j++)
		{
			free(nodes[i][j]);
		}
		free(nodes[i]);
	}
	free(nodes);
}