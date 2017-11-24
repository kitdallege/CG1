#include <stdio.h>
#include <tmx.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_image.h>



#include "cg1_game.h"

#define DISPLAY_H 480
#define DISPLAY_W 640
SDL_Renderer    *renderer;
SDL_Window      *window;

boolean Game_Init(game_t *game)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
    {
        return false;
    }
    window = SDL_CreateWindow(
            game->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            DISPLAY_W, DISPLAY_H, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
            return false;
    }
    renderer = SDL_CreateRenderer(window, SDL_RENDERER_ACCELERATED,
                                SDL_RENDERER_ACCELERATED |
                                SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        return false;
    }
    SDL_RenderSetLogicalSize(renderer, DISPLAY_W, DISPLAY_H);
    return true;
}

void Game_Run(game_t *game){
    SDL_Surface* screenSurface = NULL;

    //Get window surface
    screenSurface = SDL_GetWindowSurface( window );

    //Fill the surface white
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x33, 0x33, 0x33 ) );

    //Update the surface
    SDL_UpdateWindowSurface( window );

    //Wait two seconds
    SDL_Delay( 2000 );
}

void Game_Mainloop(void);

void Game_Free(game_t *game){
    free(game);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
