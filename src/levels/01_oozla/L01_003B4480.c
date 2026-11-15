/* func_L01_003B4480 in its own unit: it copies 128 bits, and the retail's copy keeps
   both addresses in registers, which is the compiler's opt-in grouped copy
   (-frac2-qcopy, config/cflags.txt). The flag changes every TImode copy in a unit,
   so the unit holds this function alone. */

#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int V4 __attribute__((mode(TI)));

extern float func_002A89A8(void *a0, int a1, float f12);
extern int func_00278E78(void);
extern void func_002ACB48(float *v, float f);
extern float func_L01_003BAFB0(void);
extern float func_002A7878(float a, float b);
extern int func_002A77E0(int a);
extern void func_002C19D8(char *a0, int a1, int a2, float f12, float f13);
extern float func_00282DF0(void *a0);
extern void func_L01_003B4200(void *a0, int a1, int a2, int a3);

/* The float the second argument of func_002C19D8 points at. */
extern f32 D_L01_001AFE18[];

void func_L01_003B4480(u8 *arg0)
{
    u8 *state = *(u8 **)(arg0 + 0x68);
    float v[4];
    float f;
    int i;

    func_002A89A8(arg0 + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() != 3)
        return;
    {
        u8 *p = arg0 + 0x10;
        u8 *q = state + 0xE0;
        i = 0;
        while (i >= 0) {
            *(V4 *)v = *(V4 *)p;
            func_002ACB48(v, 0.15f);
            v[2] = func_L01_003BAFB0();
            f = func_002A7878(0.3f, 2.5f);
            func_002C19D8((char *)v, (int)D_L01_001AFE18,
                          (int)((((u32)func_002A77E0(6) + 0x14) << 24) | 0x5060), f, 11000.0f);
            i--;
        }
        f = 0.0333333333f;
        if (f < FastVecLength(q) || f < FastVecLength(state + 0x2F0))
            func_L01_003B4200(arg0, 3, 10, 1);
    }
}
