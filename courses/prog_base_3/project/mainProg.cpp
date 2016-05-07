#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
 using namespace sf;

 #include "stdafx.h"
#include <SFML/Graphics.hpp>
 using namespace sf;

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

	void control(float time)
	{
		static float currentFrame = 0;

		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			direction = 1; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(160 * int(currentFrame), 150, 115, 135));
			sprite.move(-0.1 * time, 0);
		}
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			direction = 0; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(155 * int(currentFrame), 275, 115, 150));
			sprite.move(0.1 * time, 0);
		}
		if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			direction = 3; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(160 * int(currentFrame), 430, 75, 160));
			sprite.move(0, -0.1 * time);
		}

		if(Keyboard::isKeyPressed(Keyboard::Down))
		{
			direction = 2; speed = 0.1;
			currentFrame += 0.004 * time;
			if(currentFrame > 3)
				currentFrame -= 2;
			sprite.setTextureRect(IntRect(160 * int(currentFrame), 15, 70, 130));
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

void menu(RenderWindow &window)
 {
	 Texture menuText1, menuText2, menuText3, menuBackground;
	 menuBackground.loadFromFile("images/menu1.jpg");
	 menuText2.loadFromFile("images/cat.jpg");
	 Sprite menuLoad(menuText2);
	 Sprite menuBg(menuBackground);
	 bool isMenu = 1;
	 int menuNum = 0;
	 menuBg.setPosition(0,0);
	 Music music;
	 music.openFromFile("music/menu.ogg");
	 music.play();

	 Font font;
	 font.loadFromFile("dumb.ttf");
	 Text text("", font, 38); text.setStyle(Text::Bold);
	 Text text2("", font, 38); text2.setStyle(Text::Bold);
	 Text text3("", font, 38); text3.setStyle(Text::Bold);
	 text.setString("New Game");
	 text2.setString("Load");
	 text3.setString("Exit");
	 text.setPosition(485, 410);
	 text2.setPosition(550, 450);
	 text3.setPosition(550,568);


	 while(isMenu)
	 {
		text.setColor(Color(254,150,121));
		text2.setColor(Color(254,150,121));
		text3.setColor(Color(254,150,121));
		menuNum = 0;

		 window.clear(Color(129,181,221));
		 //New Game
		 if(IntRect(500,410,200,60).contains(Mouse::getPosition(window)))
		 {
			 text.setColor(Color(98,198,223));
			 menuNum = 1;
		 }
		 //Load Game
		 if(IntRect(550,488,200,60).contains(Mouse::getPosition(window)))
		 {
			 text2.setColor(Color(98,198,223));
			 menuNum = 2;
		 }
		 //Exit
		 if(IntRect(500,564,200,60).contains(Mouse::getPosition(window)))
		 {
			 text3.setColor(Color(98,198,223));
			 menuNum = 3;
		 }


		if(Mouse::isButtonPressed(Mouse::Left))
		{
			if(menuNum == 1)
			{
				music.stop();
				return;
			}
			if(menuNum == 2)
			{
				window.draw(menuLoad);
				window.display();
				while(!Keyboard::isKeyPressed(Keyboard::Escape))
				{;}
			}
			if(menuNum == 3)
			{
				music.stop();
				window.close();
				isMenu = false;
			}
		}
		 window.draw(menuBg);
		 window.draw(text);
		 window.draw(text2);
		 window.draw(text3);
		 window.display();
	 }
 }

class Object
{
public:
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	float x, y, w, h, posX, posY;

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
};



/*Sprite imageManager(String file, RenderWindow &window)
{
	Texture texture;
	texture.loadFromFile("images/" + file);
	Sprite spr(texture);
	return spr;
}*/



 int main()
 {
	 RenderWindow window(VideoMode(1300,702),"Find the fish", Style::Default);
	 window.setPosition(Vector2i(10,10));
	 menu(window);
	 int cntMeow = 0;


	//>>>>>>>>>>>>>>>>---Load basic image for level1----<<<<<<<<<<<<<<<<<
	Texture texture;
	texture.loadFromFile("images/level1empty.jpg");
	Sprite level(texture);

	//>>>>>>>>>>>>>>>>---Music---<<<<<<<<<<<<<<<<<<<<<<<<<<
	 Music mainSong;
	 mainSong.openFromFile("music/level1.ogg");
	 mainSong.play();
	 mainSong.setLoop(true);
	 mainSong.setVolume(75);

	 //>>>>>>>>>>>>>>>>---Create a cat---<<<<<<<<<<<<<<<<<<<
	 Player p("cat.png", 55, 25, 200, 120, 45, 445);
	 Clock clock;

	 //>>>>>>>>>>>>>>>>---Sounds----<<<<<<<<<<<<<<<<<<<
	SoundBuffer buf1, buf2;
	buf1.loadFromFile("music/meow1.ogg");
	buf2.loadFromFile("music/meow2.ogg");
	Sound meow1, meow2;
	meow1.setBuffer(buf1);
	meow2.setBuffer(buf2);

	 //Objects
	 Object posters("tayles1.png", 160, 660, 210, 250, 280, 215);
	 Object bed("tayles1.png", 420, 80, 280, 310, 250, 440);
	 Object toys("tayles1.png", 120, 470, 180, 150, 220, 545);
	 Object upShelf("tayles1.png", 700, 652.5, 120, 97.5, 350, 83);
	 Object cabinet("tayles1.png", 75, 40, 250, 350, 605, 305);
	 Object mop("tayles1.png", 515, 785, 165, 241, 587, 385);
	 Object flower("tayles1.png", 780, 65, 170, 330, 147, 285);
	 Object ball("tayles1.png", 905, 615, 40, 55, 357, 190);
	 Object books("tayles1.png", 860, 735, 125, 80, 290, 187);
	  while (window.isOpen())
    {

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/500;
		Vector2i pos = Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			//>>>>>----Meow----<<<<<<
			if (event.type == Event::MouseButtonPressed)
					if (event.key.code == Mouse::Left)
						if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))
						{
							if(cntMeow == 5)
							{
								meow2.play();
								cntMeow = 0;
							}
							meow1.play();
							cntMeow++;
						}
			//------------------------------------------------------------------------------
        }
		p.update(time);

		window.clear();
		window.draw(level);
		window.draw(posters.sprite);
		window.draw(bed.sprite);
		window.draw(toys.sprite);
		window.draw(upShelf.sprite);
		window.draw(cabinet.sprite);
		window.draw(mop.sprite);
		window.draw(flower.sprite);
		window.draw(ball.sprite);
		window.draw(books.sprite);
		window.draw(p.sprite);
		window.display();
    }
 }
