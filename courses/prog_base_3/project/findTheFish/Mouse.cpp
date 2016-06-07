#include "Mouse.h"

	_Mouse:: _Mouse(String F, Level &lev, float X, float Y, float W, float H, float pX, float pY)
	{
		x = pX; y = pY; w = W; h = H;
		image.loadFromFile("images/" + F);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(X,Y,w,h));
		sprite. setOrigin(w / 2, h / 2);
		obj = lev.GetAllObjects();
		dx = 0;
		dy = 0;
		speed = 0;
		rightPlace = false;
	}

	_Mouse:: ~_Mouse()
	{
		printf("Player:: ~Player()");
	}

	void _Mouse:: control(float time)
	{
		static float currentFrame = 0;

		if(Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))
		{
			direction = 1; speed = 0.1;
			currentFrame += 0.008 * time;
			if(currentFrame > 4)
				currentFrame -= 4;
			sprite.setTextureRect(IntRect(2 * int(currentFrame), 68, 40, 26));
			sprite.move(-0.1 * time, 0);		
		}
		if(Keyboard::isKeyPressed(Keyboard::Right)|| (Keyboard::isKeyPressed(Keyboard::D)))
		{
			direction = 0; speed = 0.1;
			currentFrame += 0.008 * time;
			if(currentFrame > 4)
				currentFrame -= 4;
			sprite.setTextureRect(IntRect(3 * int(currentFrame), 112, 40, 28));
			sprite.move(0.1 * time, 0);	
		}
		if(Keyboard::isKeyPressed(Keyboard::Up)|| (Keyboard::isKeyPressed(Keyboard::W)))
		{
			direction = 3; speed = 0.1;
			currentFrame += 0.008 * time;
			if(currentFrame > 4)
				currentFrame -= 4;
			sprite.setTextureRect(IntRect(2 * int(currentFrame), 160, 31, 27));
			sprite.move(0, -0.1 * time);
		}
		
		if(Keyboard::isKeyPressed(Keyboard::Down)|| (Keyboard::isKeyPressed(Keyboard::S)))
		{
			direction = 2; speed = 0.1;
			currentFrame += 0.008 * time;
			if(currentFrame > 4)
				currentFrame -= 4;
			sprite.setTextureRect(IntRect(2 * int(currentFrame), 21, 32, 25));
			sprite.move(0, 0.1 * time);
		}
	}

	void _Mouse:: checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)
		  if (getRect().intersects(obj[i].rect))
		  {
			if((obj[i].name == "end"))
				rightPlace = true;
			  if (obj[i].name == "bound")
			  {
				 if (Dy > 0)
				 { 
					 y = obj[i].rect.top - h;  
					 dy = 0; 
				 }
				 if (Dy < 0)
				 { 
					 y = obj[i].rect.top + obj[i].rect.height;   
					 dy = 0; 
				 }
				 if (Dx > 0)
				 { 
					 x = obj[i].rect.left - w; 
				 }
				 if (Dx < 0)
				 {
					 x = obj[i].rect.left + obj[i].rect.width;
				 }
			  }
		   }
	}


	void _Mouse:: Update(float time)
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
		checkCollisionWithMap(dx, dy);
	}
	 

	FloatRect _Mouse:: getRect()
	{
		return FloatRect(x, y, w, h);
	}