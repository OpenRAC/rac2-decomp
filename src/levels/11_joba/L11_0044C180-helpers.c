#include "common.h"
extern void func_002A91F0(void *a0, float *a1);

/* Moves the robot's arm history forward one step and stores its current arm position and target. */
void func_L11_0044C180(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *targetRecord;
    char *targetSlot;
    char *targetPos;

    *(s32 *)(state + 0x4B8) = 0;
    *(s32 *)(state + 0x4B4) = (*(s32 *)(state + 0x4B4) + 1) % 4;
    if (*(s32 *)(state + 0x4B0) < 4)
        *(s32 *)(state + 0x4B0) = *(s32 *)(state + 0x4B0) + 1;
    BuildRotationFromAngles(((*(s32 *)(state + 0x4B4) << 4) + 0x370) + state, (float *)(object + 0xF0));
    targetRecord = *(char **)(state + 0x4A4);
    if (targetRecord != 0) {
        targetPos = targetRecord + 0x10;
        targetSlot = (char *)((*(s32 *)(state + 0x4B4) << 4) + (u32)state + 0x270);
        qcopy(targetSlot, targetPos);
    }
}
