#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


int main(void) {
    int x, y, k = 3, l = 1, s = 0, a = 0;


    COORD position = {79, 25};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int col_yellow = BACKGROUND_INTENSITY| BACKGROUND_RED | BACKGROUND_GREEN;
    int col_green = BACKGROUND_INTENSITY|BACKGROUND_GREEN;
    int col_white = BACKGROUND_INTENSITY|BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;



    for(x = 79; x >= 0; x--)
    {
        for(y = 24; y >= 0; y--)
        {
            position.X = x;
            position.Y = y;
            SetConsoleCursorPosition(hConsole, position);


                if((k % 3) == 2)
                 SetConsoleTextAttribute(hConsole, col_yellow);
                if((k % 3) == 1)
                SetConsoleTextAttribute(hConsole, col_green);
                if((k % 3) == 0)
                SetConsoleTextAttribute(hConsole, col_white);



            puts("*");
            k = k+2;
            Sleep(10);
        }
        s = s+2;
        k = 3;
        k = k+s;
        x--;

            for(y = 0; y <= 24; y++)
            {
                position.X = x;
                position.Y = y;
                SetConsoleCursorPosition(hConsole, position);

                if((l % 3) == 1)
                 SetConsoleTextAttribute(hConsole, col_white);
                if((l % 3) == 2)
                SetConsoleTextAttribute(hConsole, col_yellow);
                if((l % 3) == 0)
                SetConsoleTextAttribute(hConsole, col_green);

                puts("*");
                l = l+1;
                Sleep(10);
            }
            l = 1;
            a = a + 2;
            l = l + a;
    }


    return 0;
}

