#include "include_asm.h"






#include "common.h"
extern void electric_orb_draw_arms(char *);
extern void electric_orb_draw_ball(char *);
extern void electric_orb_update_trails(char *);

void electric_orb_draw_pal(char *arg0) {
    electric_orb_draw_arms(arg0);
    electric_orb_draw_ball(arg0);
    electric_orb_update_trails(arg0);
}

