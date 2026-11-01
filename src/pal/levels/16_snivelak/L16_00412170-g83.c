#include "include_asm.h"

#include "common.h"
extern u8 D_001395B8[];
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern u8 *D_L16_001B16C0 __attribute__((sda));
extern int D_L16_001B16C4 __attribute__((sda));
extern u8 D_00188660[];
extern void func_L16_00411F80(u8 *, int);
extern void func_0029F338(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern u8 *func_0029EFD0(int);
extern void func_002B37E8(u8 *, u8 *);
extern void func_00282A60(void *, int, int);
extern void func_L16_00410C80(u8 *);
extern void func_002A7750(u8 *, u8, int);
extern void func_L16_004116C8(u8 *, int, int, float);
extern void func_L16_004117A8(u8 *);
extern void *func_002A9640(void *, unsigned int, int);
extern float func_L07_003F90E8(int, int, float, float);
extern void func_PAL_002AC290(int, char *);
extern float func_PAL_002AA108(u8 *, void *);
extern float func_002AA2E8(float *, float, float);
extern void func_002E59F8(int);
extern void func_PAL_L16_00417C58(u8 *);
extern void func_002B3BA8(u8 *, int, void *, void *, float, float);

/* Initializes the boss hierarchy and applies damage, phase changes and speech. */
void func_PAL_L16_00415760(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *child, *attacker, *damage;
    u8 **arms;
    u8 *speech;
    int i, threshold, sound;
    float quantum, amount, divisor;
    if (!moby[0x20]) {
        if (D_001395B8[0x83] == 2) {
            func_L16_00411F80(moby, 0);
            func_0029F338(D_L16_001B2B1C[0] + *(int *)(state + 0x174) * 256);
            func_0029F338(moby);
            return;
        }
        if (!*(short *)(state + 0x24)) {
            *(short *)(state + 0x24) = 600;
            *(float *)(state + 0x20) = 600.0f;
        }
        speech = state + 0x310;
        state[0x2e] = 1;
        divisor = func_00283CE0(D_L16_001B16C4);
        quantum = (float)*(short *)(state + 0x24);
        quantum /= divisor;
        threshold = func_00283CF0((*(float *)(state + 0x20) - 1.0f) / quantum);
        *(float *)(state + 0x248) = (float)threshold * quantum;
        arms = (u8 **)(state + 0x238);
        for (i = 1; i >= 0; i--, arms++) {
            child = func_0029EFD0(0x7e8);
            if (child) {
                func_002B37E8(child, moby);
                *(unsigned short *)(child + 0x34) |= 0x4100;
                *arms = child;
            }
        }
        {
            int bodyIndex = *(int *)(state + 0x174);
            u8 *pool = D_L16_001B2B1C[0];
            float initialHeight = *(float *)(moby + 0x18);
            D_L16_001B16C0 = 0;
            *(float *)(state + 0x264) = initialHeight;
            *(u8 **)(state + 0x1f0) = pool + bodyIndex * 256;
        }
        *(unsigned short *)(moby + 0x34) |= 0x4000;
        *(unsigned short *)(*(u8 **)(state + 0x1f0) + 0x34) |= 0x4000;
        *(unsigned short *)(moby + 0x32) = 500;
        *(unsigned short *)(*(u8 **)(state + 0x1f0) + 0x32) = 500;
        *(unsigned short *)(moby + 0x34) |= 0x400;
        func_00282A60(speech, 0, 48);
        *(int *)(state + 0x350) = 0;
        *(int *)(state + 0x354) = -1;
        func_L16_00410C80(moby);
        func_002A7750(moby, 1, 0);
        func_L16_004116C8(moby, 0, 0, 0.0f);
        if (D_001395B8[0x83] == 1) {
            func_L16_004117A8(moby);
            func_L16_00411F80(moby, 1);
        } else func_L16_00411F80(moby, 0);
    }
    if (!moby[0x95] || moby[0x95] == 5) return;
    damage = func_002A9640(moby, 0x10000, 0);
    if (!damage) damage = func_002A9640(*(u8 **)(state + 0x1f0), 0x10000, 0);
    if (!damage) damage = func_002A9640(*(u8 **)(state + 0x238), 0x10000, 0);
    if (!damage) damage = func_002A9640(*(u8 **)(state + 0x23c), 0x10000, 0);
    if (damage) {
        *(float *)(damage + 0x2c) *= func_L07_003F90E8(0, 20, 0.5f, 1.5f);
        if (moby[0x95] == 3) *(float *)(damage + 0x2c) *= 0.333f;
        attacker = *(u8 **)(damage + 0x20);
        if (attacker && *(short *)(attacker + 0xaa) != 0xea7) {
            *(float *)(damage + 0x2c) *= 0.2f;
            if (*(short *)(attacker + 0xaa) == 0x5c9) *(float *)(damage + 0x2c) *= 0.05f;
        }
        else func_PAL_002AC290((int)moby, (char *)(state + 0x50));
        amount = func_PAL_002AA108(moby, damage);
        func_002AA2E8((float *)(state + 0x20), 0.0f, amount);
        if (D_L16_001B16C0 && moby[0x95] != 3 && *(float *)(state + 0x20) < *(float *)(state + 0x248)) {
            divisor = func_00283CE0(D_L16_001B16C4);
            quantum = (float)*(short *)(state + 0x24);
            quantum /= divisor;
            threshold = func_00283CF0((*(float *)(state + 0x20) - 1.0f) / quantum);
            (*(int *)(state + 0x260))++;
            *(float *)(state + 0x248) = (float)threshold * quantum;
            func_002A7750(moby, 9, 3);
            sound = *(int *)(state + 0x368);
            if (sound != -1) {
                u8 *soundRecord = D_00188660 + sound * 112;
                if (*(u8 **)(soundRecord + 0x88) == *(u8 **)(state + 0x1f0) && soundRecord[0x74]) func_002E59F8(sound);
            }
            {
                u8 *target = D_L16_001B16C0;
                *(int *)(state + 0x368) = -1;
                *(u8 **)(state + 0x24c) = target;
            }
        } else if (*(float *)(state + 0x20) == 0.0f || state[0x2e] == 2) {
            sound = *(int *)(state + 0x368);
            if (sound != -1) {
                u8 *soundRecord = D_00188660 + sound * 112;
                if (*(u8 **)(soundRecord + 0x88) == *(u8 **)(state + 0x1f0) && soundRecord[0x74]) func_002E59F8(sound);
            }
            *(int *)(state + 0x368) = -1;
            func_002A7750(moby, 17, 5);
        }
    }
    func_PAL_L16_00417C58(moby);
    moby[0xa8] = 255;
    (*(u8 **)(state + 0x1f0))[0xa8] = 255;
    (*(u8 **)(state + 0x238))[0xa8] = 255;
    (*(u8 **)(state + 0x23c))[0xa8] = 255;
    func_002B3BA8(moby, -1, 0, 0, 128.0f, 0.0f);
}
