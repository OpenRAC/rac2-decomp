/* func_PAL_L00_003C64E8, the PAL copy of func_L00_003C27A0: the same C at 50 Hz (rates scaled by 6/5), with a
 * saved Z at 0x1FB4 passed to func_002AEE70 where USA v1.01 passes -1.0f, and 7 for 8 in func_L00_00323448's call.
 * The same C as func_PAL_L02_003D3388.
 */
#include "common.h"

typedef int Rac2TI128 __attribute__((mode(TI)));

typedef struct Vec_L00_003C27A0 {
    Rac2TI128 v;
} Vec_L00_003C27A0;

typedef struct State_L00_003C27A0 {
    f32 home[4];        /* 0x00 */
    s32 group;          /* 0x10 */
    s32 group_b;        /* 0x14 */
    s32 x18;            /* 0x18 */
    f32 spin;           /* 0x1C */
    f32 x20;            /* 0x20 */
    f32 x24;            /* 0x24 */
    f32 x28;            /* 0x28 */
    f32 x2C;            /* 0x2C */
    f32 x30;            /* 0x30 */
    f32 x34;            /* 0x34 */
    f32 x38;            /* 0x38 */
    f32 x3C;            /* 0x3C */
    s32 gate;           /* 0x40 */
    f32 x44;            /* 0x44 */
    s32 spawn;          /* 0x48 */
    u8 *moby;           /* 0x4C */
    u8 pad50[0x58 - 0x50];
    f32 angle;          /* 0x58 */
    u8 pad5C[0x70 - 0x5C];
    u8 track[0x1FB0 - 0x70];    /* 0x70 */
    u8 *target;         /* 0x1FB0 */
    f32 base_z;         /* 0x1FB4 */
} State_L00_003C27A0;

