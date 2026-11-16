#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

extern void moby_set_state(void *, s32, s32);

extern void euler_rotation_basis(void *, void *);

extern void multiply_matrix3x3(void *, void *, void *);

extern void transform_vector(void *, void *, void *);

extern s32 g_snivelak_attach_rotation __attribute__((sda));

extern s32 g_snivelak_attach_offset __attribute__((sda));

extern s32 g_snivelak_voice_cue_count __attribute__((sda));

extern char g_hero_l16_moby[] __attribute__((nosda));

extern float g_snivelak_hover_height_offset __attribute__((sda));

extern float g_snivelak_hover_limit __attribute__((nosda));

extern void anim_start_blended(void *, s32, s32, void *);

extern u32 g_current_map_index[1];

extern float g_snivelak_angle_limit __attribute__((sda));

extern float g_snivelak_angle_rate __attribute__((sda));

extern char g_scene_origin_transform[];

extern void moby_set_controller_speed_limits(void *, float, float, float, float);

extern s32 FloatToInt(float);

extern float fast_vec_dist(void *, void *);

extern void moby_update_ground_check(void *);

extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);

extern void gfx_update_color_fade(void *, void *);

extern void *part_find_owned_effect_slot(void *, s32, s32);

extern s32 FastDecTimer(void *);

extern float moby_update_aim_target_strength(void *, void *);

extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);

extern void moby_mark_spawned(void *);

extern void SetDeathBits(void *, s32, s32);

extern void *CreateMoby(s32);

extern float math_interpolate_between_limits(s32, s32, float, float);

extern void vec_store_transformed_entry(void *, s32, void *, float, float);

extern void moby_init_child_from_parent(void *, void *);

extern void math_approach_target_with_braking(void *, float, float, float, float);

extern char *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, float, float,
                          s32, s32, s32, s32);

extern char g_snivelak_voice_cues[] __attribute__((nosda));

extern char g_str_snivelak_voice_debug_a[] __attribute__((nosda));

extern char g_str_snivelak_voice_debug_b[] __attribute__((nosda));

extern void STUB_printf(void *);

extern s32 snd_resume_music_stream(void);

extern int math_fast_float_d(void *);

extern void snd_play_unplayed_voice_line(void *, s32, s32);

extern s32 math_random_int_range(s32, s32);

extern float math_random_angle(void);

extern void gfx_draw_beam_quads_glows_alt(void *, s32, s32, s32, float, float, float, s32, void *);

/* Raises the handle's measured flag, rebuilds the motion record from the level's
   pair of measured vectors and submits both halves of the sub-object. */
/* Sets up a child object so it starts on the parent's position and direction. */
void snivelak_attach_child_to_parent_pose(u8 *child, u8 *parent)
{
    u8 basis[0x30];

    moby_set_state(child, 1, -1);
    *(u16 *)(child + 0x34) |= 0x100;
    euler_rotation_basis(basis, &g_snivelak_attach_rotation);
    multiply_matrix3x3(child + 0xC0, parent, basis);
    transform_vector(child + 0x10, &g_snivelak_attach_offset, parent);
}

/* Raises the level's one-shot flag while the counter is low, then hands the sub-object
   its tail record. */
/* Plays voice lines and a sound when the hero reaches certain moments of the fight. */
void snivelak_play_voice_cues(u8 *moby)
{
    u8 *vars;
    u8 *hero;
    u8 *voice;

    vars = *(u8 **)(moby + 0x68);
    hero = g_hero_l16_moby;
    if (*(s32 *)(hero + 0x2294) == 0x39) {
        if (*(s32 *)(hero + 0x1B8) == 0) {
            STUB_printf(g_str_snivelak_voice_debug_a);
            snd_play_unplayed_voice_line(moby, 0x1C, 0x20);
            g_snivelak_voice_cue_count++;
        }
    }
    voice = g_snivelak_voice_cues;
    if (*(s16 *)(voice + 0x72) == 3 && *(s16 *)(voice + 0x6C) < 0x1770) {
        STUB_printf(g_str_snivelak_voice_debug_b);
        snd_resume_music_stream();
    }
    math_fast_float_d(vars + 0x350);
}

