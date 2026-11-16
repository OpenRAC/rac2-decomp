#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
extern void moby_set_state(void *, s32, s32);
extern s32 g_snivelak_attach_rotation __attribute__((sda));
extern s32 g_snivelak_attach_offset __attribute__((sda));
extern s32 g_snivelak_voice_cue_count __attribute__((sda));
extern void anim_start_blended_pal(void *, s32, s32, void *);
extern u32 g_current_map_index[1];
extern float g_snivelak_angle_limit __attribute__((sda));
extern float g_snivelak_angle_rate __attribute__((sda));
extern char g_scene_origin_transform[];
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern s32 FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void gfx_update_color_fade_pal(void *, void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 FastDecTimer(void *);
extern float moby_update_aim_target_strength_pal(void *, void *);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern void moby_mark_spawned(void *);
extern void SetDeathBits_pal(void *, s32, s32);
extern s32 math_random_int_range(s32, s32);
extern u8 *g_linked_node_state_ptr __attribute__((nosda));
extern s32 g_frame_l16_counter[] __attribute__((sda));
extern s32 moby_pack_handle(void *);
extern u8 g_snivelak_shot_origin[] __attribute__((nosda));
extern u8 g_turret_aim_vector[] __attribute__((nosda));

/* func_L16_0040DAE0 is defined in L16_00403900.c (this unit has no $gp access for it). */

/* Arms the object the level has just spawned: the entry latch, the two measured speed
   ratios, the object's own timer, then the two children and the hero sensor. */
s32 snivelak_boss_update_pal(u8 *moby)
{
    u8 *vars;
    u8 *effect_slot;
    float speed_rate_a;
    float speed_rate_b;
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
        speed_rate_b = *(float *)(vars + 0x2A0);
        speed_rate_a = (speed_rate_b + speed_rate_b) * 0.00040000002f;
        speed_rate_b = speed_rate_b * 0.020000001f;
        *(s32 *)(vars + 0x50) = 0;
        *(s32 *)(vars + 0x88) = *(s32 *)(vars + 0x88) | 0x17;
        *(u8 *)(vars + 0x2E) = 1;
        *(float *)(vars + 0x84) = 0.5f;
        *(float *)(vars + 0x54) = 1.0f;
        *(float *)(vars + 0x58) = 0.40000001f;
        *(float *)(vars + 0x5C) = 0.40000001f;
        *(float *)(vars + 0x60) = 1.5707965f;
        *(float *)(vars + 0x80) = 1.5533432f;
        moby_set_controller_speed_limits(moby, speed_rate_a, speed_rate_b, 0.0025132746f, 0.25132746f);
        moby_set_state(moby, 1, 0);
        if (*(u8 *)(moby + 0x43) != 0)
            anim_start_blended_pal(moby, 0, 0, 0);
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
                  g_snivelak_angle_rate * 0.0003490659f, -1.0f);
    gfx_update_color_fade_pal(moby, vars + 0x140);
    effect_slot = part_find_owned_effect_slot(moby, 0x10000, 0);
    if (FastDecTimer(vars + 0x26) == 0)
        effect_slot = 0;
    if (effect_slot != 0) {
        float effect_strength = *(float *)(effect_slot + 0x2C);

        if (*(float *)(vars + 0x1E8) != 0.0f
            && *(u8 **)(effect_slot + 0x20) != 0
            && *(s16 *)(moby + 0xAA) == *(s16 *)(*(u8 **)(effect_slot + 0x20) + 0xAA))
            *(float *)(effect_slot + 0x2C) = effect_strength * *(float *)(vars + 0x1E8);
        *(u8 *)(moby + 0xA8) = 0xFF;
    }
    damage = moby_update_aim_target_strength_pal(moby, effect_slot);
    *(u8 *)(moby + 0xA8) = 0xFF;
    *(float *)(vars + 0x20) = *(float *)(vars + 0x20) - damage;
    if ((float)*(s16 *)(vars + 0x24) * 0.33000001f <= damage || *(float *)(vars + 0x20) <= 0.0f) {
        if (*(u8 *)(moby + 0x43) != 4)
            anim_start_blended_pal(moby, 4, 0, 2);
        moby_set_state(moby, 9, 3);
    }
    if (*(u8 *)(vars + 0x2E) == 2) {
        moby_mark_spawned(*(u8 **)(vars + 0x274));
        SetDeathBits_pal(moby, 0, 3);
        return 1;
    }
    zero = 0.0f;
    *(s32 *)(vars + 0x260) = weapon_select_aim_target(moby, *(s32 *)(vars + 0x250), *(float *)(vars + 0x254), zero, 0, 0);
    *(s32 *)(vars + 0x2B4) = weapon_select_aim_target(moby, *(s32 *)(vars + 0x2B0), zero, zero, 0, 0);
    return 0;
}
