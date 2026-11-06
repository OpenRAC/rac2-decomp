#include "include_asm.h"


extern double D_L12_001AEC40 __attribute__((sda));
extern double D_L12_001AEC48 __attribute__((sda));
extern double D_L12_001AEC50 __attribute__((sda));
extern void func_3248E0(unsigned char *, int, int);
extern int func_326C70(unsigned char *, int, int);
extern void func_31A718(unsigned char *);
extern void func_333240(void *, void *, void *, void *, int, int, int, int, int, int, int);

/* Hand-adapted from func_L13_0038C718. */
extern int D_L12_001AEC70 __attribute__((sda));
extern void func_00364DF8(int, int, void *);
extern void func_00329F80(void *, int, int);
extern void func_314008(void *);
void func_L12_00388090(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        func_3248E0(a0, 1, -1);
        break;
    case 1:
        if (func_326C70(a0, 0x04010000, 0) != 0 && *(int *)s1 == 0) {
            func_3248E0(a0, 2, -1);
            func_00364DF8(0, 0, a0);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_333240(a0, &D_L12_001AEC50, &D_L12_001AEC48, &D_L12_001AEC40, 0xFFFF, 0, D_L12_001AEC70, 0,
                    0xFFFF, 0xFF, 0);
        func_00329F80(a0, 0x1308, 0);
        func_314008(a0);
        break;
    }
}
