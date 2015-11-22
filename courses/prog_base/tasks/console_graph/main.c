#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int main(void)
{
    char symbol = 0;
    double zoomGr1 = 1;
    double zoomGr2 = 1;
    int coordX = 0;
    int coordY = 0;
    int cntP = 1;

    for(;;){
    COORD pos, posXY;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    posXY.X = 39 + coordX;
    posXY.Y = 12 + coordY;
    clearScreen(hConsole);
    coord(hConsole,posXY.X,posXY.Y,cntP);

    graph1( hConsole, zoomGr1,posXY.X, posXY.Y, pos);
    graph2(hConsole,zoomGr2, posXY.Y, posXY.X,pos);


    symbol = (char)getchar();
    switch(symbol)
    {
    case 'S': case 's':
        coordY = coordY + 2;
        break;
    case 'W': case 'w':
        coordY = coordY - 2;
        break;
    case 'A': case 'a':
        coordX = coordX - 3;
       break;
    case 'D': case 'd':
        coordX = coordX + 3;
        break;
    case 'Z': case 'z':
        zoomGr1 = zoomGr1 + 0.1;
        zoomGr2 = zoomGr2 + 0.2;
        cntP = cntP + 1;
        break;
    case 'X': case 'x':
        zoomGr1 = zoomGr1 - 0.1;
        zoomGr2 = zoomGr2 - 0.2;
        cntP = cntP - 1;
        break;
    default:
        break;
    }
}
}
