#include "include_asm.h"
#include "names.h"

/* Level 23 globals the retail code reaches through $gp. */
extern char *D_L23_001B1484 __attribute__((sda));

extern int D_L23_001B13EC __attribute__((sda));

extern int D_L23_001B1658 __attribute__((sda));

extern int D_L23_001B15A4 __attribute__((sda));

extern int D_L23_001B178C __attribute__((sda));

extern int D_L23_001B1790 __attribute__((sda));

extern int D_L23_001B1794 __attribute__((sda));

extern int D_L23_001B1798 __attribute__((sda));

extern int D_L23_001B3788;

extern int D_L23_001B38C0;

extern int func_002E5CF8(int index, int a1, char *a2);

extern void func_0027DDC0(int, int, int, int);

extern int D_L23_001B1694 __attribute__((sda));

extern int D_L23_001B1698 __attribute__((sda));

extern float D_L23_001B14E4 __attribute__((sda));

extern void func_31A108(int);

extern void func_L23_0041A648(char *);

extern void func_L23_0042AC70(void);

/* Reports whether a word of the object reached through the pointer global is set. */
/* Says whether the boss has its "held" flag set. */
int func_L23_0041B948(void) {
    return *(int *)(*(char **)(gMothershipBossMoby + 0x68) + 0x604) != 0;
}

extern void func_0029F978(char *, int, char *);

extern void func_00283898(void *, int, float);

extern float func_00283BE0(float, float);

extern float D_L23_001B1570 __attribute__((sda));

extern float D_L23_001B1574 __attribute__((sda));

/* Relatches the two measured pairs at +0x580 and +0x584 from the two float arguments. */
/* Turns two boss joints a little each frame, starting their effects first if needed. */
void func_L23_0041BF18(char *moby, float deltaA, float deltaB) {
    char *vars = *(char **)(gMothershipBossMoby + 0x68);

    if (*(unsigned char *)(vars + 0x4F1) == 0)
        AttachManipulator(moby, 0x28, vars + 0x4F0);
    build_axis_rotation_quaternion(vars + 0x500, 0, *(float *)(vars + 0x580));
    *(float *)(vars + 0x580) = fast_subtract_rotations(*(float *)(vars + 0x580), deltaA * D_L23_001B1570 * 0.00029088825f);
    if (*(unsigned char *)(vars + 0x531) == 0)
        AttachManipulator(moby, 0x29, vars + 0x530);
    build_axis_rotation_quaternion(vars + 0x540, 0, *(float *)(vars + 0x584));
    *(float *)(vars + 0x584) = fast_subtract_rotations(*(float *)(vars + 0x584), deltaB * D_L23_001B1574 * 0.00029088825f);
}

typedef int TI128 __attribute__((mode(TI)));

extern void func_00283098(char *, char *, char *);

extern void func_00282CC0(char *, char *, char *);

extern void func_0032C700(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);

extern char D_00189E20[];

/* Builds the measured vector when the state's first word names the argument, and lays out the call. */
/* Spawns hit sparks on the thing that was hit (more if it is the hero) and plays a sound unless it is a shield. */
void func_L23_0041C578(char *hitMoby) {
    union {
        TI128 q;
        float f[4];
    } hitOffset;
    char *heroBase = gHeroState;

    if (*(char **)(heroBase + 0x2290) == hitMoby) {
        hitOffset.q = 0;
        hitOffset.f[0] = 1.3f;
        hitOffset.f[2] = 4.5f;
        hitOffset.f[3] = 1.0f;
        matrix_mul_vec3((char *)&hitOffset, (char *)&hitOffset, hitMoby + 0xC0);
        FastVecAdd((char *)&hitOffset, (char *)&hitOffset, heroBase + 0x80);
        SpawnExplosion((char *)&hitOffset, 0, 10, 10, 10, 25, 30, 0, 3.0f, 20.0f, 0, 1, 0, 0);
    } else {
        SpawnExplosion(hitMoby + 0x10, 0, 25, 20, 20, 15, 25, 1, 1.5f, 20.0f, 0, 0, 0, 0);
    }
    if (*(short *)(hitMoby + 0xAA) != 0x118F /* moby class 4495 */)
        PlayMobySound(3, 0, gMothershipBossMoby);
}

