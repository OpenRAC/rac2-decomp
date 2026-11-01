#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L04_00427F88);

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
extern u8 D_L04_001395C7;
extern u8 D_L04_002CA518;
extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_001395B8[];
extern s32 D_L04_001B2008[] __attribute__((sda));
extern u8 *D_L04_001B25CC[] __attribute__((sda));
extern u8 D_00189EA0[];
extern s32 func_342228(void *a0, void *a1);
extern s32 func_00288AA0(u8 *a0, s32 a1);
extern s32 func_00288BE8(void *a0);
extern float func_002AA3A8(float *a0, float *a1, float f12, float f13, float f14, float f15);
extern void func_002E5CF8(s32 a0, s32 a1, char *a2);
extern u8 D_0019B2E8[];
extern u8 D_L04_001BF880[];
extern u8 D_L04_001B9680[];
extern f32 func_00282E48(void *, void *);
extern f32 func_00283CE0(int);
extern f32 func_00282C48(f32);
extern u8 D_00189EA0[];
extern u8 D_L04_001B1218[];
extern u8 D_L04_001B1230[];
extern u8 D_L04_001B12B0[] __attribute__((sda));
extern u8 D_L04_001B12E8[] __attribute__((sda));
extern u8 D_L04_001B1300[] __attribute__((sda));
extern u8 D_L04_001B1330[] __attribute__((sda));
extern u8 D_L04_001B1348[] __attribute__((sda));
extern u8 D_L04_001B3280[] __attribute__((sda));
extern u8 D_L04_001B32B0[] __attribute__((sda));
extern u8 D_L04_001B32E0[] __attribute__((sda));
extern u8 D_L04_001B3300[] __attribute__((sda));
extern u8 D_L04_001B3320[] __attribute__((sda));
extern u8 D_L04_001B3330[] __attribute__((sda));
extern u8 D_L04_001B3360[] __attribute__((sda));
extern u8 D_L04_001B3378[] __attribute__((sda));
extern u8 D_L04_001B33A0[] __attribute__((sda));
extern u8 D_L04_001B33B0[] __attribute__((sda));
extern u8 D_L04_001B33B8[] __attribute__((sda));
extern u8 D_L04_001B33D8[] __attribute__((sda));
extern u8 D_L04_001B33E8[] __attribute__((sda));
extern u8 D_L04_001B3418[] __attribute__((sda));
extern u8 D_L04_001B3430[] __attribute__((sda));
extern u8 D_L04_001B3458[] __attribute__((sda));
extern u8 D_L04_001B3468[] __attribute__((sda));
extern u8 D_L04_001B3470[] __attribute__((sda));
extern u8 D_L04_001B3474[] __attribute__((sda));
extern u8 D_L04_001B3478[] __attribute__((sda));
extern u8 D_L04_001B347C[] __attribute__((sda));
extern u8 D_L04_001B3480[] __attribute__((sda));
extern u8 D_L04_001B3484[] __attribute__((sda));
extern u8 D_L04_001B3488[] __attribute__((sda));
extern u8 D_L04_0026D370[];
extern u8 D_L04_0026D3E0[];
extern u8 D_L04_0026D490[];
extern u8 D_L04_0026D4F0[];
extern u8 D_L04_002CA3E0[];
extern u8 D_L04_002CA438[];
extern f32 func_30F468(f32 a, f32 b);
extern f32 func_30FE88(f32 a, f32 b);
extern f32 func_30FE40(f32 a, f32 b);
extern f32 func_00283C80(f32, f32);
extern f32 func_002AA2E8(f32 *, f32, f32);

/* func_L04_00423258 is in L04_00423258-g8.c. */
/* Counts the object's state up, easing its timer down while it is over the
   limit, and hands the level's recorder the object's channel when it runs out. */
void func_PAL_L04_00430DB0(u8 *a0) {
    u32 *s1 = *(u32 **)(a0 + 0x68);

    if (a0[0x20] == 0)
        a0[0x20] = 1;
    if (a0[0x20] == 2) {
        f32 f1 = *(f32 *)(a0 + 0x18);
        if (f1 >= 3e+01f)
            *(f32 *)(a0 + 0x18) = f1 - 0.34000003f;
        if (*(f32 *)(a0 + 0x18) < 3e+01f)
            a0[0x20] = 4;
    }
    if (a0[0x20] == 3) {
        func_002AA3A8((f32 *)(a0 + 0x18), (f32 *)s1, 55.0f,
                      0.012f, 0.020000001f,
                      0.54f);
        if (55.0f <= *(f32 *)(a0 + 0x18)) {
            func_002E5CF8(0, 0, (char *)a0);
            s1[1] = 0;
            a0[0x20] = 1;
        }
    }
}

