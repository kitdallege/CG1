#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED


/* runs at 120 FPS like this */
#define MS_PER_UPDATE 8
#define SEC_PER_UPDATE (1.0f/1000.0f * MS_PER_UPDATE)
#define GOAL_FPS 60

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define DISPLAY_H 640
#define DISPLAY_W 960
#define GAME_TITLE "C-Game #1"

#endif // DEFINES_H_INCLUDED
