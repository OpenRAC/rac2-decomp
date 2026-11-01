#include "include_asm.h"

#include "common.h"
extern u8 D_00189E20[];
extern u8 D_00189EA0[];
extern u8 D_0018C750[];
extern u8 D_001395B8[];
extern u32 D_001A7390[] __attribute__((sda));
extern u8 D_001A7A60[] __attribute__((sda));
extern s32 D_001A903C[] __attribute__((sda));
extern s32 D_0018CC18;
extern s32 func_002ACBC8(void *a0, s32 a1);
extern void func_002E5E58(s32 a0, s32 a1, s32 a2);
extern void func_US2_002B1880(s32 a0, s32 a1);
extern void func_US2_00289840(s32 a0, s32 a1);

void func_US2_L13_003E9D48(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    s16 h;
    u8 *hero;
    u8 *timers;
    u8 *counters;

    if (self[0x20] == 0) {
        self[0x30] = 0xFF;
        *(s16 *)(state + 0xC) = 0;
        self[0x20] = 1;
    }
    if (self[0x20] != 1)
        return;
    h = *(s16 *)(state + 0xE);
    switch (h) {
    case 0:
        if (func_002ACBC8(D_00189EA0, *(s32 *)(state + 4)) != 0 && *(s32 *)(D_00189EA0 + 0x221C) == 0xF)
            *(s16 *)(state + 0xE) = 1;
        break;
    case 1:
        hero = D_00189E20;
        if (*(s32 *)(hero + 0x2294) == 0x3E) {
            *(s16 *)(state + 0xE) = 0;
        } else if (func_002ACBC8(hero + 0x80, *(s32 *)(state + 8)) != 0 && D_001A7A60[4] == 0) {
            D_001A7A60[4] = 1;
            func_002E5E58(1, 0, 0);
            func_US2_002B1880(0x1233, -1);
            D_001A903C[0] = 1;
        }
        break;
    }
    if (func_002ACBC8(D_00189EA0, *(s32 *)state) == 0)
        return;
    timers = D_0018C750;
    if (*(u16 *)(timers + 0x1BC) != 0 && !(D_001A7390[0] - *(u32 *)(timers + 0x1C0) > 0x69780))
        return;
    counters = D_001395B8;
    if (counters[0x7E] < 2 && *(s16 *)(state + 0xC) == 0) {
        if (D_0018CC18 >= 0)
            func_US2_00289840(0x9E3, 0x3A);
        counters[0x7E] = counters[0x7E] + 1;
        *(s16 *)(state + 0xC) = 1;
    }
}

