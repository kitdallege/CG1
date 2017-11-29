
#include "cg1_main_menu.h"


#define BACKGROUND "/home/code/c-code/CG1/assets/backgrounds/sunsetintheswamp.png"

static SDL_Texture *background = NULL;

const screen_state_t Main_Menu_Screen = {
    .Init = Main_Menu_Init,
    .Update = Main_Menu_Ticker,
    .Handle = Main_Menu_Responder,
    .Draw = Main_Menu_Render,
    .DeInit = Main_Menu_Free
};

boolean Main_Menu_Init(void)
{
    background = IMG_LoadTexture(gRenderer, BACKGROUND);
    if (background == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "Failed to LoadTexture: %s", BACKGROUND);
        return false;
    }
    return true;
}

void Main_Menu_Free(void)
{
    SDL_DestroyTexture(background);
}

ScreenId Main_Menu_Ticker(double delta)
{
    return 1;
}

boolean Main_Menu_Responder (SDL_Event *event)
{
    return true;
}

void Main_Menu_Render(float interpolation)
{
    SDL_RenderCopy(gRenderer, background, NULL, NULL);
}
