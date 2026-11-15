#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef float f32;


extern u8 D_L04_001395C7;
extern u8 D_L04_002CA518;

extern void func_2CC1F0(void *a0);
extern void func_30EA08(void *a0);
extern void func_33B9B0(void *a0, s32 a1, s32 a2);
extern void func_3317E8(void *a0);
extern void func_340BB8(void *a0, void *a1);
extern void func_345328(void *a0, void *a1, s32 a2, f32 f12, f32 f13);
extern void func_348708(void *a0, void *a1, s32 a2, s32 a3, f32 f12);
extern int func_34C4C8(void);
extern void *func_33E6B0(void *a0, s32 a1, s32 a2);
extern void func_40A090(int a0, u8 *a1, u8 *a2, u8 *a3, u8 *a4, u8 *a5);

/* func_L04_00456628: the sda incomplete arrays keep retail's absolute macro loads
   (lui into the destination register); D_001A7B00 is the inventory have-flag table. */
extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_001395B8[];
extern s32 D_L04_001B2008[] __attribute__((sda));
extern u8 *D_L04_001B25CC[] __attribute__((sda));
extern u8 D_00189EA0[];
extern void func_2DFC18(void *a0, void *a1, s32 a2, s32 a3);
extern s32 func_342228(void *a0, void *a1);

extern void func_0029F338(void *a0);
extern int func_002B38B8(u8 *a0);
extern void func_002A0430(u32 a0);
extern s32 func_00288AA0(u8 *a0, s32 a1);
extern s32 func_00288BE8(void *a0);
extern void func_002F5CC8(void);
extern float func_002AA3A8(float *a0, float *a1, float f12, float f13, float f14, float f15);
extern void func_002E5CF8(s32 a0, s32 a1, char *a2);

extern u8 D_0019B2E8[];
extern int D_001A79F0 __attribute__((sda));
extern int D_L04_001B24DC __attribute__((sda));
extern u8 D_L04_001BF880[];

typedef struct { u8 pad_0[0x20]; u8 flags; } FlareMoby;
typedef struct {
    FlareMoby *moby; s32 state; f32 intensity; s32 pad_c;
    s16 alpha[16]; s16 tex[16]; s32 color[16]; f32 dist[16]; f32 scale[16];
} LensFlare;
typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern LensFlare D_L04_001B9980;
extern u8 D_L04_001B9680[];
extern int D_L04_001B0D08;
extern ScreenExtent D_001A7340 __attribute__((sda));
extern f32 func_00282E48(void *, void *);
extern f32 func_00283CE0(int);
extern void func_00279BD8(f32 *, void *);
extern long long func_0027C878(int);
extern f32 func_00282C48(f32);
extern int func_00283CF0(f32);
extern void func_002FC560(int, long long);
extern void func_0027E018(int, int, int, int, int, int, int, int, long long, long long);

/* Defined in L04_00422D40-qcopy.c. */
/* Projects the flare object to the screen and draws its 14 sprites along the line
   through the screen centre, faded by distance and by how far off-centre it is
   (RAC1 draw_lens_flare). The base size is read through a pointer: retail
   rematerializes its address inside the loop. */
