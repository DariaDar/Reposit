#include "player.h"
#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct player_s
{
    list_t * songs;
    list_t * sub;
    int volume;
};


player_t * player_new()
{
    player_t * pl;
    pl = calloc(1, sizeof(struct player_s));
    pl->songs = list_new();
    pl->volume = 5;

    return pl;
}

void player_delete(player_t * pl)
{
    list_free(pl->songs);
    free(pl);
}

void player_addSong(player_t * pl, char * name, char * artist)
{
    song_t * s = song_new(name, artist);
    list_push_back(pl->songs, s);
}

void player_deleteSong(player_t * pl)
{
    song_t * del = list_pop_back(pl->songs);
    song_free(del);
}

int player_getVolume(player_t * pl)
{
    return pl->volume;
}

int player_setVolume(player_t * pl, int num)
{
    pl->volume = num;
    return pl->volume;
}

int player_playONIdex(player_t * pl, int index)
{

}

/*void player_subEv(player_t * pl, void * sub, cb_fn cb)
{

}

void player_subChange(player_t * self, void * user, enum player_state state, cb_fn callback)
{

}*/


//////SONG///////

song_t * song_new(char * name, char * artist)
{
    song_t * s = calloc(1, sizeof(struct song_s));
    strcpy(s->artist, artist);
    strcpy(s->name, name);
    s->sNum = 0;
    return s;
}

void song_free(song_t *s)
{
    free(s);
}




/////USER////////
typedef struct user_s {
    const char * name;
} user_t;

user_t * user_new(const char * name) {
    user_t * self = malloc(sizeof(user_t));
    self->name = name;
    return self;
}

void user_free(user_t * self) {
    free(self);
}

const char * user_getName(user_t * self) {
    return self->name;
}
