#include "common.h"

/* The unsized macro-address view preserves the absolute flag load at -G8. */
extern float D_L00_001B8DC0[4];
extern float D_00189ED0[4];
extern int D_L00_001A8FF0[] MACRO_ADDR;
extern float D_L00_001B06E4 __attribute__((sda));
extern float D_L00_001B06E8 __attribute__((sda));
extern float D_L00_001B06EC __attribute__((sda));
extern float D_L00_001B06F0 __attribute__((sda));
extern float D_L00_001B06F8 __attribute__((sda));
extern float D_L00_001B06FC __attribute__((sda));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
typedef int VectorBits __attribute__((mode(TI)));
extern void func_00282C88(VectorBits *);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, float, int);
extern int func_00283CF0(float);

/* Spray paired particles perpendicular to the viewing direction. */
/* Sprays small bright sparks out sideways from a point. */
void func_L00_003EA188(void *position, int count, float brightness)
{
    float velocity[4], lateral[4], axis[4], projected[4];
    FastVecSub(lateral, gCameraPosition_L00, position);
    if (D_L00_001A8FF0[0] == 0) {
        lateral[2] = 0.0f;
        axis[0] = 0.0f;
        axis[1] = 0.0f;
        axis[3] = axis[2] = 1.0f;
    } else {
        FastVecSub(projected, position, D_00189ED0);
        vec_scale_to_length(axis, projected, 1.0f);
        FastVecScale(projected, axis, FastVecDot(axis, lateral));
        FastVecSub(lateral, lateral, projected);
    }
    if (count > 0) {
        do {
            char *particle;
            float angle;
            float size = RandomFloatRange(D_L00_001B06F8, D_L00_001B06FC);
            int spin = RandomIntBelow(2);
            if (!spin)
                spin--;
            angle = RandomFloatRange(-1.0471977f, 1.0471977f);
            ApplyAxisRotationToQuaternion(velocity, lateral, axis, angle);
            vec_scale_to_length(velocity, velocity, RandomFloatRange(D_L00_001B06E4, D_L00_001B06E8) * (1.0f / 60.0f));
            velocity[2] = RandomFloatRange(D_L00_001B06EC, D_L00_001B06F0) * (1.0f / 60.0f);
            ClearVector128((VectorBits *)velocity);
            particle = SpawnGroundEffectParticle(position, 60, size * 0.1f, size,
                                     0x7F7F2020, 0, spin, velocity, brightness, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x70;
            particle = SpawnGroundEffectParticle(position, 60, size * 0.07f, size * 0.7f,
                                     0x7FFF4040, 1, -spin, velocity, brightness, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x70;
        } while (--count);
    }
}
