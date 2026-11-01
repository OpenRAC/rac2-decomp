#include "include_asm.h"

#include "common.h"
extern u8 *D_L09_001B285C_1;
extern u16 *D_L09_001FB560[];
extern int func_002A77E0(int a);
extern int func_002A7820(int a, int b);
extern void func_002AEC18(char *a0, int a1);
extern float func_00283B98(float a, float b);
extern float func_00283180(float a);
extern float func_00283198(float a);
extern int func_00283CF0(float a);
extern void func_00282F20(float f12, void *a0, void *a1);
extern int D_L09_001B15B8 __attribute__((sda));
extern int D_L09_001B15B8_4[] MACRO_ADDR;
extern float D_L09_001B15C4 __attribute__((sda));
extern float D_L09_001B15C0 __attribute__((sda));
extern int D_L09_001B15B4 __attribute__((sda));
extern u8 D_L09_001B15B0 __attribute__((sda));
extern u8 D_0019B4A8[];
extern u8 D_0019B278[];
extern u8 D_001A7A28[] __attribute__((sda));

void func_PAL_L09_00410200(char *a0) {
    char *s3 = *(char **)(a0 + 0x68);
    char *s1;
    float v[3];
    int n;
    float count;
    int sel;
    if (func_002A77E0(7)) {
        sel = D_L09_001B15B8;
    } else {
        sel = D_L09_001B15B8_4[1];
    }
    func_002AEC18(a0, sel);
    s1 = a0 + 0xC0;
    *(float *)(s3 + 0x10) = func_00283B98(*(float *)(s3 + 0x10), D_L09_001B15C4 * 0.0003490659f);
    v[0] = func_00283180(*(float *)(s3 + 0x10)) * D_L09_001B15C0;
    v[1] = func_00283198(*(float *)(s3 + 0x10)) * D_L09_001B15C0;
    v[2] = 0;
    count = (float)D_L09_001B15B4;
    *(float *)(a0 + 0xF0) = v[0];
    *(float *)(a0 + 0xF4) = v[1];
    n = func_00283CF0(count * (*(float *)s3 + *(float *)(s3 + 4)) * 0.5f);
    *(u8 *)(a0 + 0x23) = D_L09_001B15B0 + n + func_002A7820(-9, 9);
    *(u16 *)(a0 + 0x34) |= 0x800;
    func_002833F0(s1, a0 + 0xF0);
    func_00282F20(*(float *)s3, s1, s1);
    func_00282F20(*(float *)(s3 + 4), a0 + 0xD0, a0 + 0xD0);
}
