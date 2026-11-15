#include "names.h"
/* Aim-helper step: the shared func_002AB8C0 tail takes self + 0x50 on both paths. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));

extern char *func_002A9640(char *, int, int);
extern float func_002A96A0(char *, void *);
extern void func_L08_0032A4D0(char *, char *, char *, char *);
extern void func_L08_0032C0D8(char *, char *, int, int, int, float);
extern void func_002A7470(char *, int, int, int);
extern void func_002A6C58(char *, int, int);
extern void func_002AB800(char *, char *);
extern void func_002AB8C0(char *, char *);

/* One step of an object that can be hit: it takes damage from what touches it, and when its health
   runs out it switches to its defeated state and plays that animation. */
void func_L08_003F6348(char *self, char *state)
{
    char *vars = state;
    char *attacker;
    struct { TI128 in; float out[4]; } aim;
    float health;
    float hitAmount;

    if (*(u8 *)(self + 0x20) == 4)
        return;
    attacker = FindOwnedEffectSlot(self, 0xC30000, 0);
    hitAmount = UpdateAimTargetStrength(self, attacker);
    if (0.0f < hitAmount) {
        health = *(float *)(vars + 0x20) - *(float *)(attacker + 0x2C);
        *(float *)(vars + 0x20) = health;
        if (0.0f < health) {
            *(float *)(vars + 0x78) = 0.13333334028720856f;
            *(float *)(vars + 0x7C) = 0.11666667461395264f;
            aim.in = *(TI128 *)(attacker + 0x10);
            ResolveDirectionVector((char *)&aim.in, (char *)aim.out, vars + 0x78, vars + 0x7C);
            InitLaunchedObject(self, vars + 0x60, 3, 1, 0, aim.out[0]);
            if (1.0f <= hitAmount) {
                *(u8 *)(vars + 0x57) = 0x78;
                *(u8 *)(self + 0x20) = 3;
                StartAnimationBlended(self, 2, 0, 0);
            } else {
                *(u8 *)(vars + 0x57) = 0x78;
            }
        } else {
            *(u16 *)(self + 0x34) &= 0xEFFF;
            *(u8 *)(vars + 0x57) = 0xFA;
            *(u8 *)(self + 0x20) = 4;
            *(float *)(vars + 0x78) = 0.18333333730697632f;
            *(float *)(vars + 0x7C) = 0.11666667461395264f;
            aim.in = *(TI128 *)(attacker + 0x10);
            ResolveDirectionVector((char *)&aim.in, (char *)(aim.out + 1), vars + 0x78, vars + 0x7C);
            InitLaunchedObject(self, vars + 0x60, 3, 1, 0, aim.out[1]);
            *(float *)(vars + 0xB0) = 5.0f;
            *(float *)(vars + 0xB4) = 10.0f;
            if (*(u8 *)(self + 0x43) != 3)
                StartAnimationBlended(self, 3, 0, 0);
            SetDeathBits(self, 0, 3);
        }
        StartColorFade(self, vars + 0x50);
    }
    *(u8 *)(self + 0xA8) = 0xFF;
    UpdateColorFade(self, vars + 0x50);
}

