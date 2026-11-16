#include "include_asm.h"


#include "common.h"
extern void *CreateMoby(int id);
extern float mat_fast_helper_a(float x, float y);
extern float vec_length_xy(char *a);
extern int g_child_slot_used[];
extern int g_child_slot_light_ids[];

/* The func_L09_003A06B0 spawn for the level-06 slots: marks slot `index` busy, records it
   in the child's state and clears its handle. */
char *moby_spawn_child_in_slot_pal(char *object, char *a1, char *a2, int index, float f12)
{
    char *s1 = CreateMoby(0xFE5);
    char *s0;
    float d;

    if (s1 != 0) {
        *(u8 *)(s1 + 0x30) = 0xFF;
        *(u16 *)(s1 + 0x32) = 0xFF;
        *(u8 *)(s1 + 0x31) = 1;
        *(u8 *)(s1 + 0x20) = 0;
        *(u64 *)(s1 + 0x38) = *(u64 *)(object + 0x38);
        qcopy(s1 + 0x10, a2);
        g_child_slot_used[index] = 1;
        s0 = *(char **)(s1 + 0x68);
        qcopy(s0, a1);
        *(u32 *)(s0 + 0x38) = 0xC8;
        *(char **)(s0 + 0x3C) = object;
        *(float *)(s0 + 0x40) = f12;
        *(int *)(s0 + 0x48) = index;
        *(int *)(s0 + 0x4C) = -1;
        *(float *)(s1 + 0xF8) = mat_fast_helper_a(*(float *)a1, *(float *)(a1 + 4));
        d = vec_length_xy(a1);
        *(float *)(s1 + 0xF4) = -mat_fast_helper_a(d, *(float *)(a1 + 8));
        g_child_slot_light_ids[index] = -1;
    }
    return s1;
}

