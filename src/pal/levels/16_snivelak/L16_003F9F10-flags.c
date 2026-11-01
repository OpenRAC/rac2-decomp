#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_00282948(void *);
extern void func_L16_004050D8(u8 *);
extern void func_0029F978(u8 *, s32, void *);
extern void func_00283898(void *, s32, float);
extern float func_00283BE0(float, float);
extern void func_002A8C00(void *, u8 *, s32, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282C48(float);
extern void func_002A8E20(s32, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282E80(void *, void *);
extern u8 D_L16_00189E20[];

void func_PAL_L16_00409AD0(u8 *arg)
{
    float delta[4];
    float pos[4];
    u8 query[0x30];
    u8 *state;
    u8 *hero;
    state = *(u8 **)(arg + 0x68);
    func_00282948(state + 0x258);
    if (*(u16 *)(arg + 0x96) < 0xFFFF) ++*(u16 *)(arg + 0x96);
    func_L16_004050D8(arg);
    if (!state[0x211]) func_0029F978(arg, 7, state + 0x210);
    func_00283898(state + 0x220, 2, *(float *)(state + 0x26C));
    *(float *)(state + 0x26C) = func_00283BE0(*(float *)(state + 0x26C), 0.49916422f);
    if (*(s32 *)(state + 0x2AC)) {
        func_002A8C00(query, arg, 1, arg + 0xE0, 10.0f);
        *(u16 *)(query + 0x1A) = *(u16 *)(arg + 0xAA);
        *(TI128 *)pos = *(TI128 *)(arg + 0x10);
        pos[2] += 3.5f;
        func_00282F20(delta, arg + 0xC0, -1.3f);
        func_00282CC0(pos, delta, pos);
        hero = D_L16_00189E20;
        if (func_00282C48(*(float *)(hero + 0x88) - pos[2]) < 0.1f &&
            func_00282E80(pos, hero + 0x80) < 9.1f)
            func_002A8E20(*(s32 *)(hero + 0x2290), query);
    }
}
