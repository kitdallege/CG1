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
//#include "cg1_game.h"
//
//int main(int argc, char *argv[])
//{
//    game_t *game;
//
//    if (!(game = Game_Init())){
//        goto errorquit;
//    }
//    Game_Run(game);
//    Game_Quit(game);
//    return 0;
//
//errorquit:
//    Game_Quit(game);
//    return -1;
//}


#include "cg1_core.h"
#include "cg1_game.h"

int main(int argc, char *argv[])
{
    game_t *game = malloc(sizeof(game_t));
    game->Init = Game_Init;
    game->Update = Game_Update;
    game->Handle = Game_Handle;
    game->Draw = Game_Draw;
    game->Quit = Game_Quit;

    if (!Core_Init(game)){
        goto errorquit;
    }
    Core_Run(game);
    Core_Quit(game);
    return 0;

errorquit:
    Core_Quit(game);
    return -1;
}
