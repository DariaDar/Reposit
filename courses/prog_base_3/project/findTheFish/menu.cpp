#include "stdafx.h"
#include <SFML/Graphics.hpp> 
 using namespace sf;
 #include <SFML/Audio.hpp>

void menu(RenderWindow &window)
 {
	 Texture menuText1, menuText2, menuText3, menuBackground,loading;
	 menuBackground.loadFromFile("images/menu1.jpg");
	 menuText2.loadFromFile("images/load.png");
	 loading.loadFromFile("images/loading.png");
	 Sprite load(loading);
	 Sprite menuLoad(menuText2);
	 Sprite menuBg(menuBackground);
	 bool isMenu = 1;
	 int menuNum = 0;
	 menuBg.setPosition(0,0);
	 Music music;
	 music.openFromFile("music/menu.ogg");
	 music.play();

	 Font font;
	 font.loadFromFile("umb.ttf");
	 Text text("", font, 38); text.setStyle(Text::Bold);
	 Text text2("", font, 38); text2.setStyle(Text::Bold);
	 Text text3("", font, 38); text3.setStyle(Text::Bold);
	 text.setString("New Game");
	 text2.setString("Load");
	 text3.setString("Exit");
	 text.setPosition(485, 410);
	 text2.setPosition(550, 485);
	 text3.setPosition(550,568);
	 

	 while(isMenu)
	 {
		text.setColor(Color(254,150,121));
		text2.setColor(Color(254,150,121));
		text3.setColor(Color(254,150,121));
		menuNum = 0;

		 window.clear(Color(129,181,221));
		 //New Game
		 if(IntRect(500,410,200,60).contains(Mouse::getPosition(window)))
		 {
			 text.setColor(Color(98,198,223));
			 menuNum = 1;
		 }
		 //Load Game
		 if(IntRect(550,488,200,60).contains(Mouse::getPosition(window)))
		 {
			 text2.setColor(Color(98,198,223));
			 menuNum = 2;
		 }
		 //Exit
		 if(IntRect(500,564,200,60).contains(Mouse::getPosition(window)))
		 {
			 text3.setColor(Color(98,198,223));
			 menuNum = 3;
		 }
			
			 
		if(Mouse::isButtonPressed(Mouse::Left))
		{
			if(menuNum == 1)
			{
				window.draw(load);
				window.display();
				music.stop();
				return;
			}
			if(menuNum == 2)
			{
				window.draw(menuLoad);
				window.display();
				while(!Keyboard::isKeyPressed(Keyboard::Escape))
				{;}
			}
			if(menuNum == 3)
			{
				music.stop();
				window.close();
				isMenu = false;
			}
		}
		 window.draw(menuBg);
		 window.draw(text);
		 window.draw(text2);
		 window.draw(text3);
		 window.display();
	 }
 }