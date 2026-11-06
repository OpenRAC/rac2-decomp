/* func_PAL_L02_003C91F0, the PAL copy of func_L02_003C5438: the same C, where scale (u32)a3; wrap (u32)a1 (((int)({e}) * 5 + 2) / 6). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void *func_002C2210(void *, u32, u32, f32, f32, u32, s32, void *, f32, s32);
extern char D_L02_001A8F20[] __attribute__((sda));

/* Spawn one particle and, when both secondary parameters are set, its opposite. */
void func_PAL_L02_003C91F0(void *a0, void *a1, void *a2, void *a3, void *a4)
{
    TI128 v;
    float f20;
    float f21 = 0.0f;
    int s2;

    v = *(TI128 *)a0;
    f20 = func_002A7878(2.0f, 4.0f);
    s2 = func_002A77E0(2);
    if (s2 == 0)
        s2--;
    func_002C2210(&v, (((int)((u32)a1) * 5 + 2) / 6), (u32)a2, f20 * 0.3f, f20, 0, s2, D_L02_001A8F20, f21, 0);
    if (a3 != 0 && a4 != 0)
        func_002C2210(&v, (((int)((u32)a3) * 5 + 2) / 6), (u32)a4, f20 * 0.04f, f20 * 0.4f, 1, -s2, D_L02_001A8F20, f21, 0);
}
