#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern int math_random_int_below(int);
extern unsigned char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void FastVecSub(void *, const void *, const void *);
extern void FastVecScale(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern Vector D_L20_001A8F20 __attribute__((sda));
extern unsigned char *D_L20_001FFC14;
extern unsigned char *D_L20_001FFBF4;
extern int D_L20_001B2AC8[] __attribute__((sda));

void func_PAL_L20_0039F518(unsigned char *object) {
    Vector delta, position, jitter;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *particle;
    int shade = math_random_int_below(255);
    int count;
    float size;
    particle = part_spawn_gravity_fade(object + 0x10, &D_L20_001A8F20, 2, 0x202080, shade, 64, 16,
                            420000.0f, 420000.0f, 0.0f, 0);
    if (particle) {
        particle[2] = *D_L20_001FFC14;
    }
    particle = part_spawn_gravity_fade(object + 0x10, &D_L20_001A8F20, 2, 0x202080, (shade + 128) % 255, 64, 16,
                            420000.0f, 420000.0f, 0.0f, 0);
    if (particle) {
        particle[2] = *D_L20_001FFC14;
    }
    FastVecSub(&delta, object + 0x10, state);
    FastVecScale(&delta, &delta, 0.1f);
    qcopy(&position, state);
    count = 4;
    do {
        --count;
        shade = math_random_int_below(255);
        size = math_random_float_range(0.1f, 0.3f);
        jitter.f[0] = position.f[0] + math_random_signed_float_range(0.0f, 0.05f);
        jitter.f[1] = position.f[1] + math_random_signed_float_range(0.0f, 0.05f);
        jitter.f[2] = position.f[2] + math_random_signed_float_range(0.0f, 0.05f);
        part_spawn_gravity_fade(&jitter, &D_L20_001A8F20, 12, 0x808080, shade, 32, 0,
                      size * 210000.0f, size * 42000.0f, 0.0f, 0);
        FastVecAdd(&position, &position, &delta);
    } while (count >= 0);
    if (D_L20_001B2AC8[0] % 10 == 0) {
        particle = part_spawn_gravity_fade(object + 0x10, &D_L20_001A8F20, 25, 0x202080, 0, 32, 0,
                                2100.0f, 420000.0f, 0.0f, 0);
        if (particle) {
            particle[2] = *D_L20_001FFBF4;
        }
    }
}
