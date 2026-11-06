#include "include_asm.h"
#include "common.h"

/* func_PAL_L01_003D2EF0, the PAL copy of func_L01_003CEDA0: the same C, where the turn rate takes
   6/5, the subtitle timer's 180 frames and each read of the frame counter take the 5/6 scale. */
extern void func_0029F338(void *a0);
extern void func_002A7750(void *a0, s32 a1, s32 a2);
extern u8 *D_L01_001B255C __attribute__((sda));
extern u8 D_001A7B1C __attribute__((sda));
extern u8 D_0018C958[];
extern u8 D_00189EA0[];
extern u8 D_L01_001BF6C0[];
extern u8 *D_L01_001B264C __attribute__((sda));
extern int D_L01_001A8F40 __attribute__((sda));
extern int D_L01_001A900C __attribute__((sda));
extern float D_L01_001B1FA0 __attribute__((sda));
extern u32 D_001A7390 __attribute__((sda));
extern float func_00283B98(float, float);
extern int func_002ACBC8(void *, int);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern void func_PAL_L01_003D2C38(void *);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_00288308(int);
extern void func_002AD860(int);
extern void func_002B0A18(int, int);
extern void func_0029B3E0(int, int);
extern void func_L00_00429020(int);
extern void func_00288E18(int, int);

void func_PAL_L01_003D2EF0(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68), *q;
    int mode;

    switch (a0[0x20]) {
    case 0:
        if (D_001A7B1C) {
            func_0029F338(a0);
            break;
        }
        *(float *)(a0 + 0x18) += 0.75f;
        *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * 1.5f;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        *(float *)(a0 + 0xF8) = func_00283B98(*(float *)(a0 + 0xF8), 0.094247796f);
        if (func_002ACBC8(D_00189EA0, *(int *)(p + 4))) {
            p = D_L01_001BF6C0;
            if (func_00288AA0(p, 0x26)) {
                func_00288BE8(p);
                func_002A7750(a0, 2, -1);
            }
        }
        if (a0[0x31])
            func_PAL_L01_003D2C38(a0);
        break;
    case 2:
        mode = D_L01_001A8F40;
        (*(u16 *)(a0 + 0x96))++;
        if (mode == 2) {
            a0[0x31] = 0;
            *(u16 *)(a0 + 0x34) |= 1;
        }
        if (func_002F5D10())
            break;
        q = D_L01_001B264C + (*(int *)(p + 8) << 7);
        D_L01_001A900C = 0;
        D_L01_001B1FA0 = 0;
        func_L00_002B9D60(q + 0x30, q + 0x70, 0x6F, 1);
        func_00288308(0x24);
        func_002AD860(0x24);
        func_002B0A18(0x1225, -1);
        func_0029B3E0(0, -1);
        if (*(int *)(p + 12) != -1) {
            p = *(u8 **)(D_L01_001B255C + (*(int *)(p + 12) << 8) + 0x68);
            if (!*(int *)(p + 0x3C)) {
                func_L00_00429020(*(int *)(p + 0x38));
                *(int *)(p + 0x3C) = 1;
            }
            p = D_0018C958;
            if (!*(u16 *)(p + 0xC0)) {
                u16 elapsed = *(u16 *)(p + 0xC2);
                u32 start = *(u32 *)(p + 0xC4);
                u32 now = D_001A7390;

                if (start + elapsed >= ((s32)(now) * 5 + 2) / 6 - 2) {
                    *(u16 *)(p + 0xC2) = ++elapsed;
                    if (elapsed >= ((s32)(180) * 5 + 2) / 6) {
                        func_00288E18(0x9B9, 0x10);
                        *(u16 *)(p + 0xC2) = 0;
                    }
                } else {
                    if (start < ((s32)(now) * 5 + 2) / 6)
                        *(u32 *)(p + 0xC4) = ((s32)(now) * 5 + 2) / 6;
                    *(u16 *)(p + 0xC2) = 0;
                }
            }
        }
        func_0029F338(a0);
        break;
    }
}
