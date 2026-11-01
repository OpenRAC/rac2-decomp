#include "include_asm.h"

extern float D_L02_001B1FC4 __attribute__((sda));
extern void func_00282F20(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283BE0(float, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L02_00422638(int);

/* Rebuilds the record's second frame and folds the resident angle step in. */
void func_PAL_L02_004275E8(char *s2) {
    float buf[4];
    char *s0 = *(char **)(s2 + 0x68);
    char *s3 = s2 + 0x10;
    char *s1 = s0 + 0x10;

    func_00282F20(buf, s0 + 0x40, 1.0f);
    func_002AB668(buf, buf, *(float *)(s0 + 0x30));
    func_00282D30(s1, s0, *(float *)(s0 + 0x60));
    func_002ACDE8(s1, s1, buf);
    *(float *)(s0 + 0x20) = -*(float *)(s0 + 0x10);
    *(float *)(s0 + 0x24) = -*(float *)(s0 + 0x14);
    *(float *)(s0 + 0x28) = -*(float *)(s0 + 0x18);
    func_00282CC0(s1, s3, s1);
    func_00282CC0(s0 + 0x20, s3, s0 + 0x20);
    *(float *)(s0 + 0x30) =
        func_00283BE0(*(float *)(s0 + 0x30), D_L02_001B1FC4 * 0.0003490659f);
    func_L00_002E6CF0(func_L02_00422638, s2);
}
