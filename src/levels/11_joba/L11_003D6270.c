#include "common.h"

extern void moby_set_state(u8 *arg0, s32 arg1, s32 arg2);

extern u8 *part_find_owned_effect_slot(s32 arg0, s32 arg1, s32 arg2);

extern void anim_start_blended(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

extern void func_002A05A8(u8 *arg0);

extern s32 snd_is_voice_playing_for_owner(u8 *arg0, s32 arg1);

extern s32 PlayMobySound(s32 arg0, s32 arg1, u8 *arg2);

extern void snd_stop_voice(s32 arg0);

extern s32 FloatToInt(f32 arg0);

extern void get_moby_color(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);

extern void moby_update_ground_check(u8 *arg0);

extern f32 fast_vec_dist(u8 *arg0, u8 *arg1);

extern void joba_enemy_init();

extern void joba_enemy_apply_damage(u8 *arg0);

extern void joba_enemy_update_state_machine(u8 *arg0);

extern void joba_enemy_update_orbit(u8 *arg0);

extern void joba_enemy_update_effects(u8 *arg0);

extern s32 joba_enemy_is_active(u8 *arg0);

extern void joba_enemy_reset(u8 *arg0);

extern void joba_enemy_clear_counters(u8 *arg0);

extern u8 D_L11_00188660[];

extern u8 D_L11_001BA8C0[];

extern s32 D_L11_001A8FF0 __attribute__((sda));

extern s32 D_L11_001A8FF4 __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

extern f32 vec_get_heading_angle(u8 *a0, f32 *a1, s32 a2);

extern f32 vec_distance_xy(u8 *a0, u8 *a1);

extern void FastVecSub(f32 *a0, const f32 *a1, const f32 *a2);

extern u8 D_L11_00189EA0[];

extern void joba_beams_draw(u8 *arg0);

/* The entity table's base and the current level, read as retail's tied absolute loads. */
extern u8 *g_moby_l11_table[] __attribute__((sda));

extern s32 g_current_map_index[] __attribute__((sda));

/* Per-level flag bytes, sixteen per level. */
extern u8 D_0019B2E8[][16];

extern void vec_scale_to_length(void *, void *, f32);

extern void FastVecAdd(void *, void *, void *);

extern s32 flag_is_third_pending_set(u8 *);

extern f32 fast_subtract_rotations(f32, f32);

extern f32 math_step_value_toward_target(void *, void *, f32, f32, f32, f32);

/* Defined in L11_003D6270-path.c. */


/* func_L11_003DCEB0 lives in L11_003DCEB0-g8.c. */

/* Defined in L11_003DD068-g8.c. */

/* Per-frame update for the Joba enemy. On the first frame it sets itself up; after that it
   runs damage, its state machine, its movement and its effects. */
void arachnoid_update(u8 *mobyArg) {
    u8 *moby = mobyArg;
    if (*(u8 *)(moby + 0x20) == 0) {
        joba_enemy_init();
    } else {
        if (joba_enemy_is_active(moby) != 0)
            return;
        if (*(u8 *)(moby + 0x31) != 0
            && fast_vec_dist(moby + 0x10, D_L11_001BA8C0) < 48.0f) {
            moby_update_ground_check(moby);
            *(u8 *)(moby + 0x6F) = 0x2D;
        }
        joba_enemy_apply_damage(moby);
        joba_enemy_update_state_machine(moby);
        joba_enemy_update_orbit(moby);
        joba_enemy_update_effects(moby);
    }
}
/* Sets up a new Joba enemy: fills in its starting values and puts it in its idle state. */
void joba_enemy_init(u8 *mobyArg) {
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    *(u8 *)(vars + 0x48) = FloatToInt(15.0f);
    *(u8 *)(vars + 0x4A) = FloatToInt(16.0f);
    get_moby_color(moby, vars + 0x280, vars + 0x284, vars + 0x288);
    *(u8 *)(vars + 0x28) = 3;
    *(f32 *)(vars + 0x30) = 1.5f;
    *(u8 *)(vars + 0x29) = 1;
    *(u16 *)(moby + 0x34) |= 0x100;
    joba_enemy_reset(moby);
    *(s32 *)(vars + 0x290) = -1;
}

/* func_L11_003F1DB0 is defined in L11_003D6270-g8.c (this unit has no $gp access for it). */

/* func_L11_003F1F48 is defined in L11_003D6270-state-g8.c. */

/* Defined in L11_003F2A30-g8.c. */

/* func_L11_003F2C28 is defined in L11_003D6270-g8.c (this unit has no $gp access for it). */


/* True when the engine's two global gates are both clear and the stage byte is not nine. */
s32 joba_enemy_is_active(u8 *moby) {
    s32 result = 0;

    if (D_L11_001A8FF0 == 0 || D_L11_001A8FF4 == 0)
        result = *(u8 *)(moby + 0x20) != 9;
    return result;
}

/* Puts the enemy back into state 4. */
void joba_enemy_return_state(u8 *moby) {
    moby_set_state(moby, 4, -1);
}

/* Remembers the enemy's current state, then switches it to its hit reaction state. */
void joba_enemy_enter_hit_reaction(u8 *mobyArg) {
    u8 *moby = mobyArg;
    s32 vars = *(s32 *)(moby + 0x68);
    u8 oldState = *(u8 *)(moby + 0x20);
    u8 savedValue = *(u8 *)(moby + 0x95);
    *(u8 *)(moby + 0x94) = oldState;
    *(u16 *)(vars + 0x294) = savedValue;
    moby_set_state(mobyArg, 3, -1);
}

/* Reports the signed area of the triangle (arg0, arg1, arg2). */
f32 math_signed_triangle_area(f32 *pointA, f32 *pointB, f32 *pointC) {
    return (pointA[0] - pointC[0]) * (pointB[1] - pointC[1])
         - (pointA[1] - pointC[1]) * (pointB[0] - pointC[0]);
}


/* Resets the enemy to its idle look and clears its counters. */
void joba_enemy_reset(u8 *moby) {
    joba_enemy_clear_counters(moby);
    anim_start_blended(moby, 0, 0, 3);
    func_002A05A8(moby);
    moby_set_state(moby, 1, 0);
    *(u8 *)(moby + 0x31) = 0;
    *(s32 *)(moby + 0x98) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 1) & 0xEFFF;
}

