#include "include_asm.h"
#include "common.h"

/* func_US2_00330BE8, the USA v2.00 copy of func_0032FDD0: the same C, where the
   first axis is negated only while the byte D_US2_001A7A4C is clear, as in
   func_US2_00327AB0. */

extern char g_hero_state[];
extern unsigned char g_level_status_byte MACRO_ADDR;
extern void vec_clear_128(float *stick);
extern float FastVecLength(float *stick);
extern float g_stick_length MACRO_ADDR;

/* Reads the pad stick, negates and clamps it to the unit range and stores its length (v2.00 copy). */
void pad_read_clamped_stick_us2(char *moby)
{
    float stick[2];
    char *vars = *(char **)(moby + 104);
    float stick_x, stick_y, clamped_y;

    if (g_level_status_byte != 0) {
        char *hero = g_hero_state;
        *(float *)(vars + 84) = *(float *)(hero + 8112);
    } else {
        char *hero = g_hero_state;
        *(float *)(vars + 84) = -*(float *)(hero + 8112);
    }
    {
        char *hero = g_hero_state;
        stick_x = *(float *)(vars + 84);
        stick_y = -*(float *)(hero + 8116);
    }
    *(float *)(vars + 80) = stick_y;

    if (stick_x > 1.0f) {
        *(float *)(vars + 84) = 1.0f;
    } else if (stick_x < -1.0f) {
        *(float *)(vars + 84) = -1.0f;
    }

    clamped_y = *(float *)(vars + 80);
    if (clamped_y > 1.0f) {
        *(float *)(vars + 80) = 1.0f;
    } else if (clamped_y < -1.0f) {
        *(float *)(vars + 80) = -1.0f;
    }
    vec_clear_128(stick);
    stick[0] = *(float *)(vars + 80);
    stick[1] = *(float *)(vars + 84);
    g_stick_length = FastVecLength(stick);
}
