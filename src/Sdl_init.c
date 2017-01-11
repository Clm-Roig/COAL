#include "Sdl_init.h"

SDL_Window *screen;
SDL_Renderer *renderer;
TTF_Font *police;

SDL_Renderer *getrenderer(){
    return renderer;
}
SDL_Window *getwindow(){
    return screen;
}

void init(){
	int screenwidth; int screenheight;
	screenwidth = SCREEN_WIDTH;
	screenheight = SCREEN_HEIGHT;

    screen = SDL_CreateWindow("Coal - Connected ",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,screenwidth, screenheight,SDL_WINDOW_OPENGL|SDL_WINDOW_BORDERLESS);

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);

    if (screen == NULL || renderer == NULL)
    {
        printf("Impossible d'initialiser le mode écran à : %s\n", SDL_GetError());
        exit(1);
    }
	if(TTF_Init() == -1)
	{
    	fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    	exit(EXIT_FAILURE);
	}
	else{
		police=TTF_OpenFont("amarante.ttf", 22);
	}

}

void cleanup(){
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(screen);
    screen = NULL;
	TTF_Quit();

    SDL_Quit();
}
