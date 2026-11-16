#include "include_asm.h"

#include "common.h"
extern s32 g_hero_frozen_flag MACRO_ADDR;
extern u8 g_hero_state[];
typedef struct {
    u8 reserved000[0x80];
    float position[4];
    u8 reserved090[0x1D00];
    float position_history[32][4];
    u8 reserved1F90[0x3AC];
    float heading_history[32];
    s32 heading_index, heading_count, position_index, position_count;
} HeroHistory;
typedef struct {
    u8 reserved000[0x108];
    float horizontal, vertical;
    u8 reserved110[0x90];
    s32 held;
    u8 reserved1A4[12];
    s32 pressed;
} InputRecordPrefix;
extern InputRecordPrefix g_pad_state;
extern void hero_reset_speeds_and_vectors(void);
extern s32 FastDecTimer(void *);
extern s32 hero_get_movement_mode_pal(void);
extern float hero_get_stick_magnitude(void);
extern float vec_length_xy(void *);
extern void hero_l18_update_state_machine_pal(void);
extern void euler_to_matrix(void *, void *);
extern void set_identity_matrix(void *);
extern void matrix_from_basis_rows(void *, void *);
extern void hero_l18_update_speed_targets_pal(void);
extern void hero_probe_ground_and_ledge_pal(void);
extern void hero_update_timers_reach_pal(void);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern s32 GetCollHitMaterial(void);

/* func_L18_002C4000 is defined in L18_002C4000-hero.c. */

/* func_L18_002C41F0 is defined in L18_002C4000-g8.c (this unit has $gp access for it). */

/* func_L18_002CFD68 is defined in L18_002CFD68-qcopy.c. */

/* func_L18_002CFF48 is defined in L18_002CFD68-qcopy.c. */

/* Runs once per frame for the hero: reads the controller, saves the hero position and heading history, and updates the hero movement. */
void hero_update_frame_input_pal(void)
{
    u8 *base;
    u8 *snapshot;
    u8 *positions;
    s32 index;
    s32 active = g_hero_frozen_flag;
    if (active) {
        hero_reset_speeds_and_vectors();
        return;
    }
    snapshot = g_hero_state + 0x2030;
    qcopy(snapshot, snapshot - 0x1FB0);
    if (g_pad_state.held & 3) {
        u8 *hero = snapshot - 0x2030;
        if (*(s16 *)(hero + 0x1454) < 1) *(s16 *)(hero + 0x1454) = 1;
    } else FastDecTimer(snapshot - 0xBDC);
    base = g_hero_state;
    if (*(s32 *)(base + 0x2294) == 16) *(s16 *)(base + 0x1454) = 0;
    base[0x22C3] = hero_get_movement_mode_pal();
    *(float *)(base + 0x1FB0) = g_pad_state.horizontal;
    *(float *)(base + 0x1FB4) = g_pad_state.vertical;
    *(s32 *)(base + 0x270) = 0;
    *(float *)(base + 0x24BC) = hero_get_stick_magnitude();
    if (vec_length_xy(base + 0x1FB0) < 0.25f) {
        /* horizontal and vertical start as the left and down bits. */
        s32 right = (g_pad_state.pressed >> 13) & 1;
        s32 horizontal = (g_pad_state.pressed >> 15) & 1;
        s32 up = (g_pad_state.pressed >> 14) & 1;
        s32 vertical = (g_pad_state.pressed >> 12) & 1;
        horizontal = right - horizontal;
        vertical = up - vertical;
        *(float *)(base + 0x1FB0) = (float)horizontal;
        *(float *)(base + 0x1FB4) = (float)vertical;
    }
    *(float *)(base + 0x24B8) = hero_get_stick_magnitude();
    hero_l18_update_state_machine_pal();
    ((HeroHistory *)base)->heading_history[((HeroHistory *)base)->heading_index] = *(float *)(base + 0x98);
    *(s32 *)(base + 0x23BC) = (*(s32 *)(base + 0x23BC) + 1) % 32;
    if (++*(s32 *)(base + 0x23C0) > 32) *(s32 *)(base + 0x23C0) = 32;
    index = *(s32 *)(base + 0x23C4);
    positions = base + 0x1D90;
    qcopy_nc(positions + index * 16, (base + 0x80));
    *(s32 *)(base + 0x23C4) = (index + 1) % 32;
    if (++*(s32 *)(base + 0x23C8) > 32) *(s32 *)(base + 0x23C8) = 32;
    euler_to_matrix(base, base + 0x90);
    set_identity_matrix(base + 0x40);
    matrix_from_basis_rows(base + 0x40, base);
    hero_l18_update_speed_targets_pal();
    hero_probe_ground_and_ledge_pal();
    hero_update_timers_reach_pal();
}


