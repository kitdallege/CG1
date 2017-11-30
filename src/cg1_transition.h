#ifndef CG1_TRANSITION_H_INCLUDED
#define CG1_TRANSITION_H_INCLUDED
/*
    Handles what happens when one 'screen' transitions into another.

    Simple base-case would be it init's the new screen, update's and draw's it
    then free's the old screen and then signals that its finished.

    More complex examples include, slide in/out, cross-fade, load screens, etc.
*/
#include "cg1_stdinc.h"
#include "cg1_screen.h"
typedef struct transition_state_instance_data_s transition_state_instance_data_t;
typedef struct transition_state_s {
        screen_state_t *from;
        screen_state_t *to;
        boolean         complete;
        // pointer to whatever data the specific transition needs.
        transition_state_instance_data_t *data;
} transition_state_t;

// for whatever reason i made this an object. 0.o
typedef struct transition_s {
        transition_state_t  *self;
        boolean             (*init)(transition_state_t *self);
        game_screens_t      (*update) (transition_state_t *self, double delta);
        boolean             (*handle) (transition_state_t *self, SDL_Event *event);
        void                (*draw) (transition_state_t *self, float interpolation);
        void                (*de_init)(void);
} transition_t;


#endif // CG1_TRANSITION_H_INCLUDED
