#ifndef PLAYER_H
#define PLAYER_H
#include "Furniture.h"
#include "LevelCl.h"

	class Player: public Furniture
	{
	public:
		float dx, dy, speed;
		int direction;
		bool isMove, isSelect;

		Player(String F, float X, float Y, float W, float H, float pX, float pY, Level &lev);
		~Player();
		void control(float time);
		void Update(float time);
		void checkCollisionWithMap(float Dx, float Dy);
};


#endif 