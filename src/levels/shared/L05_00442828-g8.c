#include "common.h"
extern int g_ship_state __attribute__((sda));
extern int g_ship_transition_timer __attribute__((sda));
extern char D_L05_001B3610[] __attribute__((aligned(16))) MACRO_ADDR;
extern char D_L05_001B3620[] __attribute__((aligned(16))) MACRO_ADDR;

/* Starts a timed ship transition. It remembers a position and a direction and sets how long the transition lasts. */
void ship_start_transition(char *position, char *matrix, int frames)
{
    g_ship_state = 1;
    g_ship_transition_timer = frames;
    qcopy(D_L05_001B3610, matrix);
    qcopy(D_L05_001B3620, position);
}
