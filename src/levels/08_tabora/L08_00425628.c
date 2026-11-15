#include "common.h"

extern s32 func_L01_003165E8(void *, s32, s32, s32, s32);
extern s32 func_001163B0(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern char *D_L08_001B29DC[] MACRO_ADDR;
extern char D_00189EA0[];

/* A swinging camera target: unless it is still easing in, it either holds its rest
   point, follows the hero, or jumps to a random point on its anchor's ring. */
void func_L08_00425628(char *obj)
{
    char *s0 = *(char **)(obj + 0x68);
    char *s1 = s0 + 0x180;
    float lo, hi, r;
    float c;
    char *anchor;

    if (func_L01_003165E8(s1, *(s32 *)(s0 + 0x1D8), *(s32 *)(s0 + 0x1E0),
                          *(s32 *)(s0 + 0x1DC), -1) != 0)
        return;
    if ((func_001163B0() & 1) || *(s32 *)(s0 + 0x164) == 2 || *(s16 *)(s0 + 0x1B6) != 0) {
        if (*(s32 *)(s0 + 0x1E8) == -1 || (func_001163B0() & 1)) {
            qcopy(s0 + 0x180, s0 + 0x170);
        } else {
            lo = -3.1415927f;
            hi = 3.1415927f;
            r = 3.0f;
            *(float *)(s0 + 0x180) = func_00283180(func_002A7878(lo, hi)) * r;
            c = func_00283198(func_002A7878(lo, hi));
            anchor = D_L08_001B29DC[0] + (*(s32 *)(s0 + 0x1E8) << 8) + 0x10;
            *(float *)(s0 + 0x184) = c * r;
            *(float *)(s0 + 0x188) = 0.0f;
            FastVecAdd(s0 + 0x180, s0 + 0x180, anchor);
        }
    } else {
        qcopy(s1, D_00189EA0);
    }
    *(float *)(s0 + 0x188) += 6.5f;
}
