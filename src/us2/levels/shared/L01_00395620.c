#include "common.h"

/* func_US2_L01_00395620, the USA v2.00 copy of func_L01_00394240
   (L01_002A7248-cam.c): the same C, plus two calls of this level's
   ref_L01_00394240_02(0x6F, 1) (func_US2_L01_002BEEA8 in Oozla, a per-level
   function): after the second trigger's save-slot update and before the
   camera update in state 2. That function returns a value on every path
   (`daddu $v0,$zero,$zero` on its early exits), so it is declared int; the
   ignored result is what puts the lock flag in $v1 after the first call.

   func_L01_00394240 has a unit of its own because it calls func_L01_00394148
   with the moby, which that function's (void) definition in L01_002A7248.c
   does not accept. func_L01_00394148 is this level's copy of the helper
   func_L04_00423178(object), which tests kinds instead of the object's id, so
   its parameter went unused. Retail still sets up the call: the move of the
   moby into $a0 takes the issue slot beside `sd $s3` and is deleted after
   scheduling ($a0 already holds it). That puts `li $s2,1` after `sd $s4`. */
typedef int MotionQuad __attribute__((mode(TI)));
typedef union { float v[4]; MotionQuad q; } MotionVec;
typedef struct { MotionVec forward[4]; MotionVec inverse[4]; } MotionPath;
extern MotionPath *g_swamp_patrol_positions[] __attribute__((sda));
extern char g_level_origin_vec[];
extern char g_hero_position[];
extern void part_flash_matching_things(void *); /* the parameter is unused */

