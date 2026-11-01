#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L09_00415440);



#include "common.h"
extern s32 func_002A77E0(s32);
extern u8 *func_PAL_002BE9A8(void *, f32, f32, f32, s32, void *, f32, u32, s32);
extern s32 func_00283CF0(f32);

/* Spawn two colored particles and one white particle below the object. */
void func_PAL_L09_00415E28(u8 *arg)
{
    f32 vel[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    s32 count;
    u8 *first;
    vel[0] = 0.0f;
    vel[2] = -0.5f;
    vel[3] = 1.0f;
    vel[1] = 0.0f;
    count = func_002A77E0(16);
    if (func_002A77E0(2)) count = -count;
    qcopy(pos, arg + 0x10);
    pos[2] -= 0.25f;
    first = func_PAL_002BE9A8(pos, 0.1f, 1.0f, 0.9f, count, vel, 420000.0f, 0xdf204080, 0);
    if (first) {
        u8 *data = first + 0x20;
        *(s16 *)(first + 0xa) = 8;
        first[9] = func_00283CF0(4.0f) + 112;
        *(s32 *)(data + 4) = 2;
        data[0xa] = 0xdf;
        data[0xb] = first[0xa];
    }
    {
        u8 *p = func_PAL_002BE9A8(pos, 0.1f, 1.0f, 0.9f, count, vel, 420000.0f, 0xdf204080, 0);
        if (p) {
            u8 *data = p + 0x20;
            /* Retail updates the first particle here as well. */
            *(s16 *)(first + 0xa) = 8;
            first[9] = func_00283CF0(4.0f) + 112;
            *(s32 *)(data + 4) = 2;
            data[0xa] = 0xdf;
            data[0xb] = first[0xa];
        }
    }
    {
        u8 *p = func_PAL_002BE9A8(pos, 0.05f, 1.0f, 0.97f, 16, vel, 210000.0f, 0xdfffffff, 0);
        if (p) {
            u8 *data = p + 0x20;
            p[9] = func_00283CF0(4.0f) + 112;
            *(s16 *)(p + 0xa) = 4;
            p[8] = func_002A77E0(255);
            *(s32 *)(data + 4) = 2;
            data[0xa] = 0xdf;
            data[0xb] = first[0xa];
        }
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L09_0041FC4C);
