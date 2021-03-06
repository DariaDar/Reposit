#include "stdafx.h"
#include "Furniture.h"
#include "LevelCl.h"


	Furniture::Furniture(String F, float X, float Y, float W, float H, float pX, float pY)
	{
		x = X; y = Y; w = W; h = H;
		posX = pX; posY = pY;
		image.loadFromFile("images/" + F);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(x,y,w,h));
		sprite. setOrigin(w / 2, h / 2);
		sprite.setPosition(posX, posY);
		isSelected = false;
		isMove = false;
		isPlayed = false;
	}

	Furniture:: ~Furniture()
	{
		printf("Furniture:: ~Furniture()\n");
	}

	
	FloatRect Furniture:: getRect()
	{
		return FloatRect(x, y, w, h);
	}

	void Furniture:: moving(Event &ev, RenderWindow &window, Vector2i pos, String str, Level &lvl)
	{
		Object ob = lvl.GetObject(str);
		static float dX = 0;
		static float dY = 0;
		if (ev.type == Event::MouseButtonPressed){
			if (ev.key.code == Mouse::Left){
				if (sprite.getGlobalBounds().contains(pos.x, pos.y))
				{
					dX = pos.x - sprite.getPosition().x;
					dY = pos.y - sprite.getPosition().y;
					isMove = true;
				}
			}
		}
				
			
			if(sprite.getGlobalBounds().intersects(ob.rect))
			{
				 isPlayed = true;
			}
				
				if (ev.type == Event::MouseButtonReleased){
					if (ev.key.code == Mouse::Left){
						isMove = false;
						sprite.setColor(Color::White);
					}
				}


				if (isMove)
				sprite.setPosition(pos.x - dX, pos.y - dY);
	}

	void Furniture:: falling(Event &ev, RenderWindow &window, Vector2i pos, Level &lvl, float time)
	{
		static float tmpX = 0; 
		static float tmpY = 0;
		static float distance = 0;
		Time delayTime = milliseconds(1);
		Time delayTime2 = seconds(4);
		isSelected = true;
		printf("Selected");

		if(isSelected)
		{
			isMove = true;
			isSelected = false;

			tmpX = 430;
			tmpY = 430;
		}
		while(isMove)
		{
			distance = sqrt(pow(tmpX - x, 2) - pow(tmpY - y, 2));
			if(distance > 2)
			{
				x += 0.1 * time * (tmpX - x) / distance;
				y += 0.1 * time * (tmpY - y) / distance;
				sprite.setPosition(x, y);
				sleep(delayTime);
			}
			else
			{
				isMove = false;
				sleep(delayTime2);
			}
		}

	}

