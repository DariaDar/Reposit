#include "functions.h"

void gameOver()
{
	RenderWindow window(VideoMode(604,453), "Game Over", Style::None);
	Image im; im.loadFromFile("images/girl.jpg");
	Texture text; text.loadFromImage(im);
	Sprite sp; sp.setTexture(text);
	Music music;
	music.openFromFile("music/ohSh.ogg");
	music.play();
	Font font; font.loadFromFile("fonts/hand.ttf");
	Text joke("", font, 12);
	joke.setString("Joke! Press here to continue...");
	joke.setColor(Color(0, 0, 0));
	joke.setPosition(420, 435);
	 while(window.isOpen())
    {
		Event event;
		while (window.pollEvent(event))
		{
			if(IntRect(420,433,170,17).contains(Mouse::getPosition(window)))
				{
					if(Mouse::isButtonPressed(Mouse::Left))
					{
						window.close();
					}
			}

		}
		window.clear();
		window.draw(sp);
		window.draw(joke);
		window.display();
	 }


}