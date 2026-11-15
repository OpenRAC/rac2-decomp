#include "include_asm.h"
#include "common.h"

/* Quadword copies and clears, the spelling that reaches lq/sq. */
typedef int TI128 __attribute__((mode(TI)));

/* func_L07_003F4578 is defined in L07_003F4578-ring-g8.c. */

extern u8 D_L07_001B31AF __attribute__((sda));

/* Clears a block of 16 flag bytes to zero. */
void func_L07_0040FC50(void)
{
    u8 *p;
    s32 i;

    for (i = 15, p = &D_L07_001B31AF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}

/* func_L07_003F4970 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

/* func_L07_003F4B08 is defined in L07_003F4B08-copy.c. */

/* func_L07_003F4C18 is defined in L07_003F4C18-copy.c. */

/* func_L07_003F4CC0 is defined in L07_003F4578-beam-g8.c. */

/* func_L07_003F59C0 is defined in L07_003F59C0-g8.c. */

/* func_L07_003F5B50 is defined in L07_003F5B50.c. */

/* func_L07_003F6328 is defined in L07_003F6328.c. */

extern void func_3109C8(u8 *a, s32 b, s32 c);

extern f32 func_2E49C8(f32 a, f32 b);

extern f32 func_2E5360(f32 a, f32 b);

extern f32 D_L07_00189E20[];

extern void func_L07_003F68F0(u8 *a0, f32 x);

/* Starts the swinging turret: switches to state 2, picks which way to turn toward the player and aims it. */
void func_L07_003F6528(u8 *moby)
{
    u8 *vars;
    f32 side;

    func_3109C8(moby, 2, -1);
    vars = *(u8 **)(moby + 0x68);
    *(u8 *)(moby + 0x7F) = 0;
    *(f32 *)(vars + 0x20) = (f32)*(s16 *)(vars + 0x24);
    side = func_2E5360(func_2E49C8(D_L07_00189E20[0x20] - *(f32 *)(moby + 0x10),
                                D_L07_00189E20[0x21] - *(f32 *)(moby + 0x14)),
                    *(f32 *)(vars + 0x60));
    if (side > 0.0f) {
        *(f32 *)(vars + 0x54) = -1.5707964f;
    } else {
        *(f32 *)(vars + 0x54) = 1.5707964f;
    }
    UpdateSwingingYaw(moby, 0.0f);
}

extern u16 *D_L07_001FAD60[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern u8 *D_L07_001B22DC[] __attribute__((sda));
extern s32 D_L07_001B22F8[] __attribute__((sda));

extern s32 func_002A77E0(s32 n);

extern s32 func_00282948(s32 *counter);

/* Picks at random one of the group's entities that are in state 1: counts them, draws an index
   below the count, then walks the list again stepping the index down (func_00282948) until it
   runs out. Returns 0 when there is none. */
u8 *func_L07_003F65E8(s32 group)
{
    u16 *idPtr;
    u16 *idPtrB;
    u8 *entity;
    s32 activeCount = 0;
    s32 pickIndex;

    for (idPtr = gMobyGroupLists_L07[group];
         (group & 0xFF) != 0xFF && group <= D_L07_001B22F8[0] && idPtr != 0 &&
         ((s16)idPtr[-1] >= 0 || idPtr == gMobyGroupLists_L07[group]);
         idPtr++) {
        entity = gMobyArray_L07[0] + ((*idPtr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x20] == 1)
            activeCount++;
    }
    if (activeCount == 0)
        return 0;
    pickIndex = RandomIntBelow(activeCount);
    for (idPtrB = gMobyGroupLists_L07[group];
         (group & 0xFF) != 0xFF && group <= D_L07_001B22F8[0] && idPtrB != 0 &&
         ((s16)idPtrB[-1] >= 0 || idPtrB == gMobyGroupLists_L07[group]);
         idPtrB++) {
        entity = gMobyArray_L07[0] + ((*idPtrB & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x20] == 1 && FastFloatHelperD(&pickIndex) != 0)
            return entity;
    }
    return 0;
}

/* func_L07_003F67B8 is defined in L07_003F67B8-copy.c. */

/* func_L07_003F68F0 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

/* func_L07_003F6960 is defined in L07_003F4578-g8.c. */

/* func_L07_003F6C40 is defined in L07_003F6C40.c. */

/* func_L07_003F6CF0 is defined in L07_003F4578-spin-g8.c. */

/* func_L07_003F6DC0 is defined in L07_003F6DC0-copy.c. */

/* func_L07_003F7048 is defined in L07_003F7048-g8.c. */

/* An entity node: the flag word at 0x34, the counter at 0x98, two children. */
typedef struct SibNode SibNode;

struct SibNode {
    u8 pad00[0x34];
    u16 flags34;
    u8 pad36[0x68 - 0x36];
    SibNode *f68;
    u8 rest68[0x98 - 0x6C];
    s32 f98;
    u8 rest9c[0x410 - 0x9C];
    SibNode *f410;
    SibNode *f414;
};

/* Resets the object and its two child objects: sets their flags and clears their counters. */
void func_L07_003F78F8(SibNode *moby)
{
    SibNode *vars = moby->f68;

    moby->flags34 = (moby->flags34 | 0x41) & 0xEFFF;
    moby->f98 = 0;
    vars->f410->flags34 |= 0x41;
    vars->f410->flags34 &= 0xEFFF;
    vars->f410->f98 = 0;
    vars->f414->flags34 |= 0x41;
    vars->f414->flags34 &= 0xEFFF;
    vars->f414->f98 = 0;
}

/* func_L07_003F7968 is defined in L07_003F7968-g32.c. */

/* Returns the boss's current attack mode. */
u8 *func_L07_003F7BE0(u8 *moby)
{
    return *(u8 **)(*(u8 **)(moby + 0x68) + 0x420);
}

/* func_L07_003F7BF0 is defined in L07_003F7BF0-g8.c. */

extern void func_002A93B0(u8 *a);

extern void func_002A0F48(u8 *a);

extern void func_0029FC20(u8 *a, s32 b, void *c);

extern void func_00283678(u8 *a, void *b);

/* func_L07_003F8010 is defined in L07_003F8010-copy.c. */

/* func_L07_003F80B8 is defined in L07_003F4578-follow-g8.c. */

/* func_L07_003F8430 is defined in L07_003F8430-g8.c. */

/* func_L07_003F8780 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

extern void func_00282CF0(u8 *a, u8 *b, u8 *c);

extern void func_002AFDD8(u8 *a, u8 *b, u8 *c, s32 d);

/* func_L07_003F8828 is defined in L07_003F8828-copy.c. */

extern void func_00283098(u8 *a, u8 *b, u8 *c);

extern void func_00282CC0(u8 *a, u8 *b, u8 *c);

/* func_L07_003F8898 is defined in L07_003F8898-copy.c. */


/* func_L07_003F8AB0 is defined in L07_003F4578-qcopy.c (this unit needs the grouped quadword copy). */

extern void func_L07_003F43E0(u8 *a, u8 *b, void *c, void *d, f32 e);


extern u8 *func_L07_003F6B88(u8 *a);

extern void func_L07_003F6C40(u8 *a, u8 *b, void *c, f32 d);

/* One 128-byte record, its float field read by the measured index. */
typedef struct {
    u8 pad38[0x38];
    f32 f38;
    u8 rest[128 - 0x3C];
} SibRec128;

extern SibRec128 *D_L07_001B23CC;


/* func_L07_003F8D90 is defined in L07_003F8D90.c. */

extern void func_002A7470(u8 *a0, s32 a1, s32 a2, s32 a3);

/* Picks the boss's idle animation (one set while no attack mode is active, another while one is) and changes it only if it differs. */
void func_L07_003F9028(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u32 *)(vars + 0x420) == 0) {
        if (*(u8 *)(moby + 0x43) != 2) {
            StartAnimationBlended(moby, 2, 0, 10);
        }
        return;
    }
    if (*(u8 *)(moby + 0x43) != 8) {
        StartAnimationBlended(moby, 8, 0, 10);
    }
}

