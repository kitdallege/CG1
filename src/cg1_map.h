#ifndef CG1_MAP_H_INCLUDED
#define CG1_MAP_H_INCLUDED

#include "cg1_stdinc.h"
#include <tmx.h>

boolean Map_Init(SDL_Renderer *renderer);
void Map_Free(void);

boolean Map_Ticker(uint32_t ticks);
boolean Map_Responder (SDL_Event *event);
void Map_Render(SDL_Renderer *renderer, SDL_Rect *camera);

#endif // CG1_MAP_H_INCLUDED
