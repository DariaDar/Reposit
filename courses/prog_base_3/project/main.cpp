 #include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
 using namespace sf;

 //For the first time. Simple realization of basic functions; not the main file

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


	Player:: Player(String F, float X, float Y, float W, float H)
{
	dx = 0;
	dy = 0;
	speed = 0;
	file = F;
	w = W;
	h = H;
	x = X;
	y = Y;
	isMove = false;
	isSelect = false;
	image.loadFromFile("images/" + file);
	image.createMaskFromColor(Color(255,255,255),0);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(x,y,w,h));
	sprite.setOrigin(w / 2, h / 2);

}

	void control(float time)
	{
		static float currentFrame = 0;

		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			direction = 1; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(295 * int(currentFrame), 260, 215,200));
			sprite.move(-0.1 * time, 0);

		}
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			direction = 0; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(290 * int(currentFrame), 490, 210, 200));
			sprite.move(0.1 * time, 0);
		}
		if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			direction = 3; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(290 * int(currentFrame), 735, 150, 210));
			sprite.move(0, -0.1 * time);
		}

		if(Keyboard::isKeyPressed(Keyboard::Down))
		{
			direction = 2; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(290 * int(currentFrame), 20, 130, 230));
			sprite.move(0, 0.1 * time);
		}
	}

	void update(float time)
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

 };



int main()
{

	RenderWindow window(sf::VideoMode(700, 700), "Window");

	Player p("cat_spritesheet_11.png",295, 260 ,210,200);
	p.sprite.setPosition(50,50);

	bool isMove = false;
	float dX = 0, dY = 0;
	float tmpX = 0;
	float tmpY = 0;
	float distance = 0;

	Clock clock;

	while (window.isOpen())
	{
		sf::Event event;

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		Vector2i pixelPos = Mouse::getPosition(window);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

				if (event.type == Event::MouseButtonPressed)
					if (event.key.code == Mouse::Left)
						if (p.sprite.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
						{
							dX = pixelPos.x - p.sprite.getPosition().x;
							dY = pixelPos.y - p.sprite.getPosition().y;
							isMove = true;
							p.isSelect = true;
						}

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
					isMove = false;
					p.sprite.setColor(Color::White);
		}
		if(p.isSelect)
		{
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Right)
				{
					p.isMove = true;
					p.isSelect = false;
					p.sprite.setColor(Color::White);
					tmpX = pixelPos.x;
					tmpY = pixelPos.y;
				}
		}
		if(p.isMove)
		{
			distance = sqrt(pow(tmpX - p.x, 2) - pow(tmpY - p.y, 2));
			if(distance > 2)
			{
				p.x += 0.1 * time * (tmpX - p.x) / distance;
				p.y += 0.1 * time * (tmpY - p.y) / distance;
			}
		}

		if (isMove)
		{
			p.sprite.setColor(Color::Green);
			p.x = pixelPos.x - dX;
			p.y = pixelPos.y - dY;
		}



		p.update(time); //for the firts time

		window.clear();
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}
