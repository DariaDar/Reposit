#include "functions.h"

void gameRunning()
{
	if(miniGameLab())
		gameRunning();
}

void finish()
{
	RenderWindow window(VideoMode(500,500),"", Style::None);
	Texture text;
	text.loadFromFile("images/finish.png");
	Sprite finish; finish.setTexture(text);
	Music music;
	music.openFromFile("music/finish.ogg");
	music.play();
	
	while(window.isOpen())
    {
		Event event;
		while (window.pollEvent(event))
		{
			if(IntRect(420,461,57,36).contains(Mouse::getPosition(window)))
				{
					if(Mouse::isButtonPressed(Mouse::Left))
					{
						music.stop();
						window.close();
					}
			}

		}
		window.clear();
		window.draw(finish);
		window.display();
	 }
}

void writeMess(RenderWindow * window, int obj, Vector2i * pos)
{
	
	int pFur = obj;
	Font font;
	font.loadFromFile("fonts/hand.ttf");
	Text text("", font, 25);
	text.setColor(Color(105,68,168));

	text.setPosition(pos->x, pos->y);
	switch(pFur)
	{
	case -1:
		break;
	case 0:
		text.setColor(Color(193,4,4));
		text.setString("Toys");
		break;
	case 1:
		text.setString("Posters");
		break;
	case 2:
		text.setColor(Color(18,16,16));
		text.setPosition(pos->x, pos->y - 10);
		text.setString("Skyrim");
		break;
	case 3:
		text.setColor(Color(221,231,33));
		text.setPosition(pos->x, pos->y - 10);
		text.setString("Cabinet");
		break;
	case 4:
		text.setString("Mop");
		break;
	case 5:
		text.setPosition(pos->x, pos->y - 20);
		text.setString("Ball");
		break;
	case 6:
		text.setColor(Color(193,4,4));
		text.setPosition(pos->x, pos->y + 10);
		text.setString("Books");
		break;
	case 7:
		text.setString("Key");
		break;
	case 8:
		text.setString("Puddle");
		break;
	case 9:
		text.setString("Switch");
		break;
	case 10:
		text.setColor(Color(193,4,4));
		text.setPosition(pos->x, pos->y - 10);
		text.setString("Bath");
		break;
	case 11:
		text.setString("Sink");
		break;
	default:
		text.setString("Object");
		break;
	}

	window->draw(text);
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
	 Music skyrim, muse, bathMus;
	 bathMus.openFromFile("music/bath.ogg");
	 Object mus = lvl.GetObject("muse");
	 muse.openFromFile("music/synd.ogg"); muse.setVolume(100);
	 skyrim.openFromFile("music/skyrim.ogg"); skyrim.setVolume(100);
	 mainSong.openFromFile("music/level1.ogg");
	 mainSong.play();
	 mainSong.setLoop(true);
	 mainSong.setVolume(75);

	 //>>>>>>>>>>>>>>>>---Create a cat---<<<<<<<<<<<<<<<<<<<
	 Object player = lvl.GetObject("cat");
	 Object fish = lvl.GetObject("fish");
	 Object mo = lvl.GetObject("mouse");
	 Object ob = lvl.GetObject("catPlace");


	 Player cat("cat.png", lvl, 68, 429, 60, 120, player.rect.left,  player.rect.top, ELSE);
	 
	 Clock clock;
	 Clock gameTimeClock;
	 int sinkCnt = 0;

	 //>>>>>>>>>>>>>>>>---Sounds----<<<<<<<<<<<<<<<<<<<
	SoundBuffer buf1, buf2;
	buf1.loadFromFile("music/meow1.ogg");
	buf2.loadFromFile("music/meow2.ogg");
	Sound meow1, meow2;
	meow1.setBuffer(buf1);
	meow2.setBuffer(buf2);

	SoundBuffer buf, buf3;
	buf.loadFromFile("music/steklo.ogg");
	buf3.loadFromFile("music/mouse.ogg");
	Sound glass; Sound mouseS;
	glass.setBuffer(buf); glass.setVolume(100);
	mouseS.setBuffer(buf3);
	
	 //Objects
	 Furniture posters("tayles1.png",  160, 660, 210, 250, 280, 215, POSTERS);
	 Furniture bed("tayles1.png", 420, 80, 280, 310, 250, 440, ELSE); 
	 Furniture toys("tayles1.png", 120, 470, 180, 150, 220, 545, TOYS);
	 Furniture upShelf("tayles1.png", 700, 652.5, 120, 97.5, 350, 83, SHELF);
	 Furniture cabinet("tayles1.png", 75, 40, 250, 350, 605, 305, CABINET); 
	 Furniture mop("tayles1.png", 515, 785, 165, 241, 587, 385, MOP); 
	 Furniture flower("tayles1.png",780, 65, 170, 330, 147, 285, ELSE);
	 Furniture ball("tayles1.png", 905, 615, 40, 55, 357, 190, BALL); 
	 Furniture books("tayles1.png", 860, 735, 125, 80, 290, 187, BOOKS); 
	 Furniture brokenBall("tayles1.png",920, 540, 90, 42, 430, 430, ELSE); 
	 Furniture key("tayles1.png", 1, 1, 25, 25, 430, 425, KEY);
	 Furniture cabinetEnd("cabinet.png", 20, 50, 270, 350, 590, 290, ELSE); 
	 Furniture girl("girlHair.png", 1,1, 96, 45, 1075, 350, ELSE);
	 
	 Furniture door("tayles2.png", 0, 560, 80, 340, 870, 350, ELSE);
	 Furniture puddle("tayles1.png",789, 1000, 204, 75, 1057, 559, ELSE);
	 Furniture brokenLight("tayles2.png", 10, 110, 50, 70, 795, 430, ELSE);
	 Furniture light("tayles2.png", 20, 20, 35, 70, 220, 565, ELSE);
	 Furniture bath("tayles2.png", 80, 50, 320, 380, 1010, 330, BATH);
	 Furniture openBath("bathr.png", 264, 79, 339, 369, 1015, 315, ELSE);
	 Furniture carpet("tayles2.png", 100, 500, 100, 140, 870, 530, ELSE);
	 Furniture mirror("tayles2.png", 90, 700, 110, 290, 1200, 300, ELSE);
	 Furniture sink("tayles2.png", 290, 440, 150, 240, 1190, 450, SINK);
	 Furniture sinkWater("bathr.png", 22, 180, 197, 427, 1200, 540, ELSE);
	 Furniture mou("mouse.png",  2, 21, 32, 25, mo.rect.left, mo.rect.top, ELSE);
	 
	 
	 std::list<Furniture> fList;
	 std::list<Furniture>::iterator it;
	 fList.push_back(posters);
	 fList.push_back(toys);
	 fList.push_back(upShelf);
	 fList.push_back(cabinet);
	 fList.push_back(mop);
	 fList.push_back(ball);
	 fList.push_back(books);
	 fList.push_back(key);
	 fList.push_back(puddle);
	 fList.push_back(brokenLight);
	 fList.push_back(bath);
	 fList.push_back(sink);
	 for(it = fList.begin(); it != fList.end(); it++){
		 it->setSub((void *)&it, writeMess);
	 }

	 int cntMeow = 1, cntGame = 0, click = 0, clickBath = 1, clickSink = 1;
	 bath.isPlayed = true;
	 sink.isPlayed = true;


	  while (window.isOpen())
    {
		
		float time = clock.getElapsedTime().asMicroseconds();
		float sinkTime = gameTimeClock.getElapsedTime().asSeconds();
		if(clickSink < 2)
			gameTimeClock.restart();
		clock.restart();
		time = time/500;
		Vector2i pos = Mouse::getPosition(window);
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left){

					if (fish.rect.contains(pos.x, pos.y) && key.isPlayed == true){
						mainSong.stop();
						finish();
						window.close();
					}
					if (cat.sprite.getGlobalBounds().contains(pos.x, pos.y))
					{
						cntMeow++;
						if(cntMeow == 5)
						{
							meow2.play();
							cntMeow = 0;
						}
						else
							meow1.play();
					}
					 
					toys.trueMove(pos);
					if(light.isPlayed == false) light.trueMove(pos);
					if(ball.isPlayed == true && books.isPlayed == true) key.trueMove(pos);
					if(puddle.isPlayed == true) mop.trueMove(pos);
					click = light.clickedThings(pos);
					clickBath = bath.clickedThings(pos);
					clickSink = sink.clickedThings(pos);


					if (upShelf.sprite.getGlobalBounds().contains(pos.x, pos.y)){
						skyrim.play();
					}
					if (mus.rect.contains(pos.x, pos.y)){
						muse.play();
					}
					if (girl.sprite.getGlobalBounds().contains(pos.x, pos.y) && cat.room == 2){
						mainSong.pause();
						gameOver();
						mainSong.play();
					}
					if(mou.isPlayed == false)
						{
							if (mou.sprite.getGlobalBounds().contains(pos.x, pos.y))
							{
								mainSong.pause();
								mouseS.play();
								//gameRunning();
								mou.isPlayed = true;
								mainSong.play();
							}
						}

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
					
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left){
					toys.isMove = false;
					key.isMove = false;
					if(light.isPlayed == false) light.isMove = false;
					 mop.isMove = false;
				}
		}
		if(sinkTime > 5 && clickSink == 2) puddle.isPlayed = true;

		if(clickBath == 2 && cat.room == 2)
			bathMus.play();

		if(click == -1){}
		else if(click == 1 || click == 2)
			cat.room = click;
		toys.intersect("toys",lvl); toys.move(pos); 
		if(mop.isPlayed == false)
		{
			mop.intersect("mop", lvl);
			mop.move(pos);
		}
		if(light.isPlayed == false) 
		{
			light.intersect("light", lvl);
			light.move(pos);
		}
		if(ball.isPlayed == true && books.isPlayed == true){
			if(mop.isPlayed == true)
				key.intersect("key", lvl);
			if(key.isPlayed == false)
				key.move(pos);
		}
		if(ball.isPlayed == false && books.isPlayed == true){
			if(cat.sprite.getGlobalBounds().intersects(ob.rect))
			{
				if(cntMeow == 0)
				{
					ball.falling(event, window, pos, lvl, time);
					glass.play();
					ball.isPlayed = true;
					ball.intersect("ball", lvl);
				}
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
		if(key.isPlayed == true)
			window.draw(cabinetEnd.sprite);
		else
			window.draw(cabinet.sprite);
		window.draw(upShelf.sprite);
		window.draw(flower.sprite);
		if(ball.isPlayed == false)
			window.draw(ball.sprite);
		else
		{
			window.draw(brokenBall.sprite);
			window.draw(key.sprite);
		}
		window.draw(books.sprite);

		
		if(mou.isPlayed == false){
			window.draw(mou.sprite);
		}
		else
			window.draw(light.sprite);
		window.draw(toys.sprite);


		if(cat.room == 2){
				
			 if(clickBath == 2){
				window.draw(girl.sprite);
				window.draw(openBath.sprite);
			 }
			 else
				 window.draw(bath.sprite);
			window.draw(mirror.sprite);

			 if(clickSink == 2)
				window.draw(sinkWater.sprite);
			 else
				 window.draw(sink.sprite);

			 if(puddle.isPlayed == true && mop.isPlayed == false)
				window.draw(puddle.sprite);
		}

		if(cat.room == 1 || cat.room == 2){
			if(light.isPlayed == false)
			window.draw(brokenLight.sprite);
			window.draw(carpet.sprite);
			window.draw(door.sprite);
		}
		if(mop.isPlayed == false)
			window.draw(mop.sprite);
		window.draw(cat.sprite);

		for(it = fList.begin(); it != fList.end(); it++)
			{
				if(it->sprite.getGlobalBounds().contains(pos.x, pos.y))
				{
					if(it->f.cb_fn != NULL)
					{
						cb_fn fn;
						fn = (cb_fn)it->f.cb_fn;
						fn(&window, it->type, &pos);
					}
				}
			}
		
		window.display();
    }

}