/* 2026-11-03 w02 faithful-contract review, US object checks only.
 * Profile: -O2 -G0 -ffunction-sections -fno-expensive-optimizations.
 * Current check.py: 2068/2076 bytes,0/2 places.
 * Restored actual float pulse-smoothing return plus integer iterator/sound returns. Same real ABI; pulse-phase FP, local-address and packed-color scheduling remain.
 * Reopen: Actual address-of-local rematerialization and packed-color RTL, not equivalent pulse spellings.
 * No linked or cross-release match is claimed; earlier records follow.
 */
/* sol-high (v1322), USA v1.01: 2072 bytes versus 2076 retail, 0/2 places.
 * Required profile: -O2 -G0 -ffunction-sections -fno-expensive-optimizations.
 * The pinned compiler's default profile reproduces the earlier 2036-byte draft.
 * Disabling expensive optimizations rematerializes all eight -0.7f arguments;
 * an incomplete-array sda declaration fixes the initial timer-load sequence.
 * State-pointer lifetime and a separate camera-angle variable recover those
 * retail sequences. First remaining mismatch: +0x70, f1/f12 allocation in the
 * pulse phase. Iterator setup/backedges, packed-color construction (including
 * 0x80 << 24), and second-loop saved-register allocation also differ.
 * Equivalent pulse wordings, typed iterator declarations and -fno-regmove tie.
 * Next: investigate address-of-local rematerialization and color-expression RTL
 * with this profile; do not repeat the tied phase wordings. All declarations
 * required to compile this standalone draft are included below.
 */
