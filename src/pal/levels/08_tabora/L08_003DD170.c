#include "include_asm.h"

#include "common.h"
extern u8 D_L08_001B9B00[];
extern f32 func_00282E48(void *, void *);
extern f32 func_00283CE0(int);
extern f32 func_00282C48(f32);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
} Quad;
extern f32 func_3278F0(f32, f32);
extern f32 func_2FA3C8(f32);
extern f32 func_2FA3E0(f32);
extern f32 D_L08_001BFF68;
extern f32 D_00189EA8;
extern f32 func_L08_00422850(Quad *, f32, f32, f32, f32);
extern void func_002B60B0(u8 *, float, float, float, float);
extern int func_00282948(void *);
extern float func_002A7878(float, float);
extern float func_00282E80(void *, void *);
extern int func_PAL_002B5BA8(u8 *, void *, float);
extern float func_00282DF0(void *);
extern float func_00282C48(float);
extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_L08_001BFD00[];
extern u8 *D_L08_001B2ACC[] __attribute__((sda));
extern float func_00283180(float);
extern float func_00283198(float);
extern f32 func_002A7940(void);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);

int func_PAL_L08_003DD170(u8 *object, float accel, float unused1, float damping,
                     float speed, float unused4, float turn, float friction) {
    u8 *state = *(u8 **)(object + 0x68);
    int result;
    float amount;

    func_002B60B0(object, speed * 0.00040000002f,
                  turn * 0.020000001f,
                  accel * 6.981318e-06f,
                  damping * 0.0003490659f);
    *(float *)(state + 0x154) = friction;
    if (func_00282948(state + 0x474) != 0) {
        *(float *)(state + 0x46C) = -*(float *)(state + 0x46C);
        *(float *)(state + 0x470) = *(float *)(state + 0x46C) * 0.01745329424738884f;
        *(int *)(state + 0x474) = ((s32)(func_002A7878(30.0f, 90.0f)) * 5 + 2) / 6;
    }
    if (*(int *)(state + 0x48C) != 0 ||
        (object[0x20] == 8 && object[0x95] != 0) ||
        func_00282E80(object + 0x10, state + 0x3F0) < 5.0f)
        *(float *)(state + 0x470) = 0;
    result = func_PAL_002B5BA8(object, state + 0x3F0, *(float *)(state + 0x470));
    amount = func_00282DF0(state + 0x1C0);
    amount += func_00282C48(*(float *)(state + 0x1D4));
    if (result & 15) {
        func_00282948(state + 0x448);
        amount = func_00282C48(*(float *)(state + 0x1D4)) + 0.012000001f;
    }
    *(float *)(object + 0x48) = amount * 24.999998f;
    if (*(float *)(object + 0x48) > 1.5f)
        *(float *)(object + 0x48) = 1.5f;
    else if (*(float *)(object + 0x48) < 0.0f)
        *(float *)(object + 0x48) = 0;
    return result;
}


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
extern s32 func_00282948();
extern s32 func_002A7820(s32, s32);
extern s32 func_2EA300(void *, void *, s32, s32, s32);
extern s32 func_3357E8(Ent *, void *, s32);
extern s32 D_L08_001A8F00[] __attribute__((sda));
extern s32 D_L08_001B2700[] __attribute__((sda));
extern s32 func_002ACBC8(void *, s32);
extern s32 func_00288AA0(void *, s32);
extern s32 func_00288BE8(void *);
extern s32 func_002F5D10(void);
extern s32 func_002A7820(s32, s32);

/* the countdown runs while the entry is flagged, then the timer field saturates */
void func_PAL_L08_003DD368(Ent *a0)
{
    Moby *s0 = a0->f68;
    u16 v1;

    if (a0->fBC != 0) {
        a0->fBC = 0;
        if (s0->f448 < 167) {
            s0->f448 = ((s32)(func_002A7820(300, 360)) * 5 + 2) / 6;
            s0->f40E = 12;
        }
    }
    v1 = a0->f96;
    if (s0->f254 == 2) {
        if (func_00282948(&s0->f448)) s0->f40E = 3;
    }
    v1 = a0->f96;
    if (v1 <= 0xFFFDu) a0->f96 = v1 + 1;
    if (a0->f20 == 8) {
        if (a0->f95 == 0) func_00282948(&s0->f48C);
    }
    func_00282948(&s0->f440);
    func_00282948(&s0->f44C);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L08_003DD458);

INCLUDE_ASM("asm/pal/levels", func_PAL_L08_003DD918);

INCLUDE_ASM("asm/pal/levels", func_PAL_L08_003DE160);
