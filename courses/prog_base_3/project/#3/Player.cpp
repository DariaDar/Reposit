#include "stdafx.h"
#include "Player.h"
#include "Furniture.h"
#include <SFML/Graphics.hpp> 



	Player:: Player(String F, float X, float Y, float W, float H, float pX, float pY, Level &lev): Furniture(F, X,  Y, W,  H,  pX, pY)
{
	obj = lev.GetAllObjects();
	dx = 0;
	dy = 0;
	speed = 0;
	isMove = false;
	isSelect = false;
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

	void Player:: checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)
		  if (getRect().intersects(obj[i].rect))
		  {
			  if (obj[i].name == "bound" || obj[i].name == "bed" || obj[i].name == "cabinet")
			  {
				 if (Dy>0)
				 { 
					 y = obj[i].rect.top - h;  
					 dy = 0; 
				 }
				 if (Dy<0)
				 { 
					 y = obj[i].rect.top + obj[i].rect.height;   
					 dy = 0; 
				 }
				 if (Dx>0)
				 { 
					 x = obj[i].rect.left - w; 
				 }
				 if (Dx<0)
				 {
					 x = obj[i].rect.left + obj[i].rect.width;
				 }
			  }
		   }
	}


	void Player:: Update(float time)
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
	 