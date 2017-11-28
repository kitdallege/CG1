#include "cg1_map.h"

#define MAP_FILEPATH "/home/code/c-code/CG1/assets/maps/orthogonal-outside.tmx"

static tmx_map *map;
static SDL_Texture *map_bmp;
static SDL_Rect map_rect;
static int x_delta, y_delta;


SDL_Renderer *gRenderer;

SDL_Texture* render_map(tmx_map *map);


void* sdl_img_loader(const char *path)
{
    return IMG_LoadTexture(gRenderer, path);
}

boolean Map_Init(SDL_Renderer *renderer)
{
    gRenderer = renderer;
    tmx_img_load_func = (void* (*)(const char*))sdl_img_loader;
    tmx_img_free_func = (void  (*)(void*))      SDL_DestroyTexture;
    if (!(map = tmx_load(MAP_FILEPATH)))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load tilemap: %s", tmx_strerr());
        return false;
    }
    map_rect.w = map->width  * map->tile_width;
    map_rect.h = map->height * map->tile_height;
    map_rect.x = 0;
    map_rect.y = 0;

    x_delta = DISPLAY_W - map_rect.w;
    y_delta = DISPLAY_H - map_rect.h;
    if (!(map_bmp = render_map(map))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render map to texture: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Map_Free(void)
{
    tmx_map_free(map);
}

boolean Map_Ticker(uint32_t ticks)
{
    return true;
}

boolean Map_Responder (SDL_Event *event)
{
    return true;
}

void Map_Render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, map_bmp, NULL, &map_rect);
}

// Utils to draw map
void set_color(int color)
{
    unsigned char r, g, b;
    r = (color >> 16) & 0xFF;
    g = (color >>  8) & 0xFF;
    b = (color)       & 0xFF;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void draw_polyline(double **points, double x, double y, int pointsc)
{
    int i;
    for (i=1; i<pointsc; i++) {
        SDL_RenderDrawLine(gRenderer, x+points[i-1][0], y+points[i-1][1], x+points[i][0], y+points[i][1]);
    }
}

void draw_polygon(double **points, double x, double y, int pointsc)
{
    draw_polyline(points, x, y, pointsc);
    if (pointsc > 2) {
        SDL_RenderDrawLine(gRenderer, x+points[0][0], y+points[0][1], x+points[pointsc-1][0], y+points[pointsc-1][1]);
    }
}

void draw_objects(tmx_object_group *objgr)
{
    SDL_Rect rect;
    set_color(objgr->color);
    tmx_object *head = objgr->head;
    // FIXME line thickness
    while (head) {
        if (head->visible) {
            if (head->obj_type == OT_SQUARE) {
                rect.x =     head->x;
                rect.y =      head->y;
                rect.w = head->width;
                rect.h = head->height;
                SDL_RenderDrawRect(gRenderer, &rect);
            } else if (head->obj_type  == OT_POLYGON) {
                draw_polygon(head->content.shape->points, head->x, head->y, head->content.shape->points_len);
            } else if (head->obj_type == OT_POLYLINE) {
                draw_polyline(head->content.shape->points, head->x, head->y, head->content.shape->points_len);
            } else if (head->obj_type == OT_ELLIPSE) {
                // FIXME: no function in SDL2
            }
        }
        head = head->next;
    }
}

unsigned int gid_clear_flags(unsigned int gid)
{
    return gid & TMX_FLIP_BITS_REMOVAL;
}

void draw_layer(tmx_map *map, tmx_layer *layer)
{
    unsigned long i, j;
    unsigned int gid;
    //float op;
    tmx_tileset *ts;
    tmx_image *im;
    SDL_Rect srcrect, dstrect;
    SDL_Texture* tileset;
    //op = layer->opacity;
    for (i=0; i<map->height; i++) {
        for (j=0; j<map->width; j++) {
            gid = gid_clear_flags(layer->content.gids[(i*map->width)+j]);
            if (map->tiles[gid] != NULL) {
                ts = map->tiles[gid]->tileset;
                im = map->tiles[gid]->image;
                srcrect.x = map->tiles[gid]->ul_x;
                srcrect.y = map->tiles[gid]->ul_y;
                srcrect.w = dstrect.w = ts->tile_width;
                srcrect.h = dstrect.h = ts->tile_height;
                dstrect.x = j*ts->tile_width;
                dstrect.y = i*ts->tile_height;
                // TODO Opacity and Flips
                if (im) {
                    tileset = (SDL_Texture*)im->resource_image;
                } else {
                    tileset = (SDL_Texture*)ts->image->resource_image;
                }
                SDL_RenderCopy(gRenderer, tileset, &srcrect, &dstrect);
            }
        }
    }
}

void draw_image_layer(tmx_image *img)
{
    SDL_Rect dim;

    dim.x = dim.y = 0;
    SDL_QueryTexture((SDL_Texture*)img->resource_image, NULL, NULL, &(dim.w), &(dim.h));

    SDL_RenderCopy(gRenderer, (SDL_Texture*)img->resource_image, NULL, &dim);
}

void draw_all_layers(tmx_map *map, tmx_layer *layers)
{
    while (layers) {
        if (layers->visible) {
            if (layers->type == L_GROUP) {
                draw_all_layers(map, layers->content.group_head);
            } else if (layers->type == L_OBJGR) {
                draw_objects(layers->content.objgr);
            } else if (layers->type == L_IMAGE) {
                draw_image_layer(layers->content.image);
            } else if (layers->type == L_LAYER) {
                draw_layer(map, layers);
            }
        }
        layers = layers->next;
    }
}

SDL_Texture* render_map(tmx_map *map)
{
    SDL_Texture *res;
    int w = map->width  * map->tile_width;
    int h = map->height * map->tile_height;
    if (!(res = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading texture for map: %s", SDL_GetError());
        return NULL;
    }

    SDL_SetRenderTarget(gRenderer, res);
    set_color(map->backgroundcolor);
    SDL_RenderClear(gRenderer);
    draw_all_layers(map, map->ly_head);
    SDL_SetRenderTarget(gRenderer, NULL);
    return res;
}