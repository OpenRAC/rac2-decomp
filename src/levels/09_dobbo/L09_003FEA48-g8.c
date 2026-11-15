#include "common.h"

extern f32 D_L09_001B13F0 __attribute__((sda));
extern f32 D_L09_001B13F4 __attribute__((sda));
extern void func_L08_00316678(char *a, s32 b, s32 c, s32 d);

typedef union {
    u16 h;
    s32 w;
} U16S32;

extern U16S32 D_L09_001B13C0 __attribute__((sda));
extern void func_2EA110(char *p);

/* Switches the creature to its fast-moving animation and sets its turn speed. */
void func_L09_00404B90(char *moby, s32 param) {
    char *self = moby;
    f32 speed = D_L09_001B13F0 * 0.0166666675f;
    char *vars = *(char **)(self + 0x68);
    *(f32 *)(vars + 0x1D4) = 3.0f;
    *(f32 *)(vars + 0x1D0) = speed;
    if (*(u8 *)(self + 0x43) == 7) {
        return;
    }
    func_L08_00316678(moby, 7, 0, param);
}

/* Switches the creature to its slow-moving animation and sets its turn speed. */
void func_L09_00404BF0(char *moby, s32 param) {
    char *self = moby;
    f32 speed = D_L09_001B13F4 * 0.0166666675f;
    char *vars = *(char **)(self + 0x68);
    *(f32 *)(vars + 0x1D4) = 1.75f;
    *(f32 *)(vars + 0x1D0) = speed;
    if (*(u8 *)(self + 0x43) == 6) {
        return;
    }
    func_L08_00316678(moby, 6, 0, param);
}

/* Ticks the object's two timers and its age counter, refilling the timers when needed. */
void func_L09_004031D8(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    u16 age;
    if (*(s16 *)(vars + 0x270) != 0
        || (*(s32 *)(vars + 0x234) == 1 && *(s16 *)(vars + 0x26C) < D_L09_001B13C0.w / 2)) {
        *(u16 *)(vars + 0x26C) = D_L09_001B13C0.h;
        *(s16 *)(vars + 0x270) = 0;
    }
    func_2EA110(vars + 0x26C);
    func_2EA110(vars + 0x26E);
    age = *(u16 *)(self + 0x96);
    if (age < 0xFFFF) {
        *(u16 *)(self + 0x96) = age + 1;
    }
}


/* Small-data handles: the resident mode word (-0x7600 -> 0x001A79F0), the resident
   release word (-0x5FB0 -> 0x001A9040) and the level's record table (0x386C ->
   0x001B285C), all read with $gp pinned at 0x001AEFF0. */
extern s32 D_L09_001A79F0 __attribute__((sda));
extern s32 D_L09_001A9040 __attribute__((sda));
extern char *D_L09_001B285C __attribute__((sda));

extern s32 func_323340(char *a0, char *a1, s32 a2);
extern char *func_L09_00326E90(char *a0);
extern void func_L09_003FE978(char *a0);
extern void func_326368(char *a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);

/* Drops the record the sub-object points at, once, when the resident mode word says 9,
   then rebuilds the sub-object's effect with both blend weights at zero. */
void func_L09_003FEA48(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    s16 recordIndex;

    if (func_323340(moby, vars + 0x160, 0) != 0) {
        if (D_L09_001A79F0 == 9) {
            recordIndex = *(s16 *)(vars + 0x1D0);
            if (recordIndex != -1) {
                if (IsHeroOrSpecialStateMoby(D_L09_001B285C + (recordIndex << 8)) == 0) {
                    D_L09_001A9040 = 0;
                }
                *(s16 *)(vars + 0x1D0) = -1;
            }
        }
        FlagGroupPeers(moby);
    }
    func_326368(moby, *(s32 *)(vars + 0x448), 0, 0, 0.0f, 0.0f);
}

/* The same resident mode word, read here as an ordinary global (lui + lw) rather than
   through $gp: the two references name the same word, one small and one not. */
