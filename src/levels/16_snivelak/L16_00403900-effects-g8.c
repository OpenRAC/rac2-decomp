#include "include_asm.h"
#include "names.h"

extern int math_random_int_range(int, int);
extern float math_random_angle(void);

extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void gfx_draw_beam_quads_glows_alt(void *, int, float, int, float, float, int, int, void *);
extern float D_L16_001B1948 __attribute__((sda));
extern float D_L16_001B194C __attribute__((sda));
extern int D_L16_001B1940 __attribute__((sda));
extern int D_L16_001B1944 __attribute__((sda));
extern int D_L16_001B1908 __attribute__((sda));
extern int D_L16_001B190C __attribute__((sda));
/* Draws two glowing sprites at the object, one bigger than the other. */
void gfx_draw_two_glow_sprites(char *object) {
    int value;
    int value2;
    float scale;
    float scale2;
    float random;
    scale = D_L16_001B1948;
    scale *= *(float *)(object + 0x2C);
    value = math_random_int_range(95, 111);
    random = math_random_angle();
    gfx_draw_beam_quads_glows_alt(object + 0x10, D_L16_001B1908, scale, value, random, 1.0f, D_L16_001B1940, 2, object);
    scale2 = D_L16_001B1948;
    scale2 *= *(float *)(object + 0x2C);
    scale2 *= D_L16_001B194C;
    value2 = math_random_int_range(111, 127);
    random = math_random_angle();
    gfx_draw_beam_quads_glows_alt(object + 0x10, D_L16_001B190C, scale2, value2, random, 1.0f, D_L16_001B1944, 2, object);
}
