#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

enum Colors
{
    WHITE,
    YELLOW,
    BLUE,
};

void setColor(HANDLE hConsole, COORD pos, WORD Color)
{
    int yellow = BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY;
    int blue = BACKGROUND_BLUE|BACKGROUND_INTENSITY;
    int white = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

    switch(Color)
    {
    case WHITE:
        SetConsoleTextAttribute(hConsole, white);
        break;
    case YELLOW:
        SetConsoleTextAttribute(hConsole, yellow);
        break;
    case BLUE:
        SetConsoleTextAttribute(hConsole, blue);
        break;
    default:
        break;
    }
    SetConsoleCursorPosition(hConsole, pos);
    puts(" ");
}

void clearScreen(HANDLE hConsole)
{
    COORD pos;
    int currColor = 0;
    int i, j;
    for(i = 0; i <= 79; i++)
    {
        pos.X = i;
        for(j = 0; j <= 24; j++)
        {
            pos.Y = j;
            setColor(hConsole,pos, currColor);
        }
    }

    pos.X = 0;
    pos.Y = 0;
    currColor = 2;
    setColor(hConsole,pos, currColor);
    printf("F(x) = x^1.5 + 2 * x - 3\n");
    pos.Y = 1;
    currColor = 1;
    setColor(hConsole,pos, currColor);
    printf("F(x) = 0.3 * tg(x) + 2");
}

void coord(HANDLE hConsole, int x, int y, int cntP)
{
    COORD pos;
    int i;
    int currColor = 0;
    setColor(hConsole,pos, currColor);
    for(pos.Y = 0, pos.X = x; pos.Y < 24;pos.Y++)
    {
        SetConsoleCursorPosition(hConsole, pos);
        if(cntP <= -2)
        {
            puts("*");
            continue;
        }
        if(pos.Y % 2 == 0)
            puts("*");
            else
            puts("\xB3\n");
    }

    for(pos.Y = y, pos.X = 0; pos.X < 79; pos.X++)
    {
        SetConsoleCursorPosition(hConsole, pos);
        if(cntP <= -2)
        {
            puts("*");
            continue;
        }
        if(cntP <= -2)
        {
            puts("*");
            continue;
        }
        if(pos.X % 2 == 0)
            puts("*");
        else
            puts("\xC4\n");
    }
}

void graph1(HANDLE hConsole, double zoomGr1, int posXYx, int posXYy, COORD pos)
{
    double x, y;
    int currColor = 2;
    for(x = 0; x < (79-posXYx); x=x+0.01)
    {
        y = pow(x, 1.5) + (2 * x) - 3;
        pos.X = posXYx + x*8*zoomGr1;
        pos.Y = 24 - (posXYy+ y*1.5*zoomGr1);
        if(pos.Y < 0 || pos.Y > 24)
            continue;
        setColor(hConsole,pos, currColor);
    }
}

void graph2(HANDLE hConsole, double zoomGr2, int posXYy, int posXYx, COORD pos)
{
    int currColor = 1;
    double x, y;
    double xTg = 0, chxTg = 0;
    float fxTg = 0;
    double ixTg = 0;

    for(x = 0; x < 79; x = x + 0.01)
    {

        xTg = (x*(M_PI/2))/(10*zoomGr2);
        chxTg = xTg/(M_PI/2);
        fxTg = modf(chxTg, &ixTg);

        if(fxTg != 0)
        {
            y = 0.3 * tan(xTg) + 2;
        }
        else
            continue;

        pos.X = x;
        posXYx = x;
        pos.Y = posXYy - zoomGr2*y*4;
        if(pos.Y < 0 || pos.Y > 24)
           continue;
       setColor(hConsole,pos, currColor);
    }
}
