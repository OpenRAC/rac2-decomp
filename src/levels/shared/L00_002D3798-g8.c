#include "common.h"

/* func_L00_002D5940 is here rather than in L00_002D3798.c because its tuning floats are read
   through $gp (-G8). */

typedef int Quad5940 __attribute__((mode(TI)));

typedef struct {
    float bounds[4];            /* 0x00; [3] is the radius */
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0x10];
    unsigned char drawn;        /* 0x31 */
    char pad32[0x2];
    unsigned short modeBits;    /* 0x34 */
    char pad36[0x2E];
    void (*update)(void *);     /* 0x64 */
    char pad68[0x42];
    short oClass;               /* 0xAA */
    char padAC[0x14];
    float rotMatrix[3][4];      /* 0xC0 */
    float rotation[4];          /* 0xF0 */
} Moby5940;

typedef struct {
    char pad0000[0x80];
    float position[4];          /* 0x0080 */
    char pad0090[0xC0];
    float velocity[4];          /* 0x0150 */
    char pad0160[0x14];
    float speed;                /* 0x0174 */
    char pad0178[0x1C8];
    int f340;                   /* 0x0340 */
    char pad0344[0x3EC];
    float transform[12];        /* 0x0730 */
    Quad5940 vector760;         /* 0x0760 */
    Quad5940 vector770;         /* 0x0770 */
    char pad0780[0xAA0];
    Moby5940 *object;           /* 0x1220 */
    char pad1224[0xC];
    int flags;                  /* 0x1230 */
    char pad1234[0x8];
    unsigned char visible;      /* 0x123C */
    char pad123D[0xB];
    int weapon;                 /* 0x1248 */
    char pad124C[0x254];
    float transitionPos[4];     /* 0x14A0 */
    float transitionRot[4];     /* 0x14B0 */
    float rotation[4];          /* 0x14C0 */
    char pad14D0[0x28];
    float blend;                /* 0x14F8 */
    float blendVelocity;        /* 0x14FC */
    char pad1500[0x4];
    float offsetVelocity;       /* 0x1504 */
    float offset;               /* 0x1508 */
    float offsetTarget;         /* 0x150C */
    float angle;                /* 0x1510 */
    float angleVelocity;        /* 0x1514 */
    char pad1518[0xD78];
    int owner;                  /* 0x2290 */
} Hero5940;

extern Hero5940 D_00189E20;
extern char D_L00_001B8FF0[], D_L00_001B8DC0[], D_L00_001BF220[];
extern Quad5940 D_L00_001B8DD0;
/* Incomplete sda arrays are read with the assembler's lui/load macro, as in retail. */
extern unsigned char D_001A7A44[] __attribute__((sda));
extern int D_L00_001B19C8[] __attribute__((sda));
extern float D_L00_001A7FE4[] __attribute__((sda));
extern const float D_L00_001A7FE0 __attribute__((sda));
extern float D_L00_001A7CE0 __attribute__((sda)), D_L00_001A7CE4 __attribute__((sda));

extern int func_L00_002ADED8(int);
extern void func_002A0F48(void *);
extern char *func_L00_002F3DA8(int);
extern int func_L00_002D6418(void);
extern void func_00283658(void *, void *);
extern void func_002AA2E8(float *, float, float);
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_00283B98(float, float), func_00283198(float);
extern void func_002830C0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00283410(void *, void *), func_00283738(void *, void *, void *);
extern void func_002AB6D8(void *, void *), func_002A91F0(void *, void *);
extern void func_00283098(void *, void *, void *), func_00282D08(void *, void *, void *, float);
extern void func_00283810(void *, void *, void *, float), func_00283958(void *, void *);
extern void func_00282D30(void *, void *, float), func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_00283678(void *, void *);

/* Places the hero's held object (D_00189E20.object): from the weapon's mount offset and
   rotation, a turning bob angle, the blend from the transition pose while blend < 1, and a
   ground probe that limits the vertical offset to [-1.5, 0]. */
