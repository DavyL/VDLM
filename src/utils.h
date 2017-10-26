#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
 
//Size of the window
#define S_WIDTH 10
#define S_HEIGHT 10


//FLAGS for graph direction

#define RIGHT 	0
#define TOP	1
#define LEFT 	2
#define BOTTOM	3


typedef struct Node{
	struct Node * right;
	struct Node * top;
	struct Node * left;
	struct Node * bottom;
	int color;
}Node;

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
}SCoord[S_WIDTH + 1][S_HEIGHT + 1]; //The +1 are needed, both last cell of the array will contain pointers the other side of the lattice

//returns a color with RGB values
SColor rand_color();

//returns p+1 if x<0<p<=x
int mod(int x, int p);

//GRAPH PART

//init_graph() allocates memory for each node
int init_graph(SCoord coordinates);
//create_node() returns a pointer to a node connected to other nodes
Node * create_node( Node * node, Node * right, Node * top, Node * left, Node * bottom);

//add_node() returns a pointer to a newly created node that is at the [direction] of self
Node * add_node(Node * self, int direction);

//fill_graph() fills a graph, isomorphic to some kind of discrete torus, it contains as many nodes
//as there are coordinates
Node * fill_graph(Node * root, SCoord coordinates);


//DRAWING part

//fill_screen fils the screen with the color, if color ==(-1,-1,-1) as values, then coloring will be 
//done with randomly chose colors
int fill_screen(SDL_Renderer * aRenderer, SCoord  coordinates, SColor color);
//Averages the whole grid's color, useless here
int average_grid(SDL_Renderer * aRenderer, SCoord coordinates, SCoord backup);
//Draws a line between (xa,ya) and (xb, yb)
//Note : An SDL_image function exists, it seems to do the same thing
int draw_line(SDL_Renderer * aRenderer, SCoord coordinates, int xa, int ya, int xb, int yb);
//Draws a circle
int draw_circle(SDL_Renderer * aRenderer, SCoord coordinates, SColor color ,int x, int y, int radius);
//Draws an ellipse with semi major axis : width and semi minor axis : height
int draw_ellipse(SDL_Renderer * aRenderer, SCoord coordinates, SColor color, int xc, int yc, int width, int height);
