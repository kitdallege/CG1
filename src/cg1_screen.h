#ifndef CG1_SCREEN_H_INCLUDED
#define CG1_SCREEN_H_INCLUDED

#include "cg1_stdinc.h"

typedef unsigned short ScreenId;
typedef struct screen_state_s
{
    ScreenId    screenId; // not sure about this one
    // could just be a scalar instead of a method. eg:
    //ScreenId    id;
    // also knowing the previous screen might be nice if a screen just wants
    // to appear, do stuff, then return to whatever was going on before it
    // arrived.
    //ScreenId      previousScreenId;
    bool        (*Init)(void);
    ScreenId    (*Update) (double delta);
    bool        (*Handle) (SDL_Event *event);
    void        (*Draw) (float interpolation);
    void        (*DeInit)(void);
} screen_state_t;



#endif // CG1_SCREEN_H_INCLUDED
