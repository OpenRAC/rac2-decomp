#include "include_asm.h"

#include "common.h"

/* func_PAL_L01_00397578, the PAL copy of func_L01_00394240 (L01_002A7248-cam.c): the same
   C, where switching the camera on rescales its timer to 50 Hz, and the trigger taken
   when D_001A79F0[0] is 19 and every frame of the running camera also call
   func_PAL_L01_002BEC60(0x6F, 1)
   (ref_PAL_L01_00397578_00: that function's copy in each level, which returns a value
   nobody reads). As in USA, func_L01_00394148 is called with the moby although its
   parameter went unused: it is this level's copy of func_L04_00423178(object), which
   tests kinds instead of the object's id. Retail still sets up the call: the move of the
   moby into $a0 takes the issue slot beside `sd $s3` and is deleted after scheduling
   ($a0 already holds it). That puts `li $s2,1` after `sd $s4`. */
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
    int trigger, camera, source, timer, mode, parameter;
    u8 reset, requireEnabled, requireHero, lock;
} CamVars;
typedef struct {
    char pad0[0x20]; u8 state; char pad21[0xF]; u8 field30; char pad31; u16 field32;
    char pad34[0x34]; CamVars *vars; char pad6C[0x3E]; s16 id; u16 group;
    char padAE[2]; u8 index; char padB1; u16 saveIndex; char padB4[8]; u8 active;
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
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern void SetCamera5Pose(void *, void *, int, int, int);
extern int flag_is_third_pending_set(void *);
extern int math_fast_float_d(void *);
extern void cam_set_mode_state(int);
extern void ref_L01_00394240_01(int);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *, void *);
extern int ref_PAL_L01_00397578_00(int, int);
void func_PAL_L01_00397578(CamMoby *m)
{
    CamVars *v = m->vars;
    CamQuad position, rotation;
    int saved;
    part_flash_matching_things(m);
    switch (m->state) {
    case 0:
        if (v->requireEnabled && (g_moby_group_flags[m->index + (ref_L01_00394240_00 << 4)] & 0x80)) {
            moby_mark_spawned(m);
        } else if (v->camera == -1) {
            STUB_printf(g_str_moby_debug_format, m->id, m->group);
            moby_mark_spawned(m);
        } else {
            v->timer = ((s32)(v->timer) * 5 + 2) / 6;
            m->field30 = m->field32 = 255;
            m->state = 1;
        }
        break;
    case 1:
        if (g_level_save_state_backup.collected[(s16)m->saveIndex]) goto saved_state;
        saved = g_moby_nibble_table[((s16)m->saveIndex >> 1) + (g_current_map_index[0] << 10)];
        if (m->saveIndex & 1) {
            if ((saved >> 4) & 7) goto saved_state;
        } else {
            if (saved & 7) {
            saved_state:
                m->state = 1;
                break;
            }
        }
        if ((IsPointInCuboid(g_hero_position, v->trigger) || m->active == 1) &&
            (!v->requireHero || *(int *)(g_hero_position + 0x2C0))) {
            qcopy(&position, g_level_origin_vec);
            qcopy(&rotation, g_level_origin_vec + 16);
            if (v->source == -1) hero_reset_position_and_direction_pal(g_hero_position, g_hero_position + 0x10, 0x6F, 1);
            else hero_reset_position_and_direction_pal(&g_swamp_patrol_positions[0][v->source].forward[3],
                                  &g_swamp_patrol_positions[0][v->source].inverse[3], 0x6F, 1);
            if (v->mode) SetCamera5Pose(&position, &rotation, 2, v->parameter, 0);
            else SetCamera5Pose(&g_swamp_patrol_positions[0][v->camera].forward[3],
                              &g_swamp_patrol_positions[0][v->camera].inverse[3], 0, 0, 0);
            g_camera_lock_flag[0] = 1;
            m->state = 2;
            m->active = 1;
            if (v->lock) g_cutscene_trigger_state.busy = 1;
            { int camera = v->camera; MotionPath *base = g_swamp_patrol_positions[0];
            qcopy(&v->position, &base[camera].forward[3]);
            qcopy(&v->rotation, &base[camera].inverse[3]); }
        }
        if (g_current_map_index[0] == 19 &&
            (IsPointInCuboid(g_hero_position, v->trigger) || m->active == 1 || flag_is_third_pending_set(m)) &&
            (!v->requireHero || g_controller_active)) {
            qcopy(&position, g_level_origin_vec);
            qcopy(&rotation, g_level_origin_vec + 16);
            if (v->source == -1) hero_reset_position_and_direction_pal(g_hero_position, g_hero_position + 0x10, 0x6F, 1);
            else hero_reset_position_and_direction_pal(&g_swamp_patrol_positions[0][v->source].forward[3],
                                  &g_swamp_patrol_positions[0][v->source].inverse[3], 0x6F, 1);
            if (v->mode) SetCamera5Pose(&position, &rotation, 2, v->parameter, 0);
            else if (g_current_map_index[0] == 19) SetCamera5Pose(&g_swamp_patrol_positions[0][v->camera].forward[3],
                                                 &g_swamp_patrol_positions[0][v->camera].inverse[3], 1, 0, 0);
            else SetCamera5Pose(&g_swamp_patrol_positions[0][v->camera].forward[3],
                              &g_swamp_patrol_positions[0][v->camera].inverse[3], 0, 0, 0);
            { unsigned int saveIndex = m->saveIndex;
            u8 *p;
            u8 b;
            g_camera_lock_flag[0] = 1;
            m->active = 1;
            m->state = 2;
            if (saveIndex & 1) {
                p = &g_moby_nibble_table[((s16)saveIndex >> 1) + (g_current_map_index[0] << 10)];
                b = *p;
                if (((b >> 4) & 7) != 7) *p = b + 16;
            } else {
                p = &g_moby_nibble_table[((s16)saveIndex >> 1) + (g_current_map_index[0] << 10)];
                b = *p;
                if ((b & 7) != 7) *p = b + 1;
            } }
            ref_PAL_L01_00397578_00(0x6F, 1);
            if (v->lock) g_cutscene_trigger_state.busy = 1;
            { int camera = v->camera; MotionPath *base = g_swamp_patrol_positions[0];
            qcopy(&v->position, &base[camera].forward[3]);
            qcopy(&v->rotation, &base[camera].inverse[3]); }
        }
        break;
    case 2:
        if (math_fast_float_d(&v->timer) || m->active != 1) {
            if (v->mode) cam_set_mode_state(2);
            else cam_set_mode_state(0);
            ref_L01_00394240_01(0);
            if (v->lock) g_cutscene_trigger_state.busy = 0;
            g_camera_lock_flag[0] = 0;
            g_camera_reset_flag = 0;
            m->state = 3;
            m->active = 0;
        } else {
            if (v->lock) g_cutscene_trigger_state.busy = 1;
            ref_PAL_L01_00397578_00(0x6F, 1);
            object_copy_vector_to_selected(&v->position);
            cam_set_state_rotation(&v->rotation);
        }
        break;
    case 3:
        if (v->reset && !(g_moby_group_flags[m->index + (ref_L01_00394240_00 << 4)] & 0x80)) {
            moby_mark_table_entry_flagged(m->index);
            level_capture_checkpoint_state((char *)m + 0x10, (char *)m + 0xF0);
        }
        if (m->active == 1) m->state = 1;
        break;
    }
}