void func_L00_002D5940(void) {
    Moby5940 *obj = gHeroState.object;
    char *mount;
    float m[16], rot[16], offset[4], temp[4], a[4], b[4];
    float turn, height, scale, target;
    int state;

    if (!obj)
        return;
    if (obj->oClass == 0x47 /* moby class 71 */) {
        if (!gHeroState.visible && !obj->state) {
            obj->drawn = 0;
            obj->modeBits |= 1;
        } else {
            obj->drawn = 1;
            obj->modeBits &= ~1;
        }
        return;
    }
    if (IsHeroSlotItemWrench(0)) {
        obj->modeBits |= 1;
        obj->drawn = 0;
        if (obj->update)
            obj->update(obj);
        func_002A0F48(obj);
        return;
    }

    mount = GetLevelTableEntryAddress(gHeroState.weapon);
    copy_matrix_rotation(m, D_L00_001B8FF0);
    qcopy_nc(&m[12], D_L00_001B8FF0 - 0x230);
    m[15] = 1.0f;
    qcopy_nc(offset, mount);
    offset[0] += gHeroState.offset;
    if (D_001A7A44[0] && !IsHeroActionAllowed())
        offset[1] = -offset[1];

    /* Turn rate in degrees per second (FE4 while moving, FE0 otherwise) to radians per frame. */
    if (gHeroState.speed > 0.02f)
        turn = D_L00_001A7FE4[0] * 0.0002908882452175021f;
    else
        turn = D_L00_001A7FE0 * 0.0002908882452175021f;
    ApproachValue(&gHeroState.angleVelocity, turn, 0.006981317885220051f);
    gHeroState.angle = FastAddRotations(gHeroState.angle, gHeroState.angleVelocity);
    offset[2] += FastSinOrCosB(gHeroState.angle) * 0.02f;

    transform_vector(obj->position, offset, m);
    if (!IsHeroActionAllowed())
        FastVecAdd(obj->position, obj->position, gHeroState.velocity);
    euler_to_matrix(rot, mount + 0x10);
    multiply_matrix3x3(obj->rotMatrix, m, rot);
    GetEulerAnglesFromMatrix(obj->rotMatrix, obj->rotation);
    BuildRotationFromAngles(gHeroState.rotation, obj->rotation);

    if (gHeroState.blend < 1.0f) {
        StepValueTowardTarget(&gHeroState.blend, &gHeroState.blendVelocity, 1.0f,
                      D_L00_001A7CE0 * 0.016666667f, D_L00_001A7CE4 * 0.00027777778f,
                      D_L00_001A7CE0 * 0.016666667f);
        matrix_mul_vec3(temp, gHeroState.transitionPos, &gHeroState);
        FastVecAdd(temp, temp, gHeroState.position);
        lerp_vector(obj->position, temp, obj->position, gHeroState.blend);
        BuildRotationFromAngles(a, obj->rotation);
        FastVectorNormalize3(b, gHeroState.transitionRot, a, gHeroState.blend);
        quaternion_to_rotation_basis(b, obj->rotMatrix);
    }

    obj->drawn = 1;
    obj->modeBits &= ~1;
    func_002A0F48(obj);

    if ((gFrameCounter_L00[0] ^ 1) & 1) {
        scale = 0.0009765625f;
        height = obj->bounds[3] * scale;
        FastVecScale(temp, obj->bounds, scale);
        vec_scale_to_length(a, obj->rotMatrix[1], height * -1.2f);
        FastVecAdd(a, a, temp);
        if (CollLine(gCameraPosition_L00, a, 0, gHeroState.owner, 0)) {
            target = (gHeroState.offset - height) + fast_vec_dist(D_L00_001BF220, temp);
            gHeroState.offsetTarget = target;
            if (target > 0.0f)
                gHeroState.offsetTarget = 0.0f;
            else if (target < -1.5f)
                gHeroState.offsetTarget = -1.5f;
        } else {
            gHeroState.offsetTarget = 0;
        }
    }

    StepValueTowardTarget(&gHeroState.offset, &gHeroState.offsetVelocity, gHeroState.offsetTarget,
                  0.0041666669f, 0.0041666669f, 0.083333336f);
    copy_matrix3x4(gHeroState.transform, m);
    qcopy_nc(&gHeroState.vector760, m);
    qcopy_nc(&gHeroState.vector770, &D_L00_001B8DD0);

    state = IsHeroActionAllowed();
    if (state)
        gHeroState.flags |= 5;
    if (obj->update)
        obj->update(obj);
    if (state)
        gHeroState.flags &= ~5;
}

/* func_L00_002D5EB8 */
extern int D_0018C350[];
extern unsigned char D_001A7A00[] __attribute__((sda));
extern int D_0018C2EC[];
extern unsigned char D_001A7A28[] MACRO_ADDR;
extern unsigned char D_00139568[];
extern int D_L00_001A903C;
extern unsigned short D_0018C958 __attribute__((section(".data")));
extern int D_00139868[];
extern int D_001A7398[] MACRO_ADDR;
extern unsigned char D_001A7AF8[] MACRO_ADDR;

/* One 0xE0-byte entry of D_L00_00262570, indexed through D_00139568. */
typedef struct {
    int exists;                 /* 0x00 */
    unsigned char state;        /* 0x04 */
    char pad05[0x7];
    int index;                  /* 0x0C */
    char pad10[0x3A];
    short value;                /* 0x4A */
    char pad4C[0x20];
    int limit;                  /* 0x6C */
    char pad70[0x70];
} Entry1269;

