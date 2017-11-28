#include "cg1_mouse.h"

#define CURSOR_TEXTURE "/home/code/c-code/CG1/assets/cursor/cursor_final.png"

SDL_Texture *cursor = NULL;
SDL_Rect *position = NULL;

boolean Mouse_Init(SDL_Renderer *renderer)
{
    cursor = IMG_LoadTexture(renderer, CURSOR_TEXTURE);
    if (cursor == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading cursor texture: %s\n", SDL_GetError());
        return false;
    }
    SDL_ShowCursor(SDL_DISABLE);
    //SDL_SetRelativeMouseMode(SDL_TRUE); // captures mouse
    position = malloc(sizeof *position);
    position->w = 32;
    position->h = 32;
    return true;
}

void Mouse_Free(void)
{
    SDL_DestroyTexture(cursor);

}

boolean Mouse_Ticker(uint32_t ticks)
{
    if (position == NULL)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        position->x = x;
        position->y = y;
    }
    return true;
}

boolean Mouse_Reponder(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEWHEEL:
            {
                int x,y;
                SDL_GetMouseState(&x, &y);
                position->x = x;
                position->y = y;
                break;
            }
        default:
            break;
    }
    return true;
}

void Mouse_Render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, cursor, NULL, position);
}
