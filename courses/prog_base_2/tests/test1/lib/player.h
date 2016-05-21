#ifndef PLAYER_H
#define PLAYER_H

typedef struct song_s
{
    int sNum;
    char * name;
    char * artist;
};

enum player_state
{
    NOTHING,
    STOP,
    PAUSE,
    PLAY
};

typedef struct player_s player_t;
typedef struct song_s song_t;

//typedef void (*cb_fn)(player_t * self, void * user, enum player_state state, cb_fn callback);

player_t * player_new();
void player_delete(player_t * pl);
void player_addSong(player_t * pl, char * name, char * artist);
void player_deleteSong(player_t * pl);
int player_getVolume(player_t * pl);
int player_setVolume(player_t * pl, int num);

//void player_subChange(player_t * self, void * user, enum player_state state, cb_fn callback);


song_t * song_new(char * name, char * artist);
void song_free(song_t * s);




#endif // PLAYER_H
