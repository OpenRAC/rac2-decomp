#include "include_asm.h"






#include "common.h"
extern void electric_orb_draw_arms(char *);
extern void electric_orb_draw_ball(char *);
extern void electric_orb_update_trails(char *);

/* Draws the electric orb effect by running its three drawing steps in order. */
void electric_orb_draw_pal(char *orb) {
    electric_orb_draw_arms(orb);
    electric_orb_draw_ball(orb);
    electric_orb_update_trails(orb);
}

