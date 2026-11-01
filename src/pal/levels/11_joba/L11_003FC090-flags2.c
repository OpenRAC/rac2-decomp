#include "include_asm.h"

#include "common.h"
extern u8 *D_L11_001B359C[] __attribute__((sda));
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[][16];
extern u8 D_L11_00188660[];
extern s32 func_002E5CF8(s32,s32,u8 *);
extern void func_002E59F8(s32);
extern void func_00282F20(void *,void *,f32);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(f32 *,const f32 *,const f32 *);
extern s32 func_002ACBC8(void *, s32);
extern f32 func_00283CE0(s32);
extern s32 func_00282948(void *);

void func_PAL_L11_003FC670(u8 *arg0) {
    f32 tmp[4];
    f32 duration;
    u8 *s0 = arg0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    u8 *s2 = D_L11_001B359C[0] + *(s32 *)(s1 + 0x6C) * 256;
    if (D_0019B2E8[D_001A79F0[0]][*(u8 *)(s0 + 0xB0)] & 0x80) return;
    if (*(u8 *)(s0 + 0x20) == 0) {
        if (*(s16 *)(s0 + 0xAA) == 0xB71) *(u32 *)(s1 + 0x5C) |= 1;
        *(u8 *)(s0 + 0x20) = 1;
    }
    if (*(u8 *)(s0 + 0x20) == 1) {
        if (func_002ACBC8(s2 + 0x10, *(s32 *)(s1 + 0x60))) {
            u8 *v;
            *(u8 *)(s0 + 0x20) = 2;
            v = D_L11_00188660 + *(s32 *)(s1 + 0x70) * 0x70;
            if (*(u8 **)(v + 0x88) != s0 || *(u8 *)(v + 0x74) == 0)
                *(s32 *)(s1 + 0x70) = func_002E5CF8(0, 4, s0);
            *(s32 *)(s1 + 0x64) = 37;
        }
    }
    if (*(u8 *)(s0 + 0x20) == 2) {
        qcopy(tmp, s0 + 0xC0);
        duration = func_00283CE0(37);
        duration = *(f32 *)(s1 + 0x68) / duration;
        func_00282F20(tmp, tmp, duration);
        func_00282CC0(s0 + 0x10, s0 + 0x10, tmp);
        if (func_00282948(s1 + 0x64)) {
            s32 sound = *(s32 *)(s1 + 0x70);
            if (sound != -1) {
                u8 *v = D_L11_00188660 + sound * 0x70;
                if (*(u8 **)(v + 0x88) == s0 && *(u8 *)(v + 0x74)) func_002E59F8(sound);
            }
            *(s32 *)(s1 + 0x70) = -1;
            *(u8 *)(s0 + 0x20) = 3;
        }
    }
    if (*(u8 *)(s0 + 0x20) == 3) {
        if (!func_002ACBC8(s2 + 0x10, *(s32 *)(s1 + 0x60))) {
            u8 *v = D_L11_00188660 + *(s32 *)(s1 + 0x70) * 0x70;
            if (*(u8 **)(v + 0x88) != s0 || *(u8 *)(v + 0x74) == 0)
                *(s32 *)(s1 + 0x70) = func_002E5CF8(0, 4, s0);
            *(u8 *)(s0 + 0x20) = 4;
            *(s32 *)(s1 + 0x64) = 37;
        }
    }
    if (*(u8 *)(s0 + 0x20) == 4) {
        qcopy(tmp, s0 + 0xC0);
        duration = func_00283CE0(37);
        duration = *(f32 *)(s1 + 0x68) / duration;
        func_00282F20(tmp, tmp, duration);
        func_00282CF0((f32 *)(s0 + 0x10), (f32 *)(s0 + 0x10), tmp);
        if (func_00282948(s1 + 0x64)) {
            s32 sound = *(s32 *)(s1 + 0x70);
            if (sound != -1) {
                u8 *v = D_L11_00188660 + sound * 0x70;
                if (*(u8 **)(v + 0x88) == s0 && *(u8 *)(v + 0x74)) func_002E59F8(sound);
            }
            *(s32 *)(s1 + 0x70) = -1;
            *(u8 *)(s0 + 0x20) = 1;
        }
    }
}
