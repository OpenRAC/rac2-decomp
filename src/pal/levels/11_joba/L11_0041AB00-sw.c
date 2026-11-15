#include "include_asm.h"

#include "common.h"
extern void moby_set_state(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *part_find_owned_effect_slot(s32 arg0, s32 arg1, s32 arg2);
extern s32 snd_is_voice_playing_for_owner(u8 *arg0, s32 arg1);
extern s32 PlayMobySound(s32 arg0, s32 arg1, u8 *arg2);
extern s32 FloatToInt(f32 arg0);
extern f32 fast_vec_dist(u8 *arg0, u8 *arg1);
extern s32 joba_enemy_is_active(u8 *arg0);
extern u8 D_L11_00188660[];
extern u8 D_L11_001BA8C0[];
extern s32 D_L11_001A8FF0 __attribute__((sda));
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern f32 vec_get_heading_angle(u8 *a0, f32 *a1, s32 a2);
extern f32 vec_distance_xy(u8 *a0, u8 *a1);
extern u8 D_L11_00189EA0[];
extern u8 *g_moby_l11_table[] __attribute__((sda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 D_0019B2E8[][16];
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
void func_PAL_L11_0041B670(u8 *arg0) {
    f32 tmp[4], tmp2[4];
    u8 *s2 = arg0;
    u8 *s1 = *(u8 **)(s2 + 0x68);
    u8 *s0 = g_moby_l11_table[0] + *(s32 *)s1 * 256;
    u8 *pos;

    switch (*(u8 *)(s2 + 0x20)) {
    case 0:
        moby_set_state(s2, 1, -1);
        break;
    case 1:
        if (flag_is_third_pending_set(s0)) {
            PlayMobySound(0, 0, s2);
            moby_set_state(s2, 2, -1);
        }
        if (D_0019B2E8[g_current_map_index[0]][*(u8 *)(s2 + 0xB0)] & 0x80) {
            *(f32 *)(s2 + 0xF0) = fast_subtract_rotations(*(f32 *)(s2 + 0xF0), 1.5707965f);
            moby_set_state(s2, 6, -1);
        }
        break;
    case 2:
        math_step_value_toward_target(s2 + 0xF0, s1 + 4, -1.5707965f, 0.000767945f,
                      251.32744f, 349.06592f);
        if (*(f32 *)(s2 + 0xF0) <= -1.5707965f) {
            *(s32 *)(s1 + 4) = 0;
            moby_set_state(s2, 3, -1);
            PlayMobySound(1, 0, s2);
        }
        break;
    case 3:
        math_step_value_toward_target(s2 + 0xF0, s1 + 4, -1.308997f, 0.025132746f,
                      0.00062831864f, 1.0471977f);
        if (*(f32 *)(s2 + 0xF0) >= -1.308997f) {
            *(s32 *)(s1 + 4) = 0;
            moby_set_state(s2, 4, -1);
        }
        break;
    case 4:
        math_step_value_toward_target(s2 + 0xF0, s1 + 4, -1.5707965f, 0.00062831864f,
                      0.25132746f, 3.4906592f);
        if (*(f32 *)(s2 + 0xF0) <= -1.5707965f) {
            *(s32 *)(s1 + 4) = 0;
            moby_set_state(s2, 5, -1);
            PlayMobySound(1, 0, s2);
        }
        break;
    case 5:
        math_step_value_toward_target(s2 + 0xF0, s1 + 4, -1.48353f, 0.025132746f,
                      0.00062831864f, 1.0471977f);
        if (*(f32 *)(s2 + 0xF0) >= -1.48353f) {
            *(s32 *)(s1 + 4) = 0;
            moby_set_state(s2, 6, -1);
        }
        break;
    case 6:
        math_step_value_toward_target(s2 + 0xF0, s1 + 4, -1.5707965f, 0.00062831864f,
                      0.25132746f, 3.4906592f);
        if (*(f32 *)(s2 + 0xF0) <= -1.5707965f) {
            *(s32 *)(s1 + 4) = 0;
            moby_set_state(s2, 7, -1);
            PlayMobySound(1, 0, s2);
        }
        break;
    }
    pos = s0 + 0x10;
    qcopy(pos, s2 + 0x10);
    vec_scale_to_length(tmp, s2 + 0xE0, 5.7f);
    FastVecAdd(pos, pos, tmp);
    vec_scale_to_length(tmp2, s2 + 0xD0, 0.35f);
    FastVecAdd(pos, pos, tmp2);
}
