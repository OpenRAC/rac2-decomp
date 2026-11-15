#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern char * CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern void func_PAL_L00_00401080(void *);

void *func_PAL_L00_00400968(char *a0, char *a1, TI128 *a2, char *a3)
{
    char *o = CreateMoby(0xD5E);

    if (o != 0) {
        char *s0 = *(char **)(o + 0x68);
        float tmp[4];

        *(unsigned char *)(o + 0x30) = 0xFF;
        *(unsigned short *)(o + 0x32) = 0xFF;
        *(unsigned char *)(o + 0x31) = 1;
        *(unsigned char *)(o + 0x20) = 0;
        *(unsigned short *)(o + 0x34) |= 0x41;
        vec_scale_to_length(s0 + 0x20, a1, 0.16000001f);
        *(TI128 *)(o + 0x10) = *a2;
        vec_scale_to_length(tmp, s0 + 0x20, -1.5f);
        FastVecAdd(s0 + 0x50, a0, tmp);
        *(int *)(s0 + 0x38) = 0x11;
        *(float *)(s0 + 0x3C) = 1.0f / IntToFloat(0x11);
        *(char **)(s0 + 0x34) = a3;
        func_PAL_L00_00401080(o + 0x10);
    }
    return o;
}
