#include "cg1_main_menu.h"


#define BACKGROUND "/home/code/c-code/CG1/assets/backgrounds/sunsetintheswamp.png"

static SDL_Texture *background = NULL;
static uint32_t menu_delay_delta_sum = 0;

const screen_state_t main_menu_screen = {
        .screen_id = GS_MAIN_MENU,
        .init = main_menu_init,
        .update = main_menu_ticker,
        .handle = main_menu_responder,
        .draw = main_menu_render,
        .free = main_menu_free
};

bool main_menu_init(void)
{
        background = IMG_LoadTexture(gRenderer, BACKGROUND);
        if (background == NULL) {
                SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "Failed to LoadTexture: %s", BACKGROUND);
                return false;
        }
        return true;
}

void main_menu_free(void)
{
        SDL_DestroyTexture(background);
}

game_screens_t main_menu_ticker(double delta)
{
        menu_delay_delta_sum += delta;
        if (menu_delay_delta_sum > 2000) {
                return GS_MAP;
        } else {
                return GS_MAIN_MENU;
        }
}

bool main_menu_responder (SDL_Event *event)
{
        return true;
}

void main_menu_render(float interpolation)
{
        SDL_RenderCopy(gRenderer, background, NULL, NULL);
}
