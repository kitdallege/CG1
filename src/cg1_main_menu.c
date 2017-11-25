
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cg1_main_menu.h"

#define BACKGROUND "/home/code/c-code/CG1/assets/backgrounds/sunsetintheswamp.png"

static SDL_Texture *background = NULL;

boolean Main_Menu_Init(SDL_Renderer *renderer)
{
//    SDL_Surface *surface;
//    surface = IMG_Load("/home/code/c-code/CG1/assets/backgrounds/sunsetintheswamp.png");
//    background = SDL_CreateTextureFromSurface(renderer, surface);
    background = IMG_LoadTexture(renderer, "/home/code/c-code/CG1/assets/backgrounds/sunsetintheswamp.png");

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
