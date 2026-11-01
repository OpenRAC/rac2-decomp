#include "include_asm.h"

#include "common.h"
extern void func_0029F338(void *a0);
extern u32 D_L01_001BF918[];
extern u32 g_pHeroMoby[];
extern s32 func_3120A8(void *a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5,
                      u32 a6, f32 f12, f32 f13);
extern s32 func_355780(u32 a0, u32 a1, void *a2);
extern void func_002A7750(void *a0, s32 a1, s32 a2);
extern u8 *D_L01_001B255C_sda[] __attribute__((sda));
extern u8 *D_L01_001FE180[];
extern u8 *D_L01_001B255C __attribute__((sda));
extern u32 D_L01_001FFE80[];
extern u8 D_001A7B1C __attribute__((sda));
extern u8 D_0018C958[];
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
extern void func_L01_003CEB00(void *);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_00288308(int);
extern void func_002AD860(int);
extern void func_US2_002B1880(int, int);
extern void func_0029B3E0(int, int);
extern void func_L00_00429020(int);
extern void func_US2_00289840(int, int);
extern s32 func_L01_00337A60(void *a0, void *a1, void *a2, s32 a3);
extern s32 func_00283CF0(f32 a0);
extern s32 D_L01_001B2578[] __attribute__((sda));
extern u16 *D_L01_001FB020[];
extern u8 D_00189EA0[];
extern f32 func_002A96A0(void *, void *);
extern u8 *func_002AB1F0(u8 *);
extern f32 func_00283CE0(s32);

/* func_L01_003CE868 is defined in L01_003CE868-g8.c. */

/* Three states on the byte at +0x20: 0 raises the moby by 0.75 and sets its scale to 1.5 times
   the class value (or frees it while D_001A7B1C is set); 1 turns it (+0xF8) and, once the point
   D_00189EA0 lies in the cuboid its vars name at +4, queues movie 0x26 (QueueMovie) and enters
   state 2; 2 bumps the counter at +0x96, waits for func_002F5D10, then runs the level calls for
   the entry its vars name at +8, flags the object named at +0xC once, steps the subtitle history
   timer of entry 16 (TryQueueSubtitleSelection 0x9B9 after 180 frames) and frees the moby.
   The timer's three loads keep their retail order only when the frame counter is read last. */
void func_US2_L01_003D01F8(u8 *a0)
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
        *(float *)(a0 + 0xF8) = func_00283B98(*(float *)(a0 + 0xF8), 0.078539826f);
        if (func_002ACBC8(D_00189EA0, *(int *)(p + 4))) {
            p = D_L01_001BF6C0;
            if (func_00288AA0(p, 0x26)) {
                func_00288BE8(p);
                func_002A7750(a0, 2, -1);
            }
        }
        if (a0[0x31])
            func_L01_003CEB00(a0);
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
        func_US2_002B1880(0x1225, -1);
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

                if (start + elapsed >= now - 2) {
                    *(u16 *)(p + 0xC2) = ++elapsed;
                    if (elapsed >= 180) {
                        func_US2_00289840(0x9B9, 0x10);
                        *(u16 *)(p + 0xC2) = 0;
                    }
                } else {
                    if (start < now)
                        *(u32 *)(p + 0xC4) = now;
                    *(u16 *)(p + 0xC2) = 0;
                }
            }
        }
        func_0029F338(a0);
        break;
    }
}

