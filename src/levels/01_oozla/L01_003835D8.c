#include "include_asm.h"
#include "common.h"

typedef unsigned int TI128 __attribute__((mode(TI)));

extern void func_0029F338(void *);

extern void func_0029FCC0(void *, int, void *);

extern void *func_002A9640(void *, int, int);

extern void func_002A8E20(void *, void *);

typedef struct {
    TI128 f00;
    u32 f10;
    u32 f14;
    u8 f18;
    u8 f19;
    u16 f1A;
    f32 f1C;
    u32 f20;
} L01_003A6350_Params;

typedef struct {
    u8 pad[0x1FB0];
    f32 f1FB0;
    f32 f1FB4;
} D00189E20_View;

extern D00189E20_View D_00189E20;

extern void func_00282948();

/* func_L01_003835D8 is defined in L01_003835D8-match.c. */

/* func_L01_003839F0 is defined in L01_003839F0.c. */

/* func_L01_003A5BB8 is defined in L01_003835D8-g8.c. */

/* func_L01_003A6028 is defined in L01_003A6028-g8.c. */

/* func_L01_003A6280 is defined in L01_003A6280-helper-g8.c. */

/* Small helper object that follows its parent. If something hits it, it passes the hit on to the parent. It removes itself when the parent is gone. */
void func_L01_003A6350(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *parent = *(u8 **)(vars + 0x50);
    L01_003A6350_Params hit;
    void *result;

    if (parent == 0 || *(s16 *)(parent + 0xAA) != *(s32 *)(vars + 0x54) ||
        parent[0x20] == 0xFE || parent[0x20] == 0xFD) {
        MarkMobySpawned(object);
        return;
    }
    {
        if (*(s32 *)(vars + 0x5C) != -1) {
            TransformMobyJointToWorld(*(u32 *)(vars + 0x50), *(s32 *)(vars + 0x5C), object + 0x10);
        }
        result = FindOwnedEffectSlot(object, -1, 0);
        if (result != 0) {
            qcopy(&hit.f00, (u8 *)result + 0x10);
            hit.f10 = *(u32 *)((u8 *)result + 0x20);
            hit.f14 = *(u32 *)((u8 *)result + 0x24);
            hit.f18 = ((u8 *)result)[0x28];
            hit.f19 = ((u8 *)result)[0x29];
            hit.f1A = *(u16 *)((u8 *)result + 0x2A);
            hit.f1C = *(f32 *)((u8 *)result + 0x2C) * *(f32 *)(vars + 0x58);
            hit.f20 = *(u32 *)((u8 *)result + 0x30);
            QueueMobyImpact(*(u32 *)(vars + 0x50), &hit);
        }
        object[0xA8] = 0xFF;
    }
}

/* Reads how far the player is tilting and gives two numbers, each kept between -1 and 1. */
void func_L01_003A6448(float *outX, float *outY) {
    *outX = -gHeroState.f1FB0;
    *outY = -gHeroState.f1FB4;
    if (*outX > 1.0f)
        *outX = 1.0f;
    else if (*outX < -1.0f)
        *outX = -1.0f;
    if (*outY > 1.0f)
        *outY = 1.0f;
    else if (*outY < -1.0f)
        *outY = -1.0f;
}



/* func_L01_003B1F08 lives in L01_003B1F08.c. */

/* func_L01_003B4200 lives in L01_003B4200.c: its grouped copies and
   global-address scheduling need a per-file profile. */

/* func_L01_003B4480 lives in L01_003B4480.c: its 128-bit copy needs the grouped
   copy profile, which is a per-file flag. */

extern void func_00115484(void *, int, int);

extern int func_00277F48(float, char *, int, char *, int);

extern void *D_L01_001C3980[];

/* Finds up to 16 nearby creatures of one kind, marks them and remembers them in a list. */
void func_L01_003B45D8(void *object, void **list, int *found) {
    int i;
    int hitCount;
    void *other;

    memset(list, 0, 4);
    *found = 0;
    hitCount = ProcessCollisionHit(3.5f, (char *)object + 0x10, 1, (char *)object, 0);
    if (hitCount <= 0)
        return;
    for (i = 0; i < hitCount; i++) {
        other = D_L01_001C3980[i];
        if (other == 0)
            continue;
        if (*(s16 *)((u8 *)other + 0xAA) != 0xA26 /* moby class 2598 */)
            continue;
        *(u32 *)((u8 *)other + 0x9C) = 1;
        *(u8 *)((u8 *)D_L01_001C3980[i] + 0xBC) = 1;
        list[*found] = D_L01_001C3980[i];
        *found = *found + 1;
        if (*found >= 16)
            break;
    }
}

/* Removes the mark from every creature in the list made by the function above. */
void func_L01_003B46C8(char **list, int *count) {
    int i;

    if (*count <= 0)
        return;
    i = 0;
    do {
        *(int *)(list[i] + 0x9C) = 0;
        i++;
    } while (i < *count);
}


/* func_L01_003B49D8 and func_L01_003B4AD0 live in L01_003B49D8.c: their clamp needs
   -ffast-math (the retail's min.s), which is a per-file flag. */

