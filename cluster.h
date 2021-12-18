#pragma once

#include<stdio.h>
#include<stdlib.h>

#include"types.h"
#include"node.h"

int readNodes(Node ***node, Header *h, FILE *inFile); 

void injectSample();

void readSample();

void scatter();

void delay();

void writeExcitation();
	
void fixHeaderEndian(Header*);
