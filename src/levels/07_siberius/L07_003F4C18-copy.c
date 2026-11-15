#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);

void func_L07_003F4C18(u8 *a0, u8 *a1, u8 *a2)
{
    u8 *s0 = *(u8 **)(a0 + 0x68);

    if (*(u8 **)(s0 + 0x20) != 0) {
        matrix_mul_vec3(a1, s0, *(u8 **)(s0 + 0x20) + 0xC0);
        FastVecAdd(a1, a1, *(u8 **)(s0 + 0x20) + 0x10);
        matrix_mul_vec3(a2, s0 + 0x10, *(u8 **)(s0 + 0x20) + 0xC0);
        FastVecAdd(a2, a2, *(u8 **)(s0 + 0x20) + 0x10);
        return;
    }
    qcopy(a1, s0);
    qcopy(a2, s0 + 0x10);
}
