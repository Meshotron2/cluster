#include "node.h"

Node*** allocNodes(const Header* header)
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

void freeNodes(const Header* header, Node*** nodes)
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

float getNodeReflectionCoefficient(const Node* n)
{
	switch (n->type)
	{
	case RHO_0:
		return 0.0f;
	case RHO_01:
		return 0.1f;
	case RHO_02:
		return 0.2f;
	case RHO_03:
		return 0.3f;
	case RHO_04:
		return 0.4f;
	case RHO_05:
		return 0.5f;
	case RHO_06:
		return 0.6f;
	case RHO_07:
		return 0.7f;
	case RHO_08:
		return 0.8f;
	case RHO_09:
		return 0.9f;
	case RHO_091:
		return 0.91f;
	case RHO_092:
		return 0.92f;
	case RHO_093:
		return 0.93f;
	case RHO_094:
		return 0.94f;
	case RHO_095:
		return 0.95f;
	case RHO_096:
		return 0.96f;
	case RHO_097:
		return 0.97f;
	case RHO_098:
		return 0.98f;
	case RHO_099:
		return 0.99f;
	case RHO_1:
		return 1.0f;
	default:
		return -1.0f;
	}
}

int getAllNodesOfType(Point** buf, const Header* header, const Node*** nodes, const char type)
{
	Point* points = NULL;
	int pointCount = 0;
	
	for (int x = 0; x < header->x; x++)
	{
		for (int y = 0; y < header->y; y++)
		{
			for (int z = 0; z < header->x; z++)
			{
				if (nodes[x][y][z].type == type)
				{
					if (points == NULL)
					{
						points = malloc(sizeof(Point));
						if (points == NULL)
						{
							fprintf(stderr, "Out of memory");
							exit(EXIT_FAILURE);
						}
					}
					else
					{
						Point* rp = realloc(points, sizeof(Point) * pointCount+1);
						if (rp == NULL)
						{
							fprintf(stderr, "Out of memory");
							exit(EXIT_FAILURE);
						}
						points = rp;
					}

					points[pointCount].x = x;
					points[pointCount].y = y;
					points[pointCount].z = z;
					pointCount++;
				}
			}
		}
	}

	*buf = points;

	return pointCount;
}