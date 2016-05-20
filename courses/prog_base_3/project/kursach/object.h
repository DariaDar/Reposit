#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include "player.h"
using namespace sf;

class Object
{
public:
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	float x, y, w, h, posX, posY;

	Object(String F, float X, float Y, float W, float H, float pX, float pY);
	Object:: ~Object();
	void Object:: checkBounds(Player player);
};

#endif