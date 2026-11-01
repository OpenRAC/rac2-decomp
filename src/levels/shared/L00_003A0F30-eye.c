#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
/* Measured resident player-state prefix; fields beyond this prefix are unknown. */
typedef struct {
    char p0[0x760]; float facing[4];
    char p00[0x488]; char *aimTarget;
    char p1[0x634]; unsigned int buttons;
    char p2[0xC]; int inputTicks;
    char p3[0x20C]; char *overrideTarget;
    char p4[0xE3C]; char *hero; int mode;
    char p5[0x24]; u8 blocked;
    char p6[0x22F]; short viewMode;
    char p7[0x46]; int inputTimer;
} PlayerStatePrefix;
extern PlayerStatePrefix D_00189E20;
extern u8 D_00139584[];
extern unsigned int D_00138180[];
typedef struct { int mode; char pad[0x18]; float time; } Ctrl0F30;
extern Ctrl0F30 D_L00_001B2840 __attribute__((sda));
extern int D_L00_001AF5CC __attribute__((sda));
extern float D_L00_001AF5D0 __attribute__((sda));
extern float D_L00_001AF5D4 __attribute__((sda));
extern float D_L00_001AF5D8 __attribute__((sda));
extern float D_L00_001AF5DC __attribute__((sda));
extern float D_L00_001AF5E0 __attribute__((sda));
extern int D_L00_001AF5E4 __attribute__((sda));
extern char *D_L00_001AF5E8 __attribute__((sda));
extern int D_L00_001AF5EC __attribute__((sda));
typedef struct {
    float angle0[3], speed0[3], scale0[3];
    float angle1[3], speed1[3], scale1[3];
    float padding[2];
    VectorBits output0, output1;
    char tail[16];
} BeamOscillator;
extern BeamOscillator D_L00_0023B510[4];
typedef struct { char prefix[0x54]; float rate; char tail[0x88]; } WeaponEntry;
extern WeaponEntry D_L00_00262570[];
extern int func_00282948(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_0029F978(u8 *, u32, u8 *);
extern int func_L00_00329E90(void *, int, void *);
extern char *func_L00_0032A088(int, int);
extern float func_002A78D8(float, float), func_002A7878(float, float);
extern void func_00282C88(VectorBits *);
extern void func_L00_002C42E0(int, int);
extern int func_L00_002D4040(int);
extern void func_00273318(void *, unsigned int, int, int, int, int, float, float, float);
extern int func_002829D8(void *);
extern int func_L00_003BB5F0(void);
extern int func_L00_002D3F30(int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_0029FCC0(char *, int, char *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_0032A1A8(char *, char *, char *, float);
extern void *func_L00_003BB080(char *, char *, char *, char *);
extern void func_L00_003A1580(void *);
/* The binder: func_L00_002E6EF8 in 23 programs, its twin func_L08_002F2D10 in levels 08, 09,
   19 and 30, so the call carries a name without an address. */
extern void ref_L00_003A0F30_00(void (*)(void *), void *);
extern float func_00283B98(float, float), func_00283198(float), func_00283180(float);

/* Initialize the beam oscillators and update the weapon's charge cycle. */
void func_L00_003A0F30(char *moby)
{
    float velocity[4], origin[4], query[4];
    char *state = *(char **)(moby + 0x68);
    int ready = 1;
    if (D_00189E20.mode == 29) {
        if (func_00282948(&D_00189E20.inputTimer) == 0)
            ready = 0;
    }
    else
        D_00189E20.inputTimer = 40;
    if (D_00189E20.overrideTarget)
        D_00189E20.aimTarget = (char *)D_00189E20.overrideTarget;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0: {
        int i, handle;
        *(float *)state = 0.3666666746f;
        *(unsigned char *)(moby + 0x20) = 1;
        D_L00_001B2840.time = -1.0f;
        D_L00_001AF5E4 = 0;
        D_L00_001AF5CC = 0;
        if (*(unsigned char *)(moby + 0x43) || (*(unsigned char *)(moby + 0x60) & 2))
            func_002A7470(moby, 1, 0, 0);
        *(int *)(state + 0xC) = 0;
        *(int *)(state + 0x10) = 0;
        func_0029F978((u8 *)moby, 0, (u8 *)state + 0x20);
        handle = func_L00_00329E90(moby, 0, query);
        *(int *)(state + 4) = handle;
        *(char **)(state + 8) = func_L00_0032A088(*(short *)(moby + 0xAA), handle);
        for (i = 0; i < 4; i++) {
            BeamOscillator *entry = &D_L00_0023B510[i];
            entry->angle0[0] = 0.0f; entry->angle0[1] = 0.0f; entry->angle0[2] = 0.0f;
            entry->speed0[0] = func_002A78D8(0.05f, 0.3f);
            entry->speed0[1] = func_002A78D8(0.05f, 0.3f);
            entry->speed0[2] = func_002A78D8(0.05f, 0.3f);
            entry->scale0[0] = func_002A7878(0.25f, 0.75f);
            entry->scale0[1] = func_002A7878(0.25f, 0.75f);
            entry->scale0[2] = func_002A7878(0.25f, 0.75f);
            entry->angle1[0] = 0.0f; entry->angle1[1] = 0.0f; entry->angle1[2] = 0.0f;
            entry->speed1[0] = func_002A78D8(0.05f, 0.3f);
            entry->speed1[1] = func_002A78D8(0.05f, 0.3f);
            entry->speed1[2] = func_002A78D8(0.05f, 0.3f);
            entry->scale1[0] = func_002A7878(0.25f, 0.75f);
            entry->scale1[1] = func_002A7878(0.25f, 0.75f);
            entry->scale1[2] = func_002A7878(0.25f, 0.75f);
            func_00282C88(&D_L00_0023B510[i].output0);
            func_00282C88(&D_L00_0023B510[i].output1);
        }
        return;
    }
    case 1: {
    D_L00_001B2840.time = -1.0f;
    if (D_L00_001AF5CC == 0) {
        *(int *)(state + 0xC) = 0;
        D_L00_001AF5CC = 1;
    }
    if (D_00189E20.mode == 1)
        func_L00_002C42E0(29, 1);
    if (D_00189E20.mode == 29) {
        unsigned int color;
        if (*(float *)state != 0.0f && func_L00_002D4040(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        func_00273318(moby, color, 0, 0x26, -1, 4, 1.0f, 0.0f, 90.0f);
    }
    if (func_002829D8(state) && ready && !D_00189E20.blocked && (D_00138180[0x68] & D_00189E20.buttons) &&
        !func_L00_003BB5F0() && D_00189E20.inputTicks > 22) {
        if (func_L00_002D3F30(-1, 1)) {
            D_L00_001B2840.mode = 1;
            func_002E5CF8(2, 0, moby);
            {
                float cooldown;
                switch (D_L00_001AF5E4) {
                case 0: {
                    WeaponEntry *weapon;
                    int index;
                    D_L00_001AF5E4 = 1;
                    *(float *)(state + 0xC) = D_L00_001AF5D8;
                    weapon = &D_L00_00262570[D_00139584[0]];
                    cooldown = 1.0f / weapon->rate;
                    break;
                }
                case 2: {
                    WeaponEntry *weapon;
                    int index;
                    D_L00_001AF5E4 = 1;
                    weapon = &D_L00_00262570[D_00139584[0]];
                    cooldown = 1.0f / weapon->rate;
                    break;
                }
                default:
                    goto updateCharge;
                }
                *(float *)state = cooldown;
            }
        } else if ((D_00138180[0x69] & D_00189E20.buttons) || D_L00_001B2840.mode == 1) {
            func_002E5CF8(6, 0, moby);
            D_L00_001B2840.mode = 0;
        }
    }
updateCharge:
    switch (D_L00_001AF5E4) {
    case 0: {
        float charge = *(float *)(state + 0xC);
        float minimum = D_L00_001AF5D8;
        if (charge < minimum) {
            float next = charge + D_L00_001AF5DC;
            *(float *)(state + 0xC) = next;
            if (next > minimum)
                *(float *)(state + 0xC) = minimum;
        }
        break;
    }
    case 1: {
        float charge = *(float *)(state + 0xC) + D_L00_001AF5D0;
        float limit = D_L00_001AF5E0;
        *(float *)(state + 0xC) = charge;
        if (charge > limit) {
            float speed;
            func_0029FCC0(moby, 0, (char *)origin);
            speed = 0.3333333433f;
            if (D_00189E20.viewMode == 1) {
                speed = -speed;
                func_00282F20(velocity, moby + 0xD0, speed);
            } else
                func_00282F20(velocity, D_00189E20.facing, speed);
            if (D_00189E20.aimTarget)
                func_L00_0032A1A8(D_00189E20.aimTarget, (char *)origin, (char *)velocity, 0.3333333433f);
            D_L00_001AF5E8 = func_L00_003BB080(moby, (char *)*(int *)(state + 4), (char *)origin, (char *)velocity);
            if (D_L00_001AF5E8)
                *(char **)(D_L00_001AF5E8 + 0xB8) = moby;
            D_L00_001AF5EC = 50;
            D_L00_001AF5E4 = 2;
        }
        break;
    }
    case 2: {
        float charge = *(float *)(state + 0xC) - D_L00_001AF5D4;
        float minimum = D_L00_001AF5D8;
        *(float *)(state + 0xC) = charge;
        if (charge <= minimum) {
            *(float *)(state + 0xC) = minimum;
            D_L00_001AF5E4 = 0;
        }
    }
    }
    if (*(unsigned char *)(moby + 0x31))
        ref_L00_003A0F30_00(func_L00_003A1580, moby);
    *(float *)(state + 0x10) = func_00283B98(*(float *)(state + 0x10), *(float *)(state + 0xC) * 0.3141593039f);
    *(float *)(state + 0x30) = func_00283198(*(float *)(state + 0x10) * 0.5f);
    *(float *)(state + 0x3C) = func_00283180(*(float *)(state + 0x10) * 0.5f);
    }
    }
}
