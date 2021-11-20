#pragma once
#include "types.h"

int getNodes(int f, int dim, int c);
void customizeRoom(const Node*** nodes);
void setReceiver(Node*** nodes);
void setSource(Node*** nodes);
void buildSphere(const Header* header, Node*** nodes);
double dist(int x1, int x2, int y1, int y2, int z1, int z2);
void buildCuboid(const Header* header, Node*** nodes);
char showOpts();
Node*** alloc_nodes(const Header* header);
void free_nodes(const Header* header, Node*** nodes);
void write_dwm_file(const char* filename, const Header* header, const Node*** nodes);

//node types
#define STD_NODE ' '
#define SRC_NODE 'S'
#define RCVR_NODE 'R'
#define RHO_0 'A'
#define RHO_01 'B'
#define RHO_02 'C'
#define RHO_03 'D'
#define RHO_04 'E'
#define RHO_05 'F'
#define RHO_06 'G'
#define RHO_07 'H'
#define RHO_08 'I'
#define RHO_09 'J'
#define RHO_091 '1'
#define RHO_092 '2'
#define RHO_093 '3'
#define RHO_094 '4'
#define RHO_095 '5'
#define RHO_096 '6'
#define RHO_097 '7'
#define RHO_098 '8'
#define RHO_099 '9'
#define RHO_1 'Z'

//room customization
#define C_SPHERE 'S'
#define C_CUBOID 'C'
#define C_SRC 's'
#define C_RCVR 'r'
#define C_QUIT 'q'