/* Zero unless the counter is positive and below the limit. */
/* Says whether the blast timer is running (above zero and below its limit). */
int func_L23_0041C0C0(void) {
    if (D_L23_001B1694 > 0 && D_L23_001B1694 < D_L23_001B1698)
        return 1;
    return 0;
}

/* One for the two measured state bytes, zero otherwise. */
/* Says whether the boss is in one of its two attack states. */
int func_L23_0041E260(void) {
    unsigned char mobyState = *(unsigned char *)(gMothershipBossMoby + 0x20);

    if (mobyState == 0x10 || mobyState == 0xC)
        return 1;
    return 0;
}



/* Stores one in the state at +0x68, after the measured shared call. */
/* Marks the boss as held and plays its sound the first time. */
void func_L23_0041B8F8(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (D_L23_001B13EC == 0 && gMothershipBossMoby != 0)
        PlayMobySound(0x10, 0, gMothershipBossMoby);
    *(int *)(vars + 0x604) = 1;
}

/* Clears the measured slot of the four state pointers and of the argument state. */
/* Turns off the extra object flags on all the boss parts so they stop reacting. */
void func_L23_0041BFF0(char *moby) {
    char *state = *(char **)(gMothershipBossMoby + 0x68);
    int *slot;
    int i;

    slot = *(int **)(state + 0x610);
    if (slot != 0)
        *(int *)((char *)slot + 0x98) = 0;
    slot = *(int **)(state + 0x614);
    if (slot != 0)
        *(int *)((char *)slot + 0x98) = 0;
    slot = (int *)(state + 0x358);
    for (i = 4; i >= 0; i--) {
        if (*slot != 0)
            *(int *)(*slot + 0x98) = 0;
        slot++;
    }
    *(int *)(moby + 0x98) = 0;
}

extern int D_L23_001B150C __attribute__((sda));

extern float D_L23_001B17A0 __attribute__((sda));

extern float D_L23_001B17A4 __attribute__((sda));

extern float D_L23_001B17A8 __attribute__((sda));

extern float D_L23_001B179C __attribute__((sda));

extern void func_00291450(int);

extern char D_00189EA0[];

extern void func_00282CC0(char *, char *, char *);

extern void func_00282D30(char *, char *, float);

extern float func_002A7878(float, float);

extern int func_L00_002FCF18(char *, float, float, float, float, float);

extern void func_L23_00418650(char *, float);

extern void func_L23_0041E3C8(void);

extern void func_0027D098(void (*)(void), int);

/* Releases the held handle, makes a new one from jittered values when the difference has low bits set, then registers the callback. */
/* Replaces the running beam effect with a new one with slightly random settings and hooks up its per-frame callback. */
void func_L23_0041E290(char *moby) {
    char offset[16];
    int frameDiff;
    float jitter;
    float valueA;
    float valueB;
    float valueC;

    frameDiff = D_L23_001B15A4 - D_L23_001B3788;
    if (D_L23_001B150C != -1)
        FreePointLight(D_L23_001B150C);
    if ((frameDiff & 3) != 0) {
        FastVecAdd(offset, moby + 0x10, gHeroPosition);
        FastVecScale(offset, offset, 0.5f);
        ProjectPointOntoPlanetSurface(offset, 5.0f);
        jitter = RandomFloatRange(0.0f, D_L23_001B17A0 * 0.33333334f);
        valueA = D_L23_001B17A0 + jitter;
        jitter = RandomFloatRange(0.0f, D_L23_001B17A4 * 0.33333334f);
        valueB = D_L23_001B17A4 + jitter;
        jitter = RandomFloatRange(0.0f, D_L23_001B17A8 * 0.33333334f);
        valueC = D_L23_001B17A8 + jitter;
        D_L23_001B150C = AllocateEffectSlot_L00_2(offset, 35.0f, D_L23_001B179C, valueA, valueB, valueC);
    }
    RegisterFinalDrawCallback(ApplyBossFadeRatio, (int)moby);
}

