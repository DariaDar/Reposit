#include "stdafx.h"
#include "Furniture.h"

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
	}

	Furniture:: ~Furniture()
	{
		printf("Furniture:: ~Furniture()\n");
	}

	
	FloatRect Furniture:: getRect()
	{
		return FloatRect(x, y, w, h);
	}

	void Furniture:: moving(Event &ev, RenderWindow &window, Vector2i pos)
	{
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
				if (ev.type == Event::MouseButtonReleased){
					if (ev.key.code == Mouse::Left){
						isMove = false;
						sprite.setColor(Color::White);
					}
				}

				if (isMove)
				sprite.setPosition(pos.x - dX, pos.y - dY);
	}