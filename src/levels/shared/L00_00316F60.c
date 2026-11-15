#include "include_asm.h"
#include "names.h"

#define RAC2_T_V4_F36D8A248
#define RAC2_T_M4_F36D8A248
#define RAC2_T_SRC_F66766F2B
#define RAC2_T_LIST_F66766F2B

typedef int s32;

typedef float f32;

typedef unsigned char u8;

typedef struct {
    f32 x, y, z, w;
} V4_F36d8a248;

typedef struct {
    V4_F36d8a248 r[4];
} M4_F36d8a248;

extern void func_00283410_3(M4_F36d8a248 *, V4_F36d8a248 *);

#ifndef RAC2_T_V4TI_F36D8A248
#define RAC2_T_V4TI_F36D8A248
typedef int V4TI_F36d8a248 __attribute__((mode(TI)));
#endif

extern void func_00283788_2(M4_F36d8a248 *, M4_F36d8a248 *, V4_F36d8a248 *);

extern void func_002AB6D8_2(M4_F36d8a248 *, V4_F36d8a248 *);

typedef int BatchA_A06_s32;

typedef short BatchA_A06_BatchAs16;

typedef struct {
    char pad0[35];        /* 0   */
    unsigned char f35;    /* 35  */
    char pad36[8];        /* 36  */
    float f44;            /* 44  */
    unsigned char f48;    /* 48  */
    unsigned char f49;    /* 49  */
    unsigned short f50;   /* 50  */
    unsigned short f52;   /* 52  */
    char pad54[2];        /* 54  */
    long long f56;        /* 56  */
    char pad64[34];       /* 64  */
    unsigned char f98;    /* 98  */
    char pad99[21];       /* 99  */
    int f120;             /* 120 */
    unsigned short f124;  /* 124 */
    char pad126[26];      /* 126 */
    int f152;             /* 152 */
    char pad156[14];      /* 156 */
    short f170;           /* 170 */
} Src_F66766f2b;

typedef struct {
    char pad0[256];       /* 0   */
    int a[4];             /* 256 */
    int b[4];             /* 272 */
    Src_F66766f2b *c[4];            /* 288 */
    float d[4];           /* 304 */
    int pad320;           /* 320 */
    Src_F66766f2b *src;             /* 324 */
    int count;            /* 328 */
} List_F66766f2b;

typedef struct Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner {
    unsigned char prefix_00[0x120];
    void *slots_120[10];
    int count_148;
    int active_14c;
} Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner;

typedef unsigned int u32;

typedef struct {
    u8 prefix[0x40];
    void *payload;
    u32 unused44;
    short key;
    u8 marker;
    u8 unused4b;
    u8 selector;
    u8 tail[3];
} GornRecordWrite64;

extern float func_00283BE0_4(float x, float y);

extern float func_00283180_7(float x);

extern float func_00283B98_7(float x, float y);

extern float func_00283180_5(float x);

extern float func_00283BE0_2(float a, float b);

extern float func_00283B98_5(float a, float b);

extern void func_00283410_3(M4_F36d8a248 *, V4_F36d8a248 *);

extern void func_00283788_2(M4_F36d8a248 *, M4_F36d8a248 *, V4_F36d8a248 *);

extern void func_002AB6D8_2(M4_F36d8a248 *, V4_F36d8a248 *);

extern Src_F66766f2b *func_0029EFD0(short);

extern void func_0029F338_3(void *object);

extern u8 D_L00_00268E20;

extern s32 D_L00_001A902C __attribute__((sda));

extern f32 func_00283198_4(f32);

extern f32 func_00283B98_4(f32, f32);

extern void func_00283D38_2(s32, s32, f32);

extern void func_002A93B0(void);

extern int func_00283D38(int from, int to, float fraction);

extern int func_002EF250(float);

extern int func_002ABB78(char *);

extern void func_002AF000(float *, float, float, float);

extern void func_00282CC0(void *, void *, void *);

extern int D_001A7350 __attribute__((sda));

extern int D_001A7354 __attribute__((sda));

extern void func_00279BD8(void *, void *);

extern int func_00283CF0(f32);

extern u8 D_00189E20[];

extern void func_00283098(char *, char *, char *);

