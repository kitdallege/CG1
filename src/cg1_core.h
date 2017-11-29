#ifndef CG1_CORE_H_INCLUDED
#define CG1_CORE_H_INCLUDED
/*
The engine connects 'the Game' to the physical machine.

It knows how to:
- Load and render textures
- Load and play sounds
- Handle mouse/keyboard/controller input

Its the engines job to initialize/cleanup all the various systems.

The game is using the engine as its 'system' api.


I picture a bunch of state machines. All hierarchical in nature.

GameState
*/

// TODO: Remove dep on stdinc, creating our own, and if anything
// pulling in into that one.
#include "cg1_stdinc.h"
#include "cg1_screen.h"

typedef struct game_s
{
    boolean (*Init)(SDL_Window *window, SDL_Renderer *renderer);
    boolean (*Update)(double delta);
    boolean (*Handle)(SDL_Event *event);
    void    (*Draw)(float interpolation);
    void    (*Quit)(void);
} game_t;

//Public API (eg: in main)
boolean Core_Init(game_t *game);
void Core_Run(game_t *game);
void Core_Quit(game_t *game);

#endif // CG1_CORE_H_INCLUDED
