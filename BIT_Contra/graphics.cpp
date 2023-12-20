#include<SDL.h>
#include<SDL_image.h>
#include "graphics.h"
#include<stdio.h>

int temp = 0;
//mapMatrixµÄÖµ
//0-¿Õ
//1-player
//2-¿é1

int initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL init failed. %s",SDL_GetError());
		return 0;
	}
	window = SDL_CreateWindow("BIT_CONTRA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (window == NULL)
	{
		printf("create window failed. %s", SDL_GetError());
		return 0;
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	bgrender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	chrender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_IMAGE could not initialize! %s", IMG_GetError());
		return 0;
	}
}
int loadTexture(const char* filename)
{
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == NULL)
	{
		printf("load PNG failed. %s\n", IMG_GetError());
		return NULL;
	}
	SDL_Texture* tmp_texture = SDL_CreateTextureFromSurface(render, surface);
	if (tmp_texture == NULL)
	{
		printf("create texture failed. %s\n", SDL_GetError());
		return NULL;
	}
	SDL_FreeSurface(surface);
	texture = tmp_texture;
	return 1;
}

int setRenderer(const char* filename, int x, int y, int width, int height)
{
	SDL_Rect destinationRect = { x,y,width,height };
	SDL_RenderCopy(render, texture, NULL, &destinationRect);
	return 1;
}

int updateRender(SDL_Renderer* renderer, SDL_Texture* tmp_texture, int x, int y)
{
	SDL_Rect destRect = { x,y,BLOCK_SIZE,BLOCK_SIZE };
	SDL_RenderCopy(renderer, tmp_texture, NULL, &destRect);
	return 1;
}

int renderMap(SDL_Renderer* renderer, SDL_Texture* tmp_texture)
{
	for (int i = 0; i < MATRIX_WIDTH; i++)
	{
		for (int j = 0; j < MATRIX_HEIGHT; j++)
		{
			if (mapMatrix[i][j] == 2 )
			{
				if (temp != mapMatrix[i][j])
				{
					loadTexture("image/tb.png");
					updateRender(render, texture, j * BLOCK_SIZE, i * BLOCK_SIZE);
				}
				else
				{
					updateRender(render, texture, j * BLOCK_SIZE, i * BLOCK_SIZE);
				}
			}
			else if (mapMatrix[i][j] == 1)
			{
				if (main_player.dx == 0)
				{
					loadTexture("image/player.png");
				}
			}
		}
	}
	return 1;
}