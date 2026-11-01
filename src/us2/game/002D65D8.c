#include "include_asm.h"

extern char D_001F2840[];
extern int D_00138344;
extern int D_001A79F0 __attribute__((sda));
extern volatile unsigned char D_001A7C01 __attribute__((sda));
extern int D_001C51D0;
extern int D_001C4FA0[];
extern void func_0027D330(int);
extern void func_002C9C60(float);
extern int func_002E5E58(int, unsigned int, void *);
extern int func_0026F7D8(void);
extern int func_0026F7D8(void);
extern void func_00288CB0(int, int);
extern void func_002B49E0(int, int, int, int, int);
extern int func_US2_0029D248(int);
extern int func_0026F7D0(void);

extern int ref_US2_002D65D8_00(void);
extern int ref_US2_002D65D8_01(void);

int func_US2_002D65D8(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        char *root;
        int value;
        func_0027D330(4);
        func_002C9C60(4.0f);
        root = D_001F2840;
        value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                result = -1;
                goto finish;
            default:
                break;
            }
        }
        result = 0;
    } else if (flags & 0xD00) {
        result = 1;
        D_001C51D0 = D_001A79F0;
    } else if (flags & 0x40) {
        int *base = D_001C4FA0;
        if (D_001A79F0 != base[0x230 / 4]) {
            result = 1;
            func_002E5E58(4, 0, 0);
            if (base[0x230 / 4] != 0 && D_001A7C01 == 0 && base[0x230 / 4] == 2) {
                func_002B49E0(6, 2, 1, 0x19, 0);
            } else if (ref_US2_002D65D8_00() && ref_US2_002D65D8_01()) {
                func_00288CB0(D_001C4FA0[0x230 / 4], 1);
            } else {
                func_002B49E0(6, 2, 1, D_001C4FA0[0x230 / 4], 0);
            }
        } else {
            result = 1;
            func_002E5E58(4, 0, 0);
            func_0027D330(4);
        }
    } else {
        func_US2_0029D248(flags);
    }
finish:
    return result;
}



