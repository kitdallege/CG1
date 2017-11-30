#ifndef CG1_SCREEN_H_INCLUDED
#define CG1_SCREEN_H_INCLUDED

#include "cg1_stdinc.h"
#include "cg1_game_screens.h"

typedef struct screen_state_s {
        game_screens_t    screen_id; // not sure about this one
        // could just be a scalar instead of a method. eg:
        //game_screens_t    id;
        // also knowing the previous screen might be nice if a screen just wants
        // to appear, do stuff, then return to whatever was going on before it
        // arrived.
        //game_screens_t      previous_screen_id;
        bool            (*init)(void);
        game_screens_t  (*update) (double delta);
        bool            (*handle) (SDL_Event *event);
        void            (*draw) (float interpolation);
        void            (*free)(void);
} screen_state_t;



#endif // CG1_SCREEN_H_INCLUDED
