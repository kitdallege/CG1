#ifndef CG1_MAIN_MENU_H_INCLUDED
#define CG1_MAIN_MENU_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_screen.h"
#include "cg1_game_screens.h"
#include "cg1_globals.h"

const screen_state_t Main_Menu_Screen;

boolean Main_Menu_Init();
void Main_Menu_Free(void);

ScreenId    Main_Menu_Ticker(double delta);
boolean     Main_Menu_Responder (SDL_Event *event);
void        Main_Menu_Render(float interpolation);

#endif // CG1_MAIN_MENU_H_INCLUDED
