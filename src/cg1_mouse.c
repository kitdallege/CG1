#include "cg1_mouse.h"

#define CURSOR_TEXTURE "/home/code/c-code/CG1/assets/cursor/cursor_final.png"

SDL_Texture *cursor = NULL;
static SDL_Rect *position = NULL;

bool mouse_init()
{
        cursor = IMG_LoadTexture(gRenderer, CURSOR_TEXTURE);
        if (cursor == NULL) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading cursor texture: %s\n", SDL_GetError());
                return false;
        }
        SDL_ShowCursor(SDL_DISABLE);
        //SDL_SetRelativeMouseMode(SDL_TRUE); // captures mouse
        position = malloc(sizeof(SDL_Rect));
        position->w = 32;
        position->h = 32;
        return true;
}

void mouse_free(void)
{
        SDL_DestroyTexture(cursor);

}

bool mouse_ticker(double delta)
{
        if (position == NULL) {
                int x,y;
                SDL_GetMouseState(&x, &y);
                position->x = x;
                position->y = y;
        }
        return true;
}

bool mouse_reponder(SDL_Event *event)
{
        switch (event->type) {
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEWHEEL: {
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

void mouse_draw()
{
        SDL_RenderCopy(gRenderer, cursor, NULL, position);
}
