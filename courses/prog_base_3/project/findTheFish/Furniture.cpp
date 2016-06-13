#include "stdafx.h"
#include "Furniture.h"
#include "LevelCl.h"


	Furniture::Furniture(String F, float X, float Y, float W, float H, float pX, float pY, int t)
	{
		x = pX; y = pY; w = W; h = H;
		posX = pX; posY = pY;
		image.loadFromFile("images/" + F);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect((int)X,(int)Y,(int)w,(int)h));
		sprite. setOrigin(w / 2, h / 2);
		sprite.setPosition(posX, posY);
		isSelected = false;
		isMove = false;
		isPlayed = false;
		isInserect = false;
		dX = 0;
		dY = 0;
		f.cb_fn = NULL;
		f.sub = NULL;
		type = t;
	}

	Furniture:: ~Furniture()
	{
		printf("Furniture:: ~Furniture()\n");
	}

	
	FloatRect Furniture:: getRect()
	{
		return FloatRect(x, y, w, h);
	}

	void Furniture:: setSub(void * sub, cb_fn foo)
	{
		f.sub = sub;
		f.cb_fn = foo;
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
				 isPlayed = true; isInserect = true;
			}
				
			if (ev.type == Event::MouseButtonReleased) {
				if (ev.key.code == Mouse::Left){
					isMove = false;
				}
			}

			if (isMove)
				sprite.setPosition(pos.x - dX, pos.y - dY);
	}

	void Furniture:: intersect(String str, Level &lvl)
	{
		Object ob = lvl.GetObject(str);
		if(sprite.getGlobalBounds().intersects(ob.rect))
			{
				 isPlayed = true; isInserect = true;
			}

	}

	void Furniture:: move(Vector2i pos)
	{
		if (isMove) {
			x = pos.x-dX;
			y = pos.y-dY;
			sprite.setPosition(pos.x - dX, pos.y - dY);
		}
	}

	void Furniture:: trueMove(Vector2i pos)
	{
		if (sprite.getGlobalBounds().contains(pos.x, pos.y))
		{
			dX = pos.x - sprite.getPosition().x;
			dY = pos.y - sprite.getPosition().y;
			isMove = true;				
		}
	}

	void Furniture:: falling(Event &ev, RenderWindow &window, Vector2i pos, Level &lvl, float time)
	{
		static float tmpX = 0; 
		static float tmpY = 0;
		static float distance = 0;
		isSelected = true;
		printf("Selected");

		if(isSelected)
		{
			isMove = true;
			isSelected = false;

			tmpX = 430;
			tmpY = 430;
		}
		if(isMove)
		{
			distance = sqrt(pow(tmpX - x, 2) + pow(tmpY - y, 2));
			if(distance > 2)
			{
				x +=(float) 0.1 * time * (tmpX - x) / distance;
				y += (float)0.1 * time * (tmpY - y) / distance;
				sprite.setPosition(x, y);
			}
			else
			{
				isMove = false;
			}
		}

	}

	int Furniture:: clickedThings(Vector2i pos)
	{
		if(isPlayed == true)
		{
			int state = 0;
			static int cnt = 0;
			if(sprite.getGlobalBounds().contains(pos.x, pos.y))
			{
				if(cnt % 2 == 0)
				{
					state = 2; cnt++;
					printf("cnt++ %i", cnt);
				}
				else
				{
					state = 1; cnt--;
					printf("cnt-- %i", cnt);
				}
			}
			return state;
		}
		else
			return -1;

	}