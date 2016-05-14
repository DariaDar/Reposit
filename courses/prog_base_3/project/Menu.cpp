 #include <SFML/Graphics.hpp> 
 using namespace sf;


 void menu(RenderWindow &window)
 {
	 Texture menuText1, menuText2, menuText3, menuBackground;
	 menuBackground.loadFromFile("images/menu1.jpg");
	 menuText2.loadFromFile("images/cat.jpg");
	 Sprite menuLoad(menuText2);
	 Sprite menuBg(menuBackground);
	 bool isMenu = 1;
	 int menuNum = 0;
	 menuBg.setPosition(0,0);

	 Font font;
	 font.loadFromFile("Hamurz.ttf");
	 Text text("", font, 48);
	 Text text2("", font, 48);
	 Text text3("", font, 48);
	 text.setString("New Game");
	 text2.setString("Load");
	 text3.setString("Exit");
	 text.setPosition(500,410);
	 text2.setPosition(550,488);
	 text3.setPosition(550,564);


	 while(isMenu)
	 {
		text.setColor(Color(254,150,121));
		text2.setColor(Color(254,150,121));
		text3.setColor(Color(254,150,121));
		menuNum = 0;

		 window.clear(Color(129,181,221));
		 if(IntRect(500,410,200,60).contains(Mouse::getPosition(window)))
		 {
			 text.setColor(Color(98,198,223));
			 menuNum = 1;
		 }
		 if(IntRect(550,488,200,60).contains(Mouse::getPosition(window)))
		 {
			 text2.setColor(Color(98,198,223));
			 menuNum = 2;
		 }
		 if(IntRect(500,564,200,60).contains(Mouse::getPosition(window)))
		 {
			 text3.setColor(Color(98,198,223));
			 menuNum = 3;
		 }
			
			 
		if(Mouse::isButtonPressed(Mouse::Left))
		{
			if(menuNum == 2)
			{
				window.draw(menuLoad);
				window.display();
				while(!Keyboard::isKeyPressed(Keyboard::Escape))
				{;}
			}
			if(menuNum == 3)
			{
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

 int main()
 {
	 RenderWindow window(VideoMode(1300,702),"Find the fish", Style::Default);
	 window.setPosition(Vector2i(10,10));
	 menu(window);

	 Clock clock;

	  while (window.isOpen())
    {
		float time = 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
 }
