#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define colorXcnt  8
#define colorYcnt 5

 enum Colors
    {
        WHITE,
        GREEN,
        YELLOW
    };

void Draw(HANDLE hConsole, COORD position, WORD Color)
{
    int col_yellow = BACKGROUND_INTENSITY| BACKGROUND_RED | BACKGROUND_GREEN;
    int col_green = BACKGROUND_INTENSITY|BACKGROUND_GREEN;
    int col_white = BACKGROUND_INTENSITY|BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

    switch(Color)
    {
    case WHITE:
        SetConsoleTextAttribute(hConsole, col_white);
        break;
    case GREEN:
        SetConsoleTextAttribute(hConsole, col_green);
        break;
    case YELLOW:
        SetConsoleTextAttribute(hConsole, col_yellow);
        break;
    default:
        break;
    }

    SetConsoleCursorPosition(hConsole, position);
    puts("*");
    Sleep(10);
}

int main(void)
{
    const int colorXsize = 10;
    const int colorYsize = 5;
    /*Матрица заданных цветов*/
    int ColorMatrix[colorYcnt][colorXcnt] =
    {
        {YELLOW, WHITE, WHITE, YELLOW, GREEN, WHITE, YELLOW, GREEN},
        {GREEN, YELLOW, WHITE, WHITE, YELLOW, GREEN, WHITE, YELLOW},
        {WHITE, GREEN, YELLOW, WHITE, WHITE, YELLOW, GREEN, WHITE},
        {YELLOW, WHITE, GREEN, YELLOW, WHITE, WHITE, YELLOW, GREEN},
        {GREEN, YELLOW, WHITE, GREEN, YELLOW, WHITE, WHITE, YELLOW},
    };

    int i, j, k;
    int x, y;

    WORD curColor;
    COORD position = {79, 25};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for(i = 79, k = 0; i >= 0;i--, k++)
    {
        position.X = i;
        x = position.X/colorXsize;

        if(k % 2 == 0)
        {
            for(j = 24; j >= 0; j--)
            {
                position.Y = j;
                y = position.Y/colorYsize;
                curColor = ColorMatrix[y][x];
                Draw(hConsole,position,curColor);
            }
        }
        else
        {
            for(j = 0; j <=24; j++)
            {
                position.Y = j;
                y = position.Y/colorYsize;
                curColor = ColorMatrix[y][x];
                Draw(hConsole,position, curColor);
            }
        }
    }
}

