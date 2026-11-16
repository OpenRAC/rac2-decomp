#include "common.h"

/* func_PAL_L09_003FD248, the PAL copy of func_L09_003F8898: the same C, where the spawn counters
   are scaled to 50 Hz. */
extern int g_trooper_rearm_threshold __attribute__((sda));
extern int g_trooper_spawn_delay_min __attribute__((sda));
extern int g_trooper_spawn_delay_max __attribute__((sda));
extern int g_trooper_rearm_timer_init __attribute__((sda));

extern int math_random_int_range(int a0, int a1);
extern int FastDecTimer(char *a0);
extern void value_set_and_smooth(int a0, void *a1, int a2, int a3, f32 f12);

/* Re-arms the frame's four spawn slots, bumps the object's counter and re-runs the stage. */
void func_PAL_L09_003FD248(char *object) {
    char *frame = *(char **)(object + 0x68);

    if (*(unsigned char *)(frame + 0x2EA) != 0) {
        *(unsigned char *)(frame + 0x2EA) = 0;
        if (*(short *)(frame + 0x2E0) < ((s32)(g_trooper_rearm_threshold) * 5 + 2) / 6)
            *(short *)(frame + 0x2E0) =
                ((s32)(math_random_int_range(g_trooper_spawn_delay_min, g_trooper_spawn_delay_max)) * 5 + 2) / 6;
    }
    if (FastDecTimer(frame + 0x2E0) == 0)
        *(unsigned short *)(frame + 0x2E8) = ((s32)(g_trooper_rearm_timer_init) * 5 + 2) / 6;
    FastDecTimer(frame + 0x2E2);
    FastDecTimer(frame + 0x2E6);
    FastDecTimer(frame + 0x2E8);
    if (*(unsigned short *)(object + 0x96) <= 0xFFFE)
        *(unsigned short *)(object + 0x96) = *(unsigned short *)(object + 0x96) + 1;
    value_set_and_smooth(*(int *)(frame + 0x2F8), frame + 0x430, 4, 1, 1.9f);
}
