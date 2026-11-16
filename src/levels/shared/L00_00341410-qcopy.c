/* func_L00_00341410 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */
#include "include_asm.h"
#include "names.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct {
    unsigned char unknown_00[0x10];
    Vector position;
    unsigned char unknown_20[0xA0];
    float matrix[16];
} ParticleOwner;
extern unsigned char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern unsigned char *g_forward_particle_byte;
extern void vec_clear_128(Quadword *);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void FastVecAdd(void *, const void *, const void *);
extern void moby_get_facing_direction(void *, void *);
extern void FastVecScale(void *, const void *, float);

/* Spawns a fast particle at a position (or in front of the owner) and sends it forward from the owner. */
unsigned char *part_spawn_owner_forward(ParticleOwner *owner, Quadword *position,
                              int flags, int minimum, int maximum, float scale) {
    union { Quadword q; float f[4]; } direction;
    unsigned char *particle = part_alloc(0x6E);
    unsigned char *motion;
    Vector *origin;
    int shade;
    if (particle) {
        motion = particle + 0x20;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[3] = flags;
        particle[1] = 0;
        particle[8] = math_random_int_below(255);
        particle[2] = *g_forward_particle_byte;
        *(short *)(particle + 0xA) = math_random_int_range(minimum, maximum);
        *(int *)(motion + 0x18) = *(short *)(particle + 0xA);
        *(float *)(particle + 0xC) = scale * 630000.0f;
        if (((float *)position)[3] == -1.0f) {
            vec_clear_128(&direction.q);
            direction.f[3] = 1.0f;
            direction.f[0] = -0.3f;
            matrix_mul_vec3(&direction, &direction, owner->matrix);
            FastVecAdd(particle + 0x10, &direction, &owner->position);
        } else {
            *(Quadword *)(particle + 0x10) = *position;
        }
        origin = &owner->position;
        *(float *)(particle + 0x10) += math_random_float_range(-0.015f, 0.015f);
        *(float *)(particle + 0x14) += math_random_float_range(-0.015f, 0.015f);
        *(float *)(particle + 0x18) += math_random_float_range(-0.015f, 0.015f);
        moby_get_facing_direction(origin, &direction);
        FastVecScale(motion, &direction, math_random_float_range(0.01f, 0.015f));
        *(int *)(motion + 0x10) = math_random_int_range(80, 200);
        shade = math_random_int_range(96, 128);
        *(int *)(motion + 0x14) = shade + (shade << 8) + (shade << 16);
        *(unsigned int *)(particle + 4) = *(int *)(motion + 0x14) | (*(unsigned int *)(motion + 0x10) << 24);
    }
    return particle;
}