/* Picks the boss's attack animation (one set while no attack mode is active, another while one is) and changes it only if it differs. */
void func_L07_003F9088(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u32 *)(vars + 0x420) == 0) {
        if (*(u8 *)(moby + 0x43) != 3) {
            StartAnimationBlended(moby, 3, 0, 10);
        }
        return;
    }
    if (*(u8 *)(moby + 0x43) != 9) {
        StartAnimationBlended(moby, 9, 0, 10);
    }
}

extern u8 D_001A7BD0 __attribute__((sda));

extern void func_L01_003C91C8(u8 *a0);

/* Updates the object with the standard code, unless a global flag is set, in which case it only marks the object. */
void func_L07_003FF618(u8 *moby)
{
    if (D_001A7BD0 != 0) {
        *(u16 *)(moby + 0x34) |= 0x2;
        return;
    }
    UpdateCuboidTriggeredMoby(moby);
}

extern void func_310D80(void *a, f32 b, f32 c);

extern f32 func_2E4280(f32 a);

extern f32 func_310B30(f32 a, f32 b);

extern void func_31AFD8(void *a, void *b, f32 c, f32 d, f32 e);

extern void func_335848(void *a, void *b, s32 c);

/* The two shared level floats; `sda` gives the retail's `lui %hi ; swc1 %lo($at)` form. */
extern f32 D_L07_001AA698 __attribute__((sda));

