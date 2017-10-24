#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>

#include "graph.h"

#define S_WIDTH 600
#define S_HEIGHT 600


typedef struct Scolor{
	int r;
	int g;
	int b;
}SColor;

typedef struct Scoord{
	int r;
	int g;
	int b;
	Node * node;
}SCoord[S_WIDTH][S_HEIGHT];

SColor rand_color();


#endif
