#include "include_asm.h"
#include "names.h"

extern char *g_mothership_boss_moby __attribute__((sda));
extern void AttachManipulator(char *, int, char *);
extern void build_axis_rotation_quaternion(void *, int, float);
extern float fast_subtract_rotations(float, float);
extern float g_joint_turn_speed_a __attribute__((sda));
extern float g_joint_turn_speed_b __attribute__((sda));

/* Relatches the two measured pairs at +0x580 and +0x584 from the two float arguments. */
void mothership_turn_joints_pal(char *boss, float turn_a, float turn_b) {
    char *state = *(char **)(g_mothership_boss_moby + 0x68);

    if (*(unsigned char *)(state + 0x4F1) == 0)
        AttachManipulator(boss, 0x28, state + 0x4F0);
    build_axis_rotation_quaternion(state + 0x500, 0, *(float *)(state + 0x580));
    *(float *)(state + 0x580) = fast_subtract_rotations(*(float *)(state + 0x580), turn_a * g_joint_turn_speed_a * 0.0003490659f);
    if (*(unsigned char *)(state + 0x531) == 0)
        AttachManipulator(boss, 0x29, state + 0x530);
    build_axis_rotation_quaternion(state + 0x540, 0, *(float *)(state + 0x584));
    *(float *)(state + 0x584) = fast_subtract_rotations(*(float *)(state + 0x584), turn_b * g_joint_turn_speed_b * 0.0003490659f);
}
