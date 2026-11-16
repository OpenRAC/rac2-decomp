#include "include_asm.h"



#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(float *, float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern int moby_move_over_ground(char *, char *, char *, int, float, float, float, float);
extern float ApproachValue(float *, float, float);
extern float math_step_value_toward_target(float *, char *, float, float, float, float);
extern f32 math_approach_target_with_direction_mode(char *, float, float, float, float, char *, int);
extern float FastDiffRots(float, float);
extern int ComputeRegionRouteHeading(char *, int, float *, char *, int, char *, char *, float,
                             float);
extern void FastVecAdd(void *, void *, void *);

/* Turns the actor toward its target and keeps the two angles it stores at +0x470 and
   +0x474 of its state; returns 1 when the actor's state changed. */
int actor_steer_toward_goal_pal(char *obj, char *goal, float goal_yaw, float speed_scale, float slow_distance, float turn_rate)
{
    char *state = *(char **)(obj + 0x68);
    float to_goal[4];
    float step[4];
    float next_pos[4];
    float speed_value = 0.0f;
    float heading;
    float distance;
    float accel;
    int ret = 0;

    FastVecSub(to_goal, (float *)goal, (float *)(obj + 0x10));
    to_goal[2] = 0.0f;
    distance = FastVecLength(to_goal);
    accel = speed_scale * 0.0012f;
    if (slow_distance < distance) {
        int node_count = *(int *)(state + 0x480);

        heading = 0.0f;
        ComputeRegionRouteHeading(obj + 0x10, (int)goal, &heading, state + 0x260, node_count, state + 0x488,
                          state + 0x48C, turn_rate, 0.5f);
        math_approach_target_with_direction_mode(obj + 0xF8, heading, 0.005445428f,
                      0.005445428f, 0.35604724f, state + 0x474, 0);
        if (FastDiffRots(*(float *)(obj + 0xF8), heading) < 1.3089970350265503f) {
            math_step_value_toward_target(&speed_value, state + 0x470, distance, accel, accel, speed_scale * 0.020000001f);
        } else {
            *(float *)(state + 0x470) = 0.0f;
        }
    } else {
        math_approach_target_with_direction_mode(obj + 0xF8, goal_yaw, 0.005445428f,
                      0.005445428f, 0.35604724f, state + 0x474, 0);
        ApproachValue((float *)(state + 0x470), 0.0f, accel);
        if (*(float *)(state + 0x470) == 0.0f) {
            if (FastDiffRots(*(float *)(obj + 0xF8), goal_yaw) < 0.0872664749622345f) {
                *(float *)(state + 0x474) = 0.0f;
                ret = 1;
            }
        }
    }
    vec_scale_to_length(step, (float *)(obj + 0xC0), *(float *)(state + 0x470));
    FastVecAdd(next_pos, step, (float *)(obj + 0x10));
    if (moby_move_over_ground(obj, obj + 0x10, (char *)next_pos, 0, 0.8999999761581421f, 1.0f, 0.5f,
                     0.7853982448577881f) == 0) {
        *(int *)(state + 0x5A8) = *(int *)(state + 0x5A8) + 1;
    }
    /* The counter at +0x5A8 wraps at 0x14, and the actor then reports the change. */
    if (*(int *)(state + 0x5A8) < 0x14) {
        goto done;
    }
    *(int *)(state + 0x5A8) = 0;
    ret = 1;
done:
    return ret;
}

