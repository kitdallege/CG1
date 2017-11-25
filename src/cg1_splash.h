#ifndef CG1_SPLASH_H_INCLUDED
#define CG1_SPLASH_H_INCLUDED

#include <SDL2/SDL.h>
#include "cg1_stdinc.h"

typedef struct cg1_splash_s
{
    SDL_Texture *texture;
    // TODO:
    // texture
    // audio
} cg1_splash_t;

typedef enum
{
    SPLASH_HIDDEN,
    SPLASH_FADEIN,
    SPLASH_VISIBLE,
    SPLASH_FADEOUT,
    SPLASH_DONE
} cg1_splash_state;

// TODO: Move (cg1_splash_t *splash) to module static
// as there will only ever be one, so why thread it through a bunch of crap.

boolean Splash_Init(SDL_Renderer *renderer);
void Splash_Free(void);

boolean Splash_Ticker(uint32_t ticks);
boolean Splash_Reponder(SDL_Event *event);
void Splash_Render(SDL_Renderer *renderer);
#endif // CG1_SPLASH_H_INCLUDED
