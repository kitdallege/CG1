#ifndef CG1_MAIN_MENU_H_INCLUDED
#define CG1_MAIN_MENU_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_screen.h"
#include "cg1_game_screens.h"
#include "cg1_globals.h"

const screen_state_t main_menu_screen;

bool main_menu_init();
void main_menu_free(void);

game_screens_t    main_menu_ticker(double delta);
bool        main_menu_responder (SDL_Event *event);
void        main_menu_render(float interpolation);

#endif // CG1_MAIN_MENU_H_INCLUDED