extern int g_screen_width[] MACRO_ADDR;
extern int g_tile_int_table[];
extern float IntToFloat(s32);
extern u64 GetEffectTextureDescriptor(s32);
extern int FloatToInt(float);
extern s32 math_random_int_below(s32);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, s64, u64);

/* Tiles an alpha-blended texture over the current viewport. */
void func_PAL_L01_0039A174(void *actor) {
    char *state = *(char **)((char *)actor + 0x68);
    u64 texture;
    int color;
    int columns, rows, row, column, nextRow;
    int u, v, x, y;
    float tick, limit, phase, opacity;
    int base;
    float scale[2];
    float pos[2];

    scale[0] = IntToFloat(g_screen_width[2]);
    scale[1] = IntToFloat(g_screen_width[3]);
    texture = GetEffectTextureDescriptor(30);
    rows = g_screen_width[0] / 32 + 1;
    columns = g_screen_width[1] / 32 + 1;
    for (row = 0; row < rows; row++) {
        int *p = g_tile_int_table;
        for (column = 0; column < columns; column++) {
            pos[0] = (float)(row << 5);
            pos[1] = (float)(column << 5);
            phase = (float)*p;
            tick = IntToFloat(*(int *)(state + 0x140));
            limit = IntToFloat(75);
            opacity = (tick * 127.5f) / limit;
            color = (FloatToInt(opacity) << 24) + 0x00FF7F7F;
            u = math_random_int_below(32);
            v = math_random_int_below(32);
            x = FloatToInt(pos[0] - phase);
            y = FloatToInt(pos[1] - phase);
            DrawTexturedQuad(x, y, 32, 32, u, v, 32, 32, color, texture);
        }
    }
}

/* func_PAL_L01_0039AD60, the PAL copy of func_L01_00397950: the same stores, where the second loop
 * scales each value to 50 Hz and counts up. */
void func_PAL_L01_0039AD60(void *arg0) {
    s32 *base = *(s32 **)((u8 *)arg0 + 0x68);
    f32 *values = (f32 *)((u8 *)base + 0x20);
    s32 *slot;
    s32 i;

    for (i = 0; i < 4; i++) {
        *values = (f32)math_random_int_below(0xFF);
        values++;
    }

    *(f32 *)((u8 *)base + 0x30) = -1.0f;
    *(f32 *)((u8 *)base + 0x34) = -2.25f;
    slot = (s32 *)((u8 *)base + 0x40);
    *(f32 *)((u8 *)base + 0x38) = 1.25f;
    *(f32 *)((u8 *)base + 0x3C) = 2.5f;

    for (i = 0; i < 4; i++) {
        slot[i] = ((i * 0x40 + 0x3F) * 5 + 2) / 6;
    }

    *(f32 *)((u8 *)base + 0x50) = 2.5f;
    *(f32 *)((u8 *)base + 0x54) = 3.0f;
    *(f32 *)((u8 *)base + 0x5C) = 2.5f;
    *(f32 *)((u8 *)base + 0x58) = 3.0f;
}