void func_L04_00422DA8(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    f32 scr[4], ctr[4], d[4], off[4], at[4];
    f32 dist, fade, fx, fy, half;
    int i, size, rgba, x, y;
    long long tex;
    int *baseSize;

    if (gLensFlare.state != 1 || (gLensFlare.moby->flags & 0x80)) {
        gLensFlare.state = 0;
        return;
    }
    if (gLensFlare.intensity <= 0.0f)
        return;
    dist = fast_vec_dist(D_L04_001B9680, vars + 0x30);
    ctr[0] = IntToFloat(gScreenWidth.half_width);
    ctr[1] = IntToFloat(gScreenWidth.half_height);
    baseSize = &D_L04_001B0D08;
    ProjectWorldPointToScreen(scr, vars + 0x30);
    scr[0] = (scr[0] - IntToFloat(gScreenWidth.left)) * 0.0625f;
    scr[1] = (scr[1] - IntToFloat(gScreenWidth.top)) * 0.0625f;
    d[0] = ctr[0] - scr[0];
    d[1] = ctr[1] - scr[1];
    for (i = 0; i < 14; i++) {
        tex = GetEffectTextureDescriptor(gLensFlare.tex[i] + 0x49);
        off[0] = d[0] * gLensFlare.dist[i];
        off[1] = d[1] * gLensFlare.dist[i];
        at[0] = ctr[0] + off[0];
        at[1] = ctr[1] + off[1];
        fade = dist - 5.0f;
        if (fade > 1.0f)
            fade = 1.0f;
        else if (fade < 0.0f)
            fade = 0.0f;
        fx = FloatAbs(d[0]) / ctr[0] * -5.0f + 5.5f;
        if (fx > 1.0f)
            fx = 1.0f;
        else if (fx < 0.0f)
            fx = 0.0f;
        fy = FloatAbs(d[1]) / ctr[1] * -5.0f + 5.5f;
        if (fy > 1.0f)
            fy = 1.0f;
        else if (fy < 0.0f)
            fy = 0.0f;
        fade *= fx * fy * gLensFlare.intensity;
        rgba = (FloatToInt(fade * gLensFlare.alpha[i]) << 24) | (gLensFlare.color[i] & 0xFFFFFF);
        size = FloatToInt(*baseSize * gLensFlare.scale[i]);
        VU1_addGSregister(0x42, 0x8000000048LL);
        half = size >> 1;
        x = FloatToInt(at[0] - half);
        y = FloatToInt(at[1] - half);
        DrawTexturedQuad(x, y, size, size, 0, 0, 0x40, 0x40, rgba, tex);
    }
    gLensFlare.intensity = 0.0f;
}
/* func_L04_00423258 is in L04_00423258-g8.c. */
/* Counts the object's state up, easing its timer down while it is over the
   limit, and hands the level's recorder the object's channel when it runs out. */
void func_L04_0042BF58(u8 *object) {
    u32 *vars = *(u32 **)(object + 0x68);

    if (object[0x20] == 0)
        object[0x20] = 1;
    if (object[0x20] == 2) {
        f32 height = *(f32 *)(object + 0x18);
        if (height >= 30.0f)
            *(f32 *)(object + 0x18) = height - 0.28333336114883423f;
        if (*(f32 *)(object + 0x18) < 30.0f)
            object[0x20] = 4;
    }
    if (object[0x20] == 3) {
        SpringFloatToGoal((f32 *)(object + 0x18), (f32 *)vars, 55.0f,
                      0.008333333767950535f, 0.013888888992369175f,
                      0.45000001788139343f);
        if (55.0f <= *(f32 *)(object + 0x18)) {
            PlayMobySound(0, 0, (char *)object);
            vars[1] = 0;
            object[0x20] = 1;
        }
    }
}
struct BarlowEntry { u8 bytes[256]; };
extern u8 D_00189EA0[];
extern u16 *D_L04_001FB1E0[];
extern u8 D_L04_001B1218[];
extern u8 D_L04_001B1230[];
extern int func_002ACBC8(void *, int);
extern int func_002A8508(int, int);
extern void func_0026FEB8(const char *, ...);

