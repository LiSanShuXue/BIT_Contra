#pragma once
#include<SDL.h>
#include<SDL_image.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MATRIX_WIDTH 18
#define MATRIX_HEIGHT 32

extern int entityMatrix[SCREEN_WIDTH][SCREEN_HEIGHT];
extern int mapMatrix[MATRIX_WIDTH][MATRIX_HEIGHT];

bool player_move(int &x, int &y, int offsetx, int offsety) {//返回值为是否落地 true为已落地。
	if (offsetx > 0) {
		if (offsetx > 40) offsetx = 40;
		if (offsety == 0) {
			int ii = (x + 32) / 40 + 1;
			int dx = ii * 40 - x - 33;
			int j = y / 40;
			if (offsetx > dx && (mapMatrix[ii][j] || mapMatrix[ii][j + 1] || mapMatrix[ii][(y + 64) / 40])) {
				x += dx;
				return false;
			}
			x += offsetx;
			return false;
		}
		if (offsety > 0) {
			if (offsety > 40) offsety = 40;
			int ii = (x + 32) / 40 + 1;
			int jj = (y + 64) / 40 + 1;
			int dx = ii * 40 - x - 33;
			int dy = jj * 40 - y - 65;
			int detay = offsety * dx / offsetx;
			int detax = offsetx * dy / offsety;
			int j = (y + detay) / 40;
			if (offsetx * dy >= offsety * dx) {
				if (offsetx > dx) {
					if (mapMatrix[ii][j] || mapMatrix[ii][j + 1] || mapMatrix[ii][(y + 64 + detay) / 40]) {
						x += dx;
						if (offsety > dy && mapMatrix[ii - 1][jj]) {
							y += dy;
							return true;
						}
						y += offsety;
						return false;
					}
					if (offsety > dy && (mapMatrix[(x + detax) / 40][jj] || mapMatrix[(x + 32 + detax) / 40][jj])) {
							y += dy;
							x += detax;
							return true;
					}
				}
				x += offsetx;
				y += offsety;
				return false;
			}
			if (offsety > dy) {
				if (mapMatrix[(x + detax) / 40][jj] || mapMatrix[(x + 32 + detax) / 40][jj]) {
					y += dy;
					x += detax;
					return true;
				}
				if (offsetx > dx && (mapMatrix[ii][j] || mapMatrix[ii][j + 1] || mapMatrix[ii][(y + 64 + detay) / 40])) {
						x += dx;
						y += offsety;
						return false;
				}
			}
			x += offsetx;
			y += offsety;
			return false;
		}
		if (offsety < -40) offsety = -40;
		int ii = (x + 32) / 40 + 1;
		int jj = y / 40;
		int dx = ii * 40 - x - 33;
		int dy = jj * 40 - y;
		int detay = offsety * dx / offsetx;
		int detax = offsetx * dy / offsety;
		int j = (y + detay) / 40;
		if (offsetx * dy <= offsety * dx) {
			if (offsetx > dx) {
				if (mapMatrix[ii][j] || mapMatrix[ii][j + 1] || mapMatrix[ii][(y + 64 + detay) / 40]) {
					x += dx;
					if (offsety < dy && mapMatrix[ii - 1][jj - 1]) {
						y += dy;
						return false;
					}
					y += offsety;
					return false;
				}
				if (offsety < dy && (mapMatrix[(x + detax) / 40][jj - 1] || mapMatrix[(x + 32 + detax) / 40][jj - 1])) {
					y += dy;
					x += offsetx;
					return false;
				}
			}
			x += offsetx;
			y += offsety;
			return false;
		}
		if (offsety < dy) {
			if (mapMatrix[(x + detax) / 40][jj - 1] || mapMatrix[(x + 32 + detax) / 40][jj - 1]) {
				y += dy;
				x += offsetx;
				return false;
			}
			if (offsetx > dx && (mapMatrix[ii][j] || mapMatrix[ii][j + 1] || mapMatrix[ii][(y + 64 + detay) / 40])) {
				x += dx;
				y += offsety;
				return false;
			}
		}
		x += offsetx;
		y += offsety;
		return false;
	}
	if (offsetx == 0) {
		if (offsety > 0) {
			if (offsety > 40) offsety = 40;
			int jj = (y + 64) / 40 + 1;
			int dy = jj * 40 - y - 65;
			if (offsety > dy && (mapMatrix[x / 40][jj] || mapMatrix[(x + 32) / 40][jj])) {
				y += dy;
				return true;
			}
			y += offsety;
		}
		if (offsety < -40) offsety = -40;
		int jj = y / 40;
		int dy = jj * 40 - y;
		if (offsety < dy && (mapMatrix[x / 40][jj - 1] || mapMatrix[(x + 32) / 40][jj - 1])) {
			y += dy;
			return false;
		}
	}
	if (offsetx < -40) offsetx = -40;
	if (offsety == 0) {
		int ii = x / 40;
		int dx = ii * 40 - x;
		int j = y / 40;
		if (offsetx < dx && (mapMatrix[ii - 1][j] || mapMatrix[ii - 1][j + 1] || mapMatrix[ii - 1][(y + 64) / 40])) {
			x += dx;
			return false;
		}
	}
	if (offsety > 0) {
		if (offsety > 40)offsety = 40;
		int ii = x / 40;
		int jj = (y + 64) / 40 + 1;
		int dx = ii * 40 - x;
		int dy = jj * 40 - y - 65;
		int detay = offsety * dx / offsetx;
		int detax = offsetx * dy / offsety;
		int j = (y + detay) / 40;
		if (offsetx * dy <= offsety * dx) {
			if (offsetx < dx) {
				if (mapMatrix[ii - 1][j] || mapMatrix[ii - 1][j + 1] || mapMatrix[ii - 1][(y + 64 + detay) / 40]) {
					x += dx;
					if (offsety > dy && mapMatrix[ii][jj]) {
						y += dy;
						return true;
					}
					y+= offsety;
					return false;
				}
				if (offsety > dy && (mapMatrix[(x + detax) / 40][jj] || mapMatrix[(x + 32 + detax) / 40][jj])) {
					y += dy;
					x += detax;
					return true;
				}
			}
			x += offsetx;
			y += offsety;
			return false;
		}
		if (offsety > dy) {
			if (mapMatrix[(x + detax) / 40][jj] || mapMatrix[(x + 32 + detax) / 40][jj]) {
				y += dy;
				x += detax;
				return true;
			}
			if (offsetx < dx && (mapMatrix[ii - 1][j] || mapMatrix[ii - 1][j + 1] || mapMatrix[ii - 1][(y + 64 + detay) / 40])) {
				x += dx;
				y += offsety;
				return false;
			}
		}
		x += offsetx;
		y += offsety;
		return false;
	}
	if (offsety < -40) offsety = -40;
	int ii = x / 40;
	int jj = y / 40;
	int dx = ii * 40 - x;
	int dy = jj * 40 - y;
	int detay = offsety * dx / offsetx;
	int detax = offsetx * dy / offsety;
	int j = (y + detay) / 40;
	if (offsetx * dy >= offsety * dx) {
		if (offsetx < dx) {
			if (mapMatrix[ii - 1][j] || mapMatrix[ii - 1][j + 1] || mapMatrix[ii - 1][(y + 64 + detay) / 40]) {
				x += dx;
				if (offsety < dy && mapMatrix[ii][jj - 1]) {
					y += dy;
					return false;
				}
				y += offsety;
				return false;
			}
			if (offsety < dy && (mapMatrix[(x + detax) / 40][jj - 1] || mapMatrix[(x + 32 + detax) / 40][jj - 1])) {
				y += dy;
				x += offsetx;
				return false;
			}
		}
		x += offsetx;
		y += offsety;
		return false;
	}
	if (offsety < dy) {
		if (mapMatrix[(x + detax) / 40][jj - 1] || mapMatrix[(x + 32 + detax) / 40][jj - 1]) {
			y += dy;
			x += offsetx;
			return false;
		}
		if (offsetx < dx && (mapMatrix[ii - 1][j] || mapMatrix[ii - 1][j + 1] || mapMatrix[ii - 1][(y + 64 + detay) / 40])) {
		if (offsetx < dx && (mapMatrix[ii - 1][j] || mapMatrix[ii - 1][j + 1] || mapMatrix[ii - 1][(y + 64 + detay) / 40])) {
			x += dx;
			y += offsety;
			return false;
		}
	}
	x += offsetx;
	y += offsety;
	return false;
}