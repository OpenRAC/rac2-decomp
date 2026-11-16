#include "include_asm.h"
#include "names.h"

/* func_PAL_L03_003C8BE8, the PAL copy of func_L03_003C4BD8: the same C, with the timers scaled
   to 50 Hz. */

extern int math_fast_float_d(void *);

extern float math_random_signed_float_range(float, float);

extern float math_random_float_range(float, float);

extern int math_random_int_range(int, int);

extern int math_random_int_below(int);

/* The level's own copy of the object's tilt routine (func_L03_003C4A10), at another address
   in every level that has it. */
extern void ref_L03_003C4BD8_00(unsigned char *, void *);

/* The position the tilt is measured from: a four-float vector in the boot's resident data. */
extern char g_zero_l00_vector[];

/* Every so often picks a new random head tilt for the bot, or makes it look toward a fixed point. (PAL: timers scaled to 50 Hz) */
void bot_update_head_tilt_pal(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float pitch;
    float yaw;
    int flag;

    if (math_fast_float_d(state + 0x384) != 0) {
        if (object[0x95] == 2) {
            *(float *)(state + 0x388) = math_random_signed_float_range(5.0f, 60.0f) * 0.017453294f;
            *(float *)(state + 0x38C) = math_random_float_range(-20.0f, 0.0f) * 0.017453294f;
            *(int *)(state + 0x384) = (math_random_int_range(30, 45) * 5 + 2) / 6;
            *(int *)(state + 0x390) = 0;
        } else {
            *(float *)(state + 0x388) = math_random_signed_float_range(5.0f, 20.0f) * 0.017453294f;
            *(float *)(state + 0x38C) = math_random_float_range(-15.0f, 5.0f) * 0.017453294f;
            flag = (math_random_int_below(4) == 0);
            *(int *)(state + 0x390) = flag;
            if (flag) {
                *(int *)(state + 0x384) = (math_random_int_range(180, 300) * 5 + 2) / 6;
            } else {
                *(int *)(state + 0x384) = (math_random_int_range(60, 120) * 5 + 2) / 6;
            }
        }
    }

    if (*(int *)(state + 0x390) != 0) {
        ref_L03_003C4BD8_00(object, g_zero_l00_vector);
    } else {
        pitch = *(float *)(state + 0x38C);
        yaw = *(float *)(state + 0x388);
        /* This cc1 emits the two pairs of stores in the opposite order to the source, so the
           pair at 0x324 comes first here to land them at 0x2A4 as the retail has them. */
        *(float *)(state + 0x324) = pitch;
        *(float *)(state + 0x328) = yaw;
        *(float *)(state + 0x2A4) = pitch;
        *(float *)(state + 0x2A8) = yaw;
    }
}
