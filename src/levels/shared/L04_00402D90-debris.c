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

/* Spawns a piece of flying debris from a parent moby with random speed, spin and lifetime. */
unsigned char *debris_spawn(unsigned char *parent, int kind, void *position, void *rotation, int lifetime, int flags, void *velocity, void *spin, void *scale, float gravity, float width)
{
    float scratch[4];
    unsigned char *debris = CreateMoby(kind);
    unsigned char *debrisVars;
    float angle, speed, unit;
    if (debris) {
        float ratio = *(float *)(parent + 0x2c) / *(float *)(*(unsigned char **)(parent + 0x24) + 0x24);
        *(float *)(debris + 0x2c) = *(float *)(*(unsigned char **)(debris + 0x24) + 0x24) * ratio;
        debris[0x31] = 1;
        *(unsigned short *)(debris + 0x34) |= 0x100;
        debrisVars = *(unsigned char **)(debris + 0x68);
        *(unsigned long long *)(debris + 0x38) = *(unsigned long long *)(parent + 0x38);
        debris[0x20] = 1;
        qcopy((debris + 0x10), position);
        euler_rotation_basis(debris + 0xc0, rotation);
        debris[0x30] = 255;
        *(short *)(debris + 0x32) = 128;
        *(int *)(debris + 0x98) = 0;
        if (lifetime == 0) *(short *)(debrisVars + 0x30) = FloatToInt(math_random_float_range(60.0f, 120.0f));
        else *(short *)(debrisVars + 0x30) = lifetime;
        *(int *)(debrisVars + 0x34) = flags;
        *(short *)(debrisVars + 0x32) = 0;
        if (*(float *)(debrisVars + 0x38) == 0.0f) *(float *)(debrisVars + 0x38) = math_random_float_range(10.0f, 15.0f) * 0.00027777778f;
        else *(float *)(debrisVars + 0x38) = gravity;
        if (width != 0.0f) {
            *(float *)(debrisVars + 0x3c) = width;
            *(int *)(debrisVars + 0x34) |= 4;
        }
        if (FastVecLength(velocity) == 0.0f) {
            angle = math_random_angle();
            unit = 0.016666668f;
            speed = math_random_float_range(2.0f, 4.0f) * unit;
            scratch[0] = math_fast_sin_or_cos_a(angle) * speed;
            scratch[1] = math_fast_sin_or_cos_b(angle) * speed;
            scratch[2] = 0.0f;
            scratch[2] = math_random_float_range(5.0f, 8.0f) * unit;
            qcopy(debrisVars, scratch);
        } else qcopy(debrisVars, velocity);
        if (FastVecLength(spin) == 0.0f) {
            vec_random_direction(scratch, 0.052359886f, 0.10471977f);
            qcopy((debrisVars + 0x10), scratch);
        } else qcopy((debrisVars + 0x10), spin);
        if (FastVecLength(scale) == 0.0f && ((float *)scale)[3] == 0.0f) {
            float scaleFactor;
            qcopy(scratch, (*(unsigned char **)(debris + 0x24) + 0x30));
            scaleFactor = *(float *)(debris + 0x2c) * 0.0009765625f;
            FastVecScale(scratch, scratch, scaleFactor);
            scratch[3] = scratch[3] * scaleFactor;
            qcopy((debrisVars + 0x20), scratch);
        } else qcopy((debrisVars + 0x20), scale);
        func_002A0F48(debris);
    }
    return debris;
}
