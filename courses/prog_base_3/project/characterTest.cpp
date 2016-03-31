#include <SFML/Graphics.hpp>


 using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(700, 700), "Window", sf::Style::Titlebar);
	Image heroIm;
	heroIm.loadFromFile("images/cat.png");

	Texture heroTextr;
	heroTextr.loadFromImage(heroIm);

	Sprite heroSprite;
	heroSprite.setTexture(heroTextr);
	heroSprite.setPosition(50,50);

	while (window.isOpen())
	{
	
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
 
		window.clear();
		window.draw(heroSprite);
		window.display();
	}
 
	return 0;
}