#include "include_asm.h"

#include "common.h"
extern int g_enemy_timer_threshold __attribute__((sda));
extern int g_enemy_timer_min __attribute__((sda));
extern int g_enemy_timer_max __attribute__((sda));
extern f32 g_enemy_smooth_time __attribute__((sda));
extern int math_random_int_range(int, int);
extern int FastDecTimer(void *);
extern int math_fast_float_d(void *);
extern void value_set_and_smooth_pal(char *, char *, int, int, float);

/* Runs every frame for the enemy: counts down its timers, and counts up two frame counters (PAL: 50 Hz timings). */
void enemy_tick_timers_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (*(u8 *)(vars + 0x39A) != 0) {
        *(u8 *)(vars + 0x39A) = 0;
        if (*(s16 *)(vars + 0x390) < ((s32)(g_enemy_timer_threshold) * 5 + 2) / 6) {
            *(s16 *)(vars + 0x390) = ((s32)(math_random_int_range(g_enemy_timer_min, g_enemy_timer_max)) * 5 + 2) / 6;
        }
    }
    FastDecTimer(vars + 0x392);
    FastDecTimer(vars + 0x396);
    *(u16 *)(vars + 0x394) += 1;
    math_fast_float_d(*(void **)(vars + 0x3A8));
    if (*(u16 *)(moby + 0x96) <= 0xFFFE) {
        *(u16 *)(moby + 0x96) += 1;
    }
    value_set_and_smooth_pal(moby, vars + 0x2C0, 1, 1, g_enemy_smooth_time);
}
