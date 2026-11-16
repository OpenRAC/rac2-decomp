#include "include_asm.h"
#include "common.h"
extern f32 g_puff_fall_speed_range[2];
extern f32 g_puff_color_a __attribute__((sda));
extern f32 g_puff_color_b;
extern s32 g_puff_kind_a __attribute__((sda));
extern s32 g_puff_kind_b;
extern s32 g_puff_size_min_a __attribute__((sda));
extern s32 g_puff_size_max_a;
extern s32 g_puff_size_min_b;
extern s32 g_puff_size_max_b;
extern s32 g_puff_extra_count __attribute__((sda));
extern void moby_set_state(u8 *moby, u8 a1, s32 a2);
extern void *part_find_owned_effect_slot(char *moby, int a1, int a2);
extern int PlayMobySound(int index, int a1, char *a2);
extern void part_explode_object_into_pieces(void *moby, void *a1, void *a2, void *a3, int a4, int a5,
                               int a6, int a7, int a8, u8 a9, int a10);
extern void moby_mark_spawned(void *object);
extern f32 ref_L07_00410B48_00[2] __attribute__((sda));
extern f32 ref_L07_00410B48_01[2] __attribute__((sda));
extern f32 ref_L07_00410B48_02[2] __attribute__((sda));

/* The state byte at 0x20 picks the path: 0 clears the moby list of class 1, 1 asks the
   spawner and marks the object, 2 replaces the moby and runs the level's setup. */
void effect_l07_spawner_update_pal(u8 *moby)
{
    u8 *spawner = moby;
    u8 *vars = *(u8 **)(spawner + 0x68);

    switch (spawner[0x20]) {
    case 0:
        moby_set_state(spawner, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(spawner, 0x04010000, 0) == 0)
            goto done;
        if (*(int *)vars != 0)
            goto done;
        moby_set_state(spawner, 2, -1);
    done:
        spawner[0xA8] = 0xFF;
        break;
    case 2:
        PlayMobySound(0, 0, spawner);
        part_explode_object_into_pieces(spawner, ref_L07_00410B48_02, ref_L07_00410B48_01,
                          ref_L07_00410B48_00, 0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        moby_mark_spawned(spawner);
        break;
    }
}
