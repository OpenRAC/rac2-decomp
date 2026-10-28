/* func_L17_003C7498 - 484 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file L17_003C7498-g8.c with cflags line: `-O2 -G8 -ffunction-
   sections -g -frac2-gcse-unsplit-edges` (marker removal in L17_0032C070.c
   needed).
   -frac2-gcse-unsplit-edges stops gcse hoisting obj+0x10 to function top
   (retail recomputes it); -g + division in its own statement gives the pre-
   div.s nop pair. Size 484 OK.
   Only 3 masked diff lines remain: retail `addiu v0,zero,-1` + `lw
   a1,0xCC(s0)` + `beq a1,v0`; mine const in v1 and value in v0. Tried: -1 !=
   x, named const, local `link`, ~, u32 compare. */

#include "common.h"

extern int func_002ACBC8(void *);
extern float func_00282E80(void *, void *);
extern float func_00283180(float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern u8 D_00189EA0[];
extern u8 *D_L17_001B2D0C __attribute__((sda));
extern float D_L17_001B03B0 __attribute__((sda));

void func_L17_003C7498(u8 *obj, s32 *path, float speed) {
    u8 *st = *(u8 **)(obj + 0x68);
    u8 *hero;
    s32 index;
    f32 t;
    f32 frac;
    f32 num;
    f32 den;
    f32 ang;
    f32 delta[4] __attribute__((aligned(16)));
    u8 *from;

    if (*(s32 *)(st + 0xCC) != -1 && *(s32 *)(st + 0xAC) == 1) {
        hero = D_00189EA0;
        if (func_002ACBC8(hero) != 0 && *(f32 *)(hero + 8) <= *(f32 *)(obj + 0x18) + 0.05f
            && func_00282E80(obj + 0x10, D_L17_001B2D0C + (*(s32 *)(st + 0xCC) << 7) + 0x30) <= D_L17_001B03B0) {
            *(f32 *)(st + 0x9C) = *(f32 *)(st + 0x9C) - 1.0f;
            return;
        }
    }
    num = *(f32 *)(st + 0x9C) * 3.141593f;
    den = speed * 60.0f;
    ang = num / den;
    t = (1.0f - func_00283180(ang)) * 0.5f;
    index = func_00283CF0(func_00283CE0(path[0] - 1) * t);
    frac = func_00283CE0(path[0] - 1) * t - func_00283CE0(index);
    if (index == path[0] - 1) {
        qcopy(obj + 0x10, (u8 *)path + index * 16 + 0x10);
        return;
    }
    from = (u8 *)path + (index * 16 + 0x10);
    func_00282CF0(delta, (u8 *)path + (index * 16 + 0x20), from);
    func_00282D30(delta, delta, frac);
    func_00282CC0(obj + 0x10, delta, from);
}
