#include <iostream>
#include <SDL2/SDL.h>

int main()
{
	SDL_Window *window = SDL_CreateWindow("Test",
										  SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED,
										  800,
										  600,
										  SDL_WINDOW_SHOW);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return 0;
}