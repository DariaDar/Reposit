#include "Books.h"
#include "LevelCl.h"


Books::Books(Texture &t, int X, int Y, int W, int H, int num)
 {

	x = X, y = Y;
	h = H; w = W;
	sprite.setTexture(t);
	sprite.setTextureRect(IntRect(x,y,w,h));
	sprite. setOrigin((int)w / 2,(int) h / 2);
	sprite.setPosition((float)x, (float)y);
	int curPos = num;
	bool isSelected = false;
 }

Books:: ~Books()
	{
		printf("Books:: ~Books()");
	}

void Books:: setNewPos(int _x, int _y, int pos)
{
	curPos = pos;
	x = _x;
	y = _y;
	sprite.setPosition((float)x, (float)y);
}
