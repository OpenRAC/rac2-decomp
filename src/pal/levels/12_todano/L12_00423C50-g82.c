#include "include_asm.h"

extern double ref_L12_00420838_00 __attribute__((sda));
extern double ref_L12_00420838_01 __attribute__((sda));
extern double ref_L12_00420838_02 __attribute__((sda));
extern void func_002A7750(unsigned char *, int, int);
extern int func_002A9640(unsigned char *, int, int);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern int ref_L12_00420838_03 __attribute__((sda));
extern void func_002E5CF8(int, int, void *);
extern void func_L00_00326620(void *, int, int);
extern void func_0029F338(void *);

/* Hand-adapted from func_L12_00388090. */
void func_PAL_L12_00425BE0(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x04010000, 0) != 0 && *(int *)s1 == 0) {
            func_002A7750(a0, 2, -1);
            func_002E5CF8(0, 0, a0);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_PAL_L00_0032C328(a0, &ref_L12_00420838_02, &ref_L12_00420838_01, &ref_L12_00420838_00, 0xFFFF, 0, ref_L12_00420838_03, 0,
                    0xFFFF, 0xFF, 0);
        func_L00_00326620(a0, 0x110D, 0);
        func_0029F338(a0);
        break;
    }
}
