#include "include_asm.h"
#include "common.h"

extern char D_00189E20_9[];
extern unsigned char g_pal_enable_flag MACRO_ADDR;
extern void func_00282C88_1(float *buf);
extern float FastVecLength(float *buf);

/* func_PAL_00328438, the PAL copy of func_00326CB8: the same C, where the first value is negated
   only when the byte D_PAL_001A7ACC is zero. */
void pad_clamp_stick_to_vars_pal(char *object)
{
    float buf[2];
    char *hero_a;
    char *hero_b;
    char *data = *(char **)(object + 104);

    if (g_pal_enable_flag != 0) {
        hero_a = D_00189E20_9;
        *(float *)(data + 20) = *(float *)(hero_a + 8112);
    } else {
        hero_a = D_00189E20_9;
        *(float *)(data + 20) = -*(float *)(hero_a + 8112);
    }
    hero_b = D_00189E20_9;
    *(float *)(data + 16) = -*(float *)(hero_b + 8116);

    if (*(float *)(data + 20) > 1.0f) {
        *(float *)(data + 20) = 1.0f;
    } else if (*(float *)(data + 20) < -1.0f) {
        *(float *)(data + 20) = -1.0f;
    }

    if (*(float *)(data + 16) > 1.0f) {
        *(float *)(data + 16) = 1.0f;
    } else if (*(float *)(data + 16) < -1.0f) {
        *(float *)(data + 16) = -1.0f;
    }
    func_00282C88_1(buf);
    buf[0] = *(float *)(data + 16);
    buf[1] = *(float *)(data + 20);
    *(float *)(data + 48) = FastVecLength(buf);
}