/* Calls the measured shared helper with the measured ratio expression. */
/* Passes the current fade amount to the screen effect. */
void func_L23_0041E3C8(void) {
    SetClearColorPacket(D_L23_001B1790, D_L23_001B1794, D_L23_001B1798,
                  (D_L23_001B15A4 - D_L23_001B3788) * D_L23_001B178C / D_L23_001B15A4);
}

/* Stores the incoming float in the level global reached through $gp. */
/* Sets the boss timer value used by the attack logic. */
void func_L23_0041B960(float value) { D_L23_001B14E4 = value; }

/* Copies the measured word of every live slot into the object the argument names. */
/* Gives all the boss parts their normal object flags back. */
void func_L23_0041C040(char *moby) {
    char *state = *(char **)(gMothershipBossMoby + 0x68);
    char *slot;
    char **p;
    int i;

    slot = *(char **)(state + 0x610);
    if (slot != 0)
        *(int *)(slot + 0x98) = *(int *)(*(char **)(slot + 0x24) + 0x10);
    slot = *(char **)(state + 0x614);
    if (slot != 0)
        *(int *)(slot + 0x98) = *(int *)(*(char **)(slot + 0x24) + 0x10);
    p = (char **)(state + 0x358);
    for (i = 4; i >= 0; i--) {
        if (*p != 0)
            *(int *)(*p + 0x98) = *(int *)(*(char **)(*p + 0x24) + 0x10);
        p++;
    }
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
}

/* Releases the three measured handles of the level state. */
/* Frees the boss effect handles when the boss fight ends. */
void func_L23_0041D930(void) {
    char *state;

    ReleaseBossEffectHandles(gMothershipBossMoby);
    state = *(char **)(gMothershipBossMoby + 0x68);
    if (*(char **)(state + 0x620) != 0) {
        func_31A108((int)*(char **)(state + 0x620));
        *(char **)(state + 0x620) = 0;
    }
    if (*(char **)(state + 0x624) != 0) {
        StopBothLoopingSounds();
        func_31A108((int)*(char **)(state + 0x624));
        *(char **)(state + 0x624) = 0;
    }
    if (*(char **)(state + 0x614) != 0) {
        func_31A108((int)*(char **)(state + 0x614));
        *(char **)(state + 0x614) = 0;
    }
}

/* Zero while the counter is negative. */
/* Says whether the blast timer is negative (cooling down). */
int func_L23_0041C0B0(void) {
    if (D_L23_001B1694 < 0)
        return 1;
    return 0;
}

/* Zero when the value is among the first D_L23_001B38C0 words of the table, else one. */
/* Says whether a value is not yet in the list of used slots. */
int func_L23_00419CA0(int value) {
    int *table = &D_L23_001B1658;
    int i;

    for (i = 0; i < D_L23_001B38C0; i++) {
        if (table[i] == value)
            return 0;
    }
    return 1;
}

extern int D_L23_001B1424 __attribute__((sda));

extern unsigned char D_001395B8[];


extern void func_0029B758(int, int);

extern void func_0029CE80(void);

/* Releases the five slot objects and the level object, then raises three flags. The flags are
 * written through a pointer set after the calls, as retail's `lui`/`addiu` base with the 0x88 and
 * 0xA1 displacements; written as D_001395B8[0xA1] and [0x88], the high half is hoisted into a
 * saved register (160 bytes). */
/* Removes the boss parts and boss object, then marks the fight as finished. */
void func_L23_0041D9B0(void) {
    char **p = (char **)(*(char **)(gMothershipBossMoby + 0x68) + 0x358);
    unsigned char *flags;
    int i;

    for (i = 4; i >= 0; i--) {
        if (*p != 0) {
            MarkMobySpawned(*p);
            *p = 0;
        }
        p++;
    }
    if (gMothershipBossMoby != 0) {
        StoreLevelObjectValuePair(0, 0);
        SetLevelDependentValue();
        MarkMobySpawned(gMothershipBossMoby);
        gMothershipBossMoby = 0;
    }
    flags = D_001395B8;
    D_L23_001B1424 = 1;
    flags[0xA1] = 1;
    flags[0x88] = 1;
}

