#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL2/SDL.h>

#include "cg1_stdinc.h"

/*


*/
typedef enum
{
    GST_INITIALIZED,
    GST_SPLASH,
    GST_MAIN_MENU,
    GST_MAP_DEMO,
    GST_QUIT,
    GST_NUM_OF_STATES
} game_state_t;

typedef struct game_state_data_s
{
    game_state_t (*id) (void);
    void (*initialize) (void);
    void (*free) (void);
    game_state_t (*update) (void);
    void (*draw) (void);
} game_state_data_t;


typedef struct game_s
{
    char            *title;
    game_state_t    gstate;

} game_t;

struct {
    SDL_Window      *win;
    SDL_Renderer    *ren;
    SDL_Event       evt;
    SDL_Rect        *viewport;
} Engine;


game_t *  Game_Init();
void Game_Ticker (double delta); // Update (should take a delta).
void Game_Run(game_t *game);
void Game_Quit(game_t *game);
#endif // GAME_H_INCLUDED