extern f32 D_L07_001B3198 __attribute__((sda));

/* Runs the object's own 200 steps: each step advances the shared record's third
   float, then the three angles are computed and handed to the shared passes. */
/* Throws 200 sparks out of the object in random directions. */
void func_L07_00408338(u8 *moby)
{
    f32 sparkVelocity[4];
    f32 sparkPos[4];
    s32 i;
    f32 randomSpeed;
    f32 randomY;
    f32 randomX;

    D_L07_001B3198 = D_L07_001AA698;
    D_L07_001AA698 = 0.99f;
    for (i = 0xC7; i >= 0; i--) {
        func_310D80(sparkPos, 1.0f / 60.0f, 0.23333335f);
        sparkPos[2] = func_2E4280(sparkPos[2]) + 1.0f / 12.0f;
        randomX = func_310B30(-5.0f, 5.0f);
        randomY = func_310B30(-5.0f, 5.0f);
        randomSpeed = func_310B30(10.0f, 25.0f);
        func_31AFD8(moby, sparkVelocity, randomX, randomY, randomSpeed);
        func_335848(sparkVelocity, sparkPos, 0x1E0);
    }
}

/* func_L07_0040E198 is defined in L07_0040E198-g8.c. */

/* func_L07_0040E980 is defined in L07_0040E980-g8.c. */

/* func_L07_0040EC08 is defined in L07_0040EC08-g8.c. */


extern void func_338D68(void *a, s32 b, void *c, void *d, s32 e, f32 f);

extern f32 func_2E4508(void *a, void *b);

/* Works out the heading and tilt of a path at a given distance along it, by looking a little behind and a little ahead. */
void func_L07_0040EFC8(s32 *path, f32 *angles, f32 distance, f32 span)
{
    f32 aheadPoint[4];
    f32 behindPoint[4];
    f32 scratch[4];
    f32 behind = distance - span;
    f32 ahead;

    if (behind < 0.0f)
        behind = behind + (f32)path[0];
    ahead = distance + span;
    if ((f32)path[0] < ahead)
        ahead = ahead - (f32)path[0];
    func_338D68(path, 1, behindPoint, scratch, 0, behind);
    func_338D68(path, 1, aheadPoint, scratch, 0, ahead);
    angles[2] = func_2E49C8(behindPoint[0] - aheadPoint[0], behindPoint[1] - aheadPoint[1]);
    angles[1] = -func_2E49C8(func_2E4508(aheadPoint, behindPoint), behindPoint[2] - aheadPoint[2]);
}

/* func_L07_0040F0D0 is defined in L07_0040F0D0-g32.c. */

/* The object's state record up to its three group words (-1 means none). Indexing the array
   member is the spelling that gives retail's address arithmetic (the +0x94 base as a sum of its
   own, the group word read again inside the walk); a cast sum or a pointer variable does not. */
typedef struct {
    u8 pad[0x94];
    s32 groups[3];
} GroupState;

/* Walks the id list of each of the object's three groups, stopping at the first id with no
   entity; the walk itself does nothing. */
