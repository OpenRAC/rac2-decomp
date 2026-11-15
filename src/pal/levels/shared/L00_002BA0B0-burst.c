#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad000[0x264];
    float f264;
    u8 pad268[0x334 - 0x268];
    float f334;
} ResidentState_A220;
extern void vec_build_spherical_offset(char *, float, float, float);
extern char g_hero_position[];
extern int g_current_map_index __attribute__((sda));
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern int FloatToInt(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void part_spawn_scaling(void *, void *, unsigned, int, int, int, int, int);

/* Emit ten particles radially around the hero, using the saved height outside level 6. */
void func_PAL_L00_002BA198(void)
{
    float pos[4], vec[4];
    char *origin = g_hero_position;
    ResidentState_A220 *state = (ResidentState_A220 *)(origin - 0x80);
    int i;
    int life, fade;
    float speed, angle, elevation, radius;

    i = 9;
    do {
        life = FloatToInt(math_random_float_range(4200.0f, 7350.0f) * 0.001f);
        fade = FloatToInt(math_random_float_range(21000.0f, 31500.001953125f) * 0.001f);
        speed = math_random_float_range(0.0030000003f, 0.014f);
        qcopy(pos, origin);
        if (g_current_map_index != 6)
            pos[2] = state->f334;
        i--;
        angle = math_random_angle();
        elevation = math_random_float_range(0.349065899848938f, 1.396263599395752f);
        radius = math_random_float_range(0.05f, state->f264 + 0.2f);
        vec_build_spherical_offset((char *)vec, speed, angle, elevation);
        pos[0] += math_fast_sin_or_cos_a(angle) * radius;
        pos[1] += math_fast_sin_or_cos_b(angle) * radius;
        part_spawn_scaling(pos, vec, 0x7000c0f0, 0x70f0, 33, life, fade, 1);
    } while (i >= 0);
}
