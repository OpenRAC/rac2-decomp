#include "include_asm.h"


#include "common.h"
extern s32 *D_L12_001FEAC0[];
extern s32 *D_L12_001FEAC0[];
extern s32 CollLine(void *from, void *to, s32 mode, void *self, s32 flags);
extern s32 *D_L12_001FEAC0[];
extern f32 math_fabs(f32);
extern f32 vec_distance_xy(void *, void *);
extern s32 math_random_int_range(s32, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern s32 D_L12_001B20C0 __attribute__((sda));
extern u8 D_001395DB;
extern s32 math_random_int_below(s32);
extern s32 FloatToInt(f32);
extern void math_random_planar_offset(f32 *, f32);
extern u8 *func_PAL_002BE9A8(void *, f32, f32, f32, s32, void *, f32, u32, s32);

/* Retail tests the first allocation again after its second and third calls;
 * preserve that behavior instead of changing the test to the newer pointer. */
void func_PAL_L12_0042E990(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    f32 pos[4];
    f32 velocity[4];
    u8 *p;
    u8 *q;

    qcopy(pos, self + 0x10);
    pos[2] = *(f32 *)(state + 0x7C);
    math_random_planar_offset(velocity, 0.6f);
    velocity[2] = 0.10000001f;
    p = func_PAL_002BE9A8(pos, 0.1f, 1.0f, 0.9f, math_random_int_below(16), velocity, 420000.0f, 0xDF202020, 0);
    if (p) {
        u8 *d = p + 0x20;
        *(u16 *)(p + 10) = 8;
        p[9] = FloatToInt(4.0f) + 0x70;
        *(s32 *)(d + 4) = 2;
        d[10] = 0xDF;
        d[11] = p[10];
        p[3] = 0x44;
    }
    math_random_planar_offset(velocity, 0.6f);
    velocity[2] = 0.10000001f;
    q = func_PAL_002BE9A8(pos, 0.1f, 1.0f, 0.9f, math_random_int_below(16), velocity, 420000.0f, 0xDF208080, 0);
    if (p) {
        u8 *d = q + 0x20;
        *(u16 *)(q + 10) = 8;
        q[9] = FloatToInt(4.0f) + 0x70;
        *(s32 *)(d + 4) = 2;
        d[10] = 0xDF;
        d[11] = q[10];
        q[3] = 0x48;
    }
    math_random_planar_offset(velocity, 0.40000004f);
    velocity[2] = 0.10000001f;
    q = func_PAL_002BE9A8(pos, 0.1f, 1.0f, 0.9f, math_random_int_below(16), velocity, 420000.0f, 0xDF808080, 0);
    if (p) {
        u8 *d = q + 0x20;
        *(u16 *)(q + 10) = 8;
        q[9] = FloatToInt(4.0f) + 0x70;
        *(s32 *)(d + 4) = 2;
        d[10] = 0xDF;
        d[11] = q[10];
        q[3] = 0x44;
    }
}



