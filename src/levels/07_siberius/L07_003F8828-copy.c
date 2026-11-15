#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);

void func_L07_003F8828(u8 *a0, u8 *a1)
{
    u8 *s1 = *(u8 **)(a0 + 0x68);

    if (*(u8 *)(a0 + 0x95) == 0) {
        u8 *s0 = s1 + 0x400;

        FastVecSub(s0, a1, *(u8 **)(s1 + 0x418) + 0x10);
        func_002AFDD8(*(u8 **)(s1 + 0x418), s0, s0, 0);
        return;
    }
    qcopy(s1 + 0x400, a1);
}
