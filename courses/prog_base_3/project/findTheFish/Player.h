#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Audio.hpp>
#include "Furniture.h"
#include "LevelCl.h"

	class Player: public Furniture
	{
	public:
		float dx, dy, speed;
		int direction;
		bool isMove, isSelect, wrongPlace;
		int room;

		Player(String F, Level &lev, float X, float Y, float W, float H, float pX, float pY, int t);
		~Player();
		void control(float time);
		void Update(float time);
		void checkCollisionWithMap(float Dx, float Dy);
};


#endif 