extern s32 D_001A79F0;

extern void func_L09_00404C50(void);
extern float func_00282E48(char *a0, char *a1);
extern void func_002A93B0(void *a0);
extern s32 func_002B0ED8(char *a0, char *a1, s32 a2);
extern void func_L09_00405060(char *a0);
extern void func_L09_004050E0(char *a0);
extern s32 func_002B3BA8(char *a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);
extern char D_L09_001B9A00[];

/* Releases the record the sub-object holds once the resident mode word says 9, then
   rebuilds the sub-object's effect. */
void func_L09_00404E58(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    s32 hitLevel;
    s16 recordIndex;

    if (*(u8 *)(self + 0x20) == 0) {
        InitDobboWanderingMobyVars();
    }
    if (*(u8 *)(self + 0x31) != 0) {
        if (fast_vec_dist(self + 0x10, D_L09_001B9A00) < 24.0f) {
            UpdateMobyGroundCheck(self);
            *(u8 *)(self + 0x6F) = 0x16;
        }
    }
    hitLevel = ApplyDamageToObject(self, vars + 0x50, 0);
    if (gCurrentMapIndex == 9) {
        recordIndex = *(s16 *)(vars + 0xC0);
        if (recordIndex != -1) {
            if (IsHeroOrSpecialStateMoby(D_L09_001B285C + (recordIndex << 8)) == 0) {
                D_L09_001A9040 = 0;
            }
            *(s16 *)(vars + 0xC0) = -1;
        }
    }
    if (hitLevel != 0) {
        AlertGroupMobyClass3472(self);
        if (hitLevel >= 4) {
            DestroyMobyWithDebris(self);
        }
    }
    if (*(u8 *)(self + 0x95) != 3 && *(u8 *)(self + 0x95) != 4) {
        *(s16 *)(vars + 0x334) = SelectAimTarget_002B3BA8(self, *(s32 *)(vars + 0x230), 0, 0, 16.0f, 0.0f);
    }
}

extern void func_L09_00402D50(void);
extern void func_L09_00403100(char *a0, s32 a1);

/* The same release as func_L09_00404E58, with this level's own calls: when the
   resident mode word says 9 the record the sub-object holds is released, then the
   record's update runs with the value func_002B0ED8 returned, and the sub-object's
   effect is rebuilt from the sub-object's own index and position. */
void func_L09_00403270(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    s32 hitLevel;
    s16 recordIndex;

    if (*(u8 *)(self + 0x20) == 0) {
        InitDobboEnemyVars();
    }
    if (*(u8 *)(self + 0x31) != 0) {
        if (fast_vec_dist(self + 0x10, D_L09_001B9A00) < 48.0f) {
            UpdateMobyGroundCheck(self);
            *(u8 *)(self + 0x6F) = 0x2D;
        }
    }
    hitLevel = ApplyDamageToObject(self, vars + 0x50, 0);
    if (gCurrentMapIndex == 9) {
        recordIndex = *(s16 *)(vars + 0xC0);
        if (recordIndex != -1) {
            if (IsHeroOrSpecialStateMoby(D_L09_001B285C + (recordIndex << 8)) == 0) {
                D_L09_001A9040 = 0;
            }
            *(s16 *)(vars + 0xC0) = -1;
        }
    }
    AlertGroupAndWakeFirstMember(self, hitLevel);
    SelectAimTarget_002B3BA8(self, *(s32 *)(vars + 0x28C), 0, 0, *(f32 *)(vars + 0x24C), 0.0f);
}

/* The walks below read the group table of id lists absolute. The group count and the entity base
   are plain externs here, which come out as bare `lui`/`lw` pairs in ordinary flow and as $gp
   loads in a branch delay slot; the base takes a second name because D_L09_001B285C above is the
   $gp form. */
extern s32 D_L09_001B2878;

extern u8 *D_L09_001B285C_1;

extern u16 *D_L09_001FB560[];

