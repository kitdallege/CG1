#include <stdio.h>
#include <tmx.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_image.h>

#include "cg1_splash.h"
#include "cg1_main_menu.h"
#include "cg1_mouse.h"
#include "cg1_game.h"

// Constants
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define DISPLAY_H 480
#define DISPLAY_W 640
#define GAME_TITLE "C-Game #1"
// Globals
static SDL_Renderer    *renderer = NULL;
static SDL_Window      *window = NULL;

static game_state_t     game_state;


void Game_Mainloop();
void Game_ProcessEvents (void);
boolean Game_Responder (SDL_Event *ev);
//void Game_Ticker (uint32_t ticks);
void Game_Draw (float interpolation);

game_t * Game_Init()
{
    game_t *game = malloc(sizeof *game);
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError());
        return NULL;
    }
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    window = SDL_CreateWindow(
                 GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                 DISPLAY_W * 2, DISPLAY_H * 2, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize Window: %s", SDL_GetError());
        return NULL;
    }
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize Renderer: %s", SDL_GetError());
        return NULL;
    }
    SDL_RenderSetLogicalSize(renderer, DISPLAY_W, DISPLAY_H);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    game_state = GST_INITIALIZED;
    return game;
}


void Game_Run(game_t *game)
{
    Splash_Init(renderer);
    Main_Menu_Init(renderer);
    Mouse_Init(renderer);
    game_state = GST_SPLASH;
    Game_Mainloop();
    Mouse_Free();
    Main_Menu_Free();
    Splash_Free();
}
/**
TODO: Need to decouple the run loop from the framerate.
vsync (whilst great) isn't a means to provide a steady FPS.

 https://gafferongames.com/post/fix_your_timestep/
*/


const short  MAX_UPDATES_PER_FRAME = 10;

void Game_Mainloop(void)
{
    Uint64 lag = 0;
    Uint64 prev_count = SDL_GetPerformanceCounter();
    Uint64 curr_count = SDL_GetPerformanceCounter();
    const Uint64 count_ps = SDL_GetPerformanceFrequency();
    const Uint64 count_pms = count_ps / 1000;
    double interpolation;
    do {
//        SDL_Log("============START FRAME================");
        curr_count = SDL_GetPerformanceCounter();
        lag += curr_count - prev_count;
        prev_count = curr_count;
        Game_ProcessEvents();
        while (lag >= MS_PER_UPDATE * count_pms)
        {
//            SDL_Log("tick!");
            Game_Ticker(MS_PER_UPDATE);
            lag -= MS_PER_UPDATE*count_pms;
        }
//        SDL_Log("lag: %lu", lag);
//        SDL_Log("lag ms: %.2f", (lag * 1000.0f) / (double)count_ps);
//        SDL_Log("count_pms: %lu", count_pms);
        interpolation = (double)lag / (1000.0f * (double)count_pms);
        // TODO: update sounds
        SDL_RenderClear(renderer);
        Game_Draw(interpolation);
        SDL_RenderPresent(renderer);
//        SDL_Log("============END FRAME================");
    } while (game_state != GST_QUIT);
}

//TODO: Turn this into a state-machine with transition functions.
//Need ability to stack FSM's, and for an FSM to be able to push onto that
// stack.
void Game_Ticker (double delta)
{
    // update based on time thats passed
    if (game_state == GST_SPLASH && Splash_Ticker(delta) == false)
    {
        game_state = GST_MAIN_MENU;
    }
    SDL_Delay(5);
}

void Game_ProcessEvents (void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

        Game_Responder(&event);
    }
}

boolean Game_Responder (SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_QUIT:
            game_state = GST_QUIT;
            break;
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_ESCAPE)
            {
                game_state = GST_QUIT;
            }
            break;
        default:
            break;
    }
    switch (game_state)
    {
        case GST_SPLASH:
            Splash_Reponder(event);
            break;
        case GST_MAIN_MENU:
            Main_Menu_Responder(event);
            break;
        default:
            break;
    }
    Mouse_Reponder(event);
    return true;
}

void Game_Draw (float interpolation)
{
    SDL_Log("interpolation: %.2f", interpolation);
    switch (game_state)
    {
        case GST_SPLASH:
            Splash_Render(renderer);
            break;
        case GST_MAIN_MENU:
            Main_Menu_Render(renderer);
            break;
        default:
            break;
    }
    Mouse_Render(renderer);
}

void Game_Quit(game_t *game)
{
    free(game);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
