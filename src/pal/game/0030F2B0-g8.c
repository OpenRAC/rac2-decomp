#include "names.h"
/* func_PAL_0030F2B0, the PAL copy of func_0030DE88: the same C, where 15 becomes 12 (the 50 Hz scale of a
 * count), the spread is multiplied by 1.2 (6/5, per-frame speed at 50 Hz), and 0.3f is written in the product. */
#include "common.h"

typedef int Quadword_0030F2B0 __attribute__((mode(TI)));
typedef union {
    Quadword_0030F2B0 bits;
    float f[4];
} Vec4_0030F2B0;

extern float g_beam_particle_speed __attribute__((sda));
extern char g_hero_matrix[];

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_random_direction(void *, float, float);
extern float math_fabs(float);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern int beam_get_glow_color(void);
extern void *part_spawn_ground_effect(void *, float, float, s32, s32, s32, s32, void *, float, s32);

void func_PAL_0030F2B0(u8 *obj, int count)
{
    Vec4_0030F2B0 v;
    Vec4_0030F2B0 w;
    int i;

    v.bits = 0;
    v.f[1] = -0.9f;
    matrix_mul_vec3(&v, &v, obj + 0xC0);
    FastVecAdd(&v, &v, obj + 0x10);
    for (i = 0; i < count; i++) {
        int spin;
        int colour;
        float size;
        float life;
        vec_random_direction(&w, 0.0f, g_beam_particle_speed * 1.2f);
        w.f[0] = math_fabs(w.f[0]);
        matrix_mul_vec3(&w, &w, g_hero_matrix);
        spin = math_random_int_range(-8, 8);
        size = math_random_float_range(0.2f, 0.6f);
        life = size * 0.3f;
        colour = beam_get_glow_color() | 0x7F000000;
        part_spawn_ground_effect(&v, life, size, 12, colour, 0, spin, &w, 0.0f, 0);
        colour = 0x307F7F7F;
        part_spawn_ground_effect(&v, size * 0.15f, size * 0.5f, 12, colour, 0, -spin, &w, 0.0f, 0);
    }
}
