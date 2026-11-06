#include "include_asm.h"
/* func_US2_002CBED0, the USA v2.00 copy of func_002CAF18: the same C, where the menu object moves
 * to +0x39160, its fields to +0x484 and +0x4AC, and the queries sit one or two accessors later. */
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
extern unsigned char D_00189E20[];
extern int func_0026F7C8(void), func_0026F7D0(void), func_0026F7D8(void), func_0026F7E8(void), func_0026F7F0(void), func_0026F7F8(void), func_0026F800(void), func_002DF1B8(void);
extern void func_US2_003492A8(char *, int), func_US2_003492B0(char *, int), func_00348580(char *, int *), func_US2_00349368(char *, int, int), func_US2_00349378(char *, int, int *), func_US2_00349728(char *, int);
#define MENU (D_001A8CFC[0] + 0x39160)
void func_US2_002CBED0(void)
{
    if (!D_001A8CFC[0]) return;
    if (func_0026F7F0()) {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 5, D_001AB7F0);
        func_00348580(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x484) = D_001AB850;
        func_US2_003492A8(p, 0);
        }
        func_US2_00349368(MENU, 0, 1);
        func_US2_00349368(MENU, 2, 1);
        func_US2_00349368(MENU, 3, 1);
        func_US2_00349368(MENU, 1, 1);
        func_US2_00349368(MENU, 4, 1);
        { char *p = MENU; *(int *)(p + 0x4AC) = 0; }
    } else if (func_0026F7D0() && func_0026F7D8()) {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 5, D_001AB808);
        func_00348580(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x484) = D_001AB890;
        func_US2_00349368(p, 0, 1);
        }
        func_US2_00349368(MENU, 1, func_0026F7C8() ^ 1);
        func_US2_00349368(MENU, 2, func_0026F7C8() ^ 1);
        func_US2_00349368(MENU, 3, 1);
        func_US2_00349368(MENU, 4, func_0026F7C8() ^ 1);
        func_US2_003492A8(MENU, 0);
        { char *p = MENU; *(int *)(p + 0x4AC) = 0; }
    } else if (func_0026F7E8()) {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 3, D_001AB820);
        func_00348580(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x484) = D_001AB8D0;
        func_US2_003492A8(p, 0);
        }
        func_US2_00349368(MENU, 0, 1);
        func_US2_00349368(MENU, 1, 1);
        func_US2_00349368(MENU, 2, 1);
        { char *p = MENU; *(int *)(p + 0x4AC) = 0; }
    } else if (func_0026F800() == 0x31 || func_0026F7F8() || func_0026F800() == 0x1C) {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 2, D_001AB830);
        func_00348580(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x484) = D_001AB838;
        func_US2_003492A8(p, 0);
        }
        func_US2_00349368(MENU, 0, 1);
        func_US2_00349368(MENU, 1, 1);
        { char *p = MENU; *(int *)(p + 0x4AC) = 0; }
    } else {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 7, D_001AB7D0);
        func_00348580(MENU, D_001AB7A8);
        { char *p = MENU;
        *(int **)(p + 0x484) = D_002614E8;
        if (D_00189E20[0x22B4] == 1) {
            func_US2_00349368(p, 0, 0);
            func_US2_00349368(MENU, 1, 0);
            func_US2_00349368(MENU, 2, 0);
        } else {
            func_US2_00349368(p, 0, 1);
            func_US2_00349368(MENU, 1, 1);
            func_US2_00349368(MENU, 2, 1);
        }
        }
        func_US2_00349368(MENU, 3, 1);
        func_US2_00349368(MENU, 4, 1);
        func_US2_00349368(MENU, 5, 1);
        if (func_002DF1B8()) {
            func_US2_003492A8(MENU, 1);
            func_US2_00349368(MENU, 6, 1);
        } else {
            func_US2_003492A8(MENU, 0);
            func_US2_00349368(MENU, 6, 0);
        }
        if (D_00189E20[0x22B4] == 1) { char *p = MENU; *(int *)(p + 0x4AC) = 3; }
        else { char *p = MENU; *(int *)(p + 0x4AC) = 0; }
    }
    func_US2_00349728(MENU, 0);
}
