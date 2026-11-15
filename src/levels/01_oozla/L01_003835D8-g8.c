#include "include_asm.h"
#include "common.h"

extern float D_L01_001AF87C __attribute__((sda));

extern float D_L01_001AFE18 __attribute__((sda));

/* Returns the height of the water surface in this level. */
float func_L01_003BAFB0(void) {
    return D_L01_001AFE18;
}

extern char *D_L01_001B255C __attribute__((sda));

extern char D_L01_001BF930[];

extern u8 *D_L01_001FB020[];

extern void func_00282CC0(char *, char *, char *);

extern void func_00282CF0(char *, char *, char *);

extern void func_00282F20(char *, char *, float);

extern int func_00277258(char *, int, char *, float);

/* Moves the object by its speed for one frame and pushes it back along the surface if it hits something. */
void func_L01_003A65B0(char *object) {
    char buf[16];

    vec_scale_to_length(buf, object + 0xE0, D_L01_001AF87C);
    FastVecAdd(buf, buf, object + 0x10);
    if (TestPointAgainstCollision(buf, 0, object, D_L01_001AF87C) != 0) {
        FastVecSub(buf, D_L01_001BF930, buf);
        FastVecAdd(object + 0x10, object + 0x10, buf);
    }
}

/* Wakes up every swamp beast in the same group as this object, so they all notice the player. */
void func_L01_003B5290(u8 *object) {
    char *mobyBase;
    u8 *entry;
    u8 *groupList;

    if (object[0x21] == 0xFF)
        return;
    groupList = D_L01_001FB020[object[0x21]];
    if (groupList == 0)
        return;
    entry = groupList;
    mobyBase = gMobyTable_L01;
    for (;;) {
        char *other = mobyBase + ((*(unsigned short *)entry & 0x7FFF) << 8);

        if (*(signed char *)(other + 0x20) >= 0) {
            if (*(short *)(other + 0xAA) == 0x9A2 /* Mutant Swamp Beast */) {
                *(int *)(*(char **)(other + 0x68) + 0x350) = 1;
            }
        }
        if (*(short *)entry < 0)
            break;
        entry += 2;
    }
}

/* func_L01_003B57A8 is defined in L01_003835D8.c. */

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
extern void *D_L01_001FE180[];
extern float D_L01_001AF85C __attribute__((sda));
extern float D_L01_001AF860 __attribute__((sda));
extern int D_L01_001AF864 __attribute__((sda));
extern int D_001A79F0 MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_L01_001A907C;
extern void func_0029F338(void *);
extern float func_00282E48(void *,void *);
extern float func_00282C48(float);
extern void func_002C9828(float,void *,int,void *,void *,int);
extern void func_002A7470(void *,int,int,int);
extern int func_002A9640(void *,int,int);
extern void func_00283098(void *,void *,void *);
extern void func_002E5E58(int,int,int);
extern void func_002B0A18(int,int);
extern int func_002B3868(void *);
extern void func_002AC728(void *,void *,int,float,float);
extern void func_002E5CF8(int,int,void *);
extern float func_00283B98(float,float);
extern float func_002A89A8(void *,int,float);
extern void func_002A7750(void *,int,int);
extern void func_L01_003A6028(void *);
extern void func_L00_00326110(void *,int,float);
extern int func_00282948(void *);
/* Flies a target along its path. When it is shot it falls into the water, makes a splash and disappears. */
void func_L01_003A5BB8(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *path = D_L01_001FE180[I(state,0x50)];
    float first, last, oldHeight;
    int mode, count;
    switch (object[0x20]) {
    case 0:
        if (I(state,0x50) == -1) { MarkMobySpawned(object); return; }
        D_L01_001AF864 = 0;
        first = fast_vec_dist(path + 0x10,path + 0x20);
        last = fast_vec_dist(path + 0x10,path + I(path,0)*16);
        F(state,0x74) = (D_L01_001AF85C * 0.016666668f) / first;
        I(state,0x70) = FloatAbs(first-last) < 0.1f;
        F(state,0x5C) = F(state,0x58) * I(path,0);
        object[0x20] = 1;
        F(object,0x2C) *= D_L01_001AF860;
        object[0x30] = 255;
    case 1:
        oldHeight = F(object,0x18);
        SamplePathPosition(F(state,0x5C),path,I(state,0x70),object+0x10,object+0xF0,0);
        F(object,0xF4) *= 0.5f;
        F(object,0x18) += F(state,0x54);
        F(state,0x5C) += F(state,0x74);
        if (F(state,0x5C) > I(path,0)) F(state,0x5C) -= I(path,0);
        if (object[0x60] & 2) {
            if (oldHeight < F(object,0x18)) {
                if (object[0x43] != 0) StartAnimationBlended(object,0,0,10);
            } else if (object[0x43] != 1) StartAnimationBlended(object,1,0,10);
        }
        if (!FindOwnedEffectSlot(object,0x10000,0)) return;
        F(state,0x60) = D_L01_001AF85C * 0.008333334f;
        matrix_mul_vec3(state+0x60,state+0x60,object+0xC0);
        count = D_L01_001AF864 + 1;
        F(state,0x68) = -0.0500000045f;
        if ((D_L01_001AF864 = count) > 3 && (mode = gCurrentMapIndex) == 1 && !D_001A7A60[13]) {
            D_001A7A60[13] = 1;
            PlaySoundFromGlobalBank(1,0,0);
            SetEntryValueByIndex(0x1233,-1);
            D_L01_001A907C = mode;
        }
        SetMobyState(object,2,-1);
        break;
    case 2:
        if (SetFirstPendingFlag(object)) {
            SpawnExplosionWithSparks(object,object+0x10,-1,0.5f,13.0f);
            PlayMobySound(0,0,object);
        }
        F(object,0x48) = 0.5f;
        FastVecAdd(object+0x10,object+0x10,state+0x60);
        F(state,0x68) -= 0.003f;
        F(state,0x60) *= 0.98f;
        F(state,0x64) *= 0.98f;
        F(object,0xF0) = FastAddRotations(-3.1415927f,(F(object,0xF0)+3.1415927f)*0.95f);
        if (FloatAbs(ProbeGroundHeightBelow(object+0x10,0,0.5f)-F(object,0x18)) < 0.5f) {
            I(state,0x78) = 30;
            SetMobyState(object,3,-1);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(object)) {
            OozlaSpawnSplashParticles(object);
            PlayMobySound(1,0,object);
            SpawnScaledBolts(object,1,0.0f);
        }
        F(object,0x18) += F(state,0x68);
        if (FastFloatHelperD(state+0x78)) MarkMobySpawned(object);
        return;
    default:
        return;
    }
}

