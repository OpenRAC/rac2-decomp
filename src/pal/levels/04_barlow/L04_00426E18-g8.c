#include "include_asm.h"
#include "names.h"

extern int D_L04_001BFAD8 __attribute__((nosda));
extern int g_hero_moby __attribute__((nosda));
extern char D_L04_001A8F20[1];
extern int D_L04_001B0CF8 __attribute__((sda));
extern int coll_sweep_from_object(void *, void *, int, int, float, float, float, int, int);
extern int coll_test_point(void *, int, float, void *);
extern void func_PAL_002ABCB8(void *owner, char *offset, void *filter);
extern int math_fast_float_d(void *);

void func_PAL_L04_00426E18(char *a0)
{
    char *s0 = a0;
    char *s1 = s0 + 0x10;

    coll_sweep_from_object(s0, s1, 0x10001, 5, 1.0f, 1.0f, 1.0f, 1, 0);
    if (coll_test_point(s1, 1, 1.0f, s0) != 0) {
        if (D_L04_001BFAD8 != 0 && D_L04_001BFAD8 == g_hero_moby) {
            if (D_L04_001B0CF8 <= 0) {
                D_L04_001B0CF8 = 0x32;
            }
        }
    }
    if (D_L04_001B0CF8 > 0) {
        func_PAL_002ABCB8(g_hero_moby, D_L04_001A8F20, 0xFFFF);
        math_fast_float_d(&D_L04_001B0CF8);
    }
}
