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
    game->Init      = Game_Init;
    game->Update    = Game_Update;
    game->Handle    = Game_Handle;
    game->Draw      = Game_Draw;
    game->Quit      = Game_Quit;

    if (!Core_Init(game)){
        goto errorQuit;
    }
    Core_Run(game);
    Core_Quit(game);
    return 0;

errorQuit:
    Core_Quit(game);
    return -1;
}
