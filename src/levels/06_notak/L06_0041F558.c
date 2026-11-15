#include "common.h"

extern int FastDecTimer(char *);
extern float mat_fast_helper_a(float, float);
extern void value_set_and_smooth(char *, char *, float, int, int);
extern void gfx_update_color_fade(char *, char *);
extern float coll_probe_ground_height_below(char *, int, float);
extern float math_fabs(float);
extern float math_spring_float_to_goal(char *, float, float, float, float, char *);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void moby_update_eased_node(char *, char *, int, float, float);

/* Keeps the actor on the ground and turns its upper body toward the player while it attacks. */
void actor_aim_body_at_target(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float groundHeight, angle;

    gfx_update_color_fade(moby, vars + 0x50);
    FastDecTimer(vars + 0x24A);
    if (*(unsigned short *)(moby + 0x96) <= 0xFFFE)
        ++*(unsigned short *)(moby + 0x96);
    groundHeight = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
    if (math_fabs(*(float *)(moby + 0x18) - groundHeight) < 10.0f) {
        math_spring_float_to_goal(moby + 0x18, groundHeight, 0.00083333341171965f,
                      0.010000000707805157f, 0.18000000715255737f, vars + 0x49C);
        if (*(float *)(moby + 0x18) < groundHeight)
            *(float *)(moby + 0x18) = groundHeight;
    }
    if (FastDiffRots(*(float *)(moby + 0xF8),
                      mat_fast_helper_a(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                                    *(float *)(vars + 0x204) - *(float *)(moby + 0x14)))
            <= 2.6179940700531006f && (unsigned char)moby[0x95] == 2) {
        angle = fast_subtract_rotations(
            mat_fast_helper_a(*(float *)(vars + 0x200) - *(float *)(moby + 0x10),
                          *(float *)(vars + 0x204) - *(float *)(moby + 0x14)),
            *(float *)(moby + 0xF8));
        if (angle > 1.396263599395752f)
            angle = 1.396263599395752f;
        else if (angle < -1.396263599395752f)
            angle = -1.396263599395752f;
        *(float *)(vars + 0x588) = angle * 0.75f;
        *(float *)(vars + 0x508) = angle * 0.4f;
        moby_update_eased_node(moby, vars + 0x4A0, 1, 0.02f, 0.3f);
        moby_update_eased_node(moby, vars + 0x520, 2, 0.02f, 0.3f);
        value_set_and_smooth(moby, vars + 0x4A0, 2.5f, 1, 1);
    }
}
