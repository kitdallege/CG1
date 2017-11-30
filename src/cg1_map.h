#ifndef CG1_MAP_H_INCLUDED
#define CG1_MAP_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_screen.h"
#include "cg1_game_screens.h"
#include "cg1_globals.h"
#include <tmx.h>

const screen_state_t map_screen;

bool map_init(void);
game_screens_t map_ticker(double delta);
bool map_responder (SDL_Event *event);
void map_render(float interpolation);
void map_free(void);
#endif // CG1_MAP_H_INCLUDED
