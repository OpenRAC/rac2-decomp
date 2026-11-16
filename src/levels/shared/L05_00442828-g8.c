#include "common.h"
extern int g_ship_state __attribute__((sda));
extern int g_ship_transition_timer __attribute__((sda));
extern char g_ship_saved_euler[] __attribute__((aligned(16))) MACRO_ADDR;
extern char g_ship_record_position[] __attribute__((aligned(16))) MACRO_ADDR;

/* Starts a timed ship transition. It remembers a position and a direction and sets how long the transition lasts. */
void ship_start_transition(char *position, char *matrix, int frames)
{
    g_ship_state = 1;
    g_ship_transition_timer = frames;
    qcopy(g_ship_saved_euler, matrix);
    qcopy(g_ship_record_position, position);
}
