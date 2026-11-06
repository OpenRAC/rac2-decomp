#include "include_asm.h"

/* func_PAL_L00_003BADA0, the PAL copy of func_L00_003B72B0: the same C, where 1.0f / 60.0f becomes 0.020000001f and both
   func_002A7820 results are scaled to 50 Hz. The loop's result has a local of its own, so it stays in one block. */

extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002A7A00(float *, float, float);
extern void func_00282CC0(float *, float *, float *);
extern void func_00283098(float *, float *, void *);
extern void *func_002C3150(void *, void *, int, int, int, int, float);
extern float D_L00_001AFAE8 __attribute__((sda));
extern float D_L00_001AFAEC;
extern float D_L00_001AFAF8 __attribute__((sda));
extern float D_L00_001AFAFC;
extern int D_L00_001AFB00 __attribute__((sda));
extern int D_L00_001AFB04;
extern int D_L00_001AFB08 __attribute__((sda));
extern int D_L00_001AFB0C[] __attribute__((sda));
extern int D_L00_001AFB18 __attribute__((sda));
extern float D_L00_001AFB20[4] __attribute__((sda));
extern char D_L00_001B8DC0[];
extern float D_L00_001A8F20[4];

void func_PAL_L00_003BADA0(void)
{
    float point[4], velocity[4], scatter[4];
    int i = 0;
    unsigned char kind, kind2, random;
    func_00283098(point, D_L00_001AFB20, D_L00_001B8DC0 + 0x230);
    func_00282CC0(point, point, (float *)D_L00_001B8DC0);
    kind = ((int)func_002A7820(D_L00_001AFB08, D_L00_001AFB0C[0]) * 5 + 2) / 6;
    random = func_002A77E0(255);
    func_002C3150(point, D_L00_001A8F20, D_L00_001AFB00, kind, random, 0, D_L00_001AFAF8);
    func_002A7A00(velocity, D_L00_001AFAE8 * 0.020000001f, D_L00_001AFAEC * 0.020000001f);
    while (i < D_L00_001AFB18) {
        i++;
        func_002A7A00(scatter, 0.0f, 0.25f);
        func_00282CC0(scatter, scatter, point);
        kind2 = ((int)func_002A7820(D_L00_001AFB0C[1], D_L00_001AFB0C[2]) * 5 + 2) / 6;
        random = func_002A77E0(255);
        func_002C3150(scatter, velocity, D_L00_001AFB04, kind2, random, 0, D_L00_001AFAFC);
    }
}