extern s32 g_tutorial_points __attribute__((nosda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u16 **g_level_reloc_record;
extern u16 *g_turn_state_table[];
extern u8 *g_moby_array_base;
extern u8 *g_tie_matrix_table;
extern u8 *g_tie_table;
extern s16 g_tie_class_ids[];
extern Vec_L00_003C27A0 g_follower_color_table[] __attribute__((sda));
extern Vec_L00_003C27A0 g_follower_color_vec __attribute__((sda));
extern s32 g_follower_scatter_params[2] __attribute__((sda));
extern s32 g_follower_scatter_params_b[2] __attribute__((sda));

extern u8 *CreateMoby(s32);
extern void moby_init_child_from_parent(void *, void *);
extern void BuildObjectAttachmentTransforms(void *, void *, s32, s32, s32, s32, s32, s32);
extern void level_set_record_payload_by_key(void *, int, int, void *);
extern void vec_clear_128(void *);
extern float mat_fast_helper_a(float, float);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern void euler_rotation_basis(void *, void *);
extern float math_fabs(float);
extern void ScatterObjectPieces_pal(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern s32 math_random_int_range(s32, s32);
extern void part_spawn_bolt_pickups_pal(void *, s32, s32, s32, s32, s32, float);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern void part_spawn_random_spark_rays(char *, char *, float, float);
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern s32 PlayMobySound(s32, s32, void *);
extern void moby_mark_spawned(void *);
extern s32 math_fast_helper_a(void *, float);
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void moby_update_attached_transforms(void *, void *);

/* Per-frame update of the moby class 2503 object: it waits for its group, spawns a helper moby,
   then follows the target and blows up when hit (PAL: 50 Hz rates). */
void target_l00_follower_update_pal(u8 *self)
{
    State_L00_003C27A0 *state = *(State_L00_003C27A0 **)(self + 0x68);
    Vec_L00_003C27A0 cols[2];
    Vec_L00_003C27A0 here;
    u16 *id_ptr;
    u16 *find_ptr;
    u16 *clear_ptr;
    u16 *zero_ptr;
    u8 *tie_matrix;
    u8 *zero_matrix;
    u8 *tie_rec;
    u8 *spot;
    u8 *moby;
    s32 id;
    s32 i;

    if (state->gate >= 0 && g_tutorial_points != state->gate)
        return;
    switch (self[0x20]) {
    case 0:
        if (*(long long *)&state->group == -1)
            break;
        {
            u8 stamp = 0xFF;
            self[0x30] = stamp;
        }
        if (state->spawn != 0) {
            moby = CreateMoby(0xE9B);
            state->moby = moby;
            if (moby != 0) {
                moby_init_child_from_parent(moby, self);
                *(u16 *)(state->moby + 0x34) |= 0x41;
                *(u16 *)(state->moby + 0x34) |= 0x5000;
            }
        }
        BuildObjectAttachmentTransforms(self, state->track, 100, state->group_b, state->group, state->x18, 7, 0);
        if (g_current_map_index[0] == 2 && state->group_b != -1) {
            id_ptr = g_turn_state_table[state->group_b];
            do {
                id = *id_ptr & 0x7FFF;
                level_set_record_payload_by_key(state->track, 0, id, *(u8 **)(g_moby_array_base + (id << 8) + 0x68) + 0x50);
            } while ((s16)*id_ptr++ >= 0);
        }
        if (state->moby != 0) {
            vec_clear_128(state->moby + 0xF0);
            state->target = 0;
            for (find_ptr = g_level_reloc_record[state->group];
                 find_ptr != 0 && ((s16)find_ptr[-1] >= 0 || find_ptr == g_level_reloc_record[state->group]); find_ptr++) {
                tie_matrix = g_tie_matrix_table + ((*find_ptr & 0x7FFF) << 6);
                if (tie_matrix == 0)
                    break;
                tie_rec = g_tie_table + ((*find_ptr & 0x7FFF) << 5);
                if (g_tie_class_ids[tie_rec[0x1D]] == 0xAB6) {
                    state->target = tie_matrix;
                    break;
                }
            }
        }
        qcopy_nc(state->home, self + 0x10);
        state->home[3] = state->x44;
        state->base_z = *(f32 *)(self + 0x18);
        self[0x20] = 1;
        break;
    case 1:
        if (state->moby != 0 && (tie_matrix = state->target) != 0) {
            qcopy_nc(state->moby + 0x10, tie_matrix + 0x30);
            *(f32 *)(state->moby + 0xF8) = mat_fast_helper_a(*(f32 *)tie_matrix, *(f32 *)(tie_matrix + 4));
            if (part_find_owned_effect_slot(state->moby, 0x10000, 0) != 0) {
                *(f32 *)(state->moby + 0x2C) = *(f32 *)(*(u8 **)(state->moby + 0x24) + 0x24) * 1.35f;
                euler_rotation_basis(state->moby + 0xC0, state->moby + 0xF0);
                if (math_fabs(*(f32 *)(state->moby + 0xF8)) > 1.6f) {
                    qcopy_nc(&cols[0], g_follower_color_table);
                    qcopy_nc(&cols[1], &g_follower_color_vec);
                } else {
                    qcopy_nc(&cols[0], &g_follower_color_vec);
                    qcopy_nc(&cols[1], g_follower_color_table);
                }
                ScatterObjectPieces_pal(state->moby, cols, g_follower_scatter_params, g_follower_scatter_params_b, 0, 0, -1, 1, 0xFFFE, 0xFF, 0);
                part_spawn_bolt_pickups_pal(state->moby, 30, 50, 2, -1, math_random_int_range(3, 5), 0.0f);
                snd_play_from_class_bank(0, 0, state->moby, 0xE9B);
                here = *(Vec_L00_003C27A0 *)(self + 0x10);
                part_spawn_random_spark_rays((char *)state->moby, (char *)&here, 1.5f, 0.14000002f);
                SpawnExplosion_pal(state->moby + 0x10, 0, 25, 20, 20, 20, 45, 0, 0.85f, 20.0f, 1, 0, 0, 0);
                for (clear_ptr = g_level_reloc_record[state->group];
                     clear_ptr != 0 && ((s16)clear_ptr[-1] >= 0 || clear_ptr == g_level_reloc_record[state->group]); clear_ptr++) {
                    spot = g_tie_table + ((*clear_ptr & 0x7FFF) << 5);
                    if (spot == 0)
                        break;
                    spot[0x1C] = 0;
                }
                for (zero_ptr = g_level_reloc_record[state->group];
                     zero_ptr != 0 && ((s16)zero_ptr[-1] >= 0 || zero_ptr == g_level_reloc_record[state->group]); zero_ptr++) {
                    zero_matrix = g_tie_matrix_table + ((*zero_ptr & 0x7FFF) << 6);
                    if (zero_matrix == 0)
                        break;
                    for (i = 0; i < 3; i++) {
                        qzero_nc(zero_matrix);
                        zero_matrix += 16;
                    }
                }
                PlayMobySound(0, 0, state->moby);
                moby_mark_spawned(state->moby);
                moby_mark_spawned(self);
                return;
            }
        }
        if (math_fast_helper_a(state, 500.0f) == -1)
            return;
        if (state->x34 > 0.0f)
            math_update_wrapped_angle_offset(self, &state->x20, &state->x24, state->x30, state->x34 * 0.0003490659f, state->base_z);
        if (state->x3C > 0.0f)
            moby_scale_owner_words_by_angles(self, &state->x28, &state->x2C, state->x38 * 0.017453294f, state->x3C * 0.0003490659f,
                          0.0069813184f);
        *(f32 *)(self + 0xF8) = FastAddRotations(*(f32 *)(self + 0xF8), state->spin * 0.0003490659f);
        state->angle = FastAddRotations(state->angle, state->spin * 0.0003490659f);
        moby_update_attached_transforms(self, state->track);
        break;
    }
}