/* The vector the scaled copy starts from: small data, so its address is a $gp offset. */
extern char D_L09_001B1410[1] __attribute__((sda));

/* The colour pair func_00283D38 blends. */
extern s32 D_L09_001B1420[2];

extern void func_00282D30(char *, char *, f32);

extern void func_002830C0(char *, char *, char *);

extern s32 func_00283D38(s32, s32, f32);

extern void func_L00_00325AE8(char *, s32, f32, f32);

typedef struct {
    s32 a, b;
} ColorPair;

/* The object's blended colour word: a member store, which the scheduler knows cannot alias the
   scalar global D_L09_001B2388 (a plain cast store it must keep in front of that load). */
typedef struct {
    u8 pad[0x78];
    s32 colour;
} TintedObject;

extern ColorPair D_L09_001B1400[2];

extern s32 D_L09_001B2388;

extern f32 func_00283B98(f32, f32);

extern f32 func_00283198(f32);

extern void func_0029FC20(u8 *, s32, u8 *);

extern void func_L00_002E6CF0(void *, u8 *);

void func_L09_00405490(u8 *a0);

/* Steps the object's pulse: the angle at +0x348 advances by 2*pi/30 through the resident angle
   blend, its sine is mapped to 0..1 and kept at +0x34C, and the colour pair D_L09_001B1400 is
   blended by it into the object's word at +0x78. When the state's stamp (+0x350) differs from
   D_L09_001B2388, every visible class-0xD90 entity of the object's group that is not in state
   0xFE or 0xFD gets its point refreshed (func_0029FC20, selector 0) into its vector at +0x240
   and the same stamp; then func_L09_00405490 is registered as the object's callback. */
