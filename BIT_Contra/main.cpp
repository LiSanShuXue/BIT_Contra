#include <SDL.h>
#include<stdio.h>
#include<SDL_image.h>
#include "graphics.h"
#include"player.h"
#include"timing.h"
SDL_Window* window;
SDL_Renderer* render;
SDL_Renderer* bgrender;
SDL_Texture* texture;
SDL_Texture* ptexture;
SDL_Renderer* chrender;
SDL_Event event;
int gameRunning;
int framerate;
int initGame();
int quitGame();
int frameNum;

int attackNum;
void printMap();
int mapMatrix[MATRIX_WIDTH][MATRIX_HEIGHT];
player ryu;
int main(int argv, char* args[])
{
	initGame();
	mapMatrix[0][0] = 2;
	mapMatrix[0][1] = 2;
	mapMatrix[ryu.x][ryu.y] = 1;
	printMap();
	
	while (gameRunning)
	{
		frameNum = (frameNum + 1) % 100000;
		while (SDL_PollEvent(&event)!=0)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				gameRunning = 0;
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				ryu.dx = 1;
			}
			else if (event.key.keysym.sym == SDLK_a)
			{
				ryu.dx = -1;
			}
			if (event.key.keysym.sym == SDLK_j)
			{
				//drawAttack();
			}
			if (event.type == SDL_KEYUP)
			{
				ryu.dx = 0;
				ryu.atk = 1;
			}

		}
		ryu.x += ryu.dx*3;
		if (ryu.x >= 1200)
			ryu.x = 1200;
		SDL_RenderClear(render);
		renderMap(render, texture);
		SDL_RenderPresent(render);
		trim_speed();
	}
	quitGame();
	return 0;
}

int initGame()
{
	framerate = 60;
	if (initSDL() < 0)
		return 0;
	if (!init_timer(framerate))
	{
		printf("帧率计数器错误\n");
		return 0;
	}
	ryu = initPlayer(1, 10, 1);
	if (&ryu == NULL)
	{
		printf("创建角色失败\n");
		return 0;
	}
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