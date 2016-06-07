#include "functions.h"
#include "Mouse.h"

void miniGameLab()
{
	RenderWindow wind(VideoMode(660,660), "Mini-game", Style::None);
	Level lvl;
	lvl.LoadFromFile("labir3.tmx");
	_Mouse mouse("mouse.png", lvl, 10, 20, 30, 30, 315, 620);
	Clock clock;

	//font
	Font font;
	font.loadFromFile("fonts/urban.ttf");
	Text cont("", font, 38);
	cont.setString("Congratilation! Continue.");
	cont.setPosition(200,320);
	//cont.setColor(Color(182,31,80)); 
	cont.setStyle(Text::Bold);

	 while(wind.isOpen())
    {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/800;
        sf::Event event;
        while(wind.pollEvent(event))
        {
  
            if(event.type == sf::Event::Closed)
                wind.close();

			if(mouse.rightPlace == true)
			{
				cont.setColor(Color(182,31,80)); 
				if(IntRect(200,320,300,60).contains(Mouse::getPosition(wind)))
				{
					if(Mouse::isButtonPressed(Mouse::Left))
					{
						wind.close();
					}
				}

			}
        }

		mouse.Update(time);
        wind.clear();		
		lvl.Draw(wind);
		if(mouse.rightPlace == true)
		wind.draw(cont);
		wind.draw(mouse.sprite);
 
        wind.display();
    }




}