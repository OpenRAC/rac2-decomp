#include "common.h"
typedef int PickupQuad __attribute__((mode(TI)));
extern u8 D_L08_0021EAF0[];
extern u8 D_0019B4A8[];
extern int D_001A79F0[] __attribute__((sda));
/* Partial resident view through the last state field read here. */
typedef struct {
    u8 unknown00[0x80];
    PickupQuad position;
    u8 unknown90[0x17A0];
    u8 *vehicle;
    u8 unknown1834[0xA60];
    int mode;
    u8 unknown2298[4];
    int world;
} ResidentPrefix;
extern ResidentPrefix D_00189E20;
typedef struct { int duration; int timer; float progress; } PickupState;
extern int D_00138320[];
extern float D_L08_001B031C __attribute__((sda));
extern float D_L08_001B0324 __attribute__((sda));
extern float D_L08_001B032C __attribute__((sda));
extern float D_L08_001B0330 __attribute__((sda));
extern float D_L08_001B0334 __attribute__((sda));
extern int D_L08_001B0370 __attribute__((sda));
extern void func_002A7470(u8 *object, int bank, int anim, int frames);
extern float func_002A89A8(void *position, int flags, float distance);
extern float func_00282E80(void *a, void *b);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00282D30(void *out, void *a, float scale);
extern void func_00282FB8(void *out, void *a, float magnitude);
extern void func_00282CC0(void *out, void *a, void *b);
extern int func_00282948(int *timer);
extern void func_0029F338(void *object);
extern void func_L08_003D3EF8(u8 *object);

typedef struct { u8 p[0x464]; u8 x[1]; } Hist;
typedef struct { u8 p[0x8e]; short lock; } VData;
typedef struct { u8 p[0x31]; u8 held; u8 p2[2]; u16 flags; u8 p3[0x12]; float scale; } OView;
/* Updates a pickup (moby class 2458, Raritanium): it waits to be grabbed, is pulled towards the
   mining vehicle, then follows the hero while its amount drains, and disappears when used up. */
void func_L08_003D4190(u8 *object)
{
    PickupState *vars = *(PickupState **)(object + 0x68);
    u8 *vehicle;
    u8 *vehicleVars;
    unsigned short pickupId;
    float drainStep;
    float pull[4] __attribute__((aligned(16)));
    if (object[0xb0] != 255) {
        pickupId = *(unsigned short *)(object + 0xb2);
        {
        int savedBits;
        if (((Hist *)D_L08_0021EAF0)->x[(short)pickupId])
            goto kill;
        savedBits = D_0019B4A8[((short)pickupId >> 1) + (gCurrentMapIndex[0] << 10)];
        if (pickupId & 1) { if ((savedBits >> 4) & 7) goto kill; }
        else if (savedBits & 7) goto kill;
        }
    }
    switch (object[0x20]) {
    case 0: {
        float value;
        object[0x30] = 255;
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
        vars->timer = vars->duration * 60;
        if (object[0x43])
            StartAnimationBlended(object, 0, 0, 2);
        object[0x20] = 1;
        value = ProbeGroundHeightBelow(object + 0x10, 0, 200.0f);
        if (value != 0.0f)
            *(float *)(object + 0x18) = value;
        break;
    }
    case 1: {
        float value;
        vehicle = gHeroState.vehicle;
        if (vehicle == 0 || *(short *)(vehicle + 0xaa) != 0xeef /* Mining Vehicle */ ||
            vehicle[0x20] == 254 || vehicle[0x20] == 253 ||
            gHeroState.mode != 0x31)
            return;
        vehicleVars = *(u8 **)(vehicle + 0x68);
        *(u8 **)(vehicleVars + 0x1b0) = object;
        value = vec_distance_xy(object + 0x10, &gHeroState.position);
        if (value < *(float *)(vehicleVars + 0x68)) {
            *(float *)(vehicleVars + 0x68) = value;
            *(u8 **)(vehicleVars + 0x6c) = object;
        }
        if (!(value < D_L08_001B031C) || !(*D_00138320 & 0x80))
            return;
        { u8 *activeVehicle = gHeroState.vehicle;
        if (activeVehicle == 0 || (activeVehicle[0x42] != 2 && activeVehicle[0x43] != 2))
            return; }
        FastVecSub(pull, &gHeroState.position, object + 0x10);
        FastVecScale(pull, pull, 0.1f);
        pull[2] = 0;
        FastVectorDivideHelper(pull, pull, D_L08_001B0334 * 0.0166666675f);
        FastVecAdd(object + 0x10, object + 0x10, pull);
        if (!FastFloatHelperD(&vars->timer))
            return;
        ((VData *)vehicleVars)->lock = 180;
        vars->timer = D_L08_001B0370;
        qcopy(object + 0x10, &gHeroState.position);
        ((OView *)object)->held = 1;
        ((OView *)object)->flags = (((OView *)object)->flags & 0xfffe) | 0x800;
        vars->progress = D_L08_001B032C;
        if (object[0x43] != 1)
            StartAnimationBlended(object, 1, 0, 30);
        ((OView *)object)->scale = vars->progress * 2.0f;
        object[0x20] = 2;
        break;
    }
    case 2: {
        float value;
        value = vars->progress;
        value += (1.0f - value) * D_L08_001B0324;
        vars->progress = value;
        *(float *)(object + 0x48) = value * 2.0f;
        qcopy(object + 0x10, &gHeroState.position);
        if (FastFloatHelperD(&vars->timer) || *(float *)(object + 0x2c) <= 0.0f) {
            drainStep = D_L08_001B0330 * *(float *)(*(u8 **)(object + 0x24) + 0x24);
            if (drainStep < *(float *)(object + 0x2c) || gHeroState.world == 20 ||
                gHeroState.world == 25 ||
                gHeroState.mode == 0x39 ||
                gHeroState.mode == 0x6f) {
                *(float *)(object + 0x2c) -= drainStep;
            } else {
                gCurrentMapIndex[3]++;
                { unsigned short pickupId2 = *(unsigned short *)(object + 0xb2);
                if (pickupId2 & 1) {
                    u8 *savedByte = &D_0019B4A8[((short)pickupId2 >> 1) + (gCurrentMapIndex[0] << 10)];
                    if (((*savedByte >> 4) & 7) != 7)
                        *savedByte += 16;
                } else {
                    u8 *savedByte = &D_0019B4A8[((short)pickupId2 >> 1) + (gCurrentMapIndex[0] << 10)];
                    if ((*savedByte & 7) != 7)
                        (*savedByte)++;
                } }
kill:
                MarkMobySpawned(object);
                return;
            }
        }
        SpawnParticlesAndDrawGlowRings(object);
        break;
    }
    }
}
