#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL2/SDL.h>

#include "cg1_stdinc.h"
/*

The Game holds all the data aspects of the active game.
Viewport position, player, maps/levels, NPC's.

*/
typedef enum
{
    GST_SPLASH,
    GST_MAIN_MENU,
    GST_PLAY
} game_state_t;

typedef struct game_s
{
    char            *title;
    game_state_t    gstate;

} game_t;

struct {
    SDL_Window      *win;
    SDL_Renderer    *ren;
    SDL_Event       evt;
    SDL_Rect        *viewport;
} Engine;


boolean  Game_Init(game_t *game);
void Game_Run(game_t *game);
void Game_Free(game_t *game);
#endif // GAME_H_INCLUDED
