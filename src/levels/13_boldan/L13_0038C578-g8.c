#include "common.h"


extern f32 g_spark_burst_follow_pos __attribute__((sda));
extern f32 g_spark_burst_piece_param_c __attribute__((sda));
extern f32 g_spark_burst_piece_param_b __attribute__((sda));
extern f32 g_spark_burst_piece_param_a __attribute__((sda));
extern f32 g_spark_burst_second_value __attribute__((nosda));
extern f32 g_spark_burst_first_value __attribute__((nosda));
extern void *part_find_owned_effect_slot(u8 *, s32, s32);
extern void moby_set_state(u8 *, s32, s32);
extern void moby_mark_spawned(u8 *);
extern void *part_spawn_object_following_effect(float, float, void *, u8 *, s32, s32, s32, s32, s32, s32);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void moby_compute_local_point(u8 *, f32 *, f32, f32, f32);
extern char *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                        float, float);

/* Waits for a trigger, then plays a burst of sparks and removes itself. */
void spark_l13_burst_update(u8 *moby) {
    s32 *vars = *(s32 **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        part_spawn_object_following_effect(210000.0f, 0.75f, &g_spark_burst_follow_pos, moby, 0x50204040, -1, 1, -1, 0, -1);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0 && *vars == 0)
            moby_set_state(moby, 2, -1);
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        f32 burst_pos[4];
        part_explode_object_into_pieces(moby, &g_spark_burst_piece_param_c, &g_spark_burst_piece_param_b, &g_spark_burst_piece_param_a,
                    0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        {
            f32 first = g_spark_burst_first_value;
            f32 x = g_spark_burst_follow_pos;
            f32 second = g_spark_burst_second_value;
            moby_compute_local_point(moby, burst_pos, x, second, first);
        }
        SpawnExplosion(burst_pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0, 0.3f, 20.0f);
        moby_mark_spawned(moby);
        break;
    }
    }
}
