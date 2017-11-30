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

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include "cg1_screen.h"

typedef struct game_s {
        bool (*init)(SDL_Window *window, SDL_Renderer *renderer);
        bool (*update)(double delta);
        bool (*handle)(SDL_Event *event);
        void (*draw)(float interpolation);
        void (*quit)(void);
} game_t;

//Public API (eg: in main)
bool core_init(game_t *game);
void core_run(game_t *game);
void core_quit(game_t *game);

#endif // CG1_CORE_H_INCLUDED
