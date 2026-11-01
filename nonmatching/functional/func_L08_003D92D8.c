/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_L08_003D92D8: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections.
   Complete reconstruction with two 16-byte vectors and three independently complete 64-byte matrix buffers. Scheduling/allocation and control-flow shape remain.
   No linked match is claimed.
*/

#include "common.h"
#define W(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern u8 D_L08_001CA080[], D_L08_001B9B00[], D_L08_001BFF80[], D_00189E20[];
extern f32 func_00282E48(void *, void *);
extern void func_002A93B0(void *), func_L08_003D82F0(void *), func_L08_003D8A28(void *);
extern s32 func_00278E78(void), func_002B0ED8(void *, void *, s32);
extern void func_00283410(void *, void *), func_00283698(void *, void *);
extern f32 func_002A89A8(void *, void *, f32);
extern void func_00282F20(void *, void *, f32), func_00283098(void *, void *, void *);
extern f32 func_00283248(f32, f32), func_00283BE0(f32, f32), func_00282E80(void *, void *);
extern f32 func_002AAA00(f32 *, f32 *, s32, f32, f32, f32, f32);
extern void func_0029FCC0(void *, s32, void *);
extern void func_002AEC48(void *, void *, s32, f32, f32);

void func_L08_003D92D8(u8 *object)
{
    Vector position, direction;
    f32 rotation[16], inverse[16], objectInverse[16];
    u8 *state = *(u8 **)(object + 0x68);
    s32 mode = W(D_L08_001CA080, 0xC), hit, i;
    f32 value, yaw, pitch, x, y;
    if (mode) {
        if (F(object, 0x18) < F(D_L08_001CA080, 0x28) && W(D_L08_001CA080, 0) == 1) return;
        if (F(D_L08_001CA080, 0x28) < F(object, 0x18) && W(D_L08_001CA080, 0) == 0) return;
        if (mode == 2) {
            if (F(D_L08_001CA080, 0x38) < F(object, 0x18) && W(D_L08_001CA080, 0) == 1) return;
            if (F(object, 0x18) < F(D_L08_001CA080, 0x38) && W(D_L08_001CA080, 0) == mode) return;
        }
    }
    if (object[0x31] && func_00282E48(object + 0x10, D_L08_001B9B00) < 24.0f) {
        func_002A93B0(object);
        object[0x6F] = 0x16;
    }
    func_L08_003D82F0(object);
    if (F(object, 0x18) < F(state, 0x434) + 0.12f &&
        (func_00278E78() == 1 || func_00278E78() == 11)) {
        W(state, 0x20) = 0;
        object[0x20] = 11;
        return;
    }
    F(object, 0x2C) += (F(*(u8 **)(object + 0x24), 0x24) * 1.7f - F(object, 0x2C)) * 0.05f;
    hit = func_002B0ED8(object, state + 0x50, 0);
    if (hit) {
        if (hit == 5) W(state, 0xE0) = 0;
        W(state, 0x48C) = 240;
        func_L08_003D8A28(object);
    }
    if (object[0x20] < 9 && object[0x20] != 4) {
        direction.q = 0;
        direction.f[2] = F(object, 0xF8);
        position.q = direction.q;
        func_00283410(rotation, &position);
        func_00283698(inverse, rotation);
        func_00283698(objectInverse, object + 0xC0);
        func_002A89A8(object + 0x10, 0, 0.5f);
        func_00282F20(&direction, D_L08_001BFF80, 1.0f);
        func_00283098(&direction, &direction, inverse);
        value = func_00283248(direction.f[2], direction.f[0]);
        func_002AAA00((f32 *)(object + 0xF4), (f32 *)(state + 0x460), 0,
                     value, 0.0017453295f, 0.0017453295f, 0.10471977f);
        value = -func_00283248(direction.f[2], direction.f[1]);
        func_002AAA00((f32 *)(object + 0xF0), (f32 *)(state + 0x464), 0,
                     value, 0.0017453295f, 0.0017453295f, 0.10471977f);
    }
    if (object[0x20] == 8 && object[0x95] == 0) {
        func_0029FCC0(object, 1, &position);
        if (*(u8 **)(state + 0x250) == *(u8 **)(D_00189E20 + 0x2290)) {
            qcopy(state + 0x210, D_00189E20 + 0x80);
            qcopy(state + 0x230, D_00189E20 + 0xD0);
        }
        yaw = func_00283248(F(state, 0x230) - position.f[0], F(state, 0x234) - position.f[1]);
        pitch = func_00283248(func_00282E80(&position, state + 0x230), F(state, 0x238) - position.f[2]);
        x = func_00283BE0(yaw, F(object, 0xF8)) * 0.5f;
        y = func_00283BE0(-pitch, F(object, 0xF4)) * (1.0f / 3.0f);
        for (i = 2; i >= 0; i--) {
            u8 *part = state + (2 - i) * 0x80;
            F(part, 0x2C8) = x;
            if (x > 0.52359885f) F(part, 0x2C8) = 0.52359885f;
            else if (x < -0.52359885f) F(part, 0x2C8) = -0.52359885f;
            F(part, 0x2C4) = y;
        }
    } else {
        for (i = 2; i >= 0; i--) {
            u8 *part = state + (2 - i) * 0x80;
            W(part, 0x2C0) = 0;
            W(part, 0x2C4) = 0;
        }
    }
    for (i = 2; i >= 0; i--)
        func_002AEC48(object, state + 0x260 + (2 - i) * 0x80, 3, 0.02f, 0.4f);
}
