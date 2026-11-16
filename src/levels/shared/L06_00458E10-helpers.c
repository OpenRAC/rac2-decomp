#include "include_asm.h"
#include "common.h"

extern void *CreateMoby(int id);
extern float mat_fast_helper_a(float x, float y);
extern float vec_length_xy(char *a);
extern int g_child_slot_used[];
extern int g_child_slot_light_ids[];

/* The func_L09_003A06B0 spawn for the level-06 slots: marks slot `index` busy, records it
   in the child's state and clears its handle. */
/* Spawns a child moby (class 4069) in a numbered slot, aimed along a direction. */
char *moby_spawn_child_in_slot(char *object, char *direction, char *position, int index, float speed)
{
    char *child = CreateMoby(0xFE5 /* moby class 4069 */);
    char *child_vars;
    float flat_length;

    if (child != 0) {
        *(u8 *)(child + 0x30) = 0xFF;
        *(u16 *)(child + 0x32) = 0xFF;
        *(u8 *)(child + 0x31) = 1;
        *(u8 *)(child + 0x20) = 0;
        *(u64 *)(child + 0x38) = *(u64 *)(object + 0x38);
        qcopy(child + 0x10, position);
        g_child_slot_used[index] = 1;
        child_vars = *(char **)(child + 0x68);
        qcopy(child_vars, direction);
        *(u32 *)(child_vars + 0x38) = 0xF0;
        *(char **)(child_vars + 0x3C) = object;
        *(float *)(child_vars + 0x40) = speed;
        *(int *)(child_vars + 0x48) = index;
        *(int *)(child_vars + 0x4C) = -1;
        *(float *)(child + 0xF8) = mat_fast_helper_a(*(float *)direction, *(float *)(direction + 4));
        flat_length = vec_length_xy(direction);
        *(float *)(child + 0xF4) = -mat_fast_helper_a(flat_length, *(float *)(direction + 8));
        g_child_slot_light_ids[index] = -1;
    }
    return child;
}
