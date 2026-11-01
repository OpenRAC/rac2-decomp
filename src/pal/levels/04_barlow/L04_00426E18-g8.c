#include "include_asm.h"

extern int D_L04_001BFAD8 __attribute__((nosda));
extern int D_0018C0B0 __attribute__((nosda));
extern char D_L04_001A8F20[1];
extern int D_L04_001B0CF8 __attribute__((sda));
extern void func_002A8C28(void *, void *, int, int, float, float, float, int, int);
extern int func_00277258(void *, int, float, void *);
extern void func_PAL_002ABCB8(void *owner, char *offset, void *filter);
extern int func_00282948(void *);

void func_PAL_L04_00426E18(char *a0)
{
    char *s0 = a0;
    char *s1 = s0 + 0x10;

    func_002A8C28(s0, s1, 0x10001, 5, 1.0f, 1.0f, 1.0f, 1, 0);
    if (func_00277258(s1, 1, 1.0f, s0) != 0) {
        if (D_L04_001BFAD8 != 0 && D_L04_001BFAD8 == D_0018C0B0) {
            if (D_L04_001B0CF8 <= 0) {
                D_L04_001B0CF8 = 0x32;
            }
        }
    }
    if (D_L04_001B0CF8 > 0) {
        func_PAL_002ABCB8(D_0018C0B0, D_L04_001A8F20, 0xFFFF);
        func_00282948(&D_L04_001B0CF8);
    }
}
