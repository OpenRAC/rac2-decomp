#include "include_asm.h"

#include "common.h"
extern f32 g_burst_piece_params_a[] SDATA(D_L12_001B1F50);
extern f32 g_burst_piece_params_b[] SDATA(D_L12_001B1F58);
extern f32 g_burst_piece_params_c[] SDATA(D_L12_001B1F60);
extern s32 g_burst_piece_effect_id __attribute__((sda));
extern f32 g_burst_offset_x __attribute__((sda));
extern f32 g_burst_offset_y __attribute__((nosda));
extern f32 g_burst_offset_z __attribute__((nosda));
extern void moby_set_state(void *, int, int);
extern s32 PlayMobySound(s32, s32, s32);
extern void moby_mark_spawned(void *);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, unsigned char, int);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern u8 *g_moby_list_start MACRO_ADDR;
extern s32 g_frame_l12_counter __attribute__((sda));
extern u8 *g_tracked_object_ptr __attribute__((nosda));
extern u8 *g_second_tracked_object __attribute__((nosda));
extern s32 g_explosion_piece_effect __attribute__((sda));
extern f32 g_explosion_piece_table_c[] SDATA(D_L12_001B2280);
extern f32 g_explosion_piece_table_b[] SDATA(D_L12_001B2288);
extern f32 g_explosion_piece_offsets[] SDATA(D_L12_001B22B0);
extern int math_random_int_range(int, int);
extern int cam_moby_update_pal(unsigned char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern u8 *CreateMoby(int);
extern void mem_copy_aligned(void *, void *, int);

/* Counts down a short timer, then blows up with an explosion and sound and drops a smaller piece of debris (PAL: 50 Hz timings). */
void timed_explosion_debris_update_pal(u8 *moby)
{
    s32 *vars = *(s32 **)(moby + 0x68);
    s32 life;
    u8 *piece;
    u16 hit_flags;
    f32 blast_pos[4];

    int state = moby[0x20];

    switch (state) {
    case 0:
        *(s16 *)((u8 *)vars + 0x34) = ((s32)(math_random_int_range(20, 50)) * 5 + 2) / 6;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        life = *(s16 *)((u8 *)vars + 0x34);
        if (life < 0 || cam_moby_update_pal(moby)) {
            matrix_mul_vec3(blast_pos, (u8 *)vars + 0x20, moby + 0xC0);
            piece = 0;
            FastVecAdd(blast_pos, moby + 0x10, blast_pos);
            SpawnExplosion_pal(blast_pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, state, state, 0, 0);
            snd_play_from_class_bank(2, 0, moby, 0x12B1);
            hit_flags = *(u16 *)(moby + 0x7C);
            if (hit_flags & 1)
                piece = CreateMoby(0x12E0);
            else if (hit_flags & 2)
                piece = CreateMoby(0x12E1);
            else if (hit_flags & 4)
                piece = CreateMoby(0x12E2);
            if (piece != 0) {
                qcopy(piece + 0x10, blast_pos);
                *(f32 *)(piece + 0x2C) = *(f32 *)(*(u8 **)(piece + 0x24) + 0x24) *
                                       (*(f32 *)(moby + 0x2C) / *(f32 *)(*(u8 **)(moby + 0x24) + 0x24));
                mem_copy_aligned(piece + 0xC0, moby + 0xC0, 0x18);
                part_explode_object_into_pieces_pal(piece, g_explosion_piece_offsets, g_explosion_piece_table_b, g_explosion_piece_table_c, 0xFF, -1,
                                  g_explosion_piece_effect, 0xF, 0xFF, 0xFF, 0);
                moby_mark_spawned(piece);
            }
            moby_mark_spawned(moby);
        } else {
            *(s16 *)((u8 *)vars + 0x34) = life - 1;
        }
        break;
    }
}
