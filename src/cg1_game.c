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
void Game_Ticker (uint32_t ticks);
void Game_Draw (void);

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
void Game_Mainloop(void)
{
    // Currently using a Fixed-time-step..
    // TODO: Go to variable.
    // I can't see enforcing some strict FPS across a ton of devices
    // so its just easier to design around inconsistent step-times.
    // I Need to get this right before i build a ton of stuff atop of it.
    /*
      Or. one could code a fixed-time-step such that your passing in a
      delta to the update anyway (in this case its a constant) but if
      ya wanted to switch to a variable-time-step you could without needing
      to change any of the *game code*.
    */
    unsigned short MAX_FRAMES_PER_SEC = 60;
    float seconds_per_frame = 1.0f / (float)MAX_FRAMES_PER_SEC;
    uint64_t freq = SDL_GetPerformanceFrequency();
    uint64_t logic_ticks  = SDL_GetPerformanceCounter();
    uint64_t time_per_tick = (uint64_t) (seconds_per_frame * freq);
    int loops;
    float interpolation;
    do {
        loops = 0;
        while (SDL_GetPerformanceCounter() >= logic_ticks && loops < MAX_FRAMES_PER_SEC)
        {
            Game_ProcessEvents();
            Game_Ticker(SDL_GetTicks());
            logic_ticks += time_per_tick;
            loops++;
            SDL_Log("step logic.");
        }
        SDL_Log("(%lu - %lu) / %lu", SDL_GetPerformanceCounter(), logic_ticks, time_per_tick);
        interpolation = (SDL_GetPerformanceCounter() + time_per_tick - logic_ticks) / time_per_tick;
        SDL_Log("interpolation: %f", interpolation);
        // TODO: update sounds
        SDL_RenderClear(renderer);
        Game_Draw();
        SDL_RenderPresent(renderer);
    } while (game_state != GST_QUIT);
}

//TODO: Turn this into a state-machine with transition functions.
//Need ability to stack FSM's, and for an FSM to be able to push onto that
// stack.
void Game_Ticker (uint32_t ticks)
{
    // update based on time thats passed
    if (game_state == GST_SPLASH && Splash_Ticker(ticks) == false)
    {
        game_state = GST_MAIN_MENU;
    }
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

void Game_Draw (void)
{

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
