#include "common.h"

extern char D_001B9380[];

extern char D_00189EA0[];

extern void func_00272550(void *, void *, void *);

/* The levels' short form of the camera mode change func_00335438 (src/game/0032EB28-camera.c):
   mode 3 restarts the transition from D_00189EA0, modes 2 and 3 set its duration. */
void func_L01_0042A6F0(int mode, int duration)
{
    char *g = D_001B9380;
    char *camera = *(char **)(g + 0x190);
    char *state = *(char **)(camera + 0x70);
    char *transition = state + 0xE0;

    camera[0x88] = mode;
    switch (mode) {
    case 3:
        qcopy(state + 0x110, gHeroPosition);
        ComputeDirectionAngles(state + 0xFC, g + 0x140, gHeroPosition);
        /* fall through */
    case 2:
        *(int *)(transition + 4) = duration;
        *(int *)(state + 0xE0) = duration;
        break;
    }
}
