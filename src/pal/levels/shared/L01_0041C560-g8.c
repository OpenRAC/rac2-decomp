#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_00282CC0(void *, void *, void *);
extern float D_L01_001B1A9C __attribute__((sda));
extern float D_L01_001B1AA0 __attribute__((sda));
extern float D_L01_001B1AA4 __attribute__((sda));
extern float D_L01_001B1AA8 __attribute__((sda));
extern unsigned char D_L01_001B1AAC __attribute__((sda));
extern int D_L01_001B1AB0 __attribute__((sda));
extern int D_L01_001B1AB4 __attribute__((sda));
extern float D_L01_001B1AB8 __attribute__((sda));
extern float D_L01_001B1ABC __attribute__((sda));
extern void func_00282D30(void *, void *, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7A00(void *, float, float);
extern int func_002A77E0(int);
extern void func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_0029FCC0(void *, int, void *);

/* builds the tilt of a hanging chain over three steps and draws it */
void func_PAL_L01_0041C560(char *a0)
{
    TI128 m, v1, v2;
    int i;
    int b;

    if (*(unsigned char *)(a0 + 0x20) == 1) {
        func_00282D30(&m, a0, 0.0009765625f);
    } else {
        func_0029FCC0(a0, 0, &m);
    }
    i = 2;
    func_002A7A00(&v1, D_L01_001B1A9C * 0.020000001f, D_L01_001B1AA0 * 0.020000001f);
    b = D_L01_001B1AAC;
    func_002C3150(&m, &v1, D_L01_001B1AB0, b, func_002A77E0(255), 0, D_L01_001B1AB8);
    do {
        i--;
        func_002A7A00(&v2, D_L01_001B1AA4 * 0.020000001f, D_L01_001B1AA8 * 0.020000001f);
        func_00282CC0(&v1, &v1, &v2);
        b = D_L01_001B1AAC;
        func_002C3150(&m, &v1, D_L01_001B1AB4, b, func_002A77E0(255), 0, D_L01_001B1ABC);
    } while (i >= 0);
}
