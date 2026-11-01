#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L07_0037B708);

#include "common.h"
extern char D_L07_001B9200[];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_L02_0031E9E8(float *, float);
extern void func_PAL_L07_00338B98(float *, float *, s32, s32);

/* Scatter 200 particles around the camera target, then set the moby's position 4 ahead of it. */
void func_PAL_L07_0037BC50(u8 *m)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 vel[4] __attribute__((aligned(16)));
    f32 ahead[4] __attribute__((aligned(16)));
    f32 *vars = *(f32 **)(m + 0x68);
    s32 i;

    for (i = 0; i < 200; i++) {
        func_L02_0031E9E8(pos, 15.0f);
        pos[2] = func_002A7878(-7.0f, 7.0f);
        func_00282CC0(pos, pos, D_L07_001B9200);
        func_00282D30(ahead, D_L07_001B9200 + 0x230, 4.0f);
        func_00282CC0(pos, ahead, pos);
        func_L02_0031E9E8(vel, vars[0] * 0.020000001f);
        vel[2] = -(vars[1] * 0.020000001f) * func_002A7878(0.8f, 1.2f);
        func_PAL_L07_00338B98(pos, vel, 0, 1);
    }
    func_00282D30(ahead, D_L07_001B9200 + 0x230, 4.0f);
    func_00282CC0(vars + 0x60 / 4, ahead, D_L07_001B9200);
}

