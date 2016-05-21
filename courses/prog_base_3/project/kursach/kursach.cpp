#include "stdafx.h"
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
#include "menu.h"
#include "map.h"
#include "player.h"
#include "object.h"
 using namespace sf;




/*Sprite imageManager(String file, RenderWindow &window)
{
	Texture texture;
	texture.loadFromFile("images/" + file);
	Sprite spr(texture);
	return spr;
}*/

/*Music& loadSong(String file, int volume, bool loop)
{
	Music song;
	song.openFromFile("music/" + file);
	song.setLoop(loop);
	song.setVolume(volume);
	return song;
}*/
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
	// menu(window);
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
	 Player p("cat.png", 55, 25, 60, 120, 100, 445);
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
						meow(meow1, meow2, p, pos);
			//-----------------------------------------------------------------------------	
        }
		
		

		p.update(time);

		window.clear();
		//>>>>>>>--Draw map--<<<<<<<<<<
		for(int i = 0; i < MAP_HEIGHT; i++)
		{
			for(int j = 0; j < MAP_WEIGHT; j++)
			{
				if(tileMap[i][j] == '0')
					s_map.setTextureRect(IntRect(40, 0, 40, 40));
				if(tileMap[i][j] == ' ')
					s_map.setTextureRect(IntRect(0, 0, 40, 40));
				if(tileMap[i][j] == 'f')
					s_map.setTextureRect(IntRect(80, 0, 40, 40));

				s_map.setPosition(i * 40, j * 40);
				window.draw(s_map);
			}
		}

		

		/*window.draw(level);
		window.draw(posters.sprite);
		window.draw(bed.sprite);
		window.draw(toys.sprite);
		window.draw(upShelf.sprite);
		window.draw(cabinet.sprite);
		window.draw(mop.sprite);
		window.draw(flower.sprite);
		window.draw(ball.sprite);
		window.draw(books.sprite);*/
		window.draw(p.sprite);
		window.display();
    }
 }