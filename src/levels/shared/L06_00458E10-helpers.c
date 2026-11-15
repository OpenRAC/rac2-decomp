#include "include_asm.h"
#include "common.h"

extern void *func_0029EFD0(int id);
extern float func_00283248(float x, float y);
extern float func_00282E20(char *a);
extern int D_L06_001B3760[];
extern int D_L06_001B3778[];

/* The func_L09_003A06B0 spawn for the level-06 slots: marks slot `index` busy, records it
   in the child's state and clears its handle. */
/* Spawns a child moby (class 4069) in a numbered slot, aimed along a direction. */
char *func_L06_00458E10(char *object, char *direction, char *position, int index, float speed)
{
    char *child = CreateMoby(0xFE5 /* moby class 4069 */);
    char *childVars;
    float flatLength;

    if (child != 0) {
        *(u8 *)(child + 0x30) = 0xFF;
        *(u16 *)(child + 0x32) = 0xFF;
        *(u8 *)(child + 0x31) = 1;
        *(u8 *)(child + 0x20) = 0;
        *(u64 *)(child + 0x38) = *(u64 *)(object + 0x38);
        qcopy(child + 0x10, position);
        D_L06_001B3760[index] = 1;
        childVars = *(char **)(child + 0x68);
        qcopy(childVars, direction);
        *(u32 *)(childVars + 0x38) = 0xF0;
        *(char **)(childVars + 0x3C) = object;
        *(float *)(childVars + 0x40) = speed;
        *(int *)(childVars + 0x48) = index;
        *(int *)(childVars + 0x4C) = -1;
        *(float *)(child + 0xF8) = FastMatrixHelperA(*(float *)direction, *(float *)(direction + 4));
        flatLength = vec_length_xy(direction);
        *(float *)(child + 0xF4) = -FastMatrixHelperA(flatLength, *(float *)(direction + 8));
        D_L06_001B3778[index] = -1;
    }
    return child;
}
