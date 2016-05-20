#include "stdafx.h"
#include "object.h"

	Object:: Object(String F, float X, float Y, float W, float H, float pX, float pY)
	{
		file = F;
		x = X; y = Y; w = W; h = H;
		posX = pX; posY = pY;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(x,y,w,h));
		sprite. setOrigin(w / 2, h / 2);
		sprite.setPosition(posX, posY);
	}

	Object:: ~Object()
	{
		printf("Object:: ~Object()\n");
	}

	void Object:: checkBounds(Player player)
	{
		if(sprite.getLocalBounds().intersects(player.sprite.getLocalBounds()))
		{
			if(player.dx > 0 || player.dx < 0)
				player.dx = 0;
		}

	}
