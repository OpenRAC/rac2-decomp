#include "common.h"
typedef unsigned int ShotQuad __attribute__((mode(TI)));
typedef union { ShotQuad q; float f[4]; } ShotVector;
extern int D_L05_001B2048, D_00138320[], D_L05_002A1940[];
typedef struct { int upgrade; char pad[12]; int maximum, ammo; char tail[16]; } WeaponSlot;
extern WeaponSlot D_L05_002A1800[];
extern char g_sound_state[],D_L05_002B8770[];
extern float D_L05_001B1A9C __attribute__((sda)), D_L05_001B1B70 __attribute__((sda));
extern unsigned short D_L05_001B1AA0 __attribute__((sda)),D_L05_001B1AA4 __attribute__((sda)),D_L05_001B1AA8 __attribute__((sda));
extern int D_L05_001B1AAC __attribute__((sda)),D_L05_001B1AB0 __attribute__((sda)),D_L05_001B1AFC __attribute__((sda));
extern float D_L05_001B1B30 __attribute__((sda)),D_L05_001B1B40 __attribute__((sda)),D_L05_001B1B50 __attribute__((sda)),D_L05_001B1B60 __attribute__((sda));
extern int FastDecTimer(void *),math_fast_float_d(void *),slot_find_active_in_chain(int);
extern void FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *),vec_scale_to_length(void *,void *,float),matrix_mul_vec3(void *,void *,void *),FastVecScale(void *,void *,float);
/* The sound call and the four spawners below return a value this function ignores. Declaring them
   void changes the code: their call_value is what ends the zero register's dependence on the later
   `v0 = 5`, which orders each clear's por after its constant and keeps the upgrade test in v1. */
