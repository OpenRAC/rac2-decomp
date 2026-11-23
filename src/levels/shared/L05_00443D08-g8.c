#include "common.h"
typedef unsigned int ShotQuad __attribute__((mode(TI)));
typedef union { ShotQuad q; float f[4]; } ShotVector;
extern int g_feltzin_mission_index, g_pad_pressed_flags[], g_ship_mode_words[];
typedef struct { int upgrade; char pad[12]; int maximum, ammo; char tail[16]; } WeaponSlot;
extern WeaponSlot g_spawn_entry_table[];
extern char g_sound_state[],g_slot_record_source[];
extern float g_ship_aim_length __attribute__((sda)), g_ship_muzzle_speed __attribute__((sda));
extern unsigned short g_ship_shot_var_half_a __attribute__((sda)),g_ship_shot_var_half_b __attribute__((sda)),g_ship_shot_var_half_c __attribute__((sda));
extern int g_ship_shot_var_word_a __attribute__((sda)),g_ship_shot_var_word_b __attribute__((sda)),g_ship_shot_voice_id __attribute__((sda));
extern float g_ship_muzzle_left_offset __attribute__((sda)),g_ship_muzzle_right_offset __attribute__((sda)),g_ship_muzzle_left_alt_offset __attribute__((sda)),g_ship_muzzle_right_alt_offset __attribute__((sda));
extern int FastDecTimer(void *),math_fast_float_d(void *),slot_find_active_in_chain(int);
extern void FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *),vec_scale_to_length(void *,void *,float),matrix_mul_vec3(void *,void *,void *),FastVecScale(void *,void *,float);
/* The sound call and the four spawners below return a value this function ignores. Declaring them
   void changes the code: their call_value is what ends the zero register's dependence on the later
   `v0 = 5`, which orders each clear's por after its constant and keeps the upgrade test in v1. */
