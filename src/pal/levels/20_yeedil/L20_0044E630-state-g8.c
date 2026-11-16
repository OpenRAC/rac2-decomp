#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F449178;
extern s32 g_burst_explode_param_c __attribute__((sda));
extern s32 g_burst_explode_param_b __attribute__((sda));
extern s32 g_burst_explode_param_a __attribute__((sda));
extern void moby_set_state(char *, s32, s32);
extern void *part_find_owned_effect_slot(char *, s32, s32);
extern void *part_spawn_object_following_effect(void *, char *, s32, s32, float, float, s32, s32, s32, s32);
extern void part_explode_object_into_pieces_pal(char *, s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
extern void moby_compute_local_point(char *, void *, float, float, float);
extern char *SpawnExplosion_pal(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern char *moby_l00_spawn_child(char *, s32, s32);
extern void moby_mark_spawned(char *);

/* Three-state effect object: arms its emitter, waits for the trigger, then plays the burst and retires. */
void triggered_l20_burst_update_2_pal(char *moby)
{
    V4_F449178 v;
    s32 *rec = *(s32 **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        v.q = 0;
        v.f[2] = 2.0f;
        part_spawn_object_following_effect(&v, moby, 0x40204080, -1, 420000.0f, 1.0f, 1, -1, 0, -1);
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x04010000, 0) != 0 && *rec == 0)
            moby_set_state(moby, 2, -1);
        *(u8 *)(moby + 0xA8) = 0xFF;
        return;
    case 2:
        part_explode_object_into_pieces_pal(moby, &g_burst_explode_param_a, &g_burst_explode_param_b, &g_burst_explode_param_c, 0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        moby_compute_local_point(moby, &v, 0.0f, 0.0f, 2.0f);
        SpawnExplosion_pal(&v, 0, 0x19, 0x14, 0.5f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0);
        moby_l00_spawn_child(moby, 0x126A, 0);
        moby_mark_spawned(moby);
        return;
    }
}
