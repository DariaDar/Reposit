#include <stdio.h>
#include <stdlib.h>

int main()
{
    player_t * pl = player_new();


    user_t users2[3] = {{"Jess"}, {"John"}, {"Rob"}};

    for(int i = 0; i < 3; i++)
    {
        player_subEv(pl, &users2[i], player_subChange);
    }

    return 0;
}
