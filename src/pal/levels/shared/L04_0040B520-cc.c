#include "names.h"
/* func_PAL_L04_0040B520, the PAL copy of func_L04_00407078: the same C, where wrap func_002A7878(60.0f, 120.0f) (({e}) * 5.0f + 2.0f) * 0.. */
#include "common.h"
extern unsigned char *CreateMoby(int);
extern void euler_rotation_basis(void *, void *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_random_direction(void *, float, float);
extern void func_002A0F48(void *);

/* Spawns a debris piece moby of the given kind at a position, with random velocity, spin and lifetime where none is given (PAL: 50 Hz timings). */
unsigned char *debris_spawn_pal(unsigned char *parent, int kind, void *position, void *rotation, int lifetime, int flags, void *velocity, void *spin, void *scale, float gravity, float width)
{
    float vec[4];
    unsigned char *moby = CreateMoby(kind);
    unsigned char *vars;
    float angle, speed, unit;
    if (moby) {
        float ratio = *(float *)(parent + 0x2c) / *(float *)(*(unsigned char **)(parent + 0x24) + 0x24);
        *(float *)(moby + 0x2c) = *(float *)(*(unsigned char **)(moby + 0x24) + 0x24) * ratio;
        moby[0x31] = 1;
        *(unsigned short *)(moby + 0x34) |= 0x100;
        vars = *(unsigned char **)(moby + 0x68);
        *(unsigned long long *)(moby + 0x38) = *(unsigned long long *)(parent + 0x38);
        moby[0x20] = 1;
        qcopy((moby + 0x10), position);
        euler_rotation_basis(moby + 0xc0, rotation);
        moby[0x30] = 255;
        *(short *)(moby + 0x32) = 128;
        *(int *)(moby + 0x98) = 0;
        if (lifetime == 0) *(short *)(vars + 0x30) = FloatToInt(((math_random_float_range(60.0f, 120.0f)) * 5.0f + 2.0f) * 0.16666667f);
        else *(short *)(vars + 0x30) = lifetime;
        *(int *)(vars + 0x34) = flags;
        *(short *)(vars + 0x32) = 0;
        if (*(float *)(vars + 0x38) == 0.0f) *(float *)(vars + 0x38) = math_random_float_range(10.0f, 15.0f) * 0.00040000002f;
        else *(float *)(vars + 0x38) = gravity;
        if (width != 0.0f) {
            *(float *)(vars + 0x3c) = width;
            *(int *)(vars + 0x34) |= 4;
        }
        if (FastVecLength(velocity) == 0.0f) {
            angle = math_random_angle();
            unit = 0.020000001f;
            speed = math_random_float_range(2.0f, 4.0f) * unit;
            vec[0] = math_fast_sin_or_cos_a(angle) * speed;
            vec[1] = math_fast_sin_or_cos_b(angle) * speed;
            vec[2] = 0.0f;
            vec[2] = math_random_float_range(5.0f, 8.0f) * unit;
            qcopy(vars, vec);
        } else qcopy(vars, velocity);
        if (FastVecLength(spin) == 0.0f) {
            vec_random_direction(vec, 0.062831864f, 0.12566373f);
            qcopy((vars + 0x10), vec);
        } else qcopy((vars + 0x10), spin);
        if (FastVecLength(scale) == 0.0f && ((float *)scale)[3] == 0.0f) {
            float size_factor;
            qcopy(vec, (*(unsigned char **)(moby + 0x24) + 0x30));
            size_factor = *(float *)(moby + 0x2c) * 0.0009765625f;
            FastVecScale(vec, vec, size_factor);
            vec[3] = vec[3] * size_factor;
            qcopy((vars + 0x20), vec);
        } else qcopy((vars + 0x20), scale);
        func_002A0F48(moby);
    }
    return moby;
}
