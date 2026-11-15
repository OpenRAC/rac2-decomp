#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);

/* Gets the world positions of the two ends of the beam, following its support object if it has one. */
void func_L07_003F4C18(u8 *moby, u8 *start, u8 *end)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 **)(vars + 0x20) != 0) {
        matrix_mul_vec3(start, vars, *(u8 **)(vars + 0x20) + 0xC0);
        FastVecAdd(start, start, *(u8 **)(vars + 0x20) + 0x10);
        matrix_mul_vec3(end, vars + 0x10, *(u8 **)(vars + 0x20) + 0xC0);
        FastVecAdd(end, end, *(u8 **)(vars + 0x20) + 0x10);
        return;
    }
    qcopy(start, vars);
    qcopy(end, vars + 0x10);
}
