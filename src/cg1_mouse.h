#ifndef CG1_MOUSE_H_INCLUDED
#define CG1_MOUSE_H_INCLUDED

#include "SDL2/SDL.h"
#include "cg1_stdinc.h"

boolean Mouse_Init(SDL_Renderer *renderer);
void Mouse_Free(void);

boolean Mouse_Ticker(uint32_t ticks);
boolean Mouse_Reponder(SDL_Event *event);
void Mouse_Render(SDL_Renderer *renderer);

#endif // CG1_MOUSE_H_INCLUDED
