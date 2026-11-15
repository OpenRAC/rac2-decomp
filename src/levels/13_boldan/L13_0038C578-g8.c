#include "common.h"


extern f32 D_L13_001AEBF0 __attribute__((sda));
extern f32 D_L13_001AEBD0 __attribute__((sda));
extern f32 D_L13_001AEBC8 __attribute__((sda));
extern f32 D_L13_001AEBC0 __attribute__((sda));
extern f32 D_L13_001AEBF4 __attribute__((nosda));
extern f32 D_L13_001AEBF8 __attribute__((nosda));
extern s32 part_find_owned_effect_slot(u8 *, s32, s32);
extern s32 moby_set_state(u8 *, s32, s32);
extern s32 moby_mark_spawned(u8 *);
extern void part_spawn_object_following_effect(float, float, void *, u8 *, s32, s32, s32, s32, s32, s32);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void moby_compute_local_point(u8 *, f32 *, f32, f32, f32);
extern void SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                        float, float);

/* Waits for a trigger, then plays a burst of sparks and removes itself. */
void spark_l13_burst_update(u8 *moby) {
    s32 *vars = *(s32 **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        part_spawn_object_following_effect(210000.0f, 0.75f, &D_L13_001AEBF0, moby, 0x50204040, -1, 1, -1, 0, -1);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0 && *vars == 0)
            moby_set_state(moby, 2, -1);
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        f32 burst_pos[4];
        part_explode_object_into_pieces(moby, &D_L13_001AEBD0, &D_L13_001AEBC8, &D_L13_001AEBC0,
                    0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        {
            f32 first = D_L13_001AEBF8;
            f32 x = D_L13_001AEBF0;
            f32 second = D_L13_001AEBF4;
            moby_compute_local_point(moby, burst_pos, x, second, first);
        }
        SpawnExplosion(burst_pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0, 0.3f, 20.0f);
        moby_mark_spawned(moby);
        break;
    }
    }
}
