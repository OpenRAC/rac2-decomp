#include "common.h"

/* func_PAL_L06_004238A0, the PAL copy of func_L06_0041F558: the same C, where the three
   func_002AA3A8 rates are scaled by 1.2f at build time and the two func_002AEC48 rates by
   1.44f at run time. They stay in locals so that the product is not folded. */

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

/* Keeps the actor on the ground and turns its upper body toward the player while it attacks (PAL: 50 Hz timings). */
void actor_aim_body_at_target_pal(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    float height, angle, speed, limit;

    gfx_update_color_fade(obj, state + 0x50);
    FastDecTimer(state + 0x24A);
    if (*(unsigned short *)(obj + 0x96) <= 0xFFFE)
        ++*(unsigned short *)(obj + 0x96);
    height = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
    if (math_fabs(*(float *)(obj + 0x18) - height) < 10.0f) {
        math_spring_float_to_goal(obj + 0x18, height, 0.001f,
                      0.012000001f, 0.21600002f, state + 0x49C);
        if (*(float *)(obj + 0x18) < height)
            *(float *)(obj + 0x18) = height;
    }
    if (FastDiffRots(*(float *)(obj + 0xF8),
                      mat_fast_helper_a(*(float *)(state + 0x200) - *(float *)(obj + 0x10),
                                    *(float *)(state + 0x204) - *(float *)(obj + 0x14)))
            <= 2.6179940700531006f && (unsigned char)obj[0x95] == 2) {
        angle = fast_subtract_rotations(
            mat_fast_helper_a(*(float *)(state + 0x200) - *(float *)(obj + 0x10),
                          *(float *)(state + 0x204) - *(float *)(obj + 0x14)),
            *(float *)(obj + 0xF8));
        speed = 0.02f;
        limit = 0.3f;
        if (angle > 1.396263599395752f)
            angle = 1.396263599395752f;
        else if (angle < -1.396263599395752f)
            angle = -1.396263599395752f;
        *(float *)(state + 0x588) = angle * 0.75f;
        *(float *)(state + 0x508) = angle * 0.4f;
        moby_update_eased_node(obj, state + 0x4A0, 1, speed * 1.44f, limit * 1.44f);
        moby_update_eased_node(obj, state + 0x520, 2, speed * 1.44f, limit * 1.44f);
        value_set_and_smooth(obj, state + 0x4A0, 2.5f, 1, 1);
    }
}
