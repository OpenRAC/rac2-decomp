#include "common.h"

extern char D_001B9380[];

extern char g_hero_position[];

extern void cam_compute_direction_angles(void *, void *, void *);

/* The levels' short form of the camera mode change func_00335438 (src/game/0032EB28-camera.c):
   mode 3 restarts the transition from D_00189EA0, modes 2 and 3 set its duration. */
void SetCamera5Mode(int mode, int duration)
{
    char *g = D_001B9380;
    char *camera = *(char **)(g + 0x190);
    char *state = *(char **)(camera + 0x70);
    char *transition = state + 0xE0;

    camera[0x88] = mode;
    switch (mode) {
    case 3:
        qcopy(state + 0x110, g_hero_position);
        cam_compute_direction_angles(state + 0xFC, g + 0x140, g_hero_position);
        /* fall through */
    case 2:
        *(int *)(transition + 4) = duration;
        *(int *)(state + 0xE0) = duration;
        break;
    }
}
