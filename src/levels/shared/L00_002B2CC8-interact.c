#include "common.h"

typedef struct {
    unsigned char pad0[476];
    short timer;
    unsigned char pad1de[62];
    short soundTimer;
    unsigned char pad21e[1136];
    short f68e;
    unsigned char pad690[52];
    int f6c4;
    unsigned char pad6c8[3535];
    unsigned char f1497;
    unsigned char pad1498[104];
    int interrupted;
    unsigned char pad1504[3468];
    char *moby;
    int moveState;
    unsigned char pad2298[4];
    int controlMode;
    unsigned char pad22a0[20];
    unsigned char vehicleMode;
    unsigned char pad22b5[487];
    char *contact;
    unsigned char pad24a0[44];
    int health;
} Root;

extern Root D_00189E20;
extern char D_L00_001C3480[];
extern int D_L00_001A8F00 __attribute__((sda));
extern unsigned char D_001A7A33 __attribute__((sda));
extern unsigned char D_001A7A32 __attribute__((sda));
extern float func_L00_0037E668(void);
extern float func_L00_0037E5F0(float);
extern void func_L00_002A6708(void);
extern void func_00282CF0(void *, void *, void *);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void ref_L00_002B2CC8_0(int, int);
extern void *func_002A9640(void *, int, int);
extern int func_00283CF0(float);
extern void func_L00_002A4EF8(int);
extern void func_L00_002B9B88(int, int);
extern void func_L00_002B2C58(void *, int, float, float);
extern void func_L00_002D3C68(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

#define SI(o) (*(int *)(slot + (o)))
#define SF(o) (*(float *)(slot + (o)))

/* Checks whether the hero can grab the object it is next to and, if asked, starts the grab and pushes the hero toward it. Returns 1 when a grab is possible. */
int func_L00_002B2CC8(int apply)
{
    float pushVec[4] __attribute__((aligned(16)));
    char *targetMoby, *slot, *other;
    int special;
    float scale;

    if (gHeroState.controlMode == 20)
        return 0;
    if (gHeroState.controlMode == 7)
        return 0;
    if (gHeroState.moveState == 49)
        return 0;
    if (gHeroState.timer)
        return 0;
    if (D_L00_001A8F00)
        return 0;
    gHeroState.contact = 0;
    targetMoby = gHeroState.moby;
    if ((unsigned char)targetMoby[0xa8] == 255)
        return 0;
    slot = D_L00_001C3480 + (unsigned char)targetMoby[0xa8] * 64;
    if (*(char **)(slot + 0x38) != targetMoby || !(SI(0x24) & 9))
        return 0;
    if (SF(0x2c) != 0.0f) {
        D_001A7A33 = 0;
        gBoltMultiplier = 1;
    }
    if (GetFadeValue() != 0.0f && !gHeroState.vehicleMode) {
        SF(0x2c) = ReduceFadeValue(SF(0x2c));
        if (SF(0x2c) == 0.0f)
            return 0;
    }
    gHeroState.contact = SI(0x20);
    if (gHeroState.controlMode == 15) {
        gHeroState.f6c4 = (int)slot;
        gHeroState.f68e = 1;
        return 0;
    }
    if (!apply)
        return 1;
    ClearTrackedSlots();
    special = 0;
    if (SI(0x30) & 1) {
        qcopy(pushVec, slot + 0x10);
        if (SF(0x1c) == 5627.925f)
            special = 1;
    } else if (SI(0x20)) {
        FastVecSub(pushVec, (char *)&gHeroState + 0x80,
                     *(char **)(slot + 0x20) + 0x10);
    } else {
        BuildHeroRelativePoint(pushVec, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (gHeroState.vehicleMode) {
    case 0: {
        other = gHeroState.contact;
        if (other && (*(short *)(other + 0xaa) == 1259 /* moby class 1259 */ || *(short *)(other + 0xaa) == 1368 /* moby class 1368 */)) {
            ref_L00_002B2CC8_0(125, 1);
            return 1;
        }
        if ((gHeroState.moveState == 1 || gHeroState.moveState == 29 || gHeroState.interrupted) &&
            !(SI(0x24) & 8)) {
            other = FindOwnedEffectSlot(gHeroState.moby, 1, 0);
            if (other)
                AdjustPlayerHealth(FloatToInt(*(float *)(other + 0x2c)));
            if (!gHeroState.health)
                ref_L00_002B2CC8_0(22, 1);
            gHeroState.timer = 77;
            if (!gHeroState.soundTimer)
                gHeroState.soundTimer = 18;
            PlayHeroSound(20, 0);
            return 0;
        }
        if (gHeroState.controlMode == 18)
            ref_L00_002B2CC8_0(114, 1);
        else if (gHeroState.controlMode == 17)
            ref_L00_002B2CC8_0(115, 1);
        else if (SI(0x24) & 8)
            ref_L00_002B2CC8_0(140, 1);
        else
            ref_L00_002B2CC8_0(22, 1);
        if (gHeroState.moveState == 140) {
            qzero(pushVec);
        } else {
            scale = 0.055000003f;
            if (gHeroState.f1497)
                scale = 0.0f;
            FlattenPushVectorAndSetStrength(pushVec, special, scale, 0.028333336f);
            if (special && (unsigned char)slot[0x28] == 4)
                ScaleViewSpaceHeight(pushVec, pushVec, 2.0f);
        }
        break;
    }
    case 1: {
        ref_L00_002B2CC8_0(66, 1);
        FlattenPushVectorAndSetStrength(pushVec, special, 0.083333336f, 0.050000004f);
        break;
    }
    }
    FastVecAdd((char *)&gHeroState + 0xf0, (char *)&gHeroState + 0xf0, pushVec);
    FastVecAdd((char *)&gHeroState + 0x110, (char *)&gHeroState + 0x110, pushVec);
    return 1;
}
