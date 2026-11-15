#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);

/* Turns the stored position into one relative to the parent part, or copies it directly when there is no parent. */
void func_L07_003F8898(u8 *moby, u8 *outPos)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 *)(moby + 0x95) == 0) {
        matrix_mul_vec3(outPos, vars + 0x400, *(u8 **)(vars + 0x418) + 0xC0);
        FastVecAdd(outPos, outPos, *(u8 **)(vars + 0x418) + 0x10);
        return;
    }
    qcopy(outPos, vars + 0x400);
}
