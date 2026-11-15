#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);

void func_L07_003F8898(u8 *a0, u8 *a1)
{
    u8 *s0 = *(u8 **)(a0 + 0x68);

    if (*(u8 *)(a0 + 0x95) == 0) {
        matrix_mul_vec3(a1, s0 + 0x400, *(u8 **)(s0 + 0x418) + 0xC0);
        FastVecAdd(a1, a1, *(u8 **)(s0 + 0x418) + 0x10);
        return;
    }
    qcopy(a1, s0 + 0x400);
}
