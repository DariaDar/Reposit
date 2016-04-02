
 #include <SFML/Graphics.hpp> 
 using namespace sf;

class Player
 {
public:
	float x, y, w, h, dx, dy, speed;
	int direction;
	bool isMove, isSelect;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H);

 };

Player:: Player(String F, float X, float Y, float W, float H)
{
	dx = 0;
	dy = 0;
	speed = 0;
	file = F;
	w = W;
	h = H;
	x = X;
	y = Y;
	isMove = false;
	isSelect = false;
	image.loadFromFile("images/" + file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(x,y,w,h));
}


int main()
{

	RenderWindow window(sf::VideoMode(700, 700), "Window");
	Clock clock;

	Player p("cat_spritesheet_1.png",200, 270 ,210,200);
	//p.sprite.setPosition(50,50);
	bool isMove = false;
	float dX = 0, dY = 0;


	while (window.isOpen())
	{

		Vector2i pixelPos = Mouse::getPosition(window);
		printf("%i\n", pixelPos.x);

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

				if (event.type == Event::MouseButtonPressed)
					if (event.key.code == Mouse::Left)
						if (p.sprite.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
						{
							dX = pixelPos.x - p.sprite.getPosition().x;
							dY = pixelPos.y - p.sprite.getPosition().y;
							isMove = true;							
						}
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
					isMove = false;
					p.sprite.setColor(Color::White);
		}
			
		if (isMove) 
		{
			p.sprite.setColor(Color::Green);
			p.x = pixelPos.x-dX;
			p.y = pixelPos.y-dY;
		}
 
		window.clear();
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}

