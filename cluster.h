#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"types.h"
#include"node.h"
void readNodes(Node ***node, Header *h, FILE *inFile); 

void injectSamples(Node** n, const int sourceCount);

void readSamples(const Node** n, float** buf, const int receiverCount, const int iteration);

void scatterPass(const Header* h, Node*** ns);

void delayPass(const Header* h, Node*** ns);

void writeExcitation();
	
void fixHeaderEndian(Header*);
