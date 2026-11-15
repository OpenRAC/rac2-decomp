#include "include_asm.h"
#include "names.h"

typedef signed short s16;
typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(s32 a0);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void func_PAL_L05_0037D9D0(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void func_PAL_L05_00425FB0(u8 *a0, s32 a1);
extern s32 D_L05_001B1364 __attribute__((sda));
extern s32 D_L05_00221D10[];
extern s32 D_L05_001B2048;
extern u8 *D_L05_001B2614;

void func_PAL_L05_004267E0(u8 *arg0) {
    s32 n;
    s32 count;
    u8 **p;

    if (D_L05_001B1364 == 0) {
        D_L05_00221D10[11] = 0;
        D_L05_001B1364 = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        p = level_get_object_list();
        count = level_get_saved_value();
        if (count > 0) {
            n = count;
            do {
                if (*(s16 *)(*p + 0xAA) == 0xF73) {
                    func_PAL_L05_0037D9D0(*p, 1);
                    func_L05_0037CEE0(*p, (u8 *)D_L05_001B2614 + (D_L05_00221D10[0] << 7) + 0x30, 64.0f);
                    func_L05_0037D608(*p, (u8 *)D_L05_001B2614 + (D_L05_00221D10[0] << 7) + 0x30, 64.0f);
                }
                n--;
                p++;
            } while (n);
        }
    }
    if (D_L05_00221D10[4] == 0 && D_L05_001B2048 >= 6)
        func_PAL_L05_00425FB0(arg0, 2);
}
