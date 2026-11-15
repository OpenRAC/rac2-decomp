/* func_PAL_L05_00449FF0, the PAL copy of func_L05_00443D08: the same C, where the five weapon
   timers are scaled to 50 Hz as they are stored, the 1/60 step becomes 0.02, the frame counts
   5, 7, 8 and 10 become 4, 6, 7 and 8, and the first three timer globals are read as ints. */
#include "common.h"
typedef unsigned int ShotQuad __attribute__((mode(TI)));
typedef union { ShotQuad q; float f[4]; } ShotVector;
extern int D_L05_001B2048, D_00138320[], D_L05_002A1940[];
typedef struct { int upgrade; char pad[12]; int maximum, ammo; char tail[16]; } WeaponSlot;
extern WeaponSlot D_L05_002A1800[];
extern char g_sound_state[],D_L05_002B8770[];
extern float D_L05_001B1A9C __attribute__((sda)), D_L05_001B1B70 __attribute__((sda));
extern int D_L05_001B1AA0 __attribute__((sda)),D_L05_001B1AA4 __attribute__((sda)),D_L05_001B1AA8 __attribute__((sda));
extern int D_L05_001B1AAC __attribute__((sda)),D_L05_001B1AB0 __attribute__((sda)),D_L05_001B1AFC __attribute__((sda));
extern float D_L05_001B1B30 __attribute__((sda)),D_L05_001B1B40 __attribute__((sda)),D_L05_001B1B50 __attribute__((sda)),D_L05_001B1B60 __attribute__((sda));
extern int FastDecTimer(void *),math_fast_float_d(void *),slot_find_active_in_chain(int);
extern void FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *),vec_scale_to_length(void *,void *,float),matrix_mul_vec3(void *,void *,void *),FastVecScale(void *,void *,float);
/* The sound call and the four spawners below return a value this function ignores. Declaring them
   void changes the code: their call_value is what ends the zero register's dependence on the later
   `v0 = 5`, which orders each clear's por after its constant and keeps the upgrade test in v1. */
