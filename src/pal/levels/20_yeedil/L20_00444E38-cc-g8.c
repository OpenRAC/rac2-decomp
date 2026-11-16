#include "names.h"
/* func_PAL_L20_00444E38, the PAL copy of func_L20_0043F460: the same C, where rename func_002BDBC0 becomes func_PAL_002BE880; scale func_002A7820(0x14, 0x50). */

/* func_L20_00444088 is defined in L20_00444088-g8.c (it needs its own flags). */

extern float g_shard_speed_min __attribute__((sda));

extern float g_shard_speed_max;

extern int g_shard_puff_color_a __attribute__((sda));

extern int g_shard_puff_color_b __attribute__((nosda));

extern int g_shard_color __attribute__((nosda));

extern int g_shard_color_a __attribute__((nosda));

extern int g_shard_color_b __attribute__((nosda));

extern char g_effect_color_table[];

extern float math_random_float_range(float, float);

extern int math_random_int_range(int, int);

extern void func_PAL_002BE880(char *, char *, int, int, int, float);

void func_PAL_L20_00444E38(char *arg0) {
    char *s0 = arg0;
    float f20;
    int r;
    int v[2];

    f20 = math_random_float_range(g_shard_speed_min, g_shard_speed_max) * 210000.0f;
    r = (((int)(math_random_int_range(0x14, 0x50)) * 5 + 2) / 6);
    if (*(short *)(s0 + 0xAA) == 0xB5A) {
        v[0] = g_shard_puff_color_a;
        v[1] = g_shard_color;
    } else {
        v[0] = g_shard_color_a;
        v[1] = g_shard_color_b;
    }
    func_PAL_002BE880(s0 + 0x10, g_effect_color_table, g_shard_puff_color_a, g_shard_puff_color_b, r, f20);
}
