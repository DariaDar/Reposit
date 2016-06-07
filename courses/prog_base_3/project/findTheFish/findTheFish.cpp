// findTheFish.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include "functions.h"
#include "menu.h"


int main()
 {
	 RenderWindow window(VideoMode(1300,702),"Find the fish");
	 window.setPosition(Vector2i(10,10));
	 menu(window);
	 mainLevel(window);
	 return 0;
 }