/* func_PAL_L12_004221E8, the PAL copy of func_L12_0041CF10: the same C, where rename func_002B0A68 becomes func_PAL_002B15D8; rename func_L12_0041E8F8 becomes func_PAL_L12_00423C50; rename func_0032C700 becomes func_PAL_L00_003FB330; scale D_L12_001B1DA0 / 2; wrap D_L12_001B1DA0 (((int)({e}) * 5 + 2) / 6). */
#include "common.h"

extern int D_001A79F0 __attribute__((sda));
extern u8 D_0019B4A8[];
extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern int D_L12_001B1DA0 __attribute__((sda));

extern int func_L12_0041E8E8(void *);
extern void func_PAL_L12_00423C50(void *);
extern void func_002A7750(void *, int, int);
extern int func_00282948(void *);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, u8);
/* GPR and FP arguments retain their respective EE ABI order. */
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int,
                         int, int, int, int, float, float);
extern void func_0029F338(void *);

void func_PAL_L12_004221E8(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    float vec[4];
    int ready;

    switch (self[0x20]) {
    case 0: {
        u16 id;

        self[0x20] = 1;
        *(float *)(state + 0x10) = *(float *)(self + 0x18);
        id = *(u16 *)(self + 0xB2);
        if (D_L12_0021EDF0.flags[(s16)id])
            goto Destroy0;
        {
            int packed = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];

            if (id & 1) {
                if ((packed >> 4) & 7)
                    goto Destroy0;
                return;
            } else if (!(packed & 7)) {
                return;
            }
        }
Destroy0:
        func_0029F338(self);
        break;
    }
    case 1: {
        int i;

        ready = 1;
        for (i = 0; i < 3; i++, state += 4) {
            if (*(int *)state != -1) {
                if (!func_L12_0041E8E8(D_L12_001B2E9C_gp + (*(int *)state << 8)))
                    ready = 0;
            }
        }
        if (ready)
            self[0x20] = 2;
        break;
    }
    case 4: {
        int i;
        int *p;
        u8 *base = D_L12_001B2E9C;

        *(float *)(state + 0xC) += 0.002f;
        *(float *)(self + 0x18) += *(float *)(state + 0xC);
        p = (int *)state;
        for (i = 0; i < 3; i++) {
            if (p[i] != -1)
                *(float *)((p[i] << 8) + (u32)base + 0x18) += *(float *)(state + 0xC);
        }
        if (*(float *)(state + 0x10) + 8.0f < *(float *)(self + 0x18))
            self[0x20] = 5;
        break;
    }
    case 2:
        func_002A7750(self, 3, -1);
        *(int *)(state + 0x14) = (((int)(D_L12_001B1DA0) * 5 + 2) / 6);
        break;
    case 3: {
        int i;
        int *p;
        u8 *child;
        u16 id;

        if (func_00282948(state + 0x14)) {
            *(int *)(self + 0x98) = 0;
            *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
            func_00282F20(vec, self + 0xC0, -0.120000005f);
            func_PAL_002B15D8(self, 63, vec, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            p = (int *)state;
            for (i = 0; i < 3; i++, p++) {
                if (*p != -1) {
                    child = D_L12_001B2E9C_gp + (*p << 8);
                    func_PAL_L12_00423C50(child);
                    func_PAL_L00_003FB330(child + 0x10, 1, 14, 10, 15, 10, 20, 1,
                                  1, 1, 0, 0, 2.0f, 20.0f);
                    func_0029F338(D_L12_001B2E9C + (*p << 8));
                }
            }
            id = *(u16 *)(self + 0xB2);
            if (id & 1) {
                u8 *counter = (u8 *)(((s16)id >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
                u8 packed = *counter;

                if (((packed >> 4) & 7) != 7)
                    *counter = packed + 16;
            } else {
                u8 *counter = (u8 *)(((s16)id >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
                u8 packed = *counter;

                if ((packed & 7) != 7)
                    *counter = packed + 1;
            }
            func_0029F338(self);
            break;
        }
        if (*(int *)(state + 0x14) == (((int)(D_L12_001B1DA0 / 2) * 5 + 2) / 6)) {
            int *p2 = (int *)state;
            int i2;

            for (i2 = 0; i2 < 3; i2++, p2++) {
                if (*p2 != -1)
                    ((u8 *)((*p2 << 8) + (u32)D_L12_001B2E9C_gp))[0x20] = 4;
            }
        }
        break;
    }
    case 5: {
        int i;
        u8 *child;
        u16 id;

        for (i = 0; i < 3; i++, state += 4) {
            if (*(int *)state != -1) {
                u8 *base = D_L12_001B2E9C_gp;

                child = (u8 *)((*(int *)state << 8) + (u32)base);
                *(u16 *)(child + 0x34) &= 0xEFFF;
                func_0029F338(base + (*(int *)state << 8));
            }
        }
        id = *(u16 *)(self + 0xB2);
        if (id & 1) {
            u8 *counter = (u8 *)(((s16)id >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
            u8 packed = *counter;

            if (((packed >> 4) & 7) != 7)
                *counter = packed + 16;
        } else {
            u8 *counter = (u8 *)(((s16)id >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
            u8 packed = *counter;

            if ((packed & 7) != 7)
                *counter = packed + 1;
        }
        func_0029F338(self);
        break;
    }
    }
}
