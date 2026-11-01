#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L26_0040C130);

#include "common.h"
typedef struct {
    int a;
    float b;
    int c;
    int d;
} Quad_L26_0040C8A8;
extern void func_PAL_002B4D38(char *, char *, char *, char *, char *, char *, char *, char *,
                          char *, char *, char *);
extern void func_002A7750(char *, int, int);
extern void func_PAL_002B5050(char *, char *, int);

void func_PAL_L26_00411C98(char *a0) {
    char *s1 = a0;
    char *s0 = *(char **)(s1 + 0x68);
    Quad_L26_0040C8A8 v;

    switch (*(u8 *)(s1 + 0x20)) {
    case 0:
        qzero_nc(&v);
        if (*(int *)(s0 + 0x120) != 0)
            v.b = (float)*(int *)(s0 + 0x120) * 1.7f;
        func_PAL_002B4D38(s1, s0 + 0x60, (char *)&v, 0, 0, 0, 0, 0, 0, 0, 0);
        if (*(int *)(s0 + 0x120) != 0) {
            *(int *)(s0 + 0xD0) = 0;
            *(int *)(s0 + 0x100) = 0;
            *(int *)(s0 + 0xD4) = 0;
        }
        func_002A7750(s1, 1, -1);
        break;
    case 1:
        func_PAL_002B5050(s1, s0 + 0x60, 0);
        break;
    }
}


