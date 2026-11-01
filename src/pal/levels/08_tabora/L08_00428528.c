#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L08_00428528);


INCLUDE_ASM("asm/pal/levels", func_PAL_L08_00428D08);

#include "common.h"
extern u8 D_L08_001B9B00[];
extern f32 func_00282E48(void *, void *);
extern f32 func_00283CE0(int);
extern f32 func_00282C48(f32);
extern float func_00283180(float);
extern float func_00283198(float);
typedef struct {
    u8 pad00[0x20];
    u8 f20;
    u8 f21;
    u8 pad22[0x24 - 0x22];
    void *f24;
    u8 pad28[0x2C - 0x28];
    f32 f2C;
    u8 pad30[0x68 - 0x30];
    void *f68;
    u8 pad6C[0x95 - 0x6C];
    u8 f95;
    u16 f96;
    u8 pad98[0xBC - 0x98];
    u8 fBC;
    u8 padBD[0x100 - 0xBD];
} Ent;
typedef struct {
    u8  pad00[0x20];
    f32 f20;
    void *f24;
    u8  pad28[0x2C - 0x28];
    f32 f2C;
    u8  pad30[0x50 - 0x30];
    u8  f50[0x88 - 0x50];
    u16 f88;
    u8  pad8A[0xE4 - 0x8A];
    f32 fE4;
    u8  padE8[0x144 - 0xE8];
    s32 f144;
    u8  pad148[0x150 - 0x148];
    f32 f150[4];
    f32 f160;
    f32 f164;
    f32 f168;
    u8  pad16C[0x189 - 0x16C];
    u8  f189;
    u8  pad18A[0x18C - 0x18A];
    u8  f18C;
    u8  pad18D[0x1B0 - 0x18D];
    f32 f1B0;
    f32 f1B4;
    u8  f1B8[0x1BA - 0x1B8];
    s16 f1BA;
    s16 f1BC;
    u16 f1BE;
    u8  pad1C0[0x1CC - 0x1C0];
    s32 f1CC;
    f32 f1D0;
    f32 f1D4;
    s32 f1D8;
    s32 f1DC;
    u8  f1E0[0x254 - 0x1E0];
    s32 f254;
    u8  pad258[0x40E - 0x258];
    u16 f40E;
    u8  pad410[0x440 - 0x410];
    u8  f440[0x448 - 0x440];
    s32 f448;
    u8  f44C[0x484 - 0x44C];
    s32 f484;
    s32 f488;
    u8  f48C[8];
} Moby;
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
} Quad;
typedef struct {
    u8  pad00[0x24];
    f32 f24;
} Sub24;
extern s32 func_2F9A60();
extern s32 func_327898(s32, s32);
extern s32 func_2EA300(void *, void *, s32, s32, s32);
extern void func_PAL_002B14F8(Ent *, void *, s32, s32, f32);
extern s32 func_PAL_002B1A50(Ent *, void *, s32);
extern f32 func_3278F0(f32, f32);
extern f32 func_2FA3C8(f32);
extern f32 func_2FA3E0(f32);
extern f32 D_L08_001BFF68;
extern f32 D_00189EA8;
extern f32 func_L08_00422850(Quad *, f32, f32, f32, f32);
extern void func_L08_00422900(Ent *);
extern void func_L08_00422AD8(Ent *);
extern float func_00282C48(float);
extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_L08_001BFD00[];
extern s32 D_L08_001A8F00[] __attribute__((sda));
extern s32 D_L08_001B2700[] __attribute__((sda));
extern u8 *D_L08_001B2ACC[] __attribute__((sda));
extern s32 func_002ACBC8(void *, s32);
extern s32 func_00288AA0(void *, s32);
extern s32 func_00288BE8(void *);
extern s32 func_002F5D10(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern f32 func_002A7940(void);
extern s32 func_002A7820(s32, s32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);

/* func_L08_00423010 is in its own unit. */

/* func_L08_004233E0 is defined in L08_004233E0-init.c. */

/* func_L08_004237F0 is matched in its own unit, src/levels/08_tabora/L08_004237F0.c (default flags). */

/* the driver is primed, the entry follows its mount and then its own update runs */
void func_PAL_L08_00428DD8(Ent *a0)
{
    Moby *s0 = a0->f68;
    Sub24 *q;
    f32 f0;
    s32 r;

    func_PAL_002B14F8(a0, s0->f1E0, 2, 1, 2.5f);
    func_L08_00422900(a0);
    q = a0->f24;
    f0 = q->f24 * 0.5f;
    a0->f2C = f0;
    r = func_PAL_002B1A50(a0, s0->f50, 0);
    if (r != 0) {
        if (s0->f20 <= 0.0f) {
            s0->f88 |= 2;
            s0->fE4 = 1.0053098f;
        } else {
            s0->f1BE = 275;
        }
        func_L08_00422B60(a0);
        func_L08_00422AD8(a0);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L08_00428EA8);
