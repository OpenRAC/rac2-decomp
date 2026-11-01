#include "include_asm.h"

#include "common.h"
extern s32 func_0029EFD0(s32 size);
extern f32 func_002A7940(void);
extern u32 g_pHeroMoby[];
extern f32 D_L01_001B1A68 __attribute__((sda));
extern f32 D_L01_001B1A6C __attribute__((sda));
extern f32 D_L01_001B1A70 __attribute__((sda));
extern void func_PAL_L01_0041BFF0(void *a0);

/* Spawns a gold bolt moby at a position, already in its idle state, with random spin angles.
 * Adapted from the state 0 of RAC1's gold_bolt_update (GPL-3.0). */
s32 func_PAL_L01_0041C698(void *a0, void *a1, void *a2, void *a3) {
    u8 *m;
    u8 *st;
    f32 t, x, y, z;

    m = (u8 *)func_0029EFD0(0x1250);
    if (m != 0) {
        st = *(u8 **)(m + 0x68);
        *(u64 *)(m + 0x38) = *(u64 *)((u8 *)g_pHeroMoby[0] + 0x38);
        qcopy(m + 0x10, a0);
        *(u16 *)(m + 0x32) = 0x5A;
        *(u8 *)(m + 0x30) = 0x40;
        *(u8 *)(m + 0x31) = 1;
        *(u32 *)st = (u32)a1;
        qcopy(st + 0x10, m + 0x10);
        t = *(f32 *)(m + 0xF8);
        *(f32 *)(st + 0x1C) = t;
        t = func_002A7940();
        *(f32 *)(m + 0xF0) = t;
        t = func_002A7940();
        *(f32 *)(m + 0xF4) = t;
        t = func_002A7940();
        *(f32 *)(m + 0xF8) = t;
        t = func_002A7940();
        x = D_L01_001B1A68;
        y = D_L01_001B1A6C;
        z = D_L01_001B1A70;
        *(f32 *)(m + 0xFC) = t;
        *(u32 *)(st + 8) = (u32)a3;
        *(u32 *)(st + 4) = (u32)a2;
        *(f32 *)(st + 0x68) = x * 0.0003490659f;
        *(f32 *)(st + 0x64) = y * 0.0003490659f;
        *(f32 *)(st + 0x60) = z * 0.0003490659f;
        *(u8 *)(m + 0x20) = 1;
        func_PAL_L01_0041BFF0(m);
    }
    return (s32)m;
}
