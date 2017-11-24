#include <stdio.h>
#include <tmx.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_image.h>

#include "cg1_splash.h"
#include "cg1_game.h"

// Constants
#define DISPLAY_H 480
#define DISPLAY_W 640
#define GAME_TITLE "C-Game #1"
// Globals
static SDL_Renderer    *renderer = NULL;
static SDL_Window      *window = NULL;

static game_state_t     game_state;


void Game_Mainloop();

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

game_t * Game_Init()
{
    game_t *game = malloc(sizeof *game);
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return NULL;
    }
    window = SDL_CreateWindow(
                 GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                 DISPLAY_W, DISPLAY_H, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        fprintf(stderr, "Unable to initialize Window: %s\n", SDL_GetError());
        return NULL;
    }
    renderer = SDL_CreateRenderer(window, SDL_RENDERER_ACCELERATED,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        fprintf(stderr, "Unable to initialize Renderer: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_RenderSetLogicalSize(renderer, DISPLAY_W, DISPLAY_H);
    game_state = GST_INITIALIZED;
    return game;
}


void Game_Run(game_t *game)
{
    Splash_Init(renderer);
    Game_Mainloop();
    Splash_Free();
    //Wait two seconds

}

void Game_Mainloop(void)
{
    SDL_RenderClear(renderer);
    Splash_Render(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay( 2000 );
    return;
//    while (game_state != GST_QUIT)
//    {
//        SDL_GetTicks();
//        // get ticks
//        // process events
//        // -- update_game_objects
//        // -- collision detection
//        // audio-update
//        // render
//        // draw
//    }
}

void Game_Quit(game_t *game)
{
    free(game);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