void func_L09_004052F8(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    ColorPair color = D_L09_001B1400[0];
    u16 *idPtr;
    u8 *entity;
    u8 *entityVars;
    f32 angle;
    f32 wave;

    angle = FastAddRotations(*(f32 *)(state + 0x348), 0.20943954f);
    *(f32 *)(state + 0x348) = angle;
    wave = FastSinOrCosB(angle) * 0.5f + 0.5f;
    *(f32 *)(state + 0x34C) = wave;
    ((TintedObject *)moby)->colour = FastTweenColor(color.a, color.b, wave);
    if (*(s32 *)(state + 0x350) != D_L09_001B2388) {
        for (idPtr = D_L09_001FB560[moby[0x21]];
             moby[0x21] != 0xFF && moby[0x21] <= D_L09_001B2878 && idPtr != 0 &&
             ((idPtr != 0 && (s16)idPtr[-1] >= 0) || idPtr == D_L09_001FB560[moby[0x21]]);
             idPtr++) {
            entity = D_L09_001B285C_1 + ((*idPtr & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (entity[0x31] != 0 && *(s16 *)(entity + 0xAA) == 0xD90 /* moby class 3472 */) {
                if (entity[0x20] != 0xFE) {
                    if (entity[0x20] != 0xFD) {
                        entityVars = *(u8 **)(entity + 0x68);
                        TransformMobyJointPoint(entity, 0, entityVars + 0x240);
                        *(s32 *)(entityVars + 0x350) = D_L09_001B2388;
                    }
                }
            }
        }
        AddDrawCallbackToList1((void *)DrawPulsingEntityGlows, moby);
    }
}

/* Callback of func_L09_004052F8 for every class-0xD90 entity of the object's group that is not
   hidden (byte 0x31) or in state 0xFE or 0xFD: scales the sub-object's vector by its float at
   +0x344, transforms it by the matrix at +0x240, blends the colour pair by the float at +0x34C
   and hands the result to func_L00_00325AE8 with the +0x344 float scaled by 0.2. */
void func_L09_00405490(u8 *moby) {
    f32 point[4];
    u16 *idPtr;
    u16 *groupList;
    u8 *entity;
    u8 *entityVars;
    s32 color;

    if (moby[0x21] == 0xFF)
        return;
    groupList = D_L09_001FB560[moby[0x21]];
    if (groupList == 0)
        return;
    for (idPtr = groupList;
         moby[0x21] != 0xFF && moby[0x21] <= D_L09_001B2878 && idPtr != 0 &&
         ((idPtr != 0 && (s16)idPtr[-1] >= 0) || idPtr == D_L09_001FB560[moby[0x21]]);
         idPtr++) {
        entity = D_L09_001B285C_1 + ((*idPtr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x31] != 0 && *(s16 *)(entity + 0xAA) == 0xD90 /* moby class 3472 */) {
            if (entity[0x20] != 0xFE) {
                if (entity[0x20] != 0xFD) {
                    entityVars = *(u8 **)(entity + 0x68);
                    FastVecScale((char *)point, D_L09_001B1410, *(f32 *)(entityVars + 0x344));
                    transform_vector((char *)point, (char *)point, (char *)(entityVars + 0x240));
                    color = FastTweenColor(D_L09_001B1420[0], D_L09_001B1420[1],
                                      *(f32 *)(entityVars + 0x34C));
                    DrawBillboardQuad_L00((char *)point, color, *(f32 *)(entityVars + 0x344) * 0.2f, 0.08f);
                }
            }
        }
    }
}

extern int func_316A28(int a);
extern int func_316A68(int a, int b);
extern void func_31F4D0(char *a0, int a1);
extern float func_2EB478(float a, float b);
extern float func_2EAA60(float a);
extern float func_2EAA78(float a);
extern int func_2EB5D0(float a);
extern void func_2EA750(float f12, void *a0, void *a1);
extern int D_L09_001B15B8 __attribute__((sda));
extern int D_L09_001B15B8_4[] MACRO_ADDR;
extern float D_L09_001B15C4 __attribute__((sda));
extern float D_L09_001B15C0 __attribute__((sda));
extern int D_L09_001B15B4 __attribute__((sda));
extern u8 D_L09_001B15B0 __attribute__((sda));

/* Spins a moving object around and sets its direction, facing and blend from its path values. */
void func_L09_0040B0C8(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *velocity;
    float dir[3];
    int frameOffset;
    float scale;
    int animId;
    if (func_316A28(7)) {
        animId = D_L09_001B15B8;
    } else {
        animId = D_L09_001B15B8_4[1];
    }
    func_31F4D0(moby, animId);
    velocity = moby + 0xC0;
    *(float *)(vars + 0x10) = func_2EB478(*(float *)(vars + 0x10), D_L09_001B15C4 * 0.00029088825f);
    dir[0] = func_2EAA60(*(float *)(vars + 0x10)) * D_L09_001B15C0;
    dir[1] = func_2EAA78(*(float *)(vars + 0x10)) * D_L09_001B15C0;
    dir[2] = 0;
    scale = (float)D_L09_001B15B4;
    *(float *)(moby + 0xF0) = dir[0];
    *(float *)(moby + 0xF4) = dir[1];
    frameOffset = func_2EB5D0(scale * (*(float *)vars + *(float *)(vars + 4)) * 0.5f);
    *(u8 *)(moby + 0x23) = D_L09_001B15B0 + frameOffset + func_316A68(-9, 9);
    *(u16 *)(moby + 0x34) |= 0x800;
    func_2EACD0(velocity, moby + 0xF0);
    func_2EA750(*(float *)vars, velocity, velocity);
    func_2EA750(*(float *)(vars + 4), moby + 0xD0, moby + 0xD0);
}

typedef struct { u8 pad[0x464]; u8 spent[1]; } L09_CellFlags;
extern L09_CellFlags D_L09_0021E9F0;
extern u8 D_0019B4A8[];
extern char *D_L09_001B294C[] __attribute__((sda));
extern void func_317B40(int a0, int a1, int a2, int a3);

/* Updates the indicator on a linked object, lighting it up once the item it needs has been collected. */
void func_L09_00406E78(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *linked;
    char *linkedVars;
    int itemId;
    int flags;
    s32 linkedIndex = *(s32 *)(vars + 0x64);

    if (linkedIndex == -1)
        return;
    linked = (char *)((linkedIndex << 8) + (int)D_L09_001B285C);
    if (*(u8 *)(linked + 0x20) == 0xFE)
        return;
    if (*(u8 *)(linked + 0x20) == 0xFD)
        return;
    linkedVars = *(char **)(linked + 0x68);
    if (*(s32 *)(linkedVars + 0x70) == -1)
        return;
    if (*(s32 *)(vars + 0x50) != -1
        && (itemId = *(u16 *)((*(s32 *)(vars + 0x50) << 8) + (int)D_L09_001B285C + 0xB2),
            D_L09_0021E9F0.spent[(s16)itemId] != 0
            || (flags = D_0019B4A8[((s16)itemId >> 1) + (gCurrentMapIndex << 10)],
                (itemId & 1) ? (flags >> 4) & 7 : flags & 7) != 0)) {
        *(float *)((*(s32 *)(linkedVars + 0x70) << 7) + (int)D_L09_001B294C[0] + 0x38) = 325.25f;
        func_317B40(*(s32 *)(vars + 0x4C), 1, 1, 1);
    } else {
        *(float *)((*(s32 *)(linkedVars + 0x70) << 7) + (int)D_L09_001B294C[0] + 0x38) = 325.0f;
        func_317B40(*(s32 *)(vars + 0x4C), 0, 0, 0);
    }
}

extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_0019B278[];
extern u8 D_001A7A28[] __attribute__((sda));
extern void func_30C790(char *a0);
extern void func_L09_00406C90(char *a0);

/* Checks whether every requirement is met and, if so, releases the two linked objects and finishes. Returns 1 when done. */
s32 func_L09_00406CC0(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    s32 none;
    s32 linkedIndex;
    s32 itemId;

    if (D_0018C0B4 == 0x31)
        return 0;
    if (*(s32 *)(vars + 0x2C) != -1) {
        char *linked = (char *)((*(s32 *)(vars + 0x2C) << 8) + (s32)D_L09_001B285C);
        if (*(u8 *)(linked + 0x20) != 0xFE) {
            if (*(u8 *)(linked + 0x20) != 0xFD) {
                if (D_0019B278[*(s32 *)*(char **)(linked + 0x68) + (gCurrentMapIndex << 2)] == 0)
                    return 0;
            }
        }
    }
    if (*(s32 *)(vars + 0x7C) != -1) {
        char *linked = (char *)((*(s32 *)(vars + 0x7C) << 8) + (s32)D_L09_001B285C);
        if (*(u8 *)(linked + 0x20) != 0xFE) {
            if (*(u8 *)(linked + 0x20) != 0xFD) {
                if (*(u8 *)(*(s32 *)*(char **)(linked + 0x68) + (s32)D_001A7A28) == 0)
                    return 0;
            }
        }
    }
    linkedIndex = *(s32 *)(vars + 0x50);
    if (linkedIndex != -1) {
        itemId = *(u16 *)((linkedIndex << 8) + (s32)D_L09_001B285C + 0xB2);
        if (D_L09_0021E9F0.spent[(s16)itemId] == 0) {
            s32 flags = D_0019B4A8[((s16)itemId >> 1) + (gCurrentMapIndex << 10)];
            if (itemId & 1)
                flags = (flags >> 4) & 7;
            else
                flags = flags & 7;
            if (flags == 0)
                return 0;
        }
    }
    none = -1;
    linkedIndex = *(s32 *)(vars + 0x64);
    if (linkedIndex != none) {
        func_30C790((linkedIndex << 8) + D_L09_001B285C);
        *(s32 *)(vars + 0x64) = none;
    }
    linkedIndex = *(s32 *)(vars + 0x68);
    if (linkedIndex != none) {
        func_30C790((linkedIndex << 8) + D_L09_001B285C);
        *(s32 *)(vars + 0x68) = none;
    }
    ReleaseLinkedMoby(moby);
    return 1;
}
