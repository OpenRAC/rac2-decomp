#include "include_asm.h"

#include "common.h"
typedef struct { u8 reserved00[0x34]; u16 flags; } ObjectFlagsPrefix;
typedef struct { u8 reserved00[0x68]; u8 *state; } LinkEntityPrefix;
extern u8 *D_L18_001B281C MACRO_ADDR;
extern void func_PAL_L18_0042BA90(u8 *, s32, s32, float);
extern s32 func_L18_00427130(u8 *, s32, s32);
extern s32 func_002829A8(void *);
extern s32 func_L02_002EF388(u8 *, void *, void *, s32, s32);
extern void func_002A7750(u8 *, s32, s32);

void func_PAL_L18_0042BD70(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *source;
    u8 *target;
    if (*(s32 *)(state + 0x3B4) == -1) return;
    source = D_L18_001B281C + (*(s32 *)(state + 0x3B4) << 8);
    qcopy((object + 0x10), (source + 0x10));
    qcopy((object + 0xF0), (source += 0xF0));
    state[0x2E] = 1;
    state[0x6A] = 0;
    *(s16 *)(state + 0x88) = 0;
    *(float *)(state + 0x20) = (float)*(s16 *)(state + 0x24);
    *(s32 *)(state + 0x94) = 0;
    object[0xA8] = 255;
    func_PAL_L18_0042BA90(object, 7, 0, 1.0f);
    *(float *)(object + 0x48) = 0.1f;
    *(s32 *)(state + 0x13C) = *(s32 *)(state + 0x380);
    func_L18_00427130(object, *(s32 *)(state + 0x36C), -1);
    *(s32 *)(object + 0x98) = 0;
    object[0x7F] = 0;
    ((ObjectFlagsPrefix *)object)->flags &= ~0x1000;
    if (!(state[0x3B1] & 0x80)) func_002829A8(state + 0x3B1);
    *(float *)(state + 0x100) = 0.7f;
    if (*(s32 *)(state + 0x3B4) != -1 && (target = (u8 *)((*(s32 *)(state + 0x3B4) << 8) + (u32)D_L18_001B281C), *(s16 *)(target + 0xAA)) == 0x114D && target[0x20] != 0xFE && target[0x20] != 0xFD) {
        u8 *entities;
        s32 link_index;
        object[0x31] = 0;
        ((ObjectFlagsPrefix *)object)->flags |= 1;
        entities = D_L18_001B281C;
        link_index = *(s32 *)(state + 0x3B4);
        *(u8 **)((LinkEntityPrefix *)((link_index << 8) + (u32)entities))->state = object;
        *(float *)(object + 0x48) = 1.0f;
        func_002A7750(object, 0, 11);
    } else {
        func_L02_002EF388(object, object + 0x10, object + 0xF0, 0, 0);
        func_002A7750(object, 0, 14);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L18_0042BF58);

INCLUDE_ASM("asm/pal/levels", func_PAL_L18_0042C210);
