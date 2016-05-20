#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
	using namespace sf;

	class Player
	{
	public:
		float x, y, w, h, dx, dy, speed;
		int direction;
		bool isMove, isSelect;
		String file;
		Image image;
		Texture texture;
		Sprite sprite;


		Player(String F, float X, float Y, float W, float H, float pX, float pY);
		~Player();
		void control(float time);
		void update(float time, String map[], int mHeight, int mWeight);
};


#endif
