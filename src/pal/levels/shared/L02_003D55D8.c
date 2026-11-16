#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);

/* Positions A0 with four angles, then moves it kind six to kind two of length ten. */
void moby_start_anim_fast_pal(char *moby) {
    moby_set_controller_speed_limits(moby, 0.008f, 0.038000003f,
                  0.010053098f, 1.0053098f);
    moby_set_state(moby, 6, 3);
    if (*(unsigned char *)(moby + 0x43) != 2)
        anim_start_blended_pal(moby, 2, 0, 8);
}


/* Positions A0 with four angles, then moves it kind ten to kind six of length five. */
void moby_start_anim_slow_pal(char *moby) {
    moby_set_controller_speed_limits(moby, 0.008f, 0.080000006f,
                  0.005026549f, 0.5026549f);
    moby_set_state(moby, 10, 4);
    if (*(unsigned char *)(moby + 0x43) != 6)
        anim_start_blended_pal(moby, 6, 0, 4);
}

