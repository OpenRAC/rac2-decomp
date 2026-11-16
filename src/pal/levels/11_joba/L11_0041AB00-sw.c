#include "include_asm.h"

#include "common.h"
extern void moby_set_state(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *part_find_owned_effect_slot(s32 arg0, s32 arg1, s32 arg2);
extern s32 snd_is_voice_playing_for_owner(u8 *arg0, s32 arg1);
extern s32 PlayMobySound(s32 arg0, s32 arg1, u8 *arg2);
extern s32 FloatToInt(f32 arg0);
extern f32 fast_vec_dist(u8 *arg0, u8 *arg1);
extern s32 joba_enemy_is_active(u8 *arg0);
extern u8 g_sound_l11_slot_table[];
extern u8 g_hero_l11_position[];
extern s32 g_hero_control_locked __attribute__((sda));
extern s32 g_hero_l11_input_blocked __attribute__((sda));
extern f32 vec_get_heading_angle(u8 *a0, f32 *a1, s32 a2);
extern f32 vec_distance_xy(u8 *a0, u8 *a1);
extern u8 g_hero_l11_state_data[];
extern u8 *g_moby_l11_table[] __attribute__((sda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 g_moby_group_flags[][16];
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern s32 flag_is_third_pending_set(u8 *);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 math_step_value_toward_target(void *, void *, f32, f32, f32, f32);

/* Defined in L11_003F4F30-g8.c. */

/* func_L11_003F7B70 is in L11_003F7B70-g8.c. */

/* Defined in L11_003F7F58.c. */

/* Defined in L11_003F8150.c. */

/* Defined in L11_003F8510-g8.c. */

/* Defined in L11_00411D40-g8.c. */

/* Defined in L11_00412B20-g8.c. */

/* Defined in L11_00415E70.c. */


/* Steps a seven-state swing, easing the angle at 0xF0 between -90 and -75/-85 degrees, then
   places the linked table entity at this one's position, offset along two of its axes. */
void swinging_linked_moby_update_pal(u8 *moby) {
    f32 up_offset[4], side_offset[4];
    u8 *swing = moby;
    u8 *vars = *(u8 **)(swing + 0x68);
    u8 *linked = g_moby_l11_table[0] + *(s32 *)vars * 256;
    u8 *linked_pos;

    switch (*(u8 *)(swing + 0x20)) {
    case 0:
        moby_set_state(swing, 1, -1);
        break;
    case 1:
        if (flag_is_third_pending_set(linked)) {
            PlayMobySound(0, 0, swing);
            moby_set_state(swing, 2, -1);
        }
        if (g_moby_group_flags[g_current_map_index[0]][*(u8 *)(swing + 0xB0)] & 0x80) {
            *(f32 *)(swing + 0xF0) = fast_subtract_rotations(*(f32 *)(swing + 0xF0), 1.5707965f);
            moby_set_state(swing, 6, -1);
        }
        break;
    case 2:
        math_step_value_toward_target(swing + 0xF0, vars + 4, -1.5707965f, 0.000767945f,
                      251.32744f, 349.06592f);
        if (*(f32 *)(swing + 0xF0) <= -1.5707965f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(swing, 3, -1);
            PlayMobySound(1, 0, swing);
        }
        break;
    case 3:
        math_step_value_toward_target(swing + 0xF0, vars + 4, -1.308997f, 0.025132746f,
                      0.00062831864f, 1.0471977f);
        if (*(f32 *)(swing + 0xF0) >= -1.308997f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(swing, 4, -1);
        }
        break;
    case 4:
        math_step_value_toward_target(swing + 0xF0, vars + 4, -1.5707965f, 0.00062831864f,
                      0.25132746f, 3.4906592f);
        if (*(f32 *)(swing + 0xF0) <= -1.5707965f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(swing, 5, -1);
            PlayMobySound(1, 0, swing);
        }
        break;
    case 5:
        math_step_value_toward_target(swing + 0xF0, vars + 4, -1.48353f, 0.025132746f,
                      0.00062831864f, 1.0471977f);
        if (*(f32 *)(swing + 0xF0) >= -1.48353f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(swing, 6, -1);
        }
        break;
    case 6:
        math_step_value_toward_target(swing + 0xF0, vars + 4, -1.5707965f, 0.00062831864f,
                      0.25132746f, 3.4906592f);
        if (*(f32 *)(swing + 0xF0) <= -1.5707965f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(swing, 7, -1);
            PlayMobySound(1, 0, swing);
        }
        break;
    }
    linked_pos = linked + 0x10;
    qcopy(linked_pos, swing + 0x10);
    vec_scale_to_length(up_offset, swing + 0xE0, 5.7f);
    FastVecAdd(linked_pos, linked_pos, up_offset);
    vec_scale_to_length(side_offset, swing + 0xD0, 0.35f);
    FastVecAdd(linked_pos, linked_pos, side_offset);
}
