#include "names.h"
/* func_PAL_L05_00449FF0, the PAL copy of func_L05_00443D08: the same C, where the five weapon
   timers are scaled to 50 Hz as they are stored, the 1/60 step becomes 0.02, the frame counts
   5, 7, 8 and 10 become 4, 6, 7 and 8, and the first three timer globals are read as ints. */
#include "common.h"
typedef unsigned int ShotQuad __attribute__((mode(TI)));
typedef union { ShotQuad q; float f[4]; } ShotVector;
extern int g_feltzin_mission_index, g_pad_pressed_flags[], g_ship_mode_words[];
typedef struct { int upgrade; char pad[12]; int maximum, ammo; char tail[16]; } WeaponSlot;
extern WeaponSlot g_spawn_entry_table[];
extern char g_sound_state[],g_slot_record_source[];
extern float g_ship_aim_length __attribute__((sda)), g_ship_muzzle_speed __attribute__((sda));
extern int g_ship_shot_var_half_a __attribute__((sda)),g_ship_shot_var_half_b __attribute__((sda)),g_ship_shot_var_half_c __attribute__((sda));
extern int g_ship_shot_var_word_a __attribute__((sda)),g_ship_shot_var_word_b __attribute__((sda)),g_ship_shot_voice_id __attribute__((sda));
extern float g_ship_muzzle_left_offset __attribute__((sda)),g_ship_muzzle_right_offset __attribute__((sda)),g_ship_muzzle_left_alt_offset __attribute__((sda)),g_ship_muzzle_right_alt_offset __attribute__((sda));
extern int FastDecTimer(void *),math_fast_float_d(void *),slot_find_active_in_chain(int);
extern void FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *),vec_scale_to_length(void *,void *,float),matrix_mul_vec3(void *,void *,void *),FastVecScale(void *,void *,float);
/* The sound call and the four spawners below return a value this function ignores. Declaring them
   void changes the code: their call_value is what ends the zero register's dependence on the later
   `v0 = 5`, which orders each clear's por after its constant and keeps the upgrade test in v1. */
extern int PlayMobySound(int,int,void *);
extern void slot_subtract_value_clamped(int,int);
extern char *moby_spawn_shot_effect_pal(void *,void *,float,void *,int,int,int,int,int);
extern char *feltzin_shot_create_pal(void *,void *,int,void *,int),*moby_spawn_directed_effect_pal(void *,void *,int,void *,int),*projectile_spawn_with_target_pal(void *,void *,int,void *,int,int),*projectile_l05_spawn_pal(void *,void *,int,void *,int);
extern int snd_play_from_class_bank(int,int,void *,int),actuator_play_waves(void *);
extern void snd_stop_voice(int);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
/* Fires the ship's weapons for one frame: a pair of shots on input bit 0x40, four weapons on
   input bit 0x20, each behind its own timer, and a held weapon on 0x80, whose ammunition
   recharges every third frame while it is released. */
