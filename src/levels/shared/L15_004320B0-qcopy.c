#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
extern char *CreateMoby(int);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern short g_part_channel_timers[] __attribute__((sda));
extern short g_part_channel_reload_values[] __attribute__((sda));

/* Creates a timed effect moby of class 4522 between two points with a random timer. */
char *part_spawn_timed_effect_between_points(char *origin, char *endPoint) {
    char *o = CreateMoby(0x11AA /* moby class 4522 */);
    int i;

    if (o != 0) {
        char *st = *(char **)(o + 0x68);
        int r;

        *(u8 *)(o + 0x30) = 0xFF;
        *(short *)(o + 0x32) = 0xFF;
        *(u8 *)(o + 0x31) = 1;
        *(u8 *)(o + 0x20) = 1;
        *(TI128 *)(st + 0x10) = *(TI128 *)endPoint;
        *(TI128 *)st = *(TI128 *)origin;
        *(TI128 *)(o + 0x10) = *(TI128 *)origin;
        r = FloatToInt(math_random_float_range(6.0f, 10.0f));
        *(int *)(st + 0x50) = r;
        *(int *)(st + 0x54) = r * 2;
        for (i = 0; i < 3; i++) {
            g_part_channel_timers[i] = -1;
            g_part_channel_reload_values[i] = 10;
        }
    }
    return o;
}
