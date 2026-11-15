#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef unsigned char u8;
extern s32 math_fast_float_d(u8 *a0);
extern void FadeToBlack(s32 a0);
extern char *GetLocalizedString(s32 a0);
extern int func_PAL_L00_0030FBC0(s32 a0, s32 a1);
extern void entry_init_all_registered(void);
extern void feltzin_challenge_reset(u8 *a0);
extern s32 D_L05_001B13E4 __attribute__((sda));

/* Either shuts the level's spawn state down and marks the reset flag, or asks the shared
   gadget lookup for one of the two fixed item strings and forwards it to the dispatcher. */
void func_PAL_L05_00426200(u8 *a0, s32 a1)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (math_fast_float_d(p + 0x48) == 0) {
        if (a1 == 1)
            func_PAL_L00_0030FBC0(GetLocalizedString(0x10E1), -1);
        else if (a1 == 3)
            func_PAL_L00_0030FBC0(GetLocalizedString(0x10F6), -1);
    } else {
        /* The two stores are written against the retail order: 0x48 first. */
        *(s32 *)(p + 0x48) = 0x7D;
        *(s32 *)(p + 0x44) = 0x1770;
        FadeToBlack(0x19);
        feltzin_challenge_reset(a0);
        entry_init_all_registered();
        D_L05_001B13E4 = 0;
    }
}

typedef signed short s16;
typedef unsigned int u32;
typedef float f32;
extern void music_Unpause(void);
extern void hero_set_state_value_a(s32 a0);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void func_PAL_L05_0037D9D0(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void func_PAL_L05_00425FB0(u8 *a0, s32 a1);
extern void func_PAL_L05_00426200(u8 *a0, s32 a1);
extern s32 D_L05_001B1364 __attribute__((sda));
extern s32 D_L05_001B2048 __attribute__((sda));
typedef struct { s32 count; u8 pad04[12]; s32 active; u8 pad14[24]; s32 reset; } FeltzinState;
extern u8 D_L05_00221D10[];
extern u8 D_L05_001B3550[] __attribute__((section(".sdata")));
extern u8 *D_L05_001B2614;

void func_PAL_L05_00426658(u8 *arg0)
{
    u8 *owner = *(u8 **)(arg0 + 0x68);
    u8 **list;
    u32 count;
    s32 index;
    s32 found;

    math_fast_float_d(D_L05_001B3550);
    if (D_L05_001B1364 == 0) {
        ((FeltzinState *)D_L05_00221D10)->reset = 0;
        *(s32 *)D_L05_001B3550 = 0x1770;
        *(s32 *)(owner + 0x44) = 0x1770;
        D_L05_001B1364 = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        list = level_get_object_list();
        found = level_get_saved_value();
        if (found > 0) {
            count = found;
            do {
                u8 *entry = *list;

                if (*(s16 *)(entry + 0xAA) == 0x10F5) {
                    f32 scale = 64.0f;

                    func_PAL_L05_0037D9D0(entry, 1);
                    index = ((FeltzinState *)D_L05_00221D10)->count;
                    func_L05_0037CEE0(*list, (u8 *)D_L05_001B2614 + (index << 7) + 0x30, scale);
                    index = ((FeltzinState *)D_L05_00221D10)->count;
                    func_L05_0037D608(*list, (u8 *)D_L05_001B2614 + (index << 7) + 0x30, scale);
                }
                count--;
                list++;
            } while (count != 0);
        }
    }
    if (((FeltzinState *)D_L05_00221D10)->active == 0 && D_L05_001B2048 >= 6) {
        func_PAL_L05_00425FB0(arg0, 1);
        return;
    }
    if (math_fast_float_d(owner + 0x44) != 0)
        func_PAL_L05_00426200(arg0, 1);
}
