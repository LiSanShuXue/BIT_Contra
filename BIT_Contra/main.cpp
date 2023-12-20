#include <SDL.h>
#include<stdio.h>
#include<SDL_image.h>
#include "graphics.h"
#include"player.h"
SDL_Window* window;
SDL_Renderer* render;
SDL_Renderer* bgrender;
SDL_Texture* texture;
SDL_Event event;
int gameRunning;
int initGame();
int quitGame();
void printMap();
int mapMatrix[MATRIX_WIDTH][MATRIX_HEIGHT];
player main_player;
int main(int argv, char* args[])
{
	initGame();
	mapMatrix[0][0] = 1;
	mapMatrix[0][1] = 1;
	printMap();
	

	while (gameRunning)
	{
		while (SDL_PollEvent(&event)!=0)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				gameRunning = 0;
			}
		}
		SDL_RenderClear(render);
		renderMap(render, texture);
		SDL_RenderPresent(render);

	}
	quitGame();
	return 0;
}

int initGame()
{
	if (initSDL() < 0)
		return 0;

	gameRunning = 1;
	return 1;
}

int quitGame()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 1;
}

void printMap()
{
	for (int i = 0; i < MATRIX_WIDTH; i++)
	{
		for (int j = 0; j < MATRIX_HEIGHT; j++)
		{
			printf("%d ", mapMatrix[i][j]);
		}
		printf("\n");
	}
}