#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7A00(void *, float, float);
extern int func_002A77E0(int);
extern void func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);
extern void func_00282CC0(void *, void *, void *);
extern float D_00189F08 __attribute__((nosda));
extern float ref_L01_00397EB0_00 __attribute__((sda));
extern float ref_L01_00397EB0_01 __attribute__((sda));
extern unsigned char ref_L01_00397EB0_02 __attribute__((sda));
extern int ref_L01_00397EB0_03 __attribute__((sda));
extern float ref_L01_00397EB0_04 __attribute__((sda));
extern float ref_L01_00397EB0_05 __attribute__((sda));
extern float ref_L01_00397EB0_06 __attribute__((sda));
extern int ref_L01_00397EB0_07 __attribute__((sda));
extern float ref_L01_00397EB0_08 __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);
extern void func_0029FCC0(void *, int, void *);

void func_PAL_L01_0039B2D0(char *a0)
{
    TI128 m, v1, v2;
    int i;
    int b;

    if (*(unsigned char *)(a0 + 0x20) == 1) {
        func_00282D30(&m, a0, 0.0009765625f);
    } else {
        func_0029FCC0(a0, 0, &m);
        if (((float *)&m)[2] < D_00189F08) return;
    }
    i = 2;
    func_002A7A00(&v1, ref_L01_00397EB0_00 * 0.020000001f, ref_L01_00397EB0_01 * 0.020000001f);
    b = ref_L01_00397EB0_02;
    func_002C3150(&m, &v1, ref_L01_00397EB0_03, b, func_002A77E0(255), 0, ref_L01_00397EB0_04);
    do {
        i--;
        func_002A7A00(&v2, ref_L01_00397EB0_05 * 0.020000001f, ref_L01_00397EB0_06 * 0.020000001f);
        func_00282CC0(&v1, &v1, &v2);
        b = ref_L01_00397EB0_02;
        func_002C3150(&m, &v1, ref_L01_00397EB0_07, b, func_002A77E0(255), 0, ref_L01_00397EB0_08);
    } while (i >= 0);
}
