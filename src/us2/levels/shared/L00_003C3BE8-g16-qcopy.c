/*
 * func_US2_L00_003C3BE8, the USA v2.00 copy of func_L00_003C27A0: the same C, with a saved Z at 0x1FB4
 * (vars->base_z = follower + 0x18 at setup) passed to func_002AEE70 where USA v1.01 passes -1.0f.
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
    s32 unk_18;            /* 0x18 */
    f32 spin;           /* 0x1C */
    f32 unk_20;            /* 0x20 */
    f32 unk_24;            /* 0x24 */
    f32 unk_28;            /* 0x28 */
    f32 unk_2C;            /* 0x2C */
    f32 unk_30;            /* 0x30 */
    f32 unk_34;            /* 0x34 */
    f32 unk_38;            /* 0x38 */
    f32 unk_3C;            /* 0x3C */
    s32 gate;           /* 0x40 */
    f32 unk_44;            /* 0x44 */
    s32 spawn;          /* 0x48 */
    u8 *child;           /* 0x4C */
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
extern void ScatterObjectPieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern s32 math_random_int_range(s32, s32);
extern void part_spawn_bolt_pickups(void *, s32, s32, s32, s32, s32, float);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern void part_spawn_random_spark_rays(char *, char *, float, float);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern s32 PlayMobySound(s32, s32, void *);
extern void moby_mark_spawned(void *);
extern s32 math_fast_helper_a(void *, float);
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void moby_update_attached_transforms(void *, void *);

