#include "include_asm.h"

#include "common.h"
extern float FastDiffRots(float, float);
extern int moby_step_at_own_position_factor_pal(u8 *, float);
extern int moby_step_at_own_position_pal(u8 *);
extern float math_approach_target_with_direction_mode(void *, float, void *, float, float, float, int);
extern int ComputeRegionRouteHeading(void *, void *, void *, void *, int, void *, void *,
                              float, float);
extern int moby_step_controller_pal(u8 *, void *, float);
extern int moby_turn_toward_target_and_step_pal(u8 *, void *, float);
#define W(p, o) (*(int *)((p) + (o)))
#define H(p, o) (*(s16 *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define P(p, o) (*(u8 **)((p) + (o)))

/* Turns the Extermibot's body and torso part toward its target, depending on which animation it is playing. (PAL version) */
/* A unit of its own: the switch's jump table is this unit's only .rodata. */
void extermibot_aim_torso_pal(u8 *moby) {
    u8 *vars = P(moby, 0x68);
    int animation = moby[0x42];

    /* The byte is widened before the test, so it never equals -1; retail keeps
       the lbu, li -1, bne and the fallback load all the same. */
    if (animation == -1) animation = moby[0x43];
    switch (animation) {
    case 1:
        if (P(vars, 0x7C0)) qcopy(P(vars, 0x7C0) + 0xF0, moby + 0xF0);
        break;
    case 3: case 4: case 5: case 6: case 7:
    case 10: case 11: case 12: case 13: case 14: case 15:
        if (H(vars, 0x808) == 1) {
            if (FastDiffRots(F(vars, 0x7A4), F(moby, 0xF8)) > 0.6108652949333191f) {
                moby_step_at_own_position_factor_pal(moby, F(vars, 0x7A4));
            } else {
                if (P(vars, 0x7C0))
                    math_approach_target_with_direction_mode(P(vars, 0x7C0) + 0xF8, F(vars, 0x7A4), vars + 0x7CC,
                                  0.010053098f, 0.010053098f,
                                  0.25132746f, 0);
                moby_step_at_own_position_pal(moby);
            }
        } else {
            if (H(vars, 0x808) == 2) moby_step_at_own_position_factor_pal(moby, F(vars, 0x7A4));
            else moby_step_at_own_position_pal(moby);
            if (P(vars, 0x7C0))
                math_approach_target_with_direction_mode(P(vars, 0x7C0) + 0xF8, F(moby, 0xF8), vars + 0x7CC,
                              0.010053098f, 0.010053098f,
                              0.25132746f, 0);
        }
        break;
    case 8: case 9:
        if (W(vars, 0x7D4) != -1) {
            ComputeRegionRouteHeading(moby + 0x10, vars + 0x750, vars + 0x7DC, vars + 0x210, W(vars, 0x780),
                              vars + 0x78C, vars + 0x7D8, 0.0f, 0.4f);
            moby_step_controller_pal(moby, vars + 0x750, F(vars, 0x7DC));
        } else {
            moby_turn_toward_target_and_step_pal(moby, vars + 0x750, F(vars, 0x7A0));
        }
        if (P(vars, 0x7C0)) {
            if (H(vars, 0x808) == 1 &&
                FastDiffRots(F(vars, 0x7A4), F(moby, 0xF8)) < 0.6108652949333191f) {
                math_approach_target_with_direction_mode(P(vars, 0x7C0) + 0xF8, F(vars, 0x7A4), vars + 0x7CC,
                              0.010053098f, 0.010053098f,
                              0.25132746f, 0);
            } else {
                math_approach_target_with_direction_mode(P(vars, 0x7C0) + 0xF8, F(moby, 0xF8), vars + 0x7CC,
                              0.010053098f, 0.010053098f,
                              0.25132746f, 0);
            }
        }
        break;
    }
}
