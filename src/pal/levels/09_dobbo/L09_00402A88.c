#include "include_asm.h"
#include "names.h"

extern int FastDecTimer(unsigned short *);
extern int math_random_int_below(int);
extern float FastAddRotations(float, float);
extern void math_update_wrapped_angle_offset(unsigned char *, unsigned char *, unsigned char *, float, float, float);
extern void moby_scale_owner_words_by_angles(unsigned char *, unsigned char *, unsigned char *, float, float, float);
extern float math_spring_float_to_goal(unsigned char *, unsigned char *, float, float, float, float);

/* Feeds the sub-object two measured channel ramps, then, only in state 1 and
   only while the sub-object's halfword 0x3D4 is live, stamps it 0x104 and
   folds a 2.0943954 radian turn into its 0xF8 angle -- sign drawn from the
   resident two-way draw -- before the shared four-float ramp body runs on the
   block at 0x3D8. */
void sub_object_update_turn_ramps_pal(unsigned char *a0) {
    unsigned char *s1 = a0;
    unsigned char *s0 = *(unsigned char **)(s1 + 0x68);
    math_update_wrapped_angle_offset(a0, s0 + 0x3C0, s0 + 0x3C4, 0.25f, 0.06f, -1.0f);
    moby_scale_owner_words_by_angles(s1, s0 + 0x3C8, s0 + 0x3CC, 0.15f, 0.05f, 0.025f);
    if (s1[0x20] != 1)
        return;
    if (FastDecTimer((unsigned short *)(s0 + 0x3D4)) != 0) {
        float t = 2.0943954f;
        *(short *)(s0 + 0x3D4) = 0xD9;
        if (math_random_int_below(2) != 0)
            t = -t;
        *(float *)(s0 + 0x3D0) = FastAddRotations(*(float *)(s1 + 0xF8), t);
    }
    math_spring_float_to_goal(s1 + 0xF8, s0 + 0x3D8, *(float *)(s0 + 0x3D0), 0.003f, 0.2f,
                  0.02f);
}

