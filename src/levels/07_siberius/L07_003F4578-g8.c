#include "include_asm.h"

#include "common.h"

extern f32 func_2E5318(f32 a, f32 b);

extern f32 func_2E4918(f32 a, f32 b);

extern f32 g_unused_float_param __attribute__((sda));

extern u8 *g_moby_l07_array __attribute__((sda));

extern void func_317520(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f);

extern void func_421288(s32 a, f32 b, f32 c);

extern void func_4212D0(f32 a, f32 b);

extern u8 *func_2CD050(s32 a);

extern void func_3109C8(u8 *a, s32 b, s32 c);

extern s32 func_312FA8(u8 *a, s32 b, s32 c);

extern f32 func_313008(u8 *a, s32 b);

extern void func_313DD8(void *a, f32 b, f32 c);

extern f32 g_boss_cam_distance __attribute__((sda));

extern f32 g_boss_cam_height __attribute__((sda));

extern u32 g_boss_screen_color __attribute__((sda));

extern f32 g_bomb_scale __attribute__((sda));

extern f32 g_beam_fade_in_rate __attribute__((sda));

extern f32 g_beam_fade_out_rate __attribute__((sda));

extern f32 g_beam_spin_rate __attribute__((sda));

extern f32 ApproachValue(f32 *value, f32 target, f32 step);

extern void moby_set_state(u8 *a, u8 b, s32 c);

extern void moby_mark_spawned(void *a);

extern f32 FastAddRotations(f32 a, f32 b);

extern void gfx_add_draw_callback_first(void *a, void *b);

extern void beam_get_end_points(void *a, void *b, void *c);

extern s32 coll_cast_object_line(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);

extern char DrawSegmentedBeam[];

/* Advances the object's own state: three step kinds by the 0x20 flag, then the shared
   spin and the two sampled vectors. */
/* Updates the beam: fades it in, then fades it out and removes it. While alive it spins, draws itself and hurts what it touches. */
void beam_update(u8 *moby)
{
    u8 *beam_moby = moby;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 state = *(u8 *)(moby + 0x20);
    f32 start_point[4];
    f32 end_point[4];

    switch (state) {
    case 0:
        {
            u32 frame_count = *(u16 *)(beam_moby + 0x96) + 1;

            *(u16 *)(beam_moby + 0x96) = frame_count;
            if ((u16)frame_count == 1) {
                break;
            }
            ApproachValue((f32 *)(vars + 0x24), 1.0f, g_beam_fade_in_rate * (1.0f / 60.0f));
            if (1.0f <= *(f32 *)(vars + 0x24)) {
                moby_set_state(beam_moby, 1, -1);
            }
        }
        break;
    case 1:
        ApproachValue((f32 *)(vars + 0x24), 0.0f, g_beam_fade_out_rate * (1.0f / 60.0f));
        if (*(f32 *)(vars + 0x24) <= 0.0f) {
            moby_mark_spawned(beam_moby);
            return;
        }
        break;
    }
    *(f32 *)(vars + 0x28) = FastAddRotations(*(f32 *)(vars + 0x28), g_beam_spin_rate * 0.00029088825f);
    gfx_add_draw_callback_first(DrawSegmentedBeam, beam_moby);
    if (0.333f < *(f32 *)(vars + 0x24)) {
        beam_get_end_points(beam_moby, start_point, end_point);
        coll_cast_object_line(*(u32 *)(beam_moby + 0xB8), start_point, end_point, 1, *(f32 *)(vars + 0x2C), 1.0f, 0, 1, 0);
    }
}


typedef int TI128 __attribute__((mode(TI)));

/* The object up to its flag word, its state pointer and its counter. */
typedef struct {
    u8 pad00[0x34];
    u16 flags34;
    u8 pad36[0x68 - 0x36];
    u8 *state;
    u8 pad6c[0x98 - 0x6C];
    s32 f98;
} SibObj;

/* The state record up to its two group words. */
typedef struct {
    u8 pad00[0xCC];
    s32 groupCC;
    s32 groupD0;
} SibGroups;

extern f32 g_hero_reset_offset_z;

extern u8 g_hero_l07_reset_position __attribute__((sda));

extern u16 **g_group_l07_id_lists;

extern u8 *g_joint_record_table;

extern u8 *g_matrix_l07_record_table;

extern s32 g_ship_phase_state;

extern void hero_reset_position_and_direction(void *obj, void *pos, s32 a2, s32 a3);

extern void gfx_setup_scale_record(s32 id, s32 a1);

