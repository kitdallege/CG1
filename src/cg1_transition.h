#ifndef CG1_TRANSITION_H_INCLUDED
#define CG1_TRANSITION_H_INCLUDED
/*
    Handles what happens when one 'screen' transitions into another.

    Simple base-case would be it Init's the new screen, Update's and Draw's it
    then DeInit's the old screen and then signals that its finished.

    More complex examples include, slide in/out, cross-fade, load screens, etc.
*/
#include "cg1_stdinc.h"
#include "cg1_screen.h"
typedef struct transition_state_instance_data_s transition_state_instance_data_t;
typedef struct transition_state_s
{
    screen_state_t *from;
    screen_state_t *to;
    boolean         complete;
    // pointer to whatever data the specific transition needs.
    transition_state_instance_data_t *data;
} transition_state_t;

// for whatever reason i made this an object. 0.o
typedef struct transition_s
{
    transition_state_t  *self;
    boolean             (*Init)(transition_state_t *self);
    ScreenId            (*Update) (transition_state_t *self, double delta);
    boolean             (*Handle) (transition_state_t *self, SDL_Event *event);
    void                (*Draw) (transition_state_t *self, float interpolation);
    void                (*DeInit)(void);
} transition_t;


#endif // CG1_TRANSITION_H_INCLUDED
