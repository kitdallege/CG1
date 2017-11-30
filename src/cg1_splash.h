#ifndef CG1_SPLASH_H_INCLUDED
#define CG1_SPLASH_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_globals.h"
#include "cg1_screen.h"
#include "cg1_game_screens.h"

typedef struct cg1_splash_s {
    SDL_Texture *texture;
    // TODO:
    // texture
    // audio
} cg1_splash_t;

typedef enum {
    SPLASH_HIDDEN,
    SPLASH_FADEIN,
    SPLASH_VISIBLE,
    SPLASH_FADEOUT,
    SPLASH_DONE
} cg1_splash_state;

// TODO: Move (cg1_splash_t *splash) to module static
// as there will only ever be one, so why thread it through a bunch of crap.

const screen_state_t splash_screen;
bool splash_init(void);
void splash_free(void);

game_screens_t splash_ticker(double delta);
bool splash_reponder(SDL_Event *event);
void splash_render(float interpolation);
#endif // CG1_SPLASH_H_INCLUDED
