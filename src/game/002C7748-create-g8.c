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
/* Creates a drifting particle with a random size and starting speed. */
char *part_spawn_drifting_2(char *pos, char *velocity, int life)
{
    char *state;
    char *particle = part_alloc(0x60);
    float scale;
    if (particle) {
        state = particle + 32;
        scale = 2.0f;
        particle[9] = FloatToInt(scale) + 64;
        particle[3] = 0x44;
        particle[1] = 0;
        particle[2] = g_part_tex_drifting_table[0][0];
        *(float *)(particle + 12) = math_random_float_range(g_drift_speed_range_low, g_drift_speed_range_high) * 105000.0f;
        particle[8] = math_random_int_below(255);
        *(short *)(particle + 10) = life;
        *(int *)(particle + 4) = 0x40808080;
        qcopy(particle + 16, pos);
        qcopy(state, velocity);
        *(int *)(state + 12) = 0;
        *(float *)(state + 24) = *(float *)(particle + 12) * 2;
        {
            int random = math_random_int_range(0, 3);
            float min = g_drift_spawn_min;
            float max = min + scale;
            *(int *)(state + 20) = random;
            *(int *)(state + 16) = life / 2;
            *(float *)(state + 28) = math_random_float_range(min, max) * 0.00027777778450399637f;
        }
    }
    return particle;
}