/* Gives back this creature's place in its group, if it had taken one. */
void func_L01_003B4BD8(u8 *object) {
    char *vars = *(char **)(object + 0x68);

    if (object[0x21] != 0xFF) {
        if (*(int *)(vars + 0x340) != 0) {
            FastFloatHelperD(*(int **)(vars + 0x33C));
        }
    }
    *(int *)(vars + 0x340) = 0;
}

/* Takes a place in the creature's group if it has none yet, and counts it. Always returns 1. */
int func_L01_003B4C20(u8 *object) {
    char *vars = *(char **)(object + 0x68);
    int result = 1;

    if (object[0x21] != 0xFF) {
        if (*(int *)(vars + 0x340) == 0) {
            int *groupCount = *(int **)(vars + 0x33C);
            *groupCount = *groupCount + 1;
        }
    }
    *(int *)(vars + 0x340) = result;
    return result;
}

/* func_L01_003B4C58 is defined in L01_003B4C58-g8.c. */

extern float func_002A89A8(void *, int, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L01_0032EF38(void *, int, int, float, float, int);
extern void func_002B0990(u8 *, u8 *, s32, s32, f32);

/* Throws a number of small particles around the object at the given height. A height of -1 means use the height of what it stands on. */
void func_L01_003B50C8(char *object, int count, float height)
{
    float position[4];
    float angle, radius, first, second;
    char *state;
    int life, left;

    if (height == -1.0f) {
        state = *(char **)(object + 0x68);
        if (*(int *)(state + 0x1E8) != -1 || *(int *)(state + 0x198) != 0)
            return;
        height = *(float *)(state + 0x1A0) + 0.015f;
    }
    if (height == 0.0f)
        height = ProbeGroundHeightBelow(object + 0x10, 0, 0.5f) + 0.025f;
    for (left = 0; left < count; left++) {
        angle = RandomAngle();
        radius = RandomFloatRange(0.0f, 0.8f);
        first = RandomFloatRange(0.0f, 1.5f);
        second = RandomFloatRange(1.5f, 5.7f);
        life = RandomIntRange(100, 180);
        position[0] = FastSinOrCosA(angle) * radius;
        position[1] = FastSinOrCosB(angle) * radius;
        position[2] = 0.0f;
        FastVecAdd(position, position, object + 0x10);
        position[2] = height;
        SpawnGlowParticle_L01(position, 0x38002028, 0x2020, first, second, life);
    }
}

/* Clears the measured 0x350 word when it is set, then draws the new duration
   if the old one is still short. */
/* Runs the creature's timers each frame and picks a new random wait when the old one is short. */
void func_L01_003B5310(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    u16 flags;

    if (*(u32 *)(vars + 0x350) != 0) {
        *(u32 *)(vars + 0x350) = 0;
        if (*(s32 *)(vars + 0x330) < 200) {
            *(u32 *)(vars + 0x330) = RandomIntRange(300, 360);
        }
    }
    if (*(u32 *)(vars + 0x244) != 1)
        FastFloatHelperD(vars + 0x330);
    flags = *(u16 *)(object + 0x96);
    if (flags < 65534)
        *(u16 *)(object + 0x96) = flags + 1;
    FastFloatHelperD(vars + 0x32C);
    FastFloatHelperD(vars + 0x334);
    SetValueAndStartSmoothChange(object, vars + 0x250, 6, 1, 4.0f);
}

/* func_L01_003B53C8 is defined in L01_003835D8-g8.c. */

/* func_L01_003B57A8 uses the SDA pointer to the position table. */
extern u8 *D_L01_001B264C __attribute__((sda));
extern char D_00189EA0[];
extern float func_00282E80(void *, void *);

/* Of the (up to four) positions whose indices are listed at the state's +0x310, copies the one
   func_00282E80 rates highest against D_00189EA0 to OUT (its rating at +0xC), then stores
   func_002A89A8's value for it at +0x8. A position is the 16-byte record at +0x30 of the
   index's 0x80-byte entry in the D_L01_001B264C table. */
void func_L01_003B57A8(u8 *object, u8 *result) {
    s32 *indexList = (s32 *)(*(u8 **)(object + 0x68) + 0x310);
    u8 pos[16] __attribute__((aligned(16)));
    s32 count = 4;
    f32 rating;

    *(f32 *)(result + 0xC) = 0.0f;
    while (--count >= 0) {
        if (*indexList != -1) {
            qcopy(pos, D_L01_001B264C + *indexList * 0x80 + 0x30);
            rating = vec_distance_xy(pos, gHeroPosition);
            if (*(f32 *)(result + 0xC) < rating) {
                qcopy(result, pos);
                *(f32 *)(result + 0xC) = rating;
            }
        }
        indexList++;
    }
    *(f32 *)(result + 0x8) = ProbeGroundHeightBelow(result, 0, 10.0f);
}

/* func_L01_003B5878 is defined in L01_003B5878-g8.c. */

/* func_L01_003B9F30 is defined in L01_003B9F30-g16.c. */

/* func_L01_003BAFB0 lives in the -g8 sibling file (it reads a float through $gp). */

/* func_L01_003BAFB8 is defined in L01_003BAFB8-g8.c. */
