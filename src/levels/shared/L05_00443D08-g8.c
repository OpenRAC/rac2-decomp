#include "common.h"
typedef unsigned int ShotQuad __attribute__((mode(TI)));
typedef union { ShotQuad q; float f[4]; } ShotVector;
extern int D_L05_001B2048, D_00138320[], D_L05_002A1940[];
typedef struct { int upgrade; char pad[12]; int maximum, ammo; char tail[16]; } WeaponSlot;
extern WeaponSlot D_L05_002A1800[];
extern char D_00188660[],D_L05_002B8770[];
extern float D_L05_001B1A9C __attribute__((sda)), D_L05_001B1B70 __attribute__((sda));
extern unsigned short D_L05_001B1AA0 __attribute__((sda)),D_L05_001B1AA4 __attribute__((sda)),D_L05_001B1AA8 __attribute__((sda));
extern int D_L05_001B1AAC __attribute__((sda)),D_L05_001B1AB0 __attribute__((sda)),D_L05_001B1AFC __attribute__((sda));
extern float D_L05_001B1B30 __attribute__((sda)),D_L05_001B1B40 __attribute__((sda)),D_L05_001B1B50 __attribute__((sda)),D_L05_001B1B60 __attribute__((sda));
extern int func_00282978(void *),func_00282948(void *),func_L05_0037AA88(int);
extern void func_00282CF0(void *,void *,void *),func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float),func_00283098(void *,void *,void *),func_00282D30(void *,void *,float);
/* The sound call and the four spawners below return a value this function ignores. Declaring them
   void changes the code: their call_value is what ends the zero register's dependence on the later
   `v0 = 5`, which orders each clear's por after its constant and keeps the upgrade test in v1. */
extern int func_002E5CF8(int,int,void *);
extern void func_L05_0037AB18(int,int);
extern char *func_L05_00419CC8(void *,void *,float,void *,int,int,int,int,int);
extern char *func_L05_003D0960(void *,void *,int,void *,int),*func_L05_003979B0(void *,void *,int,void *,int),*func_L05_00427090(void *,void *,int,void *,int,int),*func_L05_00427988(void *,void *,int,void *,int);
extern int func_002E5DA0(int,int,void *,int),func_L00_002D6998(void *);
extern void func_002E59F8(int);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
/* Fires the ship's weapons for one frame: a pair of shots on input bit 0x40, four weapons on
   input bit 0x20, each behind its own timer, and a held weapon on 0x80, whose ammunition
   recharges every third frame while it is released. */
/* Fires the ship's guns when the player presses fire. This covers the twin shots, the four special weapons and the held beam with its ammo recharge. */
void func_L05_00443D08(char *moby, char *driver)
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
        shot = SpawnShotEffectMoby(moby, &muzzleLeft, -1.0f, &shotDir, 0x2020ff, 0x20207f, 0, mode, 0);
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
        shot = SpawnShotEffectMoby(moby, &muzzleRight, 1.0f, &shotDir, 0x2020ff, 0x20207f, 0, mode, 0);
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
        int slot = FindActiveSlotInChain(1);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && FastDecTimer(vars + 0xa)
            && (D_00138320[0] & 0x20)) {
            SubtractSlotValueClamped(1, 1);
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
        int slot = FindActiveSlotInChain(3);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && FastDecTimer(vars + 0xa8)
            && (D_00138320[0] & 0x20)) {
            SubtractSlotValueClamped(3, 1);
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
        int slot = FindActiveSlotInChain(2);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && FastFloatHelperD(vars + 0x20c)
            && (D_00138320[0] & 0x20)) {
            SubtractSlotValueClamped(2, 1);
            aim.q = 0;
            aim.f[2] = -0.2f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            SpawnProjectileWithTarget(&base, moby + 0xc0, I(vars, 0x18), moby, D_L05_002A1800[10].upgrade, 1);
            if (D_L05_002A1800[10].upgrade) {
                muzzleLeft.q = 0;
                muzzleLeft.f[1] = -0.275f;
                muzzleLeft.f[3] = 1.0f;
                matrix_mul_vec3(&base, &muzzleLeft, moby + 0xc0);
                FastVecAdd(&base, &base, moby + 0x10);
                SpawnProjectileWithTarget(&base, moby + 0xc0, I(vars, 0x18), moby, D_L05_002A1800[10].upgrade, 0);
                shotDir.q = 0;
                shotDir.f[1] = 0.275f;
                shotDir.f[3] = 1.0f;
                matrix_mul_vec3(&base, &shotDir, moby + 0xc0);
                FastVecAdd(&base, &base, moby + 0x10);
                SpawnProjectileWithTarget(&base, moby + 0xc0, I(vars, 0x18), moby, D_L05_002A1800[10].upgrade, 0);
            }
            I(vars, 0x20c) = D_L05_001B1AAC;
            I(vars, 0x218) = 7;
        }
    }

    {
        int slot = FindActiveSlotInChain(4);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && FastFloatHelperD(vars + 0x210)
            && (D_00138320[0] & 0x20)) {
            SubtractSlotValueClamped(4, 1);
            aim.q = 0;
            aim.f[2] = -0.1f;
            aim.f[3] = 1.0f;
            matrix_mul_vec3(&base, &aim, moby + 0xc0);
            FastVecAdd(&base, &base, moby + 0x10);
            PlayMobySound(2, 0, moby);
            SpawnProjectile_L05(&base, moby + 0xc0, I(vars, 0x18), moby, 0);
            I(vars, 0x210) = D_L05_001B1AB0;
            I(vars, 0x218) = 10;
        }
    }

    index = FindActiveSlotInChain(7);
    if (index >= 0 && D_L05_002A1800[index].ammo != 0 && (D_00138320[0] & 0x80)) {
        char *shotVars = (char *)(D_L05_001B1AFC * 112 + (int)gSoundState);
        if (P(shotVars, 0x88) != moby || !B(shotVars, 0x74))
            D_L05_001B1AFC = PlaySoundFromClassBank(0x11, 4, moby, 0xfbf);
        if (++I(vars, 0x34) >= 8) {
            I(vars, 0x34) = 8;
            FastFloatHelperD(&D_L05_002A1800[index].ammo);
        }
    } else {
        if (D_L05_001B1AFC != -1) {
            char *shotVars = (char *)(D_L05_001B1AFC * 112 + (int)gSoundState);
            if (P(shotVars, 0x88) == moby && B(shotVars, 0x74))
                StopSoundVoice(D_L05_001B1AFC);
        }
        D_L05_001B1AFC = -1;
        FastFloatHelperD(vars + 0x34);
        if (I(vars, 0x34) == 0 && D_L05_001B2048 % 3 == 0 && !(D_00138320[0] & 0x80)) {
            ++D_L05_002A1800[index].ammo;
            if (D_L05_002A1800[index].ammo > D_L05_002A1800[index].maximum)
                D_L05_002A1800[index].ammo = D_L05_002A1800[index].maximum;
        }
    }

    if (!FastFloatHelperD(vars + 0x218))
        I(vars, 0x214) = CopyRecordsToFreeSlots(D_L05_002B8770);
}
