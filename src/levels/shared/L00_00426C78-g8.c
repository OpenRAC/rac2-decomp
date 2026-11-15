#include "common.h"
extern float func_00282DB0(char *, char *);
extern float func_00282DF0(char *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002831B0(float);
extern void func_00282D30(char *, char *, float);
extern void func_00282CF0(char *, char *, char *);
extern char *func_L00_002DB350(char *, float);
extern void func_L00_00424F00(char *, float, float);
extern void func_L00_002D9D98(void);
extern void func_00282978(char *);
typedef struct { char *table; } Table_b0898;
extern Table_b0898 D_L00_001B1844[] __attribute__((section(".sdata")));
extern int ref_L00_00426C78_00 __attribute__((sda));
extern char *D_L00_001B8E10 __attribute__((section(".data")));
extern char D_00189EA0[];
extern unsigned int D_001A7390[] __attribute__((section(".sdata")));
extern int D_001A79F0[] __attribute__((section(".sdata")));
typedef struct {
 char pad[0x98]; float angle; char pad9c[0x2290-0x9C]; char *owner;
 char pad2294[0x24A0-0x2294]; int identity;
} Global_6C78;
extern Global_6C78 D_00189E20_6C78;
typedef struct { char pad[0x190]; char *owner; char pad194[0x3C]; char axis[16]; } Global_6C78B;
extern Global_6C78B D_L00_001B8C80_6C78;
typedef struct { char pad[0x198]; unsigned short count; char pad19a[2]; unsigned int time; unsigned int flags; } Global_6C78C;
extern Global_6C78C D_0018C750_6C78;


typedef struct { char pad[0x20]; short count, active, timer; } TransitionState;
typedef int CameraQuad __attribute__((mode(TI)));
/* Checks every frame whether the hero is hitting a trigger the right way. Counts the hits, and after 7 in a row it fires the trigger. It also nudges the camera while a hit is in progress. */
int func_L00_00426C78(char *triggerObj, char *otherObj)
{
    float scratch[4] __attribute__((aligned(16)));
    char dirA[16] __attribute__((aligned(16)));
    char dirB[16] __attribute__((aligned(16)));
    TransitionState *transition = *(TransitionState **)(D_L00_001B1844[0].table + *(short *)(triggerObj + 0x84)*32 + 28);
    char *owner;
    char *blocker;
    int heroIdentity;
    int otherType, ownerType;
    float lengthProduct, dotValue;
    if (ref_L00_00426C78_00) { ref_L00_00426C78_00 = 0; return 0; }
    heroIdentity = D_00189E20_6C78.identity;
    { int identity = *(short *)(triggerObj + 0x86);
    ref_L00_00426C78_00 = 0;
    if (heroIdentity == identity || heroIdentity == 0x51) {
        owner = gFollowCameraObject;
        otherType = *(short *)(otherObj + 0x86);
        if (!(otherType == 0 || otherType == 10 || otherType == 14 || otherType == 2)) goto clear;
        ownerType = *(short *)(owner + 0x86);
        if (!(ownerType == 0 || ownerType == 10 || ownerType == 14 || ownerType == 2)) goto clear;
        *(CameraQuad *)scratch = *(CameraQuad *)gHeroPosition;
        blocker = FindIntersectingGridPrimitive((char *)scratch, 0.25f);
        if (blocker && (*(int *)(blocker + 0x18) & 1)) return 0;
        transition->timer = 0;
        transition->active = 1;
        transition->count++;
        if (transition->count >= 7) {
            if (*(short *)(owner + 0x86) == 0) *(char *)(triggerObj + 0x7C) = 5;
            return 1;
        }
        scratch[0] = FastSinOrCosA(D_00189E20_6C78.angle);
        scratch[1] = FastSinOrCosB(D_00189E20_6C78.angle);
        scratch[2] = 0;
        SetCameraStrengthAndSteer((char *)scratch, 0.06981317698955536f, scratch[2]);
        goto timer;
clear:
        transition->count = 0;
        transition->active = 0;
        goto timer;
    }
    }
    transition->count = 0;
    if (transition->active == 0) goto timer;
    transition->active = 0;
    if (*(short *)(D_L00_001B8C80_6C78.owner + 0x86) != 0) goto timer;
    if (D_0018C750_6C78.count < 65535) ++D_0018C750_6C78.count;
    if (D_001A7390[0] > D_0018C750_6C78.time) D_0018C750_6C78.time = D_001A7390[0];
    D_0018C750_6C78.flags = (D_0018C750_6C78.flags | (1U << gCurrentMapIndex[0])) | 0x80000000U;
    dotValue = FastVecDot(D_L00_001B8C80_6C78.axis, D_L00_001B8C80_6C78.owner);
    FastVecScale((char *)scratch, D_L00_001B8C80_6C78.axis, dotValue);
    FastVecSub(dirA, D_L00_001B8C80_6C78.owner, (char *)scratch);
    dotValue = FastVecDot(D_L00_001B8C80_6C78.axis, D_00189E20_6C78.owner + 0xC0);
    FastVecScale((char *)scratch, D_L00_001B8C80_6C78.axis, dotValue);
    FastVecSub(dirB, D_00189E20_6C78.owner + 0xC0, (char *)scratch);
    lengthProduct = FastVecLength(dirB);
    if (lengthProduct != 0.0f) {
        lengthProduct *= FastVecLength(dirA);
    }
    if (lengthProduct != 0.0f) {
        do { dotValue = FastAngleHelper(FastVecDot(dirB, dirA) / lengthProduct); } while (0);
        if (1.3962636f <= 1.5707964f - dotValue) { ResetDefaultCamera(); return 0; }
    }
    transition->timer = 30;
timer:
    if (transition->timer) {
        FastDecTimer((char *)&transition->timer);
        scratch[0] = FastSinOrCosA(D_00189E20_6C78.angle);
        scratch[1] = FastSinOrCosB(D_00189E20_6C78.angle);
        scratch[2] = 0;
        SetCameraStrengthAndSteer((char *)scratch, 0.13962635397911072f, scratch[2]);
    }
    return 0;
}
