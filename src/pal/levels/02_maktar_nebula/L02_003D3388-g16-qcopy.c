/*
 * func_PAL_L02_003D3388, the PAL copy of func_L00_003C27A0: the same C at 50 Hz (rates scaled by 6/5), with a
 * saved Z at 0x1FB4 passed to func_002AEE70 where USA v1.01 passes -1.0f, and 7 for 8 in func_L00_00323448's call.
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

/* A target follower that waits for its tutorial point, then bursts into pieces, bolts and sparks and removes its group of tie objects; before that it spins and follows its parent (PAL: 50 Hz rates). */
void target_l02_follower_update_pal(u8 *self)
{
    State_L00_003C27A0 *vars = *(State_L00_003C27A0 **)(self + 0x68);
    Vec_L00_003C27A0 cols[2];
    Vec_L00_003C27A0 here;
    u16 *turn_ref;
    u16 *group_ref;
    u16 *hide_ref;
    u16 *clear_ref;
    u8 *tie_matrix;
    u8 *clear_matrix;
    u8 *tie_record;
    u8 *tie_entry;
    u8 *moby;
    s32 id;
    s32 i;

    if (vars->gate >= 0 && g_tutorial_points != vars->gate)
        return;
    switch (self[0x20]) {
    case 0:
        if (*(long long *)&vars->group == -1)
            break;
        {
            u8 stamp = 0xFF;
            self[0x30] = stamp;
        }
        if (vars->spawn != 0) {
            moby = CreateMoby(0xE9B);
            vars->moby = moby;
            if (moby != 0) {
                moby_init_child_from_parent(moby, self);
                *(u16 *)(vars->moby + 0x34) |= 0x41;
                *(u16 *)(vars->moby + 0x34) |= 0x5000;
            }
        }
        BuildObjectAttachmentTransforms(self, vars->track, 100, vars->group_b, vars->group, vars->x18, 7, 0);
        if (g_current_map_index[0] == 2 && vars->group_b != -1) {
            turn_ref = g_turn_state_table[vars->group_b];
            do {
                id = *turn_ref & 0x7FFF;
                level_set_record_payload_by_key(vars->track, 0, id, *(u8 **)(g_moby_array_base + (id << 8) + 0x68) + 0x50);
            } while ((s16)*turn_ref++ >= 0);
        }
        if (vars->moby != 0) {
            vec_clear_128(vars->moby + 0xF0);
            vars->target = 0;
            for (group_ref = g_level_reloc_record[vars->group];
                 group_ref != 0 && ((s16)group_ref[-1] >= 0 || group_ref == g_level_reloc_record[vars->group]); group_ref++) {
                tie_matrix = g_tie_matrix_table + ((*group_ref & 0x7FFF) << 6);
                if (tie_matrix == 0)
                    break;
                tie_record = g_tie_table + ((*group_ref & 0x7FFF) << 5);
                if (g_tie_class_ids[tie_record[0x1D]] == 0xAB6) {
                    vars->target = tie_matrix;
                    break;
                }
            }
        }
        qcopy_nc(vars->home, self + 0x10);
        vars->home[3] = vars->x44;
        vars->base_z = *(f32 *)(self + 0x18);
        self[0x20] = 1;
        break;
    case 1:
        if (vars->moby != 0 && (tie_matrix = vars->target) != 0) {
            qcopy_nc(vars->moby + 0x10, tie_matrix + 0x30);
            *(f32 *)(vars->moby + 0xF8) = mat_fast_helper_a(*(f32 *)tie_matrix, *(f32 *)(tie_matrix + 4));
            if (part_find_owned_effect_slot(vars->moby, 0x10000, 0) != 0) {
                *(f32 *)(vars->moby + 0x2C) = *(f32 *)(*(u8 **)(vars->moby + 0x24) + 0x24) * 1.35f;
                euler_rotation_basis(vars->moby + 0xC0, vars->moby + 0xF0);
                if (math_fabs(*(f32 *)(vars->moby + 0xF8)) > 1.6f) {
                    qcopy_nc(&cols[0], g_follower_color_table);
                    qcopy_nc(&cols[1], &g_follower_color_vec);
                } else {
                    qcopy_nc(&cols[0], &g_follower_color_vec);
                    qcopy_nc(&cols[1], g_follower_color_table);
                }
                ScatterObjectPieces_pal(vars->moby, cols, g_follower_scatter_params, g_follower_scatter_params_b, 0, 0, -1, 1, 0xFFFE, 0xFF, 0);
                part_spawn_bolt_pickups_pal(vars->moby, 30, 50, 2, -1, math_random_int_range(3, 5), 0.0f);
                snd_play_from_class_bank(0, 0, vars->moby, 0xE9B);
                here = *(Vec_L00_003C27A0 *)(self + 0x10);
                part_spawn_random_spark_rays((char *)vars->moby, (char *)&here, 1.5f, 0.14000002f);
                SpawnExplosion_pal(vars->moby + 0x10, 0, 25, 20, 20, 20, 45, 0, 0.85f, 20.0f, 1, 0, 0, 0);
                for (hide_ref = g_level_reloc_record[vars->group];
                     hide_ref != 0 && ((s16)hide_ref[-1] >= 0 || hide_ref == g_level_reloc_record[vars->group]); hide_ref++) {
                    tie_entry = g_tie_table + ((*hide_ref & 0x7FFF) << 5);
                    if (tie_entry == 0)
                        break;
                    tie_entry[0x1C] = 0;
                }
                for (clear_ref = g_level_reloc_record[vars->group];
                     clear_ref != 0 && ((s16)clear_ref[-1] >= 0 || clear_ref == g_level_reloc_record[vars->group]); clear_ref++) {
                    clear_matrix = g_tie_matrix_table + ((*clear_ref & 0x7FFF) << 6);
                    if (clear_matrix == 0)
                        break;
                    for (i = 0; i < 3; i++) {
                        qzero_nc(clear_matrix);
                        clear_matrix += 16;
                    }
                }
                PlayMobySound(0, 0, vars->moby);
                moby_mark_spawned(vars->moby);
                moby_mark_spawned(self);
                return;
            }
        }
        if (math_fast_helper_a(vars, 500.0f) == -1)
            return;
        if (vars->x34 > 0.0f)
            math_update_wrapped_angle_offset(self, &vars->x20, &vars->x24, vars->x30, vars->x34 * 0.0003490659f, vars->base_z);
        if (vars->x3C > 0.0f)
            moby_scale_owner_words_by_angles(self, &vars->x28, &vars->x2C, vars->x38 * 0.017453294f, vars->x3C * 0.0003490659f,
                          0.0069813184f);
        *(f32 *)(self + 0xF8) = FastAddRotations(*(f32 *)(self + 0xF8), vars->spin * 0.0003490659f);
        vars->angle = FastAddRotations(vars->angle, vars->spin * 0.0003490659f);
        moby_update_attached_transforms(self, vars->track);
        break;
    }
}