void UpdateShipWeapons_pal(char *moby, char *ship)
{
    ShotVector vec_a, vec_b, vec_c, vec_d, vec_e, vec_f;
    char *driver_state = P(ship, 0x70);
    char *vars = P(moby, 0x68);
    char *shot;
    int mode, index;

    if (H(driver_state, 0xd8) && (g_feltzin_mission_index & 1))
        return;

    if (FastDecTimer(vars + 8) && (g_pad_pressed_flags[0] & 0x40)) {
        H(vars, 8) = ((s32)(g_ship_shot_var_half_a) * 5 + 2) / 6;
        FastVecSub(&vec_a, vars + 0x20, ship + 0x30);
        vec_scale_to_length(&vec_a, &vec_a, g_ship_aim_length);
        FastVecAdd(&vec_b, &vec_a, ship + 0x30);
        mode = g_ship_mode_words[0];
        if (mode)
            matrix_mul_vec3(&vec_c, &g_ship_muzzle_left_alt_offset, moby + 0xc0);
        else
            matrix_mul_vec3(&vec_c, &g_ship_muzzle_left_offset, moby + 0xc0);
        FastVecAdd(&vec_c, &vec_c, moby + 0x10);
        FastVecSub(&vec_d, &vec_b, &vec_c);
        PlayMobySound(3, 0, moby);
        shot = moby_spawn_shot_effect_pal(moby, &vec_c, -1.0f, &vec_d, 0x2020ff, 0x20207f, 0, mode, 0);
        if (shot) {
            char *shot_vars = P(shot, 0x68);
            I(shot_vars, 0x28) = 0;
            F(shot_vars, 0x10) += F(driver_state, 0x30);
            F(shot_vars, 0x14) += F(driver_state, 0x34);
            F(shot_vars, 0x18) += F(driver_state, 0x38);
            if (mode) {
                FastVecScale(&vec_e, moby + 0xd0, g_ship_muzzle_speed * 0.020000001f);
                FastVecAdd(shot_vars + 0x10, shot_vars + 0x10, &vec_e);
            }
        }
        if (mode)
            matrix_mul_vec3(&vec_e, &g_ship_muzzle_right_alt_offset, moby + 0xc0);
        else
            matrix_mul_vec3(&vec_e, &g_ship_muzzle_right_offset, moby + 0xc0);
        FastVecAdd(&vec_e, &vec_e, moby + 0x10);
        FastVecSub(&vec_d, &vec_b, &vec_e);
        shot = moby_spawn_shot_effect_pal(moby, &vec_e, 1.0f, &vec_d, 0x2020ff, 0x20207f, 0, mode, 0);
        if (shot) {
            char *shot_vars = P(shot, 0x68);
            I(shot_vars, 0x28) = 0;
            F(shot_vars, 0x10) += F(driver_state, 0x30);
            F(shot_vars, 0x14) += F(driver_state, 0x34);
            F(shot_vars, 0x18) += F(driver_state, 0x38);
            if (mode) {
                FastVecScale(&vec_f, moby + 0xd0, -(g_ship_muzzle_speed * 0.020000001f));
                FastVecAdd(shot_vars + 0x10, shot_vars + 0x10, &vec_f);
            }
        }
    }

    {
        int slot = slot_find_active_in_chain(1);
        if (slot >= 0 && g_spawn_entry_table[slot].ammo != 0 && FastDecTimer(vars + 0xa)
            && (g_pad_pressed_flags[0] & 0x20)) {
            slot_subtract_value_clamped(1, 1);
            vec_a.q = 0;
            vec_a.f[2] = -0.1f;
            vec_a.f[3] = 1.0f;
            matrix_mul_vec3(&vec_b, &vec_a, moby + 0xc0);
            FastVecAdd(&vec_b, &vec_b, moby + 0x10);
            PlayMobySound(2, 0, moby);
            feltzin_shot_create_pal(&vec_b, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[9].upgrade);
            H(vars, 0xa) = ((s32)(g_ship_shot_var_half_b) * 5 + 2) / 6;
            I(vars, 0x218) = 4;
        }
    }

    {
        int slot = slot_find_active_in_chain(3);
        if (slot >= 0 && g_spawn_entry_table[slot].ammo != 0 && FastDecTimer(vars + 0xa8)
            && (g_pad_pressed_flags[0] & 0x20)) {
            slot_subtract_value_clamped(3, 1);
            vec_a.q = 0;
            vec_a.f[2] = -0.1f;
            vec_a.f[3] = 1.0f;
            matrix_mul_vec3(&vec_b, &vec_a, moby + 0xc0);
            FastVecAdd(&vec_b, &vec_b, moby + 0x10);
            PlayMobySound(2, 0, moby);
            moby_spawn_directed_effect_pal(&vec_b, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[11].upgrade);
            H(vars, 0xa8) = ((s32)(g_ship_shot_var_half_c) * 5 + 2) / 6;
            I(vars, 0x218) = 4;
        }
    }

    {
        int slot = slot_find_active_in_chain(2);
        if (slot >= 0 && g_spawn_entry_table[slot].ammo != 0 && math_fast_float_d(vars + 0x20c)
            && (g_pad_pressed_flags[0] & 0x20)) {
            slot_subtract_value_clamped(2, 1);
            vec_a.q = 0;
            vec_a.f[2] = -0.2f;
            vec_a.f[3] = 1.0f;
            matrix_mul_vec3(&vec_b, &vec_a, moby + 0xc0);
            FastVecAdd(&vec_b, &vec_b, moby + 0x10);
            PlayMobySound(2, 0, moby);
            projectile_spawn_with_target_pal(&vec_b, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[10].upgrade, 1);
            if (g_spawn_entry_table[10].upgrade) {
                vec_c.q = 0;
                vec_c.f[1] = -0.275f;
                vec_c.f[3] = 1.0f;
                matrix_mul_vec3(&vec_b, &vec_c, moby + 0xc0);
                FastVecAdd(&vec_b, &vec_b, moby + 0x10);
                projectile_spawn_with_target_pal(&vec_b, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[10].upgrade, 0);
                vec_d.q = 0;
                vec_d.f[1] = 0.275f;
                vec_d.f[3] = 1.0f;
                matrix_mul_vec3(&vec_b, &vec_d, moby + 0xc0);
                FastVecAdd(&vec_b, &vec_b, moby + 0x10);
                projectile_spawn_with_target_pal(&vec_b, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[10].upgrade, 0);
            }
            I(vars, 0x20c) = ((s32)(g_ship_shot_var_word_a) * 5 + 2) / 6;
            I(vars, 0x218) = 6;
        }
    }

    {
        int slot = slot_find_active_in_chain(4);
        if (slot >= 0 && g_spawn_entry_table[slot].ammo != 0 && math_fast_float_d(vars + 0x210)
            && (g_pad_pressed_flags[0] & 0x20)) {
            slot_subtract_value_clamped(4, 1);
            vec_a.q = 0;
            vec_a.f[2] = -0.1f;
            vec_a.f[3] = 1.0f;
            matrix_mul_vec3(&vec_b, &vec_a, moby + 0xc0);
            FastVecAdd(&vec_b, &vec_b, moby + 0x10);
            PlayMobySound(2, 0, moby);
            projectile_l05_spawn_pal(&vec_b, moby + 0xc0, I(vars, 0x18), moby, 0);
            I(vars, 0x210) = ((s32)(g_ship_shot_var_word_b) * 5 + 2) / 6;
            I(vars, 0x218) = 8;
        }
    }

    index = slot_find_active_in_chain(7);
    if (index >= 0 && g_spawn_entry_table[index].ammo != 0 && (g_pad_pressed_flags[0] & 0x80)) {
        char *voice = (char *)(g_ship_shot_voice_id * 112 + (int)g_sound_state);
        if (P(voice, 0x88) != moby || !B(voice, 0x74))
            g_ship_shot_voice_id = snd_play_from_class_bank(0x11, 4, moby, 0xfbf);
        if (++I(vars, 0x34) >= 7) {
            I(vars, 0x34) = 7;
            math_fast_float_d(&g_spawn_entry_table[index].ammo);
        }
    } else {
        if (g_ship_shot_voice_id != -1) {
            char *voice = (char *)(g_ship_shot_voice_id * 112 + (int)g_sound_state);
            if (P(voice, 0x88) == moby && B(voice, 0x74))
                snd_stop_voice(g_ship_shot_voice_id);
        }
        g_ship_shot_voice_id = -1;
        math_fast_float_d(vars + 0x34);
        if (I(vars, 0x34) == 0 && g_feltzin_mission_index % 3 == 0 && !(g_pad_pressed_flags[0] & 0x80)) {
            ++g_spawn_entry_table[index].ammo;
            if (g_spawn_entry_table[index].ammo > g_spawn_entry_table[index].maximum)
                g_spawn_entry_table[index].ammo = g_spawn_entry_table[index].maximum;
        }
    }

    if (!math_fast_float_d(vars + 0x218))
        I(vars, 0x214) = actuator_play_waves(g_slot_record_source);
}
