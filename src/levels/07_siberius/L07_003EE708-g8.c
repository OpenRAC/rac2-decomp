#include "include_asm.h"
#include "names.h"

/* func_L07_003EE708 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void func_0029F338(int);
extern float func_002A7940();
extern void func_002A7750(char *, int, int);
extern int func_002ACBC8(char *, int);
extern void func_L07_003EECE0(char *);
extern int func_002B3868(char *);
extern float func_L07_003EEE28(char *);
extern int func_002A8508(int, int);
extern int func_00282948(void *);
extern int func_002B38B8(char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002E5CF8(int, int, char *);
extern void func_L07_003E7380(char *, void *, void *, char *, int);
extern void func_L07_003EBBE8(char *, void *, void *, char *, int);
extern float func_002AA2E8(void *, float, float);
extern int func_002A9640(char *, int, int);
extern float func_002A96A0(char *, int);
extern void func_002B0A68(char *, int, void *, int, float, float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_0032DA58(char *, void *, void *, float);

extern char D_00189EA0[];
extern char D_L07_001B9200[];
extern int D_L07_001B0C50 __attribute__((sda));
extern unsigned short *D_L07_001FAD60[];
extern char *D_L07_001B22DC[] __attribute__((sda));
extern int D_L07_001B22F8[] __attribute__((sda));
extern void *D_L07_002A3380[];

typedef struct {
    char pad00[0x20];
    float f20;
    short h24;
    char pad26[0x60 - 0x26];
    char b60[0x30];
    int f90;
    char pad94[0x9C - 0x94];
    int ids[7];
    char padB8[0xF0 - 0xB8];
    char b0F0[0x10];
    char pad100[0x104 - 0x100];
    float f104;
    float f108;
    char pad10C[0x110 - 0x10C];
    int f110;
    float f114;
    float f118;
    char pad11C[0x120 - 0x11C];
    int idx;
    int f124;
} L07State;

/* The object's six states, state 0 to 5 (anything above only runs the tail). The dispatch reads the
   level's own jump table (six code addresses in the level's data at 0x2A3380: the bodies come in
   the order 0, 1, 4, 2, 3, 5); `cases` only keeps the labels alive. */
/* Per-frame update for moby class 3396: steps through its list of linked objects, throws
   launchers at them and fades out when hurt. */
void func_L07_003EE708(char *mobyArg)
{
    static void *cases[6] = {&&c0, &&c1, &&c4, &&c2, &&c3, &&c5};
    char *moby = mobyArg;
    L07State *vars;
    unsigned int state;

    state = *(unsigned char *)(moby + 0x20);
    vars = *(L07State **)(moby + 0x68);
    if (state < 6)
        goto *D_L07_002A3380[state];
    goto tail;
c0:
    if (vars->h24 == 0) {
        vars->h24 = 0x28;
        vars->f20 = 40.0f;
    }
    vars->f104 = RandomAngle();
    vars->f108 = RandomAngle();
    *(TI128 *)vars->b0F0 = *(TI128 *)(moby + 0x10);
    SetMobyState(moby, 1, -1);
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    goto tail;
c1:
    if (vars->f90 != -1) {
        if (IsPointInCuboid(gHeroPosition, vars->f90))
            ResetPathFollowerToPathPoint(moby);
    }
    goto tail;
c4: {
    int i;

    if (SetFirstPendingFlag(moby))
        vars->f124 = 0x3C;
    SteerTowardTarget(moby);
    i = vars->idx;
    if (i >= 6 || vars->ids[i + 1] == -1) {
        SetMobyState(moby, 5, -1);
    } else {
        if (CountMobysInGroupNotInState(vars->ids[i], -1) == 0) {
            if (FastFloatHelperD(&vars->f124)) {
                vars->idx = vars->idx + 1;
                SetMobyState(moby, 3, -1);
            }
        }
    }
    goto tail;
}
c2:
    SteerTowardTarget(moby);
    if (IsThirdPendingFlagSet(moby))
        SetMobyState(moby, 3, -1);
    goto tail;
c3: {
    float distance;
    unsigned short *p;
    char *member;
    char launchPos[16];

    distance = SteerTowardTarget(moby);
    if (distance < 3.0f) {
        if (vars->ids[vars->idx] != -1) {
            matrix_mul_vec3(launchPos, &D_L07_001B0C50, moby + 0xC0);
            FastVecAdd(launchPos, launchPos, moby + 0x10);
            for (p = gMobyGroupLists_L07[vars->ids[vars->idx]];
                 (vars->ids[vars->idx] & 0xFF) != 0xFF &&
                 vars->ids[vars->idx] <= D_L07_001B22F8[0] && p != 0 &&
                 ((short)p[-1] >= 0 || p == gMobyGroupLists_L07[vars->ids[vars->idx]]);
                 p++) {
                member = gMobyArray_L07[0] + ((*p & 0x7FFF) << 8);
                if (member == 0)
                    break;
                if (*(unsigned char *)(member + 0x20) != 0xFE) {
                    if (*(unsigned char *)(member + 0x20) != 0xFD) {
                        switch (*(short *)(member + 0xAA)) {
                        case 0xD29 /* moby class 3369 */:
                            PlayMobySound(0, 0, moby);
                            LaunchGroupMemberMode10(member, launchPos, member + 0x10, moby, vars->f110);
                            break;
                        case 0xD2A /* moby class 3370 */:
                            PlayMobySound(0, 0, moby);
                            LaunchGroupMemberMode8(member, launchPos, member + 0x10, moby, vars->f110);
                            break;
                        }
                    }
                }
            }
        }
        SetMobyState(moby, 4, -1);
    }
    goto tail;
}
c5: {
    SteerTowardTarget(moby);
    ApproachValue(&vars->f114, 0.16666667f, 0.00083333335f);
    vars->f118 += vars->f114;
    if (30.0f < vars->f118) {
        if (*(unsigned char *)(moby + 0x31) == 0) {
            MarkMobySpawned((int)moby);
            return;
        }
    }
}
tail:
    if (*(unsigned char *)(moby + 0x20) < 2)
        return;
    if (vars->f110 != 0)
        return;
    {
        char awayDir[16];
        int hitId;
        float damage;

        hitId = FindOwnedEffectSlot(moby, 0x10000, 0);
        damage = UpdateAimTargetStrength(moby, hitId);
        ApproachValue(&vars->f20, 0.0f, damage);
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        if (vars->f20 == 0.0f) {
            SpawnDebrisForMaskedParts(moby, 0x7F7, vars->b60, 0xFF, 5.0f, 10.0f, 5.0f, 10.0f);
            FastVecSub(awayDir, D_L07_001B9200, moby + 0x10);
            vec_scale_to_length(awayDir, awayDir, 1.0f);
            SpawnBlastEffectMoby(moby, moby + 0x10, awayDir, 0.0f);
            PlayMobySound(2, 0, moby);
            MarkMobySpawned((int)moby);
        }
    }
}
