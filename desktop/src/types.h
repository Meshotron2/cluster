// types.h : Include file for standard system include files,
// or project specific include files.

#pragma once

typedef struct Node {
	char type;
} Node;

typedef struct DWMHeader {
	int x;
	int y;
	int z;
	int frequency;
} Header;