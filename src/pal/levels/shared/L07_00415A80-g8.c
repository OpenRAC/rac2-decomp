#include "include_asm.h"
#include "common.h"
extern f32 D_L07_001B0FE8[2];
extern f32 D_L07_001B0FF0 __attribute__((sda));
extern f32 D_L07_001B0FF4;
extern s32 D_L07_001B0FF8 __attribute__((sda));
extern s32 D_L07_001B0FFC;
extern s32 D_L07_001B1000 __attribute__((sda));
extern s32 D_L07_001B1004;
extern s32 D_L07_001B1008;
extern s32 D_L07_001B100C;
extern s32 D_L07_001B1010 __attribute__((sda));
extern void moby_set_state(u8 *a0, u8 a1, s32 a2);
extern int part_find_owned_effect_slot(char *a0, int a1, int a2);
extern int PlayMobySound(int index, int a1, char *a2);
extern void part_explode_object_into_pieces(void *a0, void *a1, void *a2, void *a3, int a4, int a5,
                               int a6, int a7, int a8, u8 a9, int a10);
extern void moby_mark_spawned(void *object);
extern f32 ref_L07_00410B48_00[2] __attribute__((sda));
extern f32 ref_L07_00410B48_01[2] __attribute__((sda));
extern f32 ref_L07_00410B48_02[2] __attribute__((sda));

/* The state byte at 0x20 picks the path: 0 clears the moby list of class 1, 1 asks the
   spawner and marks the object, 2 replaces the moby and runs the level's setup. */
void func_PAL_L07_00415A80(u8 *a0)
{
    u8 *s0 = a0;
    u8 *s1 = *(u8 **)(s0 + 0x68);

    switch (s0[0x20]) {
    case 0:
        moby_set_state(s0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(s0, 0x04010000, 0) == 0)
            goto done;
        if (*(int *)s1 != 0)
            goto done;
        moby_set_state(s0, 2, -1);
    done:
        s0[0xA8] = 0xFF;
        break;
    case 2:
        PlayMobySound(0, 0, s0);
        part_explode_object_into_pieces(s0, ref_L07_00410B48_02, ref_L07_00410B48_01,
                          ref_L07_00410B48_00, 0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        moby_mark_spawned(s0);
        break;
    }
}
