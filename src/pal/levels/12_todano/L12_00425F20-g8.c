#include "include_asm.h"

#include "common.h"
extern f32 g_burst_piece_params_a[] SDATA(D_L12_001B1F50);
extern f32 g_burst_piece_params_b[] SDATA(D_L12_001B1F58);
extern f32 g_burst_piece_params_c[] SDATA(D_L12_001B1F60);
extern s32 g_burst_piece_effect_id __attribute__((sda));
extern f32 g_burst_offset_x __attribute__((sda));
extern f32 g_burst_offset_y __attribute__((nosda));
extern f32 g_burst_offset_z __attribute__((nosda));
extern char g_burst_piece_params_d[];
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern s32 PlayMobySound(s32, s32, s32);
extern void moby_mark_spawned(void *);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, unsigned char, int);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern u8 *g_moby_list_start MACRO_ADDR;
extern s32 g_frame_l12_counter __attribute__((sda));
extern u8 *g_tracked_object_ptr __attribute__((nosda));
extern u8 *g_second_tracked_object __attribute__((nosda));
extern s32 g_explosion_piece_effect __attribute__((sda));
extern f32 g_explosion_piece_table_c[] SDATA(D_L12_001B2280);
extern f32 g_explosion_piece_table_b[] SDATA(D_L12_001B2288);
extern f32 g_explosion_piece_offsets[] SDATA(D_L12_001B22B0);
extern u8 *CreateMoby(int);

/* Waits until the hero hits it, then shows a flash, a burst of sparks and a sound before removing itself (PAL: 50 Hz timings). */
void hit_l12_burst_update_pal(u8 *moby)
{
    s32 *vars = *(s32 **)(moby + 0x68);
    f32 pos[4];

    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0 && *vars == 0) {
            moby_set_state(moby, 2, -1);
            PlayMobySound(0, 0, (s32)moby);
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        part_explode_object_into_pieces_pal(moby, g_burst_piece_params_c, g_burst_piece_params_b, g_burst_piece_params_a, 0xFFFF, 0,
                          g_burst_piece_effect_id, 0, 1, 0xFF, 0);
        part_explode_object_into_pieces_pal(moby, g_burst_piece_params_d, g_burst_piece_params_b, g_burst_piece_params_a, 0xFFFF, 0,
                          g_burst_piece_effect_id, 1, 0x1FE, 0xFF, 0);
        vec_local_offset_to_world(moby, pos, g_burst_offset_x, g_burst_offset_y, g_burst_offset_z);
        SpawnExplosion_pal(pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, *(f32 *)(moby + 0x2C) * 20.0f, 20.0f,
                      1, 0, 1, 0);
        moby_mark_spawned(moby);
        break;
    }
}
