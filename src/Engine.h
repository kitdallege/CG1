#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
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
#include <SDL2/SDL.h>

struct {
    SDL_Window      *win;
    SDL_Renderer    *ren;
    SDL_Event       evt;
    SDL_Rect        *viewport;
} Engine;




#endif // ENGINE_H_INCLUDED
