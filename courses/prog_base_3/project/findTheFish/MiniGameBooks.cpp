#include "Books.h"
#include <SFML/Audio.hpp>
#include "LevelCl.h"

void MiniGame_Books()
{
	RenderWindow smallW(VideoMode(700,700), "Mini-game", Style::None);
	//>>>>>MUSIC<<<<<<<<<
	Music music;
	music.openFromFile("music/books.ogg");
	music.play();
	music.setLoop(true);
	music.setVolume(75);

	SoundBuffer buf1;
	buf1.loadFromFile("music/bookSound.ogg");
	Sound sound;
	sound.setBuffer(buf1);

	//_________________________

	//>>>>>>>>FONT<<<<<<<<
	 Font font;
	 font.loadFromFile("fonts/weston.ttf");
	 Text cont("", font, 38);
	 cont.setString("Continue");
	 cont.setPosition(200,600);
	 cont.setColor(Color(182,31,80));

	//--------------------
	Texture txt; 
	Texture t; 
	t.loadFromFile("images/books.png");
	txt.loadFromFile("images/shelf1.jpg");
	Sprite menuBg(txt);
	int cnt = 0; //check right position

	Level lvl;
	lvl.LoadFromFile("books.tmx");

	Books * ptr1 = NULL;
	Books * ptr2 = NULL;

	const int cntBooks = 7;
	Books * books[cntBooks];

	for(int i = 0; i < cntBooks; i++)
	{
		std::vector<Object> ob = lvl.GetObjects("book");
		books[i] = new Books(t, ob[i].rect.left, ob[i].rect.top, ob[i].rect.width, ob[i].rect.height, i);
	}
	for(int i = 0; i < cntBooks; i++)
		books[i]->curPos = i;

	books[0]->truePos = 0;
	books[1]->truePos = 6;
	books[2]->truePos = 5;
	books[3]->truePos = 1;
	books[4]->truePos = 4;
	books[5]->truePos = 2;
	books[6]->truePos = 3;

	while (smallW.isOpen())
	{
		Event event;
		Vector2i pixelPos = Mouse::getPosition(smallW);
		while (smallW.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				smallW.close();

			cnt = 0;
			for(int i = 0; i < cntBooks; i++)
			{
				if(books[i]->curPos == books[i]->truePos)
					cnt++;
			}
			if(cnt == cntBooks)
			{
				cont.setColor(Color(34,177,76));
				if(IntRect(200,600,200,60).contains(Mouse::getPosition(smallW)))
				{
					if(Mouse::isButtonPressed(Mouse::Left))
					{
						music.stop();
						smallW.close();
					}
				}
			}


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
								ptr1->sprite.setColor(Color::Magenta);
							}
							else if(ptr2 == NULL)
							{
								ptr1->sprite.setColor(Color::White);
								ptr2 = books[i];

								int xTmp = ptr1->x;
								int yTmp = ptr1->y;
								int posTmp = ptr1->curPos;

								ptr1->setNewPos(ptr2->x, ptr2->y, ptr2->curPos);
								ptr2->setNewPos(xTmp, yTmp, posTmp);
								sound.play();
								ptr1 = NULL; ptr2 = NULL;
							}
						}
					}
				}
			}
				
	}
			smallW.clear();

			smallW.draw(menuBg);
			smallW.draw(cont);
			for(int i = 0; i < cntBooks; i++)
			{
				smallW.draw(books[i]->sprite);
			}

			smallW.display();
	}
}
