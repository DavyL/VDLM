#include "draw.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

int fillScreen(SDL_Renderer * aRenderer, SCoord coordinates, SColor color)
{
	int x;
	int y;
	int isColor;
	SColor toPrint;
	if (color.r == -1 && color.g == -1 && color.b == -1) {
		isColor = 0;
	} else {
		toPrint.r = color.r;
		toPrint.g = color.g;
		toPrint.b = color.b;
	}
	for (x = 0; x < S_WIDTH; x++) {
		for (y = 0; y < S_HEIGHT; y++) {
			if (!isColor) {
				toPrint = randColor();
			}
			coordinates[x][y].r = toPrint.r;
			coordinates[x][y].g = toPrint.g;
			coordinates[x][y].b = toPrint.b;

			SDL_SetRenderDrawColor(aRenderer, coordinates[x][y].r,
					       coordinates[x][y].g,
					       coordinates[x][y].b, 255);
			SDL_RenderDrawPoint(aRenderer, x, y);
		}
	}
	SDL_RenderPresent(aRenderer);

}

//Draws a line between (xa, ya) and (xb, yb)
int drawLine(SDL_Renderer * aRenderer, SCoord coordinates, int xa, int ya,
	     int xb, int yb)
{

	int x;
	SDL_SetRenderDrawColor(aRenderer, 255, 255, 255, 255);

	int slope = (xb - xa) / (yb - ya);
	int dist = abs(xb - xa);

	for (x = 0; x < dist; x++) {
		SDL_RenderDrawPoint(aRenderer, xa - x,
				    ya - x * (xb - xa) / (yb - ya));
	}
	SDL_RenderPresent(aRenderer);
}

//Each coordintes takes as color the medium value of colors around
int averageGrid(SDL_Renderer * aRenderer, SCoord coordinates, SCoord backup)
{

	int x;
	int y;
	for (x = 0; x < S_WIDTH; x++) {
		for (y = 0; y < S_HEIGHT; y++) {
			backup[x][y].r = coordinates[x][y].r;
			backup[x][y].g = coordinates[x][y].g;
			backup[x][y].b = coordinates[x][y].b;
		}
	}
	for (x = 0; x < S_WIDTH; x++) {
		for (y = 0; y < S_HEIGHT; y++) {
			coordinates[x][y].r =
			    (backup[(x + S_WIDTH - 1) % S_WIDTH][y].r +
			     backup[(x + S_WIDTH + 1) % S_WIDTH][y].r +
			     backup[x][y].r +
			     backup[x][(y + S_HEIGHT - 1) % S_HEIGHT].r +
			     backup[x][(y + S_HEIGHT + 1) % S_HEIGHT].r)
			    / 5;
			coordinates[x][y].g =
			    (backup[(x + S_WIDTH - 1) % S_WIDTH][y].g +
			     backup[(x + S_WIDTH + 1) % S_WIDTH][y].g +
			     backup[x][y].g +
			     backup[x][(y + S_HEIGHT - 1) % S_HEIGHT].g +
			     backup[x][(y + S_HEIGHT + 1) % S_HEIGHT].g)
			    / 5;
			coordinates[x][y].b =
			    (backup[(x + S_WIDTH - 1) % S_WIDTH][y].b +
			     backup[(x + S_WIDTH + 1) % S_WIDTH][y].b +
			     backup[x][y].b +
			     backup[x][(y + S_HEIGHT - 1) % S_HEIGHT].b +
			     backup[x][(y + S_HEIGHT + 1) % S_HEIGHT].b)
			    / 5;

			SDL_SetRenderDrawColor(aRenderer, coordinates[x][y].r,
					       coordinates[x][y].g,
					       coordinates[x][y].b, 255);
			SDL_RenderDrawPoint(aRenderer, x, y);
		}
	}
	SDL_RenderPresent(aRenderer);

}

//Draws a circle with a center (x0, y0)
int drawCircle(SDL_Renderer * aRenderer, SCoord coordinates, SColor color,
	       int x0, int y0, int radius)
{

	SDL_SetRenderDrawColor(aRenderer, color.r, color.g, color.b, 255);

	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y) {
		SDL_RenderDrawPoint(aRenderer, x0 + x, y0 + y);
		SDL_RenderDrawPoint(aRenderer, x0 + y, y0 + x);
		SDL_RenderDrawPoint(aRenderer, x0 - y, y0 + x);
		SDL_RenderDrawPoint(aRenderer, x0 - x, y0 + y);
		SDL_RenderDrawPoint(aRenderer, x0 - x, y0 - y);
		SDL_RenderDrawPoint(aRenderer, x0 - y, y0 - x);
		SDL_RenderDrawPoint(aRenderer, x0 + y, y0 - x);
		SDL_RenderDrawPoint(aRenderer, x0 + x, y0 - y);

		if (err <= 0) {
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0) {
			x--;
			dx += 2;
			err += (-radius << 1) + dx;
		}
	}
	SDL_RenderPresent(aRenderer);
}

int drawEllipse(SDL_Renderer * aRenderer, SCoord coordinates, SColor color,
		int xc, int yc, int width, int height)
{
		SDL_SetRenderDrawColor(aRenderer, color.r, color.g, color.b, 255);
		int a2 = width * width;
		int b2 = height * height;
		int fa2 = 4 * a2, fb2 = 4 * b2;
		int x, y, sigma;

		/* first half */
		for (x = 0, y = height, sigma = 2 * b2 + a2 * (1 - 2 * height);
		     b2 * x <= a2 * y; x++) {
			SDL_RenderDrawPoint(aRenderer, xc + x, yc + y);
			SDL_RenderDrawPoint(aRenderer, xc - x, yc + y);
			SDL_RenderDrawPoint(aRenderer, xc + x, yc - y);
			SDL_RenderDrawPoint(aRenderer, xc - x, yc - y);
			if (sigma >= 0) {
				sigma += fa2 * (1 - y);
				y--;
			}
			sigma += b2 * ((4 * x) + 6);
		}

		/* second half */
		for (x = width, y = 0, sigma = 2 * a2 + b2 * (1 - 2 * width);
		     a2 * y <= b2 * x; y++) {
			SDL_RenderDrawPoint(aRenderer, xc + x, yc + y);
			SDL_RenderDrawPoint(aRenderer, xc - x, yc + y);
			SDL_RenderDrawPoint(aRenderer, xc + x, yc - y);
			SDL_RenderDrawPoint(aRenderer, xc - x, yc - y);
			if (sigma >= 0) {
				sigma += fb2 * (1 - x);
				x--;
			}
			sigma += a2 * ((4 * y) + 6);
		}
	SDL_RenderPresent(aRenderer);
}
