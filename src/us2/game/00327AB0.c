#include "include_asm.h"
#include "common.h"

/* func_US2_00327AB0, the USA v2.00 copy of func_00326CB8: the same C, where the
   first axis is negated only while the byte D_US2_001A7A4C is clear. */

extern char D_00189E20_9[];
extern unsigned char g_level_status_byte MACRO_ADDR;
extern void func_00282C88_1(float *stick);
extern float FastVecLength(float *stick);

/* Reads the pad stick, negates and clamps it to the unit range and stores the result and its length in the object's state (v2.00 copy). */
void pad_clamp_stick_to_vars_us2(char *moby)
{
    float stick[2];
    char *vars = *(char **)(moby + 104);
    float stick_x, stick_y, clamped_y;

    if (g_level_status_byte != 0) {
        char *hero = D_00189E20_9;
        *(float *)(vars + 20) = *(float *)(hero + 8112);
    } else {
        char *hero = D_00189E20_9;
        *(float *)(vars + 20) = -*(float *)(hero + 8112);
    }
    {
        char *hero = D_00189E20_9;
        stick_x = *(float *)(vars + 20);
        stick_y = -*(float *)(hero + 8116);
    }
    *(float *)(vars + 16) = stick_y;

    if (stick_x > 1.0f) {
        *(float *)(vars + 20) = 1.0f;
    } else if (stick_x < -1.0f) {
        *(float *)(vars + 20) = -1.0f;
    }

    clamped_y = *(float *)(vars + 16);
    if (clamped_y > 1.0f) {
        *(float *)(vars + 16) = 1.0f;
    } else if (clamped_y < -1.0f) {
        *(float *)(vars + 16) = -1.0f;
    }
    func_00282C88_1(stick);
    stick[0] = *(float *)(vars + 16);
    stick[1] = *(float *)(vars + 20);
    *(float *)(vars + 48) = FastVecLength(stick);
}
