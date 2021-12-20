#pragma once

#include<stdio.h>
#include<stdlib.h>

#include"types.h"
#include"node.h"

int readNodes(Node ***node, Header *h, FILE *inFile); 

void injectSample();

void readSample();

void scatterPass(const Header* h, Node*** ns);

void delayPass(const Header* h, Node*** ns);

void writeExcitation();
	
void fixHeaderEndian(Header*);