/* Clears one pair of the enemy's counters and sets the other pair to 1. */
void joba_enemy_set_counters_one(u8 *moby) {
    s32 i = 1;
    u16 *counters = (u16 *)(*(u8 **)(moby + 0x68) + 0x278);
    do {
        counters[-2] = 0;
        counters[0] = 1;
        i--;
        counters++;
    } while (i >= 0);
}

/* Clears one pair of the enemy's counters, sets the other pair to 2 and starts its sound
   effect if it has none. */
void joba_enemy_set_counters_two(u8 *mobyArg) {
    s32 i = 1;
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u16 *counters = (u16 *)(vars + 0x278);
    do {
        counters[-2] = 0;
        counters[0] = 2;
        i--;
        counters++;
    } while (i >= 0);
    if (snd_is_voice_playing_for_owner(moby, *(s32 *)(vars + 0x290)) == 0) {
        *(s32 *)(vars + 0x290) = PlayMobySound(2, 4, moby);
    }
}

/* Clears the enemy's counters and stops its sound effect. */
void joba_enemy_clear_counters(u8 *mobyArg) {
    s32 i = 1;
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u16 *counters = (u16 *)(vars + 0x278);
    s32 soundIndex;
    do {
        counters[-2] = 0;
        counters[0] = 0;
        i--;
        counters++;
    } while (i >= 0);
    soundIndex = *(s32 *)(vars + 0x290);
    if (soundIndex != -1) {
        u8 *sound = D_L11_00188660 + soundIndex * 0x70;
        if (*(u8 **)(sound + 0x88) == moby && *(u8 *)(sound + 0x74) != 0) {
            snd_stop_voice(soundIndex);
        }
    }
    *(s32 *)(vars + 0x290) = -1;
}

