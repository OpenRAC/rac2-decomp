#include "common.h"
extern void mat_build_rotation_from_angles(void *a0, float *a1);

/* Moves the robot's arm history forward one step and stores its current arm position and target. */
void smasher_robot_advance_arm_history(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *target_record;
    char *target_slot;
    char *target_pos;

    *(s32 *)(state + 0x4B8) = 0;
    *(s32 *)(state + 0x4B4) = (*(s32 *)(state + 0x4B4) + 1) % 4;
    if (*(s32 *)(state + 0x4B0) < 4)
        *(s32 *)(state + 0x4B0) = *(s32 *)(state + 0x4B0) + 1;
    mat_build_rotation_from_angles(((*(s32 *)(state + 0x4B4) << 4) + 0x370) + state, (float *)(object + 0xF0));
    target_record = *(char **)(state + 0x4A4);
    if (target_record != 0) {
        target_pos = target_record + 0x10;
        target_slot = (char *)((*(s32 *)(state + 0x4B4) << 4) + (u32)state + 0x270);
        qcopy(target_slot, target_pos);
    }
}
