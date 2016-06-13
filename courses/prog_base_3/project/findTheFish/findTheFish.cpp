// findTheFish.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include "functions.h"



int main()
 {
	 RenderWindow window(VideoMode(1300,702),"Find the fish");
	 window.setPosition(Vector2i(0,0));
	 menu(window);
	 mainLevel(window);
	 //MiniGame_Books();
	 return 0;
 }
