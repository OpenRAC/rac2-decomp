#include "common.h"


extern void func_0029F338(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_002AF000(void *, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_L08_003B2DB0(void *, void *, void *, int);
extern float func_002A7878(float, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7820(int, int);
extern void func_L04_00358AE8(void *, void *, int, int, float);

/* family c459a266b43242d6 - 352 bytes, 2 placements
   levels/19_grelbin @0x00412F70, levels/8_tabora @0x0041E630

   Fills five output floats from two pinned tables and a resident flag word,
   then clamps the three still free outputs to [-1, 1]. */

extern float D_00189E20_14[];

extern int D_00138180[];

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TI128 __attribute__((mode(TI)));

/* A resident word: the same address and the same value in every program.  It is
   read as a symbol here (the `sda` declaration leaves the one- or two-instruction
   choice to the assembler) and as a literal in func_L08_003DB4A0, whose two
   conditional loads the literal address form is what reproduces. */
extern s32 D_001A79F0 __attribute__((sda));

/* shared callee, named by its catalogue row (08:003289D0, 19:00319288) */
extern void func_L00_00326048(void *, s32, s32, s32, float);

extern char D_00189EA0[];
extern float func_00282E80(char *, void *);

/* Two 0x30-byte target records: [0] the tracked owner, [1] the nearest one seen. */
typedef struct {
    TI128 pos;      /* 0x00 */
    void *owner;    /* 0x10 */
    float dist;     /* 0x14 */
    s32 unk18;      /* 0x18 */
    s32 unk1C;      /* 0x1C */
    s32 valid;      /* 0x20 */
    s32 pad[3];
} L08Target;

extern L08Target D_L08_001B3490[] __attribute__((sda));

/* One entity of the group: the kind word is at 0xAA. */
typedef struct L08Thing {
    u8 pad[0xAA];
    s16 kind;
} L08Thing;

/* The group: the count is at 0x44, the list of entities at 0x18C. */
typedef struct L08Group {
    u8 pad0[0x44];
    s16 count;
    u8 pad1[0x18C - 0x46];
    L08Thing *items[1];     /* bounded by count */
} L08Group;

extern L08Group D_L08_001BD800;
extern s32 D_L08_001A8F00[] __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern u8 D_L08_001B22E0[] __attribute__((sda));
extern f32 D_L08_001B2300[] __attribute__((sda));

extern void func_0029F978(u8 *, u32, u8 *);

/* For func_L08_00435A78. */
extern void func_002A7750(void *, int, int);
extern s32 func_L08_00435938(void);
extern void func_L08_0036EFC8(void), func_L01_003128C0(void *);
extern int func_L01_003245E0(void *, int, float);
extern void func_L01_003246D0(void *), func_L01_00324550(int, ...);
extern int func_00288AA0(void *, int), func_002F5D10(void);
extern void func_00288BE8(void *), func_002A8598(int, int), func_L08_0036F030(void);
extern void func_0026FEB8(const char *, ...);
extern int func_0029B3E0(int, int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L00_0030C710(int);
extern int func_00282978(void *), func_00282948(void *), func_00283CF0(float);
extern float func_00283248(float, float), func_00283C80(float, float);
extern float func_00283B98(float, float), func_00283BE0(float, float), func_00282E20(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AEC48(void *, void *, int, float, float);

/* The hero: read at 0x80 (centre), 0xE0 (position) and 0x110 (velocity). */
typedef struct {
    u8 pad0[0x80];
    char x80[0x60];
    f32 pos[4];
    u8 padF0[0x20];
    f32 x110[4];
} L08Hero;
extern L08Hero D_00189E20;

/* One 0x100-byte entity of the table at D_L08_001B29DC. */
typedef struct {
    u8 pad0[0x31];
    u8 x31;
    u8 pad32[2];
    u16 x34;
    u8 pad36[0xBC - 0x36];
    u8 xBC;
    u8 padBD[0x100 - 0xBD];
} L08Moby;
extern L08Moby *D_L08_001B29DC MACRO_ADDR;

/* Words retail never moves into a delay slot are fields read at an offset from
   an earlier symbol; bare names are loaded by $gp in a slot (docs/build/compiler-notes.md). */
extern u8 D_001A7A00[] __attribute__((sda));
extern u8 D_L08_001A7C80[] __attribute__((sda));
extern int D_L08_001B2724[] __attribute__((sda));
extern int D_L08_001B2508 MACRO_ADDR;
extern int D_L08_001B1FA8 MACRO_ADDR;
extern int D_001A79F8 MACRO_ADDR;
extern u8 D_001395B8[];
extern int D_00138324;
extern int D_L08_00295E50[];
extern u8 D_L08_001BFD00[];
extern char D_L08_001B1FB0[];

/* Measures the resident actor position against POS: a nearer POS replaces record [1]
   (owner, distance, position), and record [0] is refreshed when OWNER is its owner.
   The records are reached as `sda` offsets, so every access is one assembler macro. */
/* Offers a candidate lock-on target: keeps it if it is the closest one seen so far this frame. */
void func_L08_003D3928(void *owner, void *pos)
{
    float distance = vec_distance_xy(gHeroPosition, pos);

    if (distance < D_L08_001B3490[1].dist) {
        D_L08_001B3490[1].unk1C = 0;
        D_L08_001B3490[1].owner = owner;
        D_L08_001B3490[1].unk18 = 0;
        D_L08_001B3490[1].dist = distance;
        qcopy(&D_L08_001B3490[1].pos, pos);
        D_L08_001B3490[1].valid = 1;
    }
    if (D_L08_001B3490[0].owner == owner) {
        D_L08_001B3490[0].dist = distance;
        qcopy(&D_L08_001B3490[0].pos, pos);
        D_L08_001B3490[0].valid = 1;
    }
}

/* func_L08_003D39F0 is defined in L08_003D3928-g8.c. */

/* One resident word, two states, and a 16-byte table entry: hands the entry to
   func_L00_00326048 with an alpha of 0x3D7A35E0. */
/* Updates a Glider Pad (moby class 2440): draws its glow effect once it has its data. */
void func_L08_003D3EB8(u8 *moby)
{
    s32 effectData = *(s32 *)(moby + 0x68);

    if (effectData == 0)
        return;
    StoreAngleUpdateResult(moby, effectData, 0x80AAAAD2, 0x80396464, 0.0610865355f);
}


/* Updates an effect object (moby class 2465): when its target is hit it plays an animation and
   throws a burst of sparks, and it removes itself when the target is gone. */
void func_L08_003D4690(u8 *moby)
{
    float direction[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float randomDir[4] __attribute__((aligned(16)));
    u8 *target = *(u8 **)*(u32 *)(moby + 0x68);
    int sparksLeft;
    if (!target || target[0x20] == 0xFE || target[0x20] == 0xFD) {
        MarkMobySpawned(moby);
        return;
    }
    if ((moby[0x60] & 2) && moby[0x43])
        StartAnimationBlended(moby, 0, 0, 0);
    if (moby[0xBC]) {
        moby[0xBC] = 0;
        if (moby[0x43] != 1) StartAnimationBlended(moby, 1, 0, 0);
        BuildSphericalOffset(direction, 1.0f, *(float *)(moby+0xF8), -*(float *)(moby+0xF4));
        TransformMobyJointToWorld(moby, 0, position);
        SpawnDirectedEffectObject(moby, position, direction, 0x5A);
        sparksLeft = 4;
        do {
            *(TI128 *)randomDir = 0;
            randomDir[0] = RandomFloatRange(-1.0f, 1.0f);
            randomDir[1] = RandomFloatRange(-1.0f, 1.0f);
            randomDir[2] = RandomFloatRange(-1.0f, 1.0f);
            *(TI128 *)velocity = *(TI128 *)randomDir;
            vec_scale_to_length(velocity, velocity, FastVecLength(direction)*0.65f);
            FastVecAdd(velocity, direction, velocity);
            vec_scale_to_length(velocity, velocity, RandomFloatRange(0.050000004f, 0.10000001f));
            SpawnVelocityParticle(position, velocity, 0x5F2F4F6F, RandomIntRange(5,10), 50000.0f);
        } while (--sparksLeft >= 0);
        vec_scale_to_length(direction, direction, 0.008333334f);
        SpawnVelocityParticle(position, direction, 0x2F4F7F7F, RandomIntRange(4,7), 500000.0f);
    }
}

/* Returns 2 in one special mode and 1 otherwise. */
/* The same resident word, but the 8 case falls through to a 1/2 selector. */
s32 func_L08_003DB4E8(void)
{
    s32 mode = gCurrentMapIndex;
    s32 result = 1;

    if (mode == 8)
        return 1;
    if (mode == 0x13)
        result = 2;
    return result;
}


/* func_L08_003DB8E8 is matched in its own unit, L08_003DB8E8-g8.c. */






/* func_L08_003F6610 is matched in its own unit, L08_003F6610-g8.c. */

/* func_L08_0041E4F8 is defined in L08_0041E4F8-flags-g8.c. */

/* Reads the controller and gives back five movement values, each limited to the range -1 to 1. */
/* shared native body of family c459a266b43242d6 */
void func_L08_0041E630(float *stickX, float *liftAxis, float *stickY, float *throttle, float *turnAxis)
{
    float axis;
    float upDown;
    int buttons;

    *stickX = -D_00189E20_14[2028];
    *stickY = -D_00189E20_14[2029];
    buttons = gPadState[104];
    upDown = 0.0f;
    if (buttons & 0x40)
        upDown = 1.0f;
    axis = (buttons & 0x20) ? (upDown - 1.0f) : upDown;
    *liftAxis = axis;
    *throttle = *(float *)&gPadState[75];
    buttons = gPadState[104];
    axis = 0.0f;
    if (buttons & 0x1)
        axis = 1.0f;
    if (buttons & 0x2)
        axis = axis - 1.0f;
    *turnAxis = axis;
    if (*stickX > 1.0f)
        *stickX = 1.0f;
    else if (*stickX < -1.0f)
        *stickX = -1.0f;
    if (*liftAxis > 1.0f)
        *liftAxis = 1.0f;
    else if (*liftAxis < -1.0f)
        *liftAxis = -1.0f;
    if (*turnAxis > 1.0f)
        *turnAxis = 1.0f;
    else if (*turnAxis < -1.0f)
        *turnAxis = -1.0f;
}

/* func_L08_0041E790 is defined in L08_0041E790-g8.c. */

/* func_L08_0041EA88 is defined in L08_0041EA88-match.c. */

/* func_L08_004207D0 is defined in L08_004207D0-g8.c. */

/* func_L08_0042E678 is defined in L08_0042E678-g8.c. */

/* func_L08_0042EF00 is defined in L08_0042EF00-g8.c. */

/* func_L08_00435600 is defined in L08_00435600-helpers.c. */

/* Copies a position value into the object's private data. */
/* Stores one 16-byte block through the pointer at 0x68 of the argument. */
void func_L08_004356A0(u8 *moby, void *source)
{
    *(volatile TI128 *)*(u32 *)(moby + 0x68) = *(TI128 *)source;
}

/* func_L08_004356B8 is defined in L08_004356B8-g8.c. */


/* Makes every other object of the same kind glow bright when the shop screen is open. */
/* For every listed entity of A0's kind, while the mode word is 2 and the resident
   flag is set, hands it to func_0029F978 with the level block at 0x001B22E0 unless its
   byte 1 is set, and sets the vector at 0x001B2300 to 2.3. */
void func_L08_00435990(L08Thing *sample)
{
    L08Thing *other;
    s32 i;

    if (D_L08_001A8F00[0] != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    for (i = 0; i < D_L08_001BD800.count; i++) {
        other = D_L08_001BD800.items[i];
        if (other->kind != sample->kind)
            continue;
        if (D_L08_001B22E0[1] != 0)
            continue;
        AttachManipulator((u8 *)other, 0, D_L08_001B22E0);
        D_L08_001B2300[0] = 2.3f;
        D_L08_001B2300[1] = 2.3f;
        D_L08_001B2300[2] = 2.3f;
    }
}

#define I(p, o) (*(int *)((u8 *)(p) + (o)))
#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define QUANTITY (*(s16 *)(D_001A7A00 + 0x1A))
#define PRICE (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2])

/* Updates The Mystic (moby class 3646), a shopkeeper that sells an item and buys back the
   player's collected bolts or Raritanium, and turns its head to watch the hero. */
/* An interaction state machine at byte 0x20: offers an item for its price while
   the quantity at D_001A7A00+0x1A covers it, then buys the remaining quantity back
   at 1000 (10000 with the flag at D_001A7A00+0xA) each; afterwards aims the head at the hero. */
void func_L08_00435A78(u8 *mystic)
{
    float lookTarget[4] __attribute__((aligned(16)));
    float headPos[4] __attribute__((aligned(16)));
    float toTarget[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(mystic + 0x68);
    int payMultiplier, watchingHero;
    float blendSpeed, yaw, pitch, angle;
    float blendWeight = 0.3f;

    HandleMysticEntityList((L08Thing *)mystic);
    if (D_L08_001A8F00[0] == 6) {
        mystic[0x31] = 0;
        H(mystic, 0x34) |= 1;
        F(mystic, 0xF4) = -3.14159274f;
    } else {
        mystic[0x31] = 1;
        F(mystic, 0xF4) = 0;
        H(mystic, 0x34) &= 0xFFFE;
    }
    if (D_L08_001B2508 == 5)
        GetLevelSavedCount();
    switch (mystic[0x20]) {
    case 0:
        if (!D_001395B8[0x1C])
            DisableObjectListFlags();
        else if (I(vars, 0x124) != -1) {
            MarkMobySpawned(&D_L08_001B29DC[I(vars, 0x124)]);
            I(vars, 0x124) = -1;
        }
        GetLevelSavedCount();
        ResetMobyVarsDefaults(mystic);
        if (D_001395B8[0x1C]) {
            if (QUANTITY <= 0)
                SetMobyState(mystic, 6, -1);
            else
                SetMobyState(mystic, 7, -1);
        } else if (D_001395B8[0x1B]) {
            if (QUANTITY < PRICE)
                SetMobyState(mystic, 3, -1);
            else
                SetMobyState(mystic, 4, -1);
        } else
            SetMobyState(mystic, 1, -1);
        break;
    case 1:
        if (IsHeroReachableForCount(mystic, 10, 2.5f)) {
            ApplyIndexForKey(mystic);
            if (PushRequestQueue(D_L08_001BFD00, 0x59)) {
                D_001395B8[0x1B] = 1;
                LaunchQueuedRequest(D_L08_001BFD00);
                SetMobyState(mystic, 2, -1);
            }
        }
        break;
    case 2:
        if (D_L08_001A8F00[0] == 2) {
            mystic[0x31] = 0;
            H(mystic, 0x34) |= 1;
        }
        if (I(vars, 0x124) != -1 && D_L08_001A8F00[0] == 2) {
            D_L08_001B29DC[I(vars, 0x124)].x34 |= 1;
            D_L08_001B29DC[I(vars, 0x124)].x31 = 0;
        }
        D_L08_001B2724[1] = 1;
        if (!IsEitherModeTwo()) {
            D_L08_001B2724[1] = 0;
            mystic[0x31] = 1;
            H(mystic, 0x34) &= 0xFFFE;
            if (I(vars, 0x124) != -1) {
                D_L08_001B29DC[I(vars, 0x124)].x34 &= 0xFFFE;
                D_L08_001B29DC[I(vars, 0x124)].x31 = 1;
            }
            if (QUANTITY < PRICE)
                SetMobyState(mystic, 3, -1);
            else
                SetMobyState(mystic, 4, -1);
        }
        break;
    case 3:
        if (QUANTITY >= PRICE)
            SetMobyState(mystic, 4, -1);
        else if (IsHeroReachableForCount(mystic, 10, 2.5f)) {
            PrintLocalizedFormatted(0x27A4, PRICE, -1);
            ApplyIndexForKey(mystic);
        }
        break;
    case 4:
        if (QUANTITY < PRICE)
            SetMobyState(mystic, 3, -1);
        else if (IsHeroReachableForCount(mystic, 10, 2.5f)) {
            PrintLocalizedFormatted(0x2796, PRICE, -1);
            ApplyIndexForKey(mystic);
            if (D_00138324 & 0x10) {
                PushRequestQueue(D_L08_001BFD00, 0x5A);
                QUANTITY -= PRICE;
                LaunchQueuedRequest(D_L08_001BFD00);
                SetMobyState(mystic, 5, -1);
            }
        }
        break;
    case 5:
        if (D_L08_001A8F00[0] == 2) {
            mystic[0x31] = 0;
            H(mystic, 0x34) |= 1;
        }
        if (I(vars, 0x124) != -1 && D_L08_001A8F00[0] == 2) {
            MarkMobySpawned(&D_L08_001B29DC[I(vars, 0x124)]);
            I(vars, 0x124) = -1;
        }
        D_L08_001B2724[1] = 1;
        if (!IsEitherModeTwo()) {
            D_L08_001B2724[1] = 0;
            mystic[0x31] = 1;
            H(mystic, 0x34) &= 0xFFFE;
            if (mystic[0x21] != 0xFF)
                SetByteOnGroupMobys(mystic[0x21], 1);
            D_001395B8[0x1C] = 1;
            RestoreObjectListFlags();
            STUB_printf(D_L08_001B1FB0);
            if (I(vars, 0x124) != -1) {
                MarkMobySpawned(&D_L08_001B29DC[I(vars, 0x124)]);
                I(vars, 0x124) = -1;
            }
            if (I(vars, 0x120) != -1)
                D_L08_001B29DC[I(vars, 0x120)].xBC = 1;
            MemcardSave(0, -1);
            if (QUANTITY <= 0)
                SetMobyState(mystic, 6, -1);
            else
                SetMobyState(mystic, 7, -1);
        }
        break;
    case 6:
        if (QUANTITY > 0)
            SetMobyState(mystic, 7, -1);
        else if (IsHeroReachableForCount(mystic, 10, 2.5f)) {
            if (!D_L08_001B1FA8)
                PrintLocalizedFormatted(0x27D0, 0, -1);
            else
                PrintLocalizedFormatted(0x27A7, -1);
            ApplyIndexForKey(mystic);
        }
        break;
    case 7:
        if (QUANTITY <= 0)
            SetMobyState(mystic, 6, -1);
        else {
            payMultiplier = D_001A7A00[0xA] ? 10 : 1;
            if (IsHeroReachableForCount(mystic, 10, 2.5f)) {
                payMultiplier *= 1000;
                PrintLocalizedFormatted(0x2797, QUANTITY, QUANTITY * payMultiplier, -1);
                ApplyIndexForKey(mystic);
                if (D_00138324 & 0x10) {
                    GetLevelSavedCount();
                    gPlayerBolts += QUANTITY * payMultiplier;
                    PlaySoundFromClassBank(0, 0, mystic, RandomIntRange(13, 17));
                    QUANTITY = 0;
                    func_L00_0030C710(180);
                    SetMobyState(mystic, 8, -1);
                }
            }
        }
        break;
    case 8:
        H(mystic, 0x96)++;
        if (H(mystic, 0x96) > 0x7FF8)
            H(mystic, 0x96) = 0x7FF8;
        if (H(mystic, 0x96) > 40 && H(mystic, 0x96) < 90 && H(mystic, 0x96) % 4 == 0)
            PlaySoundFromClassBank(0, 0, mystic, RandomIntRange(13, 17));
        if (IsHeroReachableForCount(mystic, 10, 2.5f))
            PrintLocalizedFormatted(0x27D0, D_L08_001B1FA8, -1);
        else
            SetMobyState(mystic, 6, -1);
        break;
    }
    if (mystic[0x20]) {
        if (mystic[0x43] == 1 && FastDecTimer(vars + 0x11E)) {
            H(vars, 0x11E) = FloatToInt(RandomFloatRange(1200, 2400));
            if (mystic[0x43] != 2)
                StartAnimationBlended(mystic, 2, 0, 10);
        } else if ((mystic[0x60] & 2) && mystic[0x43] != 1)
            StartAnimationBlended(mystic, 1, 0, 10);
    }
    blendSpeed = 0.02f;
    watchingHero = 0;
    if (mystic[0x43] == 1) {
        watchingHero = 1;
        if (vec_distance_xy((char *)mystic + 0x10, gHeroState.x80) < 8 &&
            FastDiffRots(F(mystic, 0xF8), FastMatrixHelperA(gHeroState.pos[0] - F(mystic, 0x10),
                                                       gHeroState.pos[1] - F(mystic, 0x14))) < 1.57079649f) {
            if (FastVecLength(gHeroState.x110) > 0.01f)
                I(vars, 0x114) = 120;
            else
                FastFloatHelperD(vars + 0x114);
        } else if (I(vars, 0x114)) {
            I(vars, 0x114) = 0;
            qcopy(vars + 0x100, gHeroState.pos);
        }
        if (FastFloatHelperD(vars + 0x118)) {
            I(vars, 0x118) = FloatToInt(RandomFloatRange(180, 300));
            angle = FastAddRotations(F(mystic, 0xF8), RandomFloatRange(-90, 90) * 0.0174532942f);
            pitch = RandomFloatRange(0, 30) * 0.0174532942f;
            BuildSphericalOffset(vars + 0x100, 6, angle, pitch);
            FastVecAdd(vars + 0x100, vars + 0x100, mystic + 0x10);
        }
        if (I(vars, 0x114)) {
            qcopy(lookTarget, gHeroState.pos);
            blendSpeed = 0.04f;
        } else
            qcopy(lookTarget, vars + 0x100);
    }
    if (watchingHero) {
        qcopy(headPos, mystic + 0x10);
        headPos[2] += 2;
        FastVecSub(toTarget, lookTarget, headPos);
        yaw = fast_subtract_rotations(FastMatrixHelperA(toTarget[0], toTarget[1]), F(mystic, 0xF8));
        pitch = -FastMatrixHelperA(vec_length_xy(toTarget), toTarget[2]);
        if (yaw > 1.57079649f)
            yaw = 1.57079649f;
        else if (yaw < -1.57079649f)
            yaw = -1.57079649f;
        if (pitch > 0.52359885f)
            pitch = 0.52359885f;
        else if (pitch < -0.52359885f)
            pitch = -0.52359885f;
        F(vars, 0x64) = pitch;
        F(vars, 0x68) = yaw * 0.6f;
        F(vars, 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40[0])
        F(vars, 0x70) = 2.75f;
    UpdateEasedNode(mystic, vars, 0, blendSpeed, blendWeight);
    UpdateEasedNode(mystic, vars + 0x80, 1, blendSpeed, blendWeight);
}

#undef I
#undef H
#undef F
#undef QUANTITY
#undef PRICE
