#ifndef BOOKS_H
#define BOOKS_H

	#include "Furniture.h"
	#include <SFML/Graphics.hpp> 
	using namespace sf;

 class Books
 {
 public:
	 int x, y, h, w;
	 int truePos, curPos;
	 Sprite sprite;


	 Books(Texture &t, int x, int y, int H, int W, int num);
	 ~Books();
	 void setNewPos(int _x, int _y, int pos);
 };

#endif

