#include "include_asm.h"
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
extern unsigned char D_00189E20[];
extern int func_L00_002D6710(void), func_L00_002D6728(void), func_L00_002D6768(void), func_L00_002D6848(void), func_L00_002D6880(void), func_L00_002D68E8(void), func_L00_00358668(void);
extern int ref_US2_L00_00345740_07(void);
extern void func_US2_003492A8(char *, int), func_US2_003492B0(char *, int), func_00348580(char *, int *), func_US2_00349368(char *, int, int), func_US2_00349378(char *, int, int *), func_US2_00349728(char *, int);
#define MENU (D_001A8CFC[0] + 0x39160)
void func_US2_L00_00345740(void)
{
    if (!D_001A8CFC[0]) return;
    if (func_L00_002D6880()) {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 5, ref_US2_L00_00345740_00);
        func_00348580(MENU, ref_US2_L00_00345740_01);
        { char *p = MENU;
        *(int **)(p + 0x484) = ref_US2_L00_00345740_02;
        func_US2_003492A8(p, 0);
        }
        func_US2_00349368(MENU, 0, 1);
        func_US2_00349368(MENU, 2, 1);
        func_US2_00349368(MENU, 3, 1);
        func_US2_00349368(MENU, 1, 1);
        func_US2_00349368(MENU, 4, 1);
        { char *p = MENU; *(int *)(p + 0x4AC) = 0; }
    } else if (func_L00_002D6728() && func_L00_002D6768()) {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 5, ref_US2_L00_00345740_03);
        func_00348580(MENU, ref_US2_L00_00345740_01);
        { char *p = MENU;
        *(int **)(p + 0x484) = ref_US2_L00_00345740_04;
        func_US2_00349368(p, 0, 1);
        }
        func_US2_00349368(MENU, 1, func_L00_002D6710() ^ 1);
        func_US2_00349368(MENU, 2, func_L00_002D6710() ^ 1);
        func_US2_00349368(MENU, 3, 1);
        func_US2_00349368(MENU, 4, func_L00_002D6710() ^ 1);
        func_US2_003492A8(MENU, 0);
        { char *p = MENU; *(int *)(p + 0x4AC) = 0; }
    } else if (func_L00_002D6848()) {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 3, ref_US2_L00_00345740_05);
        func_00348580(MENU, ref_US2_L00_00345740_01);
        { char *p = MENU;
        *(int **)(p + 0x484) = ref_US2_L00_00345740_06;
        func_US2_003492A8(p, 0);
        }
        func_US2_00349368(MENU, 0, 1);
        func_US2_00349368(MENU, 1, 1);
        func_US2_00349368(MENU, 2, 1);
        { char *p = MENU; *(int *)(p + 0x4AC) = 0; }
    } else if (func_L00_002D68E8() == 0x31 || ref_US2_L00_00345740_07() || func_L00_002D68E8() == 0x1C) {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 2, ref_US2_L00_00345740_08);
        func_00348580(MENU, ref_US2_L00_00345740_01);
        { char *p = MENU;
        *(int **)(p + 0x484) = ref_US2_L00_00345740_09;
        func_US2_003492A8(p, 0);
        }
        func_US2_00349368(MENU, 0, 1);
        func_US2_00349368(MENU, 1, 1);
        { char *p = MENU; *(int *)(p + 0x4AC) = 0; }
    } else {
        func_US2_003492B0(MENU, 1);
        func_US2_00349378(MENU, 7, ref_US2_L00_00345740_10);
        func_00348580(MENU, ref_US2_L00_00345740_01);
        { char *p = MENU;
        *(int **)(p + 0x484) = ref_US2_L00_00345740_11;
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
        if (func_L00_00358668()) {
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
