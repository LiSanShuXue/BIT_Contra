#include"player.h"
#include"stdlib.h"
player initPlayer(int atk_num, int hp_num, int lives_num)
{
	player ryu = { 10,200,0,0,atk_num,hp_num,lives_num };

	return ryu;
}