void func_L07_0040F598(u8 *a0)
{
    GroupState *state = *(GroupState **)(a0 + 0x68);
    s32 i;
    u16 *p;
    u8 *e;

    for (i = 0; i < 3; i++) {
        if (state->groups[i] == -1)
            continue;
        for (p = gMobyGroupLists_L07[state->groups[i]];
             (state->groups[i] & 0xFF) != 0xFF && state->groups[i] <= D_L07_001B22F8[0] && p != 0 &&
             ((s16)p[-1] >= 0 || p == gMobyGroupLists_L07[state->groups[i]]);
             p++) {
            e = gMobyArray_L07[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
        }
    }
}

/* func_L07_0040F6B8 is defined in L07_003F4578-geometry-g8.c. */

/* func_L07_0040F760 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */


typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) Vec4;
extern Vec4 D_L07_002A0100[][18];
extern void func_2E4310(void *a, void *b, void *c);
extern void func_2E4398(void *a, void *b, f32 c);
extern f32 func_2E44D0(void *a, void *b);

/* For each of three paths, finds the middle of its points and stores it after the last point, along with the largest distance of any point from it. */
void func_L07_0040F8F8(void)
{
    s32 i, pointCount, j, testIndex, sumIndex;
    f32 center[4];
    f32 distance;

    for (i = 0; i < 3; i++) {
        pointCount = 0;
        testIndex = 0;
        sumIndex = 0;
        qzero(center);
        /* separate counters for the test (testIndex) and the call (sumIndex); pointCount stays for after the loop */
        while (D_L07_002A0100[i][testIndex].w == 1.0f) {
            func_2E4310(center, center, &D_L07_002A0100[i][sumIndex]);
            pointCount++;
            sumIndex++;
            testIndex++;
        }
        func_2E4398(&D_L07_002A0100[i][pointCount], &D_L07_002A0100[i][pointCount], 1.0f / pointCount);
        D_L07_002A0100[i][pointCount].w = 0.0f;
        for (j = 0; j < pointCount; j++) {
            distance = func_2E44D0(&D_L07_002A0100[i][j], &D_L07_002A0100[i][pointCount]) + 4.0f;
            if (D_L07_002A0100[i][pointCount].w < distance)
                D_L07_002A0100[i][pointCount].w = distance;
        }
    }
}

extern u8 *D_L07_001B1F40 MACRO_ADDR;
extern s32 *D_L07_001FDEC0[];
extern void func_2E4DD8(void *, void *);
extern void func_2E47F8(void *, void *, void *);

/* Turns the stored path points into world positions using the object's own matrix and position, and saves them for its record. */
void func_L07_0040FA90(u8 *moby, s32 index)
{
    f32 matrix[16];
    f32 endPoint[4];
    u8 *state = *(u8 **)(moby + 0x68);
    s32 *dest;
    u8 *record;
    f32 radius;
    s32 i;

    if (*(s32 *)(state + 0xBC) == -1)
        return;
    record = D_L07_001B1F40 + *(s32 *)(state + 0xBC) * 0x30;
    dest = D_L07_001FDEC0[**(s32 **)(record + 0x3C)];
    *dest = 0;
    func_2E4DD8(matrix, moby + 0xC0);
    qcopy(matrix + 12, moby + 0x10);
    matrix[15] = 1.0f;
    for (i = 0; (D_L07_002A0100[index] + i)->w == 1.0f; i++) {
        func_2E47F8(dest + 4 + i * 4, D_L07_002A0100[index] + i, matrix);
        (*dest)++;
    }
    qcopy(endPoint, &D_L07_002A0100[index][*dest]);
    radius = endPoint[3];
    endPoint[3] = 1.0f;
    func_2E47F8(D_L07_001B1F40 + (*(s32 *)(state + 0xBC) * 0x30 + 0x20), endPoint, matrix);
    {
        u8 *table = D_L07_001B1F40;
        table += *(s32 *)(state + 0xBC) * 0x30;
        ((f32 *)table)[11] = radius;
    }
}

/* func_L07_0040FC88 is defined in L07_0040FC88-g16.c. */

/* func_L07_00410588 is defined in L07_00410588-snapshot.c. */

extern void func_002833F0(u8 *a, u8 *b);

extern void func_L00_00323958(u8 *a, u8 *b);

/* Builds the object's matrix from its angles, then updates its attached record. */
void func_L07_004106B8(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    euler_rotation_basis(moby + 0xC0, moby + 0xF0);
    UpdateAttachedObjectTransforms(moby, vars + 0x1B0);
}

/* func_L07_00410700 is defined in L07_00410700-g8.c. */

/* func_L07_00410930 is defined in L07_003F4578-g8.c (it takes the address of $gp data). */

/* func_L07_00410C50 is defined in L07_00410C50.c. */