/* Waits for a trigger, then switches on the linked groups of objects, and switches them back off when the trigger ends. */
void func_L04_00438B50(u8 *object) {
    int *data = *(int **)(object + 0x68);
    int i;
    if (object[0x20] == 0) {
        if (IsPointInCuboid(gHeroPosition, data[4]))
            object[0x20] = 1;
    }
    if (object[0x20] == 1) {
        u16 *ids;
        u8 *entry;
        struct BarlowEntry *base;
        for (i = 0; i < 4; i++) {
            if (gMobyGroupLists_L04[*(int *)((u32)data + (i << 2))] && CountMobysInGroupNotInState(*(int *)((u32)data + (i << 2)), -1) >= 2) {
                base = (struct BarlowEntry *)gMobyPool_L04;
                ids = gMobyGroupLists_L04[*(int *)((u32)data + (i << 2))];
                do {
                    entry = base[*ids & 0x7FFF].bytes;
                    *(u16 *)(entry + 0x34) |= 0x43;
                    *(int *)(entry + 0x98) = 0;
                } while ((s16)*ids++ >= 0);
            }
        }
        STUB_printf(D_L04_001B1218);
        object[0x20] = 2;
    }
    if (object[0x20] == 2) {
        if (!IsPointInCuboid(gHeroPosition, data[4]))
            object[0x20] = 3;
    }
    if (object[0x20] == 3) {
        u16 *ids;
        u8 *entry;
        struct BarlowEntry *base;
        for (i = 0; i < 4; i++) {
            if (gMobyGroupLists_L04[*(int *)((u32)data + (i << 2))] && CountMobysInGroupNotInState(*(int *)((u32)data + (i << 2)), -1) >= 2) {
                base = (struct BarlowEntry *)gMobyPool_L04;
                ids = gMobyGroupLists_L04[*(int *)((u32)data + (i << 2))];
                do {
                    entry = base[*ids & 0x7FFF].bytes;
                    *(u16 *)(entry + 0x34) &= ~0x41;
                    *(int *)(entry + 0x98) = *(int *)(*(u8 **)(entry + 0x24) + 0x10);
                    *(u16 *)(entry + 0x34) &= ~2;
                } while ((s16)*ids++ >= 0);
            }
        }
        STUB_printf(D_L04_001B1230);
        MarkMobySpawned(object);
    }
}

/* func_L04_00439870 is defined in L04_00422A00-g8.c (this unit's -G8 profile gives the
   retail's address forms). */
extern void func_40A090(int a0, u8 *a1, u8 *a2, u8 *a3, u8 *a4, u8 *a5);

extern u8 D_L04_001B12B0[] __attribute__((sda));
extern u8 D_L04_001B12E8[] __attribute__((sda));
extern u8 D_L04_001B1300[] __attribute__((sda));
extern u8 D_L04_001B1330[] __attribute__((sda));
extern u8 D_L04_001B1348[] __attribute__((sda));
extern u8 D_L04_001B3280[] __attribute__((sda));
extern u8 D_L04_001B32B0[] __attribute__((sda));
extern u8 D_L04_001B32E0[] __attribute__((sda));
extern u8 D_L04_001B3300[] __attribute__((sda));
extern u8 D_L04_001B3320[] __attribute__((sda));
extern u8 D_L04_001B3330[] __attribute__((sda));
extern u8 D_L04_001B3360[] __attribute__((sda));
extern u8 D_L04_001B3378[] __attribute__((sda));
extern u8 D_L04_001B33A0[] __attribute__((sda));
extern u8 D_L04_001B33B0[] __attribute__((sda));
extern u8 D_L04_001B33B8[] __attribute__((sda));
extern u8 D_L04_001B33D8[] __attribute__((sda));
extern u8 D_L04_001B33E8[] __attribute__((sda));
extern u8 D_L04_001B3418[] __attribute__((sda));
extern u8 D_L04_001B3430[] __attribute__((sda));
extern u8 D_L04_001B3458[] __attribute__((sda));
extern u8 D_L04_001B3468[] __attribute__((sda));
extern u8 D_L04_001B3470[] __attribute__((sda));
extern u8 D_L04_001B3474[] __attribute__((sda));
extern u8 D_L04_001B3478[] __attribute__((sda));
extern u8 D_L04_001B347C[] __attribute__((sda));
extern u8 D_L04_001B3480[] __attribute__((sda));
extern u8 D_L04_001B3484[] __attribute__((sda));
extern u8 D_L04_001B3488[] __attribute__((sda));
extern u8 D_L04_0026D370[];
extern u8 D_L04_0026D3E0[];
extern u8 D_L04_0026D490[];
extern u8 D_L04_0026D4F0[];
extern u8 D_L04_002CA3E0[];
extern u8 D_L04_002CA438[];

