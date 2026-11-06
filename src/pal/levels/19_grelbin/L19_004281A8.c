/* func_PAL_L19_004289C0, the PAL copy of func_L19_00423270: the same C, where 0.016666668f becomes
   0.020000001f and the fade 255 - x over 255 becomes 212 - (x * 5 + 2) / 6 over 212. The scale makes
   the loop too long for loop.c to hoist its constants, so the floats stay literals in the loop and
   the 20 is a local set before it, which lets i * spacing still reduce to a counter. */
#include "include_asm.h"
#include "common.h"

extern char D_L19_001B9A40[];
extern float D_L19_001B1ECC[] SDATA(D_L19_001B1ECC);
extern float D_L19_001B1ED0[] SDATA(D_L19_001B1ED0);
extern float D_L19_001B1ED4[] SDATA(D_L19_001B1ED4);
extern float D_L19_001B1ED8[] SDATA(D_L19_001B1ED8);
extern u8 D_L19_001B1EDC[] SDATA(D_L19_001B1EDC);
extern int D_L19_001B1EE0[] SDATA(D_L19_001B1EE0);
extern int D_L19_001B1EE4[] SDATA(D_L19_001B1EE4);
extern float D_L19_001B1EE8[] SDATA(D_L19_001B1EE8);
extern float D_L19_001B1EEC[] SDATA(D_L19_001B1EEC);
extern u32 D_L19_001B1EF0[] SDATA(D_L19_001B1EF0);
extern u32 D_L19_001B1EF4[] SDATA(D_L19_001B1EF4);
extern int D_L19_001B1EFC[] SDATA(D_L19_001B1EFC);
extern int D_L19_001B1F00[] SDATA(D_L19_001B1F00);
extern int D_L19_001B2508[] __attribute__((sda));
extern int func_002A77E0(int);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7A00(float *, float, float);
extern void *func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(unsigned int, unsigned int, float);
extern unsigned char *func_002C2FD8(void *, int, unsigned char, int, int, int, int, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

void func_PAL_L19_004289C0(char *obj)
{
    float origin[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float jitter[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    int i, color, alpha, spacing;

    if (*(short *)(obj + 0xAA) == 0x11C7) {
        func_00282F20(point, obj + 0xE0, 1.5f);
        func_00282CC0(origin, obj + 0x10, point);
    } else {
        func_0029FCC0(obj, 0, origin);
    }
    if (!func_002A77E0(4)) {
        func_002A7A00(velocity, D_L19_001B1ECC[0] * 0.020000001f, D_L19_001B1ED0[0] * 0.020000001f);
        {
            int glowAlpha = D_L19_001B1EDC[0];
            func_002C3150(origin, velocity, D_L19_001B1EE0[0], glowAlpha, func_002A77E0(255), 0,
                          D_L19_001B1EE8[0]);
        }
        for (i = 2; i >= 0; i--) {
            func_002A7A00(jitter, D_L19_001B1ED4[0] * 0.020000001f, D_L19_001B1ED8[0] * 0.020000001f);
            func_00282CC0(velocity, velocity, jitter);
            {
                int glowAlpha = D_L19_001B1EDC[0];
                func_002C3150(origin, velocity, D_L19_001B1EE4[0], glowAlpha, func_002A77E0(255), 0,
                              D_L19_001B1EEC[0]);
            }
        }
    }
    func_00282CF0(point, D_L19_001B9A40, origin);
    func_00282F20(point, point, -0.3f);
    func_00282F20(step, point, 0.1f);
    func_00282CC0(point, point, origin);
    spacing = 20;
    for (i = 0; i < 4; i++) {
        color = func_00283D38(D_L19_001B1EF0[0], D_L19_001B1EF4[0],
                              func_00282C48(0.5f - func_00283CE0(212 - (((D_L19_001B2508[0] + i * spacing) & 255) * 5 + 2) / 6) * (1.0f / 212.0f)));
        alpha = *(u8 *)D_L19_001B2508;
        if (i & 2)
            alpha *= 2;
        if (i & 1)
            alpha = 255 - alpha;
        func_002C2FD8(point, color, alpha, D_L19_001B1F00[0], D_L19_001B1EFC[0], 2, 0,
                      (func_00283CE0(i) + 3.0f) * (*(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24)));
        func_00282CC0(point, point, step);
    }
}
