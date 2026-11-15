#include "common.h"

extern s32 coll_test_point_against_shapes(void *, s32, s32, s32, s32);
extern s32 func_001163B0(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern char *D_L08_001B29DC[] MACRO_ADDR;
extern char g_hero_position[];

/* A swinging camera target: unless it is still easing in, it either holds its rest
   point, follows the hero, or jumps to a random point on its anchor's ring. */
void UpdateTaboraSwingTarget(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    char *target = vars + 0x180;
    float lo, hi, r;
    float c;
    char *anchor;

    if (coll_test_point_against_shapes(target, *(s32 *)(vars + 0x1D8), *(s32 *)(vars + 0x1E0),
                          *(s32 *)(vars + 0x1DC), -1) != 0)
        return;
    if ((func_001163B0() & 1) || *(s32 *)(vars + 0x164) == 2 || *(s16 *)(vars + 0x1B6) != 0) {
        if (*(s32 *)(vars + 0x1E8) == -1 || (func_001163B0() & 1)) {
            qcopy(vars + 0x180, vars + 0x170);
        } else {
            lo = -3.1415927f;
            hi = 3.1415927f;
            r = 3.0f;
            *(float *)(vars + 0x180) = math_fast_sin_or_cos_a(math_random_float_range(lo, hi)) * r;
            c = math_fast_sin_or_cos_b(math_random_float_range(lo, hi));
            anchor = D_L08_001B29DC[0] + (*(s32 *)(vars + 0x1E8) << 8) + 0x10;
            *(float *)(vars + 0x184) = c * r;
            *(float *)(vars + 0x188) = 0.0f;
            FastVecAdd(vars + 0x180, vars + 0x180, anchor);
        }
    } else {
        qcopy(target, g_hero_position);
    }
    *(float *)(vars + 0x188) += 6.5f;
}