extern Entry1269 D_L00_00262570[];
extern int func_L00_002D5E30(int *, int *, int *);
extern void func_0028A180(int, int);
extern void func_L00_003F1300(void);
extern void func_L00_0030C7F8(int);
extern void func_002B0A18(int, int);
extern int func_002E5E58(int, int, void *);
extern int func_00288D58(void);
extern int func_00287F60(int);
extern void func_L00_0037E6A8(int, int);
extern void func_00287EB0(int);
extern void func_00288508(int);
extern int ref_L00_002D5EB8_00 __attribute__((sda));

static inline int special(int i)
{
    int r = 0;

    switch (i) {
    case 12:
    case 14:
    case 17:
    case 18:
    case 53:
        r = 1;
        break;
    }
    return r;
}

static inline int unlocked(Entry1269 *e, int i)
{
    if (e->state >= 2 || (e->state == 1 && special(i)))
        return 1;
    return 0;
}

static inline int owned(int i)
{
    if (gWeaponTable_L00[gItemSlotToRecord[i]].exists) {
        int n = CountChainEntriesAfterHead(i);
        if (n >= 2 || (n == 1 && special(i)))
            return 1;
    }
    return 0;
}

/* Checks the player's weapons and gadgets each frame: updates the item count, plays the unlock effects, and gives the final reward once everything is collected. */
void func_L00_002D5EB8(void)
{
    int count, i, j, ok;

    if ((gFrameCounter_L00[0] & 15) == 1 && gFrameCounter_L00[0] != 1)
        return;
    count = 4;
    {
        int *p = D_0018C350;
        SumTableEntriesUnderLimit(p, p - 1, &count);
    }
    for (j = 0; j < 10; j++)
        if (D_001A7A28[j])
            count++;
    if (*(int *)D_001A7A00 != count) {
        if (ref_L00_002D5EB8_00 >= 11 && *(int *)D_001A7A00 < count) {
            if (!gSubtitleHistory)
                QueueHintMessage(0x9A9, 0);
            SpawnEffectControllerMoby();
            CallLoadedModuleHandlerWithArg_0034B000(0x168);
            SetEntryValueByIndex(0x1235, -1);
            PlaySoundFromGlobalBank(6, 0, 0);
        }
        D_0018C2EC[0] = count;
        *(int *)D_001A7A00 = count;
    }

    for (i = 0; i < 56; i++) {
        if ((gWeaponTable_L00 + gItemSlotToRecord[i])->state) {
            if (!IsFlagByteSet())
                continue;
            if (CountChainEntriesAfterHead(i) == 1)
                continue;
        }
        {
            Entry1269 *e = &gWeaponTable_L00[gItemSlotToRecord[i]];
            int sel = 0;
            if (e->exists)
                sel = e->state == 3;
            if (sel)
                continue;
        }
        if (CountChainEntriesAfterHead(i) <= 0)
            continue;
        {
            Entry1269 *e = &gWeaponTable_L00[gItemSlotToRecord[i]];
            if ((D_00139868[i] >> 5) < e->limit || e->limit <= 0)
                continue;
            if (i == 31 || i == 9 || i == 45) {
                SetScreenPairAndRunEffect(i, gWeaponTable_L00[gItemSlotToRecord[i]].value);
                continue;
            }
            if (gHeroState.weapon == i) {
                if (!gHeroState.f340)
                    continue;
                if (D_001A7398[e->index] != i)
                    continue;
                SetScreenPairAndRunEffect(i, e->value);
                continue;
            }
        }
        if (IsFlagByteSet()) {
            Entry1269 *e = &gWeaponTable_L00[gItemSlotToRecord[i]];
            if (!e->exists)
                continue;
            if (unlocked(e, i)) {
                if (owned(i)) {
                    AdvanceChainEntry(i);
                    ShowHelpMessageForId(i);
                }
            }
        } else {
            AdvanceChainEntry(i);
            ShowHelpMessageForId(i);
        }
    }

    if ((gFrameCounter_L00[0] & 127) || D_001A7A00[0x7A])
        return;
    ok = 1;
    for (i = 0; i < 56; i++) {
        int ex = gWeaponTable_L00[gItemSlotToRecord[i]].exists;
        if (ex && i == 10)
            continue;
        if (ex && i == 9)
            continue;
        if (ex) {
            if (!gItemOwnedFlags[i]) {
                ok = 0;
                break;
            }
            if (i == 14 || i == 12 || i == 17 || i == 18 || i == 53)
                continue;
            if (CountChainEntriesAfterHead(i) <= 0)
                continue;
            if (!gWeaponTable_L00[gItemSlotToRecord[i]].state) {
                ok = 0;
                break;
            }
        }
    }
    if (ok && !D_001A7A00[0x7A]) {
        D_001A7A00[0x7A] = 1;
        PlaySoundFromGlobalBank(1, 0, 0);
        SetEntryValueByIndex(0x1233, -1);
        D_L00_001A903C = 1;
    }
}
