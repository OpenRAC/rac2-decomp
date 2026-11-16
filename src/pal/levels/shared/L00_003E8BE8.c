#include "include_asm.h"

#include "common.h"
extern void FastVecScale(void *, void *, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern char g_effect_definitions[];
extern char g_default_vector[] __attribute__((sda));
#include "common.h"

/* Throws out bright particles in a short line from an object's position (PAL: 50 Hz timings). */
void part_spawn_line_at_moby_pal(char *moby) {
    float a[3];
    float b[3];
    float c[3];
    float d[3];
    char *definitions;
    int n;
    char *particle;
    char *vars;
    float big;
    int i;

    vars = *(char **)(moby + 0x68);
    { float *p = (float *)(vars + 0x14);
    a[0] = p[0];
    a[1] = p[1];
    a[2] = p[2]; }
    a[3] = 0.0f;
    FastVecScale(b, moby + 0xD0, -0.1f);
    FastVecAdd(a, a, b);
    FastVecScale(c, moby + 0xE0, 0.15f);
    FastVecAdd(a, a, c);
    FastVecScale(c, moby + 0xE0, -0.033333335f);
    definitions = g_effect_definitions;
    for (i = 8; i >= 0; i--) {
        d[0] = a[0] + math_random_signed_float_range(0.0f, 0.1f);
        d[1] = a[1] + math_random_signed_float_range(0.0f, 0.1f);
        d[2] = a[2] + math_random_signed_float_range(0.0f, 0.1f);
        n = math_random_int_below(0xFF);
        big = 42000.0f;
        part_spawn_gravity_fade(d, g_default_vector, 3, 0x808080, n, 0x7F, 0x7F, big, big, 0.0f, 1);
        big = 273000.0f;
        particle = part_spawn_gravity_fade(a, g_default_vector, 3, 0x406080, n, 0x10, 0x10, big, big, 0.0f, 1);
        if (particle != 0)
            *(unsigned char *)(particle + 2) = *(unsigned char *)(*(unsigned *)(definitions + 0xD4));
        FastVecAdd(a, a, c);
    }
}

