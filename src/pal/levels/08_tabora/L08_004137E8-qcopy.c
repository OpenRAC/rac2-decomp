#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern s32 func_0029EFD0(s32 size);
extern f32 func_002A7940(void);
extern s32 func_L02_003A8770(void *a0, s32 a1);
extern void func_0026FEB8(void *a0);
extern void func_0029F338(void *a0);
extern u8 D_L08_001B14F0[];
typedef int V4 __attribute__((mode(TI)));

s32 func_PAL_L08_00414850(void *a0, void *a1, void *a2, f32 p1, f32 p2)
{
    u8 *m;
    u8 *p;
    u8 *st;
    f32 v;
    s32 r;

    m = (u8 *)func_0029EFD0(0xE78);
    if (m != 0) {
        st = *(u8 **)(m + 0x68);
        p = m + 0x10;
        *(u8 *)(m + 0x30) = 0x40;
        *(u8 *)(m + 0xBC) = 0;
        *(u8 *)(m + 0x95) = 0;
        *(u8 *)(m + 0x20) = 0;
        *(u32 *)(st + 0x18) = (u32)a0;
        *(V4 *)p = *(V4 *)a1;
        *(V4 *)st = *(V4 *)a2;
        *(f32 *)(st + 0x14) = p1 * 0.0003490659f;
        *(f32 *)(st + 0x10) = p2 * 0.00040000002f;
        v = func_002A7940();
        *(f32 *)(m + 0xF0) = v;
        v = func_002A7940();
        *(f32 *)(m + 0xF4) = v;
        v = func_002A7940();
        *(f32 *)(m + 0xF8) = v;
        r = func_L02_003A8770(p, 0);
        *(u32 *)(st + 0x1C) = r;
        if (r == 0) {
            func_0026FEB8(D_L08_001B14F0);
            func_0029F338(m);
            m = 0;
        }
    }
    return (s32)m;
}