extern int PlayMobySound(int,int,void *);
extern void slot_subtract_value_clamped(int,int);
extern char *moby_spawn_shot_effect(void *,void *,float,void *,int,int,int,int,int);
extern char *func_L05_003D0960(void *,void *,int,void *,int),*func_L05_003979B0(void *,void *,int,void *,int),*projectile_spawn_with_target(void *,void *,int,void *,int,int),*projectile_l05_spawn(void *,void *,int,void *,int);
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
/* Fires the ship's guns when the player presses fire. This covers the twin shots, the four special weapons and the held beam with its ammo recharge. */
void UpdateShipWeapons(char *moby, char *driver)
{
    ShotVector aim, base, muzzle_left, shot_dir, muzzle_right, kick;
    char *driverState = P(driver, 0x70);
    char *vars = P(moby, 0x68);
    char *shot;
    int mode, index;

    if (H(driverState, 0xd8) && (g_feltzin_mission_index & 1))
        return;

    if (FastDecTimer(vars + 8) && (g_pad_pressed_flags[0] & 0x40)) {
        H(vars, 8) = g_ship_shot_var_half_a;
        FastVecSub(&aim, vars + 0x20, driver + 0x30);
        vec_scale_to_length(&aim, &aim, g_ship_aim_length);
        FastVecAdd(&base, &aim, driver + 0x30);
        mode = g_ship_mode_words[0];
        if (mode)
            matrix_mul_vec3(&muzzle_left, &g_ship_muzzle_left_alt_offset, moby + 0xc0);
        else
            matrix_mul_vec3(&muzzle_left, &g_ship_muzzle_left_offset, moby + 0xc0);
        FastVecAdd(&muzzle_left, &muzzle_left, moby + 0x10);
        FastVecSub(&shot_dir, &base, &muzzle_left);
        PlayMobySound(3, 0, moby);
        shot = moby_spawn_shot_effect(moby, &muzzle_left, -1.0f, &shot_dir, 0x2020ff, 0x20207f, 0, mode, 0);
        if (shot) {
            char *shot_vars = P(shot, 0x68);
            I(shot_vars, 0x28) = 0;
            F(shot_vars, 0x10) += F(driverState, 0x30);
            F(shot_vars, 0x14) += F(driverState, 0x34);
            F(shot_vars, 0x18) += F(driverState, 0x38);
            if (mode) {
                FastVecScale(&muzzle_right, moby + 0xd0, g_ship_muzzle_speed * 0.01666666753590107f);
                FastVecAdd(shot_vars + 0x10, shot_vars + 0x10, &muzzle_right);
            }
        }
        if (mode)
            matrix_mul_vec3(&muzzle_right, &g_ship_muzzle_right_alt_offset, moby + 0xc0);
        else
            matrix_mul_vec3(&muzzle_right, &g_ship_muzzle_right_offset, moby + 0xc0);
        FastVecAdd(&muzzle_right, &muzzle_right, moby + 0x10);
        FastVecSub(&shot_dir, &base, &muzzle_right);
        shot = moby_spawn_shot_effect(moby, &muzzle_right, 1.0f, &shot_dir, 0x2020ff, 0x20207f, 0, mode, 0);
        if (shot) {
            char *shot_vars = P(shot, 0x68);
            I(shot_vars, 0x28) = 0;
            F(shot_vars, 0x10) += F(driverState, 0x30);
            F(shot_vars, 0x14) += F(driverState, 0x34);
            F(shot_vars, 0x18) += F(driverState, 0x38);
            if (mode) {
                FastVecScale(&kick, moby + 0xd0, -(g_ship_muzzle_speed * 0.01666666753590107f));
                FastVecAdd(shot_vars + 0x10, shot_vars + 0x10, &kick);
            }
        }
    }

    {
        int slot = slot_find_active_in_chain(1);
        if (slot >= 0 && g_spawn_entry_table[slot].ammo != 0 && FastDecTimer(vars + 0xa)
            && (g_pad_pressed_flags[0] & 0x20)) {
            slot_subtract_value_clamped(1, 1);
            aim.q = 0;
            aim.f[2] = -0.1f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            func_L05_003D0960(&base, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[9].upgrade);
            H(vars, 0xa) = g_ship_shot_var_half_b;
            I(vars, 0x218) = 5;
        }
    }

    {
        int slot = slot_find_active_in_chain(3);
        if (slot >= 0 && g_spawn_entry_table[slot].ammo != 0 && FastDecTimer(vars + 0xa8)
            && (g_pad_pressed_flags[0] & 0x20)) {
            slot_subtract_value_clamped(3, 1);
            aim.q = 0;
            aim.f[2] = -0.1f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            func_L05_003979B0(&base, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[11].upgrade);
            H(vars, 0xa8) = g_ship_shot_var_half_c;
            I(vars, 0x218) = 5;
        }
    }

    {
        int slot = slot_find_active_in_chain(2);
        if (slot >= 0 && g_spawn_entry_table[slot].ammo != 0 && math_fast_float_d(vars + 0x20c)
            && (g_pad_pressed_flags[0] & 0x20)) {
            slot_subtract_value_clamped(2, 1);
            aim.q = 0;
            aim.f[2] = -0.2f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            projectile_spawn_with_target(&base, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[10].upgrade, 1);
            if (g_spawn_entry_table[10].upgrade) {
                muzzle_left.q = 0;
                muzzle_left.f[1] = -0.275f;
                muzzle_left.f[3] = 1.0f;
                matrix_mul_vec3(&base, &muzzle_left, moby + 0xc0);
                FastVecAdd(&base, &base, moby + 0x10);
                projectile_spawn_with_target(&base, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[10].upgrade, 0);
                shot_dir.q = 0;
                shot_dir.f[1] = 0.275f;
                shot_dir.f[3] = 1.0f;
                matrix_mul_vec3(&base, &shot_dir, moby + 0xc0);
                FastVecAdd(&base, &base, moby + 0x10);
                projectile_spawn_with_target(&base, moby + 0xc0, I(vars, 0x18), moby, g_spawn_entry_table[10].upgrade, 0);
            }
            I(vars, 0x20c) = g_ship_shot_var_word_a;
            I(vars, 0x218) = 7;
        }
    }

    {
        int slot = slot_find_active_in_chain(4);
        if (slot >= 0 && g_spawn_entry_table[slot].ammo != 0 && math_fast_float_d(vars + 0x210)
            && (g_pad_pressed_flags[0] & 0x20)) {
            slot_subtract_value_clamped(4, 1);
            aim.q = 0;
            aim.f[2] = -0.1f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            projectile_l05_spawn(&base, moby + 0xc0, I(vars, 0x18), moby, 0);
            I(vars, 0x210) = g_ship_shot_var_word_b;
            I(vars, 0x218) = 10;
        }
    }

    index = slot_find_active_in_chain(7);
    if (index >= 0 && g_spawn_entry_table[index].ammo != 0 && (g_pad_pressed_flags[0] & 0x80)) {
        char *shot_vars = (char *)(g_ship_shot_voice_id * 112 + (int)g_sound_state);
        if (P(shot_vars, 0x88) != moby || !B(shot_vars, 0x74))
            g_ship_shot_voice_id = snd_play_from_class_bank(0x11, 4, moby, 0xfbf);
        if (++I(vars, 0x34) >= 8) {
            I(vars, 0x34) = 8;
            math_fast_float_d(&g_spawn_entry_table[index].ammo);
        }
    } else {
        if (g_ship_shot_voice_id != -1) {
            char *shot_vars = (char *)(g_ship_shot_voice_id * 112 + (int)g_sound_state);
            if (P(shot_vars, 0x88) == moby && B(shot_vars, 0x74))
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
