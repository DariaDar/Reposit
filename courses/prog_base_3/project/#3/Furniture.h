#ifndef FURNITURE_H
#define FURNITURE_H

#include <SFML/Graphics.hpp>
#include "Object.h"
using namespace sf;

class Furniture
{
public:
	Image image;
	Texture texture;
	Sprite sprite;
	float x, y, w, h, posX, posY;
	std::vector<Object> obj;

	Furniture(String F, float X, float Y, float W, float H, float pX, float pY);
	~Furniture();
	FloatRect getRect();
};

#endif