extern int PlayMobySound(int,int,void *);
extern void slot_subtract_value_clamped(int,int);
extern char *func_PAL_L05_0041EA08(void *,void *,float,void *,int,int,int,int,int);
extern char *func_PAL_L05_003D46A8(void *,void *,int,void *,int),*func_PAL_L05_0039A808(void *,void *,int,void *,int),*func_PAL_L05_0042CAA0(void *,void *,int,void *,int,int),*func_PAL_L05_0042D3B8(void *,void *,int,void *,int);
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
void func_PAL_L05_00449FF0(char *m, char *driver)
{
    ShotVector a, b, c, d, e, f;
    char *driverState = P(driver, 0x70);
    char *s = P(m, 0x68);
    char *shot;
    int mode, index;

    if (H(driverState, 0xd8) && (D_L05_001B2048 & 1))
        return;

    if (FastDecTimer(s + 8) && (D_00138320[0] & 0x40)) {
        H(s, 8) = ((s32)(D_L05_001B1AA0) * 5 + 2) / 6;
        FastVecSub(&a, s + 0x20, driver + 0x30);
        vec_scale_to_length(&a, &a, D_L05_001B1A9C);
        FastVecAdd(&b, &a, driver + 0x30);
        mode = D_L05_002A1940[0];
        if (mode)
            matrix_mul_vec3(&c, &D_L05_001B1B50, m + 0xc0);
        else
            matrix_mul_vec3(&c, &D_L05_001B1B30, m + 0xc0);
        FastVecAdd(&c, &c, m + 0x10);
        FastVecSub(&d, &b, &c);
        PlayMobySound(3, 0, m);
        shot = func_PAL_L05_0041EA08(m, &c, -1.0f, &d, 0x2020ff, 0x20207f, 0, mode, 0);
        if (shot) {
            char *v = P(shot, 0x68);
            I(v, 0x28) = 0;
            F(v, 0x10) += F(driverState, 0x30);
            F(v, 0x14) += F(driverState, 0x34);
            F(v, 0x18) += F(driverState, 0x38);
            if (mode) {
                FastVecScale(&e, m + 0xd0, D_L05_001B1B70 * 0.020000001f);
                FastVecAdd(v + 0x10, v + 0x10, &e);
            }
        }
        if (mode)
            matrix_mul_vec3(&e, &D_L05_001B1B60, m + 0xc0);
        else
            matrix_mul_vec3(&e, &D_L05_001B1B40, m + 0xc0);
        FastVecAdd(&e, &e, m + 0x10);
        FastVecSub(&d, &b, &e);
        shot = func_PAL_L05_0041EA08(m, &e, 1.0f, &d, 0x2020ff, 0x20207f, 0, mode, 0);
        if (shot) {
            char *v = P(shot, 0x68);
            I(v, 0x28) = 0;
            F(v, 0x10) += F(driverState, 0x30);
            F(v, 0x14) += F(driverState, 0x34);
            F(v, 0x18) += F(driverState, 0x38);
            if (mode) {
                FastVecScale(&f, m + 0xd0, -(D_L05_001B1B70 * 0.020000001f));
                FastVecAdd(v + 0x10, v + 0x10, &f);
            }
        }
    }

    {
        int slot = slot_find_active_in_chain(1);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && FastDecTimer(s + 0xa)
            && (D_00138320[0] & 0x20)) {
            slot_subtract_value_clamped(1, 1);
            a.q = 0;
            a.f[2] = -0.1f;
            a.f[3] = 1.0f;
            matrix_mul_vec3(&b, &a, m + 0xc0);
            FastVecAdd(&b, &b, m + 0x10);
            PlayMobySound(2, 0, m);
            func_PAL_L05_003D46A8(&b, m + 0xc0, I(s, 0x18), m, D_L05_002A1800[9].upgrade);
            H(s, 0xa) = ((s32)(D_L05_001B1AA4) * 5 + 2) / 6;
            I(s, 0x218) = 4;
        }
    }

    {
        int slot = slot_find_active_in_chain(3);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && FastDecTimer(s + 0xa8)
            && (D_00138320[0] & 0x20)) {
            slot_subtract_value_clamped(3, 1);
            a.q = 0;
            a.f[2] = -0.1f;
            a.f[3] = 1.0f;
            matrix_mul_vec3(&b, &a, m + 0xc0);
            FastVecAdd(&b, &b, m + 0x10);
            PlayMobySound(2, 0, m);
            func_PAL_L05_0039A808(&b, m + 0xc0, I(s, 0x18), m, D_L05_002A1800[11].upgrade);
            H(s, 0xa8) = ((s32)(D_L05_001B1AA8) * 5 + 2) / 6;
            I(s, 0x218) = 4;
        }
    }

    {
        int slot = slot_find_active_in_chain(2);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && math_fast_float_d(s + 0x20c)
            && (D_00138320[0] & 0x20)) {
            slot_subtract_value_clamped(2, 1);
            a.q = 0;
            a.f[2] = -0.2f;
            a.f[3] = 1.0f;
            matrix_mul_vec3(&b, &a, m + 0xc0);
            FastVecAdd(&b, &b, m + 0x10);
            PlayMobySound(2, 0, m);
            func_PAL_L05_0042CAA0(&b, m + 0xc0, I(s, 0x18), m, D_L05_002A1800[10].upgrade, 1);
            if (D_L05_002A1800[10].upgrade) {
                c.q = 0;
                c.f[1] = -0.275f;
                c.f[3] = 1.0f;
                matrix_mul_vec3(&b, &c, m + 0xc0);
                FastVecAdd(&b, &b, m + 0x10);
                func_PAL_L05_0042CAA0(&b, m + 0xc0, I(s, 0x18), m, D_L05_002A1800[10].upgrade, 0);
                d.q = 0;
                d.f[1] = 0.275f;
                d.f[3] = 1.0f;
                matrix_mul_vec3(&b, &d, m + 0xc0);
                FastVecAdd(&b, &b, m + 0x10);
                func_PAL_L05_0042CAA0(&b, m + 0xc0, I(s, 0x18), m, D_L05_002A1800[10].upgrade, 0);
            }
            I(s, 0x20c) = ((s32)(D_L05_001B1AAC) * 5 + 2) / 6;
            I(s, 0x218) = 6;
        }
    }

    {
        int slot = slot_find_active_in_chain(4);
        if (slot >= 0 && D_L05_002A1800[slot].ammo != 0 && math_fast_float_d(s + 0x210)
            && (D_00138320[0] & 0x20)) {
            slot_subtract_value_clamped(4, 1);
            a.q = 0;
            a.f[2] = -0.1f;
            a.f[3] = 1.0f;
            matrix_mul_vec3(&b, &a, m + 0xc0);
            FastVecAdd(&b, &b, m + 0x10);
            PlayMobySound(2, 0, m);
            func_PAL_L05_0042D3B8(&b, m + 0xc0, I(s, 0x18), m, 0);
            I(s, 0x210) = ((s32)(D_L05_001B1AB0) * 5 + 2) / 6;
            I(s, 0x218) = 8;
        }
    }

    index = slot_find_active_in_chain(7);
    if (index >= 0 && D_L05_002A1800[index].ammo != 0 && (D_00138320[0] & 0x80)) {
        char *v = (char *)(D_L05_001B1AFC * 112 + (int)g_sound_state);
        if (P(v, 0x88) != m || !B(v, 0x74))
            D_L05_001B1AFC = snd_play_from_class_bank(0x11, 4, m, 0xfbf);
        if (++I(s, 0x34) >= 7) {
            I(s, 0x34) = 7;
            math_fast_float_d(&D_L05_002A1800[index].ammo);
        }
    } else {
        if (D_L05_001B1AFC != -1) {
            char *v = (char *)(D_L05_001B1AFC * 112 + (int)g_sound_state);
            if (P(v, 0x88) == m && B(v, 0x74))
                snd_stop_voice(D_L05_001B1AFC);
        }
        D_L05_001B1AFC = -1;
        math_fast_float_d(s + 0x34);
        if (I(s, 0x34) == 0 && D_L05_001B2048 % 3 == 0 && !(D_00138320[0] & 0x80)) {
            ++D_L05_002A1800[index].ammo;
            if (D_L05_002A1800[index].ammo > D_L05_002A1800[index].maximum)
                D_L05_002A1800[index].ammo = D_L05_002A1800[index].maximum;
        }
    }

    if (!math_fast_float_d(s + 0x218))
        I(s, 0x214) = slot_copy_records_to_free(D_L05_002B8770);
}
