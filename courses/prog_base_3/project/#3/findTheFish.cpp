// findTheFish.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
#include "Player.h"
#include "Furniture.h"
#include "menu.h"
#include "LevelCl.h"
/*#include <string>
#include <vector>
#include <map>*/
#include <list>

void meow(Sound & meow1, Sound & meow2, Player p, Vector2i pos)
 {
	static int cntMeow = 0;
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
 }

int main()
 {
	 RenderWindow window(VideoMode(1300,702),"Find the fish", Style::Default);
	 window.setPosition(Vector2i(10,10));
	 menu(window);
	 int cntMeow = 0;

	 //>>>>>>>>>>>>>>>---Level---<<<<<<<<<<<<<<<<<<<<<<<<<<<
	 Level lvl;
	 lvl.LoadFromFile("map.tmx");

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
	 Player p("cat.png", 55, 25, 60, 120, 100, 445, lvl);
	 Clock clock;

	 //>>>>>>>>>>>>>>>>---Map---<<<<<<<<<<<<<<<<<<<<<<<
	 Image map_image;
	 map_image.loadFromFile("images/back.png");
	 Texture map;
	 map.loadFromImage(map_image);
	 Sprite s_map;
	 s_map.setTexture(map);

	 //>>>>>>>>>>>>>>>>---Sounds----<<<<<<<<<<<<<<<<<<<
	SoundBuffer buf1, buf2;
	buf1.loadFromFile("music/meow1.ogg");
	buf2.loadFromFile("music/meow2.ogg");
	Sound meow1, meow2;
	meow1.setBuffer(buf1);
	meow2.setBuffer(buf2);

	 //Objects
	 Furniture posters("tayles1.png", 160, 660, 210, 250, 280, 215);
	 Furniture bed("tayles1.png", 420, 80, 280, 310, 250, 440);
	 Furniture toys("tayles1.png", 120, 470, 180, 150, 220, 545);
	 Furniture upShelf("tayles1.png", 700, 652.5, 120, 97.5, 350, 83);
	 Furniture cabinet("tayles1.png", 75, 40, 250, 350, 605, 305);
	 Furniture mop("tayles1.png", 515, 785, 165, 241, 587, 385);
	 Furniture flower("tayles1.png", 780, 65, 170, 330, 147, 285);
	 Furniture ball("tayles1.png", 905, 615, 40, 55, 357, 190);
	 Furniture books("tayles1.png", 860, 735, 125, 80, 290, 187);

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
						meow(meow1, meow2, p, pos);
			//-----------------------------------------------------------------------------	
        }
		
		

		p.Update(time);

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