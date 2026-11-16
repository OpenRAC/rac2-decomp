#include "names.h"
/* func_PAL_L15_00437CD0, the PAL copy of func_L15_004320B0: the same C, where scale func_00283CF0(func_002A7878(6.0f, 10.0f)). */
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
extern char *CreateMoby(int);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern short g_part_channel_timers[] __attribute__((sda));
extern short g_part_channel_reload_values[] __attribute__((sda));

/* Spawns a timed effect moby between two points with a random lifetime and resets the three channel timers. */
char *part_spawn_timed_effect_between_points_pal(char *from_pos, char *to_pos) {
    char *moby = CreateMoby(0x11AA);
    int i;

    if (moby != 0) {
        char *vars = *(char **)(moby + 0x68);
        int lifetime;

        *(u8 *)(moby + 0x30) = 0xFF;
        *(short *)(moby + 0x32) = 0xFF;
        *(u8 *)(moby + 0x31) = 1;
        *(u8 *)(moby + 0x20) = 1;
        *(TI128 *)(vars + 0x10) = *(TI128 *)to_pos;
        *(TI128 *)vars = *(TI128 *)from_pos;
        *(TI128 *)(moby + 0x10) = *(TI128 *)from_pos;
        lifetime = (((int)(FloatToInt(math_random_float_range(6.0f, 10.0f))) * 5 + 2) / 6);
        *(int *)(vars + 0x50) = lifetime;
        *(int *)(vars + 0x54) = lifetime * 2;
        for (i = 0; i < 3; i++) {
            g_part_channel_timers[i] = -1;
            g_part_channel_reload_values[i] = 10;
        }
    }
    return moby;
}
