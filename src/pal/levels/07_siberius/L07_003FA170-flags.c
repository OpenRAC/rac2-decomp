#include "include_asm.h"

#include "common.h"
typedef float Vector[4];
extern void func_PAL_L07_003FAF68(u8 *);
extern void func_002A7750(u8 *, u8, s32);
extern s32 func_002B3868(u8 *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_L07_003F68F0(s8 *, f32);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern int func_002E5CF8(int, int, char *);
extern void *func_PAL_L03_003DDB50(void *, void *, void *, s32);
extern f32 D_L07_001B0FA0 __attribute__((sda));
extern s32 D_L07_001B0FA8 __attribute__((sda));
extern Vector D_L07_001B0FB0 __attribute__((sda));
extern f32 D_L07_001B0FC0 __attribute__((sda));
extern s32 D_L07_001B1E08 __attribute__((nosda));

/* Advances the dormant entity through initialization and its firing state. */
void func_PAL_L07_003FAAD8(u8 *object)
{
    u8 *state;
    Vector position, velocity;
    if (object[0x20] == 1) return;
    state = *(u8 **)(object + 0x68);
    func_PAL_L07_003FAF68(object);
    switch (object[0x20]) {
    case 0:
        *(f32 *)(state + 0x58) = *(f32 *)(object + 0x18);
        *(f32 *)(state + 0x60) = *(f32 *)(object + 0xF8);
        *(s32 *)(object + 0x98) = 0;
        *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
        func_002A7750(object, 1, -1);
        break;
    case 2:
        if (func_002B3868(object)) {
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xFFBE) | 0x1000;
            *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
            if (object[0x43]) func_PAL_002A7E68(object, 0, 0, 1);
        }
        if (object[0x60] & 2) {
            if (object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, 1);
            func_002A7750(object, 3, -1);
        }
        break;
    case 3: {
        s32 period, tick;
        func_L07_003F68F0((s8 *)object, D_L07_001B0FA0 * 0.0003490659f);
        period = D_L07_001B0FA8;
        tick = D_L07_001B1E08;
        if (tick % period == 0) {
            func_00283098(position, D_L07_001B0FB0, object + 0xC0);
            func_00282CC0(position, position, object + 0x10);
            func_00282F20(velocity, object + 0xC0, D_L07_001B0FC0 * 0.020000001f);
            func_002E5CF8(0, 0, (char *)object);
            func_PAL_L03_003DDB50(object, position, velocity, state[0x34]);
        }
        break;
    }
    }
}
