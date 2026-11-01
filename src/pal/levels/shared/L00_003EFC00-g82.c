#include "include_asm.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern float func_002A7878(float low, float high);
extern void func_0029FCC0(char *object, int joint, void *out);
extern void func_L00_0033C0D0(char *object, void *position, void *velocity, void *parameters, int mode);
extern char D_L00_001B02E8 __attribute__((sda));
extern char D_L00_001B02F8 __attribute__((sda));
extern char D_L00_001B0308 __attribute__((sda));

extern char D_PAL_001B0800 __attribute__((sda));
extern char D_PAL_001B0810 __attribute__((sda));
extern char D_PAL_001B0820 __attribute__((sda));

void func_PAL_L00_003F0390(char *object)
{
    Vector position, velocity, temporary;
    if (*(unsigned char *)(object + 0x31) != 0) {
        temporary.q = 0;
        temporary.v[2] = -(func_002A7878(1.0f, 2.0f) * 0.020000001f);
        velocity.q = temporary.q;
        func_0029FCC0(object, 0, &position);
        func_L00_0033C0D0(object, &position, &velocity, &D_PAL_001B0800, 1);
        func_L00_0033C0D0(object, &position, &velocity, &D_PAL_001B0810, 1);
        func_L00_0033C0D0(object, &position, &velocity, &D_PAL_001B0820, 1);
    }
}


