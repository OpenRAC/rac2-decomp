#include "include_asm.h"

#include "common.h"
extern void anim_start_blended_pal(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern int math_random_int_below(int);
extern int g_request_enabled_flag;
extern int g_player_stats MACRO_ADDR;
extern float math_random_float_range(float, float);

/* Picks a random idle animation for the current phase, avoiding the one already playing, and records the state. */
void chainblade_pick_idle_anim_pal(char *self, int previous) {
    int phase = *(unsigned char *)(self + 0x95);
    char *state = *(char **)(self + 0x68);
    float elapsed;
    float fraction;
    float choice;
    if (phase == 1) {
        fraction = ((float)*(short *)(state + 0x24) - *(float *)(state + 0x20)) / (float)*(short *)(state + 0x24);
        elapsed = (float)((g_player_stats - g_request_enabled_flag) / g_player_stats);
        choice = elapsed - fraction + math_random_float_range(-0.2f, 0.2f);
        {
            if (previous != phase && (choice < 0.0f || previous == -1)) {
                if (math_random_int_below(2)) {
                    if (*(unsigned char *)(self + 0x43) != 5)
                        anim_start_blended_pal(self, 5, 0, 8);
                } else {
                    if (*(unsigned char *)(self + 0x43) != 6)
                        anim_start_blended_pal(self, 6, 0, 8);
                }
            } else {
                if (math_random_int_below(2)) {
                    if (*(unsigned char *)(self + 0x43) != 7)
                        anim_start_blended_pal(self, 7, 0, 8);
                } else {
                    if (*(unsigned char *)(self + 0x43) != 8)
                        anim_start_blended_pal(self, 8, 0, 8);
                }
            }
        }
    }
    if (*(unsigned char *)(self + 0x95) == 2) {
        if (math_random_int_below(2)) {
            if (*(unsigned char *)(self + 0x43) != 20)
                anim_start_blended_pal(self, 20, 0, 8);
        } else {
            if (*(unsigned char *)(self + 0x43) != 19)
                anim_start_blended_pal(self, 19, 0, 8);
        }
    }
    *(short *)(state + 0x324) = *(unsigned char *)(self + 0x20);
    *(short *)(state + 0x326) = *(unsigned char *)(self + 0x95);
    moby_set_state(self, 10, *(unsigned char *)(self + 0x95));
}
