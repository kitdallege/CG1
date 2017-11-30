#include "cg1_splash.h"

#define SPLASH_ALPHA_MIN 125
#define SPLASH_ALPHA_MAX 255
#define SPLASH_HIDDEN_DELAY 1000
#define SPLASH_VISIBLE_LENGTH 1000
#define FADEIN_STEP 4
#define FADEIN_STEP_DELAY 10
#define FADEOUT_STEP 4
#define FADEOUT_STEP_DELAY 10


//static SDL_Renderer *gRenderer;
static cg1_splash_t *splash = NULL;

static cg1_splash_state splash_state = SPLASH_HIDDEN;
static uint32_t splash_alpha = SPLASH_ALPHA_MIN;
static uint32_t splash_animation_last_update = 0;
static uint32_t splash_animation_delta_sum = 0;

const screen_state_t splash_screen = {
    .screen_id = GS_SPLASH,
    .init = splash_init,
    .update = splash_ticker,
    .handle = splash_reponder,
    .draw = splash_render,
    .free = NULL
};

bool splash_init()
{
    splash = malloc(sizeof *splash);
    SDL_Surface *surface = NULL;
    surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating surface: %s\n", SDL_GetError());
        return false;
    }
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xcc, 0xcc, 0xcc ));
    splash->texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if (SDL_SetTextureBlendMode(splash->texture, SDL_BLENDMODE_BLEND) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error setting texture blend-mode: %s\n", SDL_GetError());
        return false;
    }
    if (SDL_SetTextureAlphaMod(splash->texture, splash_alpha) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error setting texture alpha-mode: %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);
    return true;
}


game_screens_t splash_ticker(double delta)
{
    splash_animation_delta_sum += delta;
    uint32_t elapsed = splash_animation_delta_sum- splash_animation_last_update;
    switch (splash_state) {
    case SPLASH_HIDDEN:
        if (elapsed > SPLASH_HIDDEN_DELAY) {
            splash_animation_last_update = splash_animation_delta_sum;
            splash_state = SPLASH_FADEIN;
        } else {
            //SDL_Delay(SPLASH_HIDDEN_DELAY - elapsed);
        }
        break;
    case SPLASH_FADEIN:
        if (elapsed > FADEIN_STEP_DELAY) {
            if (splash_alpha + FADEIN_STEP > SPLASH_ALPHA_MAX) {
                splash_alpha  = SPLASH_ALPHA_MAX;
            } else {
                splash_alpha += FADEIN_STEP;
            }
            SDL_SetTextureAlphaMod(splash->texture, splash_alpha);
            splash_animation_last_update = splash_animation_delta_sum;
        }
        if (splash_alpha == SPLASH_ALPHA_MAX) {
            splash_state = SPLASH_VISIBLE;
            splash_animation_last_update = splash_animation_delta_sum;
        }
        break;
    case SPLASH_VISIBLE:
        if (elapsed > SPLASH_VISIBLE_LENGTH) {
            splash_state = SPLASH_FADEOUT;
            splash_animation_last_update = splash_animation_delta_sum;
        }
        break;
    case SPLASH_FADEOUT:
        if (elapsed > FADEOUT_STEP_DELAY) {
            if (splash_alpha - FADEOUT_STEP < SPLASH_ALPHA_MIN) {
                splash_alpha = SPLASH_ALPHA_MIN;
            } else {
                splash_alpha -= FADEOUT_STEP;
            }
            SDL_SetTextureAlphaMod(splash->texture, splash_alpha);
            splash_animation_last_update = splash_animation_delta_sum;
        }
        if (splash_alpha <= SPLASH_ALPHA_MIN) {
            splash_state = SPLASH_DONE;
            splash_animation_last_update = splash_animation_delta_sum;
        }
        break;
    case SPLASH_DONE:
        return GS_MAIN_MENU;
        break;
    }
    return GS_SPLASH;

}

bool splash_reponder(SDL_Event *event)
{
    return true; // eat all events processing none.
}

void splash_render(float interpolation)
{
    //SDL_Log("splash_alpha: %i", splash_alpha);
    SDL_RenderCopy(gRenderer, splash->texture, NULL, NULL);
    return ;
}

void splash_free(void)
{
    SDL_DestroyTexture(splash->texture);
    splash->texture = NULL;
    free(splash);
}

