#ifndef CG1_SPLASH_H_INCLUDED
#define CG1_SPLASH_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_globals.h"
#include "cg1_screen.h"

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

const screen_state_t Splash_Screen;
boolean Splash_Init(void);
void Splash_Free(void);

ScreenId Splash_Ticker(double delta);
boolean Splash_Reponder(SDL_Event *event);
void Splash_Render(float interpolation);
#endif // CG1_SPLASH_H_INCLUDED