extern int PlayMobySound(int,int,void *);
extern void slot_subtract_value_clamped(int,int);
extern char *moby_spawn_shot_effect(void *,void *,float,void *,int,int,int,int,int);
extern char *func_L05_003D0960(void *,void *,int,void *,int),*func_L05_003979B0(void *,void *,int,void *,int),*projectile_spawn_with_target(void *,void *,int,void *,int,int),*projectile_l05_spawn(void *,void *,int,void *,int);
extern int snd_play_from_class_bank(int,int,void *,int),slot_copy_records_to_free(void *);
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
    ShotVector aim, base, muzzleLeft, shotDir, muzzleRight, kick;
    char *driverState = P(driver, 0x70);
    char *vars = P(moby, 0x68);
    char *shot;
    int mode, index;

    if (H(driverState, 0xd8) && (D_L05_001B2048 & 1))
        return;

    if (FastDecTimer(vars + 8) && (D_00138320[0] & 0x40)) {
        H(vars, 8) = D_L05_001B1AA0;
        FastVecSub(&aim, vars + 0x20, driver + 0x30);
        vec_scale_to_length(&aim, &aim, D_L05_001B1A9C);
        FastVecAdd(&base, &aim, driver + 0x30);
        mode = D_L05_002A1940[0];
        if (mode)
            matrix_mul_vec3(&muzzleLeft, &D_L05_001B1B50, moby + 0xc0);
        else
            matrix_mul_vec3(&muzzleLeft, &D_L05_001B1B30, moby + 0xc0);
        FastVecAdd(&muzzleLeft, &muzzleLeft, moby + 0x10);
        FastVecSub(&shotDir, &base, &muzzleLeft);
        PlayMobySound(3, 0, moby);
        shot = moby_spawn_shot_effect(moby, &muzzleLeft, -1.0f, &shotDir, 0x2020ff, 0x20207f, 0, mode, 0);
        if (shot) {
            char *shotVars = P(shot, 0x68);
            I(shotVars, 0x28) = 0;
            F(shotVars, 0x10) += F(driverState, 0x30);
            F(shotVars, 0x14) += F(driverState, 0x34);
            F(shotVars, 0x18) += F(driverState, 0x38);
            if (mode) {
                FastVecScale(&muzzleRight, moby + 0xd0, D_L05_001B1B70 * 0.01666666753590107f);
                FastVecAdd(shotVars + 0x10, shotVars + 0x10, &muzzleRight);
            }
        }
        if (mode)
            matrix_mul_vec3(&muzzleRight, &D_L05_001B1B60, moby + 0xc0);
        else
            matrix_mul_vec3(&muzzleRight, &D_L05_001B1B40, moby + 0xc0);
        FastVecAdd(&muzzleRight, &muzzleRight, moby + 0x10);
        FastVecSub(&shotDir, &base, &muzzleRight);
        shot = moby_spawn_shot_effect(moby, &muzzleRight, 1.0f, &shotDir, 0x2020ff, 0x20207f, 0, mode, 0);
        if (shot) {
            char *shotVars = P(shot, 0x68);
            I(shotVars, 0x28) = 0;
            F(shotVars, 0x10) += F(driverState, 0x30);
            F(shotVars, 0x14) += F(driverState, 0x34);
            F(shotVars, 0x18) += F(driverState, 0x38);
            if (mode) {
                FastVecScale(&kick, moby + 0xd0, -(D_L05_001B1B70 * 0.01666666753590107f));
                FastVecAdd(shotVars + 0x10, shotVars + 0x10, &kick);
            }
        }
    }

    {
        int slot = slot_find_active_in_chain(1);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && FastDecTimer(vars + 0xa)
            && (D_00138320[0] & 0x20)) {
            slot_subtract_value_clamped(1, 1);
            aim.q = 0;
            aim.f[2] = -0.1f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            func_L05_003D0960(&base, moby + 0xc0, I(vars, 0x18), moby, D_L05_002A1800[9].upgrade);
            H(vars, 0xa) = D_L05_001B1AA4;
            I(vars, 0x218) = 5;
        }
    }

    {
        int slot = slot_find_active_in_chain(3);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && FastDecTimer(vars + 0xa8)
            && (D_00138320[0] & 0x20)) {
            slot_subtract_value_clamped(3, 1);
            aim.q = 0;
            aim.f[2] = -0.1f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            func_L05_003979B0(&base, moby + 0xc0, I(vars, 0x18), moby, D_L05_002A1800[11].upgrade);
            H(vars, 0xa8) = D_L05_001B1AA8;
            I(vars, 0x218) = 5;
        }
    }

    {
        int slot = slot_find_active_in_chain(2);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && math_fast_float_d(vars + 0x20c)
            && (D_00138320[0] & 0x20)) {
            slot_subtract_value_clamped(2, 1);
            aim.q = 0;
            aim.f[2] = -0.2f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            projectile_spawn_with_target(&base, moby + 0xc0, I(vars, 0x18), moby, D_L05_002A1800[10].upgrade, 1);
            if (D_L05_002A1800[10].upgrade) {
                muzzleLeft.q = 0;
                muzzleLeft.f[1] = -0.275f;
                muzzleLeft.f[3] = 1.0f;
                matrix_mul_vec3(&base, &muzzleLeft, moby + 0xc0);
                FastVecAdd(&base, &base, moby + 0x10);
                projectile_spawn_with_target(&base, moby + 0xc0, I(vars, 0x18), moby, D_L05_002A1800[10].upgrade, 0);
                shotDir.q = 0;
                shotDir.f[1] = 0.275f;
                shotDir.f[3] = 1.0f;
                matrix_mul_vec3(&base, &shotDir, moby + 0xc0);
                FastVecAdd(&base, &base, moby + 0x10);
                projectile_spawn_with_target(&base, moby + 0xc0, I(vars, 0x18), moby, D_L05_002A1800[10].upgrade, 0);
            }
            I(vars, 0x20c) = D_L05_001B1AAC;
            I(vars, 0x218) = 7;
        }
    }

    {
        int slot = slot_find_active_in_chain(4);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && math_fast_float_d(vars + 0x210)
            && (D_00138320[0] & 0x20)) {
            slot_subtract_value_clamped(4, 1);
            aim.q = 0;
            aim.f[2] = -0.1f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            projectile_l05_spawn(&base, moby + 0xc0, I(vars, 0x18), moby, 0);
            I(vars, 0x210) = D_L05_001B1AB0;
            I(vars, 0x218) = 10;
        }
    }

    index = slot_find_active_in_chain(7);
    if (index >= 0 && D_L05_002A1800[index].ammo != 0 && (D_00138320[0] & 0x80)) {
        char *shotVars = (char *)(D_L05_001B1AFC * 112 + (int)g_sound_state);
        if (P(shotVars, 0x88) != moby || !B(shotVars, 0x74))
            D_L05_001B1AFC = snd_play_from_class_bank(0x11, 4, moby, 0xfbf);
        if (++I(vars, 0x34) >= 8) {
            I(vars, 0x34) = 8;
            math_fast_float_d(&D_L05_002A1800[index].ammo);
        }
    } else {
        if (D_L05_001B1AFC != -1) {
            char *shotVars = (char *)(D_L05_001B1AFC * 112 + (int)g_sound_state);
            if (P(shotVars, 0x88) == moby && B(shotVars, 0x74))
                snd_stop_voice(D_L05_001B1AFC);
        }
        D_L05_001B1AFC = -1;
        math_fast_float_d(vars + 0x34);
        if (I(vars, 0x34) == 0 && D_L05_001B2048 % 3 == 0 && !(D_00138320[0] & 0x80)) {
            ++D_L05_002A1800[index].ammo;
            if (D_L05_002A1800[index].ammo > D_L05_002A1800[index].maximum)
                D_L05_002A1800[index].ammo = D_L05_002A1800[index].maximum;
        }
    }

    if (!math_fast_float_d(vars + 0x218))
        I(vars, 0x214) = slot_copy_records_to_free(D_L05_002B8770);
}
