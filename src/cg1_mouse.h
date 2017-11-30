#ifndef CG1_MOUSE_H_INCLUDED
#define CG1_MOUSE_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_globals.h"

bool mouse_init(void);
bool mouse_ticker(double delta);
bool mouse_reponder(SDL_Event *event);
void mouse_draw();
void mouse_free(void);

#endif // CG1_MOUSE_H_INCLUDED
