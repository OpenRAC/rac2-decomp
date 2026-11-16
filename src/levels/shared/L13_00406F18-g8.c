#include "include_asm.h"

#include "common.h"

extern float g_sign_sparkle_scale __attribute__((sda));

extern int g_sign_sparkle_flags_a __attribute__((sda));

extern int g_sign_sparkle_flags_b __attribute__((sda));

extern int g_sparkle_effect_type_a __attribute__((sda));

extern int g_sparkle_effect_type_b __attribute__((sda));

extern float g_sign_sparkle_scale_factor __attribute__((sda));

extern int func_003249F0(int, int);

extern float func_00324B10(void);

extern void ref_L13_0040DE50_00(void *, int, float, int, float, float, int, int, void *);

/* draws the two halves of the sign band, each from its own colour pair */
void part_draw_sign_band_sparkles(char *object) {
    int value;
    int value2;
    float scale;
    float scale2;
    float random;
    scale = g_sign_sparkle_scale;
    scale *= *(float *)(object + 0x2C);
    value = func_003249F0(95, 111);
    random = func_00324B10();
    ref_L13_0040DE50_00(object + 0x10, g_sparkle_effect_type_a, scale, value, random, 1.0f, g_sign_sparkle_flags_a, 2, object);
    scale2 = g_sign_sparkle_scale;
    scale2 *= *(float *)(object + 0x2C);
    scale2 *= g_sign_sparkle_scale_factor;
    value2 = func_003249F0(111, 127);
    random = func_00324B10();
    ref_L13_0040DE50_00(object + 0x10, g_sparkle_effect_type_b, scale2, value2, random, 1.0f, g_sign_sparkle_flags_b, 2, object);
}
