#include "SDL2/SDL.h"
#include "cg1_splash.h"

static cg1_splash_t *splash = NULL;

boolean Splash_Init(SDL_Renderer *renderer)
{
    splash = malloc(sizeof *splash);
    splash->startTime = 0;
    SDL_Surface *surface = NULL;
    surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
    if (surface == NULL){
        fprintf(stderr, "Error creating surface: %s\n", SDL_GetError());
        return false;
    }
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x33, 0x33, 0x33 ));
    splash->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return true;
}


boolean Splash_Tick(uint32_t ticks)
{
    if (splash->startTime == 0)
    {
        splash->startTime = ticks;
        return true;
    }
    uint32_t elapsed = ticks - splash->startTime;
    if (elapsed > (3 * 1000))
    {
        // fade out.
        return false;
    }
    splash->startTime = ticks;
    return true;
}

void Splash_Render(SDL_Renderer *renderer)
{
    //Fill the surface white
    SDL_RenderCopy(renderer, splash->texture, NULL, NULL);
}

void Splash_Free(void)
{
    SDL_DestroyTexture(splash->texture);
    splash->texture = NULL;
    free(splash);
}

