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