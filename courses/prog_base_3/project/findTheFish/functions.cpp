#include "functions.h"

/*Sound &soundManager(String name)
{
	SoundBuffer buf;
	buf.loadFromFile("music/" + name);
	Sound s;
	s.setBuffer(buf);
	return s;
}*/

int meow(Sound & meow1, Sound & meow2, Player p, Vector2i pos)
 {
	static int cntMeow = 0;
	 if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		cntMeow++;
		if(cntMeow == 5)
		{
			meow2.play();
			cntMeow = 0;
		}
		else
			meow1.play();
	
		if(cntMeow == 0)
			return -1;
		else 
			return cntMeow;
	 }
	 return -22;
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

	SoundBuffer buf;
	buf.loadFromFile("music/steklo.ogg");
	Sound glass;
	glass.setBuffer(buf); glass.setVolume(100);

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
	 Furniture brokenBall("tayles1.png",920, 540, 90, 42, 430, 430);
	 Furniture key("tayles1.png", 1, 1, 25, 25, 430, 425);
	 Furniture cabinetEnd("cabinet.png", 20, 50, 270, 350, 560, 290);
	 
	 Furniture door("tayles2.png", 0, 560, 80, 340, 870, 350);
	 Furniture brokenLight("tayles2.png", 10, 110, 50, 70, 795, 430);
	 Furniture light("tayles2.png", 20, 20, 35, 70, 220, 565);
	 Furniture bath("tayles2.png", 80, 50, 320, 380, 1010, 330);
	 Furniture carpet("tayles2.png", 100, 500, 100, 140, 870, 530);
	 Furniture mirror("tayles2.png", 90, 700, 110, 290, 1200, 300);
	 Furniture sink("tayles2.png", 290, 440, 150, 240, 1190, 450);
	 int cntMeow = 0, cntGame = 0;
	 Object ob = lvl.GetObject("catPlace");
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

			
			if (event.type == Event::MouseButtonPressed){
					if (event.key.code == Mouse::Left)
					{
						int cntMeow = meow(meow1, meow2, cat, pos);

						
						//>>>>>>BALL<<<<<<<<<<<<<<
						if(cat.sprite.getGlobalBounds().intersects(ob.rect))
						{
							if(cntMeow == -1)
							{
								ball.falling(event, window, pos, lvl, time);
								glass.play();
								ball.moving(event, window, pos, "ball", lvl);
							}
						}
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
					if(ball.isPlayed == true)
					{
						key.moving(event, window, pos, "key", lvl);
						if(key.isPlayed == true && cntGame == 0)
						{
							miniGameLab();
							cntGame++;
						}
					}
				
					if(books.isPlayed == true && key.isPlayed == true)
					{
						mop.moving(event, window, pos, "mop", lvl);
					}
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
		if(mop.isPlayed == true)
			window.draw(cabinetEnd.sprite);
		else
			window.draw(cabinet.sprite);
		window.draw(upShelf.sprite);
		window.draw(mop.sprite);
		window.draw(flower.sprite);
		if(ball.isPlayed == false)
			window.draw(ball.sprite);
		else
		{
			window.draw(brokenBall.sprite);
			window.draw(key.sprite);
		}
		window.draw(books.sprite);



		if(cat.room == 2){
			window.draw(bath.sprite);
			window.draw(mirror.sprite);
			window.draw(sink.sprite);
		}

		if(cat.room == 1 || cat.room == 2){
			if(light.isPlayed == false)
			window.draw(brokenLight.sprite);
			window.draw(carpet.sprite);
			window.draw(door.sprite);
		}
		

		window.draw(cat.sprite);
		
		window.display();
    }

}