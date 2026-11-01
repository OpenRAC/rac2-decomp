#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef float f32;
extern u8 *D_L04_001FB1E0[];
extern u8 *D_L04_001B24DC __attribute__((sda));
extern s32 D_001A7340 __attribute__((sda));
extern s32 D_001A7344;
extern f32 D_L04_001B31EC __attribute__((sda));
typedef int TI128 __attribute__((mode(TI)));
extern u16 **D_L04_001A9014;
extern u8 *D_L04_001B2B54;
extern u8 D_L04_001B17E0[8] __attribute__((sda));
extern u8 D_L04_001B17D8[8] __attribute__((sda));
extern u8 D_L04_001B17D0[8] __attribute__((sda));
extern s32 D_L04_001B1800 __attribute__((sda));
extern void func_002A7750(void *a0, s32 a1, s32 a2);
extern void *func_002A9640(void *a0, s32 a1, s32 a2);
extern void func_PAL_L00_0032C600(void *a0, void *a1, void *a2, void *a3, s32 a4, s32 a5, s32 a6,
                              s32 a7, s32 a8, s32 a9, s32 a10);
extern void func_PAL_L00_003281C0(void *a0, s32 a1, f32 f12);
extern void func_L00_00324F18(void *a0, void *a1, f32 f12, f32 f13, f32 f14);
extern void func_PAL_002AC718(void *o, void *a, void *b, f32 f0, f32 f1, s32 i0, s32 i1, s32 i2,
                          f32 f2, f32 f3, f32 f4, f32 f5, s32 i3, f32 f6, s32 i4, s32 i5, s32 i6,
                          s32 i7, s32 i8);
extern void func_0029F338(void *a0);
extern s32 D_L04_001A8F00;
extern u8 D_001A7A40;
extern u8 D_L04_001B1DE0;
extern u8 D_L04_001B1DE1;
extern f32 D_L04_001B1E00;
extern f32 D_L04_001B1E04;
extern f32 D_L04_001B1E08;

/* State 0 arms the object and moves it to state 1; state 1 moves to state 2 once func_002A9640
   finds a match while the state word is clear; state 2 makes the three func_PAL_002AC718 calls,
   sets bit 2 of byte +0x1E of every entity of the group at +4 and calls func_0029F338. */
void func_PAL_L04_0045030C(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    f32 A[4] __attribute__((aligned(16)));
    f32 B[4] __attribute__((aligned(16)));
    u16 *p;
    u8 *e;

    switch (a0[0x20]) {
    case 0:
        a0[0x31] = 0;
        *(u16 *)(a0 + 0x34) |= 1;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x4010000, 0) != 0) {
            if (*(s32 *)state == 0)
                func_002A7750(a0, 2, -1);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_PAL_L00_0032C600(a0, D_L04_001B17E0, D_L04_001B17D8, D_L04_001B17D0, 0x7F, 0,
                          D_L04_001B1800, 1, 0xFFFF, 0xFF, 0);
        func_PAL_L00_003281C0(a0, 5, 0.0f);
        *(TI128 *)A = 0;
        A[2] = 0.20000002f;
        func_L00_00324F18(a0, B, 0.0f, 0.0f, 4.0f);
        func_PAL_002AC718(a0, A, B, 0.0f, 0.0f, 50, 10, 10, 3.0f, 1.0f, 9.0f, 2.25f, -1, 15.0f, 1, 7,
                      -1, 0, 0x810001);
        func_PAL_002AC718(a0, A, B, 0.0f, 0.0f, 5, 1, 1, 0.0f, 0.0f, 9.0f, 2.25f, -1, 0.0f, 0, 0, -1,
                      1, 0x810001);
        func_PAL_002AC718(a0, A, B, 0.0f, 0.0f, 5, 1, 1, 0.0f, 0.0f, 9.0f, 2.25f, -1, 0.0f, 0, 0, -1,
                      2, 0x810001);
        if (*(s32 *)(state + 4) != 0) {
            for (p = D_L04_001A9014[*(s32 *)(state + 4)];
                 p != 0 &&
                 ((p != 0 && (s16)p[-1] >= 0) || p == D_L04_001A9014[*(s32 *)(state + 4)]);
                 p++) {
                e = D_L04_001B2B54 + ((*p & 0x7FFF) << 5);
                if (e == 0)
                    break;
                e[0x1E] |= 4;
            }
        }
        func_0029F338(a0);
        break;
    }
}
