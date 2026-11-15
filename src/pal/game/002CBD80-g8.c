#include "include_asm.h"
#include "names.h"
/* func_PAL_002CBD80, the PAL copy of func_002CAF18: the same C, where the menu object moves
 * to +0x39160, its fields to +0x484 and +0x4AC, and each query is the next accessor along. */
extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001AB7A8[1] __attribute__((sda));
extern int D_001AB7D0[1] __attribute__((sda));
extern int D_001AB7F0[1] __attribute__((sda));
extern int D_001AB808[1] __attribute__((sda));
extern int D_001AB820[1] __attribute__((sda));
extern int D_001AB830[1] __attribute__((sda));
extern int D_001AB838[1] __attribute__((sda));
extern int D_001AB850[1] __attribute__((sda));
extern int D_001AB890[1] __attribute__((sda));
extern int D_001AB8D0[1] __attribute__((sda));
extern int D_002614E8[];
extern unsigned char g_hero_state[];
extern int stub_empty_23(void), stub_empty_24(void), stub_empty_25(void), stub_empty_26(void), stub_empty_27(void), stub_empty_28(void), stub_empty_29(void), menu_always_return_true(void);
extern void func_PAL_0034A738(char *, int), func_PAL_0034A740(char *, int), menu_load_sprites_from_values(char *, int *), func_PAL_0034A7F8(char *, int, int), func_PAL_0034A808(char *, int, int *), func_PAL_0034ABB0(char *, int);
void func_PAL_002CBD80(void)
{
    if (!D_001A8CFC[0]) return;
    if (stub_empty_27()) {
        func_PAL_0034A740((D_001A8CFC[0] + 0x39160), 1);
        func_PAL_0034A808((D_001A8CFC[0] + 0x39160), 5, D_001AB7F0);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), D_001AB7A8);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = D_001AB850;
        func_PAL_0034A738(p, 0);
        }
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 0, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 2, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 3, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 1, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 4, 1);
        { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    } else if (stub_empty_24() && stub_empty_25()) {
        func_PAL_0034A740((D_001A8CFC[0] + 0x39160), 1);
        func_PAL_0034A808((D_001A8CFC[0] + 0x39160), 5, D_001AB808);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), D_001AB7A8);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = D_001AB890;
        func_PAL_0034A7F8(p, 0, 1);
        }
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 1, stub_empty_23() ^ 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 2, stub_empty_23() ^ 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 3, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 4, stub_empty_23() ^ 1);
        func_PAL_0034A738((D_001A8CFC[0] + 0x39160), 0);
        { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    } else if (stub_empty_26()) {
        func_PAL_0034A740((D_001A8CFC[0] + 0x39160), 1);
        func_PAL_0034A808((D_001A8CFC[0] + 0x39160), 3, D_001AB820);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), D_001AB7A8);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = D_001AB8D0;
        func_PAL_0034A738(p, 0);
        }
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 0, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 1, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 2, 1);
        { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    } else if (stub_empty_29() == 0x31 || stub_empty_28() || stub_empty_29() == 0x1C) {
        func_PAL_0034A740((D_001A8CFC[0] + 0x39160), 1);
        func_PAL_0034A808((D_001A8CFC[0] + 0x39160), 2, D_001AB830);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), D_001AB7A8);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = D_001AB838;
        func_PAL_0034A738(p, 0);
        }
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 0, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 1, 1);
        { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    } else {
        func_PAL_0034A740((D_001A8CFC[0] + 0x39160), 1);
        func_PAL_0034A808((D_001A8CFC[0] + 0x39160), 7, D_001AB7D0);
        menu_load_sprites_from_values((D_001A8CFC[0] + 0x39160), D_001AB7A8);
        { char *p = (D_001A8CFC[0] + 0x39160);
        *(int **)(p + 0x484) = D_002614E8;
        if (g_hero_state[0x22B4] == 1) {
            func_PAL_0034A7F8(p, 0, 0);
            func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 1, 0);
            func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 2, 0);
        } else {
            func_PAL_0034A7F8(p, 0, 1);
            func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 1, 1);
            func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 2, 1);
        }
        }
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 3, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 4, 1);
        func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 5, 1);
        if (menu_always_return_true()) {
            func_PAL_0034A738((D_001A8CFC[0] + 0x39160), 1);
            func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 6, 1);
        } else {
            func_PAL_0034A738((D_001A8CFC[0] + 0x39160), 0);
            func_PAL_0034A7F8((D_001A8CFC[0] + 0x39160), 6, 0);
        }
        if (g_hero_state[0x22B4] == 1) { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4ac) = 3; }
        else { char *p = (D_001A8CFC[0] + 0x39160); *(int *)(p + 0x4ac) = 0; }
    }
    func_PAL_0034ABB0((D_001A8CFC[0] + 0x39160), 0);
}
