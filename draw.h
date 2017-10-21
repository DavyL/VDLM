#ifndef DRAW_H
#define DRAW_H

int fillScreen(SDL_Renderer * aRenderer, SCoord  coordinates, SColor color);
int averageGrid(SDL_Renderer * aRenderer, SCoord coordinates, SCoord backup);
int drawLine(SDL_Renderer * aRenderer, SCoord coordinates, int xa, int ya, int xb, int yb);

#endif
