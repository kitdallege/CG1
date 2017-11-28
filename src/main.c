/*
	TODO:
        - Move subsystems initialization to engine
            - Texture loading
            - Map loader
            - Keyboard & Mouse handling
                - Player: Stub out a player to hook up because its the primary use-case.
            - Sound ?


        - Initialize Game
            - Load Screen
            - Start Menu
            - Game
            - Menu
            - Map
            - Shops/Dialog
            - Dev Console
            - FPS Display

*/
#include "cg1_game.h"

int main(int argc, char *argv[])
{
    game_t *game;

    if (!(game = Game_Init())){
        goto errorquit;
    }
    Game_Run(game);
    Game_Quit(game);
    return 0;

errorquit:
    Game_Quit(game);
    return -1;
}
