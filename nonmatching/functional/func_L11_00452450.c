/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol, high effort, 28 October 2026; retained near miss.
 * Fresh pinned toolchain: default -O2 -G8 -ffunction-sections, USA v1.01.
 * check.py: 956/956 bytes, 0/1 places, first difference +0xB0;
 * seven non-relocation instructions differ. No linked build or runtime validation.
 * Chained initialization of the shared 0.5f and 0.4f values recovers retail's
 * f0/f1 allocation and all eleven float stores in their exact order. Remaining:
 * +0xB0/+0xC0 load the 4 and 11 integer constants in reverse order;
 * +0x134..+0x13C rotate the byte/word stores (0x4A, 0x60, 0x98);
 * +0x170/+0x17C use v1 instead of v0 for the post-constructor state byte.
 * Keep func_002B60B0's real pointer-return interface (see src/game/002B60B0.c).
 * Typed initialization fields, -fno-strict-aliasing, a comma-grouped count store,
 * and a bank-preserving constructor argument interleaving did not improve this
 * result. Default declaration/order retained. Next useful evidence: original
 * initialization field types or compiler scheduling/return-value lifetime.
 * USA v2.00 and PAL were not checked in this attempt.
 */

#include "common.h"

extern s32 D_L11_001A8FF4 __attribute__((sda));
extern f32 D_L11_001BA8C0[4];
extern f32 func_002A7878(f32, f32);
extern s32 func_002A77E0(s32);
extern int func_00283CF0(float);
extern void *func_002B60B0(char *, float, float, float, float);
extern void func_L11_00452DF8(char *);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_0029FCC0(char *, int, void *);
extern void func_0029FC20(char *, int, void *);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002A9640(void *, u32, s32);
extern s32 func_002B0ED8(char *, char *, s32);
extern void func_00283698(char *, char *);
extern void func_002AFFD8(char *, char *, int);
extern s32 func_L11_004461C0(s32, char *);
extern void func_002A7750(char *, int, int);
extern s32 func_002B3BA8(char *, s32, s32, s32, float, float);

void func_L11_00452450(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    char *s0;
    char *v;
    char *e;
    float mtx[16];
    float f20;
    s16 c;

    if (*(u8 *)(a0 + 0x20) == 0) {
        *(char **)(s1 + 0x18) = s1 + 0x100;
        f20 = func_002A7878(15.0f, 40.0f) * 0.017453294f;
        if (func_002A77E0(2) != 0)
            f20 = -f20;
        *(f32 *)(s1 + 0x2C8) = f20;
        if (func_002A77E0(2) == 1)
            *(u16 *)(a0 + 0x34) |= 0x8000;
        *(u8 *)(s1 + 0x48) = func_00283CF0(15.0f);
        *(u8 *)(s1 + 0x4A) = func_00283CF0(12.0f);
        *(u8 *)(s1 + 0x60) = 0xB;
        *(s32 *)(s1 + 0x98) = 4;
        *(f32 *)(s1 + 0x100) = 0.8f;
        *(f32 *)(s1 + 0x104) = *(f32 *)(s1 + 0x84) = *(f32 *)(s1 + 0x80) = 0.5f;
        *(f32 *)(s1 + 0x10C) = *(f32 *)(s1 + 0x108) = *(f32 *)(s1 + 0x8C) = 0.4f;
        *(f32 *)(s1 + 0x110) = 1.5707965f;
        *(f32 *)(s1 + 0x130) = 0.52359885f;
        *(f32 *)(s1 + 0x12C) = 0.0055555557f;
        *(f32 *)(s1 + 0x134) = 2.8f;
        func_002B60B0(a0, 0.004444444552063942f, 0.13333334028720856f,
                      0.0011635529808700085f, 0.10471977293491364f);
        *(u8 *)(s1 + 0x28) = 3;
        func_L11_00452DF8(a0);
    }
    if (*(s16 *)(s1 + 0x2D8) == 0 && *(u8 *)(a0 + 0x20) != 0xC && D_L11_001A8FF4 == 0) {
        *(u16 *)(a0 + 0x34) |= 0x400;
        if (*(u8 *)(a0 + 0x31) != 0 && func_00282E48(a0 + 0x10, D_L11_001BA8C0) < 24.0f) {
            func_002A93B0(a0);
            *(u8 *)(a0 + 0x6F) = 0x16;
        }
    } else {
        *(u16 *)(a0 + 0x34) &= 0xFBFF;
    }
    s0 = s1 + 0x290;
    func_0029FCC0(a0, 1, s1 + 0x270);
    func_0029FCC0(a0, 2, s1 + 0x280);
    func_0029FC20(a0, 3, mtx);
    func_00282C88(s0);
    *(s32 *)(s1 + 0x298) = 0;
    *(f32 *)(s1 + 0x290) = 0.25f;
    func_002830C0(s0, s0, mtx);
    func_00282CC0(s0, s0, mtx + 12);
    if (*(u8 *)(a0 + 0x20) >= 3) {
        v = func_002A9640(a0, 0x10000, 1);
        if (v != 0) {
            e = *(char **)(v + 0x20);
            if (e != 0 && *(u8 *)(a0 + 0x31) == 0) {
                c = *(s16 *)(e + 0xAA);
                if (c == 0xA03 || c == 0xB89)
                    *(s32 *)(v + 0x2C) = 0;
            }
        }
        if (func_002B0ED8(a0, s1 + 0x50, 0) == 5) {
            *(s32 *)(s1 + 0xE0) = 0;
            *(f32 *)(s1 + 0xE4) = 0.8377582f;
        }
        if (*(s16 *)(s1 + 0x2D8) != 0) {
            char *pos;
            func_00283698(s1 + 0x230, a0 + 0xC0);
            pos = a0 + 0x10;
            func_002AFFD8(pos, s1 + 0x260, 0);
            if (func_L11_004461C0(*(s32 *)(a0 + 0xB8), pos) == 0) {
                *(s32 *)(s1 + 0x20) = 0;
                func_002A7750(a0, 0xC, 4);
            }
        }
        if (*(u8 *)(a0 + 0x20) >= 2 && *(u8 *)(s1 + 0x2E) == 2)
            func_L11_00452DF8(a0);
        *(s16 *)(s1 + 0x2D0) = func_002B3BA8(a0, *(s32 *)(s1 + 0x2CC), 0, 0, 100.0f, 100.0f);
        *(s32 *)(s1 + 0x2C4) = *(s32 *)(s1 + 0x220);
    }
}
