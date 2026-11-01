#include "include_asm.h"

#include "common.h"
extern f32 D_L09_001B13F0 __attribute__((sda));
extern f32 D_L09_001B13F4 __attribute__((sda));
extern s32 D_L09_001A79F0 __attribute__((sda));
extern s32 D_L09_001A9040 __attribute__((sda));
extern s32 func_323340(char *a0, char *a1, s32 a2);
extern s32 D_001A79F0;
extern s32 func_002B0ED8(char *a0, char *a1, s32 a2);
extern s32 func_002B3BA8(char *a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);
extern s32 D_L09_001B2878;
extern u8 *D_L09_001B285C_1;
extern u16 *D_L09_001FB560[];
extern s32 D_L09_001B1420[2];
extern s32 func_00283D38(s32, s32, f32);
typedef struct {
    s32 a, b;
} ColorPair;
typedef struct {
    u8 pad[0x78];
    s32 colour;
} TintedObject;
extern ColorPair D_L09_001B1400[2];
extern s32 D_L09_001B2388;
extern f32 func_00283B98(f32, f32);
extern f32 func_00283198(f32);
extern void func_0029FC20(u8 *, s32, u8 *);
extern void func_L00_002E6CF0(void *, u8 *);
void func_L09_00405490(u8 *a0);
extern u8 D_L09_001B15B0 __attribute__((sda));
extern u8 D_0019B4A8[];
extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_0019B278[];
extern u8 D_001A7A28[] __attribute__((sda));

/* Steps the object's pulse: the angle at +0x348 advances by 2*pi/30 through the resident angle
   blend, its sine is mapped to 0..1 and kept at +0x34C, and the colour pair D_L09_001B1400 is
   blended by it into the object's word at +0x78. When the state's stamp (+0x350) differs from
   D_L09_001B2388, every visible class-0xD90 entity of the object's group that is not in state
   0xFE or 0xFD gets its point refreshed (func_0029FC20, selector 0) into its vector at +0x240
   and the same stamp; then func_L09_00405490 is registered as the object's callback. */
void func_PAL_L09_0040A268(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    ColorPair color = D_L09_001B1400[0];
    u16 *p;
    u8 *e;
    u8 *sub;
    f32 angle;
    f32 wave;

    angle = func_00283B98(*(f32 *)(state + 0x348), 0.25132746f);
    *(f32 *)(state + 0x348) = angle;
    wave = func_00283198(angle) * 0.5f + 0.5f;
    *(f32 *)(state + 0x34C) = wave;
    ((TintedObject *)a0)->colour = func_00283D38(color.a, color.b, wave);
    if (*(s32 *)(state + 0x350) != D_L09_001B2388) {
        for (p = D_L09_001FB560[a0[0x21]];
             a0[0x21] != 0xFF && a0[0x21] <= D_L09_001B2878 && p != 0 &&
             ((p != 0 && (s16)p[-1] >= 0) || p == D_L09_001FB560[a0[0x21]]);
             p++) {
            e = D_L09_001B285C_1 + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (e[0x31] != 0 && *(s16 *)(e + 0xAA) == 0xD90) {
                if (e[0x20] != 0xFE) {
                    if (e[0x20] != 0xFD) {
                        sub = *(u8 **)(e + 0x68);
                        func_0029FC20(e, 0, sub + 0x240);
                        *(s32 *)(sub + 0x350) = D_L09_001B2388;
                    }
                }
            }
        }
        func_L00_002E6CF0((void *)func_L09_00405490, a0);
    }
}
