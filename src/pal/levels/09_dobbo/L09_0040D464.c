#include "include_asm.h"


#include "common.h"
typedef int Quad_Dobbo __attribute__((mode(TI)));
extern float func_002A7878(float, float);
extern void func_0029FCC0(char *, int, void *);
extern float func_00283CE0(int);
extern char *func_002BAE50(void *, void *, int, int, int, int, int, int);

void func_PAL_L09_0040E1C0(char *obj)
{
    float pos[3];
    float vel[3];
    float initial[3];
    int i;
    *(Quad_Dobbo *)initial = 0;
    initial[2] = -(func_002A7878(3.5f, 4.5f) * 0.020000001f);
    *(Quad_Dobbo *)vel = *(Quad_Dobbo *)initial;
    for (i = 0; i < 2; i++) {
        func_0029FCC0(obj, 2, pos);
        pos[2] += func_00283CE0(i) * 0.015f;
        if (i & 1)
            func_002BAE50(pos, vel, 0x77FF0000, 0xFF0060, 14, 150, -100, 1);
        else
            func_002BAE50(pos, vel, 0x77FF0060, 0xFF0000, 16, 220, -100, 1);
        func_002BAE50(pos, vel, 0x77FFFFFF, 0xFF0000, 8, 80, -80, 1);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L09_0040E300);

INCLUDE_ASM("asm/pal/levels", func_PAL_L09_0040F3A0);

INCLUDE_ASM("asm/pal/levels", func_PAL_L09_0040FD68);