/* func_L16_00413EC8 is defined in L16_00403900.c (this unit has no $gp access for it). */

/* Two timed transitions of the same handle: the first drops the swung state once the
   measured clock passes the level's threshold, the second raises it below the other. */
/* Switches the boss between a flying state and a hovering state depending on how high the hero is. */
void snivelak_switch_fly_hover_state(u8 *moby)
{
    u8 *vars;
    u8 *hero;

    vars = *(u8 **)(moby + 0x68);
    if (*(s32 *)(vars + 0x26C) != 0) {
        if (*(float *)(vars + 0x264) + g_snivelak_hover_height_offset > g_snivelak_hover_limit) {
            *(s32 *)(vars + 0x26C) = 0;
            *(s32 *)(vars + 0x270) = *(u8 *)(moby + 0x20);
            *(s32 *)(vars + 0x274) = *(u8 *)(moby + 0x95);
            moby_set_state(moby, 0x10, 4);
        }
    } else {
        hero = g_hero_l16_moby;
        if (*(s32 *)(hero + 0x2294) != 0x81
            && *(float *)(vars + 0x264) + g_snivelak_hover_height_offset < *(float *)(hero + 0xD8)) {
            *(s32 *)(vars + 0x268) = 0;
            *(s32 *)(vars + 0x26C) = 1;
            if (*(u8 *)(moby + 0x43) != 0x16)
                anim_start_blended(moby, 0x16, 0, 0x1E);
            if (*(u8 *)(*(u8 **)(vars + 0x1F0) + 0x43) == 0xA)
                anim_start_blended(*(u8 **)(vars + 0x1F0), 0, 0, 0x1E);
        }
    }
}

/* func_L16_0040DAE0 is defined in L16_00403900.c (this unit has no $gp access for it). */

/* Arms the object the level has just spawned: the entry latch, the two measured speed
   ratios, the object's own timer, then the two children and the hero sensor. */
