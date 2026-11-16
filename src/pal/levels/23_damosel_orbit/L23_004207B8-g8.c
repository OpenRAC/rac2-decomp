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

void boss_turn_gun_toward_target_pal(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    float M0[16];
    float B[4];
    float A[4];
    float C[4];
    float M2[16];
    float D[4];
    float E[4];
    float f;

    moby_transform_joint_point(arg0, 0x22, (char *)M0);
    if (*(int *)(state + 0x604) != 0) {
        if (*(unsigned char *)(state + 0x431) == 0)
            AttachManipulator(arg0, 0x22, state + 0x430);
        build_axis_rotation_quaternion(state + 0x440, 2, *(float *)(state + 0x570));
        *(float *)(state + 0x570) = fast_subtract_rotations(*(float *)(state + 0x570), g_gun_turn_speed_degrees * 0.0003490659f);
    } else if (*(int *)(state + 0x60C) != -1) {
        FastVecSub((char *)A, state + 0x3F0, state + 0x3E0);
        vec_scale_to_length((char *)A, (char *)A, 10.0f);
        FastVecAdd((char *)B, (char *)A, arg0 + 0x10);
        mothership_project_point_onto_surface((char *)B, 0.0f);
        FastVecSub((char *)A, (char *)B, state + 0x3E0);
        vec_scale_to_length((char *)A, (char *)A, 1.0f);
        moby_transform_joint_point(arg0, *(int *)(state + 0x60C) + 1, (char *)M2);
        *(TI128 *)C = *(TI128 *)(M2 + 4);
        if (FastVecDot((char *)C, (char *)A) < 0.95f) {
            FastVecCross((char *)D, (char *)C, (char *)A);
            vec_scale_to_length((char *)E, state + 0x410, 1.0f);
            if (0.0f < FastVecDot((char *)D, (char *)E))
                f = g_gun_turn_speed_degrees;
            else
                f = -g_gun_turn_speed_degrees;
            if (*(unsigned char *)(state + 0x431) == 0)
                AttachManipulator(arg0, 0x22, state + 0x430);
            build_axis_rotation_quaternion(state + 0x440, 2, *(float *)(state + 0x570));
            *(float *)(state + 0x570) = fast_subtract_rotations(*(float *)(state + 0x570), -(f * 0.0003490659f));
        }
    }
}
