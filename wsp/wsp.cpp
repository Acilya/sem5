//============================================================================
// Name        : wsp.cpp
// Author      : Alicja Kapiszka
// Version     :
// Description :
//============================================================================

#include <iostream>
#include <thread>
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void worker()
{
	std::cout << "hello" << std::endl;
}

int main()
{
	std::thread t(worker);
	t.join();
	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}
	window = SDL_CreateWindow("Triangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		std::cout << "SDL_Error while creating a window: " << SDL_GetError() << std::endl;
	}
	else
	{
		screen = SDL_GetWindowSurface(window);
		SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
		SDL_Renderer* Renderer = NULL;
		Renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(Renderer);
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Renderer, 20, 460, 320, 20);
		SDL_RenderDrawLine(Renderer, 620, 460, 320, 20);
		SDL_RenderDrawLine(Renderer, 20, 460, 620, 460);
		SDL_RenderPresent(Renderer);
	}
	SDL_Event event;
	bool running = true;
	while (running)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
