
#ifndef DRAW_H
#define DRAW_H

#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int fillScreen(SDL_Renderer * aRenderer, SCoord  coordinates, SColor color);
int averageGrid(SDL_Renderer * aRenderer, SCoord coordinates, SCoord backup);
int drawLine(SDL_Renderer * aRenderer, SCoord coordinates, int xa, int ya, int xb, int yb);
int drawCircle(SDL_Renderer * aRenderer, SCoord coordinates, SColor color ,int x, int y, int radius);
int drawEllipse(SDL_Renderer * aRenderer, SCoord coordinates, SColor color, int xc, int yc, int width, int height);
#endif
