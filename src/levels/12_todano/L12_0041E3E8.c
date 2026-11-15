#include "common.h"

/* func_L12_0041E3E8 is defined in L12_0041E3E8-update-g8.c. */

/* Tells if the given moby has reached its final state. */
s32 func_L12_0041E8E8(u8 *self) {
    return *(u8 *)(self + 0x20) == 3;
}
extern int D_001A79F0 __attribute__((sda));
extern char D_0019B4A8[];
extern char D_00189EA0[];
extern void func_00282CF0(f32 *, const f32 *, const f32 *);
extern void func_002AFEB8(char *, char *, char *, char *, f32);
extern void func_00282F20(f32 *, f32 *, f32);
extern void func_002B0A68(void *, s32, void *, f32, f32, f32, f32, s32);

/* Sets off the moby: spawns a small burst, adds one to the saved progress counter and plays a sound. */
void func_L12_0041E8F8(u8 *moby) {
    u8 *self = moby;
    f32 vec[4];
    u16 rawId;

    FastVecSub(vec, (f32 *)(self + 0x10), (f32 *)gHeroPosition);
    TransformAndSetHeight((char *)self, (char *)vec, (char *)vec, 0, 0.0f);
    vec_scale_to_length(vec, vec, 0.10000000894069672f);
    SpawnDebrisForMaskedParts(self, 31, vec, 6.0f, 12.0f, 6.0f, 12.0f, 255);

    rawId = *(u16 *)(self + 0xB2);
    if (rawId & 1) {
        u8 *counter = (u8 *)(((s16)rawId >> 1) + (gCurrentMapIndex << 10)) + (int)D_0019B4A8;
        u8 packed = *counter;

        if (((packed >> 4) & 7) != 7)
            *counter = packed + 0x10;
    } else {
        u8 *counter = (u8 *)(((s16)rawId >> 1) + (gCurrentMapIndex << 10)) + (int)D_0019B4A8;
        u8 packed = *counter;

        if ((packed & 7) != 7)
            *counter = packed + 1;
    }
    PlayMobySound(1, 0, self);
}

/* func_L12_0041EA18 is defined in L12_0041EA18-g8.c. */

/* func_L12_0041EDB8 is defined in L12_0041E3E8-split-g8.c (this unit keeps split addresses). */

/* func_L12_00420660 is defined in L12_0041E3E8-g8.c. */

/* func_L12_00420838 is defined in L12_00420838-flags-g8.c. */

/* func_L12_00420950 is defined in L12_00420950-g8.c. */

/* func_L12_00420B78 is defined in L12_00420950-g8.c. */

/* func_L12_00421110 is defined in L12_0041E3E8-g8.c. */

/* func_L12_004212C0 is defined in L12_004212C0-g8.c. */

/* func_L12_00424370 is defined in L12_00424370-g8.c. */

extern s32 *D_L12_001FEAC0[];
typedef int L12_25070Quad __attribute__((mode(TI)));

extern s32 *D_L12_001FEAC0[];
extern s32 func_002761F8(void *from, void *to, s32 mode, void *self, s32 flags);

/* Picks the first point of the object's list (D_L12_001FEAC0, chosen by the state's +0x298)
   other than the current one (+0x2B0) that it can see: both ends are raised by 0.5, and a
   zero result from the sight test means clear. Returns that point's index, or the current
   one when none is clear. */