extern void func_00282D30(void *, void *, float);

extern void func_002AFFD8(char *, char *, int);

extern int D_001A8FF0;

extern void func_00282C98(void *);

extern void func_L00_003252C8_1(u8 *) __asm__("func_L00_003252C8");

extern void func_002B00D8(void *, float *, float *, float);

extern void func_002B0408(void *, void *, void *);

extern void func_0029CC50(void);

extern unsigned char D_001395B8[];

extern int func_L00_003269F0(void);

#ifndef RAC2_T_V4_F36D8A248
#endif

#ifndef RAC2_T_M4_F36D8A248
#endif

#ifndef RAC2_T_SRC_F66766F2B
#endif

#ifndef RAC2_T_LIST_F66766F2B
#endif

/* Measured partial layouts; original type and game roles are unknown. */
extern void func_00282CF0(void *, void *, void *);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282D30(void *, void *, float);

extern float func_00282C48(float);

ASM_FUNC("asm/levels", func_L00_00316F60);

/* computes a scalar complement-power curve by repeated multiplication */
f32 func_L00_0031A6C8(f32 amount, s32 steps) {
    f32 remaining = 1.0f - amount;
    f32 power = remaining;
    for (; steps > 1; --steps)
        power = power * remaining;
    return 1.0f - power;
}

/* func_L00_0031AA28 is defined in L00_0031AA28-curve.c. */

/* Blends a value toward a target: helper(second,first) halved, scaled by (1 - helper(third*pi)); the first argument and that product go to a two-float helper whose float result is returned. */
float func_L00_0031ABE0(float from, float to, float phase)
{
    float diff;
    float wave;

    diff = func_00283BE0_4(to, from);
    wave = func_00283180_7(phase * 3.1415927f);
    diff = diff * 0.5f;
    return func_00283B98_7(from, diff * (1.0f - wave));
}

/* Blends between two vectors: at a phase of zero the first vector is copied, at one the
   second, and in between a sine-shaped weight scales the difference between them. */
void func_L00_0031AC60(V4TI_F36d8a248 *result, V4TI_F36d8a248 *from, V4TI_F36d8a248 *to, float phase)
{
    char delta[16];
    float weight;

    if (phase == 0.0f) {
        *(volatile V4TI_F36d8a248 *)result = *(V4TI_F36d8a248 *)from;
    } else if (phase == 1.0f) {
        *(volatile V4TI_F36d8a248 *)result = *(V4TI_F36d8a248 *)to;
    } else {
        weight = (1.0f - func_00283180_5(phase * 3.1415927f)) * 0.5f;
        FastVecSub(delta, to, from);
        FastVecScale(delta, delta, weight);
        FastVecAdd(result, from, delta);
    }
}

/* converts a normalised phase to radians, derives a blend factor of half the complement of a phase helper's result, and applies it to a two-argument helper over three consecutive float components written back over the first vector. */
void func_L00_0031AD40(float *result, float *from, float *to, float phase)
{
    float weight;

    weight = (1.0f - func_00283180_5(phase * 3.1415927f)) * 0.5f;
    result[0] = func_00283B98_5(from[0], func_00283BE0_2(to[0], from[0]) * weight);
    result[1] = func_00283B98_5(from[1], func_00283BE0_2(to[1], from[1]) * weight);
    result[2] = func_00283B98_5(from[2], func_00283BE0_2(to[2], from[2]) * weight);
}




/* func_L00_0031B9F8 is matched in L00_0031B9F8.c (built with -g). */


/* func_L00_0031BDC0 is defined in L00_0031BDC0.c. */

/* True only when the pending object exists and its inner flag is set. */
s32 func_L00_0031BE88(char *object) {
    if (*(s32 **)(object + 0x98) != 0 && *(s32 *)(*(char **)(object + 0x98) + 8) != 0)
        return 1;
    return 0;
}


/* func_L00_0031C3D0 is built in its own unit. */

/* Calls the engine routine that resets the shared effect state. */
void func_L00_0031C978(void)
{
    UpdateMobyGroundCheck();
}

/* Blends between two integer values by a fraction. */
int func_L00_0031C998(int from, int to, float fraction)
{
    return FastTweenColor(from, to, fraction);
}




