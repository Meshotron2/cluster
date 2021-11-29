#pragma once
#include<math.h>
#include"../common/common.h"

int getNodes(int f, int dim, int c);
void customizeRoom(const Header* header, Node*** nodes);
void setReceiver(Node*** nodes);
void setSource(Node*** nodes);
void buildSphere(const Header* header, Node*** nodes);
double dist(int x1, int x2, int y1, int y2, int z1, int z2);
void buildCuboid(const Header* header, Node*** nodes);
char showOpts();

//room customization
#define C_SPHERE 'S'
#define C_CUBOID 'C'
#define C_SRC 's'
#define C_RCVR 'r'
#define C_QUIT 'q'