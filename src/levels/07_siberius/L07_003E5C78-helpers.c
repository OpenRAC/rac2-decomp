#include "common.h"

extern void func_002A7750(unsigned char *, int, int);

extern void func_00282CF0(void *, void *, void *);

extern void func_002AFDD8(char *, char *, char *, char *);

extern void func_00282F20(void *, void *, float);

void func_L07_003E5C78(char *arg, char *a1, char *a2, char *a3)
{
    char *s0;
    unsigned short v;
    int i;

    if (*(unsigned char *)(arg + 0x20) != 8)
        return;

    s0 = *(char **)(arg + 0x68);
    *(unsigned short *)(arg + 0x34) = (*(unsigned short *)(arg + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(arg + 0x98) = 0;
    func_002A7750((unsigned char *)arg, 9, 4);

    qcopy(arg + 0x10, a1);
    qcopy(s0 + 0x230, a2);
    *(int *)(s0 + 0x260) = (int)a3;
    *(unsigned char *)(arg + 0x7F) = 0;

    if (a3 != 0) {
        FastVecSub(s0 + 0x220, a2, a3 + 0x10);
        func_002AFDD8(a3, s0 + 0x220, s0 + 0x220, 0);
    }
    v = *(unsigned short *)(arg + 0x34);
    s0 = arg + 0xC0;
    i = 2;
    *(unsigned short *)(arg + 0x34) = v | 0x100;
    do {
        vec_scale_to_length(s0, s0, 0.1f);
        s0 += 0x10;
        i--;
    } while (i >= 0);
}
