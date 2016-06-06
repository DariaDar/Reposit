#include "functions.h"


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



void mainLevel(RenderWindow &window)
{
	//>>>>>>>>>>>>>>>---Level---<<<<<<<<<<<<<<<<<<<<<<<<<<<
	 Level lvl;
	 lvl.LoadFromFile("map.tmx");

	//>>>>>>>>>>>>>>>>---Load basic image for level1----<<<<<<<<<<<<<<<<<
	Texture texture;
	texture.loadFromFile("images/level1empty.jpg");
	Sprite level(texture);

	Texture texture2; 
	texture2.loadFromFile("images/levelShad.png");
	Sprite level2(texture2);

	Texture texture3;
	texture3.loadFromFile("images/level12.png");
	Sprite level3(texture3);
	//>>>>>>>>>>>>>>>>---Music---<<<<<<<<<<<<<<<<<<<<<<<<<<
	 Music mainSong;
	 mainSong.openFromFile("music/level1.ogg");
	 mainSong.play();
	 mainSong.setLoop(true);
	 mainSong.setVolume(75);

	 //>>>>>>>>>>>>>>>>---Create a cat---<<<<<<<<<<<<<<<<<<<
	 Object player = lvl.GetObject("cat");
	 Player cat("cat.png", lvl, player.rect.left, player.rect.top, 60, 120, 55, 25);
	 Clock clock;

	 //>>>>>>>>>>>>>>>>---Sounds----<<<<<<<<<<<<<<<<<<<
	SoundBuffer buf1, buf2;
	buf1.loadFromFile("music/meow1.ogg");
	buf2.loadFromFile("music/meow2.ogg");
	Sound meow1, meow2;
	meow1.setBuffer(buf1);
	meow2.setBuffer(buf2);

	 //Objects
	 Furniture posters("tayles1.png",  160, 660, 210, 250, 280, 215);
	 Furniture bed("tayles1.png", 420, 80, 280, 310, 250, 440);
	 Furniture toys("tayles1.png", 120, 470, 180, 150, 220, 545);
	 Furniture upShelf("tayles1.png", 700, 652.5, 120, 97.5, 350, 83);
	 Furniture cabinet("tayles1.png", 75, 40, 250, 350, 605, 305);
	 Furniture mop("tayles1.png", 515, 785, 165, 241, 587, 385);
	 Furniture flower("tayles1.png",780, 65, 170, 330, 147, 285);
	 Furniture ball("tayles1.png", 905, 615, 40, 55, 357, 190);
	 Furniture books("tayles1.png", 860, 735, 125, 80, 290, 187);
	 
	 Furniture brokenLight("tayles2.png", 10, 110, 50, 70, 795, 430);
	 Furniture light("tayles2.png", 20, 20, 35, 70, 220, 565);
	 Furniture bath("tayles2.png", 80, 50, 320, 380, 1010, 330);
	 Furniture carpet("tayles2.png", 100, 500, 100, 140, 870, 530);
	 Furniture mirror("tayles2.png", 90, 700, 110, 290, 1200, 300);
	 Furniture sink("tayles2.png", 290, 440, 150, 240, 1190, 450);

	  while (window.isOpen())
    {
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/500;
		Vector2i pos = Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			//>>>>>----Meow----<<<<<<
			if (event.type == Event::MouseButtonPressed){
					if (event.key.code == Mouse::Left)
					{
						meow(meow1, meow2, cat, pos);
						cat.clickedThings(window, light);
						//BOOKS>>>>----<<<<<<
						if(books.isPlayed == false)
						{
							if (books.sprite.getGlobalBounds().contains(pos.x, pos.y))
							{
								mainSong.pause();
								MiniGame_Books();
								books.isPlayed = true;
								mainSong.play();
							}
						}

					}
			}

					toys.moving(event, window, pos, "toys", lvl);
					if(light.isPlayed == false)
						light.moving(event, window, pos, "light", lvl);
					


			//-----------------------------------------------------------------------------	
        }
		
		

		cat.Update(time);

		window.clear(Color::Black);
		lvl.Draw(window);
		if(cat.room == 0)
			window.draw(level);
		if(cat.room == 1)
			window.draw(level2); 
		if(cat.room == 2)
			window.draw(level3);
			
		window.draw(posters.sprite);
		window.draw(bed.sprite);
		window.draw(light.sprite);
		window.draw(toys.sprite);
		window.draw(upShelf.sprite);
		window.draw(cabinet.sprite);
		window.draw(mop.sprite);
		window.draw(flower.sprite);
		window.draw(ball.sprite);
		window.draw(books.sprite);

		if(cat.room == 1 || cat.room == 2){
			if(light.isPlayed == false)
			window.draw(brokenLight.sprite);
			window.draw(carpet.sprite);
		}
		if(cat.room == 2){
			window.draw(bath.sprite);
			window.draw(mirror.sprite);
			window.draw(sink.sprite);
		}

		window.draw(cat.sprite);
		
		window.display();
    }

}