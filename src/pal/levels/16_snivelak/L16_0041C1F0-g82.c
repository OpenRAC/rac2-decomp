#include "include_asm.h"

#include "common.h"
extern char g_destructible_burst_params_c[8] __attribute__((sda));
extern char g_destructible_burst_params_b[8] __attribute__((sda));
extern char g_destructible_burst_params_a[8] __attribute__((sda));
extern s32 g_destructible_burst_group_bit __attribute__((sda));
typedef struct { f32 x, y, z, w; } BurstPoint;
extern BurstPoint g_destructible_burst_points[];
extern s32 math_fast_float_d(char *);
extern void moby_set_state(char *, s32, s32);
extern void *part_find_owned_effect_slot(char *, u32, s32);
extern void part_explode_object_into_pieces_pal(char *, char *, char *, char *, s32, s32, s32, s32, s32, s32, s32);
extern void vec_local_offset_to_world(char *, char *, f32, f32, f32);
extern char *SpawnExplosion_pal(char *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern void moby_mark_spawned(char *);

/* Alternates its hit color, then emits the three configured destruction bursts. */
void destructible_burst_update_pal(char *moby) {
    char pos[16];
    char *state = *(char **)(moby + 0x68);
    s32 i;
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(u16 *)(moby + 0x34) |= 16;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (math_fast_float_d(state + 4)) {
            if (*(u32 *)(moby + 0x78) & 1)
                *(u32 *)(moby + 0x78) = 0x7F60800E;
            else *(u32 *)(moby + 0x78) = 0x7F4C6C01;
            *(s32 *)(state + 4) = 2;
        }
        if (part_find_owned_effect_slot(moby, 0x04010000, 0) && *(s32 *)state == 0)
            moby_set_state(moby, 2, -1);
        *(u8 *)(moby + 0xA8) = 255;
        break;
    case 2:
        part_explode_object_into_pieces_pal(moby, g_destructible_burst_params_c, g_destructible_burst_params_b, g_destructible_burst_params_a, 65535, 0, g_destructible_burst_group_bit, 0, 65535, 255, 0);
        for (i = 0; i < 3; i++) {
            vec_local_offset_to_world(moby, pos, g_destructible_burst_points[i].x, g_destructible_burst_points[i].y, g_destructible_burst_points[i].z);
            SpawnExplosion_pal(pos, 0, 12, 12, 12, 12, 12, 0, 1, 0, 0, 0, *(f32 *)(moby + 0x2C), 20.0f);
        }
        if (g_destructible_burst_group_bit >= 0) {
            *(u16 *)(moby + 0x7C) = (1 << g_destructible_burst_group_bit) | 0x8000;
            moby_set_state(moby, 3, -1);
        } else moby_mark_spawned(moby);
        break;
    }
}
