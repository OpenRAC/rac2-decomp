/* Retained reconstruction,30 October2026; not linked and no matching credit.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1076/1072 bytes; us 0/1, us2 0/1, pal absent.
 * New complete actor/route initializer and reaction-state reconstruction; correct0x20
 * frame. Mode/table address materialization, initializer store groups and FP allocation
 * remain. No-split-addresses improves some absolute-load shapes but grows to1080bytes;
 * retain the default profile. All random-helper and reaction contracts keep their
 * actual argument/return widths.
 */
#include "common.h"

extern int D_001A79F0 NOT_SDA;
extern int D_L14_001A8FF0 __attribute__((sda));
extern u8 *D_L14_001B2200 NOT_SDA;
extern u8 D_L14_001B2210[], D_L14_001B9500[];
extern float D_L14_001B18B0 __attribute__((sda));
extern float func_002B0178(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_0029F338(void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern float func_002A78D8(float, float), func_002A7940(void);
extern void func_002A7750(void *, int, int), func_002A7470(void *, int, int, int);
extern void func_002A93B0(void *), func_L14_004286F8(void *);
extern int func_002B0ED8(void *, void *, int);
extern int func_002B3BA8(void *, int, void *, int, float, float);
extern void func_002AFFD8(void *, void *, int);

#define F(p, n) (*(float *)((p) + (n)))
#define I(p, n) (*(int *)((p) + (n)))
#define H(p, n) (*(short *)((p) + (n)))

/* Initializes the actor's motion and route state, then services reactions. */
void func_L14_004281D0(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *entry;
    int route, result;
    float scale, height;
    u16 flags;

    if (object[0x20] == 0) {
        if (D_001A79F0 == 2 && F(object, 0x18) > 400.0f) {
            if (!D_L14_001A8FF0) return;
            func_002B0178(object + 0x10, object, object + 0x10);
            H(state, 0x338) = 1;
            I(object, 0x9C) = 3;
            *(u16 *)(object + 0x34) |= 0x100;
            height = func_00282E48(object + 0x10, D_L14_001B2210) - 1.5f;
        } else {
            I(object, 0x9C) = 12;
            height = F(object, 0x18) - 1.0f;
        }
        F(state, 0x90) = height;
        route = I(state, 0x210);
        if (route == -1) {
            func_0029F338(object);
            return;
        }
        entry = D_L14_001B2200 + route * 0x30;
        if (H(entry, 0x30)) {
            int first = **(int **)(entry + 0x3C);
            I(state, 0x13C) = first;
            I(state, 0x218) = first;
        } else {
            I(state, 0x218) = -1;
        }
        scale = func_002A7878(1.0f, 1.333f);
        F(state, 0x324) = scale;
        F(object, 0x2C) = F(*(u8 **)(object + 0x24), 0x24) * scale;
        state[0x48] = func_00283CF0(15.0f);
        state[0x4A] = func_00283CF0(6.4f);
        state[0x60] = 11;
        state[0x28] = 3;
        F(state, 0x30) = 0.333f;
        F(state, 0x104) = F(state, 0x324) * 0.2f;
        F(state, 0x100) = F(state, 0x324) * 0.3f;
        F(state, 0x10C) = 0.4f;
        F(state, 0x110) = 1.5707964897155762f;
        F(state, 0x130) = 0.523598849773407f;
        I(state, 0x138) |= 0x280;
        I(state, 0x98) = 3;
        F(state, 0x80) = F(state, 0x84) = 0.2f;
        F(state, 0x8C) = F(state, 0x108) = 0.4f;
        F(state, 0x134) = 0.05f;
        scale = func_002A78D8(18.0f, 22.0f);
        state[0x1E8] = 7;
        state[0x1E9] = 6;
        H(state, 0x1E4) = 180;
        H(state, 0x1E2) = 120;
        F(state, 0x1DC) = scale * 0.01745329424738884f;
        F(state, 0x1D4) = 3.0f;
        F(state, 0x1D0) = D_L14_001B18B0 * 0.016666668f;
        F(state, 0x328) = func_002A7940();
        if (I(state, 0x214)) {
            flags = *(u16 *)(object + 0x34);
            I(object, 0x98) = 0;
            *(u16 *)(object + 0x34) = (flags | 0x41) & 0xEFFF;
            func_002A7750(object, 13, 4);
            if (object[0x43] != 10) func_002A7470(object, 10, 0, 0);
        } else {
            func_002A7750(object, 1, 0);
            if (object[0x43]) func_002A7470(object, 0, 0, 0);
        }
        qcopy(state + 0x2E0, object + 0x10);
    }
    if (object[0x31] && func_00282E48(object + 0x10, D_L14_001B9500) < 24.0f) {
        func_002A93B0(object);
        object[0x6F] = 22;
    }
    result = func_002B0ED8(object, state + 0x50, 0);
    if (result) {
        func_L14_004286F8(object);
        if (result >= 4) func_002A7750(object, 12, -1);
    }
    if (object[0x20] != 12 && I(state, 0x1D8) == 1)
        func_002A7750(object, 12, -1);
    if ((u32)(object[0x95] - 3) >= 2)
        H(state, 0x314) = func_002B3BA8(object, I(state, 0x210), 0, 0, 16.0f, 0.0f);
    if (H(state, 0x338)) func_002AFFD8(object + 0x10, state + 0x300, 0);
}
