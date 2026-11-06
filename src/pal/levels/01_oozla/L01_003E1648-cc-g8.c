/* func_PAL_L01_003E1648, the PAL copy of func_L01_003DCF40: the same C, where rename func_002A7470 becomes func_PAL_002A7E68. */
#include "common.h"

/* Raises the measured flag on every record of the table the object's selector names. */
/* func_L01_00416A50 is defined in L01_003DA740.c (this unit has no $gp access for it). */

typedef unsigned int TI128 __attribute__((mode(TI)));

extern void func_002A7750(void *,s32,s32);
typedef struct {
 u8 pad0[0x80]; f32 position[4];
 u8 pad90[0x33C-0x90]; void *platform;
 u8 pad340[0xE]; s16 flag34E;
 u8 pad350[0x229C-0x350]; s32 mode;
} UpdateHero;
extern UpdateHero D_00189E20 NOT_SDA;
/* Tilting lift: initializes its height range, moves while the hero rides it,
 * and tilts toward the hero's offset projected on the object's axes. */
extern s32 func_00283CF0(f32);
extern f32 func_002A78D8(f32, f32);
extern void func_L01_003377C8(void *);
extern void func_002B60B0(void *, f32, f32, f32, f32);
extern s32 func_002A7820(s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern u8 *D_L01_001FE180[] NOT_SDA;
extern u8 D_L01_001B0900[] SDATA(D_L01_001B0900);

void func_PAL_L01_003E1648(u8 *obj) {
    u8 *p = *(u8 **)(obj + 0x68);
    s32 idx;

    *(void **)(p + 0x18) = p + 0x1C0;
    p[0x48] = func_00283CF0(10.0f);
    p[0x4A] = func_00283CF0(9.6f);
    *(s32 *)(p + 0x158) = 5;
    *(u8 *)(p + 0x127) = 11;
    *(f32 *)(p + 0x12C) = 0.24000001f;
    *(f32 *)(p + 0x130) = 0.120000005f;
    *(f32 *)(p + 0x134) = 0.0088f;
    *(f32 *)(p + 0x138) = 0.014800001f;
    *(f32 *)(p + 0x13C) = 0.016f;
    *(f32 *)(p + 0x14C) = 0.4f;
    *(u8 *)(p + 0x120) = 0;
    *(u8 *)(p + 0x121) = 10;
    *(u8 *)(p + 0x122) = 10;
    *(u8 *)(p + 0x126) = 10;
    *(f32 *)(p + 0x140) = 0.5f;
    *(f32 *)(p + 0x144) = 0.5f;
    *(u8 *)(p + 0x17C) = 6;
    *(u8 *)(p + 0x17D) = 10;
    *(u8 *)(p + 0x17E) = 6;
    *(u8 *)(p + 0x17F) = 10;
    *(s16 *)(p + 0x148) = 0;
    *(u8 *)(p + 0x28) = 0;
    *(u8 *)(p + 0x182) = 6;
    *(u8 *)(p + 0x183) = 10;
    *(u8 *)(p + 0x29) = 1;
    *(f32 *)(p + 0x30) = 0.5f;
    *(TI128 *)(p + 0x3A0) = *(TI128 *)(obj + 0x10);
    *(s16 *)(p + 0x3D8) = 0;
    if (*(s32 *)(p + 0x3C0) != -1) {
        func_L01_003377C8(D_L01_001FE180[*(s32 *)(p + 0x3C0)]);
    }
    idx = *(s32 *)(p + 0x3BC);
    if (idx != -1) {
        func_L01_003377C8(D_L01_001FE180[idx]);
    }
    qcopy(p + 0x2B0, obj + 0x10);
    *(f32 *)(p + 0x2C0) = 0.3f;
    *(f32 *)(p + 0x2CC) = 5.0f;
    *(f32 *)(p + 0x1C8) = 0.2f;
    *(f32 *)(p + 0x1C4) = 0.1f;
    *(f32 *)(p + 0x2D0) = 5.0f;
    *(f32 *)(p + 0x1C0) = 0.3f;
    *(f32 *)(p + 0x1CC) = 0.2f;
    *(f32 *)(p + 0x1D0) = 0.8726646900177002f;
    *(f32 *)(p + 0x1F0) = 0.523598849773407f;
    *(f32 *)(p + 0x1EC) = 0.008f;
    *(s32 *)(p + 0x1FC) = *(s32 *)(p + 0x3BC);
    *(f32 *)(p + 0x29C) = func_002A78D8(25.0f, 35.0f) * 0.01745329424738884f;
    *(s16 *)(p + 0x2A2) = 100;
    *(s16 *)(p + 0x2A4) = 150;
    func_002B60B0(obj, 0.0032000002f, 0.080000006f, 0.00307178f, 0.2303835f);
    *(f32 *)(p + 0xF0) = *(f32 *)(obj + 0x2C);
    *(f32 *)(p + 0xE0) = *(f32 *)(p + 0x30);
    *(void **)(p + 0xC0) = D_L01_001B0900;
    *(s32 *)(obj + 0xF4) = 0;
    *(s32 *)(obj + 0xF0) = 0;
    qzero_nc(p + 0x210);
    *(f32 *)(p + 0x218) = 1.0f;
    if (obj[0x21] != 255) {
        **(s32 **)(p + 0x3FC) = 0;
        **(s32 **)(p + 0x400) = -1;
    }
    if (!p[0x3D0]) {
        if (p[0x3D1]) {
            if (*(s32 *)(p + 0x414) != -1) *(s32 *)(p + 0x3F8) = *(s32 *)(p + 0x414);
            else if ((idx = *(s32 *)(p + 0x418)) != -1) *(s32 *)(p + 0x3F8) = idx;
            else *(s32 *)(p + 0x3F8) = *(s32 *)(p + 0x41C);
            if (p[0x3D2]) {
                func_002A7750(obj, 0, 1);
            } else {
                func_002A7750(obj, 1, 3);
            }
        } else {
            if (*(s32 *)(p + 0x418) != -1) *(s32 *)(p + 0x3F8) = *(s32 *)(p + 0x418);
            else if ((idx = *(s32 *)(p + 0x414)) != -1) *(s32 *)(p + 0x3F8) = idx;
            else *(s32 *)(p + 0x3F8) = *(s32 *)(p + 0x41C);
            func_002A7750(obj, 1, 3);
        }
        if (*(s32 *)(p + 0x408) != -1) {
            if (obj[0x43] != 7) func_PAL_002A7E68(obj, 7, 0, func_002A7820(2, 10));
        } else if (obj[0x43] != 0) {
            func_PAL_002A7E68(obj, 0, 0, func_002A7820(2, 10));
        }
    } else {
        if (*(s32 *)(p + 0x414) != -1) *(s32 *)(p + 0x3F8) = *(s32 *)(p + 0x414);
        else if ((idx = *(s32 *)(p + 0x418)) != -1) *(s32 *)(p + 0x3F8) = idx;
        else *(s32 *)(p + 0x3F8) = *(s32 *)(p + 0x41C);
        *(s32 *)(obj + 0x98) = 0;
        obj[0x31] = 0;
        *(u16 *)(obj + 0x34) |= 1;
        *(f32 *)(obj + 0x18) -= 2.0f;
        func_002A7750(obj, 0, 1);
        if (obj[0x43] != 0) func_PAL_002A7E68(obj, 0, 0, func_002A7820(2, 10));
    }
}
