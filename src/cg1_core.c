#include "cg1_core.h"

static SDL_Renderer    *renderer = NULL;
static SDL_Window      *window = NULL;

bool core_init(game_t *game)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    window = SDL_CreateWindow(
                 GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                 DISPLAY_W, DISPLAY_H, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize Window: %s", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize Renderer: %s", SDL_GetError());
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, DISPLAY_W, DISPLAY_H);
    game->init(window, renderer);
    return true;
}

void core_run(game_t *game)
{
    Uint64 lag = 0;
    Uint64 prev_count = SDL_GetPerformanceCounter();
    Uint64 curr_count = SDL_GetPerformanceCounter();
    const Uint64 count_ps = SDL_GetPerformanceFrequency();
    const Uint64 count_pms = count_ps / 1000;
    double interpolation;
    SDL_Event event;
    bool running = true;
    do {
        curr_count = SDL_GetPerformanceCounter();
        lag += curr_count - prev_count;
        prev_count = curr_count;
        while (SDL_PollEvent(&event)) {
            game->handle(&event);
        }
        while (lag >= MS_PER_UPDATE * count_pms) {
            running = game->update(MS_PER_UPDATE);
            lag -= MS_PER_UPDATE*count_pms;
        }
        // TODO: update sounds
        SDL_RenderClear(renderer);
        // TODO: Check out `interpolation` it seems off.
        interpolation = (double)lag / (1000.0f * (double)count_pms);
        game->draw(interpolation);
        SDL_RenderPresent(renderer);
    } while (running);
}

void core_quit(game_t *game)
{
    game->quit();
    free(game);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
