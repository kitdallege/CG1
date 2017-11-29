#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL2/SDL.h>

#include "cg1_stdinc.h"
#include "cg1_screen.h"
typedef enum
{
    GST_QUIT,
    GST_INITIALIZED,
    GST_SPLASH,
    GST_MAIN_MENU,
    GST_MAP_DEMO,
    GST_NUM_OF_STATES
} game_state_t;


boolean Game_Init(SDL_Window *window, SDL_Renderer *renderer);
ScreenId Game_Update (double delta);
boolean Game_Handle (SDL_Event *ev);
void Game_Draw(float interpolation);
void Game_Quit(void);

#endif // GAME_H_INCLUDED


