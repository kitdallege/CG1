/**
 * Core contains the basic code to get a window up and setup an SDL_Renderer.
 * It then Init()'s the game, giving it a chance to hook the window/renderer
 * and then drops into the run-loop. The game's update/handle/draw are call
 * within the run-loop, game.Update() returns a boolean which controls when
 * the run-loop exits.
 */
#include "cg1_core.h"
#include "cg1_game.h"

int main(int argc, char *argv[])
{
    game_t *game = malloc(sizeof(game_t));
    game->init      = game_init;
    game->update    = game_update;
    game->handle    = game_handle;
    game->draw      = game_draw;
    game->quit      = game_quit;

    if (!core_init(game)) {
        goto errorQuit;
    }
    core_run(game);
    core_quit(game);
    return 0;

errorQuit:
    core_quit(game);
    return -1;
}
