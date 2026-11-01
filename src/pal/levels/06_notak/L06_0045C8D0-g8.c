#include "include_asm.h"

#include "common.h"
extern u8 *D_L06_001FB3A0[];
extern float D_L06_001B18D0 __attribute__((sda));
extern float D_L06_001B18D4;
extern float D_L06_001B18D8;
extern float func_00283B98(float, float);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern void func_L03_0042B868(u8 *, void *, void *);

/* Turns the owner's three angles by the level's step, then walks the owner's eight records:
   each gets a fresh object, scaled and blended against the owner's own axes. `axes` is the
   scratch area func_002833F0 fills; its first vector is the one the objects are given. */
void func_PAL_L06_0045C8D0(char *a0)
{
    float axes[12];
    float v0[4];
    float v1[4];
    char *s0 = *(char **)(a0 + 0x68);
    char *s3 = s0 + 0xA0;
    char *s2 = s0 + 0x80;
    char *s4 = a0 + 0x10;
    float step = 0.0003490659f;
    float one = 1.0f;
    float two = 2.0f;
    int i;

    *(float *)(s0 + 0x120) = func_00283B98(*(float *)(s0 + 0x120), D_L06_001B18D0 * step);
    *(float *)(s0 + 0x124) = func_00283B98(*(float *)(s0 + 0x124), D_L06_001B18D4 * step);
    *(float *)(s0 + 0x128) = func_00283B98(*(float *)(s0 + 0x128), D_L06_001B18D8 * step);
    func_002833F0(axes, s0 + 0x120);
    for (i = 7; i >= 0; i--) {
        func_00283098(v0, s3, axes);
        s3 += 0x10;
        func_00282D30((char *)v0, (char *)v0, 3.0f);
        func_00282D30((char *)v1, (char *)v0, 3.3333335f);
        func_00282CC0((char *)v0, (char *)v0, s4);
        func_00282CC0((char *)v1, (char *)v1, s4);
        v0[3] = one;
        v1[3] = two;
        func_L03_0042B868(*(u8 **)s2, v0, v1);
        s2 += 4;
    }
}
