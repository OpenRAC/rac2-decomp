#include "common.h"

/* Offsets from the sound-table anchor; the index stride is 0x70. */
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad2[0x13];
    char *owner;
} DobboSoundAnchor;

extern u16 D_L09_001B13C0 __attribute__((sda));
extern int D_L09_001B13D4 __attribute__((sda));
extern char D_L09_001B13D8[], D_00189EA0[], D_00188660[];
extern struct {
    char pad[0x80];
    char position[0x10];
    char pad2[0x240C];
    char *target;
} D_00189E20;
extern int *D_L09_001FE6C0[];

extern void func_L09_00403270(char *);
extern void func_L09_00403378(char *);
extern void func_L09_00403080(char *);
extern void func_002A7470(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern void func_002B60B0(char *, float, float, float, float);
extern void func_L01_00318638(char *, char *, char *);
extern float func_00283CE0(int);
/* The wrapper replaces the path index with its pointer and forwards the other
   arguments to func_002C9828, then returns a status. */
extern int func_L07_00338D20(int, int, char *, char *, int, float);
extern int func_002B3868(char *);
extern int func_002E5CF8(int, int, char *);
extern int func_002B4FF0(char *, char *, float);
extern float func_00282E80(char *, char *);
extern int func_002B1C20(char *, char *);
extern void func_0026FEB8(char *, ...);
extern void func_002E59F8(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFEB8(char *, void *, void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_002B0A68(char *, int, void *, u8, float, float, float, float);
extern void func_002A6C58(char *, int, int);
extern void func_0029F338(char *);
extern void func_L09_004031D8(char *);
extern void func_L09_00403398(char *);
extern void func_L09_00403700(char *);

/* Per-frame update of the Dobbo path enemy (moby class 3415): it waits, follows its path, walks up to the hero, and blows up when hit. */
void func_L09_00403798(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    int state, flags, index;
    int *path;
    float length;
    float away[4];

    UpdateLargeCreatureReleaseRecord(obj);
    RestoreMobySavedHeight(obj);
    state = (u8)obj[0x95];
    switch (state) {
    case 0:
        if (*(int *)(vars + 0x234) == 1 || *(s16 *)(vars + 0x26C)) {
            AlertGroupMobyClass3415(obj);
            if ((u8)obj[0x43] != 2)
                StartAnimationBlended(obj, 2, 0, 5);
            *(int *)(vars + 0x28C) = *(int *)(vars + 0x244);
            *(float *)(vars + 0x290) = 0;
            *(int *)(vars + 0x138) |= 4;
            SetMobyState(obj, 4, 1);
        }
        break;
    case 2:
        if (*(int *)(vars + 0x234) == 1 || *(s16 *)(vars + 0x26C)) {
            AlertGroupMobyClass3415(obj);
            *(u16 *)(vars + 0x26C) = D_L09_001B13C0;
            if ((u8)obj[0x43] != state)
                StartAnimationBlended(obj, 2, 0, 5);
            SetControllerSpeedLimits(obj, 0.0066666668f, 0.06666667f, 0.8377582f, 0.8377582f);
            *(int *)(vars + 0x13C) = *(int *)(vars + 0x254);
            *(int *)(vars + 0x28C) = *(int *)(vars + 0x244);
            SetMobyState(obj, 3, 3);
        }
        break;
    case 3:
        if (!*(int *)(vars + 0x234) && !*(s16 *)(vars + 0x26C)) {
            SetControllerSpeedLimits(obj, 0.0066666668f, 0.06666667f, 0.8377582f, 0.8377582f);
            if (*(u8 *)(obj + 0x43) != 0)
                StartAnimationBlended(obj, 0, 0, 20);
            SetMobyState(obj, 2, 2);
        }
        break;
    }

    switch ((u8)obj[0x20]) {
    case 2:
        UpdateWanderHeading(obj, vars + 0x1F0, vars + 0x100);
        break;
    case 3:
        if (obj[0x60] & 2)
            SetMobyState(obj, 5, -1);
        break;
    case 4:
        if (obj[0x60] & 2) {
            if (*(u8 *)(obj + 0x43) != 0)
                StartAnimationBlended(obj, 0, 0, 20);
        }
        path = D_L09_001FE6C0[*(int *)(vars + 0x250)];
        length = IntToFloat(*path);
        *(float *)(vars + 0x290) += length / (*(float *)(vars + 0x25C) * 60.0f);
        if (length <= *(float *)(vars + 0x290)) {
            *(float *)(vars + 0x290) = length;
            SetControllerSpeedLimits(obj, 0.0066666668f, 0.06666667f, 0.8377582f, 0.8377582f);
            *(int *)(vars + 0x138) &= ~4;
            SetMobyState(obj, 5, 3);
        }
        RunTableEntryByIndex(*(int *)(vars + 0x250), 0, obj + 0x10, obj + 0xF0, 0,
                         *(float *)(vars + 0x290));
        break;
    case 5:
        if (obj[0x60] & 2) {
            if (*(u8 *)(obj + 0x43) != 0)
                StartAnimationBlended(obj, 0, 0, 20);
        }
        UpdateWanderHeading(obj, vars + 0x1F0, vars + 0x100);
        if (*(s16 *)(vars + 0x26A)) {
            SetControllerSpeedLimits(obj, 0.0066666668f, 0.06666667f, 0.8377582f, 0.8377582f);
            if ((u8)obj[0x43] != 2)
                StartAnimationBlended(obj, 2, 0, 5);
            SetMobyState(obj, 6, -1);
        }
        break;
    case 6:
        if ((obj[0x60] & 2) && (u8)obj[0x42] == 2) {
            if ((u8)obj[0x43] != 3)
                StartAnimationBlended(obj, 3, 0, 5);
            SetMobyState(obj, 7, -1);
        }
        break;
    case 7:
        if (SetFirstPendingFlag(obj)) {
            DobboSoundAnchor *entry = (DobboSoundAnchor *)(gSoundState + *(s16 *)(vars + 0x274) * 0x70);
            if (entry->owner != obj || !entry->active)
                *(s16 *)(vars + 0x274) = PlayMobySound(D_L09_001B13D4, 4, obj);
        }
        TurnTowardTargetAndStepMovement(obj, vars + 0x220, 0.0f);
        if (gHeroState.target == obj || vec_distance_xy(obj + 0x10, gHeroState.position) < 1.2f) {
            if ((u8)obj[0x43] != 4)
                StartAnimationBlended(obj, 4, 0, 5);
            SetMobyState(obj, 8, -1);
        }
        break;
    case 8:
        if ((obj[0x60] & 2) && (u8)obj[0x42] == 4) {
            if (*(u8 *)(obj + 0x43) != 0)
                StartAnimationBlended(obj, 0, 0, 20);
            SetMobyState(obj, 5, -1);
        }
        break;
    case 9:
        flags = DispatchActionByKind(obj, vars + 0x50);
        if (flags & 1) {
            STUB_printf(D_L09_001B13D8, *(s16 *)(vars + 0x274), *(s16 *)(obj + 0xB2));
            index = *(s16 *)(vars + 0x274);
            if (index != -1) {
                DobboSoundAnchor *entry = (DobboSoundAnchor *)(gSoundState + index * 0x70);
                if (entry->owner == obj && entry->active)
                    StopSoundVoice(index);
            }
            *(s16 *)(vars + 0x274) = -1;
            FastVecSub(away, obj + 0x10, gHeroPosition);
            TransformAndSetHeight(obj, away, away, 0, 0.0f);
            vec_scale_to_length(away, away, 0.10000001f);
            SpawnDebrisForMaskedParts(obj, 0x3F, away, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            PlayMobySound(0, 0, obj);
            SetDeathBits(obj, 0, 3);
            MarkMobySpawned(obj);
            return;
        } else if (flags & 2) {
            *(u16 *)(vars + 0x26C) = D_L09_001B13C0;
            SetMobyState(obj, 5, 3);
            PlayMobySound(3, 0, obj);
        }
        break;
    }

    if ((u8)obj[0x20] != 7) {
        index = *(s16 *)(vars + 0x274);
        if (index != -1) {
            DobboSoundAnchor *entry = (DobboSoundAnchor *)(gSoundState + index * 0x70);
            if (entry->owner == obj && entry->active)
                StopSoundVoice(index);
        }
        *(s16 *)(vars + 0x274) = -1;
    }
    TickTimersAndAge(obj);
    UpdateMobyHeightAndSeparation(obj);
    SpawnBoneSparksInState7(obj);
}