/* Moves a whole number part of the way toward another one. */
int func_L00_0031D620(int from, int to, float fraction) {
    return from + func_002EF250((float)(to - from) * fraction);
}

/* func_L00_0031D670 is defined in L00_0031D670.c. */


/* Blends three components of a vector into a second one: for every component that is
   negative the two vectors are mixed through a helper, scaled by the angle between them
   and added back into the second vector. */
void func_L00_0031EC88(V4TI_F36d8a248 *basis, V4TI_F36d8a248 *vec)
{
    V4_F36d8a248 saved;
    V4_F36d8a248 push;
    V4_F36d8a248 *vecPtr = vec;
    V4_F36d8a248 *savedPtr = &saved;
    V4_F36d8a248 *pushPtr = &push;
    float *savedComp = (float *)&saved;
    float *vecComp = (float *)vec;
    float *pushComp = (float *)&push;
    int axis;

    *(V4TI_F36d8a248 *)&saved = *(V4TI_F36d8a248 *)basis;
    for (axis = 0; axis < 3; axis++) {
        if (*vecComp < 0.0f) {
            FastVecSub(pushPtr, vecPtr, savedPtr);
            FastVecScale(pushPtr, pushPtr, FloatAbs((*savedComp - 0.1f) / *pushComp));
            FastVecAdd(vecPtr, savedPtr, pushPtr);
        }
        vecComp++;
        pushComp++;
        savedComp++;
    }
}


/* Tells if an object is missing or has the class 502 identity; objects that fail the engine check count as true. */
int func_L00_0031F220(const unsigned char *moby) {
    if (moby == 0)
        return 0;
    if (IsMobyInSpecialClassRange((char *)moby) != 0)
        return *(const signed short *)(moby + 0xAA) == 0x1F6 /* moby class 502 */;
    return 1;
}

/* One fixed ordinary scalar query. Signed halfword width, offset and
   equality constant are measured; no original class or field-name claim. */
/* Tells if an object is an Ammo pickup. */
int func_L00_0031F2B0(const unsigned char *moby) {
    return *(const signed short *)(moby + 0xAA) == 0x0CDB /* Ammo */;
}

/* func_L00_003200F8 is defined in L00_003200F8.c. */


/* func_L00_003206B8 only matches when this unit is built -G8 (its object table load comes
   out of $gp there), so its body lives in L00_00316F60-g8.c. */


/* Defined in L00_00320B70.c. */

/* func_L00_00321878 is defined in L00_00321878-g8.c. */


/* builds two 64-byte blocks from a 3-float vector and from a vector inside the caller object, combines them, then scales one block again from the same source vector */
void func_L00_00322A18(u8 *object, f32 x, f32 y, f32 z) {
    V4_F36d8a248 offset;
    M4_F36d8a248 offsetMatrix;
    M4_F36d8a248 objectMatrix;
    offset.x = x;
    offset.y = y;
    offset.z = z;
    func_00283410_3(&offsetMatrix, &offset);
    func_00283410_3(&objectMatrix, (V4_F36d8a248 *)(object + 240));
    func_00283788_2(&objectMatrix, &objectMatrix, &offsetMatrix);
    func_002AB6D8_2(&objectMatrix, (V4_F36d8a248 *)(object + 240));
}

/* A06-inline-init-40 freshly exact-verified under family reservation */
/* Sets up an object's pending slot once, storing a target and clearing its counters. */
void func_L00_00322A98(void *target, char *object){
    if (*(BatchA_A06_s32 *)(object + 0x14C) == 0) {
        *(void **)(object + 0x144) = target;
        *(BatchA_A06_s32 *)(object + 0x14C) = 1;
        *(BatchA_A06_BatchAs16 *)(object + 0x142) = 0;
        *(BatchA_A06_s32 *)(object + 0x148) = 0;
        *(BatchA_A06_BatchAs16 *)(object + 0x140) = 0;
    }
}

