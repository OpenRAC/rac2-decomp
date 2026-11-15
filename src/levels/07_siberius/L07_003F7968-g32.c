#include "common.h"

/* -G32 (with the assembler's -G32): the 32-byte table D_L07_001B1020 and the 16-byte vector
   D_L07_001B1060 are addressed through $gp, and so is D_L07_001B24B0 where its load fills a
   delay slot. */
extern u8 D_L07_001B1020[32] __attribute__((sda));
extern u8 D_L07_001B1060[16] __attribute__((sda));
extern u8 D_L07_001B9200[];
/* `sda` on an array of unknown size: cc1 emits the one-instruction access, which the assembler
   expands absolute outside a delay slot, as retail has it. */
extern u8 *D_L07_001B24B0[] __attribute__((sda));
extern u8 D_L07_001FE3B8[];
extern void func_002A7750(void *, s32, s32);
extern void func_00282A60(void *, s32, s32);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A0F48(void *);
extern f32 func_L07_003F90E8(s32, s32, f32, f32);
extern s32 func_00283CF0(f32);

/* Clears flags 0x41 and 0x80 and sets 0x1000 on the object and its two children, enters state 3
   with or without a target (with one, the tier clamped to 0..1 picks the quadword copied to
   +0x3E0), then sets +0x430 and +0x20 from the tier's share of the duration at +0x24. */
/* Starts the boss's moving state: clears flags on it and its two helpers, remembers the target, and sets the timers for the given tier. */
void func_L07_003F7968(u8 *obj, void *target, s32 tier)
{
    u8 *state = *(u8 **)(obj + 0x68);
    f32 duration, start, end;
    s32 tierIndex;

    *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) & 0xFFBE) | 0x1000;
    *(s32 *)(obj + 0x98) = *(s32 *)(*(u8 **)(obj + 0x24) + 0x10);
    *(u16 *)(obj + 0x34) &= 0xFF7F;
    if (*(u8 **)(state + 0x410)) {
        *(u16 *)(*(u8 **)(state + 0x410) + 0x34) &= 0xFFBE;
        *(u16 *)(*(u8 **)(state + 0x410) + 0x34) |= 0x1000;
        *(s32 *)(*(u8 **)(state + 0x410) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(state + 0x410) + 0x24) + 0x10);
        *(u16 *)(*(u8 **)(state + 0x410) + 0x34) &= 0xFF7F;
    }
    if (*(u8 **)(state + 0x414)) {
        *(u16 *)(*(u8 **)(state + 0x414) + 0x34) &= 0xFFBE;
        *(u16 *)(*(u8 **)(state + 0x414) + 0x34) |= 0x1000;
        *(s32 *)(*(u8 **)(state + 0x414) + 0x98) = *(s32 *)(*(u8 **)(*(u8 **)(state + 0x414) + 0x24) + 0x10);
        *(u16 *)(*(u8 **)(state + 0x414) + 0x34) &= 0xFF7F;
    }
    if (target) {
        tierIndex = tier;
        if (tier >= 2) tierIndex = 1;
        else if (tier < 0) tierIndex = 0;
        qcopy(state + 0x3E0, D_L07_001B1020 + tierIndex * 16);
        *(void **)(state + 0x418) = target;
        SetMobyState(obj, 3, 0);
    } else {
        *(void **)(state + 0x418) = 0;
        SetMobyState(obj, 3, 1);
    }
    if (!D_L07_001B24B0[0]) {
        D_L07_001B24B0[0] = obj;
        ClearMemory(D_L07_001FE3B8, 0, 0xE0);
    }
    start = (tier + 1) * 0.166944921f;
    duration = *(s16 *)(state + 0x24);
    end = tier * 0.166944921f;
    *(u8 *)(state + 0x2E) = 1;
    *(f32 *)(state + 0x430) = duration - duration * start;
    *(f32 *)(state + 0x20) = duration - duration * end;
    if (*(f32 *)(state + 0x430) < 0.0f) *(f32 *)(state + 0x430) = 0.0f;
    *(f32 *)(obj + 0xF4) = *(f32 *)(obj + 0xF0) = 0.0f;
    matrix_mul_vec3(obj + 0x10, D_L07_001B1060, D_L07_001B9200 + 0x230);
    FastVecAdd(obj + 0x10, obj + 0x10, D_L07_001B9200);
    func_002A0F48(obj);
    qzero(state + 0x3F0);
    if (tier >= 0) {
        *(s32 *)(state + 0x420) = tier;
        *(s32 *)(state + 0x458) = FloatToInt(InterpolateBetweenLimits(3, 7, 4.0f, 1.0f));
    }
}
