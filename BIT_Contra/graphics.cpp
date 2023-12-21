#include<SDL.h>
#include<SDL_image.h>
#include "graphics.h"
#include<stdio.h>

int temp = 0;
//mapMatrixµÄÖµ
//0-¿Õ
//1-player
//2-¿é1
SDL_Rect clips[100];
SDL_Rect block;
int runKey=0;
int attackKey = 0;
enum characterStatus
{
	stand,
	moveRight1,
	moveRight2,
	moveRight3,
	sit,
	jump1,
	jump2,
	jump3,
	jump4,
	jump5,
	attack1,
	attack2,
	attack3
};
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
	int imgFlags = IMG_INIT_PNG ;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_IMAGE could not initialize! %s", IMG_GetError());
		return 0;
	}
	loadCharacter("image/ryu2.png");
	texture = loadTexture("image/tb.png");
}
SDL_Texture* loadTexture(const char* filename)
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
	return tmp_texture;
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
					updateRender(render, texture, j * BLOCK_SIZE, i * BLOCK_SIZE);
				}
				else
				{
					updateRender(render, texture, j * BLOCK_SIZE, i * BLOCK_SIZE);
				}
			}
		}
	}
	if (ryu.dx == 0)
	{
		block = { ryu.x, ryu.y, clips[stand].w * 2, clips[stand].h * 2 };
		SDL_RenderCopy(render, ptexture, &clips[stand], &block);

	}
	else if (ryu.dx)
	{
		switch (runKey)
		{
		case 0:
			block = { ryu.x, ryu.y, clips[moveRight1].w * 2, clips[moveRight1].h * 2 };
			SDL_RenderCopy(render, ptexture, &clips[moveRight1], &block);
			if (frameNum % 5 == 0)
				runKey = (runKey + 1) % 3;
			break;
		case 1:
			block = { ryu.x, ryu.y, clips[moveRight2].w * 2, clips[moveRight2].h * 2 };
			SDL_RenderCopy(render, ptexture, &clips[moveRight2], &block);
			if (frameNum % 5 == 0)
				runKey = (runKey + 1) % 3;
			break;
		case 2:
			block = { ryu.x, ryu.y, clips[moveRight3].w * 2, clips[moveRight3].h * 2 };
			SDL_RenderCopy(render, ptexture, &clips[moveRight3], &block);
			if (frameNum % 5 == 0)
				runKey = (runKey + 1) % 3;
			break;
		}
	}
	else if (ryu.dx==-1)
	{
		switch (runKey)
		{
		case 0:
			block = { ryu.x, ryu.y, clips[moveRight1].w * 2, clips[moveRight1].h * 2 };
			SDL_RenderCopy(render, ptexture, &clips[moveRight1], &block);
			if (frameNum % 5 == 0)
				runKey = (runKey + 1) % 3;
			break;
		case 1:
			block = { ryu.x, ryu.y, clips[moveRight2].w * 2, clips[moveRight2].h * 2 };
			SDL_RenderCopy(render, ptexture, &clips[moveRight2], &block);
			if (frameNum % 5 == 0)
				runKey = (runKey + 1) % 3;
			break;
		case 2:
			block = { ryu.x, ryu.y, clips[moveRight3].w * 2, clips[moveRight3].h * 2 };
			SDL_RenderCopy(render, ptexture, &clips[moveRight3], &block);
			if (frameNum % 5 == 0)
				runKey = (runKey + 1) % 3;
			break;
		}
	}
	return 1;
}

int loadCharacter(const char* filename)
{
	ptexture = loadTexture(filename);

	clips[stand].x = 3;		clips[stand].y = 19;	clips[stand].w = 22;	clips[stand].h = 36;
	clips[moveRight1].x = 38; clips[moveRight1].y = 19; clips[moveRight1].w = 22;	clips[moveRight1].h = 36;
	clips[moveRight2].x = 64; clips[moveRight2].y = 19; clips[moveRight2].w = 22;	clips[moveRight2].h = 36;
	clips[moveRight3].x = 91; clips[moveRight3].y = 19; clips[moveRight3].w = 22;	clips[moveRight3].h = 36;
	clips[attack1].x = 124;	clips[attack1].y = 19; clips[attack1].w = 22;	clips[attack1].h = 36;
	clips[attack2].x = 150;	clips[attack2].y = 19; clips[attack2].w = 41;	clips[attack2].h = 36;
	clips[attack3].x = 193;	clips[attack3].y = 19; clips[attack3].w = 30;	clips[attack3].h = 36;
	return 1;
}