/* Switches the object to its second phase. */
void boss_enter_second_phase(SibObj *moby)
{
    f32 offset_copy[4];
    f32 offset[4];
    SibGroups *state;
    u16 *id_list;
    u16 *id_list_b;
    u8 *entry;

    *(TI128 *)offset = 0;
    offset[2] = g_hero_reset_offset_z;
    *(TI128 *)offset_copy = *(TI128 *)offset;
    state = (SibGroups *)moby->state;
    hero_reset_position_and_direction(&g_hero_l07_reset_position, offset_copy, 0, 1);
    moby->flags34 |= 2;
    moby->f98 = 0;
    for (id_list = g_group_l07_id_lists[state->groupD0];
         id_list != 0 && ((s16)id_list[-1] >= 0 || id_list == g_group_l07_id_lists[state->groupD0]) &&
         (entry = g_joint_record_table + ((*id_list & 0x7FFF) << 5)) != 0;
         id_list++) {
        entry[0x1E] &= 0xFB;
    }
    for (id_list = g_group_l07_id_lists[state->groupCC];
         id_list != 0 && ((s16)id_list[-1] >= 0 || id_list == g_group_l07_id_lists[state->groupCC]) &&
         (entry = g_joint_record_table + ((*id_list & 0x7FFF) << 5)) != 0;
         id_list++) {
        entry[0x1E] |= 4;
    }
    for (id_list_b = g_group_l07_id_lists[state->groupCC];
         id_list_b != 0 && ((s16)id_list_b[-1] >= 0 || id_list_b == g_group_l07_id_lists[state->groupCC]) &&
         (entry = g_matrix_l07_record_table + ((*id_list_b & 0x7FFF) << 6)) != 0;
         id_list_b++) {
        *(f32 *)(entry + 0x38) -= 100.0f;
        gfx_setup_scale_record(*id_list_b & 0x7FFF, 1);
    }
    g_ship_phase_state = 2;
}


/* Seeds the two shared field defaults, then fills the 0x450 record once. */
extern void follow_camera_set_distance(s32, f32, f32);
extern void follow_camera_set_height(f32, f32);
extern u8 *cam_alloc_override_slot(s32);

typedef struct { f32 x, y; u8 pad08[0x2C]; u32 color; } Effect;
typedef struct { u8 pad[0x450]; Effect *effect; } EffectState;
/* Sets up the screen effect of the boss. For one variant it also creates the effect record once and fills it in. */
void boss_setup_screen_effect(u8 *moby)
{
    EffectState *vars = *(EffectState **)(moby + 0x68);

    follow_camera_set_distance(0, g_boss_cam_distance, 0.003f);
    follow_camera_set_height(g_boss_cam_height, 0.003f);
    if (*(u8 *)(moby + 0x95) != 0) {
        if (vars->effect == 0)
            vars->effect = (Effect *)cam_alloc_override_slot(5);
        {
            f32 x = g_boss_cam_distance;
            f32 y = g_boss_cam_height;
            u32 color;
            vars->effect->x = x;
            color = g_boss_screen_color;
            vars->effect->y = y;
            vars->effect->color = color;
        }
    }
}

/* Arms the spinner on the first pass, otherwise steers its 0x20 angle down. */
/* func_L07_003F6CF0 is defined in L07_003F4578-spin-g8.c. */

/* Steers the 0x54 yaw toward the argument and refreshes the two 0xF8 angles. */

/* Feeds the four 0xA8 ids to the shared geometry pass. */
/* func_L07_0040F6B8 is defined in L07_003F4578-geometry-g8.c. */

extern f32 func_2E49C8(f32 a, f32 b);

extern f32 func_2E5360(f32 a, f32 b);

extern void func_3144F0(void *a0, void *a1, f32 a2, f32 a3, f32 a4, f32 a5, s32 a6);

/* The two level floats the scaling uses; the pointers are reached absolutely. */
extern f32 g_aim_yaw_turn_accel __attribute__((sda));

extern f32 g_aim_yaw_max_turn_speed __attribute__((sda));

extern u8 *g_world_info __attribute__((nosda));

extern u8 *g_snowfall_target_moby MACRO_ADDR;

extern u8 g_aim_yaw_init_flag;

/* Steers the object's two angles: the yaw toward the argument, the pitch from the shared
   record, and the two scaled fields of the state record. */
void moby_steer_aim_yaw(u8 *moby)
{
    u8 *owner;
    u8 *vars;
    u8 *record;
    u8 *world_info;
    u8 *target_obj;
    f32 *dir_xy;
    f32 aim_angle;
    f32 target_yaw;
    f32 dir_angle;
    f32 max_turn_speed;
    f32 turn_accel;
    f32 pi;

    world_info = g_world_info;
    if (*(s16 *)(world_info + 0x86) != 0) {
        return;
    }
    target_obj = g_snowfall_target_moby;
    if (target_obj == 0) {
        return;
    }
    pi = 3.14159274f;
    owner = *(u8 **)(world_info + 0x70);
    vars = *(u8 **)(moby + 0x68);
    dir_xy = (f32 *)(owner + 0x160);
    target_yaw = func_2E5318(*(f32 *)(target_obj + 0xF8), pi);
    record = owner + 0x1C0;
    dir_angle = func_2E49C8(dir_xy[0], dir_xy[1]);
    aim_angle = func_2E5360(target_yaw, dir_angle);
    turn_accel = g_aim_yaw_turn_accel * 0.0000048481375f;
    max_turn_speed = g_aim_yaw_max_turn_speed * 0.000290888245f;
    if (g_aim_yaw_init_flag == 0) {
        aim_angle = func_2E5318(aim_angle, pi);
    }
    func_3144F0(&aim_angle, vars + 0x1A8, 0.0f, turn_accel, turn_accel, max_turn_speed, 0);
    *(f32 *)(record + 0x1C) = 1.0f;
    *(f32 *)(record + 0x14) = -*(f32 *)(vars + 0x1A8);
}

