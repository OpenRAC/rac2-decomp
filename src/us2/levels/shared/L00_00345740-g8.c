#include "include_asm.h"
#include "names.h"
/* func_US2_L00_00345740, the level copy of func_US2_002CBED0: the same C, with the level's own
 * accessors. The menu data sits elsewhere in each level, and the accessor _07 is a 48-byte
 * function in levels 18, 19 and 20 but func_L00_002D6878 in the others. */
extern char *D_001A8CFC[] __attribute__((sda));
extern int ref_US2_L00_00345740_00[1] __attribute__((sda)), ref_US2_L00_00345740_01[1] __attribute__((sda));
extern int ref_US2_L00_00345740_02[1] __attribute__((sda)), ref_US2_L00_00345740_03[1] __attribute__((sda));
extern int ref_US2_L00_00345740_04[1] __attribute__((sda)), ref_US2_L00_00345740_05[1] __attribute__((sda));
extern int ref_US2_L00_00345740_06[1] __attribute__((sda)), ref_US2_L00_00345740_08[1] __attribute__((sda));
extern int ref_US2_L00_00345740_09[1] __attribute__((sda)), ref_US2_L00_00345740_10[1] __attribute__((sda));
extern int ref_US2_L00_00345740_11[];
extern unsigned char g_hero_state[];
extern int level_is_mode_twenty_five(void), level_is_mode_in_set(void), level_run_mode_update_zero(void), level_is_special_global_value(void), level_is_special_mode_active(void), level_get_global_word(void), stub_l00_return_one(void);
extern int ref_US2_L00_00345740_07(void);
extern void func_US2_003492A8(char *, int), func_US2_003492B0(char *, int), menu_load_sprites_from_values(char *, int *), func_US2_00349368(char *, int, int), func_US2_00349378(char *, int, int *);
extern int func_US2_00349728(char *, int);
void func_US2_L00_00345740(void)
{
    if (!D_001A8CFC[0]) return;
    if (level_is_special_mode_active()) {
        func_US2_003492B0((D_001A8CFC[0] + 0x39160), 1);
        func_US2_00349378((D_001A8CFC[0] + 0x39160), 5, ref_US2_L00_00345740_00);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), ref_US2_L00_00345740_01);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = ref_US2_L00_00345740_02;
        func_US2_003492A8(p, 0);
        }
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 0, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 2, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 3, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 1, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 4, 1);
        { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4AC) = 0; }
    } else if (level_is_mode_in_set() && level_run_mode_update_zero()) {
        func_US2_003492B0((D_001A8CFC[0] + 0x39160), 1);
        func_US2_00349378((D_001A8CFC[0] + 0x39160), 5, ref_US2_L00_00345740_03);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), ref_US2_L00_00345740_01);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = ref_US2_L00_00345740_04;
        func_US2_00349368(p, 0, 1);
        }
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 1, level_is_mode_twenty_five() ^ 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 2, level_is_mode_twenty_five() ^ 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 3, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 4, level_is_mode_twenty_five() ^ 1);
        func_US2_003492A8((D_001A8CFC[0] + 0x39160), 0);
        { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4AC) = 0; }
    } else if (level_is_special_global_value()) {
        func_US2_003492B0((D_001A8CFC[0] + 0x39160), 1);
        func_US2_00349378((D_001A8CFC[0] + 0x39160), 3, ref_US2_L00_00345740_05);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), ref_US2_L00_00345740_01);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = ref_US2_L00_00345740_06;
        func_US2_003492A8(p, 0);
        }
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 0, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 1, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 2, 1);
        { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4AC) = 0; }
    } else if (level_get_global_word() == 0x31 || ref_US2_L00_00345740_07() || level_get_global_word() == 0x1C) {
        func_US2_003492B0((D_001A8CFC[0] + 0x39160), 1);
        func_US2_00349378((D_001A8CFC[0] + 0x39160), 2, ref_US2_L00_00345740_08);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), ref_US2_L00_00345740_01);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = ref_US2_L00_00345740_09;
        func_US2_003492A8(p, 0);
        }
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 0, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 1, 1);
        { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4AC) = 0; }
    } else {
        func_US2_003492B0((D_001A8CFC[0] + 0x39160), 1);
        func_US2_00349378((D_001A8CFC[0] + 0x39160), 7, ref_US2_L00_00345740_10);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), ref_US2_L00_00345740_01);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = ref_US2_L00_00345740_11;
        if (g_hero_state[0x22B4] == 1) {
            func_US2_00349368(p, 0, 0);
            func_US2_00349368((D_001A8CFC[0] + 0x39160), 1, 0);
            func_US2_00349368((D_001A8CFC[0] + 0x39160), 2, 0);
        } else {
            func_US2_00349368(p, 0, 1);
            func_US2_00349368((D_001A8CFC[0] + 0x39160), 1, 1);
            func_US2_00349368((D_001A8CFC[0] + 0x39160), 2, 1);
        }
        }
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 3, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 4, 1);
        func_US2_00349368((D_001A8CFC[0] + 0x39160), 5, 1);
        if (stub_l00_return_one()) {
            func_US2_003492A8((D_001A8CFC[0] + 0x39160), 1);
            func_US2_00349368((D_001A8CFC[0] + 0x39160), 6, 1);
        } else {
            func_US2_003492A8((D_001A8CFC[0] + 0x39160), 0);
            func_US2_00349368((D_001A8CFC[0] + 0x39160), 6, 0);
        }
        if (g_hero_state[0x22B4] == 1) { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4AC) = 3; }
        else { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4AC) = 0; }
    }
    func_US2_00349728((D_001A8CFC[0] + 0x39160), 0);
}
