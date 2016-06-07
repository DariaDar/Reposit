#ifndef FURNITURE_H
#define FURNITURE_H

#include <SFML/Graphics.hpp>
#include "Object.h"
#include "LevelCl.h"
using namespace sf;

class Furniture
{
public:
	Image image;
	Texture texture;
	Sprite sprite;
	float x, y, w, h, posX, posY;
	std::vector<Object> obj;
	bool isSelected, isMove, isPlayed, isInserect;

	Furniture(String F, float X, float Y, float W, float H, float pX, float pY);
	~Furniture();
	FloatRect getRect();
	void moving(Event &ev, RenderWindow &window, Vector2i pos, String str, Level &lvl);
	void  falling(Event &ev, RenderWindow &window, Vector2i pos, Level &lvl, float time);
};

#endif