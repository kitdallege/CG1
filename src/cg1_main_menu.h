#ifndef CG1_MAIN_MENU_H_INCLUDED
#define CG1_MAIN_MENU_H_INCLUDED

#include "SDL2/SDL.h"
#include "cg1_stdinc.h"

boolean Main_Menu_Init(SDL_Renderer *renderer);
void Main_Menu_Free(void);

boolean Main_Menu_Ticker(uint32_t ticks);
boolean Main_Menu_Responder (SDL_Event *event);
void Main_Menu_Render(SDL_Renderer *renderer);

#endif // CG1_MAIN_MENU_H_INCLUDED
