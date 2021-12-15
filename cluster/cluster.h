#pragma once

#include<stdio.h>
#include<stdlib.h>

#include"types.h"

int readNode(int ***node, Header *h, FILE *inFile); 

void injectSample();

void readSample();

void scatter();

void delay();

void writeExcitation();
