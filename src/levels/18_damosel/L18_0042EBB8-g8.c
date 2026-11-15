#include "common.h"

extern void func_0029F338(void *);
extern int func_002E59B0(u8 *, int);
extern int func_002E5CF8(int, int, u8 *);
extern void func_002E59F8(int);
extern u8 D_00188660[];
extern int func_002A9640(u8 *, int, int);
extern float func_002A96A0(u8 *, int);
extern void func_002B3380(void *, void *, void *);
extern char *func_0032C700(void *, int, int, int, float, float, int, int, int, int, int, int, int, void *);
extern u8 *D_L18_001B281C;
extern void func_L18_004329B0(u8 *);
extern void func_L18_00432B30(u8 *, int);
extern void func_L18_00432D08(u8 *);
extern void func_L18_0042F768(u8 *);
extern void func_L18_0042F308(u8 *, int, int);
extern int func_L18_0042F688(u8 *, void *, int, void *, int, float);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002B0A68(u8 *, int, void *, int, float, float, float, float);
extern void func_002A7470(u8 *, int, int, int);
extern void func_002A7750(u8 *, int, int);
extern int func_002ACBC8(u8 *, int);
extern u8 D_00189EA0[];
extern float func_0029F530(u8 *);
extern int func_002B3868(u8 *);
extern int *D_L18_001FE480[];
extern int func_L09_0033E690(void *, int, float);

typedef struct {
    u8 pad00[0x20];
    float health;
    u8 pad24[10];
    u8 state;
    u8 pad2F[0x21];
    float hit[4];
    u8 pad60[0x10];
    float movement[4];
    float velocity[4];
    int ids[6];
    int paths[2];
    short groups[6];
    short waypoint;
    short group;
    int escapePath;
    int trigger;
    u8 padC8[0x14];
    int voice;
} LeaderState;

static inline void ReleaseVoice(u8 *moby, LeaderState *vars) {
    int slot = vars->voice;
    if (slot != -1) {
        u8 *record = gSoundState + slot * 0x70;
        if (*(u8 **)(record + 0x88) == moby && record[0x74])
            StopSoundVoice(slot);
    }
    vars->voice = -1;
}

/* Updates the leader boss: it takes damage, follows its paths, drops pieces in
   stages, and explodes when its health runs out. */
