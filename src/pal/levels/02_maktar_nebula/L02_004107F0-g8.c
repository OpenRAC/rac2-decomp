#include "include_asm.h"

#include "common.h"
extern s32 FloatToInt(float);
extern float math_random_float_range(float, float);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern void get_moby_color(u8 *, s32 *, s32 *, s32 *);
extern void blade_ball_explode_pal(u8 *);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(u8 *);
extern s32 snd_is_voice_playing_for_owner(s32, s32);
extern s32 PlayMobySound(s32, s32, char *);
extern void snd_stop_voice(s32);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern float moby_update_aim_target_strength_pal(u8 *, u8 *);
extern void vec_scale_to_length(float *, float *, float);
extern void vec_random_direction(float *, float, float);
extern void FastVecAdd(float *, float *, float *);
extern float FastAddRotations(float, float);
extern void gfx_start_color_fade_pal(s32, char *);
extern void moby_set_state(u8 *, s32, s32);
extern void blade_ball_update_targeting(u8 *);
extern u8 g_camera_l02_position[];
extern u8 g_sound_state[];
extern float g_blade_ball_push_speed __attribute__((sda));
extern float g_blade_ball_random_spread_min __attribute__((sda));
extern float g_blade_ball_random_spread_max __attribute__((sda));
extern float g_blade_ball_up_speed __attribute__((sda));
extern float g_blade_ball_angle_spread_min __attribute__((sda));
extern float g_blade_ball_angle_spread_max __attribute__((sda));

/* Maintain the held effect slot and react to contacts with another actor. */
void blade_ball_update_common_pal(u8 *object)
{
    float velocity[4];
    float random[4];
    u8 *state = *(u8 **)(object + 0x68);
    u8 *contact;
    float amount;
    float scale;
    float push;

    if (object[0x20] == 0) {
        *(u8 **)(state + 0x18) = state + 0x60;
        *(float *)(object + 0x2C) *= 0.75f;
        *(s32 *)(state + 0x19C) = -1;
        state[0x48] = FloatToInt(15.0f);
        state[0x4A] = FloatToInt(4.0f);
        *(float *)(state + 0x190) = math_random_float_range(-*(float *)(state + 0x190), *(float *)(state + 0x190)) * 0.017453294f;
        object[0x30] = 0x80;
        *(s32 *)(state + 0x194) = 1;
        *(float *)(state + 0x198) *= 0.020000001f;
        moby_set_controller_speed_limits(object, 0.040000003f, 2.0000002f, 0.0016755164f, 0.12566373f);
        get_moby_color(object, (s32 *)(state + 0x1A0), (s32 *)(state + 0x1A4), (s32 *)(state + 0x1A8));
        *(float *)(state + 0x60) = 0.75f;
        *(float *)(state + 0x68) = 0.75f;
        *(s32 *)(state + 0x64) = 0;
        *(s32 *)(state + 0x30) = 0;
        *(u16 *)(state + 0x1B8) = 0;
        *(float *)(state + 0x6C) = 0.5f;
        *(float *)(state + 0x70) = 1.1344641f;
        *(float *)(state + 0x90) = 0.52359885f;
        *(float *)(state + 0x8C) = 0.004f;
        *(u32 *)(state + 0x98) |= 0x14;
        state[0x28] = 3;
        blade_ball_explode_pal(object);
    }
    if (object[0x31] && fast_vec_dist(object + 0x10, g_camera_l02_position) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6F] = 0x16;
    }
    if (object[0x95] >= 2) {
        if (!snd_is_voice_playing_for_owner((s32)object, *(s32 *)(state + 0x19C)))
            *(s32 *)(state + 0x19C) = PlayMobySound(1, 4, (char *)object);
    } else if (snd_is_voice_playing_for_owner((s32)object, *(s32 *)(state + 0x19C))) {
        s32 slot = *(s32 *)(state + 0x19C);
        if (slot != -1) {
            u8 *record = g_sound_state + slot * 0x70;
            if (*(u8 **)(record + 0x88) == object && record[0x74])
                snd_stop_voice(slot);
        }
        *(s32 *)(state + 0x19C) = -1;
    }
    contact = part_find_owned_effect_slot(object, 0x10000, 0);
    if (contact && *(u8 **)(contact + 0x20)) {
        s16 kind = *(s16 *)(*(u8 **)(contact + 0x20) + 0xAA);
        if (kind == 0xA03)
            *(s32 *)(contact + 0x2C) = 0;
        else if (object[0x31] == 0 && kind == 0xB89)
            *(s32 *)(contact + 0x2C) = 0;
    }
    amount = moby_update_aim_target_strength_pal(object, contact);
    object[0xA8] = 0xFF;
    if (amount != 0.0f) {
        scale = 0.00040000002f;
        push = g_blade_ball_push_speed * scale;
        *(float *)(state + 0x20) -= amount;
        vec_scale_to_length(velocity, (float *)(contact + 0x10), push);
        vec_random_direction(random, g_blade_ball_random_spread_min * scale, g_blade_ball_random_spread_max * scale);
        FastVecAdd(velocity, velocity, random);
        velocity[2] = math_random_float_range(g_blade_ball_up_speed, g_blade_ball_up_speed) * scale;
        velocity[3] = 5627.925f;
        FastVecAdd((float *)(state + 0x100), (float *)(state + 0x100), velocity);
        vec_random_direction(random, g_blade_ball_angle_spread_min * 6.981318e-06f, g_blade_ball_angle_spread_max * 6.981318e-06f);
        *(float *)(state + 0x170) = FastAddRotations(*(float *)(state + 0x170), random[0]);
        *(float *)(state + 0x174) = FastAddRotations(*(float *)(state + 0x174), random[1]);
        *(float *)(state + 0x178) = FastAddRotations(*(float *)(state + 0x178), random[2]);
        gfx_start_color_fade_pal((s32)object, (char *)(state + 0x50));
        moby_set_state(object, 13, 4);
    }
    if (object[0x20] >= 2 && state[0x2E] == 2)
        blade_ball_explode_pal(object);
    blade_ball_update_targeting(object);
}
