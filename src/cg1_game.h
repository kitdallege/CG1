#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_globals.h"
#include "cg1_screen.h"

typedef enum {
        GST_QUIT,
        GST_INITIALIZED,
        GST_SPLASH,
        GST_MAIN_MENU,
        GST_MAP_DEMO,
        GST_NUM_OF_STATES
} game_state_t;


bool game_init(SDL_Window *window, SDL_Renderer *renderer);
bool game_update (double delta);
bool game_handle (SDL_Event *ev);
void game_draw(float interpolation);
void game_quit(void);

#endif // GAME_H_INCLUDED


