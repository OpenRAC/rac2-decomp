#include "include_asm.h"

extern double D_L13_001AEC00 __attribute__((sda));
extern double D_L13_001AEC08 __attribute__((sda));
extern double D_L13_001AEC10 __attribute__((sda));
extern void func_002A7750(unsigned char *, int, int);
extern int func_002A9640(unsigned char *, int, int);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_0029F338(void *);
extern int D_L01_001AEC38;
extern int ref_L01_00412E00_00 __attribute__((sda));

void func_PAL_L01_00418210(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        ref_L01_00412E00_00 = ref_L01_00412E00_00 + 1;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x04010000, 0) != 0 && *(int *)s1 == 0) {
            ref_L01_00412E00_00 = D_L01_001AEC38 - 1;
            func_002A7750(a0, 2, -1);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_PAL_L00_0032C328(a0, &D_L13_001AEC10, &D_L13_001AEC08, &D_L13_001AEC00, 0xFFFF, 0, -1, 0,
                    0xFFFF, 0xFF, 0);
        func_0029F338(a0);
        break;
    }
}
