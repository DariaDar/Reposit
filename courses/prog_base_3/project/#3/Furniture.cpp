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
	}

	Furniture:: ~Furniture()
	{
		printf("Furniture:: ~Furniture()\n");
	}

	
	FloatRect Furniture:: getRect()
	{
		return FloatRect(x, y, w, h);
	}
