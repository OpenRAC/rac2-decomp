#include "common.h"

typedef struct DamoselHeroView {
    u8 pad0[0xBF8];
    void *saved;
    u8 padBFC[0x1230 - 0xBFC];
    int mask;
    u8 pad1234[0x1244 - 0x1234];
    int mode;
    u8 pad1248[0x1450 - 0x1248];
    void *vehicle;
    u8 pad1454[0x2290 - 0x1454];
    u8 *moby;
    int action;
    u8 pad2298[0x22BC - 0x2298];
    u8 blocked;
    u8 pad22BD[0x2534 - 0x22BD];
    int timer;
} DamoselHeroView;
extern DamoselHeroView D_00189E20;
extern u8 D_00188660[], D_00139568[];
typedef struct DamoselInputView {
    u8 pad[0x1A0];
    int held, pressed;
} DamoselInputView;
extern DamoselInputView D_00138180;
typedef struct DamoselWeaponView {
    u8 pad[0x70];
    float damage;
    u8 tail[0x6C];
} DamoselWeaponView;
extern u8 D_L18_0026BCF0[];
typedef struct DamoselHitRecord {
    float direction[4];
    u8 pad10[8];
    u8 type, active;
    u16 classId;
    int pad1C, flag;
    u8 pad24[12];
} __attribute__((aligned(16))) DamoselHitRecord;

