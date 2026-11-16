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

void func_PAL_L12_0042EE58(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    s32 life;
    u8 *obj;
    u16 flags;
    f32 v[4];

    int state = a0[0x20];

    switch (state) {
    case 0:
        *(s16 *)((u8 *)s + 0x34) = ((s32)(math_random_int_range(20, 50)) * 5 + 2) / 6;
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        life = *(s16 *)((u8 *)s + 0x34);
        if (life < 0 || cam_moby_update_pal(a0)) {
            matrix_mul_vec3(v, (u8 *)s + 0x20, a0 + 0xC0);
            obj = 0;
            FastVecAdd(v, a0 + 0x10, v);
            SpawnExplosion_pal(v, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, state, state, 0, 0);
            snd_play_from_class_bank(2, 0, a0, 0x12B1);
            flags = *(u16 *)(a0 + 0x7C);
            if (flags & 1)
                obj = CreateMoby(0x12E0);
            else if (flags & 2)
                obj = CreateMoby(0x12E1);
            else if (flags & 4)
                obj = CreateMoby(0x12E2);
            if (obj != 0) {
                qcopy(obj + 0x10, v);
                *(f32 *)(obj + 0x2C) = *(f32 *)(*(u8 **)(obj + 0x24) + 0x24) *
                                       (*(f32 *)(a0 + 0x2C) / *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24));
                mem_copy_aligned(obj + 0xC0, a0 + 0xC0, 0x18);
                part_explode_object_into_pieces_pal(obj, g_explosion_piece_offsets, g_explosion_piece_table_b, g_explosion_piece_table_c, 0xFF, -1,
                                  g_explosion_piece_effect, 0xF, 0xFF, 0xFF, 0);
                moby_mark_spawned(obj);
            }
            moby_mark_spawned(a0);
        } else {
            *(s16 *)((u8 *)s + 0x34) = life - 1;
        }
        break;
    }
}
