#include <tmx.h>

#include "cg1_splash.h"
#include "cg1_main_menu.h"
#include "cg1_map.h"
#include "cg1_mouse.h"
#include "cg1_game.h"
#include "cg1_screen.h"

#define CAMERA_STEP 2

// Globals
//static SDL_Renderer    *gRenderer = NULL;
//static SDL_Window      *gWindow = NULL;
//static SDL_Rect         camera = {0, 0, DISPLAY_W, DISPLAY_H};
static game_state_t     game_state;

static ScreenId current_screen = 0, next_screen, prev_screen;
static screen_state_t screen_stack[3];
// for each screen in screen_stack the transition table grows 1 item in
// both directions. Though most of the table will be NULL values as only
//certain screens transform to one another.
//static transition_func_t *transition = NULL;
//static transition_func_t screen_transition[][] = {
//    {NULL, NULL, NULL},
//    {NULL, NULL, NULL},
//    {NULL, NULL, NULL},
//};

boolean Game_Init(SDL_Window *window, SDL_Renderer *renderer)
{
    // set 'game' globals before bring in the various modules which use them.
    gWindow = window;
    gRenderer = renderer;
    gCamera = malloc(sizeof(SDL_Rect));
    gCamera->x = 0;
    gCamera->y = 0;
    gCamera->w = DISPLAY_W;
    gCamera->h = DISPLAY_H;
//    SDL_Log("camera: SDL_Rect {x:%i, y:%i, w:%i, h:%i}", gCamera->x, gCamera->y, gCamera->w, gCamera->h);
    SDL_SetWindowTitle(window, "C-Game v1");
    // screen state-machine init.
    screen_stack[0] = Splash_Screen;
    screen_stack[0].Init();
    screen_stack[1] = Main_Menu_Screen;
    screen_stack[2] = Map_Screen;
    Mouse_Init();
//    Map_Init(renderer);
    game_state = GST_SPLASH;
    return true;
}

boolean Game_Update (double delta)
{
    // update based on time thats passed
    next_screen = screen_stack[current_screen].Update(delta);
    if (next_screen != current_screen)
    {
        if(screen_stack[current_screen].DeInit)
        {
            screen_stack[current_screen].DeInit();
        }
        screen_stack[next_screen].Init();
        prev_screen = current_screen;
        current_screen = next_screen;
        //transition = screen_transition[current_screen][next_screen];
    }
//    if (game_state == GST_SPLASH && Splash_Ticker(delta) == false)
//    {
//        game_state = GST_MAP_DEMO;
//    }
    if (game_state == GST_QUIT)
    {
        // probably set up a transition to quit rather than just 'go black'.
        return false;
    }
//    Mouse_Ticker(delta);
    return true;
}

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
//    switch (game_state)
//    {
//        case GST_SPLASH:
//            Splash_Reponder(event);
//            break;
//        case GST_MAIN_MENU:
//            Main_Menu_Responder(event);
//            break;
//        case GST_MAP_DEMO:
//            Map_Responder(event);
//        default:
//            break;
//    }
    // TODO: Camera needs its own home.
    /*
    Needs to work off a state machine principal to reduce the choppy
    behavior. should just turn it on/off @ keyboard event
    and then update those that are on every Update() chance we get.
    */
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
        gCamera->y -= gCamera->y-CAMERA_STEP>0?CAMERA_STEP:0;
    }
    if (state[SDL_SCANCODE_S])
    {
        gCamera->y += gCamera->y+gCamera->h+CAMERA_STEP<MAP_H?CAMERA_STEP:0;
    }
    if (state[SDL_SCANCODE_A])
    {
        gCamera->x -= gCamera->x-CAMERA_STEP>0?CAMERA_STEP:0;
    }
    if (state[SDL_SCANCODE_D])
    {
        gCamera->x += gCamera->x+gCamera->w+CAMERA_STEP<MAP_W?CAMERA_STEP:0;
    }
//    SDL_Log("camera: SDL_Rect {x:%i, y:%i, w:%i, h:%i}", gCamera->x, gCamera->y, gCamera->w, gCamera->h);
    Mouse_Reponder(event);
    return true;
}

void Game_Draw (float interpolation)
{
//    SDL_Log("interpolation: %.2f", interpolation);
//    if(transition)
//    {
//       transition.Draw(interpolation);
//    } else {
        screen_stack[current_screen].Draw(interpolation);
//    }

//    switch (game_state)
//    {
//        case GST_SPLASH:
//            Splash_Render(gRenderer);
//            break;
//        case GST_MAIN_MENU:
//            Main_Menu_Render(gRenderer);
//            break;
//        case GST_MAP_DEMO:
//            Map_Render(gRenderer, &camera);
//        default:
//            break;
//    }
    Mouse_Render(gRenderer);
}

void Game_Quit(void)
{
    Map_Free();
    Mouse_Free();
    Main_Menu_Free();
    Splash_Free();
//    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyWindow(gWindow);
}