typedef int DamoselQuad __attribute__((mode(TI)));
extern u8 *D_L18_001B1DCC __attribute__((sda));
extern u8 *D_L18_001B1DD0 __attribute__((sda));
extern u8 *D_L18_001B1DC8 __attribute__((sda));
extern u8 *D_L18_001C3C80[];
extern int D_L18_001A8FF0, D_L18_001A8F00;
extern void func_002FEE50(int);
extern int func_L00_00329E90(void *, int, void *);
extern u8 *func_L00_0032A088(int, int);
extern u8 *func_L00_0041A490(void *);
extern void func_002E59F8(int);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_00282948(void *);
extern int func_L00_002D4040(int);
extern void func_002AA3A8(void *, void *, float, float, float, float);
extern void func_L00_002D3F30(int, int);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002A7470(void *, int, int, int);
extern int func_00277F48(float, void *, int, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern void func_002A8E20(void *, void *);
extern void func_0032D758(void *, int, void *);
extern void func_L18_002E0070(int, int);
extern void func_00282C88(void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_0032A1A8(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L00_0041ABB8(void *, void *, void *, int);
extern void func_L00_0041A5C0(void *);
extern void func_L00_0041A500(void *);
extern void func_L00_0041BAE8(void *);
extern void func_L00_002E6EF8(void (*)(char *), void *);
extern void func_L00_0041AE28(char *);

/* Updates the Lava Gun (moby class 1481): while the fire button is held it sprays lava, hurting targets in front and playing a sound, and updates the stream effects. */
void func_L18_00447128(u8 *obj)
{
    float velocity[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    DamoselHitRecord hit;
    int scratch;
    u8 *state = *(u8 **)(obj + 0x68);
    int i = 0, active, count;
    u8 *entry;
    u8 **targets;
    if (gHeroState.mode == 3 && D_L18_001B1DCC) {
        for (i = 0; i < 35; i++) {
            u8 *entry = D_L18_001B1DCC + i * 64;
            if (*(int *)(entry + 0x38) >= 0) {
                ClearEntryFlag(*(int *)(entry + 0x38));
                *(int *)(entry + 0x38) = -1;
            }
        }
    }
    if (!obj[0x20]) {
        *(int *)(state + 0x34) = AcquireEntitySlot(obj, 0, &scratch);
        D_L18_001B1DD0 = GetSlotBody(*(short *)(obj + 0xAA), *(int *)(state + 0x34));
        D_L18_001B1DC8 = AlignUpTo16_L00_2(D_L18_001B1DD0 + 0x33E0);
        D_L18_001B1DCC = AlignUpTo16_L00_2(D_L18_001B1DC8 + 0x1F40);
        {
            int *word = (int *)(D_L18_001B1DC8 + 0x1F30);
            for (i = 124; i >= 0; i--, word -= 16) *word = 1;
        }
        entry = D_L18_001B1DD0 + 0x33C4;
        for (i = 9; i >= 0; i--, entry -= 0x530) *(int *)entry = 0;
        {
            int invalid = -1;
            entry = D_L18_001B1DCC + 0x8B8;
            for (i = 34; i >= 0; i--, entry -= 64) *(int *)entry = invalid;
        }
        *(int *)(state + 0x3C) = 0; *(int *)(state + 0x48) = 0;
        *(int *)(state + 0x40) = 0; *(int *)(state + 0x44) = 0;
        *(int *)(state + 0x54) = 0; *(int *)(state + 0x50) = 0;
        *(int *)(state + 0x58) = 0; *(int *)(state + 0x5C) = 0;
        *(int *)(state + 0x60) = 0; *(int *)(state + 0x64) = 0;
        obj[0x20] = 1; *(int *)(state + 0x38) = -1;
    }
    if (gHeroState.mode == 3) {
        int handle = *(int *)(state + 0x38);
        if (handle != -1) {
            u8 *p = gSoundState + handle * 0x70;
            if (*(u8 **)(p + 0x88) == obj && p[0x74]) StopSoundVoice(handle);
        }
        *(int *)(state + 0x38) = -1;
        return;
    }
    TransformMobyJointToWorld(obj, 0, state);
    if (obj[0x42] == obj[0x43] && (obj[0x60] & 2)) StartAnimationBlendedWithFlags(obj, 1, 0, 2, 0);
    active = 1;
    if (gHeroState.action == 29) {
        if (!FastFloatHelperD(&gHeroState.timer)) active = 0;
    } else gHeroState.timer = 40;
    if ((gPadState.held & gHeroState.mask) && active && get_ammo(-1) && !gHeroState.blocked) {
        SpringFloatToGoal(state + 0x50, state + 0x54, 10.0f, 0.0075f, 0.002f, 10.0f);
        if (*(int *)(state + 0x60) % 10 == 0) SpendWeaponAmmo(-1, 1);
        ++*(int *)(state + 0x60);
        if (!IsVoicePlayingForOwner(obj, *(int *)(state + 0x38))) *(int *)(state + 0x38) = PlayMobySound(0, 4, obj);
        if (obj[0x43] != 2) StartAnimationBlended(obj, 2, 0, 0);
        count = ProcessCollisionHit(0.5f, state, 16, obj, 0);
        if (count > 0) {
            targets = gNearbyHitTargets;
            {
                int remaining = count;
                do {
                    if (*targets != gHeroState.moby) {
                        FastVecSub(direction, *targets + 0x10, obj + 0x10);
                        vec_scale_to_length(direction, direction, 1.0f);
                        vec_scale_to_length(&hit, &hit, 1.0f);
                        make_hit_descriptor(&hit, obj, 0x910000,
                            ((DamoselWeaponView *)(D_L18_0026BCF0 + gItemSlotToRecord[0x1D] * 0xE0))->damage,
                            direction);
                        hit.flag = 1;
                        *(DamoselQuad *)&hit = *(DamoselQuad *)direction;
                        hit.direction[3] = 5627.925f;
                        hit.type = 9; hit.active = 1;
                        hit.classId = *(short *)(*targets + 0xAA);
                        QueueMobyImpact(*targets, &hit);
                        StartAttachedEffect(*targets, 29, obj);
                        PlayMobySound(1, 0, obj);
                    }
                    ++targets;
                } while (--remaining);
            }
        }
    } else {
        int handle = *(int *)(state + 0x38);
        if (handle != -1) {
            u8 *p = gSoundState + handle * 0x70;
            if (*(u8 **)(p + 0x88) == obj && p[0x74]) StopSoundVoice(handle);
        }
        *(int *)(state + 0x38) = -1;
        if ((gPadState.pressed & gHeroState.mask) && !get_ammo(-1) && !gHeroState.blocked) PlayMobySound(2, 0, obj);
        SpringFloatToGoal(state + 0x50, state + 0x54, 0.0f, 0.06f, 0.01f, 0.125f);
        *(int *)(state + 0x60) = 0;
    }
    if (gHeroState.action == 1) SetHeroAction_L18(29, 1);
    TransformMobyJointToWorld(obj, 0, state);
    ClearVector128(velocity);
    velocity[1] = -1.0f;
    matrix_mul_vec3(velocity, velocity, obj + 0xC0);
    velocity[2] += 0.02f;
    vec_scale_to_length(velocity, velocity, *(float *)(state + 0x50) * 0.05f);
    if (gHeroState.vehicle) {
        gHeroState.saved = gHeroState.vehicle;
        ComputeObjectToTargetVector(gHeroState.vehicle, state, velocity, *(float *)(state + 0x50) * 0.05f);
        if (D_L18_001A8FF0) {
            FastVecScale(direction, obj + 0xE0, 0.02f);
            FastVecAdd(velocity, velocity, direction);
        } else {
            velocity[2] += 0.02f;
        }
    }
    qcopy(state + 0x10, state);
    if (gHeroState.action) ApplyAxisRotationToQuaternion(velocity, velocity, gHeroState.moby + 0xD0, -0.09817477f);
    if (*(float *)(state + 0x50) != 0.0f) AppendVectorRingEntry(obj, state, velocity, 40);
    *(float *)(state + 0x58) -= 0.1f;
    if (*(float *)(state + 0x58) <= -8.0f) *(float *)(state + 0x58) += 8.0f;
    *(float *)(state + 0x5C) -= 0.025f;
    if (*(float *)(state + 0x5C) <= -8.0f) *(float *)(state + 0x5C) += 8.0f;
    if (*(float *)(state + 0x50) != 0.0f) {
        UpdateLavaGunBlobs(obj); UpdateLavaGunRingEntries(obj);
    } else {
        *(int *)(state + 0x44) = 0; *(int *)(state + 0x3C) = 0;
        *(int *)(state + 0x48) = 0; *(int *)(state + 0x40) = 0;
    }
    UpdateEffectSlots_L00_2(obj);
    if (D_L18_001A8F00 != 2 && obj[0x31]) AddDrawCallbackToList3(DrawLavaGunShot, obj);
}
