#include "include_asm.h"

#include "common.h"
extern u8 *D_L09_001B285C_1;
extern u16 *D_L09_001FB560[];
extern int math_random_int_below(int a);
extern int math_random_int_range(int a, int b);
extern void moby_set_light_color(char *a0, int a1);
extern float FastAddRotations(float a, float b);
extern float math_fast_sin_or_cos_a(float a);
extern float math_fast_sin_or_cos_b(float a);
extern int FloatToInt(float a);
extern void vec_scale_to_length(float f12, void *a0, void *a1);
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
    if (math_random_int_below(7)) {
        sel = D_L09_001B15B8;
    } else {
        sel = D_L09_001B15B8_4[1];
    }
    moby_set_light_color(a0, sel);
    s1 = a0 + 0xC0;
    *(float *)(s3 + 0x10) = FastAddRotations(*(float *)(s3 + 0x10), D_L09_001B15C4 * 0.0003490659f);
    v[0] = math_fast_sin_or_cos_a(*(float *)(s3 + 0x10)) * D_L09_001B15C0;
    v[1] = math_fast_sin_or_cos_b(*(float *)(s3 + 0x10)) * D_L09_001B15C0;
    v[2] = 0;
    count = (float)D_L09_001B15B4;
    *(float *)(a0 + 0xF0) = v[0];
    *(float *)(a0 + 0xF4) = v[1];
    n = FloatToInt(count * (*(float *)s3 + *(float *)(s3 + 4)) * 0.5f);
    *(u8 *)(a0 + 0x23) = D_L09_001B15B0 + n + math_random_int_range(-9, 9);
    *(u16 *)(a0 + 0x34) |= 0x800;
    euler_rotation_basis(s1, a0 + 0xF0);
    vec_scale_to_length(*(float *)s3, s1, s1);
    vec_scale_to_length(*(float *)(s3 + 4), a0 + 0xD0, a0 + 0xD0);
}