s32 func_L12_00425070(u8 *object)
{
    f32 from[4] __attribute__((aligned(16)));
    f32 to[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(object + 0x68);
    s32 *list = D_L12_001FEAC0[*(s32 *)(state + 0x298)];
    s32 i;

    qcopy(from, object + 0x10);
    from[2] += 0.5f;
    for (i = 0; i < list[0]; i++) {
        if (i == *(s32 *)(state + 0x2B0))
            continue;
        qcopy(to, (L12_25070Quad *)list + i + 1);
        to[2] += 0.5f;
        if (CollLine(from, to, 2, object, 0) == 0)
            return i;
    }
    return *(s32 *)(state + 0x2B0);
}

/* func_L12_00425178 is defined in L12_00425178-g8.c. */

extern s32 *D_L12_001FEAC0[];
extern char D_00189EA0[];
extern f32 func_00282C48(f32);
extern f32 func_00282E80(void *, void *);

/* Looks along the path for a point at the hero's height that the hero is close to, and remembers it as the target point. */
void func_L12_00425348(u8 *self) {
    u8 *state = *(u8 **)(self + 0x68);
    s32 i = *(s32 *)(state + 0x2B4) + 1;
    u32 *entry = D_L12_001FEAC0[*(s32 *)(state + 0x298)];

    while (i < *(s32 *)entry) {
        if (FloatAbs(*(f32 *)((u8 *)entry + (i * 16 + 0x18)) - *(f32 *)((u8 *)entry + 0x18)) < 2.0f) {
            if (vec_distance_xy(gHeroPosition, (u8 *)entry + (i * 16 + 0x10)) < 6.0f)
                *(s32 *)(state + 0x2B4) = i;
        }
        i++;
    }
}

extern int func_00282948(void *);
extern s32 func_002A7820(s32, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern s32 D_L12_001B20C0 __attribute__((sda));

extern u8 D_001395DB;
extern int func_002ACBC8(void *, int);
extern void func_L12_0031E1D0(u8 *, s32, s32);

/* Waits for the hero to enter its zone, then marks the level event and moves on. */
void func_L12_004254A8(u8 *moby) {
    u8 *self = moby;
    s32 *vars;

    if (*(u8 *)(self + 0x20) == 0) {
        vars = *(s32 **)(self + 0x68);
        if (*vars != -1) {
            if (IsPointInCuboid(gHeroPosition, *vars) != 0) {
                D_001395DB = 1;
                func_L12_0031E1D0(self, 1, -1);
            }
        }
    }
}

/* func_L12_004285A8 is defined in L12_004285A8-g32.c. */

extern s32 func_002A77E0(s32);
extern s32 func_00283CF0(f32);
extern void func_L02_0031E9E8(f32 *, f32);
extern u8 *func_002BDCE8(void *, f32, f32, f32, s32, void *, f32, u32, s32);

/* Retail tests the first allocation again after its second and third calls;
 * preserve that behavior instead of changing the test to the newer pointer. */
/* Sprays three small spark particles upward from the object. */
void func_L12_004293A0(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    f32 pos[4];
    f32 velocity[4];
    u8 *spark1;
    u8 *spark2;

    qcopy(pos, self + 0x10);
    pos[2] = *(f32 *)(state + 0x7C);
    RandomPlanarOffset(velocity, 0.5f);
    velocity[2] = 0.083333336f;
    spark1 = SpawnSpinningSparkParticle(pos, 0.1f, 1.0f, 0.9f, RandomIntBelow(16), velocity, 420000.0f, 0xDF202020, 0);
    if (spark1) {
        u8 *payload = spark1 + 0x20;
        *(u16 *)(spark1 + 10) = 10;
        spark1[9] = FloatToInt(4.0f) + 0x70;
        *(s32 *)(payload + 4) = 2;
        payload[10] = 0xDF;
        payload[11] = spark1[10];
        spark1[3] = 0x44;
    }
    RandomPlanarOffset(velocity, 0.5f);
    velocity[2] = 0.083333336f;
    spark2 = SpawnSpinningSparkParticle(pos, 0.1f, 1.0f, 0.9f, RandomIntBelow(16), velocity, 420000.0f, 0xDF208080, 0);
    if (spark1) {
        u8 *payload = spark2 + 0x20;
        *(u16 *)(spark2 + 10) = 10;
        spark2[9] = FloatToInt(4.0f) + 0x70;
        *(s32 *)(payload + 4) = 2;
        payload[10] = 0xDF;
        payload[11] = spark2[10];
        spark2[3] = 0x48;
    }
    RandomPlanarOffset(velocity, 0.33333334f);
    velocity[2] = 0.083333336f;
    spark2 = SpawnSpinningSparkParticle(pos, 0.1f, 1.0f, 0.9f, RandomIntBelow(16), velocity, 420000.0f, 0xDF808080, 0);
    if (spark1) {
        u8 *payload = spark2 + 0x20;
        *(u16 *)(spark2 + 10) = 10;
        spark2[9] = FloatToInt(4.0f) + 0x70;
        *(s32 *)(payload + 4) = 2;
        payload[10] = 0xDF;
        payload[11] = spark2[10];
        spark2[3] = 0x44;
    }
}

/* func_L12_00429610 is in L12_00429610.c. */

/* func_L12_00429868 is defined in L12_0041E3E8-g8.c. */
