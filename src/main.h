#ifndef MAIN_H
#define MAIN_H
#include "stdlib.h"

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
}SCoord[S_WIDTH][S_HEIGHT];

SColor randColor();


#endif
