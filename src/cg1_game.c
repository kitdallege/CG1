#include <tmx.h>

#include "cg1_splash.h"
#include "cg1_main_menu.h"
#include "cg1_map.h"
#include "cg1_mouse.h"
#include "cg1_game.h"
#include "cg1_screen.h"

#define CAMERA_STEP 2
/*
 * The main game is a stack of screens which are link'd by transitions.
 * Each 'screen' itself may contain any number of sub-screens.
 * A screen in an oo world would be a the implementation of
 * some (Renderable, Updatable, EventHandler) type hierarchy.
 *
 * eg: https://gamedev.stackexchange.com/a/13475
 * in C world its more modeled after:
 *
 * https://github.com/allefant/allegro/tree/master/demos/skater
 */


// Globals
//static SDL_Renderer    *gRenderer = NULL;
//static SDL_Window      *gWindow = NULL;
//static SDL_Rect         camera = {0, 0, DISPLAY_W, DISPLAY_H};
static game_state_t     game_state;

static game_screens_t current_screen = GS_SPLASH, next_screen, prev_screen;
static screen_state_t screen_stack[GS_SCREEN_COUNT];
// for each screen in screen_stack the transition table grows 1 item in
// both directions. Though most of the table will be NULL values as only
//certain screens transform to one another.
//static transition_func_t *transition = NULL;
//static transition_func_t screen_transition[][] = {
//    {NULL, NULL, NULL},
//    {NULL, NULL, NULL},
//    {NULL, NULL, NULL},
//};

bool game_init(SDL_Window *window, SDL_Renderer *renderer)
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
        SDL_SetWindowTitle(window, GAME_TITLE);
        // screen state-machine init.
        screen_stack[GS_SPLASH] = splash_screen;
        screen_stack[GS_SPLASH].init();
        screen_stack[GS_MAIN_MENU] = main_menu_screen;
        screen_stack[GS_MAP] = map_screen;
        mouse_init();
//    Map_Init(renderer);
        game_state = GST_SPLASH;
        return true;
}

bool game_update (double delta)
{
        // update based on time thats passed
        next_screen = screen_stack[current_screen].update(delta);
        if (next_screen != current_screen) {
                if(screen_stack[current_screen].free) {
                        screen_stack[current_screen].free();
                }
                screen_stack[next_screen].init();
                prev_screen = current_screen;
                current_screen = next_screen;
                //transition = screen_transition[current_screen][next_screen];
        }
        if (game_state == GST_QUIT) {
                // probably set up a transition to quit rather than just 'go black'.
                return false;
        }
//   mouse_ticker(delta);
        return true;
}

bool game_handle( SDL_Event *event)
{
        switch (event->type) {
        case SDL_QUIT:
                game_state = GST_QUIT;
                break;
        case SDL_KEYDOWN:
                if (event->key.keysym.sym == SDLK_ESCAPE) {
                        game_state = GST_QUIT;
                }
                break;
        default:
                break;
        }
        // TODO: Camera needs its own home.
        /*
        Needs to work off a state machine principal to reduce the choppy
        behavior. should just turn it on/off @ keyboard event
        and then update those that are on every Update() chance we get.
        */
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_W]) {
                gCamera->y -= gCamera->y - CAMERA_STEP>0?CAMERA_STEP:0;
        }
        if (state[SDL_SCANCODE_S]) {
                gCamera->y += gCamera->y + gCamera->h + CAMERA_STEP<MAP_H?CAMERA_STEP:0;
        }
        if (state[SDL_SCANCODE_A]) {
                gCamera->x -= gCamera->x - CAMERA_STEP>0?CAMERA_STEP:0;
        }
        if (state[SDL_SCANCODE_D]) {
                gCamera->x += gCamera->x + gCamera->w + CAMERA_STEP<MAP_W?CAMERA_STEP:0;
        }
//    SDL_Log("camera: SDL_Rect {x:%i, y:%i, w:%i, h:%i}", gCamera->x, gCamera->y, gCamera->w, gCamera->h);
        mouse_reponder(event);
        return true;
}

void game_draw (float interpolation)
{
        // draw the current screen first
//    SDL_Log("interpolation: %.2f", interpolation);
//    if(transition)
//    {
//       transition.draw(interpolation);
//    } else {
        screen_stack[current_screen].draw(interpolation);
//    }
        // add player layer
        mouse_draw(); // add mouse layer
        // add hud etc.
        // add a console {0.^}
}

void game_quit(void)
{
        free(gCamera);
}
