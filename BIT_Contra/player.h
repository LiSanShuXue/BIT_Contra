#pragma once

typedef struct Player
{
	int x;
	int y;
	int dx;
	int dy;
	int atk;
	int hp;
	int lives;
}player;

int closeAttack();	//½üÉí¹¥»÷
int remoteAttack();	//Ô¶³Ì¹¥»÷
int jumpUp();
int jumpDown();
int bloodLoss();
int restoreHP();
int addLives();
int minusLives();
int move();

