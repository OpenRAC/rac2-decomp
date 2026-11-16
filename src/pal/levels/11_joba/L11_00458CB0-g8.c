#include "include_asm.h"

#include "common.h"
extern float math_random_float_range(float a, float b);
extern void vec_scale_to_length(char *a0, void *a1, float f12);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern s32 g_hero_l11_input_blocked __attribute__((sda));
extern char g_sound_state[];
extern char g_hero_l11_position[];
extern int FloatToInt(float);
extern void moby_set_state(void *, int, int);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void get_moby_color(void *, void *, void *, void *);
extern void moby_update_ground_check(void *);
extern float moby_update_aim_target_strength_pal(void *, void *);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern float fast_vec_dist(void *, void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, char *);
extern void matrix_from_basis_rows(void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void gfx_start_color_fade_pal(void *, void *);
extern void vec_random_direction(void *, float, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern float FastAddRotations(float, float);
extern float func_L00_002EE290(void *);
extern void drone_update_lock_on(char *);
extern void drone_reset_to_idle_pal(char *);
extern u8 *arena_get_center_point(u8 *);
extern int arena_is_point_in_inner_zone(u8 *, u8 *);

/* The launcher's state handler: re-arms the shot, aims the head at the level's
   target and hands the launch to the level's helpers. */
void drone_launcher_update_state_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float push[4];
    float jitter[4];
    float to_center[4];
    float aim_damage;
    float dot;
    float length;
    int voice_index;
    char *slot;
    char *voice;
    u8 *effect_obj;

    if (*(u8 *)(moby + 0x20) == 0) {
        *(int *)(vars + 0x18) = (int)(vars + 0x60);
        *(float *)(moby + 0x2C) *= 0.75f;
        *(int *)(vars + 0x1DC) = -1;
        *(u8 *)(vars + 0x48) = FloatToInt(15.0f);
        *(u8 *)(vars + 0x4A) = FloatToInt(12.0f);
        *(float *)(vars + 0x1D0) =
            math_random_float_range(-*(float *)(vars + 0x1D0), *(float *)(vars + 0x1D0)) *
            0.01745329424738884f;
        *(u8 *)(moby + 0x30) = 0x80;
        *(int *)(vars + 0x1D4) = 1;
        *(float *)(vars + 0x1D8) *= 0.020000001f;
        moby_set_controller_speed_limits(moby, 0.040000003f, 2.0000002f,
                      0.0016755164f, 0.12566373f);
        *(int *)(vars + 0x98) |= 4;
        *(float *)(vars + 0x60) = 0.75f;
        *(float *)(vars + 0x68) = 0.75f;
        *(int *)(vars + 0x64) = 0;
        *(float *)(vars + 0x6C) = 0.5f;
        *(float *)(vars + 0x70) = 1.134464144706726f;
        *(float *)(vars + 0x90) = 0.523598849773407f;
        *(float *)(vars + 0x8C) = 0.004f;
        get_moby_color(moby, vars + 0x1F0, vars + 0x1F4, vars + 0x1F8);
        *(u8 *)(vars + 0x28) = 3;
        *(int *)(vars + 0x30) = 0;
        *(short *)(vars + 0x1EC) = 0;
        drone_reset_to_idle_pal(moby);
    }
    if (*(short *)(vars + 0x1FC) == 0 && *(u8 *)(moby + 0x20) != 0xE &&
        g_hero_l11_input_blocked == 0) {
        *(u16 *)(moby + 0x34) |= 0x400;
        if (*(u8 *)(moby + 0x31) != 0) {
            if (fast_vec_dist(moby + 0x10, g_hero_l11_position) < 24.0f) {
                moby_update_ground_check(moby);
                *(u8 *)(moby + 0x6F) = 0x16;
            }
        }
    } else {
        *(u16 *)(moby + 0x34) &= 0xFBFF;
    }
    if (*(u8 *)(moby + 0x95) >= 2) {
        if (snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x1DC)) == 0)
            *(int *)(vars + 0x1DC) = PlayMobySound(1, 4, moby);
    } else {
        if (snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x1DC))) {
            voice_index = *(int *)(vars + 0x1DC);
            if (voice_index != -1) {
                voice = g_sound_state + voice_index * 0x70;
                if (*(char **)(voice + 0x88) == moby && *(u8 *)(voice + 0x74) != 0)
                    snd_stop_voice(voice_index);
            }
            *(int *)(vars + 0x1DC) = -1;
        }
    }
    if (*(short *)(vars + 0x1FC) != 0)
        *(int *)(vars + 0x98) &= ~0x10;
    else
        *(int *)(vars + 0x98) |= 0x10;
    slot = (char *)part_find_owned_effect_slot(moby, 0x10000, 0);
    if (slot != 0) {
        effect_obj = *(u8 **)(slot + 0x20);
        if (effect_obj != 0) {
            if (*(short *)(effect_obj + 0xAA) == 0xA03)
                *(int *)(slot + 0x2C) = 0;
            else if (*(u8 *)(moby + 0x31) == 0 && *(short *)(effect_obj + 0xAA) == 0xB89)
                *(int *)(slot + 0x2C) = 0;
        }
    }
    aim_damage = moby_update_aim_target_strength_pal(moby, slot);
    *(u8 *)(moby + 0xA8) = 0xFF;
    *(float *)(vars + 0x20) -= aim_damage;
    if (aim_damage != 0.0f) {
        if (*(u8 *)(moby + 0x20) != 3 && *(u8 *)(moby + 0x20) != 0xE) {
            vec_scale_to_length((char *)push, slot + 0x10, 1.2f);
            vec_random_direction(jitter, -0.2f, 0.2f);
            FastVecAdd(push, push, jitter);
            if (*(short *)(vars + 0x1FC) == 0) {
                push[2] = math_random_float_range(0.0f, 0.0f) * 0.00040000002f;
                push[3] = 5627.9248046875f;
            } else {
                FastVecSub(to_center, arena_get_center_point(*(u8 **)(moby + 0xB8)),
                              moby + 0x10);
                to_center[2] = 0.0f;
                vec_scale_to_length((char *)to_center, to_center, 1.0f);
                dot = FastVecDot(push, to_center);
                if (dot < 0.0f) {
                    vec_scale_to_length((char *)to_center, to_center, dot);
                    length = FastVecLength(push);
                    FastVecSub(push, push, to_center);
                    vec_scale_to_length((char *)push, push, length);
                }
            }
            FastVecAdd(vars + 0x100, vars + 0x100, push);
            vec_random_direction(jitter, 0.0025132746f, 0.010053098f);
            *(float *)(vars + 0x1B0) = FastAddRotations(*(float *)(vars + 0x1B0), jitter[0]);
            *(float *)(vars + 0x1B4) = FastAddRotations(*(float *)(vars + 0x1B4), jitter[1]);
            *(float *)(vars + 0x1B8) = FastAddRotations(*(float *)(vars + 0x1B8), jitter[2]);
            gfx_start_color_fade_pal(moby, vars + 0x50);
            moby_set_state(moby, 0xD, 4);
        }
    }
    if (*(short *)(vars + 0x1FC) != 0) {
        matrix_from_basis_rows(vars + 0x170, moby + 0xC0);
        cam_compute_view_direction(moby + 0x10, vars + 0x1A0, 0);
        if (arena_is_point_in_inner_zone(*(u8 **)(moby + 0xB8), (u8 *)(moby + 0x10)) == 0) {
            *(int *)(vars + 0x20) = 0;
            moby_set_state(moby, 0xE, 4);
        }
        if (*(u8 *)(moby + 0x20) != 0xE) {
            length = *(float *)(moby + 0x18);
            effect_obj = arena_get_center_point(*(u8 **)(moby + 0xB8));
            FastVecSub(push, moby + 0x10, effect_obj);
            push[2] = 0.0f;
            if (func_L00_002EE290(push) > 225.0f) {
                vec_scale_to_length((char *)push, push, 15.0f);
                effect_obj = arena_get_center_point(*(u8 **)(moby + 0xB8));
                FastVecAdd(moby + 0x10, push, effect_obj);
                *(float *)(moby + 0x18) = length;
            }
        }
    }
    if (*(u8 *)(moby + 0x20) >= 2 && *(u8 *)(vars + 0x2E) == 2)
        drone_reset_to_idle_pal(moby);
    drone_update_lock_on(moby);
}
