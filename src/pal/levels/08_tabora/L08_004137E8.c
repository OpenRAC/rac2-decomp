#include "include_asm.h"

#include "common.h"
extern void moby_mark_spawned(void *);
extern u8 g_hero_position_vec[];
extern f32 fast_vec_dist(void *, void *);
extern f32 IntToFloat(int);
extern f32 math_fabs(f32);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
typedef struct {
    u8 pad00[0x20];
    u8 unk_20;
    u8 unk_21;
    u8 pad22[0x24 - 0x22];
    void *unk_24;
    u8 pad28[0x2C - 0x28];
    f32 unk_2C;
    u8 pad30[0x68 - 0x30];
    void *unk_68;
    u8 pad6C[0x95 - 0x6C];
    u8 unk_95;
    u16 unk_96;
    u8 pad98[0xBC - 0x98];
    u8 unk_BC;
    u8 padBD[0x100 - 0xBD];
} Ent;
typedef struct {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
    f32 unk_C;
} Quad;
extern s32 func_2F9A60();
extern s32 func_327898(s32, s32);
extern s32 func_2EA300(void *, void *, s32, s32, s32);
extern s32 func_3357E8(Ent *, void *, s32);
extern f32 func_3278F0(f32, f32);
extern f32 func_2FA3C8(f32);
extern f32 func_2FA3E0(f32);
extern f32 g_ground_height_result;
extern f32 g_hero_height_limit;
extern char g_hero_position[];
extern f32 coll_find_ground_height(Quad *, f32, f32, f32, f32);
extern float math_fabs(float);
extern void moby_set_state(void *, s32, s32);
extern u8 g_inventory_have_flags[] __attribute__((sda));
extern u8 g_request_l08_queue[];
extern s32 g_cutscene_l08_active_flag[] __attribute__((sda));
extern s32 g_glider_flag_table[] __attribute__((sda));
extern u8 *g_collision_box_table[] __attribute__((sda));
extern s32 IsPointInCuboid(void *, s32);
extern s32 req_push_queue(void *, s32);
extern s32 req_launch_queued(void *);
extern void part_spawn_sparkles_and_glow_rings_pal(u8 *);
extern s32 game_is_either_mode_two(void);
extern void hero_reset_position_and_direction_pal(u8 *, u8 *, s32, s32);
extern void help_unlock_entry(s32);
extern void value_set_entry_by_index_pal(s32, s32);
extern int MemcardSave(s32, s32);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern f32 math_random_angle(void);
extern s32 math_random_int_range(s32, s32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);

/* Updates the Glider moby (class 3675): it rises into place, turns slowly, and when the hero is near it plays a sound and removes itself (PAL version). */
void glider_update_pal(u8 *self) {
    u8 *state = *(u8 **)(self + 0x68);
    u8 *box_entry;

    switch (self[0x20]) {
    case 0:
        if (g_inventory_have_flags[13] != 0) {
            moby_mark_spawned(self);
            break;
        }
        *(float *)(self + 0x18) = *(float *)(self + 0x18) + 0.75f;
        *(float *)(self + 0x2C) = *(float *)(*(u8 **)(self + 0x24) + 0x24) * 1.5f;
        moby_set_state(self, 1, -1);
        break;
    case 1:
        *(float *)(self + 0xF8) = FastAddRotations(*(float *)(self + 0xF8), 0.094247796f);
        if (IsPointInCuboid(g_hero_position, *(s32 *)(state + 4)) != 0) {
            if (req_push_queue(g_request_l08_queue, 0x5B) != 0) {
                req_launch_queued(g_request_l08_queue);
                self[0x20] = 2;
            }
        }
        if (self[0x31] != 0)
            part_spawn_sparkles_and_glow_rings_pal(self);
        break;
    case 2:
        g_glider_flag_table[10] = 1;
        if (g_cutscene_l08_active_flag[0] == 2) {
            self[0x31] = 0;
            *(u16 *)(self + 0x34) |= 1;
        }
        if (game_is_either_mode_two() != 0)
            break;
        g_glider_flag_table[10] = 0;
        self[0x31] = 1;
        box_entry = g_collision_box_table[0];
        *(u16 *)(self + 0x34) &= 0xFFFE;
        box_entry += *(s32 *)(state + 8) * 0x80;
        hero_reset_position_and_direction_pal(box_entry + 0x30, box_entry + 0x70, 0, 1);
        help_unlock_entry(0x15);
        value_set_entry_by_index_pal(0x122B, -1);
        MemcardSave(0, -1);
        moby_mark_spawned(self);
        break;
    }
}


