#ifndef CG1_MAP_H_INCLUDED
#define CG1_MAP_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_screen.h"
#include "cg1_game_screens.h"
#include "cg1_globals.h"
#include <tmx.h>

const screen_state_t Map_Screen;

bool Map_Init(void);
ScreenId Map_Ticker(double delta);
bool Map_Responder (SDL_Event *event);
void Map_Render(float interpolation);
void Map_Free(void);
#endif // CG1_MAP_H_INCLUDED
