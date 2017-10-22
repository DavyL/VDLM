#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "draw.h"



int main(int argc, char **argv){
	
	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n",
			SDL_GetError());
		return -1;
	}

	{
		/* Création de la fenêtre */
		SDL_Window *pWindow = NULL;
		pWindow =
		    SDL_CreateWindow("Ma première application SDL2",
				     SDL_WINDOWPOS_UNDEFINED,
				     SDL_WINDOWPOS_UNDEFINED, S_WIDTH, S_HEIGHT,
				     SDL_WINDOW_SHOWN);

		if (pWindow) {
			SDL_Renderer * renderer = SDL_CreateRenderer( pWindow, -1, 0);
			SDL_Texture * texture = SDL_CreateTexture(renderer,
					        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, S_WIDTH, S_HEIGHT);	//Create texture for pixel drawing
			SCoord coordinates;	
			SCoord * backup = malloc(sizeof(SCoord));

			srand(time(NULL));
			
			SColor color = randColor();				
			SColor white;
			white.r = white.g = white.b = 255;
			fillScreen(renderer, coordinates, color);			
			
			drawLine(renderer, coordinates, S_WIDTH/2, S_HEIGHT/2, S_WIDTH/4, S_HEIGHT/4);
		 	drawCircle(renderer, coordinates, white, S_WIDTH/2, S_HEIGHT/2, 42);
			drawEllipse(renderer, coordinates, white , S_WIDTH/2, S_HEIGHT/2, 42, 69);			

			SDL_Delay(10000);

			SDL_DestroyTexture(texture);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(pWindow);
		} else {
			fprintf(stderr,
				"Erreur de création de la fenêtre: %s\n",
				SDL_GetError());
		}
	}

	SDL_Quit();

	return 0;
}

//Colors the whole screen with the color, if color contains only -1, the screen will be colored randomly
//returns a random color
SColor randColor( ){
	SColor color;
	color.r = rand()%255;
	color.g = rand()%255;
	color.b = rand()%255;
	
	return color;
}


