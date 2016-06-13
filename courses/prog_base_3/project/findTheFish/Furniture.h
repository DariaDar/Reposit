#ifndef FURNITURE_H
#define FURNITURE_H

#include <SFML/Graphics.hpp>
#include "Object.h"
#include "LevelCl.h"
using namespace sf;


typedef void (*cb_fn)(RenderWindow * window, int obj, Vector2i * pos);
void writeMess(RenderWindow * window, int obj, Vector2i * pos);

enum fur_type
{
	ELSE = -1,
	TOYS = 0,
	POSTERS,
	SHELF,
	CABINET,
	MOP,
	BALL,
	BOOKS,
	KEY,
	PUDDLE,
	BROKENLIGHT,
	BATH,
	SINK
};

struct EV
{
	void * sub;
	void * cb_fn;
};

class Furniture
{
public:
	Image image;
	Texture texture;
	Sprite sprite;
	float x, y, w, h, posX, posY;
	float dX, dY;
	std::vector<Object> obj;
	bool isSelected, isMove, isPlayed, isInserect;
	EV f;
	int type;

	Furniture(String F, float X, float Y, float W, float H, float pX, float pY, int t);
	~Furniture();
	void setSub(void * sub, cb_fn foo);
	FloatRect getRect();
	void moving(Event &ev, RenderWindow &window, Vector2i pos, String str, Level &lvl);
	void move(Vector2i pos);
	void falling(Event &ev, RenderWindow &window, Vector2i pos, Level &lvl, float time);
	void trueMove(Vector2i pos);
	void intersect(String str, Level &lvl);
	int clickedThings(Vector2i pos);
};



#endif