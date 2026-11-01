#include "include_asm.h"

#include "common.h"
typedef int V4 __attribute__((mode(TI)));
extern float func_002A89A8(void *a0, int a1, float f12);
extern int func_00278E78(void);
extern void func_002ACB48(float *v, float f);
extern float func_PAL_L01_003BEB40(void);
extern float func_002A7878(float a, float b);
extern int func_002A77E0(int a);
extern void func_002C19D8(char *a0, int a1, int a2, float f12, float f13);
extern float func_00282DF0(void *a0);
extern f32 D_L01_001AFE18[];

/* Same body as func_L01_003B4480, with this function's own callees. */
void func_PAL_L01_003E05D0(u8 *arg0)
{
    u8 *state = *(u8 **)(arg0 + 0x68);
    float v[4];
    float f;
    int i;

    func_002A89A8(arg0 + 0x10, 0, 0.5f);
    if (func_00278E78() != 3)
        return;
    {
        u8 *p = arg0 + 0x10;
        u8 *q = state + 0x190;
        i = 0;
        while (i >= 0) {
            *(V4 *)v = *(V4 *)p;
            func_002ACB48(v, 0.1f);
            v[2] = func_PAL_L01_003BEB40();
            f = func_002A7878(0.2f, 2.0f);
            func_002C19D8((char *)v, (int)D_L01_001AFE18,
                          (int)((((u32)func_002A77E0(6) + 0x14) << 24) | 0x5060), f, 1.2e+04f);
            i--;
        }
        if (0.040000003f < func_00282DF0(q))
            func_PAL_L01_003E0350(arg0, 3, 10, 1);
    }
}
