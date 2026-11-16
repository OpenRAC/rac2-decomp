#include "common.h"

extern char g_hero_state[];
extern char ref_0030E8A8_00[];

extern void moby_get_facing_direction(char *, float *);
extern void FastVecSub(float *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(float *, float *, float);
extern float FastVecDot(float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern int CollLine(float *, float *, int, int, int);
extern float math_spring_float_to_goal(void *, float, void *, float, float, float);
extern int moby_move_and_collide(char *, float *, float, float, float, int);

/* Pushes a springy object down when the player stands on it and lets it bounce back up. Keeps it above the floor (PAL copy). */
void moby_spring_away_from_player_game_pal(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    char *hero = g_hero_state;
    short flag = *(short *)(hero + 0x202);
    float facing[4] __attribute__((aligned(16)));
    float to_object[4] __attribute__((aligned(16)));
    float side_offset[4] __attribute__((aligned(16)));
    float along_up[4] __attribute__((aligned(16)));
    float probe_below[4] __attribute__((aligned(16)));
    float probe_above[4] __attribute__((aligned(16)));
    float ground_point[4] __attribute__((aligned(16)));
    float ground_along[4] __attribute__((aligned(16)));
    float push[4] __attribute__((aligned(16)));
    float ground_to_object[4] __attribute__((aligned(16)));
    float push_amount;
    float projection;
    int mode;
    float height_along, side_distance, step, ground_gap, new_speed;

    if (*(int *)(vars + 0x44) == 0 && flag == 0)
        return;
    moby_get_facing_direction(obj + 0x10, facing);
    ground_gap = 0.0f;
    FastVecSub(to_object, obj + 0x10, hero + 0x80);
    projection = FastVecDot(to_object, facing);
    FastVecScale(along_up, facing, projection);
    FastVecSub(side_offset, to_object, along_up);
    height_along = FastVecLength(along_up);
    side_distance = FastVecLength(side_offset);
    FastVecScale(probe_below, facing, -2.5f);
    FastVecAdd(probe_below, obj + 0x10, probe_below);
    FastVecScale(probe_above, facing, 0.5f);
    FastVecAdd(probe_above, obj + 0x10, probe_above);
    if (CollLine(probe_above, probe_below, 2, 0, 0)) {
        qcopy(ground_point, ref_0030E8A8_00);
        mode = 0;
    } else {
        mode = 1;
    }
    if (mode == 0) {
        FastVecSub(push, ground_point, obj + 0x10);
        projection = FastVecDot(push, facing);
        FastVecScale(ground_along, facing, projection);
        ground_gap = FastVecLength(ground_along);
    }
    if (*(int *)(vars + 0x44) == 0) {
        if (!(side_distance < 1.0f))
            return;
        if (!(height_along < 1.3f))
            return;
        *(int *)(vars + 0x44) = 1;
    }
    qcopy(push, side_offset);
    push_amount = side_distance - 1.4f;
    if (push_amount > 0.0f)
        push_amount = 0.0f;
    if (flag == 0)
        push_amount = 0.0f;
    math_spring_float_to_goal(&push_amount, 0.0f, (float *)(vars + 0x48), 0.0288000014f, 0.432000041f, 0.080000006f);
    if (push_amount == 0.0f && *(float *)(vars + 0x48) == 0.0f && ground_gap < 0.02f)
        *(int *)(vars + 0x44) = 0;
    if (side_distance < *(float *)(vars + 0x48))
        *(float *)(vars + 0x48) = side_distance;
    if (*(float *)(vars + 0x48) < side_distance)
        vec_scale_to_length(push, push, *(float *)(vars + 0x48));
    moby_move_and_collide(obj, push, 0.5f, 0.4f, 0.0f, 0);
    if (mode == 0) {
        if (FastVecDot(ground_along, facing) > 0.0f) {
            qcopy(obj + 0x10, ground_point);
            *(float *)(vars + 0x4C) = 0.0f;
        } else {
            new_speed = *(float *)(vars + 0x4C) - 0.0096000005f;
            *(float *)(vars + 0x4C) = new_speed;
            FastVecScale(push, facing, new_speed);
            FastVecAdd(obj + 0x10, push, obj + 0x10);
            FastVecSub(ground_to_object, ground_point, obj + 0x10);
            if (FastVecDot(ground_to_object, facing) > 0.0f) {
                qcopy(obj + 0x10, ground_point);
                *(float *)(vars + 0x4C) = 0.0f;
            }
        }
    } else {
        *(float *)(vars + 0x4C) -= 0.0096000005f;
        FastVecScale(push, facing, *(float *)(vars + 0x4C));
        FastVecAdd(obj + 0x10, push, obj + 0x10);
    }
}
