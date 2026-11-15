#include "common.h"

extern unsigned int D_L04_001B24DC;

extern int func_00282948(void *a0);

extern void func_L04_003F8FA0(unsigned char *a0);

extern void func_L04_003F9078(unsigned char *a0);

/* Update for the hoverbike race item box: waits for its owner slot to be active, then shows or hides itself. */
void func_L04_003F9270(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    int ownerIndex = *(int *)(vars + 8);
    unsigned char *ownerEntry;

    if (ownerIndex != -1) {
        ownerEntry = (unsigned char *)((ownerIndex << 8) + gMobyPool_L04);
        if ((unsigned int)(ownerEntry[0x20] - 2) >= 2) {
            return;
        }
    }
    if (moby[0x20] == 0) {
        *(int *)vars = 0;
        moby[0x30] = 0xFF;
        *(unsigned short *)(moby + 0x32) = 0x7F;
        moby[0x20] = 1;
        InitGlowRingMobyVariant(moby);
    }
    if (FastFloatHelperD(vars) != 0) {
        UpdateGlowRingMobyVariant(moby);
        *(unsigned short *)(moby + 0x34) &= 0xFFBE;
    } else {
        *(unsigned short *)(moby + 0x34) |= 0x41;
    }
}

typedef int L04_FBD80Quad __attribute__((mode(TI)));

/* The spawned object's state: a jitter table, a scale and a link back to the entity. */
typedef struct {
    float jitter[28];
    float scale;
    unsigned char *owner;
    int timer;
    float age;
} L04_FBD80Vars;

extern unsigned char *ref_L04_003FBD80_00(int kind);
extern int ref_L04_003FBD80_01(int a0, int a1, void *owner);
extern float ref_L04_003FBD80_02(float low, float high);
extern void func_L04_003FB990(unsigned char *object, L04_FBD80Vars *vars);
extern int D_L04_001B0488 __attribute__((sda));

/* Spawns a kind-0xABE object for an entity of kind 0xBBC: it takes the entity's 8-byte
   word at +0x38, the given position raised by 0.2 and the entity's quadword at +0xF0 (with
   +0xF4 replaced by the entity state's +0x284 when its +0x274 is set), and its state
   points back at the entity with a 0.5 scale and a jitter table of 28 random floats in
   [-10, 10] / 75, the first and last zero. Returns the object, or 0. */
/* Creates a shield dome effect around the given object at the given position. */
unsigned char *func_L04_003FBD80(unsigned char *owner, L04_FBD80Quad *posIn)
{
    float spawnPos[4] __attribute__((aligned(16)));
    unsigned char *dome;
    unsigned char *ownerVars;
    L04_FBD80Vars *domeVars;
    int handle;
    long ownerWord;
    int i;

    *(L04_FBD80Quad *)spawnPos = *posIn;
    if (owner == 0 || *(short *)(owner + 0xAA) != 0xBBC /* moby class 3004 */)
        return 0;
    dome = ref_L04_003FBD80_00(0xABE /* moby class 2750 */);
    if (dome != 0) {
        ownerVars = *(unsigned char **)(owner + 0x68);
        dome[0x30] = 0x7F;
        *(short *)(dome + 0x32) = 0x7F;
        dome[0x31] = 1;
        domeVars = *(L04_FBD80Vars **)(dome + 0x68);
        handle = ref_L04_003FBD80_01(9, 0, owner);
        ownerWord = *(long *)(owner + 0x38);
        D_L04_001B0488 = handle;
        *(long *)(dome + 0x38) = ownerWord;
        *(L04_FBD80Quad *)(dome + 0x10) = *(L04_FBD80Quad *)spawnPos;
        *(float *)(dome + 0x18) += 0.2f;
        *(L04_FBD80Quad *)(dome + 0xF0) = *(L04_FBD80Quad *)(owner + 0xF0);
        if (*(short *)(ownerVars + 0x274) != 0)
            *(float *)(dome + 0xF4) = *(float *)(ownerVars + 0x284);
        domeVars->owner = owner;
        domeVars->scale = 0.5f;
        domeVars->timer = 0;
        domeVars->age = 0;
        for (i = 0; i < 28; i++) {
            domeVars->jitter[i] = ref_L04_003FBD80_02(-10.0f, 10.0f) * 0.013333335f;
            if (i == 0 || i == 27)
                domeVars->jitter[i] = 0;
        }
        DamageMobysInFiringCone(dome, domeVars);
    }
    return dome;
}

