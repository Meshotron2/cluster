#pragma once
#include<string.h>
#include "../common/common.h"

FILE* getDWMFile();
void getRooms(int* Xg, int* Yg, int* Zg);
void fillNodeMatrix(FILE* file, const Header* header, Node*** nodeMatrix);
Header* getRoomPartitionHeaders(const int Xg, const int Yg, const int Zg);