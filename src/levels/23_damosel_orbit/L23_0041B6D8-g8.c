#include "include_asm.h"
#include "names.h"

/* func_L23_0041B6D8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001B1564 __attribute__((sda));

extern void func_0029FC20(char *, int, char *);

extern void func_0029F978(char *, int, char *);

extern void func_00283898(void *, int, float);

extern float func_00283BE0(float, float);

extern void func_00282CF0(char *, char *, char *);

extern void func_00282CC0(char *, char *, char *);

extern void func_00282F20(char *, char *, float);

extern float func_00282DB0(char *, char *);

extern void func_00282DD8(char *, char *, char *);

extern void func_L23_00418650(char *, float);

/* Turns the gun joint toward its target, or keeps it turning while a shot is active. */
void func_L23_0041B6D8(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float gunMatrix[16];
    float aimPoint[4];
    float aimDir[4];
    float jointDir[4];
    float jointMatrix[16];
    float turnAxis[4];
    float upDir[4];
    float turnSpeed;

    TransformMobyJointPoint(moby, 0x22, (char *)gunMatrix);
    if (*(int *)(state + 0x604) != 0) {
        if (*(unsigned char *)(state + 0x431) == 0)
            AttachManipulator(moby, 0x22, state + 0x430);
        build_axis_rotation_quaternion(state + 0x440, 2, *(float *)(state + 0x570));
        *(float *)(state + 0x570) = fast_subtract_rotations(*(float *)(state + 0x570), D_L23_001B1564 * 0.00029088825f);
    } else if (*(int *)(state + 0x60C) != -1) {
        FastVecSub((char *)aimDir, state + 0x3F0, state + 0x3E0);
        vec_scale_to_length((char *)aimDir, (char *)aimDir, 10.0f);
        FastVecAdd((char *)aimPoint, (char *)aimDir, moby + 0x10);
        ProjectPointOntoPlanetSurface((char *)aimPoint, 0.0f);
        FastVecSub((char *)aimDir, (char *)aimPoint, state + 0x3E0);
        vec_scale_to_length((char *)aimDir, (char *)aimDir, 1.0f);
        TransformMobyJointPoint(moby, *(int *)(state + 0x60C) + 1, (char *)jointMatrix);
        *(TI128 *)jointDir = *(TI128 *)(jointMatrix + 4);
        if (FastVecDot((char *)jointDir, (char *)aimDir) < 0.95f) {
            FastVecCross((char *)turnAxis, (char *)jointDir, (char *)aimDir);
            vec_scale_to_length((char *)upDir, state + 0x410, 1.0f);
            if (0.0f < FastVecDot((char *)turnAxis, (char *)upDir))
                turnSpeed = D_L23_001B1564;
            else
                turnSpeed = -D_L23_001B1564;
            if (*(unsigned char *)(state + 0x431) == 0)
                AttachManipulator(moby, 0x22, state + 0x430);
            build_axis_rotation_quaternion(state + 0x440, 2, *(float *)(state + 0x570));
            *(float *)(state + 0x570) = fast_subtract_rotations(*(float *)(state + 0x570), -(turnSpeed * 0.00029088825f));
        }
    }
}
