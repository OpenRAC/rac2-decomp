#include "common.h"
extern unsigned char *func_0029EFD0(int);
extern void func_002833F0(void *, void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002A7A00(void *, float, float);
extern void func_002A0F48(void *);

/* Spawns a piece of flying debris from a parent moby with random speed, spin and lifetime. */
unsigned char *func_L04_00407078(unsigned char *parent, int kind, void *position, void *rotation, int lifetime, int flags, void *velocity, void *spin, void *scale, float gravity, float width)
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
        if (lifetime == 0) *(short *)(debrisVars + 0x30) = FloatToInt(RandomFloatRange(60.0f, 120.0f));
        else *(short *)(debrisVars + 0x30) = lifetime;
        *(int *)(debrisVars + 0x34) = flags;
        *(short *)(debrisVars + 0x32) = 0;
        if (*(float *)(debrisVars + 0x38) == 0.0f) *(float *)(debrisVars + 0x38) = RandomFloatRange(10.0f, 15.0f) * 0.00027777778f;
        else *(float *)(debrisVars + 0x38) = gravity;
        if (width != 0.0f) {
            *(float *)(debrisVars + 0x3c) = width;
            *(int *)(debrisVars + 0x34) |= 4;
        }
        if (FastVecLength(velocity) == 0.0f) {
            angle = RandomAngle();
            unit = 0.016666668f;
            speed = RandomFloatRange(2.0f, 4.0f) * unit;
            scratch[0] = FastSinOrCosA(angle) * speed;
            scratch[1] = FastSinOrCosB(angle) * speed;
            scratch[2] = 0.0f;
            scratch[2] = RandomFloatRange(5.0f, 8.0f) * unit;
            qcopy(debrisVars, scratch);
        } else qcopy(debrisVars, velocity);
        if (FastVecLength(spin) == 0.0f) {
            RandomDirectionVector(scratch, 0.052359886f, 0.10471977f);
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
