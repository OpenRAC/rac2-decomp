#include "include_asm.h"

#include "common.h"
extern void func_0029F338(void *);
extern u8 D_L08_001B9B00[];
extern f32 func_00282E48(void *, void *);
extern f32 func_00283CE0(int);
extern f32 func_00282C48(f32);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
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
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
} Quad;
extern s32 func_2F9A60();
extern s32 func_327898(s32, s32);
extern s32 func_2EA300(void *, void *, s32, s32, s32);
extern s32 func_3357E8(Ent *, void *, s32);
extern f32 func_3278F0(f32, f32);
extern f32 func_2FA3C8(f32);
extern f32 func_2FA3E0(f32);
extern f32 D_L08_001BFF68;
extern f32 D_00189EA8;
extern char D_00189EA0[];
extern f32 func_L08_00422850(Quad *, f32, f32, f32, f32);
extern float func_00282C48(float);
extern void func_002A7750(void *, s32, s32);
extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_L08_001BFD00[];
extern s32 D_L08_001A8F00[] __attribute__((sda));
extern s32 D_L08_001B2700[] __attribute__((sda));
extern u8 *D_L08_001B2ACC[] __attribute__((sda));
extern s32 func_002ACBC8(void *, s32);
extern s32 func_00288AA0(void *, s32);
extern s32 func_00288BE8(void *);
extern void func_L01_003CEB00(u8 *);
extern s32 func_002F5D10(void);
extern void func_L00_002B9D60(u8 *, u8 *, s32, s32);
extern void func_00288308(s32);
extern void func_US2_002B1880(s32, s32);
extern void func_0029B3E0(s32, s32);
extern float func_00283180(float);
extern float func_00283198(float);
extern f32 func_002A7940(void);
extern s32 func_002A7820(s32, s32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);

void func_US2_L08_0040FF80(u8 *self) {
    u8 *st = *(u8 **)(self + 0x68);
    u8 *ent;

    switch (self[0x20]) {
    case 0:
        if (D_001A7B00[13] != 0) {
            func_0029F338(self);
            break;
        }
        *(float *)(self + 0x18) = *(float *)(self + 0x18) + 0.75f;
        *(float *)(self + 0x2C) = *(float *)(*(u8 **)(self + 0x24) + 0x24) * 1.5f;
        func_002A7750(self, 1, -1);
        break;
    case 1:
        *(float *)(self + 0xF8) = func_00283B98(*(float *)(self + 0xF8), 0.07853982597589493f);
        if (func_002ACBC8(D_00189EA0, *(s32 *)(st + 4)) != 0) {
            if (func_00288AA0(D_L08_001BFD00, 0x5B) != 0) {
                func_00288BE8(D_L08_001BFD00);
                self[0x20] = 2;
            }
        }
        if (self[0x31] != 0)
            func_L01_003CEB00(self);
        break;
    case 2:
        D_L08_001B2700[10] = 1;
        if (D_L08_001A8F00[0] == 2) {
            self[0x31] = 0;
            *(u16 *)(self + 0x34) |= 1;
        }
        if (func_002F5D10() != 0)
            break;
        D_L08_001B2700[10] = 0;
        self[0x31] = 1;
        ent = D_L08_001B2ACC[0];
        *(u16 *)(self + 0x34) &= 0xFFFE;
        ent += *(s32 *)(st + 8) * 0x80;
        func_L00_002B9D60(ent + 0x30, ent + 0x70, 0, 1);
        func_00288308(0x15);
        func_US2_002B1880(0x122B, -1);
        func_0029B3E0(0, -1);
        func_0029F338(self);
        break;
    }
}

