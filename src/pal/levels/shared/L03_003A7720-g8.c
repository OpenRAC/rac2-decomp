#include "include_asm.h"

extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00282DF0(float *);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern void ref_L03_003C4240_00(unsigned char *, float);
extern void ref_L03_003C4240_01(unsigned char *, void *, int, float, float, float);
extern int ref_L03_003C4240_02(void *, void *, void *);
extern void ref_L03_003C4240_03(void *, void *);
extern float ref_L03_003C4240_04 __attribute__((sda));
extern float ref_L03_003C4240_05 __attribute__((sda));

/* Turns the object with its state: it stops when the state has no time left, otherwise it
   spreads the turn over the frame and lets the state and the object react to it. */
void func_PAL_L03_003C8250(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);
    unsigned char *v;
    float f;
    float g;

    f = func_00282DF0((float *)(s1 + 0x1B0));
    if (f <= 0.0f)
        return;
    g = func_00282DF0((float *)(s1 + 0x1B0));
    if (g > 0.020000001f) {
        f = func_00283248(*(float *)(s1 + 0x1B0), *(float *)(s1 + 0x1B4));
        f = func_00283B98(f, 3.14159274f);
        ref_L03_003C4240_00(a0, f);
    }
    ref_L03_003C4240_01(a0, a0 + 0x10, 0x10, *(float *)(a0 + 0xF8),
                        ref_L03_003C4240_05 * 0.020000001f,
                        ref_L03_003C4240_04 * 0.00040000002f);
    ref_L03_003C4240_02(*(void **)(s1 + 0x220), a0 + 0x10, s1 + 0x368);
    v = *(unsigned char **)(s1 + 0x194);
    if (v != 0) {
        if (*(short *)(v + 0xAA) == 0x940 || *(short *)(v + 0xAA) == 0x93C ||
            *(short *)(v + 0xAA) == 0x964)
            ref_L03_003C4240_03(*(unsigned char **)(s1 + 0x194), a0 + 0x10);
    }
}

#include "common.h"
extern int func_002AD0B0(u8 *);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AC9F8(float *, float);
extern float D_L03_001AFF08 __attribute__((sda));
extern float D_L03_001AFF04 __attribute__((sda));

void func_PAL_L03_003C8378(u8 *object, void *target)
{
    float delta[4];
    u8 *state;
    u8 *attachment;
    if (object[0x20] != 4 && object[0x20] != 2)
        return;
    state = *(u8 **)(object + 0x68);
    if (*(u8 **)(state + 0x198) != 0) {
        attachment = (u8 *)func_002AD0B0(*(u8 **)(state + 0x198));
        if (attachment != 0 && 0.002f < func_00282C48(*(float *)(attachment + 0x18)))
            return;
    }
    func_00282CF0(delta, object + 0x10, target);
    delta[2] = 0.0f;
    func_00282F20(delta, delta, (D_L03_001AFF08 + D_L03_001AFF08) * 0.00040000002f);
    func_00282CC0(state + 0x1B0, state + 0x1B0, delta);
    func_002AC9F8((float *)(state + 0x1B0), D_L03_001AFF04 * 0.020000001f);
}
