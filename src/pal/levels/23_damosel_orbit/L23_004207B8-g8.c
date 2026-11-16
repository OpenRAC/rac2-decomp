#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern float g_gun_turn_speed_degrees __attribute__((sda));
extern void moby_transform_joint_point(char *, int, char *);
extern void AttachManipulator(char *, int, char *);
extern void build_axis_rotation_quaternion(void *, int, float);
extern float fast_subtract_rotations(float, float);
extern void FastVecSub(char *, char *, char *);
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern float FastVecDot(char *, char *);
extern void FastVecCross(char *, char *, char *);
extern void mothership_project_point_onto_surface(char *, float);

/* Turns the boss gun joint toward its target. (PAL: 50 Hz timings) */
void boss_turn_gun_toward_target_pal(char *boss) {
    char *state = *(char **)(boss + 0x68);
    float joint_matrix[16];
    float target_point[4];
    float target_dir[4];
    float gun_axis[4];
    float target_matrix[16];
    float turn_axis[4];
    float state_axis[4];
    float turn_speed;

    moby_transform_joint_point(boss, 0x22, (char *)joint_matrix);
    if (*(int *)(state + 0x604) != 0) {
        if (*(unsigned char *)(state + 0x431) == 0)
            AttachManipulator(boss, 0x22, state + 0x430);
        build_axis_rotation_quaternion(state + 0x440, 2, *(float *)(state + 0x570));
        *(float *)(state + 0x570) = fast_subtract_rotations(*(float *)(state + 0x570), g_gun_turn_speed_degrees * 0.0003490659f);
    } else if (*(int *)(state + 0x60C) != -1) {
        FastVecSub((char *)target_dir, state + 0x3F0, state + 0x3E0);
        vec_scale_to_length((char *)target_dir, (char *)target_dir, 10.0f);
        FastVecAdd((char *)target_point, (char *)target_dir, boss + 0x10);
        mothership_project_point_onto_surface((char *)target_point, 0.0f);
        FastVecSub((char *)target_dir, (char *)target_point, state + 0x3E0);
        vec_scale_to_length((char *)target_dir, (char *)target_dir, 1.0f);
        moby_transform_joint_point(boss, *(int *)(state + 0x60C) + 1, (char *)target_matrix);
        *(TI128 *)gun_axis = *(TI128 *)(target_matrix + 4);
        if (FastVecDot((char *)gun_axis, (char *)target_dir) < 0.95f) {
            FastVecCross((char *)turn_axis, (char *)gun_axis, (char *)target_dir);
            vec_scale_to_length((char *)state_axis, state + 0x410, 1.0f);
            if (0.0f < FastVecDot((char *)turn_axis, (char *)state_axis))
                turn_speed = g_gun_turn_speed_degrees;
            else
                turn_speed = -g_gun_turn_speed_degrees;
            if (*(unsigned char *)(state + 0x431) == 0)
                AttachManipulator(boss, 0x22, state + 0x430);
            build_axis_rotation_quaternion(state + 0x440, 2, *(float *)(state + 0x570));
            *(float *)(state + 0x570) = fast_subtract_rotations(*(float *)(state + 0x570), -(turn_speed * 0.0003490659f));
        }
    }
}
