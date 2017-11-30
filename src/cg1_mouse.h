#ifndef CG1_MOUSE_H_INCLUDED
#define CG1_MOUSE_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_globals.h"

bool Mouse_Init();
bool Mouse_Ticker(double delta);
bool Mouse_Reponder(SDL_Event *event);
void Mouse_Render();
void Mouse_Free(void);

#endif // CG1_MOUSE_H_INCLUDED
