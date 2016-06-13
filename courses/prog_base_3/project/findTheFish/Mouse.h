#ifndef MOUSE_H
#define MOUSE_H
#include "Furniture.h"
#include "LevelCl.h"

	class _Mouse
	{
	public:
		float dx, dy, speed;
		int direction;
		Image image;
		Texture texture;
		Sprite sprite;
		float x, y, w, h;
		std::vector<Object> obj;
		bool rightPlace, life;
		int health;

		_Mouse(String F, Level &lev, float X, float Y, float W, float H, float pX, float pY);
		~_Mouse();
		void control(float time);
		void Update(float time);
		void checkCollisionWithMap(float Dx, float Dy);
		FloatRect getRect();
};

#endif