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
    GST_INITIALIZED,
    GST_SPLASH,
    GST_MAIN_MENU,
    GST_QUIT
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


game_t *  Game_Init();
void Game_Ticker (uint32_t ticks); // Update (should take a delta).
void Game_Run(game_t *game);
void Game_Quit(game_t *game);
#endif // GAME_H_INCLUDED
