/* func_PAL_L00_003EE450, the PAL copy of func_L00_003EA188: the same C, where the lifetime 60 becomes 50, 1/60 becomes 0.020000001f and the brightness is scaled by 1.44. */
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


void func_PAL_L00_003EE450(void *position, int count, float brightness)
{
    float velocity[4], lateral[4], axis[4], projected[4];
    func_00282CF0(lateral, D_L00_001B8DC0, position);
    if (D_L00_001A8FF0[0] == 0) {
        lateral[2] = 0.0f;
        axis[0] = 0.0f;
        axis[1] = 0.0f;
        axis[3] = axis[2] = 1.0f;
    } else {
        func_00282CF0(projected, position, D_00189ED0);
        func_00282F20(axis, projected, 1.0f);
        func_00282D30(projected, axis, func_00282DB0(axis, lateral));
        func_00282CF0(lateral, lateral, projected);
    }
    if (count > 0) {
        do {
            char *particle;
            float angle;
            float scaled;
            float size = func_002A7878(D_L00_001B06F8, D_L00_001B06FC);
            int spin = func_002A77E0(2);
            if (!spin)
                spin--;
            angle = func_002A7878(-1.0471977f, 1.0471977f);
            func_002ACEC0(velocity, lateral, axis, angle);
            func_00282F20(velocity, velocity, func_002A7878(D_L00_001B06E4, D_L00_001B06E8) * 0.020000001f);
            velocity[2] = func_002A7878(D_L00_001B06EC, D_L00_001B06F0) * 0.020000001f;
            func_00282C88((VectorBits *)velocity);
            scaled = brightness * 1.44f;
            particle = func_002C2210(position, 50, size * 0.1f, size,
                                     0x7F7F2020, 0, spin, velocity, scaled, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(position, 50, size * 0.07f, size * 0.7f,
                                     0x7FFF4040, 1, -spin, velocity, scaled, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = func_00283CF0(4.0f) + 0x70;
        } while (--count);
    }
}