extern u8 g_hero_state[];
extern u32 g_frame_l07_counter MACRO_ADDR;
extern int coll_apply_push_to_object(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f);
extern void func_002A0F48(u8 *a);
extern f32 fast_vec_dist(u8 *a, u8 *b);

typedef struct { u8 pad[0xA8]; s32 ids[4]; } Rec;

/* Updates the four attached parts of the object: places each one, and lets the player grab a Swingshot Node part or shows and hides it. */
void swingshot_nodes_update_attached(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u32 frame_slot = ((s32)moby >> 8) & 7;
    s32 i;

    for (i = 0; i < 4; i++) {
        s32 id = ((Rec *)vars)->ids[i];
        u8 *part;
        if (id == -1)
            continue;
        part = g_moby_l07_array + (id << 8);
        coll_apply_push_to_object(part, moby, vars + 0x120 + i * 0x10, vars + 0x160 + i * 0x10, part + 0x10, part + 0xF0);
        func_002A0F48(part);
        if (*(s16 *)(part + 0xAA) == MOBY_CLASS_SWINGSHOT_NODE) {
            u8 *hero = g_hero_state;
            if (*(s32 *)(hero + 0x229C) == 13 && *(u8 **)(hero + 0xAA4) == part && *(u8 **)(hero + 0x3A0) != moby) {
                if (fast_vec_dist(hero + 0x80, part + 0x10) < 8.0f)
                    *(u8 **)(hero + 0x3A0) = moby;
                continue;
            }
        }
        if ((g_frame_l07_counter & 7) == frame_slot && *(s16 *)(part + 0xAA) == MOBY_CLASS_SWINGSHOT_NODE) {
            u8 *hero_b = g_hero_state;
            if (*(s32 *)(hero_b + 0x229C) != 13) {
                if (g_snowfall_target_moby == moby)
                    *(u16 *)(part + 0x34) &= 0xEFFF;
                else
                    *(u16 *)(part + 0x34) |= 0x1000;
            }
        }
    }
}

extern f32 g_bomb_scale __attribute__((sda));
extern char g_hero_position[];
extern char g_hero_position_block[];
extern u8 *g_hit_object_list[];
extern int coll_process_hit(void *, float, int, char *, void *);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int coll_sweep_from_object(char *, char *, int, float, float, float, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *part_spawn_blast_effect_moby(char *, char *, char *, float);
extern void homing_bomb_tick_fuse(u8 *a);
extern void homing_bomb_move_to_target(u8 *self, float *target);
extern void part_spawn_falling_puff(u8 *a0);

/* Updates the homing bomb: it flies toward the player and, when it touches something, explodes with a sound and damage, then waits to be reset. */
void homing_bomb_update(u8 *moby)
{
    u8 *vars;
    u8 *hit_cursor;
    char *pos;
    char *tuning_base;
    f32 dir[4];
    s32 hit_count, remaining;

    vars = *(u8 **)(moby + 0x68);
    if (moby[0x20] != 1)
        homing_bomb_tick_fuse(moby);
    switch (moby[0x20]) {
    case 2:
        *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * g_bomb_scale;
        homing_bomb_move_to_target(moby, (float *)g_hero_position);
        part_spawn_falling_puff(moby);
        hit_count = coll_process_hit(moby + 0x10, 0.333f, 0, (char *)moby, 0);
        if (hit_count > 0) {
            hit_cursor = (u8 *)g_hit_object_list;
            for (remaining = hit_count; remaining != 0; remaining--, hit_cursor += 4) {
                u8 *other = *(u8 **)hit_cursor;
                if (other == moby)
                    continue;
                if (other != *(u8 **)(moby + 0xB8))
                    moby_set_state(moby, 3, -1);
            }
        }
        break;
    case 3:
        snd_play_from_class_bank(6, 0, (char *)moby, 0xE5F);
        pos = (char *)moby + 0x10;
        coll_sweep_from_object((char *)moby, pos, 0x10000, 6.0f, 5.0f, 1.0f, 0, 1, 0);
        coll_sweep_from_object((char *)moby, pos, 1, 4.0f, (f32)vars[0x34], 1.0f, 0, 1, 0);
        FastVecSub(dir, g_hero_position_block, pos);
        vec_scale_to_length(dir, dir, 1.0f);
        part_spawn_blast_effect_moby((char *)moby, pos, (char *)dir, 0.0f);
        tuning_base = g_hero_position_block - 0x140;
        *(f32 *)(tuning_base + 0x180) = 0.1f;
        *(s32 *)(tuning_base + 0x188) = 0x5A;
        *(f32 *)(tuning_base + 0x160) = 0.2f;
        *(s32 *)(tuning_base + 0x168) = 0x3C;
        *(s32 *)(tuning_base + 0x16C) = 0;
        *(s32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(moby, 1, -1);
        break;
    }
}
