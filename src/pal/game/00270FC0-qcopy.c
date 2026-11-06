#include "include_asm.h"


typedef int TI128 __attribute__((mode(TI)));

extern char D_00189F70[];
extern char D_001B5340[];

extern void func_00282CC0(void *, void *, void *);
extern void func_00283810(void *, void *, void *, float);
extern void func_002839D0(void *, void *);
extern void func_00283678(void *, void *);
extern void func_002AB600(void *, void *);
extern float func_002A7C00(float, float, float);

/* func_PAL_00270FC0, the PAL copy of func_00271130: the same C, where both
   weight rates are scaled by 1.2f for 50 Hz. */
/* Advances the two blend weights of a transition and refreshes its eased
   position; returns 1 when both are already complete. */
int func_PAL_00270FC0(char *a0, char *a1)
{
    float *w = (float *)a1;
    float t, e;
    float x, y, z;
    struct { TI128 vec; TI128 mat[4]; } f;

    if (w[3] == 1.0f && w[0] == 1.0f)
        return 1;
    t = func_002A7C00(0.0f, 1.0f, w[3]);
    func_00282CC0(a1 + 0x30, D_00189F70, a1 + 0x30);
    x = *(float *)(a1 + 0x30);
    y = *(float *)(a1 + 0x34);
    z = *(float *)(a1 + 0x38);
    *(float *)(a1 + 0x40) = x + (*(float *)(a0 + 0x30) - x) * t;
    *(float *)(a1 + 0x44) = y + (*(float *)(a0 + 0x34) - y) * t;
    *(float *)(a1 + 0x48) = z + (*(float *)(a0 + 0x38) - z) * t;
    *(TI128 *)D_001B5340 = *(TI128 *)(a1 + 0x40);
    func_002AB600(&f.vec, a0);
    e = func_002A7C00(0.0f, 1.0f, w[0]);
    func_00283810(a1 + 0x50, a1 + 0x20, &f.vec, e);
    func_002839D0(a1 + 0x50, f.mat);
    func_00283678(D_001B5340 + 0x230, f.mat);
    w[3] = w[3] + w[4] * 1.2f;
    if (w[3] > 1.0f)
        w[3] = 1.0f;
    w[0] = w[0] + w[1] * 1.2f;
    if (w[0] > 1.0f)
        w[0] = 1.0f;
    return 0;
}
