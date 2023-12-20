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

int closeAttack();	//������
int remoteAttack();	//Զ�̹���
int jumpUp();
int jumpDown();
int bloodLoss();
int restoreHP();
int addLives();
int minusLives();
int move();