extern void func_L04_0040A090(int, void *, void *, void *, void *, void *);

/* Sets up the seven animation walk paths used by the Barlow cutscene. */
void func_L04_0043ABE0(void) {
    MeasurePathSegments(7, D_L04_001B12B0, D_L04_0026D370, D_L04_001B3300, D_L04_001B33B8, D_L04_001B3470);
    MeasurePathSegments(3, D_L04_001B12E8, D_L04_001B3280, D_L04_001B3320, D_L04_001B33D8, D_L04_001B3474);
    {
        u8 *data = D_L04_002CA3E0;
        MeasurePathSegments(11, data, D_L04_0026D3E0, D_L04_001B3330, D_L04_001B33E8, D_L04_001B3478);
    }
    MeasurePathSegments(6, D_L04_001B1300, D_L04_0026D490, D_L04_001B3360, D_L04_001B3418, D_L04_001B347C);
    MeasurePathSegments(9, D_L04_002CA438, D_L04_0026D4F0, D_L04_001B3378, D_L04_001B3430, D_L04_001B3480);
    MeasurePathSegments(3, D_L04_001B1330, D_L04_001B32B0, D_L04_001B33A0, D_L04_001B3458, D_L04_001B3484);
    MeasurePathSegments(2, D_L04_001B1348, D_L04_001B32E0, D_L04_001B33B0, D_L04_001B3468, D_L04_001B3488);
}



/* On its first update waits for a go signal, then sets a level flag and moves to the next state. */
void func_L04_00441178(u8 *object) {
    if (object[0x20] != 0)
        return;
    if (func_34C4C8() != 0) {
        func_2CC1F0(&D_L04_002CA518);
        D_L04_001395C7 = 1;
        func_33B9B0(object, 1, -1);
    }
}
/* func_L04_0044AAC8 is defined in L04_00422A00-g8.c (it reads small data through $gp). */
/* func_L04_0044BC90 is defined in L04_0044BC90-g8.c. */

/* Defined in L04_0044BC90-g8.c. */
/* func_L04_0044C598 is in L04_0044C598-g8.c. */
/* func_L04_0044D0C0 is in L04_0044D0C0-g8.c. */
/* func_L04_0044D428 is in L04_0044D428-g8.c. */
extern void func_30E9D8(void *a0);
extern f32 func_30F468(f32 a, f32 b);
extern f32 func_30FE88(f32 a, f32 b);
extern f32 func_30FE40(f32 a, f32 b);

/* Counts the object up, turns it towards the hero and keeps the turn inside
   a sixty degree limit, then hands the result to the frame helpers. */
void func_L04_0044D6A0(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *target;
    f32 angle, negLimit, deltaX, deltaY, limit;

    func_340BB8(object, vars + 0x50);
    func_30E9D8(vars + 0x2FC);
    func_30EA08(vars + 0x302);
    if (*(u16 *)(object + 0x96) <= 0xFFFE)
        *(u16 *)(object + 0x96) = *(u16 *)(object + 0x96) + 1;
    if (object[0x95] == 2) {
        target = *(u8 **)(vars + 0x250);
        deltaX = *(f32 *)(target + 0x10) - *(f32 *)(object + 0x10);
        deltaY = *(f32 *)(target + 0x14) - *(f32 *)(object + 0x14);
        limit = 1.047197699546814f;
        angle = func_30F468(deltaX, deltaY);
        angle = func_30FE88(angle, *(f32 *)(object + 0xF8));
        if (limit < angle) {
            angle = limit;
        } else {
            negLimit = -limit;
            if (angle < negLimit)
                angle = negLimit;
        }
        if (*(u16 *)(object + 0x34) & 0x8000)
            angle = -angle;
        angle = func_30FE40(angle, *(f32 *)(vars + 0x2C8));
        *(f32 *)(vars + 0x2C8) = angle;
        if (limit < angle) {
            *(f32 *)(vars + 0x2C8) = limit;
        } else {
            negLimit = -limit;
            if (angle < negLimit)
                *(f32 *)(vars + 0x2C8) = negLimit;
        }
    }
    func_348708(object, vars + 0x260, 1, 1, 2.5f);
}
/* Defined in L04_0044D860-g8.c. */

