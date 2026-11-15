#include "common.h"
extern int D_L05_001B1B20 __attribute__((sda));
extern int D_L05_001B1B24 __attribute__((sda));
extern char D_L05_001B3610[] __attribute__((aligned(16))) MACRO_ADDR;
extern char D_L05_001B3620[] __attribute__((aligned(16))) MACRO_ADDR;

/* Starts a timed ship transition. It remembers a position and a direction and sets how long the transition lasts. */
void func_L05_00442828(char *position, char *matrix, int frames)
{
    gShipState = 1;
    gShipTransitionTimer = frames;
    qcopy(D_L05_001B3610, matrix);
    qcopy(D_L05_001B3620, position);
}
