#include "Books.h"
#include "LevelCl.h"


Books::Books(Texture &t, int X, int Y, int H, int W, int num)
 {
	x = X, y = Y;
	h = H; w = W;
	sprite.setTexture(t);
	sprite.setTextureRect(IntRect(x,y,w,h));
	sprite. setOrigin(w / 2, h / 2);
	sprite.setPosition(x, y);
	int bookNum = num;
	bool isSelected = false;
 }

void Books:: setNewPos(int _x, int _y)
{
	x = _x;
	y = _y;
	sprite.setPosition((float)x, (float)y);
}
