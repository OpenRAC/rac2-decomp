#include "include_asm.h"

#include "common.h"
extern void func_00282F20(char *a0, void *a1, float f12);
extern void func_002AB668(void *a0, void *a1, float f12);
extern void func_00282D30(char *a0, void *a1, float f12);
extern void func_002ACDE8(void *a0, void *a1, void *a2);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern float func_00283BE0(float a, float b);
extern void func_L00_002E6CF0(void *a0, void *a1);
extern void func_L11_00459E48(char *p);
extern float D_L11_001B1FFC __attribute__((sda));

/* Rebuilds the state's offset block from its rotation and installs the next handler. */
void func_PAL_L11_0045F9F8(char *p)
{
    char *q = *(char **)(p + 0x68);
    float v[4];

    func_00282F20((char *)v, q + 0x40, 1.0f);
    func_002AB668(v, v, *(float *)(q + 0x30));
    func_00282D30(q + 0x10, q, *(float *)(q + 0x60));
    func_002ACDE8(q + 0x10, q + 0x10, v);
    *(float *)(q + 0x20) = -*(float *)(q + 0x10);
    *(float *)(q + 0x24) = -*(float *)(q + 0x14);
    *(float *)(q + 0x28) = -*(float *)(q + 0x18);
    func_00282CC0(q + 0x10, p + 0x10, q + 0x10);
    func_00282CC0(q + 0x20, p + 0x10, q + 0x20);
    *(float *)(q + 0x30) = func_00283BE0(*(float *)(q + 0x30),
                                         D_L11_001B1FFC * 0.0003490659f);
    func_L00_002E6CF0(func_L11_00459E48, p);
}
