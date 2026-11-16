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
void sub_object_update_turn_ramps_pal(unsigned char *moby) {
    unsigned char *self = moby;
    unsigned char *vars = *(unsigned char **)(self + 0x68);
    math_update_wrapped_angle_offset(moby, vars + 0x3C0, vars + 0x3C4, 0.25f, 0.06f, -1.0f);
    moby_scale_owner_words_by_angles(self, vars + 0x3C8, vars + 0x3CC, 0.15f, 0.05f, 0.025f);
    if (self[0x20] != 1)
        return;
    if (FastDecTimer((unsigned short *)(vars + 0x3D4)) != 0) {
        float turn = 2.0943954f;
        *(short *)(vars + 0x3D4) = 0xD9;
        if (math_random_int_below(2) != 0)
            turn = -turn;
        *(float *)(vars + 0x3D0) = FastAddRotations(*(float *)(self + 0xF8), turn);
    }
    math_spring_float_to_goal(self + 0xF8, vars + 0x3D8, *(float *)(vars + 0x3D0), 0.003f, 0.2f,
                  0.02f);
}