/* The state at +0x68 as func_L23_0041BE70 reads it. Indexing the slot array through the
 * struct keeps the base first in the address sum (`addu $v0,$a0,$v0`); pointer arithmetic
 * puts the scaled index first. */
typedef struct Vars_0041BE70 {
    char pad0[0x358];
    char *slot[5];            /* 0x358 */
    char pad1[0x60C - 0x36C];
    int index;                /* 0x60C */
    char *held;               /* 0x610 */
} Vars_0041BE70;

/* A scalar: declared as an array, its address is scheduled differently in the two calls. */
extern int D_L23_001B36E0;

extern void func_002A90C8(void *, int, int, void *, float);

/* Attaches the level object, the indexed slot or the held object, with the argument's two
 * words. The two early returns give retail's arm layout: [no held object][slot][held]. */
/* Attaches a hit effect to the boss, one of its parts, or the held object. */
void func_L23_0041BE70(char *source) {
    char *state = gMothershipBossMoby;
    Vars_0041BE70 *vars = *(Vars_0041BE70 **)(state + 0x68);
    int index = vars->index;
    char *p;

    if (index == -1) {
        p = vars->held;
        if (p == 0) {
            StartEffectWithDefaultTable(state, *(int *)(source + 0x20), 0x10000, state + 0x10,
                          *(float *)(source + 0x2C));
            return;
        }
    } else {
        StartEffectWithDefaultTable(vars->slot[index], *(int *)(source + 0x20), 0x10000, &D_L23_001B36E0,
                      *(float *)(source + 0x2C));
        return;
    }
    if ((*(unsigned short *)(p + 0x34) | 0x4000) != 0)
        StartEffectWithDefaultTable(p, *(int *)(source + 0x20), 0x10000, &D_L23_001B36E0,
                      *(float *)(source + 0x2C));
}

extern float D_L23_001B1400 __attribute__((sda));

extern float D_L23_001B1404 __attribute__((sda));

extern float D_L23_001B1408 __attribute__((sda));

/* Returns the new value in $f0. Declared void, the call leaves $f0 free and the measure
 * reloaded right after it takes $f0 where retail has $f1. */
extern float func_002AA548(float *, float *, float, float, float, float);

extern float func_00282C48(float);

/* Springs the first measure toward its target at the three scaled global rates, and latches
 * it once it is within a tenth of the target. */
/* Eases a boss value toward its target, and stops once it is close enough. */
void func_L23_0041B498(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (*(int *)(vars + 0x5DC) != 0)
        return;
    StepValueTowardTarget((float *)(vars + 0x5C8), (float *)(vars + 0x5CC), *(float *)(vars + 0x5D0),
                  D_L23_001B1400 * 0.00027777778f, D_L23_001B1404 * 0.00027777778f,
                  D_L23_001B1408 * 0.016666668f);
    if (FloatAbs(*(float *)(vars + 0x5C8) - *(float *)(vars + 0x5D0)) < 0.1f) {
        *(int *)(vars + 0x5DC) = 1;
        *(int *)(vars + 0x5CC) = 0;
    }
}

extern void func_0029F338(void *);

extern void func_002E59F8(int);

extern void func_00291450(int);

extern int D_L23_001B1418 __attribute__((sda));

extern short D_L23_001B146C __attribute__((sda));

/* the two 8 x 3 handle tables */
extern void *D_L23_00259320[8][3];

extern void *D_L23_00259380[8][3];

/* four handles; declared at 8 bytes so this -G8 unit loads its address as the bare
   lui/addiu pair into one register, as retail does (an incomplete or 16-byte array splits it) */
extern void *D_L23_001B3790[2];

