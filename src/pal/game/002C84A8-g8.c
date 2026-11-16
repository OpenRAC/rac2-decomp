#include "names.h"
/* func_PAL_002C84A8, the PAL copy of func_002C7748: the same C, with the life and timer scaled for 50 Hz, the
   scaled timer computed before the float load, and the final factor 0.00040000002f. */
#include "common.h"
extern char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern unsigned char *g_part_tex_drifting_table[];
extern float g_drift_speed_range_low __attribute__((sda));
extern float g_drift_speed_range_high __attribute__((sda));
extern float g_drift_spawn_min __attribute__((sda));
char *func_PAL_002C84A8(char *pos, char *velocity, int life)
{
    char *state;
    char *p = part_alloc(0x60);
    float scale;
    if (p) {
        state = p + 32;
        scale = 2.0f;
        p[9] = FloatToInt(scale) + 64;
        p[3] = 0x44;
        p[1] = 0;
        p[2] = g_part_tex_drifting_table[0][0];
        *(float *)(p + 12) = math_random_float_range(g_drift_speed_range_low, g_drift_speed_range_high) * 105000.0f;
        p[8] = math_random_int_below(255);
        *(short *)(p + 10) = ((s32)(life) * 5 + 2) / 6;
        *(int *)(p + 4) = 0x40808080;
        qcopy(p + 16, pos);
        qcopy(state, velocity);
        *(int *)(state + 12) = 0;
        *(float *)(state + 24) = *(float *)(p + 12) * 2;
        {
            int random = math_random_int_range(0, 3);
            int timer;
            float min;
            float max;
            *(int *)(state + 20) = random;
            timer = ((s32)(life / 2) * 5 + 2) / 6;
            min = g_drift_spawn_min;
            max = min + scale;
            *(int *)(state + 16) = timer;
            *(float *)(state + 28) = math_random_float_range(min, max) * 0.00040000002f;
        }
    }
    return p;
}