/* Handler for a follower object: spawns its child, then turns on contact into a burst of scattered pieces, bolts and sparks, otherwise spins its parts (US2 copy of target_l00_follower_update). */
void target_l00_follower_update_us2(u8 *follower)
{
    State_L00_003C27A0 *vars = *(State_L00_003C27A0 **)(follower + 0x68);
    Vec_L00_003C27A0 cols[2];
    Vec_L00_003C27A0 here;
    u16 *turn_entry;
    u16 *group_entry;
    u16 *reset_entry;
    u16 *clear_entry;
    u8 *tie_matrix;
    u8 *matrix_row;
    u8 *tie_record;
    u8 *reset_record;
    u8 *child;
    s32 id;
    s32 i;

    if (vars->gate >= 0 && g_tutorial_points != vars->gate)
        return;
    switch (follower[0x20]) {
    case 0:
        if (*(long long *)&vars->group == -1)
            break;
        {
            u8 stamp = 0xFF;
            follower[0x30] = stamp;
        }
        if (vars->spawn != 0) {
            child = CreateMoby(0xE9B);
            vars->child = child;
            if (child != 0) {
                moby_init_child_from_parent(child, follower);
                *(u16 *)(vars->child + 0x34) |= 0x41;
                *(u16 *)(vars->child + 0x34) |= 0x5000;
            }
        }
        BuildObjectAttachmentTransforms(follower, vars->track, 100, vars->group_b, vars->group, vars->unk_18, 8, 0);
        if (g_current_map_index[0] == 2 && vars->group_b != -1) {
            turn_entry = g_turn_state_table[vars->group_b];
            do {
                id = *turn_entry & 0x7FFF;
                level_set_record_payload_by_key(vars->track, 0, id, *(u8 **)(g_moby_array_base + (id << 8) + 0x68) + 0x50);
            } while ((s16)*turn_entry++ >= 0);
        }
        if (vars->child != 0) {
            vec_clear_128(vars->child + 0xF0);
            vars->target = 0;
            for (group_entry = g_level_reloc_record[vars->group];
                 group_entry != 0 && ((s16)group_entry[-1] >= 0 || group_entry == g_level_reloc_record[vars->group]); group_entry++) {
                tie_matrix = g_tie_matrix_table + ((*group_entry & 0x7FFF) << 6);
                if (tie_matrix == 0)
                    break;
                tie_record = g_tie_table + ((*group_entry & 0x7FFF) << 5);
                if (g_tie_class_ids[tie_record[0x1D]] == 0xAB6) {
                    vars->target = tie_matrix;
                    break;
                }
            }
        }
        qcopy_nc(vars->home, follower + 0x10);
        vars->home[3] = vars->unk_44;
        vars->base_z = *(f32 *)(follower + 0x18);
        follower[0x20] = 1;
        break;
    case 1:
        if (vars->child != 0 && (tie_matrix = vars->target) != 0) {
            qcopy_nc(vars->child + 0x10, tie_matrix + 0x30);
            *(f32 *)(vars->child + 0xF8) = mat_fast_helper_a(*(f32 *)tie_matrix, *(f32 *)(tie_matrix + 4));
            if (part_find_owned_effect_slot(vars->child, 0x10000, 0) != 0) {
                *(f32 *)(vars->child + 0x2C) = *(f32 *)(*(u8 **)(vars->child + 0x24) + 0x24) * 1.35f;
                euler_rotation_basis(vars->child + 0xC0, vars->child + 0xF0);
                if (math_fabs(*(f32 *)(vars->child + 0xF8)) > 1.6f) {
                    qcopy_nc(&cols[0], g_follower_color_table);
                    qcopy_nc(&cols[1], &g_follower_color_vec);
                } else {
                    qcopy_nc(&cols[0], &g_follower_color_vec);
                    qcopy_nc(&cols[1], g_follower_color_table);
                }
                ScatterObjectPieces(vars->child, cols, g_follower_scatter_params, g_follower_scatter_params_b, 0, 0, -1, 1, 0xFFFE, 0xFF, 0);
                part_spawn_bolt_pickups(vars->child, 30, 50, 2, -1, math_random_int_range(3, 5), 0.0f);
                snd_play_from_class_bank(0, 0, vars->child, 0xE9B);
                here = *(Vec_L00_003C27A0 *)(follower + 0x10);
                part_spawn_random_spark_rays((char *)vars->child, (char *)&here, 1.5f, 0.116666675f);
                SpawnExplosion(vars->child + 0x10, 0, 25, 20, 20, 20, 45, 0, 0.85f, 20.0f, 1, 0, 0, 0);
                for (reset_entry = g_level_reloc_record[vars->group];
                     reset_entry != 0 && ((s16)reset_entry[-1] >= 0 || reset_entry == g_level_reloc_record[vars->group]); reset_entry++) {
                    reset_record = g_tie_table + ((*reset_entry & 0x7FFF) << 5);
                    if (reset_record == 0)
                        break;
                    reset_record[0x1C] = 0;
                }
                for (clear_entry = g_level_reloc_record[vars->group];
                     clear_entry != 0 && ((s16)clear_entry[-1] >= 0 || clear_entry == g_level_reloc_record[vars->group]); clear_entry++) {
                    matrix_row = g_tie_matrix_table + ((*clear_entry & 0x7FFF) << 6);
                    if (matrix_row == 0)
                        break;
                    for (i = 0; i < 3; i++) {
                        qzero_nc(matrix_row);
                        matrix_row += 16;
                    }
                }
                PlayMobySound(0, 0, vars->child);
                moby_mark_spawned(vars->child);
                moby_mark_spawned(follower);
                return;
            }
        }
        if (math_fast_helper_a(vars, 500.0f) == -1)
            return;
        if (vars->unk_34 > 0.0f)
            math_update_wrapped_angle_offset(follower, &vars->unk_20, &vars->unk_24, vars->unk_30, vars->unk_34 * 0.000290888245f, vars->base_z);
        if (vars->unk_3C > 0.0f)
            moby_scale_owner_words_by_angles(follower, &vars->unk_28, &vars->unk_2C, vars->unk_38 * 0.017453294f, vars->unk_3C * 0.000290888245f,
                          0.0058177654f);
        *(f32 *)(follower + 0xF8) = FastAddRotations(*(f32 *)(follower + 0xF8), vars->spin * 0.000290888245f);
        vars->angle = FastAddRotations(vars->angle, vars->spin * 0.000290888245f);
        moby_update_attached_transforms(follower, vars->track);
        break;
    }
}