#include "common.h"
typedef unsigned int L04Quad __attribute__((mode(TI)));
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00282C48(float);
extern float func_00282DB0(void *, void *);
extern float func_L00_002EE290(void *);
extern void func_00282CF0(void *, void *, void *);
extern char D_00189EA0[];
extern void func_L04_0040C0C0(L04Quad *, L04Quad *, int, int);
extern int D_L04_001B2008[] __attribute__((sda));
extern int D_00138320;
extern float D_L04_001BDC30;
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_002AA2E8(void *, float, float);
extern int func_00282948(void *);
extern int func_002829A8(void *);
extern void func_L00_00322BE0(void *, int);
extern void func_L00_00322A98(void *, void *);
extern void func_L00_00322AC0(void *, float, int, int);
extern void func_L00_00322EC8(void *);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_L01_00355BA0(int, int);
extern void func_0027AB40(void);
extern int func_002A8600(void *, int, int, int);
extern int func_002A86E8(void *, void *, int, int);
extern void func_00283388(void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
void func_L04_0040E460(unsigned char *m)
{
    float delta[4], rotation[16];
    unsigned char *item, *other;
    unsigned char **iterator;
    int red, green, blue;
    int period = 50;
    unsigned char *p = *(unsigned char **)(m + 0x68);
    unsigned char *state;
    int *data;
    float wave, active, angle, sine, radius;
    unsigned int color;
    angle = func_00283CE0(period);
    red = D_L04_001B2008[0] % period;
    {
        float phase = (float)red;
        phase /= angle;
        phase *= 2.0f;
        phase *= 3.1415927f;
        phase += -3.1415927f;
        wave = func_00283198(phase);
    }
    red = func_00283CF0(wave * 48.0f) + 104;
    green = func_00283CF0(wave * 64.0f) + 208;
    blue = func_00283CF0(wave * 24.0f) + 60;
    if (green > 255) green = 255;
    if (*(int *)(p + 0x278)) {
        func_002AA2E8(p + 0x27c, 0.16666669f, 0.00555555569008f);
        func_002AA2E8(p + 0x28c, 97.0f, 0.5666667f);
        if (*(int *)(p + 0x278)) func_00282948(p + 0x278);
        func_L00_00322BE0(p + 0x4e0, 1);
        state = p + 0x4e0;
    } else {
        if ((m[0x20] == 3 || (D_00138320 & 10)) && *(int *)(p + 0x338) < 30 && *(int *)(p + 0x33c) > 0) {
            *(int *)(p + 0x338) = 240;
            --*(int *)(p + 0x33c);
            if (m[0x20] != 3) func_002E5DA0(0, 0, m, 0x474);
            if (!func_002E59B0(m, *(int *)(p + 0x714))) {
                if (m[0x20] != 3) *(int *)(p + 0x714) = func_002E5CF8(15, 4, m);
                else {
                    *(int *)(p + 0x714) = func_002E5CF8(24, 5, m);
                    func_L01_00355BA0(*(int *)(p + 0x714), 0x400);
                }
            }
            if (*(unsigned char **)(p + 0x4c4)) {
                unsigned char *child = *(unsigned char **)(p + 0x4c4);
                unsigned char *childState = *(unsigned char **)(child + 0x68);
                if (*(float *)(p + 0x27c) <= 0.016666668f) *(int *)(childState + 0x1c0) = 0;
            }
            if (!*(int *)(p + 0x640)) {
                func_L00_00322A98(m, p + 0x4e0);
                func_L00_00322AC0(p + 0x4e0, -0.7f, 64, 1);
                func_L00_00322AC0(p + 0x4e0, -0.7f, 48, 2);
                func_L00_00322AC0(p + 0x4e0, -0.7f, 32, 3);
                func_L00_00322AC0(p + 0x4e0, -0.7f, 16, 4);
                *(int *)(p + 0x640) = 1;
            }
        }
        state = p + 0x4e0;
        if (func_00282948(p + 0x338)) {
            active = 0.0f;
            func_L00_00322EC8(state);
            *(int *)(p + 0x640) = 0;
        } else {
            active = 1.0f;
            func_L00_00322BE0(state, 1);
        }
        func_002AA2E8(p + 0x27c, active * 0.10000001f, 0.00138888892252f);
        if (*(float *)(p + 0x27c) < 0.0f) *(float *)(p + 0x27c) = 0.0f;
        if (active > 0.5f) func_002AA2E8(p + 0x28c, 97.0f, 0.5666667f);
        else func_002AA2E8(p + 0x28c, 80.0f, 0.14166668f);
    }
    if (m[0x20] != 3) {
        float viewAngle = *(float *)(p + 0x28c);
        viewAngle *= 0.008726647f;
        sine = func_00283198(viewAngle);
        sine /= func_00283180(viewAngle);
        D_L04_001BDC30 = sine;
        func_0027AB40();
    }
    if (*(int *)(p + 0x25c) != -1) {
        func_002A8600(&item, *(int *)(p + 0x25c), 0, 0);
        iterator = &item;
        if (item) do {
            if (*(short *)(item + 0xaa) == 0xa99) {
                data = *(int **)(item + 0x68);
                func_00282CF0(delta, item + 0x10, m + 0x10);
                if (*data == 0 && *(int *)(p + 0x33c) < 3 && func_L00_002EE290(delta) < 1.0f) {
                    ++*(int *)(p + 0x33c);
                    if (m[0x20] != 3) func_002E5DA0(0, 0, m, 0xa99);
                    func_L04_0040C0C0((L04Quad *)(item + 0x10), (L04Quad *)(p + 0x290), 8, 0);
                    *data = 300;
                }
            }
            func_002A86E8(iterator, item, 0, 0);
        } while (item);
    }
    if (*(int *)(p + 0x254) != -1) {
        func_002A8600(&other, *(int *)(p + 0x254), 0, 0);
        iterator = &other;
        if (other) {
            color = (128u << 24) | (blue << 16) | (green << 8) | red;
            do {
                if (*(short *)(other + 0xaa) == 0x474) radius = 1.25f;
                else if (*(short *)(other + 0xaa) == 0xcef) radius = 3.75f;
                else goto next;
                *(unsigned short *)(other + 0x34) |= 16;
                *(unsigned int *)(other + 0x78) = color;
                if (!func_002829A8(other + 0xbc)) goto next;
                func_00282CF0(delta, other + 0x10, D_00189EA0);
                if (func_00282DB0(delta, delta) > 20.0f) goto next;
                func_00283388(rotation);
                func_00283698(rotation, other + 0xc0);
                func_002830C0(delta, delta, rotation);
                if (!(func_00282C48(delta[0]) < 2.8f) || !(func_00282C48(delta[1]) < radius) || !(func_00282C48(delta[2]) < 1.5f)) goto next;
                data = *(int **)(other + 0x68);
                *(int *)(p + 0x278) += *data;
                if (!func_002E59B0(m, *(int *)(p + 0x714))) {
                    if (m[0x20] != 3) *(int *)(p + 0x714) = func_002E5CF8(15, 4, m);
                    else {
                        *(int *)(p + 0x714) = func_002E5CF8(24, 5, m);
                        func_L01_00355BA0(*(int *)(p + 0x714), 0x400);
                    }
                }
                if (m[0x20] != 3) func_002E5CF8(12, 0, m);
                *(int *)(p + 0x650) = *data;
                other[0xbc] = 60;
                if (*(unsigned char **)(p + 0x4c4)) {
                    unsigned char *child = *(unsigned char **)(p + 0x4c4);
                    unsigned char *childState = *(unsigned char **)(child + 0x68);
                    if (*(float *)(p + 0x27c) <= 0.016666668f) *(int *)(childState + 0x1c0) = 0;
                }
                if (!*(int *)(p + 0x640)) {
                    func_L00_00322A98(m, p + 0x4e0);
                    func_L00_00322AC0(p + 0x4e0, -0.7f, 64, 1);
                    func_L00_00322AC0(p + 0x4e0, -0.7f, 48, 2);
                    func_L00_00322AC0(p + 0x4e0, -0.7f, 32, 3);
                    func_L00_00322AC0(p + 0x4e0, -0.7f, 16, 4);
                    *(int *)(p + 0x640) = 1;
                }
next:
                func_002A86E8(iterator, other, 0, 0);
            } while (other);
        }
    }
}
