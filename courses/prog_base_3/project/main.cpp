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

}

	void control(float time)
	{
		static float currentFrame = 0;

		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(295 * int(currentFrame), 260, 215,200));
			sprite.move(-0.1 * time, 0);

		}
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(290 * int(currentFrame), 490, 210, 200));
			sprite.move(0.1 * time, 0);
		}
	}

 };



int main()
{

	RenderWindow window(sf::VideoMode(700, 700), "Window");

	Player p("cat_spritesheet_11.png",295, 260 ,210,200);
	p.sprite.setPosition(50,50);

	bool isMove = false;
	float dX = 0, dY = 0;

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
						}

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
					isMove = false;
					p.sprite.setColor(Color::White);
		}
		if (isMove)
		{
			p.sprite.setColor(Color::Green);
			p.sprite.setPosition(pixelPos.x - dX,pixelPos.y - dY);
		}



		p.control(time); //for the first time

		window.clear();
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}
