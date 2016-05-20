#include "stdafx.h"
#include "player.h"



	Player:: Player(String F, float X, float Y, float W, float H, float pX, float pY)
{
	dx = 0;
	dy = 0;
	speed = 0;
	file = F;
	w = W;
	h = H;
	x = pX;
	y = pY;
	isMove = false;
	isSelect = false;
	image.loadFromFile("images/" + file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(X,Y,w,h));
	sprite.setOrigin(w / 2, h / 2);
}

	Player:: ~Player()
	{
		printf("Player:: ~Player()");
	}

	void Player:: control(float time)
	{
		static float currentFrame = 1;

		if(Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))
		{
			direction = 1; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(160 * int(currentFrame), 150, 115, 135));
			sprite.move(-0.1 * time, 0);
		}
		if(Keyboard::isKeyPressed(Keyboard::Right)|| (Keyboard::isKeyPressed(Keyboard::D)))
		{
			direction = 0; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(155 * int(currentFrame), 275, 115, 150));
			sprite.move(0.1 * time, 0);
		}
		if(Keyboard::isKeyPressed(Keyboard::Up)|| (Keyboard::isKeyPressed(Keyboard::W)))
		{
			direction = 3; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(160 * int(currentFrame), 430, 75, 160));
			sprite.move(0, -0.1 * time);
		}

		if(Keyboard::isKeyPressed(Keyboard::Down)|| (Keyboard::isKeyPressed(Keyboard::S)))
		{
			direction = 2; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(160 * int(currentFrame), 15, 70, 130));
			sprite.move(0, 0.1 * time);
		}
	}


	void Player:: update(float time)
	{
		control(time);
		switch(direction)
		{
		case 0: //right
			dx = speed;
			dy = 0;
			break;
		case 1: //left
			dx = -speed;
			dy = 0;
			break;
		case 2: //down
			dx = 0;
			dy = speed;
			break;
		case 3: // up
			dx = 0;
			dy = -speed;
			break;
		default:
			break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y);
	}
