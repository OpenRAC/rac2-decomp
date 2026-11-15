#include "common.h"

typedef int EffectQuad __attribute__((mode(TI)));
extern void func_L03_00419A60(u32, u8 *, s32);
extern void func_L03_0038B4E8(void *);
extern void func_L03_0038B408(void *);
extern void func_002A7750(u8 *, s32, s32);
extern int func_002B3868(u8 *);
extern int func_00282948(void *);
extern void func_L03_0038B238(void);
extern void func_L03_0038B5D8(u8 *);
typedef void (*EffectDrawCallback)(void *);
extern void func_L00_002E6EF8(EffectDrawCallback, void *);

extern void ref_L03_0038A6D8_00(void *);
extern int func_002B38B8(u8 *);
extern void func_00282CC0(void *, void *, void *);
extern u8 *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,void *);
extern unsigned short D_0018CDE4;
extern unsigned char D_00188660[];
/* Only the accessed prefix is described. Indexing still uses the measured
 * 0x70-byte stride, not sizeof this partial view. */
typedef struct {
    u8 reserved00[0x74];
    u8 active;
    u8 reserved75[0x13];
    u8 *owner;
} SoundSlotPrefix;
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, char *);
extern void func_0029F338(void *);

/* Updates a moby (class 2832) that cycles through three timed states, draws its effect, and blows up with a sound when destroyed. */
void func_L03_0038A6D8(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    union { EffectQuad quad; float values[4]; } position;
    int handle;
    switch (object[0x20]) {
    case 0:
        qcopy(state, object + 0x10);
        if (*(int *)(state + 0x10) != -1 && *(int *)(state + 0x14))
            SetRouteNodeEnabledFlag(*(int *)(state + 0x10), object + 0x10, 0);
        InitEffectMobyState(object);
        if ((*(unsigned long long *)(state + 0x38) & 0x1100000000ULL) == 0x1100000000ULL)
            func_L03_0038B408(object);
        SetMobyState(object, 1, -1);
        break;
    case 1:
        if (SetFirstPendingFlag(object))
            qcopy(object + 0x10, state);
        if (FastFloatHelperD(state + 0x24)) {
            *(int *)(state + 0x24) = *(int *)(state + 0x18);
            SetMobyState(object, 2, -1);
        }
        break;
    case 2:
        if (FastFloatHelperD(state + 0x24)) {
            *(int *)(state + 0x24) = *(int *)(state + 0x1C);
            SetMobyState(object, 3, -1);
        }
        break;
    case 3:
        if (FastFloatHelperD(state + 0x24)) {
            *(int *)(state + 0x24) = *(int *)(state + 0x20);
            SetMobyState(object, 1, -1);
        }
        break;
    }
    if (!(*(int *)(state + 0x3C) & 0x20)) {
        if (!(*(int *)(state + 0x3C) & 0x40))
            RefreshRandomVectorTable();
        UpdateRopeStrandPoints(object);
        AddDrawCallbackToList3(ref_L03_0038A6D8_00, object);
    }
    if (IsThirdPendingFlagSet(object)) {
        position.quad = 0;
        position.values[2] = 1.0f;
        FastVecAdd(&position, &position, object + 0x10);
        SpawnExplosion(&position,0,0,0,0,0x14,0x2D,1,1.0f,20.0f,1,0,0,0);
        if (*(int *)(state + 0x10) != -1 && *(int *)(state + 0x14))
            SetRouteNodeEnabledFlag(*(int *)(state + 0x10), object + 0x10, 1);
        D_0018CDE4 = 0xFFFF;
        handle = *(int *)(state + 0xD8);
        if (handle != -1) {
            if (((SoundSlotPrefix *)(gSoundState + handle * 0x70))->owner == object && ((SoundSlotPrefix *)(gSoundState + handle * 0x70))->active)
                StopSoundVoice(handle);
        }
        *(int *)(state + 0xD8) = -1;
        PlayMobySound(1, 0, (char *)object);
        MarkMobySpawned(object);
    } else {
        if (((SoundSlotPrefix *)(gSoundState + *(int *)(state + 0xD8) * 0x70))->owner != object || !((SoundSlotPrefix *)(gSoundState + *(int *)(state + 0xD8) * 0x70))->active)
            *(int *)(state + 0xD8) = PlayMobySound(0, 4, (char *)object);
    }
}
