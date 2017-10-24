
#ifndef DRAW_H
#define DRAW_H

#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int fill_screen(SDL_Renderer * aRenderer, SCoord  coordinates, SColor color);
int average_grid(SDL_Renderer * aRenderer, SCoord coordinates, SCoord backup);
int draw_line(SDL_Renderer * aRenderer, SCoord coordinates, int xa, int ya, int xb, int yb);
int draw_circle(SDL_Renderer * aRenderer, SCoord coordinates, SColor color ,int x, int y, int radius);
int draw_ellipse(SDL_Renderer * aRenderer, SCoord coordinates, SColor color, int xc, int yc, int width, int height);
#endif