/* Releases the measured handles, then every object handle of the three tables, and clears them. */
/* Removes all the boss's effect objects and handles, and clears them. */
void func_L23_0041A648(char *boss) {
    char *vars = *(char **)(boss + 0x68);
    int i;
    int j;

    if (D_L23_001B1418 != -1) {
        StopSoundVoice(D_L23_001B1418);
        D_L23_001B1418 = -1;
    }
    if (D_L23_001B146C != -1) {
        FreePointLight(D_L23_001B146C);
        D_L23_001B146C = -1;
    }
    if (*(int *)(vars + 0x5B0) != 0) {
        *(int *)(vars + 0x5C4) = 0;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 3; j++) {
                if (D_L23_00259320[i][j] != 0) {
                    MarkMobySpawned(D_L23_00259320[i][j]);
                    D_L23_00259320[i][j] = 0;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (D_L23_001B3790[i] != 0) {
                MarkMobySpawned(D_L23_001B3790[i]);
                D_L23_001B3790[i] = 0;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 3; j++) {
                if (D_L23_00259380[i][j] != 0) {
                    MarkMobySpawned(D_L23_00259380[i][j]);
                    D_L23_00259380[i][j] = 0;
                }
            }
        }
        *(int *)(vars + 0x5B0) = 0;
    }
}

/* boot data: a pointer whose byte at +0x43 selects the draw range; nosda keeps its lui/lw pair */
extern unsigned char *D_0018C0B0 __attribute__((nosda));

extern int D_L23_00259050[3][60];

extern int func_002A77E0(int);

extern int func_L23_0041C8C0(char *, void *, int, int);

/* Draws a row (0, 1 or 2, the last one only when the byte at +0x43 is not 6) and hands the
 * position to func_L23_0041C8C0 with that row. The search for a free slot is retail's: its
 * result is never used. The three cases make cc1 build the decision tree rooted on 1 (with two,
 * it emits a comparison chain from 0). */
/* Picks a random effect row and spawns the effect at the given position. */
void func_L23_0041C7D8(void *pos, int extra) {
    int row = 0;
    int i;

    switch (RandomIntBelow(gHeroMoby_0018C0B0[0x43] == 6 ? 2 : 3)) {
    case 0:
        row = 1;
        break;
    case 1:
        row = 2;
        break;
    case 2:
        row = 0;
        break;
    }
    for (i = 0; i < 50; i++) {
        if (gEffectPools[row][i] == 0)
            break;
        if (i == 49) {
            i = -1;
            break;
        }
    }
    SpawnEffectInFreeSlot(gMothershipBossMoby, pos, row, extra);
}
/* The fields of the level state, the object and the hero this function reads. */
typedef struct {
    char pad0[0x408];
    int handle;
    char pad40C[0x588 - 0x40C];
    float limit;
    char pad58C[0x5B8 - 0x58C];
    float dist;
    float range;
    float level;
} C0E8State;

typedef struct {
    char pad0[0x10];
    TI128 pos;
    unsigned char state;
} C0E8Moby;

typedef struct {
    char pad0[0x80];
    float pos[4];
    char pad90[0x1DC - 0x90];
    short busy;
    char pad1DE[0x33C - 0x1DE];
    int armed;
    int charge;
    char pad344[0x34E - 0x344];
    short heat;
} C0E8Hero;

extern int D_L23_001B141C __attribute__((sda));

extern float D_L23_001B168C __attribute__((sda));

extern float D_L23_001B1690 __attribute__((sda));

extern int D_L23_001B169C __attribute__((sda));

extern int D_L23_001B16A4 __attribute__((sda));

extern int D_L23_001B16A8 __attribute__((sda));

extern int D_L23_001B16AC __attribute__((sda));

extern float D_L23_001B16B0 __attribute__((sda));

extern float D_L23_001B36D0[4] __attribute__((sda));

extern int D_L23_001B371C;

extern int func_00282948(int *);

extern void func_00282CF0(float *, float *, float *);

extern void func_00282F20(float *, float *, float);

extern void func_L23_0041E5B0(void *, int, int, TI128 *, float *, int);

extern int func_L23_00426248(void *, void *, int, int, int, int, int, int, float, int, int, int, int, int);

