
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cg1_main_menu.h"

#define BACKGROUND "/home/code/c-code/CG1/assets/backgrounds/sunsetintheswamp.png"

static SDL_Texture *background = NULL;

boolean Main_Menu_Init(SDL_Renderer *renderer)
{
    background = IMG_LoadTexture(renderer, BACKGROUND);
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

boolean Main_Menu_Ticker(uint32_t ticks)
{
    return true;
}

boolean Main_Menu_Responder (SDL_Event *event)
{
    return true;
}

void Main_Menu_Render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, background, NULL, NULL);
}
