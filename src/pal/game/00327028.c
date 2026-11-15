#include "include_asm.h"
#include "names.h"

extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecAdd(float *, float *, int);
extern void part_spawn_ground_effect(float *, int, int, int, int, float *, int, float, float, float);

void func_PAL_00327028(float *self, int unused, int a2)
{
    float vec[4];
    float scale = math_random_float_range(0.10000000149011612f, 0.25f);
    int r = math_random_int_below(2);
    int sign;
    float a, b;

    if (r == 0)
        r = r - 1;
    sign = r;
    a = math_random_angle();
    b = math_random_float_range(0.349065899848938f, 1.5358898639678955f);

    vec_build_spherical_offset(vec, math_random_float_range(0.05000000074505806f, 0.10000000149011612f), a, b);
    FastVecAdd(vec, vec, a2);
    self[0] = self[0] + math_random_signed_float_range(0.0f, 0.15000000596046448f);
    self[1] = self[1] + math_random_signed_float_range(0.0f, 0.15000000596046448f);
    part_spawn_ground_effect(self, 0x19, 0x7F207F7F, 0, sign, vec, 0, scale * 0.10000000149011612f, scale,
                  0.006000000052154064f);
    part_spawn_ground_effect(self, 0x19, 0x7F7F7F7F, 1, -sign, vec, 0, scale * 0.07000000029802322f,
                  scale * 0.699999988079071f, 0.006000000052154064f);
}

