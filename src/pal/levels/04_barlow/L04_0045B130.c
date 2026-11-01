#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
extern u8 D_L04_001395C7;
extern u8 D_L04_002CA518;
extern void func_0029F338(void *a0);
extern int func_002B38B8(u8 *a0);
extern void func_002A0430(u32 a0);
extern s32 func_00288AA0(u8 *a0, s32 a1);
extern s32 func_00288BE8(void *a0);
extern void func_002F5CC8(void);
extern u8 D_0019B2E8[];
extern int D_001A79F0 __attribute__((sda));
extern int D_L04_001B24DC __attribute__((sda));
extern u8 D_L04_001BF880[];
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

/* Starts the object's encounter state and, once it is running, hands the level's
   camera table the object's slot and asks the frame helpers to update it. */
void func_PAL_L04_0045B130(u8 *a0) {
    u32 *a1 = *(u32 **)(a0 + 0x68);

    if (a0[0x20] == 0) {
        if (D_0019B2E8[a0[0xB0] + D_001A79F0 * 16] & 0x80) {
            func_0029F338(a0);
            return;
        }
        a0[0x20] = 1;
    }
    if (a0[0x20] == 1) {
        if (func_002B38B8((u8 *)(D_L04_001B24DC + (*a1 << 8)))) {
            func_002A0430(a0[0xB0]);
            func_00288AA0(D_L04_001BF880, 0x38);
            func_00288BE8(D_L04_001BF880);
            func_002F5CC8();
            func_0029F338(a0);
        }
    }
}

extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_001395B8[];
extern s32 D_L04_001B2008[] __attribute__((sda));
extern u8 *D_L04_001B25CC[] __attribute__((sda));
extern u8 D_00189EA0[];
extern void func_PAL_L00_002B9CD8(void *a0, void *a1, s32 a2, s32 a3);
extern s32 func_002ACBC8(void *a0, void *a1);
extern u8 D_L04_001B9680[];
extern u8 D_00189EA0[];
extern u8 D_L04_001B1218[];
extern u8 D_L04_001B1230[];

/* On the first update: with inventory item 0x1F owned, the byte at D_001395B8+0x12
   clear and the level counter D_L04_001B2008 below 5, passes the +0x30/+0x70 vectors
   of the level record the object names to func_PAL_L00_002B9CD8 (RAC1's Hero_ResetToPosition
   call shape); with the item owned and that byte set, hands the object to
   func_0029F338. Later, once func_002ACBC8 accepts the hero position (D_00189EA0) for
   the object's volume and the item is still owned, sets the byte and does the same. */
void func_PAL_L04_0045C268(u8 *a0) {
    u8 *s2 = *(u8 **)(a0 + 0x68);
    u8 *p;
    if (a0[0x20] == 0) {
        if (D_001A7B00[0x1F] != 0 && D_001395B8[0x12] == 0 && D_L04_001B2008[0] < 5) {
            p = D_L04_001B25CC[0] + (*(s32 *)(s2 + 4) << 7);
            func_PAL_L00_002B9CD8(p + 0x30, p + 0x70, 0, 1);
        } else if (D_001A7B00[0x1F] != 0 && D_001395B8[0x12] != 0) {
            func_0029F338(a0);
            return;
        } else {
            a0[0x20] = 1;
        }
        a0[0x30] = 0xFF;
    }
    if (a0[0x20] == 1) {
        if (func_002ACBC8(D_00189EA0, *(void **)s2) != 0) {
            if (D_001A7B00[0x1F] != 0) {
                D_001395B8[0x12] = 1;
                func_0029F338(a0);
            }
        }
    }
}

