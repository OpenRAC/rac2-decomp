#include "include_asm.h"


extern double D_L01_001B1950 __attribute__((sda));
extern double D_L01_001B1958 __attribute__((sda));
extern double D_L01_001B1960 __attribute__((sda));
extern void func_3248E0(unsigned char *, int, int);
extern int func_326C70(unsigned char *, int, int);
extern void func_333240(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_00364DF8(int, int, void *);
extern void func_00329F80(void *, int, int);
extern void func_314008(void *);

/* Hand-adapted from func_L12_00388090. */
extern int D_L01_001AEBF8 __attribute__((sda));
extern int D_L01_001AEC38;
extern int ref_L01_00412E00_00 __attribute__((sda));
void func_L01_00412E00(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        ref_L01_00412E00_00 = ref_L01_00412E00_00 + 1;
        func_3248E0(a0, 1, -1);
        break;
    case 1:
        if (func_326C70(a0, 0x04010000, 0) != 0 && *(int *)s1 == 0) {
            ref_L01_00412E00_00 = D_L01_001AEC38 - 1;
            func_3248E0(a0, 2, -1);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_333240(a0, &D_L01_001B1960, &D_L01_001B1958, &D_L01_001B1950, 0xFFFF, 0, -1, 0,
                    0xFFFF, 0xFF, 0);
        func_314008(a0);
        break;
    }
}
