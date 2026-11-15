#include "include_asm.h"
#include "common.h"

extern void *CreateMoby(int id);
extern float mat_fast_helper_a(float x, float y);
extern float vec_length_xy(char *a);
extern int D_L06_001B3760[];
extern int D_L06_001B3778[];

/* The func_L09_003A06B0 spawn for the level-06 slots: marks slot `index` busy, records it
   in the child's state and clears its handle. */
/* Spawns a child moby (class 4069) in a numbered slot, aimed along a direction. */
char *moby_spawn_child_in_slot(char *object, char *direction, char *position, int index, float speed)
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
        *(float *)(child + 0xF8) = mat_fast_helper_a(*(float *)direction, *(float *)(direction + 4));
        flatLength = vec_length_xy(direction);
        *(float *)(child + 0xF4) = -mat_fast_helper_a(flatLength, *(float *)(direction + 8));
        D_L06_001B3778[index] = -1;
    }
    return child;
}
