#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F449178;

extern s32 D_L20_001B23A0 __attribute__((sda));
extern s32 D_L20_001B23A8 __attribute__((sda));
extern s32 D_L20_001B23B0 __attribute__((sda));

extern void moby_set_state(char *, s32, s32);
extern s32 part_find_owned_effect_slot(char *, s32, s32);
extern void part_spawn_object_following_effect(void *, char *, s32, s32, float, float, s32, s32, s32, s32);
extern s32 part_explode_object_into_pieces(char *, s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
extern void moby_compute_local_point(char *, void *, float, float, float);
extern void SpawnExplosion(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern void moby_l00_spawn_child(char *, s32, s32);
extern void moby_mark_spawned(char *);

/* Three-state effect object: arms its emitter, waits for the trigger, then plays the burst and retires. */
/* Update handler for moby class 4713: it arms itself, waits for a trigger, then plays a burst effect and removes itself. */
void triggered_l20_burst_update_2(char *moby)
{
    V4_F449178 burst_pos;
    s32 *vars = *(s32 **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        burst_pos.q = 0;
        burst_pos.f[2] = 2.0f;
        part_spawn_object_following_effect(&burst_pos, moby, 0x40204080, -1, 420000.0f, 1.0f, 1, -1, 0, -1);
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x04010000, 0) != 0 && *vars == 0)
            moby_set_state(moby, 2, -1);
        *(u8 *)(moby + 0xA8) = 0xFF;
        return;
    case 2:
        part_explode_object_into_pieces(moby, &D_L20_001B23B0, &D_L20_001B23A8, &D_L20_001B23A0, 0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        moby_compute_local_point(moby, &burst_pos, 0.0f, 0.0f, 2.0f);
        SpawnExplosion(&burst_pos, 0, 0x19, 0x14, 0.5f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0);
        moby_l00_spawn_child(moby, 0x126A, 0);
        moby_mark_spawned(moby);
        return;
    }
}