/* func_L11_003F3258 is defined in L11_003F3258-g8.c. */

/* func_L11_003F33E0 is defined in L11_003F33E0-g8.c. */

/* func_L11_003F3CB8 is in L11_003F3CB8-g8.c. */

/* Defined in L11_003F4060-g8.c. */

/* Defined in L11_003F4490-g8.c. */


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
/* Swings a part of the object between a few angles and keeps a linked object attached in
   front of it. */
void swinging_linked_moby_update(u8 *mobyArg) {
    f32 frontOffset[4], sideOffset[4];
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *linked = g_moby_l11_table[0] + *(s32 *)vars * 256;
    u8 *pos;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (flag_is_third_pending_set(linked)) {
            PlayMobySound(0, 0, moby);
            moby_set_state(moby, 2, -1);
        }
        if (D_0019B2E8[g_current_map_index[0]][*(u8 *)(moby + 0xB0)] & 0x80) {
            *(f32 *)(moby + 0xF0) = fast_subtract_rotations(*(f32 *)(moby + 0xF0), 1.5707964897155762f);
            moby_set_state(moby, 6, -1);
        }
        break;
    case 2:
        math_step_value_toward_target(moby + 0xF0, vars + 4, -1.5707964897155762f, 0.0005332950968295336f,
                      174.53294372558594f, 290.8882751464844f);
        if (*(f32 *)(moby + 0xF0) <= -1.5707964897155762f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(moby, 3, -1);
            PlayMobySound(1, 0, moby);
        }
        break;
    case 3:
        math_step_value_toward_target(moby + 0xF0, vars + 4, -1.3089970350265503f, 0.01745329424738884f,
                      0.0004363323678262532f, 0.872664749622345f);
        if (*(f32 *)(moby + 0xF0) >= -1.3089970350265503f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(moby, 4, -1);
        }
        break;
    case 4:
        math_step_value_toward_target(moby + 0xF0, vars + 4, -1.5707964897155762f, 0.0004363323678262532f,
                      0.174532949924469f, 2.9088826179504395f);
        if (*(f32 *)(moby + 0xF0) <= -1.5707964897155762f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(moby, 5, -1);
            PlayMobySound(1, 0, moby);
        }
        break;
    case 5:
        math_step_value_toward_target(moby + 0xF0, vars + 4, -1.483530044555664f, 0.01745329424738884f,
                      0.0004363323678262532f, 0.872664749622345f);
        if (*(f32 *)(moby + 0xF0) >= -1.483530044555664f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 6:
        math_step_value_toward_target(moby + 0xF0, vars + 4, -1.5707964897155762f, 0.0004363323678262532f,
                      0.174532949924469f, 2.9088826179504395f);
        if (*(f32 *)(moby + 0xF0) <= -1.5707964897155762f) {
            *(s32 *)(vars + 4) = 0;
            moby_set_state(moby, 7, -1);
            PlayMobySound(1, 0, moby);
        }
        break;
    }
    pos = linked + 0x10;
    qcopy(pos, moby + 0x10);
    vec_scale_to_length(frontOffset, moby + 0xE0, 5.7f);
    FastVecAdd(pos, pos, frontOffset);
    vec_scale_to_length(sideOffset, moby + 0xD0, 0.35f);
    FastVecAdd(pos, pos, sideOffset);
}


/* func_L11_00417340 is defined in L11_003D6270-g8.c (this unit has no $gp access for it). */

/* Reports whether the helper found the measured resource and updates its timer. */
/* Checks whether the enemy's damage source still exists and takes its damage off the
   enemy's health. */
s32 joba_enemy_apply_source_damage(u8 *mobyArg) {
    u8 *vars = *(u8 **)(mobyArg + 0x68);
    u8 *source = part_find_owned_effect_slot(*(s32 *)(vars + 0x280), 0x10000, 0);
    if (source != 0) {
        *(f32 *)(vars + 0x20) = *(f32 *)(vars + 0x20) - *(f32 *)(source + 0x2C);
        return 1;
    }
    return 0;
}
