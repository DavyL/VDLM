#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define S_WIDTH 720
#define S_HEIGHT 720


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
int fillScreen(SDL_Renderer * aRenderer, SCoord  coordinates, SColor color);
int averageGrid(SDL_Renderer * aRenderer, SCoord coordinates, SCoord backup);
int drawLine(SDL_Renderer * aRenderer, SCoord coordinates, int xa, int ya, int xb, int yb);

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
			
			fillScreen(renderer, coordinates, color);			
			
			drawLine(renderer, coordinates, S_WIDTH/2, S_HEIGHT/2, S_WIDTH/4, S_HEIGHT/4);
			
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
int fillScreen(SDL_Renderer * aRenderer, SCoord  coordinates, SColor color){
	int x;
        int y;
	int isColor;
	SColor toPrint;
	if(color.r == -1 && color.g == -1 && color.b == -1){
		isColor = 0;
	}else{
		toPrint.r = color.r;
		toPrint.g = color.g;
		toPrint.b = color.b;
	}
	for(x = 0; x<S_WIDTH; x++){
		for(y = 0; y < S_HEIGHT; y++){
			if(!isColor){
				toPrint = randColor();
			}
			coordinates[x][y].r = toPrint.r;	
			coordinates[x][y].g = toPrint.g;
			coordinates[x][y].b = toPrint.b;

			SDL_SetRenderDrawColor(aRenderer, coordinates[x][y].r, coordinates[x][y].g, coordinates[x][y].b, 255);	
			SDL_RenderDrawPoint( aRenderer, x, y);
		}	
	}	
	SDL_RenderPresent(aRenderer);

}
//returns a random color
SColor randColor( ){
	SColor color;
	color.r = rand()%255;
	color.g = rand()%255;
	color.b = rand()%255;
	
	return color;
}
int drawLine(SDL_Renderer * aRenderer, SCoord coordinates,int xa,int ya, int xb, int yb){
	
	int x;
	SDL_SetRenderDrawColor(aRenderer, 255, 255, 255, 255);
	
	int slope = (xb-xa)/(yb-ya);
	int dist = abs(xb-xa);
		
	for(x=0; x < dist ; x++){
		SDL_RenderDrawPoint(aRenderer, xa-x, ya - x*(xb-xa)/(yb-ya)); 
	}
	SDL_RenderPresent(aRenderer);	
}
//Each coordintes takes as color the medium value of colors around
int averageGrid(SDL_Renderer * aRenderer, SCoord coordinates, SCoord backup){
	
	int x;
	int y;
	for(x=0; x <S_WIDTH; x ++){
		for(y = 0; y < S_HEIGHT; y++){
			backup[x][y].r = coordinates[x][y].r;
			backup[x][y].g = coordinates[x][y].g;
			backup[x][y].b = coordinates[x][y].b;
		}
	}
	for(x=0; x <S_WIDTH; x ++){
		for(y = 0; y < S_HEIGHT; y++){
			coordinates[x][y].r  = (backup[(x + S_WIDTH - 1)%S_WIDTH][y].r 
						+ backup[(x + S_WIDTH + 1)%S_WIDTH][y].r
						+ backup[x][y].r
						+ backup[x][(y + S_HEIGHT - 1)%S_HEIGHT].r
						+ backup[x][(y + S_HEIGHT + 1)%S_HEIGHT].r)
						/5;
			coordinates[x][y].g  = (backup[(x + S_WIDTH - 1)%S_WIDTH][y].g 
						+ backup[(x + S_WIDTH + 1)%S_WIDTH][y].g
						+ backup[x][y].g
						+ backup[x][(y + S_HEIGHT - 1)%S_HEIGHT].g
						+ backup[x][(y + S_HEIGHT + 1)%S_HEIGHT].g)
						/5;
			coordinates[x][y].b  = (backup[(x + S_WIDTH - 1)%S_WIDTH][y].b 
						+ backup[(x + S_WIDTH + 1)%S_WIDTH][y].b
						+ backup[x][y].b
						+ backup[x][(y + S_HEIGHT - 1)%S_HEIGHT].b
						+ backup[x][(y + S_HEIGHT + 1)%S_HEIGHT].b)
						/5;
			
			SDL_SetRenderDrawColor(aRenderer, coordinates[x][y].r, coordinates[x][y].g, coordinates[x][y].b, 255);	
			SDL_RenderDrawPoint( aRenderer, x, y);
		}
	}	
	SDL_RenderPresent(aRenderer);


}