/* Updates the Snivelak boss each frame: setup, hearing the hero, taking damage; returns 1 when it dies. */
s32 snivelak_boss_update(u8 *moby)
{
    u8 *vars;
    u8 *hit;
    float speedA;
    float speedB;
    float zero;
    float damage;

    vars = *(u8 **)(moby + 0x68);
    if (*(u8 *)(moby + 0x20) == 0) {
        if (g_current_map_index[0] == 0x10
            && (*(s16 *)(moby + 0xB2) == 0x27 || *(s16 *)(moby + 0xB2) == 0x114))
            *(s32 *)(vars + 0x2AC) = 1;
        if (*(s32 *)(vars + 0x2AC) != 0)
            *(float *)(vars + 0x28C) = *(float *)(moby + 0x18) + 300.0f;
        *(u8 *)(vars + 0x150) = 8;
        *(s32 *)(vars + 0x188) = 3;
        *(float *)(vars + 0x17C) = 0.15000001f;
        *(s32 *)(vars + 0x2A4) = 0;
        *(float *)(vars + 0x170) = 0.5f;
        *(float *)(vars + 0x174) = 0.5f;
        if (*(s16 *)(vars + 0x24) == 0) {
            *(s16 *)(vars + 0x24) = 5;
            *(float *)(vars + 0x20) = 5.0f;
        }
        speedB = *(float *)(vars + 0x2A0);
        speedA = (speedB + speedB) * 0.00027777778f;
        speedB = speedB * 0.016666668f;
        *(s32 *)(vars + 0x50) = 0;
        *(s32 *)(vars + 0x88) = *(s32 *)(vars + 0x88) | 0x17;
        *(u8 *)(vars + 0x2E) = 1;
        *(float *)(vars + 0x84) = 0.5f;
        *(float *)(vars + 0x54) = 1.0f;
        *(float *)(vars + 0x58) = 0.40000001f;
        *(float *)(vars + 0x5C) = 0.40000001f;
        *(float *)(vars + 0x60) = 1.5707965f;
        *(float *)(vars + 0x80) = 1.5533432f;
        moby_set_controller_speed_limits(moby, speedA, speedB, 0.0017453295f, 0.20943955f);
        moby_set_state(moby, 1, 0);
        if (*(u8 *)(moby + 0x43) != 0)
            anim_start_blended(moby, 0, 0, 0);
        *(u8 *)(vars + 0x48) = FloatToInt(17.0f);
        *(u8 *)(vars + 0x4A) = FloatToInt(32.0f);
    }
    if (*(u8 *)(moby + 0x31) != 0) {
        if (fast_vec_dist(moby + 0x10, g_scene_origin_transform) < 24.0f) {
            moby_update_ground_check(moby);
            *(u8 *)(moby + 0x6F) = 0x16;
        }
    }
    math_update_wrapped_angle_offset(moby, vars + 0x284, vars + 0x278, g_snivelak_angle_limit,
                  g_snivelak_angle_rate * 0.00029088825f, -1.0f);
    gfx_update_color_fade(moby, vars + 0x140);
    hit = part_find_owned_effect_slot(moby, 0x10000, 0);
    if (FastDecTimer(vars + 0x26) == 0)
        hit = 0;
    if (hit != 0) {
        float v = *(float *)(hit + 0x2C);

        if (*(float *)(vars + 0x1E8) != 0.0f
            && *(u8 **)(hit + 0x20) != 0
            && *(s16 *)(moby + 0xAA) == *(s16 *)(*(u8 **)(hit + 0x20) + 0xAA))
            *(float *)(hit + 0x2C) = v * *(float *)(vars + 0x1E8);
        *(u8 *)(moby + 0xA8) = 0xFF;
    }
    damage = moby_update_aim_target_strength(moby, hit);
    *(u8 *)(moby + 0xA8) = 0xFF;
    *(float *)(vars + 0x20) = *(float *)(vars + 0x20) - damage;
    if ((float)*(s16 *)(vars + 0x24) * 0.33000001f <= damage || *(float *)(vars + 0x20) <= 0.0f) {
        if (*(u8 *)(moby + 0x43) != 4)
            anim_start_blended(moby, 4, 0, 3);
        moby_set_state(moby, 9, 3);
    }
    if (*(u8 *)(vars + 0x2E) == 2) {
        moby_mark_spawned(*(u8 **)(vars + 0x274));
        SetDeathBits(moby, 0, 3);
        return 1;
    }
    zero = 0.0f;
    *(s32 *)(vars + 0x260) = weapon_select_aim_target(moby, *(s32 *)(vars + 0x250), *(float *)(vars + 0x254), zero, 0, 0);
    *(s32 *)(vars + 0x2B4) = weapon_select_aim_target(moby, *(s32 *)(vars + 0x2B0), zero, zero, 0, 0);
    return 0;
}