void func_L18_0042EBB8(u8 *moby) {
    LeaderState *vars = *(LeaderState **)(moby + 0x68);
    float hit;
    float vec[4];

    if (moby[0x20] >= 2) {
        if (!IsVoicePlayingForOwner(moby, vars->voice))
            vars->voice = PlayMobySound(0, 4, moby);
    } else if (IsVoicePlayingForOwner(moby, vars->voice)) {
        ReleaseVoice(moby, vars);
    }
    hit = UpdateAimTargetStrength(moby, FindOwnedEffectSlot(moby, 0x10000, 0));
    if (moby[0x20] >= 2) {
        vars->health -= hit;
        SpawnDamageDebrisOnHealthLoss(moby, vars->hit, &vars->health);
        if (vars->health <= 0.0f || vars->state == 2) {
            int i;
            SpawnExplosion(moby + 0x10, 1, 0x19, 20, 1.0f, 20.0f, 20, 20, 45, 1, 1, 1, 0, 0);
            for (i = 0; i < 6; i++) {
                if (vars->ids[i] != -1)
                    DestroyPieceAndParts(gMobyTable_L18 + (vars->ids[i] << 8));
            }
            if (IsVoicePlayingForOwner(moby, vars->voice))
                ReleaseVoice(moby, vars);
            RandomDirectionVector(vec, 0.10000000894069672f, 0.25f);
            FastVecAdd(vec, vec, vars->velocity);
            SpawnDebrisForMaskedParts(moby, 63, vec, 255, 3.0f, 6.0f, 3.0f, 6.0f);
            MarkMobySpawned(moby);
            return;
        }
    }
    switch (moby[0x20]) {
    case 0: {
        int i;
        int all;
        u8 *base;
        StartAnimationBlended(moby, 1, 0, 0);
        *(int *)(moby + 0x48) = 0;
        *(int *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        SetMobyState(moby, 1, -1);
        vars->state = 1;
        ReleaseVoice(moby, vars);
        base = gMobyTable_L18;
        *(u16 *)(moby + 0x34) |= 0x1000;
        all = 1;
        for (i = 0; i < 6; i++) {
            u8 *e;
            if (vars->ids[i] == -1)
                continue;
            e = base + (vars->ids[i] << 8);
            if (e == 0)
                continue;
            if (e[0x20] == 0xFE)
                continue;
            if (e[0x20] == 0xFD)
                continue;
            all = 0;
            break;
        }
        if (all) {
            MarkMobySpawned(moby);
            return;
        }
        break;
    }
    case 1:
        if (vars->trigger != -1 && IsPointInCuboid(gHeroPosition, vars->trigger))
            StartLeaderMoving(moby);
        break;
    case 2: {
        float damage = GetMobyAnimationValue(moby);
        if (SetFirstPendingFlag(moby)) {
            int i;
            moby[0xBC] = 0;
            *(float *)(moby + 0x48) = 1.0f;
            for (i = 0; i < 6; i++) {
                if (vars->ids[i] != -1)
                    ShrinkPieceAndLinkedParts(gMobyTable_L18 + (vars->ids[i] << 8), (int)moby);
            }
        } else if (moby[0xBC] == 0) {
            SteerLeaderMoby(moby, 1, 1);
            if (damage > 8.0f) {
                int i;
                moby[0xBC] = 1;
                for (i = 0; i < 6; i++) {
                    if (vars->ids[i] != -1 && vars->groups[i] == vars->group) {
                        AdvancePieceToState3(gMobyTable_L18 + (vars->ids[i] << 8));
                        vars->ids[i] = -1;
                    }
                }
                vars->group++;
                *(int *)(moby + 0x48) = 0;
            }
        } else if (moby[0xBC] == 1) {
            SteerLeaderMoby(moby, 1, 1);
            if (*(u16 *)(moby + 0x96) >= 31) {
                moby[0xBC] = 2;
                *(float *)(moby + 0x48) = 1.0f;
            }
        } else if (moby[0xBC] == 2) {
            SteerLeaderMoby(moby, 1, 1);
            if (damage > 59.0f) {
                *(int *)(moby + 0x48) = 0;
                SetMobyState(moby, moby[0x94], -1);
            }
        }
        break;
    }
    case 3:
        if (SetFirstPendingFlag(moby)) {
            vars->waypoint = MeasureMobyAgainstPathEntry(moby + 0x10, vars->paths[vars->group], 0.0f);
            break;
        } else {
            int id = vars->paths[vars->group];
            float speed = 5.0f;
            if (vars->waypoint == D_L18_001FE480[id][0] - 1)
                speed = 0.3f;
            if (!StepAlongPathPoint(moby, vars->movement, id, &vars->waypoint, 0, speed)) {
                if (vars->group <= 0 && vars->paths[1] != -1)
                    SetMobyState(moby, 3, -1);
                else
                    SetMobyState(moby, 4, -1);
                SetMobyState(moby, 2, -1);
            }
        }
        SteerLeaderMoby(moby, 1, 1);
        break;
    case 4:
        if (SetFirstPendingFlag(moby)) {
            vars->waypoint = MeasureMobyAgainstPathEntry(moby + 0x10, vars->escapePath, 0.0f);
            break;
        } else if (!StepAlongPathPoint(moby, vars->movement, vars->escapePath, &vars->waypoint, 0, 2.0f)) {
            if (IsVoicePlayingForOwner(moby, vars->voice))
                ReleaseVoice(moby, vars);
            MarkMobySpawned(moby);
            return;
        }
        SteerLeaderMoby(moby, 1, 1);
        break;
    }
    if (*(u16 *)(moby + 0x96) <= 0xFFFE)
        (*(u16 *)(moby + 0x96))++;
}
