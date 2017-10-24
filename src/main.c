#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

int main(int argc, char **argv){
		
	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n",
			SDL_GetError());
		return -1;
	}
	//IMG_Init(IMG_INIT_JPG);

	{
		/* Création de la fenêtre */
		SDL_Window *pWindow = NULL;
		pWindow =
		    SDL_CreateWindow("VDLM",
				     SDL_WINDOWPOS_UNDEFINED,
				     SDL_WINDOWPOS_UNDEFINED, S_WIDTH, S_HEIGHT,
				     SDL_WINDOW_SHOWN);

		if (pWindow) {
			IMG_Init(IMG_INIT_JPG);

			SDL_Renderer * renderer = SDL_CreateRenderer( pWindow, -1, 0);
		//	SDL_Texture * texture = SDL_CreateTexture(renderer,
		//			        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, S_WIDTH, S_HEIGHT);	//Create texture for pixel drawing
			SDL_Surface * image = IMG_Load("mona.jpg");
			if(image == NULL){
				printf("Couldn't load image using IMG_Load()\n");
				return -1;
			}
			SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
			SCoord coordinates;	
			SCoord * backup = malloc(sizeof(SCoord));

			SDL_RenderCopy(renderer, texture, NULL, NULL);	
			SDL_RenderPresent(renderer);

			Node * root;
			fill_graph(root, coordinates);



			srand(time(NULL));
			
			/*SColor color = randColor();				
			SColor white;
			white.r = white.g = white.b = 255;
			fill_screen(renderer, coordinates, color);			
			*/
			SColor white; 
			white.r = white.g = white.b = 255;
			draw_line(renderer, coordinates, S_WIDTH/2, S_HEIGHT/2, S_WIDTH/4, S_HEIGHT/4);
		 	draw_circle(renderer, coordinates, white, S_WIDTH/2, S_HEIGHT/2, 42);
			draw_ellipse(renderer, coordinates, white , S_WIDTH/2, S_HEIGHT/2, 42, 69);			

			SDL_Delay(10000);

			SDL_DestroyTexture(texture);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(pWindow);
			SDL_FreeSurface(image);
			free(backup);
		} else {
			fprintf(stderr,
				"Erreur de création de la fenêtre: %s\n",
				SDL_GetError());
		}
		
	}
	IMG_Quit();
	SDL_Quit();
	
	
	return 0;
}

//Colors the whole screen with the color, if color contains only -1, the screen will be colored randomly
//returns a random color
SColor rand_color( ){
	SColor color;
	color.r = rand()%255;
	color.g = rand()%255;
	color.b = rand()%255;
	
	return color;
}