extern void moby_bob_along_sine_wave(void *);
extern float g_snivelak_part_threshold __attribute__((nosda));
extern u8 *g_linked_node_state_ptr __attribute__((nosda));
extern float g_snivelak_camera_distance __attribute__((sda));
extern float g_snivelak_camera_height __attribute__((sda));
extern void follow_camera_set_distance(s32, float, float);
extern void follow_camera_set_height(float, float);
extern float IntToFloat(s32);
extern void hud_start_overlay(s32, s32, float);
extern s32 g_frame_l16_counter[] __attribute__((sda));
extern u8 *snivelak_spawn_rock_projectile(void *, s32);
extern s32 moby_pack_handle(void *);
extern void moby_set_light_color(void *, s32);
extern void value_set_and_smooth(void *, void *, s32, s32, float);
extern void moby_transform_joint_point(void *, s32, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *SpawnEA7Moby(void *, void *, void *, s32, float);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float g_snivelak_shot_speed __attribute__((sda));
extern u8 g_snivelak_shot_origin[] __attribute__((nosda));
extern void FastVecScale(void *, void *, float);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastAddRotations(float, float);
extern void moby_update_eased_node(void *, void *, s32, float, float);
extern u8 g_turret_aim_vector[] __attribute__((nosda));
extern float g_turret_ease_rate_a __attribute__((sda));
extern float g_turret_ease_rate_b __attribute__((sda));

/* Updates a boss part each frame: follows the parent, makes sounds and moves the children. */
void snivelak_part_update(u8 *moby)
{
    u8 *state;
    s32 value;
    float rate;
    state = *(u8 **)(moby + 0x68);
    if (*(s32 *)(state + 0x26C) != 0)
        moby_bob_along_sine_wave(moby);
    if (moby[0x95] != 0) {
        if (g_snivelak_part_threshold > 118.0f && *(s16 *)(g_linked_node_state_ptr + 0x86) == 0) {
            rate = 0.003f;
            follow_camera_set_distance(0, g_snivelak_camera_distance, rate);
            follow_camera_set_height(g_snivelak_camera_height, rate);
        }
        hud_start_overlay(11, 0, *(float *)(state + 0x20) / IntToFloat(*(s16 *)(state + 0x24)));
        if ((g_frame_l16_counter[0] & 31) == (((s32)moby >> 8) & 31))
            snivelak_spawn_rock_projectile(moby, 0);
        moby_update_ground_check(moby);
    }
    gfx_update_color_fade(moby, state + 0x50);
    value = moby_pack_handle(moby);
    if (*(void **)(state + 0x1F0)) moby_set_light_color(*(void **)(state + 0x1F0), value);
    if (*(void **)(state + 0x238)) moby_set_light_color(*(void **)(state + 0x238), value);
    if (*(void **)(state + 0x23C)) moby_set_light_color(*(void **)(state + 0x23C), value);
    if (*(u16 *)(moby + 0x96) < 0xFFFF) ++*(u16 *)(moby + 0x96);
    value_set_and_smooth(*(void **)(state + 0x1F0), state + 0x390, 2, 1, 4.0f);
}



/* Aims the turret part at the hero and swivels it, limited to a safe angle. */
void turret_l16_aim_at_hero(u8 *moby)
{
    float partPos[4];
    float target[4];
    u8 *state;
    u8 *aimPoint;
    float value;
    float scale;
    state = *(u8 **)(moby + 0x68);
    math_fast_float_d(state + 0x238);
    FastDecTimer(state + 0x23C);
    if (*(u16 *)(moby + 0x96) < 0xFFFF) ++*(u16 *)(moby + 0x96);
    moby_transform_joint_to_world(moby, 0, partPos);
    if (moby[0x20] != 4) {
        aimPoint = state + 0x1F0;
        value = fast_vec_dist(partPos, aimPoint) - 1.0f;
        FastVecScale(target, g_turret_aim_vector, value + value);
        target[2] = 0.0f;
        FastVecAdd(target, target, aimPoint);
        FastVecSub(partPos, target, partPos);
        *(float *)(state + 0x2B8) = fast_subtract_rotations(mat_fast_helper_a(partPos[0], partPos[1]), *(float *)(moby + 0xF8));
        moby_transform_joint_to_world(moby, 1, partPos);
        FastVecSub(partPos, target, partPos);
        value = fast_subtract_rotations(-mat_fast_helper_a(vec_length_xy(partPos), partPos[2]), *(float *)(moby + 0xF4));
        if (value > 0.523598849773407f) value = 0.523598849773407f;
        else if (value < -0.523598849773407f) value = -0.523598849773407f;
        *(float *)(state + 0x334) = value;
        scale = 0.5f;
    } else {
        scale = 0.085f;
        *(float *)(state + 0x2B8) = FastAddRotations(*(float *)(state + 0x298), 0.523598849773407f);
    }
    moby_update_eased_node(moby, state + 0x250, 0, g_turret_ease_rate_a * scale, g_turret_ease_rate_b * scale);
    moby_update_eased_node(moby, state + 0x2D0, 1, g_turret_ease_rate_a * scale, g_turret_ease_rate_b * scale);
}
