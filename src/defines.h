#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED


/* sets the run speed of the simulation */
#define MS_PER_UPDATE 8
#define SEC_PER_UPDATE (1.0f/1000.0f * MS_PER_UPDATE)
#define GOAL_FPS 60

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define DISPLAY_H 320
#define DISPLAY_W 480

#define MAP_H 496
#define MAP_W 720
#define GAME_TITLE "C-Game #1"

//TODO: Define some pixel-to->meter world scale constants

#endif // DEFINES_H_INCLUDED