extern s32 hero_get_movement_mode(void);
typedef struct { u8 prefix[0x18]; s32 object; s32 count; u8 gap[0x20]; float normal[4]; } MotionCollision;
extern MotionCollision g_hero_ground_hit;
extern float cam_get_view_space_vector_length(void *);
extern void hero_build_relative_point(float *, float, float, float, s32);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_set_view_space_height(float *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float cam_get_view_space_angle(void *);
extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(void *a0, void *a1, float f12);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern void vec_scale_to_length(void *a0, void *a1, float f12);
extern void FastVecAdd(void *a0, void *a1, void *a2);

/* Stops the hero's velocity from pushing into a wall in front of it. */
void ClipHeroVelocityAtWall_pal(s32 force)
{
    float start[4], end[4], lower_start[4], lower_end[4];
    float height, reach, angle, dot;
    s32 material;
    if (cam_get_view_space_vector_length(g_hero_state + 0xF0) < 0.002f) return;
    /* Each block forms its own hero pointer; retail keeps only the %hi part across calls. */
    {
        u8 *hero = g_hero_state;
        height = 0.37f;
        reach = 0.5f;
        if ((u32)(*(s32 *)(hero + 0x229C) - 17) < 2) {
            height = 0.0f;
            reach = 0.7f;
        } else if (hero[0x22B4] == 4) height = 0.35f;
    }
    hero_build_relative_point(start, 0.0f, 0.0f, height, 1);
    hero_build_relative_point(lower_start, 0.0f, 0.0f, height * 0.3f, 1);
    if (force || vec_length_xy(g_hero_state + 0xF0) < 0.01f) {
        vec_scale_to_length(end, g_hero_state, reach);
        vec_scale_to_length(lower_end, g_hero_state, reach * 1.4f);
    } else {
        cam_set_view_space_height(end, g_hero_state + 0xF0, 0.0f);
        vec_scale_to_length(end, end, reach);
        FastVecScale(lower_end, end, 1.4f);
    }
    FastVecAdd(end, end, start);
    material = -1;
    FastVecAdd(lower_end, lower_end, lower_start);
    {
        u8 *hero = g_hero_state;
        if (CollLine(lower_start, lower_end, 2, *(u8 **)(hero + 0x2290), 0) && g_hero_ground_hit.count > 0) material = GetCollHitMaterial();
    }
    angle = 0.0f;
    {
        u8 *hero = g_hero_state;
        if (CollLine(start, end, 2, *(u8 **)(hero + 0x2290), 0) && g_hero_ground_hit.count > 0) angle = cam_get_view_space_angle(g_hero_ground_hit.normal);
    }
    if (angle >= 0.8726647f || material == 8 || material == 12) {
        u8 *hero = g_hero_state;
        *(s32 *)(hero + 0x270) = g_hero_ground_hit.object;
        cam_set_view_space_height(g_hero_ground_hit.normal, g_hero_ground_hit.normal, 0.0f);
        vec_scale_to_length(g_hero_ground_hit.normal, g_hero_ground_hit.normal, 1.0f);
        dot = FastVecDot(g_hero_ground_hit.normal, hero + 0xF0);
        if (dot < 0.0f) {
            FastVecScale(g_hero_ground_hit.normal, g_hero_ground_hit.normal, -dot);
            FastVecAdd(hero + 0xF0, hero + 0xF0, g_hero_ground_hit.normal);
        }
    }
}

