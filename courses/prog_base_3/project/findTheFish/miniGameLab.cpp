#include "functions.h"
#include "Mouse.h"
#include <sstream>
#include <iostream>

bool miniGameLab()
{
	RenderWindow wind(VideoMode(660,660), "Mini-game", Style::None);
	Level lvl;
	lvl.LoadFromFile("labir.tmx");
	_Mouse mouse("mouse.png", lvl, 10, 20, 30, 20, 315, 615);
	Clock clock;
	Music song;
	song.openFromFile("music/gameLab.ogg");
	song.play(); song.setLoop(true);
	//font
	Font font;
	font.loadFromFile("fonts/weston.ttf");
	Text cont("", font, 25);
	Text finish("", font, 12);
	Text health("", font, 40);
	finish.setString("Finish");
	finish.setColor(Color::Green);
	finish.setPosition(310, 10);
	cont.setString("Congratilation! Continue.");
	cont.setPosition(127,320);
	health.setString("YOU LOSE. (Restart)");
	health.setPosition(130,320);
	health.setColor(Color::Red);
	cont.setStyle(Text::Bold);

	 while(wind.isOpen())
    {
		float time = (float)clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/800;
        sf::Event event;
        while(wind.pollEvent(event))
        {
			if(mouse.health == 0)
			{
				song.stop();
				if(IntRect(130,320,400,60).contains(Mouse::getPosition(wind)))
				{
					if(Mouse::isButtonPressed(Mouse::Left))
					{
						return true;
					}
				}
			}
  
            if(event.type == sf::Event::Closed)
                wind.close();

			if(mouse.rightPlace == true)
			{
				cont.setColor(Color(182,31,80)); 
				if(IntRect(120,320,400,60).contains(Mouse::getPosition(wind)))
				{
					if(Mouse::isButtonPressed(Mouse::Left))
					{
						song.stop();
						wind.close();
						return false;
					}
				}

			}
        }

		mouse.Update(time);
        wind.clear();		
		lvl.Draw(wind);

		if(mouse.rightPlace == true)
		wind.draw(cont);
		if(mouse.health == 0)
		wind.draw(health);
		wind.draw(finish);
		wind.draw(mouse.sprite);
 
        wind.display();
    }

	 return false;
}