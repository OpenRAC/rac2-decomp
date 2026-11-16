#include "include_asm.h"
#include "names.h"

/* func_L23_0041B6D8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

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

/* Turns the gun joint toward its target, or keeps it turning while a shot is active. */
void boss_turn_gun_toward_target(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float gunMatrix[16];
    float aimPoint[4];
    float aimDir[4];
    float jointDir[4];
    float jointMatrix[16];
    float turnAxis[4];
    float upDir[4];
    float turnSpeed;

    moby_transform_joint_point(moby, 0x22, (char *)gunMatrix);
    if (*(int *)(state + 0x604) != 0) {
        if (*(unsigned char *)(state + 0x431) == 0)
            AttachManipulator(moby, 0x22, state + 0x430);
        build_axis_rotation_quaternion(state + 0x440, 2, *(float *)(state + 0x570));
        *(float *)(state + 0x570) = fast_subtract_rotations(*(float *)(state + 0x570), g_gun_turn_speed_degrees * 0.00029088825f);
    } else if (*(int *)(state + 0x60C) != -1) {
        FastVecSub((char *)aimDir, state + 0x3F0, state + 0x3E0);
        vec_scale_to_length((char *)aimDir, (char *)aimDir, 10.0f);
        FastVecAdd((char *)aimPoint, (char *)aimDir, moby + 0x10);
        mothership_project_point_onto_surface((char *)aimPoint, 0.0f);
        FastVecSub((char *)aimDir, (char *)aimPoint, state + 0x3E0);
        vec_scale_to_length((char *)aimDir, (char *)aimDir, 1.0f);
        moby_transform_joint_point(moby, *(int *)(state + 0x60C) + 1, (char *)jointMatrix);
        *(TI128 *)jointDir = *(TI128 *)(jointMatrix + 4);
        if (FastVecDot((char *)jointDir, (char *)aimDir) < 0.95f) {
            FastVecCross((char *)turnAxis, (char *)jointDir, (char *)aimDir);
            vec_scale_to_length((char *)upDir, state + 0x410, 1.0f);
            if (0.0f < FastVecDot((char *)turnAxis, (char *)upDir))
                turnSpeed = g_gun_turn_speed_degrees;
            else
                turnSpeed = -g_gun_turn_speed_degrees;
            if (*(unsigned char *)(state + 0x431) == 0)
                AttachManipulator(moby, 0x22, state + 0x430);
            build_axis_rotation_quaternion(state + 0x440, 2, *(float *)(state + 0x570));
            *(float *)(state + 0x570) = fast_subtract_rotations(*(float *)(state + 0x570), -(turnSpeed * 0.00029088825f));
        }
    }
}