typedef int CamQuad __attribute__((mode(TI)));
typedef struct {
    CamQuad position, rotation;
    int trigger, cam_index, source, timer, mode, parameter;
    u8 reset, require_enabled, require_hero, lock;
} CamVars;
typedef struct {
    char pad0[0x20]; u8 state; char pad21[0xF]; u8 field30; char pad31; u16 field32;
    char pad34[0x34]; CamVars *vars; char pad6C[0x3E]; s16 id; u16 group;
    char padAE[2]; u8 index; char padB1; u16 save_index; char padB4[8]; u8 active;
} CamMoby;
extern u8 g_moby_group_flags[];
extern int g_current_map_index[] __attribute__((sda));
extern u8 g_moby_nibble_table[];
extern struct { u8 header[0x464]; u8 collected[0]; } g_level_save_state_backup;
extern int g_controller_active NOT_SDA;
extern int ref_L01_00394240_00 MACRO_ADDR;
extern int g_camera_lock_flag[] __attribute__((sda));
extern struct {
    s16 f0, f2, f4, pad6;
    s32 busy;
} D_L01_001B22A0 MACRO_ADDR;
extern int g_camera_reset_flag NOT_SDA;
extern char g_str_moby_debug_format[];
extern void STUB_printf(void *, int, int);
extern void moby_mark_spawned(void *);
extern int IsPointInCuboid(void *, int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void SetCamera5Pose(void *, void *, int, int, int);
extern int flag_is_third_pending_set(void *);
extern int math_fast_float_d(void *);
extern void cam_set_mode_state(int);
extern void ref_L01_00394240_01(int);
extern int ref_L01_00394240_02(int, int); /* result unused here */
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *, void *);
/* Camera trigger: when Ratchet is inside the trigger box it takes over the camera until the timer ends, then resets it (USA v2.00). */
void camera_pose_trigger_update_us2(CamMoby *moby)
{
    CamVars *vars = moby->vars;
    CamQuad position, rotation;
    int saved;
    part_flash_matching_things(moby);
    switch (moby->state) {
    case 0:
        if (vars->require_enabled && (g_moby_group_flags[moby->index + (ref_L01_00394240_00 << 4)] & 0x80)) {
            moby_mark_spawned(moby);
        } else if (vars->cam_index == -1) {
            STUB_printf(g_str_moby_debug_format, moby->id, moby->group);
            moby_mark_spawned(moby);
        } else {
            moby->field30 = moby->field32 = 255;
            moby->state = 1;
        }
        break;
    case 1:
        if (g_level_save_state_backup.collected[(s16)moby->save_index]) goto saved_state;
        saved = g_moby_nibble_table[((s16)moby->save_index >> 1) + (g_current_map_index[0] << 10)];
        if (moby->save_index & 1) {
            if ((saved >> 4) & 7) goto saved_state;
        } else {
            if (saved & 7) {
            saved_state:
                moby->state = 1;
                break;
            }
        }
        if ((IsPointInCuboid(g_hero_position, vars->trigger) || moby->active == 1) &&
            (!vars->require_hero || *(int *)(g_hero_position + 0x2C0))) {
            qcopy(&position, g_level_origin_vec);
            qcopy(&rotation, g_level_origin_vec + 16);
            if (vars->source == -1) hero_reset_position_and_direction(g_hero_position, g_hero_position + 0x10, 0x6F, 1);
            else hero_reset_position_and_direction(&g_swamp_patrol_positions[0][vars->source].forward[3],
                                  &g_swamp_patrol_positions[0][vars->source].inverse[3], 0x6F, 1);
            if (vars->mode) SetCamera5Pose(&position, &rotation, 2, vars->parameter, 0);
            else SetCamera5Pose(&g_swamp_patrol_positions[0][vars->cam_index].forward[3],
                              &g_swamp_patrol_positions[0][vars->cam_index].inverse[3], 0, 0, 0);
            g_camera_lock_flag[0] = 1;
            moby->state = 2;
            moby->active = 1;
            if (vars->lock) g_cutscene_trigger_state.busy = 1;
            { int cam_index = vars->cam_index; MotionPath *base = g_swamp_patrol_positions[0];
            qcopy(&vars->position, &base[cam_index].forward[3]);
            qcopy(&vars->rotation, &base[cam_index].inverse[3]); }
        }
        if (g_current_map_index[0] == 19 &&
            (IsPointInCuboid(g_hero_position, vars->trigger) || moby->active == 1 || flag_is_third_pending_set(moby)) &&
            (!vars->require_hero || g_controller_active)) {
            qcopy(&position, g_level_origin_vec);
            qcopy(&rotation, g_level_origin_vec + 16);
            if (vars->source == -1) hero_reset_position_and_direction(g_hero_position, g_hero_position + 0x10, 0x6F, 1);
            else hero_reset_position_and_direction(&g_swamp_patrol_positions[0][vars->source].forward[3],
                                  &g_swamp_patrol_positions[0][vars->source].inverse[3], 0x6F, 1);
            if (vars->mode) SetCamera5Pose(&position, &rotation, 2, vars->parameter, 0);
            else if (g_current_map_index[0] == 19) SetCamera5Pose(&g_swamp_patrol_positions[0][vars->cam_index].forward[3],
                                                 &g_swamp_patrol_positions[0][vars->cam_index].inverse[3], 1, 0, 0);
            else SetCamera5Pose(&g_swamp_patrol_positions[0][vars->cam_index].forward[3],
                              &g_swamp_patrol_positions[0][vars->cam_index].inverse[3], 0, 0, 0);
            { unsigned int save_index = moby->save_index;
            u8 *p;
            u8 b;
            g_camera_lock_flag[0] = 1;
            moby->active = 1;
            moby->state = 2;
            if (save_index & 1) {
                p = &g_moby_nibble_table[((s16)save_index >> 1) + (g_current_map_index[0] << 10)];
                b = *p;
                if (((b >> 4) & 7) != 7) *p = b + 16;
            } else {
                p = &g_moby_nibble_table[((s16)save_index >> 1) + (g_current_map_index[0] << 10)];
                b = *p;
                if ((b & 7) != 7) *p = b + 1;
            } }
            ref_L01_00394240_02(0x6F, 1);
            if (vars->lock) g_cutscene_trigger_state.busy = 1;
            { int cam_index = vars->cam_index; MotionPath *base = g_swamp_patrol_positions[0];
            qcopy(&vars->position, &base[cam_index].forward[3]);
            qcopy(&vars->rotation, &base[cam_index].inverse[3]); }
        }
        break;
    case 2:
        if (math_fast_float_d(&vars->timer) || moby->active != 1) {
            if (vars->mode) cam_set_mode_state(2);
            else cam_set_mode_state(0);
            ref_L01_00394240_01(0);
            if (vars->lock) g_cutscene_trigger_state.busy = 0;
            g_camera_lock_flag[0] = 0;
            g_camera_reset_flag = 0;
            moby->state = 3;
            moby->active = 0;
        } else {
            if (vars->lock) g_cutscene_trigger_state.busy = 1;
            ref_L01_00394240_02(0x6F, 1);
            object_copy_vector_to_selected(&vars->position);
            cam_set_state_rotation(&vars->rotation);
        }
        break;
    case 3:
        if (vars->reset && !(g_moby_group_flags[moby->index + (ref_L01_00394240_00 << 4)] & 0x80)) {
            moby_mark_table_entry_flagged(moby->index);
            level_capture_checkpoint_state((char *)moby + 0x10, (char *)moby + 0xF0);
        }
        if (moby->active == 1) moby->state = 1;
        break;
    }
}
