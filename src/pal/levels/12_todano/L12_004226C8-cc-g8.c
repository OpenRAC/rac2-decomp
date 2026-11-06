/* func_PAL_L12_004226C8, the PAL copy of func_L12_0041D3B0: the same C, where rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_002B0A68 becomes func_PAL_002B15D8; rename func_L12_0041E8F8 becomes func_PAL_L12_00423C50; scale D_L12_001B1DC0 / 2; wrap D_L12_001B1DC0 (((int)({e}) * 5 + 2) / 6). */
#include "common.h"

extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern u8 D_0019B4A8[];
extern s32 D_001A79F0 __attribute__((sda));
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern s32 D_L12_001B1DC0 __attribute__((sda));
/* The burst helper reads a vector at this GP-relative address. */
extern f32 D_L12_001B1DD0[] SDATA(D_L12_001B1DD0);
extern u8 D_00189EA0[];

extern void func_0029F338(void *);
extern s32 func_L12_0041E8E8(void *);
extern void func_PAL_L12_00423C50(void *);
extern void func_002A7750(void *, s32, s32);
extern s32 func_00282948(void *);
/* Eight GPR inputs, four stack inputs and two FP inputs, in their EE ABI order. */
extern void *func_PAL_L00_003FB330(void *, s32, s32, s32, s32, s32, s32, s32,
                         s32, s32, s32, s32, f32, f32);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFEB8(void *, void *, void *, void *, f32);
extern void func_00282F20(void *, void *, f32);
extern void func_PAL_002B15D8(void *, s32, void *, u8, f32, f32, f32, f32);

void func_PAL_L12_004226C8(u8 *self)
{
    u8 *v = *(u8 **)(self + 0x68);
    s32 ready;
    f32 temp[4] __attribute__((aligned(16)));

    switch (self[0x20]) {
    case 0: {
        u16 id;
        s32 packed;

        self[0x20] = 1;
        *(f32 *)(v + 0x10) = *(f32 *)(self + 0x18);
        id = *(u16 *)(self + 0xB2);
        if (D_L12_0021EDF0.flags[(s16)id])
            goto Destroy0;
        packed = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];
        if (id & 1) {
            if ((packed >> 4) & 7)
                goto Destroy0;
            return;
        } else {
            if (!(packed & 7))
                return;
        }
Destroy0:
        func_0029F338(self);
        break;
    }
    case 1: {
        s32 *p1;
        s32 i1;

        ready = 1;
        p1 = (s32 *)v;
        for (i1 = 0; i1 < 3; i1++) {
            if (p1[i1] != -1) {
                if (!func_L12_0041E8E8(D_L12_001B2E9C_gp + (p1[i1] << 8)))
                    ready = 0;
            }
        }
        if (ready)
            self[0x20] = 2;
        break;
    }
    case 4: {
        u8 *b = D_L12_001B2E9C;
        s32 *p4;
        s32 i4;

        *(f32 *)(v + 0xC) += 0.002f;
        *(f32 *)(self + 0x18) += *(f32 *)(v + 0xC);
        p4 = (s32 *)v;
        for (i4 = 0; i4 < 3; i4++) {
            if (p4[i4] != -1)
                *(f32 *)((p4[i4] << 8) + (u32)b + 0x18) += *(f32 *)(v + 0xC);
        }
        if (*(f32 *)(v + 0x10) + 8.0f < *(f32 *)(self + 0x18))
            self[0x20] = 5;
        break;
    }
    case 2:
        func_002A7750(self, 3, -1);
        *(s32 *)(v + 0x14) = (((int)(D_L12_001B1DC0) * 5 + 2) / 6);
        break;

    case 3: {
        s32 *p3;
        s32 i3;
        s32 *p3b;
        s32 i3b;

        if (func_00282948(v + 0x14)) {
            func_PAL_L00_003FB330(D_L12_001B1DD0, 1, 14, 10, 15, 10, 20, 1,
                          1, 1, 0, 0, 2.0f, 20.0f);
            *(s32 *)(self + 0x98) = 0;
            *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
            func_00282CF0(temp, self + 0x10, D_00189EA0);
            func_002AFEB8(self, temp, temp, 0, 0.0f);
            func_00282F20(temp, temp, 0.120000005f);
            func_PAL_002B15D8(self, 0xFFF, temp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            func_002A7750(self, 5, -1);
            p3 = (s32 *)v;
            for (i3 = 0; i3 < 3; i3++) {
                if (p3[i3] != -1) {
                    D_L12_001B2E9C_gp[(p3[i3] << 8) + 0x20] = 4;
                    func_PAL_L12_00423C50(D_L12_001B2E9C + (p3[i3] << 8));
                }
            }
        }
        if (*(s32 *)(v + 0x14) == (((int)(D_L12_001B1DC0 / 2) * 5 + 2) / 6)) {
            p3b = (s32 *)v;
            for (i3b = 0; i3b < 3; i3b++) {
                if (p3b[i3b] != -1)
                    D_L12_001B2E9C_gp[(p3b[i3b] << 8) + 0x20] = 4;
            }
        }
        break;
    }
    case 5: {
        u8 *b, *child, *counter;
        u16 id;
        s32 *p5;
        s32 i5;

        p5 = (s32 *)v;
        for (i5 = 0; i5 < 3; i5++) {
            if (p5[i5] != -1) {
                b = D_L12_001B2E9C_gp;
                child = (u8 *)((p5[i5] << 8) + (u32)b);
                *(u16 *)(child + 0x34) &= 0xEFFF;
                func_0029F338(b + (p5[i5] << 8));
            }
        }
        id = *(u16 *)(self + 0xB2);
        if (id & 1) {
            counter = &D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];
            if (((*counter >> 4) & 7) != 7)
                *counter += 16;
        } else {
            counter = &D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];
            if ((*counter & 7) != 7)
                *counter += 1;
        }
        func_0029F338(self);
        break;
    }
    }
}