/* subtracts the sub-structure's field from the owner's timer and reports it */
int func_L04_0044DAC8(char *object) {
    char *vars = *(char **)(object + 0x68);
    char *part = func_33E6B0(*(char **)(vars + 0x290), 0x10000, 0);

    if (part != 0) {
        *(f32 *)(vars + 0x20) -= *(f32 *)(part + 0x2C);
        return 1;
    }
    return 0;
}

/* Frees up to three linked child objects and clears the links to them. */
void func_L04_00450268(char *object) {
    char *vars = *(char **)(object + 0x68);
    void *child;

    child = *(void **)(vars + 0x2AC);
    if (child != 0) {
        func_3317E8(child);
        *(void **)(vars + 0x2AC) = 0;
    }
    child = *(void **)(vars + 0x288);
    if (child != 0) {
        func_3317E8(child);
        *(void **)(vars + 0x288) = 0;
    }
    child = *(void **)(vars + 0x290);
    if (child != 0) {
        func_3317E8(child);
        *(void **)(vars + 0x290) = 0;
    }
}
/* Defined in L04_004502D0-g8.c. */
extern float func_00282DF0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_L02_0032E998(void *, void *, void *, void *, int, void *, void *, f32, f32);
extern void func_002AAA00(void *, f32, f32, f32, f32, void *, int);
extern f32 func_00283C80(f32, f32);
extern void func_002AA548(void *, void *, f32, f32, f32, f32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7EA0(void *, void *, void *, f32, f32, f32, f32, int);

/* Walks the object toward a target while turning to face it. Returns 1 when it has arrived and finished turning, or when it has been stuck for too long. */
int func_L04_00450D50(u8 *object, void *target, f32 desiredHeading, f32 speed, f32 stopDistance, f32 margin) {
    f32 delta[4], displacement[4], destination[4];
    f32 angle, frameSpeed = 0.0f;
    u8 *data = *(u8 **)(object + 0x68);
    int done = 0;
    f32 distance, acceleration;
    FastVecSub(delta, target, object + 0x10);
    delta[2] = 0.0f;
    distance = FastVecLength(delta);
    acceleration = speed * 0.0008333333535119891f;
    if (stopDistance < distance) {
        int collision = *(int *)(data + 0x540);
        angle = 0.0f;
        ComputeRegionRouteHeading(object + 0x10, target, &angle, data + 0x340, collision, data + 0x550, data + 0x554, margin, 0.4f);
        ApproachTargetWithDirectionMode(object + 0xF8, angle, 0.006981317885220051f, 0.0034906589426100254f, 0.20943954586982727f, data + 0x28C, 0);
        if (FastDiffRots(*(f32 *)(object + 0xF8), angle) < 0.523598849773407f) {
            StepValueTowardTarget(&frameSpeed, data + 0x558, distance, acceleration, acceleration, speed * 0.01666666753590107f);
        } else {
            *(f32 *)(data + 0x558) = 0.0f;
        }
    } else {
        ApproachTargetWithDirectionMode(object + 0xF8, desiredHeading, 0.006981317885220051f, 0.2f, 0.20943954586982727f, data + 0x28C, 0);
        ApproachValue((f32 *)(data + 0x558), 0.0f, acceleration);
        if (*(f32 *)(data + 0x558) == 0.0f && FastDiffRots(*(f32 *)(object + 0xF8), desiredHeading) < 0.0872664749622345f) {
            *(f32 *)(data + 0x28C) = 0.0f;
            done = 1;
        }
    }
    vec_scale_to_length(displacement, object + 0xC0, *(f32 *)(data + 0x558));
    FastVecAdd(destination, displacement, object + 0x10);
    if (!MoveOverGround(object, object + 0x10, destination, 0.75f, 0.75f, 0.4f, 0.523598849773407f, 0))
        *(int *)(data + 0x55C) += 1;
    if (*(int *)(data + 0x55C) >= 30) {
        *(int *)(data + 0x55C) = 0;
        done = 1;
    }
    return done;
}


/* Counts down the object's timers, ages the object by one tick and updates its animation blending. */
void func_L04_00451018(char *object) {
    char *vars = *(char **)(object + 0x68);
    u16 age;

    func_340BB8(object, vars + 0x50);
    func_30EA08(vars + 0x270);
    func_30EA08(vars + 0x272);
    func_30EA08(vars + 0x26);
    age = *(u16 *)(object + 0x96);
    if (age <= 0xFFFE) {
        *(u16 *)(object + 0x96) = age + 1;
    }
    vars += 0x2C0;
    func_345328(object, vars, 4, 0.03f, 0.3f);
    func_348708(object, vars, 4, 1, 2.5f);
}
/* Starts the object's encounter state and, once it is running, hands the level's
   camera table the object's slot and asks the frame helpers to update it. */
void func_L04_00455520(u8 *object) {
    u32 *links = *(u32 **)(object + 0x68);

    if (object[0x20] == 0) {
        if (D_0019B2E8[object[0xB0] + gCurrentMapIndex * 16] & 0x80) {
            MarkMobySpawned(object);
            return;
        }
        object[0x20] = 1;
    }
    if (object[0x20] == 1) {
        if (IsThirdPendingFlagSet((u8 *)(gMobyPool_L04 + (*links << 8)))) {
            MarkTableEntryFlagged(object[0xB0]);
            PushRequestQueue(D_L04_001BF880, 0x38);
            LaunchQueuedRequest(D_L04_001BF880);
            SetSlowdownFactorAndLowFpsFade();
            MarkMobySpawned(object);
        }
    }
}
/* On the first update: with inventory item 0x1F owned, the byte at D_001395B8+0x12
   clear and the level counter D_L04_001B2008 below 5, passes the +0x30/+0x70 vectors
   of the level record the object names to func_2DFC18 (RAC1's Hero_ResetToPosition
   call shape); with the item owned and that byte set, hands the object to
   func_3317E8. Later, once func_342228 accepts the hero position (D_00189EA0) for
   the object's volume and the item is still owned, sets the byte and does the same. */
void func_L04_00456628(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *record;
    if (object[0x20] == 0) {
        if (D_001A7B00[0x1F] != 0 && D_001395B8[0x12] == 0 && D_L04_001B2008[0] < 5) {
            record = D_L04_001B25CC[0] + (*(s32 *)(vars + 4) << 7);
            func_2DFC18(record + 0x30, record + 0x70, 0, 1);
        } else if (D_001A7B00[0x1F] != 0 && D_001395B8[0x12] != 0) {
            func_3317E8(object);
            return;
        } else {
            object[0x20] = 1;
        }
        object[0x30] = 0xFF;
    }
    if (object[0x20] == 1) {
        if (func_342228(gHeroPosition, *(void **)vars) != 0) {
            if (D_001A7B00[0x1F] != 0) {
                D_001395B8[0x12] = 1;
                func_3317E8(object);
            }
        }
    }
}