/* Runs the boss's charged blast: waits for the hero to charge, fires the blast, and pushes the hero back if close. */
void func_L23_0041C0E8(C0E8Moby *boss) {
    C0E8State *state = *(C0E8State **)(gMothershipBossMoby + 0x68);
    float impulse[4] __attribute__((aligned(16)));
    TI128 spawnPos;

    FastFloatHelperD(&D_L23_001B371C);
    if (boss->state == 0x10 && state->dist < D_L23_001B168C && state->level > state->limit &&
        FloatAbs(state->level - state->limit) < D_L23_001B1690) {
        C0E8Hero *hero = (C0E8Hero *)gHeroState;

        if (hero->charge >= 11 && D_L23_001B1694 == 0) {
            D_L23_001B16A4 = 1;
            D_L23_001B1694 = D_L23_001B169C;
            if (D_L23_001B16A8 != 0) {
                D_L23_001B16A8 = 0;
                D_L23_001B1694 = D_L23_001B1698;
            }
        }
    }
    if (D_L23_001B1694 > 0) {
        if (D_L23_001B1694 == D_L23_001B1698) {
            if (D_L23_001B16A4 != 0)
                D_L23_001B371C = 0;
            else
                D_L23_001B1694 += 2;
        } else {
            C0E8Hero *hero = (C0E8Hero *)gHeroState;

            if (hero->heat >= 11)
                D_L23_001B16A8 = 1;
        }
    }
    if (D_L23_001B16A8 != 0 && D_L23_001B1694 > D_L23_001B1698) {
        C0E8Hero *hero = (C0E8Hero *)gHeroState;

        if (hero->charge >= 11)
            D_L23_001B1694 = D_L23_001B1698;
    }
    {
        C0E8Hero *hero = (C0E8Hero *)gHeroState;

        if (hero->charge != 0 && hero->armed == 0)
            D_L23_001B16A8 = 0;
    }
    {
        C0E8Hero *hero = (C0E8Hero *)gHeroState;

        if (hero->charge >= 11 && D_L23_001B16A4 == 0 && D_L23_001B1694 > 0 && D_L23_001B1694 <= D_L23_001B1698)
            D_L23_001B1694 = D_L23_001B1698 + 5;
    }
    if (D_L23_001B1694 == D_L23_001B1698) {
        PlayMobySound(10, 0, (char *)boss);
        PlayMobySound(0x11, 0, (char *)boss);
    }
    if (D_L23_001B1694 < 0) {
        D_L23_001B1694++;
        if (D_L23_001B371C == 0) {
            C0E8Hero *hero = (C0E8Hero *)gHeroState;

            if (hero->charge != 0 && state->range < 10.0f && state->level > state->limit) {
                FastVecSub(impulse, hero->pos, (float *)&boss->pos);
                vec_scale_to_length(impulse, impulse, 3.0f);
                spawnPos = boss->pos;
                impulse[3] = 5627.9248046875f;
                PlayEffectOnTarget((void *)state->handle, 0x10007, 0x46, &spawnPos, impulse, 0);
                D_L23_001B371C = D_L23_001B141C;
                SpawnExplosion((char *)D_L23_001B36D0, 1, 5, 0x46, 3, 15, 20, 1, 3.0f, 20.0f, 0, 1, 0, 0);
            }
        }
    } else if (D_L23_001B1694 > 0) {
        FastFloatHelperD(&D_L23_001B1694);
        if (D_L23_001B1694 == 0) {
            state->handle = CreateSlotEffect(&boss->pos, boss, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1.0f, 1, 1, 0, 0, 0x40);
            D_L23_001B1694 = -D_L23_001B16AC;
            PlayMobySound(7, 0, (char *)boss);
            PlayMobySound(12, 0, (char *)boss);
            if (state->range < 15.0f && state->level > state->limit) {
                C0E8Hero *hero = (C0E8Hero *)gHeroState;

                if (hero->busy == 0) {
                    FastVecSub(impulse, hero->pos, (float *)&boss->pos);
                    vec_scale_to_length(impulse, impulse, D_L23_001B16B0);
                    spawnPos = boss->pos;
                    impulse[3] = 5627.9248046875f;
                    PlayEffectOnTarget(boss, 0x10007, 0x46, &spawnPos, impulse, 0);
                    SpawnExplosion((char *)D_L23_001B36D0, 1, 5, 0x46, 3, 15, 20, 1, 3.0f, 20.0f, 0, 1, 0, 0);
                }
            }
        }
    }
}
