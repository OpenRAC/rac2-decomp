#include "common.h"

extern float math_random_float_range(float, float);
extern u8 g_particle_effect_template[] MACRO_ADDR;
extern void moby_pick_random_point_around(void *, void *);
extern int math_random_int_range(int, int);
extern int FastTweenColor(int, int, float);
extern char *part_spawn_size_changing(void *, void *, int, int, int, int, int, float, float, float, int);

/* Makes puffs of dust around the object as its dust counter fills up. */
void part_spawn_dust_puffs(char *moby)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    int color, alpha, life, type;
    float scale, size;

    while (*(float *)(vars + 0x24) > 1.0f) {
        *(float *)(vars + 0x24) -= 1.0f;
        qcopy(vel, g_particle_effect_template);
        moby_pick_random_point_around(moby, pos);
        if (*(u8 *)(moby + 0x20) == 3 && math_random_int_range(0, 1))
            pos[2] = *(float *)(vars + 4);
        else
            vel[2] = *(float *)(vars + 0xC) * 0.5f;
        pos[2] += 6.0f;
        color = FastTweenColor(*(int *)(vars + 0x38), *(int *)(vars + 0x34),
                              math_random_float_range(0.0f, 1.0f));
        alpha = color >> 24;
        life = math_random_int_range(*(int *)(vars + 0x40) / 2, *(int *)(vars + 0x40));
        color &= 0xFFFFFF;
        type = math_random_int_range(0, *(int *)(vars + 0x3C));
        scale = math_random_float_range(0.5f, 1.0f) * *(float *)(vars + 0x30);
        size = math_random_float_range(0.7f, 1.0f);
        part_spawn_size_changing(pos, vel, life, color, type, alpha, 0, scale,
                      *(float *)(vars + 0x30) * size, 0.0033333334f,
                      *(int *)(vars + 0x2C));
    }
}
