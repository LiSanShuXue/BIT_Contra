#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include"player.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MATRIX_WIDTH 18
#define MATRIX_HEIGHT 32
#define BLOCK_SIZE 40
extern SDL_Window* window;
extern SDL_Renderer* bgrender;
extern SDL_Renderer* render;
extern SDL_Renderer* chrender;
extern SDL_Texture* texture;

extern int mapMatrix[MATRIX_WIDTH][MATRIX_HEIGHT];
extern player main_player;

int initSDL();
int loadTexture(const char* filename);
int setRenderer(const char* filename, int x, int y, int width, int height);
int updateRender(SDL_Renderer* renderer, SDL_Texture* tmp_texture, int x, int y);
int renderMap(SDL_Renderer* renderer, SDL_Texture* tmp_texture);