/* Appends a record to a fixed four-entry table: aborts when the table is full or an index argument is out of range, copies selected fields from one linked record into a helper-allocated record, then stores the three inputs and that record into four parallel tables and bumps the count. */
void func_L00_00322AC0(List_F66766f2b *list, int color, int slot, float weight)
{
    Src_F66766f2b *newItem;
    short itemKind;

    if (list->count == 4)
        return;
    if (slot >= 9)
        return;

    newItem = CreateMoby(list->src->f170);
    if (newItem == 0)
        return;

    itemKind = newItem->f170;
    newItem->f124 = list->src->f124;
    newItem->f50 = list->src->f50;
    newItem->f56 = list->src->f56;
    newItem->f44 = list->src->f44;
    newItem->f120 = list->src->f120;
    newItem->f49 = 1;
    newItem->f52 = 2058;
    newItem->f48 = 0;
    newItem->f152 = 0;
    if (itemKind == 0)
        newItem->f98 = 0;
    newItem->f35 = color;

    list->b[list->count] = slot;
    list->a[list->count] = color;
    list->d[list->count] = weight;
    list->c[list->count] = newItem;
    list->count = list->count + 1;
}

/* func_L00_00322428 is defined in L00_00322428-g8.c. */

/* func_L00_00322BE0 is defined in L00_00322BE0.c. */

/* When active field 0x14C is nonzero, iterate the slots beginning at 0x120 using count 0x148, call the bound helper for each non-null slot, clear each processed slot, and reset the active field. Original game role is unknown. */
void func_L00_00322EC8(Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *owner)
{
    int i;
    if (owner->active_14c != 0) {
        for (i = 0; i < owner->count_148; ++i) {
            if (owner->slots_120[i] != 0) {
                func_0029F338_3(owner->slots_120[i]);
                owner->slots_120[i] = 0;
            }
        }
        owner->active_14c = 0;
    }
}


/* func_L00_00323448 is defined in L00_00323448-g8.c. */

/* func_L00_00323958 is defined in L00_00316F60-g8.c. */

/* Write a payload pointer in the first selector/key record before the list terminator */
void func_L00_00323E48(GornRecordWrite64 *entry, u32 wantedSelector,
                            int wantedKey, void *newPayload)
{
    if (entry->marker != 0) {
        u8 markerByte;
        do {
            if (entry->selector == wantedSelector && entry->key == wantedKey) {
                entry->payload = newPayload;
                return;
            }
            markerByte = entry->marker;
            ++entry;
        } while (markerByte != 1);
    }
}

/* Builds a vector from three numbers and adds another vector to it. */
void func_L00_00323F28(void *result, void *other, float x, float y, float z) {
    float vec[4];
    BuildSphericalOffset(vec, x, y, z);
    FastVecAdd(result, vec, other);
}

/* Turns a position into a grid cell coordinate pair. */
void func_L00_00323F70(void *worldPos, int *outX, int *outY) {
    u8 screenPos[8];

    ProjectWorldPointToScreen(screenPos, worldPos);
    *outX = FloatToInt(((*(f32 *)screenPos) - (f32)gScreenOffsetX) * 0.0625f);
    *outY = FloatToInt(((*(f32 *)(screenPos + 4)) - (f32)gScreenOffsetY) * 0.0625f);
}

/* func_L00_00324120 (three-way state test) is a near miss:
   nonmatching/levels/func_L00_00324120.c */
/* Tells if the given id is the current selected one in the player state. */
s32 func_L00_00324120(s32 id) {
    u8 *state = gHeroState;
    if (*(s32 *)(state + 0x229C) == 3 || *(s32 *)(state + 0x2294) == 0x1B) {
        if (*(s32 *)(state + 0x588) != id)
            goto Lzero;
        return 1;
    }
    if (*(short *)(state + 0x34E) != 0)
        goto Lzero;
    if (*(s32 *)(state + 0x33C) == id) {
        return 1;
    }
Lzero:
    return 0;
}


extern u8 *func_L00_00324D18(void *, void *, f32, f32, f32, f32, f32, int);

/* Picks a point in front of the player and starts a helper effect there. */
u8 *func_L00_00324E48(void *target, int flags, f32 p1, f32 p2, f32 p3, f32 p4, f32 p5) {
    u8 *hero = gHeroState;
    float point[4];
    FastVecScale(point, *(u8 **)(hero + 0x2290) + 0xE0, 0.75f);
    FastVecAdd(point, hero + 0x80, point);
    return GetOrFindTargetMoby(point, target, p1, p2, p3, p4, p5, flags);
}


