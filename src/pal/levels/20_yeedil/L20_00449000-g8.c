#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float IntToFloat(int);
extern void hud_start_overlay(int, int, float);
extern void func_PAL_L20_004482C8(char *);
extern void func_PAL_L20_00448428(char *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern int math_fast_float_d(void *);
extern void *func_PAL_L20_004489E0(char *);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void euler_rotation_basis(char *, char *);
extern void FastVecSub(void *, void *, void *);
extern void moby_update_ground_check(void *);
extern void func_PAL_002B14F8(void *, float *, float, int, int);
extern float D_L20_001B20B0[] SDATA(D_L20_001B20B0);
extern float D_L20_001B2164 __attribute__((sda));

void func_PAL_L20_00449000(char *arg0) {
    char *s2 = arg0;
    char *s1 = *(char **)(arg0 + 0x68);
    char *p;
    char *dst;
    char *src;
    TI128 v0, v1, v2;
    float f;
    unsigned short n;

    if (*(unsigned char *)(arg0 + 0x95) != 6) {
        hud_start_overlay(0xA, 0,
                         *(float *)(s1 + 0x20)
                         / IntToFloat(*(short *)(s1 + 0x24)));
        func_PAL_L20_004482C8(arg0);
        func_PAL_L20_00448428(arg0);
    }
    moby_update_eased_node(arg0, s1 + 0x250, 0, 0.0216f, 0.43200004f);
    if (*(int *)(s1 + 0x1810) > 0) {
        if (math_fast_float_d(s1 + 0x1810) != 0) {
            func_PAL_L20_004489E0(arg0);
            *(int *)(s1 + 0x1810) = -1;
        }
    }
    p = *(char **)(s1 + 0x1850);
    if (p != 0) {
        if (*(short *)(p + 0xAA) != 0x1316) {
            *(int *)(s1 + 0x1850) = 0;
        } else {
            if (*(unsigned char *)(p + 0x20) != 0xFE) {
                if (*(unsigned char *)(p + 0x20) != 0xFD) {
                    goto copy;
                }
            }
            *(int *)(s1 + 0x1850) = 0;
        }
    }
copy:
    dst = s1 + 0x17E0;
    src = arg0 + 0x10;
    qcopy(dst, src);
    f = *(float *)(s1 + 0x1800);
    if (f == 0.0f && *(float *)(s1 + 0x1804) == 0.0f) {
        goto done;
    }
    *(float *)(arg0 + 0xF0) = f;
    *(float *)(arg0 + 0xF4) = *(float *)(s1 + 0x1804);
    matrix_mul_vec3(&v0, D_L20_001B20B0, arg0 + 0xC0);
    euler_rotation_basis(arg0 + 0xC0, arg0 + 0xF0);
    matrix_mul_vec3(&v1, D_L20_001B20B0, arg0 + 0xC0);
    FastVecSub(&v2, &v1, &v0);
    FastVecSub(src, src, &v2);
done:
    moby_update_ground_check(arg0);
    n = *(unsigned short *)(arg0 + 0x96);
    arg0[0xBD] = 2;
    if (n <= 0xFFFE) {
        *(unsigned short *)(arg0 + 0x96) = n + 1;
    }
    func_PAL_002B14F8(arg0, (float *)(s1 + 0x250), D_L20_001B2164, 0, 1);
}
