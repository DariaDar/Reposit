#include "Books.h"
#include "LevelCl.h"

void MiniGame_Books()
{
	RenderWindow smallW(VideoMode(700,700), "Mini-game", Style::Close);
	/*Image im;
	im.loadFromFile("images/test.png");
	Texture t; t.loadFromImage(im);*/

	Texture txt; 
	Texture t; 
	t.loadFromFile("images/test.png");
	txt.loadFromFile("images/cat.jpg");
	Sprite menuBg(txt);

	Level lvl;
	lvl.LoadFromFile("books.tmx");

	//std::vector<Object> objects = lvl.GetAllObjects();

	//Books * books, *tmp1, *tmp2;
	Books * ptr1 = NULL;
	Books * ptr2 = NULL;

	const int cntBooks = 7;
	Books * books[cntBooks];

	
	
	for(int i = 0; i < cntBooks; i++)
	{
		std::vector<Object> ob = lvl.GetObjects("book");
		books[i] = new Books(t, ob[i].rect.left, ob[i].rect.top, 150, 50, i);
	}

	while (smallW.isOpen())
	{
		Event event;
		Vector2i pixelPos = Mouse::getPosition(smallW);
		while (smallW.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				smallW.close();

			if(event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					for(int i = 0; i < cntBooks; i++)
					{
						if (books[i]->sprite.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
						{
							if(ptr1 == NULL)
							{
								ptr1 = books[i];
								ptr1->sprite.setColor(Color::Green);
							}
							else if(ptr2 == NULL)
							{
								ptr2 = books[i];
								ptr1->sprite.setColor(Color::Yellow);

								int xTmp = ptr1->x;
								int yTmp = ptr1->y;
								ptr1->setNewPos(ptr2->x, ptr2->y);
								ptr2->setNewPos(xTmp, yTmp);
								printf("changed");
								ptr1->sprite.setColor(Color::White);
								ptr2->sprite.setColor(Color::White);
								ptr1 = NULL; ptr2 = NULL;
							}
						}
					}
				}
			}
				
	}
			smallW.clear();

			smallW.draw(menuBg);
			for(int i = 0; i < cntBooks; i++)
			{
				smallW.draw(books[i]->sprite);
			}

			smallW.display();
	}
}