typedef int UpdateQuad __attribute__((mode(TI)));
typedef float L04_EE090Vec[4] __attribute__((aligned(16)));
extern int D_L04_001B2008 MACRO_ADDR;
extern L04_EE090Vec D_L04_001B9680, D_00189EA0;
extern unsigned char D_L04_001A8F20[] MACRO_ADDR;
/* Table of 0x80-byte target records; targets[] below holds indices into it. */
extern unsigned char *D_L04_001B25CC __attribute__((sda));
extern unsigned char *D_L04_001FE340[];
extern void func_L04_003EDF80(unsigned char *, unsigned char *);
extern int func_L04_003EDFF0(unsigned char *, unsigned char *);
extern void func_0029F338(void *);
extern int func_002A8600(unsigned char **, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_002A7470(void *, int, int, int);
extern int func_00282978(short *);
extern int func_002A77E0(int);
extern void func_L04_003429F8(void *, void *, void *, int, void *, int, float);
extern int func_002A7820(int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282FB8(void *, void *, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_L02_0031E9E8(void *, float);
extern float func_002A7878(float, float);
extern float func_002A89A8(void *, int, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002ACB48(void *, float);
extern float func_L00_0031CDD0(void *, void *, int, float, float);
extern unsigned char *func_L04_003EDD40(void *, void *);
extern void func_002A7A00(void *, float, float);
extern void *func_L04_0030C4C0(void *, void *, void *, void *, void *, void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern char *func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_002A6C58(void *, int, int);

typedef struct {
    char pad0[0x20];
    float speed;
    char pad24[5];
    unsigned char active;
    char pad2a[0x46];
    float range;
    int idList;
    int pathIndex;
    short delay;
    short timer;
    unsigned char limit;
    unsigned char fired;
    unsigned char nearest;
    char pad83;
    int group;
    char pad88[8];
    int targets[4]; /* indices into D_L04_001B25CC, -1 for an empty slot */
    char padA0[0x50];
    UpdateQuad goal;
    char pad100[0x30];
    unsigned char *link;
    int linkState;
    char pad138[8];
    int shots;
} L04_EE090Vars;

/* Launcher: pick a target point near a record (nearest to the player, or a
 * random one), fire a child towards it, and retire after enough shots. */
/* Update for a launcher: picks a target point near a record or the player and fires a shot at it, until it runs out of shots. */
void func_L04_003EE090(unsigned char *moby)
{
    float target[4], delta[4], rotation[4], axis[4], position[4], velocity[4];
    L04_EE090Vars *vars = *(L04_EE090Vars **)(moby + 0x68);
    unsigned char *cursorMoby, *chosenTarget, *shot;
    int foundCount, slot;
    float speedScale, groundZ;

    StartMobyTimedEffect(moby, (unsigned char *)vars);
    if (moby[0x31] && fast_vec_dist(moby + 0x10, D_L04_001B9680) < 24.0f) {
        UpdateMobyGroundCheck(moby);
        moby[0x6F] = 22;
    }
    switch (moby[0x20]) {
    case 0:
        vars->active = 1;
        vars->speed = 1.0f;
        vars->shots = 0;
        if (D_L04_001B2008) {
            cursorMoby = 0;
            foundCount = 0;
            while (!GetFirstMobyInGroup(&cursorMoby, vars->group, 0, 0)) {
                MarkMobySpawned(cursorMoby);
                foundCount++;
            }
            if (foundCount < vars->limit)
                vars->limit = foundCount;
            moby[0x20] = 1;
        }
        break;
    case 1: {
        float best, distance;

        StartMobyTimedEffect(moby, (unsigned char *)vars);
        if (moby[0x43] == 1 && (moby[0x60] & 2))
            StartAnimationBlended(moby, 0, 0, 5);
        if (!FastDecTimer(&vars->timer))
            break;
        if (!RandomIntBelow(7)) {
            void *ids, *path;
            int n, pathCount;
            ids = 0;
            n = 0;
            path = 0;
            pathCount = 0;
            if (vars->idList != -1) {
                ids = &vars->idList;
                n = 1;
            }
            if (vars->pathIndex != -1) {
                unsigned char *d = gRoutePathTable[vars->pathIndex];
                path = d + 0x10;
                pathCount = *(int *)d;
            }
            FindHeroOrMobyTarget(moby, &vars->goal, ids, n, path, pathCount, vars->range);
        } else {
            unsigned char *q = vars->link;
            if (q && q[0x20] != 0xFE && q[0x20] != 0xFD) {
                qcopy_nc(&vars->goal, q + 0x10);
            } else {
                vars->link = 0;
                vars->linkState = 2;
            }
        }
        if (vars->linkState == 2)
            break;
        slot = CountSlotObjectsAndFindFreeSlot(moby, (unsigned char *)vars);
        if (vars->fired >= vars->limit || slot == -1)
            break;
        chosenTarget = 0;
        if (vars->nearest) {
            int i;
            best = 100000.0f;
            /* Read through an int-pointer view, as in func_L06_003F3800;
             * vars->targets[i] here gives different registers and stack slots. */
            for (i = 0; i < 4; i++) {
                int id = ((int *)((unsigned char *)vars + 0x90))[i];
                if (id != -1) {
                    unsigned char *q = D_L04_001B25CC + id * 128;
                    distance = fast_vec_dist(gHeroPosition, q + 0x30);
                    if (distance < best) {
                        chosenTarget = q;
                        best = distance;
                    }
                }
            }
            if (!chosenTarget) {
                FastVecSub(target, &vars->goal, moby + 0x10);
                FastVecScale(target, target, 0.5f);
                if (vars->range > 1.0f)
                    FastVectorDivideHelper(target, target, 1.0f);
                if (FastVecLength(target) < 1.0f)
                    vec_scale_to_length(target, target, 1.0f);
                FastVecAdd(target, target, moby + 0x10);
            } else {
                qcopy_nc(target, chosenTarget + 0x30);
            }
        } else {
            int i;
            int start = RandomIntRange(0, 3);
            /* targets[k] is read twice (cse merges the loads), keeping the
             * exit test short enough that jump1 does not peel an iteration. */
            for (i = 0; i < 4; i++) {
                int k = (i + start) % 4;
                if (vars->targets[k] != -1) {
                    chosenTarget = D_L04_001B25CC + vars->targets[k] * 128;
                    break;
                }
            }
            if (!chosenTarget) {
                float radius = vars->range;
                if (radius < 1.0f)
                    radius = 1.0f;
                RandomPlanarOffset(target, radius);
                FastVecAdd(target, target, moby + 0x10);
            } else {
                qcopy_nc(target, chosenTarget + 0x30);
            }
        }
        if (chosenTarget) {
            FastVecScale(delta, chosenTarget, RandomFloatRange(-0.5f, 0.5f));
            FastVecAdd(target, target, delta);
            FastVecScale(delta, chosenTarget + 0x10, RandomFloatRange(-0.5f, 0.5f));
            FastVecAdd(target, target, delta);
        }
        groundZ = ProbeGroundHeightBelow(target, 0, 3.0f);
        if (groundZ != 0)
            target[2] = groundZ;
        FastVecSub(delta, target, moby + 0x10);
        speedScale = FastVecLength(delta) * 0.0100000007f;
        vec_scale_to_length(delta, delta, speedScale);
        TransformMobyJointToWorld(moby, 0, rotation);
        vec_scale_to_length(axis, delta, 0.05f);
        AddRandomOffsetToVector(axis, 0.025f);
        delta[2] = ComputeShotLaunchSpeed(rotation, target, 0, speedScale, -0.00272222236f);
        *(UpdateQuad *)position = *(UpdateQuad *)(moby + 0x10);
        shot = SpawnChildMoby(moby, position);
        *(float *)(shot + 0x2C) = *(float *)(*(unsigned char **)(shot + 0x24) + 0x24);
        RandomDirectionVector(position, 2.0f, 3.0f);
        position[2] = 0;
        FastVecAdd(position, position, target);
        rotation[2] += 1.0f;
        *(UpdateQuad *)velocity = 0;
        velocity[2] = 3.0f;
        BuildSpawnRecordFromBlocks(shot, rotation, velocity, position, velocity, D_L04_001A8F20, 60, 0, 0);
        vars->fired++;
        vars->timer = vars->delay;
        if (++vars->shots >= 19)
            SetMobyState(moby, 2, -1);
        PlayMobySound(0, 0, moby);
        if (moby[0x43] != 1)
            StartAnimationBlended(moby, 1, 0, 5);
        break;
    }
    case 2:
        SpawnExplosion(moby + 0x10, 0, 25, 20, 20, 20, 20, 0, 1, 0, 0, 0, 0.75f, 20.0f);
        vars->speed = 0;
        PlayMobySound(1, 0, moby);
        SetDeathBits(moby, 0, 3);
        MarkMobySpawned(moby);
        break;
    }
}
