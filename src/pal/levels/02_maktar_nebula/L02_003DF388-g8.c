#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern float D_L02_001B04B0 __attribute__((sda));
extern float D_L02_001B04C8 __attribute__((sda));
extern float D_L02_001B04CC __attribute__((sda));
extern float D_L02_001B04D0 __attribute__((sda));
extern float D_L02_001B04D4 __attribute__((sda));
extern float D_L02_001B04D8 __attribute__((sda));
extern int D_L02_001B359C;
extern float D_L02_001BA500[4];
extern void *func_0029FCC0(char *, int, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_L02_003449D8(void *, void *, void *, int, int);

void func_PAL_L02_003DF388(char *arg0) {
    float a[4];
    float b[4];
    float c[4];

    *(TI128 *)a = 0;
    func_0029FCC0((char *)(D_L02_001B359C + (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)), 4, b);
    b[2] = b[2] + D_L02_001B04D4;
    func_00282CF0(c, D_L02_001BA500, b);
    c[2] = 0.0f;
    func_00282F20(c, c, D_L02_001B04D8);
    func_00282CC0(b, b, c);
    func_002ACB48(b, D_L02_001B04C8);
    a[2] = func_002A7878(D_L02_001B04CC, D_L02_001B04D0) * 0.020000001f;
    func_L02_003449D8(b, a, &D_L02_001B04B0, func_002A77E0(2), 1);
}