#define P(p,o) (*(int **)((u8 *)(p)+(o)))
#define C(p,o) (*(u8 **)((u8 *)(p)+(o)))
typedef int OozlaQuad __attribute__((mode(TI)));
extern float D_L01_001B94C0[];
typedef struct { u8 pad[0x2290]; u8 *target; } OozlaHero;
extern OozlaHero D_00189E20;
extern float D_00189EA0[];
extern int D_L01_001B2088 MACRO_ADDR;
extern void func_002A93B0(void *);
extern int func_002B3BA8(void *,int,int,int,float,float);
extern float func_00282E80(void *,void *);
extern s32 func_002AB1F0(u8 *);
extern int func_002B0ED8(void *,void *,int);
extern void func_L01_003B4BD8(void *);
extern float func_00283248(float,float);
extern float func_00283BE0(float,float);
extern void func_002AEC48(void *,void *,int,float,float);
extern int func_002A77E0(int);
extern void func_L01_003B4480(void *);
extern int func_002A8600(void *,int,int,int);
extern int func_002A86E8(void *,void *,int,int);
/* Main behaviour for a swimming creature. It checks for the player, steers toward its goal, makes bubbles near the surface and picks its group mates. */
void func_L01_003B53C8(u8 *object)
{
    OozlaQuad saved[2];
    u8 *iterator;
    u8 *common;
    u8 *state = C(object,0x68);
    u8 *target, *detail;
    float angle, distance, best;
    if (object[0x31] && fast_vec_dist(object+0x10,D_L01_001B94C0) < 24.0f) {
        UpdateMobyGroundCheck(object);
        object[0x6F] = 22;
    }
    saved[0] = *(OozlaQuad *)(state+0x230);
    saved[1] = *(OozlaQuad *)(state+0x240);
    if (SelectAimTarget_002B3BA8(object,I(state,0x398),0,0,F(state,0x388),0.5f) != 1 && ((int *)saved)[5] == 1) {
        target = ((u8 **)saved)[4];
        if (target && target[0x20] != 254 && target[0x20] != 253 && vec_distance_xy(object+0x10,target+0x10) < F(state,0x39C)) {
            *(OozlaQuad *)(state+0x230) = saved[0];
            *(OozlaQuad *)(state+0x240) = saved[1];
            target = C(state,0x240);
            if (target == gHeroState.target) {
                qcopy(state+0x230, (u8 *)&gHeroState+0xD0);
            } else {
                qcopy(state+0x230, target+0x10);
                detail = (u8 *)GetMobyPrivateValue0(target);
                if (detail) F(state,0x238) += F(detail,0x10);
            }
        }
    }
    common = C(object,0x68);
    if (ApplyDamageToObject(object,common+0x60,0)) {
        if (F(common,0x20) <= 0.0f) I(common,0xDC) = -1;
        else I(common,0xDC) = I(common,0x14C);
        ReleaseGroupSlot(object);
        AlertSwampBeastGroup(object);
        if (object[0x95] < 3) {
            common[0x7A] = 2;
            if (object[0x43] != 4) StartAnimationBlended(object,4,0,15);
            I(common,0x320) = 0;
            SetMobyState(object,1,1);
        }
    }
    if (object[0x31]) {
        u8 *goal = C(state,0x240);
        angle = FastMatrixHelperA(F(goal,0x10)-F(object,0x10),F(goal,0x14)-F(object,0x14));
        F(state,0x2B8) = fast_subtract_rotations(angle,F(object,0xF8));
        UpdateEasedNode(object,state+0x250,4,0.03f,0.3f);
        if (F(object,0x18) <= GetWaterHeight()+0.3f && (object[0x95] >= 2 || RandomIntBelow(9) == 0))
            SpawnSwampBeastBubbles(object);
    }
    if (object[0x21] != 255 && *P(state,0x368) != D_L01_001B2088) {
        if (*P(state,0x36C) == -1 || *P(state,0x368) < D_L01_001B2088-10) {
            *P(state,0x36C) = -1;
            *P(state,0x370) = -1;
            best = 100000.0f;
            GetFirstMobyInGroup(&iterator,object[0x21],0,0);
            while (iterator) {
                if (*(short *)(iterator+0xAA) == *(short *)(object+0xAA)) {
                    distance = vec_distance_xy(iterator+0x10,gHeroPosition);
                    if (distance < best && iterator[0x95] == 3 && iterator[0x20] < 3) {
                        best = distance;
                        *P(state,0x370) = *P(state,0x36C);
                        *P(state,0x36C) = *(short *)(iterator+0xB2);
                    }
                }
                GetNextMobyInGroup(&iterator,iterator,0,0);
            }
            *P(state,0x368) = D_L01_001B2088;
        }
    }
}
