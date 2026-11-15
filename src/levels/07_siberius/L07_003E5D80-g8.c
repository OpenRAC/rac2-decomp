#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

extern void func_002A6C58(void *, int, int);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F70(void *, void *, float);
extern void *func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);
extern void func_002AD330(void *, void *, void *, void *);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002A7750(u8 *, int, int);
extern void func_0029F338(void *);
extern u8 D_00188660[];
extern u8 D_00189EA0[];
extern float D_L07_001B0AAC __attribute__((sda));

/* Handles the entity's death: stops its sound, spawns an explosion and flying pickups, then
   respawns it with one life fewer or removes it. */
void func_L07_003E5D80(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    int slot;
    u8 *rec;
    u8 *pos;
    u8 *platform;
    union { Quad q; f32 f[4]; } burstPos;
    f32 impulse[4] __attribute__((aligned(16)));
    f32 carry[4] __attribute__((aligned(16)));
    int livesLeft;

    if (vars[0x2E] != 2) {
        SetDeathBits(obj, 0, 1);
    }
    slot = *(s32 *)(vars + 0x264);
    if (slot != -1) {
        rec = gSoundState + slot * 0x70;
        if (*(u8 **)(rec + 0x88) == obj && rec[0x74] != 0) {
            StopSoundVoice(slot);
        }
    }
    *(s32 *)(vars + 0x264) = -1;
    PlayMobySound(0, 0, obj);
    pos = obj + 0x10;
    burstPos.q = 0;
    burstPos.f[2] = 0.5f;
    FastVecAdd(&burstPos, &burstPos, pos);
    SpawnExplosion(&burstPos, 0, 0, 0, 0, 0x14, 0x2D, 1, D_L07_001B0AAC, 20.0f, 1, 0, 0, *(s32 *)(vars + 0x260));
    FastVecSub(impulse, pos, gHeroPosition);
    impulse[2] = 0.0f;
    FastVectorNormalizeHelper(impulse, impulse, 0.06666667f);
    platform = *(u8 **)(vars + 0x260);
    if (platform != 0) {
        TransformPointByMobyAttachment(obj, platform, pos, carry);
        FastVecAdd(impulse, impulse, carry);
    }
    SpawnDebrisForMaskedParts(obj, 3, impulse, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    livesLeft = *(u16 *)(vars + 0x21A) - 1;
    *(u16 *)(vars + 0x21A) = livesLeft;
    if ((s16)livesLeft != -1) {
        *(s16 *)(vars + 0x88) = 0;
        *(s32 *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
        SetMobyState(obj, 8, 4);
        vars[0x2E] = 1;
        *(f32 *)(vars + 0x20) = *(s16 *)(vars + 0x24);
    } else {
        MarkMobySpawned(obj);
    }
}
