#include "common.h"

typedef struct { char pad[0x2A0]; short counters[17]; } JobaCounters46020;
extern int g_hero_state[];
extern float D_L11_001B1870 __attribute__((sda));
extern int math_random_int_below(int);
extern int arena_queue_voice_line(char *, int);

/* Selects an available action from the class-specific counter table, then dispatches it. */
void joba_boss_pick_action_by_target(char *moby) {
    int action;
    char *state = *(char **)(moby + 0x68);
    char *target = *(char **)(state + 0x180);

    if (target != 0) {
        action = -1;
        if (*(short *)(target + 0xAA) != MOBY_CLASS_ARACHNOID) {
            if (*(short *)(target + 0xAA) == 0xD4A /* moby class 3402 */) {
                char *targetState = *(char **)(target + 0x68);
                if ((float)g_hero_state[0x933] <= 0.0f) {
                    action = math_random_int_below(3) + 0xC;
                    if (((JobaCounters46020 *)state)->counters[action] != 0) {
                        action = -1;
                    }
                }
                if (*(short *)(state + 0x2BE) == 0) {
                    if ((float)g_hero_state[0x933] < D_L11_001B1870) {
                        action = 0xF;
                    }
                }
                if (*(short *)(state + 0x2C0) == 0) {
                    if (*(float *)(targetState + 0x20) <= 0.0f) {
                        if (*(int *)(state + 0x140) == 0) {
                            action = 0x10;
                        }
                    }
                }
            }
        } else {
            char *targetState = *(char **)(target + 0x68);
            if ((float)g_hero_state[0x933] <= 0.0f) {
                action = math_random_int_below(2) + 6;
                if (((JobaCounters46020 *)state)->counters[action] != 0) {
                    action = -1;
                }
            }
            if (*(short *)(state + 0x2B0) == 0) {
                if ((float)g_hero_state[0x933] < D_L11_001B1870) {
                    action = 8;
                }
            }
            if (*(short *)(state + 0x2B2) == 0) {
                if (*(float *)(targetState + 0x20) <= 0.0f) {
                    action = 9;
                }
            }
        }
        if (action > 0) {
            arena_queue_voice_line(moby, action);
        }
    }
}
