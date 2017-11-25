#include "SDL2/SDL.h"
#include "cg1_splash.h"
#define SPLASH_ALPHA_MIN 125
#define SPLASH_ALPHA_MAX 255
#define SPLASH_HIDDEN_DELAY 3000
#define SPLASH_VISIBLE_LENGTH 3000
#define FADEIN_STEP 4
#define FADEIN_STEP_DELAY 20
#define FADEOUT_STEP 4
#define FADEOUT_STEP_DELAY 20

static cg1_splash_t *splash = NULL;

static cg1_splash_state splash_state = SPLASH_HIDDEN;
static uint32_t splash_alpha = SPLASH_ALPHA_MIN;
static uint32_t splash_animation_last_update = 0;

boolean Splash_Init(SDL_Renderer *renderer)
{
    splash = malloc(sizeof *splash);
    SDL_Surface *surface = NULL;
    surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
    if (surface == NULL){
        fprintf(stderr, "Error creating surface: %s\n", SDL_GetError());
        return false;
    }
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xcc, 0xcc, 0xcc ));
    splash->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (SDL_SetTextureBlendMode(splash->texture, SDL_BLENDMODE_BLEND) != 0)
    {
        fprintf(stderr, "Error setting texture blend-mode: %s\n", SDL_GetError());
        return false;
    }
    if (SDL_SetTextureAlphaMod(splash->texture, splash_alpha) != 0)
    {
        fprintf(stderr, "Error setting texture alpha-mode: %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);
    return true;
}


boolean Splash_Ticker(uint32_t ticks)
{
    uint32_t elapsed = ticks - splash_animation_last_update;
    switch (splash_state)
    {
    case SPLASH_HIDDEN:

        if (elapsed > SPLASH_HIDDEN_DELAY)
        {
            splash_animation_last_update = ticks;
            splash_state = SPLASH_FADEIN;
        } else {
            SDL_Delay(SPLASH_HIDDEN_DELAY - elapsed);
        }
        break;
    case SPLASH_FADEIN:
        if (elapsed > FADEIN_STEP_DELAY)
        {
            if (splash_alpha + FADEIN_STEP > SPLASH_ALPHA_MAX)
            {
                splash_alpha  = SPLASH_ALPHA_MAX;
            } else {
                splash_alpha += FADEIN_STEP;
            }
            SDL_SetTextureAlphaMod(splash->texture, splash_alpha);
            splash_animation_last_update = ticks;
        }
        if (splash_alpha == SPLASH_ALPHA_MAX)
        {
            splash_state = SPLASH_VISIBLE;
            splash_animation_last_update = ticks;
        }
        break;
    case SPLASH_VISIBLE:
        if (elapsed > SPLASH_VISIBLE_LENGTH)
        {
            splash_state = SPLASH_FADEOUT;
            splash_animation_last_update = ticks;
        }
        break;
    case SPLASH_FADEOUT:
        if (elapsed > FADEOUT_STEP_DELAY)
        {
            if (splash_alpha - FADEOUT_STEP < SPLASH_ALPHA_MIN)
            {
                splash_alpha = SPLASH_ALPHA_MIN;
            } else {
                splash_alpha -= FADEOUT_STEP;
            }
            SDL_SetTextureAlphaMod(splash->texture, splash_alpha);
            splash_animation_last_update = ticks;
        }
        if (splash_alpha <= SPLASH_ALPHA_MIN)
        {
            splash_state = SPLASH_DONE;
            splash_animation_last_update = ticks;
        }
        break;
    case SPLASH_DONE:
        return false;
        break;
    }
    return true;

}

boolean Splash_Reponder(SDL_Event *event)
{
    return true; // eat all events processing none.
}

void Splash_Render(SDL_Renderer *renderer)
{
    //SDL_Log("splash_alpha: %i", splash_alpha);
    SDL_RenderCopy(renderer, splash->texture, NULL, NULL);
    return ;
}

void Splash_Free(void)
{
    SDL_DestroyTexture(splash->texture);
    splash->texture = NULL;
    free(splash);
}