/* Turns a local offset into a world position for an object. */
void func_L00_00324F18(char *object, char *out, float x, float y, float z) {
    *(float *)(out + 0) = x;
    *(float *)(out + 4) = y;
    *(float *)(out + 8) = z;
    matrix_mul_vec3(out, out, object + 0xC0);
    FastVecScale(out, out, *(float *)(object + 0x2C));
    FastVecAdd(out, out, object + 0x10);
}

/* Passes an object's position area on to an engine routine. */
void func_L00_003252A8(void *object, void *output, int mode)
{
    ComputeViewDirection((char *)object + 0x10, (char *)output, mode);
}

/* func_L00_003252C8 (flag-routed handler, reads the caller's a1) is a near miss:
   nonmatching/levels/func_L00_003252C8.c */
/* func_L00_003252C8 is matched in L00_003252C8.c (built with -mno-split-addresses). */

/* Calls the flag-routed handler on an object's inner data. */
void func_L00_00325300(u8 *object)
{
    func_L00_003252C8_1(object + 0x10);
}

/* Mixes two things on an object's inner data by a given amount. */
void func_L00_003253A0(u8 *object, float *first, float *second, float amount)
{
    OffsetPositionAlongGravity(object + 0x10, first, second, amount);
}


/* Flips a vector around and passes it on with another one. */
void func_L00_00325600(void *dest, void *vec, void *other) {
    int negated[4];
    FastVecScale(negated, vec, -1.0f);
    AlignRotationToDirection(dest, negated, other);
}




/* stores a wrapped angle back into the caller field and forwards its [0,1] rescaled value (x*0.5+0.5) with two pointer arguments to a second callee */
int func_L00_00325FC8(f32 *angle, s32 argA, s32 argB, f32 delta) {
    f32 sineValue = func_00283198_4(angle[0]);
    f32 ratio = sineValue * 0.5f + 0.5f;
    angle[0] = func_00283B98_4(angle[0], delta);
    func_00283D38_2(argA, argB, ratio);
}

/* Updates an angle and stores the result in an object. */
void func_L00_00326048(char *object, f32 *angle, s32 argA, s32 argB, f32 delta) {
    *(int *)(object + 0x78) = UpdateAngleAndBlend(angle, argA, argB, delta);
}




/* Calls the engine routine that resets effects. */
void func_L00_00326200(void)
{
    func_0029CC50();
}

/* func_L00_003263D0 is in L00_003263D0.c: its qcopy needs common.h. */

/* Defined in L00_00326620.c. */

/* func_L00_003266D8 is built in its own unit. */

/* Adds to a counter if enough room is left, and tells if it worked. */
int func_L00_00326950(int amount) {
    unsigned char *counters;

    if (func_L00_003269F0() < amount)
        return 0;
    counters = D_001395B8;
    counters[0x90] = counters[0x90] + amount;
    return 1;
}

/* One fixed ordinary scalar source hypothesis. Byte offset and mask are
   measured; no original object/class/field name or allocation claim. The
   observed callers pass scalar one and ignore the result. */
void func_L00_003294F0(unsigned char *object, int enable) {
    if (enable)
        object[0xBE] |= 4;
    else
        object[0xBE] &= 0xFB;
}

/* func_L00_00329520 is in L00_00329520.c. */


/* func_L00_00329E90 is in L00_00329E90.c: its counter is declared differently there. */

/* func_L00_00329FF0 is defined in L00_00329FF0-g.c. */



/* Clears every entry in a big table of slots so each one is empty. */
void func_L00_0032A0E8(void) {
    u8 *slot = &D_L00_00268E20;
    u8 *limit = slot + 0x14860;

    D_L00_001A902C = 0;
    do {
        *(s32 *)(slot + 4) = -1;
        *(s32 *)slot = 0;
        slot += 0xA430;
    } while ((s32)slot < (s32)limit);
}

/* func_L00_0032A1A8 is matched in L00_0032A1A8.c (built with -frac2-qcopy). */

/* func_L00_0032A258 is matched in L00_0032A258-g8.c (built with -G8). */

/* func_L00_0032A530 is matched in L00_0032A530-g.c (built with -g; its qcopy needs common.h). */
