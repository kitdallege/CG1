#include <tmx.h>

#include "cg1_splash.h"
#include "cg1_main_menu.h"
#include "cg1_map.h"
#include "cg1_mouse.h"
#include "cg1_game.h"

#define CAMERA_STEP 2

// Globals
static SDL_Renderer    *gRenderer = NULL;
static SDL_Window      *gWindow = NULL;
static SDL_Rect         camera = {0, 0, DISPLAY_W, DISPLAY_H};
static game_state_t     game_state;


//void Game_Mainloop();
//void Game_ProcessEvents (void);

boolean Game_Init(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_SetWindowTitle(window, "C-Game v1");
    Splash_Init(renderer);
    Main_Menu_Init(renderer);
    Mouse_Init(renderer);
    Map_Init(renderer);
    game_state = GST_SPLASH;
    gWindow = window;
    gRenderer = renderer;
    return true;
}

//
//void Game_Mainloop(void)
//{
//    Uint64 lag = 0;
//    Uint64 prev_count = SDL_GetPerformanceCounter();
//    Uint64 curr_count = SDL_GetPerformanceCounter();
//    const Uint64 count_ps = SDL_GetPerformanceFrequency();
//    const Uint64 count_pms = count_ps / 1000;
//    double interpolation;
//    do {
//        curr_count = SDL_GetPerformanceCounter();
//        lag += curr_count - prev_count;
//        prev_count = curr_count;
//        Game_ProcessEvents();
//        while (lag >= MS_PER_UPDATE * count_pms)
//        {
//            Game_Ticker(MS_PER_UPDATE);
//            lag -= MS_PER_UPDATE*count_pms;
//        }
//        // TODO: update sounds
//        SDL_RenderClear(renderer);
//        // TODO: Check out `interpolation` it seems off.
//        interpolation = (double)lag / (1000.0f * (double)count_pms);
//        Game_Draw(interpolation);
//        SDL_RenderPresent(renderer);
//    } while (game_state != GST_QUIT);
//}

//TODO: Turn this into a state-machine with transition functions.
//Need ability to stack FSM's, and for an FSM to be able to push onto that
// stack.
ScreenId Game_Update (double delta)
{
    // update based on time thats passed
    if (game_state == GST_SPLASH && Splash_Ticker(delta) == false)
    {
        game_state = GST_MAP_DEMO;
    }
    return game_state;
}
//
//void Game_ProcessEvents (void)
//{
//    SDL_Event event;
//    while (SDL_PollEvent(&event))
//    {
//
//        Game_Responder(&event);
//    }
//}

boolean Game_Handle( SDL_Event *event)
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
        case GST_MAP_DEMO:
            Map_Responder(event);
        default:
            break;
    }
    // TODO: Camera needs its own home.
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
        camera.y -= camera.y-CAMERA_STEP>0?CAMERA_STEP:0;
    }
    if (state[SDL_SCANCODE_S])
    {
        camera.y += camera.y+camera.h+CAMERA_STEP<MAP_H?CAMERA_STEP:0;
    }
    if (state[SDL_SCANCODE_A])
    {
        camera.x -= camera.x-CAMERA_STEP>0?CAMERA_STEP:0;
    }
    if (state[SDL_SCANCODE_D])
    {
        camera.x += camera.x+camera.w+CAMERA_STEP<MAP_W?CAMERA_STEP:0;
    }
    Mouse_Reponder(event);
    return true;
}

void Game_Draw (float interpolation)
{
//    SDL_Log("interpolation: %.2f", interpolation);
    switch (game_state)
    {
        case GST_SPLASH:
            Splash_Render(gRenderer);
            break;
        case GST_MAIN_MENU:
            Main_Menu_Render(gRenderer);
            break;
        case GST_MAP_DEMO:
            Map_Render(gRenderer, &camera);
        default:
            break;
    }
    Mouse_Render(gRenderer);
}

void Game_Quit(void)
{
    Map_Free();
    Mouse_Free();
    Main_Menu_Free();
    Splash_Free();
}
