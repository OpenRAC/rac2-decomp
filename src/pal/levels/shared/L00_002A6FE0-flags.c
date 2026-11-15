#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef float f32;
typedef struct {
    u8 pad0[0x10];
    f32 m10[4];
    u8 pad1[0x80 - 0x20];
    f32 v80[4];
    u8 pad2[0x660 - 0x90];
    int f660;
    u8 pad3[0x6B0 - 0x664];
    f32 f6B0;
    u8 pad4[0x6BC - 0x6B4];
    short f6BC;
    u8 pad5[0x7A8 - 0x6BE];
    f32 f7A8;
    f32 f7AC;
    u8 pad6[0x2290 - 0x7B0];
    char *obj;
    int state;
} Owner_002A75D8;
extern Owner_002A75D8 g_hero_state;
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void euler_to_matrix(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);

void func_PAL_L00_002A74C0(void)
{
    Owner_002A75D8 *o = &g_hero_state;
    float v[4];
    float m[16];

    if (o->state == 0x7C)
        math_update_wrapped_angle_offset(o->obj, &o->f7A8, &o->f7AC, 0.3f, 0.13962635f, -1.0f);
    if (o->f6BC == 0)
        return;
    if (o->f660 != 0)
        return;
    *(float *)(o->obj + 0xF4) = o->f6B0;
    *(TI128 *)v = 0;
    v[2] = 2.0f;
    euler_to_matrix(m, o->obj + 0xF0);
    transform_vector(v, v, m);
    FastVecAdd(o->obj + 0x10, o->v80, v);
}
