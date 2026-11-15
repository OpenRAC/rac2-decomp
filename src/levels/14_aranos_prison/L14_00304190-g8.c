#include "common.h"
#include "include_asm.h"

extern int D_001A79F0;

extern int D_001A72E0;

extern int D_L14_001B23D0 __attribute__((sda));

extern char *D_L14_001B259C __attribute__((sda));

extern char D_L14_00284690[];

extern void func_367708();

extern void func_3674A0();

extern void func_367778();

extern void func_385CB8(unsigned int reg, unsigned long value);

extern void func_L14_00304190();

extern void func_2F5CC0(void *dst, void *src, float s);

extern void func_2F5C38(void *dst, void *src, void *src2);

extern void func_420B10();

extern void func_321F58();

extern void func_3DFA10();

extern int func_002B38B8();

extern int func_3322A0();

extern void func_369AD0();

extern void func_2F5C10();

extern void func_2F5C38(void *dst, void *src, void *src2);

extern void func_2F5D68(void *dst, void *src, void *mtx);

extern void func_2F5F18(void *dst, void *src, float s);

extern float func_2F6C80(float a, float b);

extern float func_2F5B78(float a);

extern void func_317D90();

extern void func_2EE5F0();

extern void func_L14_003DFA60();

extern int D_L14_001B092C __attribute__((sda));

extern float func_002A78D8(float a0, float a1);

extern int func_00283CF0(float f);

extern long long func_0027C878(int a);

extern void func_00283410(void *dst, void *src);

extern void func_00282D30(void *dst, void *src, float s);

extern void func_00280B90(void *dst, void *src, int c);

extern void func_L14_003F0E98(char *a);

extern float D_L14_001B0388 __attribute__((sda));

extern float D_L14_001B038C __attribute__((sda));

extern float D_L14_001B0390 __attribute__((sda));

/* This unit is built with -G8: these two bodies reach a global through $gp. */

/* Sets up the level's scene at load time and starts the sound and graphics registers. */
void func_L14_00304280(void) {
    func_367708();
    D_L14_001B23D0 = (int)D_L14_00284690;
    if (gCurrentMapIndex == 0xE) {
        InitRecordTable();
    } else {
        func_3674A0();
    }
    func_367778();
    func_385CB8(0x47, 0x5360B);
    func_385CB8(0x4E, 0x1000000 | (D_001A72E0 >> 13));
}

extern char D_00189EA0[];
extern unsigned char D_00188660[];
extern void func_002A7750(void *, int, int);
extern void func_00282CF0(void *dst, void *a, void *b);
extern float func_00282DF0(void *);
extern void func_00282DD8(void *dst, void *a, void *b);
extern int func_L14_003DE2D8(char *);
extern int func_002B3868(void *);
extern int func_002ACBC8(void *, int);
extern void func_L14_003DE488(char *);
extern int func_00282948(int *);
extern int func_L00_00324120(void *);
extern float func_00282E48(void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_L14_003DE360(char *, float);
extern void func_L14_003DE310(char *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Updates moby class 2788 (no label yet): a door-like part that swings between two positions. */
/* A two-position mover. State 0 stores its two end points (which one is the current
   position depends on word 0x70) and each linked entity's distance to them; state 1 waits on
   func_002ACBC8; states 3 and 4 re-arm the timer at 0x8C and, once func_L00_00324120 says so
   or the player has moved to the other side of the object, start the turn (states 5 and 6),
   which steps func_L14_003DE360 until the angle at 0x80 reaches 0 or pi/2 and then stops the
   object's sound. */
void func_L14_003DDD38(char *self)
{
    float pos[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float d1[4] __attribute__((aligned(16)));
    float d2[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);
    char **ent;
    float *dist;
    int i;
    float distance;
    int side;
    unsigned char *sound;

    qcopy(pos, self + 0x10);
    qcopy(rot, self + 0xF0);

    switch ((unsigned char)self[0x20]) {
    case 0:
        *(unsigned short *)(self + 0x34) |= 0x100;
        *(float *)(vars + 0x7C) = 0.0087266471f;
        *(int *)(vars + 0x78) = -1;
        *(int *)(vars + 0x5C) |= 1;
        if (*(int *)(vars + 0x70) != 0) {
            qcopy(vars + 0x90, self + 0x10);
            qcopy(vars + 0xA0, vars + 0x60);
            *(float *)(vars + 0x80) = 1.5707964f;
            SetMobyState(self, 4, -1);
        } else {
            qcopy(vars + 0xA0, self + 0x10);
            qcopy(vars + 0x90, vars + 0x60);
            *(float *)(vars + 0x80) = 0.0f;
            SetMobyState(self, 3, -1);
        }
        qcopy(vars + 0xB0, vars + 0xA0);
        *(float *)(vars + 0xB8) = *(float *)(vars + 0x98);
        FastVecSub(d1, vars + 0xA0, vars + 0xB0);
        *(float *)(vars + 0x84) = FastVecLength(d1);
        FastVecSub(d2, vars + 0x90, vars + 0xB0);
        *(float *)(vars + 0x88) = FastVecLength(d2);
        FastVecCross(vars + 0xC0, d2, d1);
        ent = (char **)(vars + 0xE0);
        dist = (float *)(vars + 0xF0);
        /* The four linked-entity ids are the words at st+0xD0, just before the distances at
           st+0xF0, so each one is read eight words back from its distance. */
        for (i = 3; i >= 0; i--) {
            if (*(int *)(dist - 8) > 0) {
                *ent = gMobyPool_L14 + (*(int *)(dist - 8) << 8);
                FastVecSub(d1, *ent + 0x10, vars + 0xB0);
                distance = FastVecLength(d1);
                if ((unsigned char)self[0x20] == 4) {
                    dist[0] = distance;
                    dist[4] = *(float *)(vars + 0x84) - *(float *)(vars + 0x88) + distance;
                } else {
                    dist[4] = distance;
                    dist[0] = *(float *)(vars + 0x88) - *(float *)(vars + 0x84) + distance;
                }
            } else {
                *ent = 0;
            }
            ent++;
            dist++;
        }
        if (CountUsedChildSlots(self) != 0 && *(int *)(vars + 0x74) >= 0) {
            SetMobyState(self, 1, -1);
        }
        break;
    case 1:
        SetFirstPendingFlag(self);
        if (IsPointInCuboid(gHeroPosition, *(int *)(vars + 0x74)) != 0) {
            SetMobyState(self, 2, -1);
        }
        break;
    case 2:
        SetMobyState(self, 3, -1);
    case 3:
    case 4:
        if (SetFirstPendingFlag(self) != 0) {
            WakeChildMobys(self);
            *(int *)(vars + 0x8C) = 100;
        }
        FastFloatHelperD((int *)(vars + 0x8C));
        if (IsCurrentSelectedId(self) == 0) {
            if (!(fast_vec_dist(gHeroPosition, self + 0x10) < 30.0f)) {
                break;
            }
            /* Which end the player is nearer; the object's own nearer end must differ. */
            side = fast_vec_dist(gHeroPosition, vars + 0x90) > fast_vec_dist(gHeroPosition, vars + 0xA0);
            if ((side ^ (fast_vec_dist(self + 0x10, vars + 0x90) > fast_vec_dist(self + 0x10, vars + 0xA0))) == 0) {
                break;
            }
        }
        if (CountUsedChildSlots(self) == 0 && *(int *)(vars + 0x8C) <= 0) {
            if ((unsigned char)self[0x20] == 4) {
                SetMobyState(self, 5, -1);
            } else {
                SetMobyState(self, 6, -1);
            }
        }
        break;
    case 5:
        if (SetFirstPendingFlag(self) != 0) {
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, self);
        }
        if (*(float *)(vars + 0x80) > 0.0f) {
            PlaceObjectFromGroupMatrices(self, -*(float *)(vars + 0x7C));
        } else {
            if (*(int *)(vars + 0x78) >= 0) {
                if (*(int *)(vars + 0x78) != -1) {
                    sound = gSoundState + *(int *)(vars + 0x78) * 0x70;
                    if (*(char **)(sound + 0x88) == self && sound[0x74]) {
                        StopSoundVoice(*(int *)(vars + 0x78));
                    }
                }
                *(int *)(vars + 0x78) = -1;
            }
            if (IsCurrentSelectedId(self) == 0) {
                SetMobyState(self, 3, -1);
            }
        }
        break;
    case 6:
        if (SetFirstPendingFlag(self) != 0) {
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, self);
        }
        if (*(float *)(vars + 0x80) < 1.5707964f) {
            PlaceObjectFromGroupMatrices(self, *(float *)(vars + 0x7C));
        } else {
            if (*(int *)(vars + 0x78) >= 0) {
                if (*(int *)(vars + 0x78) != -1) {
                    sound = gSoundState + *(int *)(vars + 0x78) * 0x70;
                    if (*(char **)(sound + 0x88) == self && sound[0x74]) {
                        StopSoundVoice(*(int *)(vars + 0x78));
                    }
                }
                *(int *)(vars + 0x78) = -1;
            }
            if (IsCurrentSelectedId(self) == 0) {
                SetMobyState(self, 4, -1);
            }
        }
        break;
    }
    ClearDeadLinkedMobys(self);
    FastVecSub(delta, self + 0x10, pos);
    CombineTransformsAndStore(vars + 0x20, delta, rot, self + 0xF0);
}

/* func_L14_003E5030 is matched in its own unit, src/levels/shared/L14_003E5030-g8.c (-O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */

/* Draws two lines on either side of the object, along its facing direction. */
void func_L14_003DF100(char *moby, int isFirst) {
    float offsetA[4];
    float offsetB[4];
    char *vars;
    char *pos;

    vars = *(char **)(moby + 0x68);
    func_2F5CC0(offsetA, moby + 0xC0, 2.0f);
    func_2F5CC0(offsetB, moby + 0xC0, -2.0f);
    if (*(int *)(vars + 0x7C) != 0) {
        func_2F5CC0(offsetA, offsetA, -1.0f);
        func_2F5CC0(offsetB, offsetB, -1.0f);
    }
    pos = moby + 0x10;
    func_2F5C38(offsetA, offsetA, pos);
    func_2F5C38(offsetB, offsetB, pos);
    func_420B10(*(int *)(vars + 0x64), offsetA, pos, isFirst == 0);
    func_420B10(*(int *)(vars + 0x64), offsetB, pos, 0);
}

/* The id-list walks of func_L14_003DF440 and func_L14_003DF540 read D_L14_001B259C as a bare
   symbol (the second name: `sda` on an array over 8 bytes), while D_L14_001B25B8 is a plain int:
   its `.extern` comes last in the file, so the load in a branch delay slot is a $gp access and
   no other load is. */
extern unsigned short *D_L14_001FB060[];
extern int D_L14_001B25B8;
extern unsigned char *D_L14_001B259C_base[3] __asm__("D_L14_001B259C") __attribute__((sda));
extern void *func_L00_0032C638(char *a0);

/* 0 when an entity of the owner's group (state word 0x68), other than the two states 0xFE and
   0xFD, has a linked object whose word at +0x88 is not the owner; else 1. */
int func_L14_003DF440(char *self) {
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;
    char *t;

    for (p = gGroupEntityLists[*(int *)(state + 0x68)];
         (*(int *)(state + 0x68) & 0xFF) != 0xFF && *(int *)(state + 0x68) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == gGroupEntityLists[*(int *)(state + 0x68)]);
         p++) {
        e = D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one range test */
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                t = GetObjectVarsWord18(e);
                if (t != 0 && *(char **)(t + 0x88) != self)
                    return 0;
            }
        }
    }
    return 1;
}

extern float func_00282C48(float x);

/* 1 when an entity of the owner's group (state word 0x68), other than the two states 0xFE and
   0xFD, is more than 1.5 away from it along the float at +0x18; else 0. */
int func_L14_003DF540(char *self) {
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;

    for (p = gGroupEntityLists[*(int *)(state + 0x68)];
         (*(int *)(state + 0x68) & 0xFF) != 0xFF && *(int *)(state + 0x68) <= D_L14_001B25B8 &&
         p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == gGroupEntityLists[*(int *)(state + 0x68)]);
         p++) {
        e = D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] != 0xFE) {
            if (e[0x20] != 0xFD) {
                if (FloatAbs(*(float *)(e + 0x18) - *(float *)(self + 0x18)) > 1.5f)
                    return 1;
            }
        }
    }
    return 0;
}

/* Moves and spins an object that flies off and is removed once it has gone far enough. */
void func_L14_003DF7F8(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        func_321F58(moby, 1, -1);
        if (*(int *)(vars + 0x0) != -1) {
            func_3DFA10(moby, 0);
        }
        break;
    case 1:
        if (IsThirdPendingFlagSet(moby) != 0) {
            if (*(int *)(vars + 0x0) != -1) {
                func_3DFA10(moby, 1);
            }
            func_321F58(moby, 2, -1);
            {
                float s = D_L14_001B0388 * 0.016666668f;

                *(float *)(vars + 0xC) = s;
                if (*(int *)(vars + 0x8) != 0) {
                    *(float *)(vars + 0xC) = -s;
                }
            }
            *(int *)(vars + 0x10) = 0;
        }
        break;
    case 2:
        {
            float a[4];
            float b[4];

            if (func_3322A0(moby) != 0) {
                func_369AD0(0, 0, moby);
            }
            func_2F5C10(b);
            func_2F5D68(a, moby + 0xC0, b);
            func_2F5F18(a, a, *(float *)(vars + 0xC));
            func_2F5C38(moby + 0x10, moby + 0x10, a);
            {
                float old = *(float *)(vars + 0xC);
                float m;

                *(float *)(vars + 0x10) = *(float *)(vars + 0x10) + old;
                if (*(int *)(vars + 0x8) != 0) {
                    m = old - D_L14_001B038C * 0.00027777778f;
                } else {
                    m = old + D_L14_001B038C * 0.00027777778f;
                }
                {
                    float x = m * D_L14_001B0390;

                    *(float *)(vars + 0xC) = m;
                    *(float *)(moby + 0xF0) = func_2F6C80(*(float *)(moby + 0xF0), x);
                }
            }
            if (func_2F5B78(*(float *)(vars + 0x10)) > 4.0f) {
                func_317D90(moby);
                return;
            }
        }
        break;
    }
    if (*(unsigned char *)(moby + 0x31) != 0 && *(int *)(vars + 0x4) != -1) {
        func_2EE5F0(DrawFlipbookBillboardQuad, moby);
    }
}

/* The record func_L14_003F0E98 resets: four vertices, four words, eight floats,
   then three 64-bit fields. */
typedef struct {
    struct {
        int id;
        float x;
        float y;
        float z;
    } v[4];
    int p[4];
    float f[8];
    long long q;
    long long r;
    long long s;
} L14_003F0F38_rec;

/* The record, a 64-bit word, a matrix, a vector and a direction. */
typedef struct {
    L14_003F0F38_rec rec;
    long long t;
    float mat[12];
    float vec[4];
    float dir[4];
} L14_003F0F38_frame;

/* The caller supplies an unused scale in F12; the body replaces it before use. */
/* Builds two ribbon-like quads at the object with random fading colours and draws them. */
void func_L14_003F0F38(char *moby, char *target, float unused_scale, int colorBase, int fadeA, int fadeB) {
    L14_003F0F38_frame fr;
    char *vars;
    long long id;
    long long sv;
    long long tw;
    long long tv;

    vars = *(char **)(moby + 0x68);

    fadeA = fadeA - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 5.0f)) << 24);
    ResetBoxRecord(&fr.rec);

    fr.rec.f[0] = *(float *)vars;
    fr.rec.f[1] = 0.0f;
    fr.rec.f[2] = *(float *)vars;
    fr.rec.f[3] = 1.0f;
    fr.rec.f[4] = *(float *)vars + 1.0f;
    fr.rec.f[5] = 0.0f;
    fr.rec.f[6] = *(float *)vars + 1.0f;
    fr.rec.f[7] = 1.0f;

    id = GetEffectTextureDescriptor(D_L14_001B092C);
    fr.rec.r = id;
    fr.rec.s = 280993940374112LL;
    fr.t = 0x8000000048LL;
    fr.rec.p[0] = colorBase + fadeA;
    fr.rec.q = 0LL;

    fadeA = fadeA - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[1] = colorBase + fadeA;
    fadeA = fadeA - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[2] = colorBase + fadeA;
    fadeA = fadeA - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[3] = colorBase + fadeA;

    fr.dir[2] = *(float *)(moby + 0xF8);
    fr.dir[1] = *(float *)(moby + 0xF4);
    fr.dir[0] = 1.5707965f;
    fr.dir[3] = 0.0f;
    euler_to_matrix(fr.mat, fr.dir);

    fr.vec[0] = *(float *)target;
    fr.vec[1] = *(float *)(target + 4);
    fr.vec[2] = *(float *)(target + 8);
    fr.vec[3] = 1.0f;
    FastVecScale(&fr.rec.v[0], &fr.rec.v[0], 1.0f);
    FastVecScale(&fr.rec.v[1], &fr.rec.v[1], 1.0f);
    FastVecScale(&fr.rec.v[2], &fr.rec.v[2], 1.0f);
    FastVecScale(&fr.rec.v[3], &fr.rec.v[3], 1.0f);
    draw_world_quad(&fr.rec, fr.mat, 0);

    tv = 0x8000000044LL;
    fr.rec.f[0] = *(float *)(vars + 8);
    fr.rec.f[1] = 0.0f;
    fr.rec.f[2] = *(float *)(vars + 8);
    fr.rec.f[3] = 1.0f;
    fr.t = tv;
    fadeB = fadeB - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[0] = colorBase + fadeB;
    fadeB = fadeB - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[1] = colorBase + fadeB;
    fadeB = fadeB - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[2] = colorBase + fadeB;
    fadeB = fadeB - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[3] = colorBase + fadeB;
    fr.rec.f[4] = *(float *)(vars + 8) + 1.0f;
    fr.rec.f[5] = 0.0f;
    fr.rec.f[6] = *(float *)(vars + 8) + 1.0f;
    fr.rec.f[7] = 1.0f;
    draw_world_quad(&fr.rec, fr.mat, 0);
}

extern float D_L14_001B04B0 __attribute__((sda));
extern float D_L14_001B04B4 __attribute__((sda));
extern float D_L14_001B04B8 __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);
extern void func_0027C768(void *, float *, float *);
extern float func_00283198(float);
extern float func_L14_003E22A8(char *);
extern float func_L14_003E28E8(float);

/* The caller fills four vertices (indices 0..3), colors at +0x40,
 * and four UV pairs at +0x50 in its quad packet. */
typedef struct {
    float rows[4][4];
    unsigned int colors[4];
    float pairs[4][2];
} L14Swing;

/* Works out one corner of a wobbling quad: its position and clamped texture coordinates. */
void func_L14_003E2688(char *object, L14Swing *base, int index, float *a, float *b, float *c,
                       int phase0, int phase1)
{
    float v[4];

    FastVecScale(v, b, (float)phase1 * 0.125f);
    FastVecAdd(base->rows[index], a, v);
    FastVecScale(v, c, (float)phase0 * 0.125f);
    FastVecAdd(base->rows[index], base->rows[index], v);
    ProjectWorldToScreen(base->rows[index], &base->pairs[index][0], &base->pairs[index][1]);
    base->pairs[index][0] += (1.0f - GetStateProgressFraction(object)) * D_L14_001B04B0
        * FastSinOrCosB(WrapAngleToTwoPi((D_L14_001B04B4 + D_L14_001B04B4) * (GetStateProgressFraction(object) * 3.1415927f)
                                          + (float)phase0 * 3.1415927f / D_L14_001B04B8));
    base->pairs[index][1] += (1.0f - GetStateProgressFraction(object)) * D_L14_001B04B0
        * FastSinOrCosB(WrapAngleToTwoPi((D_L14_001B04B4 + D_L14_001B04B4) * (GetStateProgressFraction(object) * 3.1415927f)
                                          + (float)phase1 * 3.1415927f / D_L14_001B04B8));
    if (1.0f < base->pairs[index][0])
        base->pairs[index][0] = 1.0f;
    else if (base->pairs[index][0] < 0.0f)
        base->pairs[index][0] = 0.0f;
    if (1.0f < base->pairs[index][1])
        base->pairs[index][1] = 1.0f;
    else if (base->pairs[index][1] < 0.0f)
        base->pairs[index][1] = 0.0f;
}

extern float D_L14_001B04BC __attribute__((sda));
extern s32 D_L14_001B04D4 __attribute__((sda));
extern float D_L14_001B04D8 __attribute__((sda));
extern float D_L14_001B04DC __attribute__((sda));
extern s32 D_L14_001B04E0 __attribute__((sda));
extern s32 D_L14_001B04E4 __attribute__((sda));
extern s32 D_L14_001B04E8 __attribute__((sda));
extern s32 D_L14_001B04EC __attribute__((sda));
extern s32 D_L14_001B04F0 __attribute__((sda));
extern float D_L14_001B04F4 __attribute__((sda));
extern char D_L14_001A8F20[] MACRO_ADDR;

extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern int func_00283D38(int, int, float);
extern char *func_002C7BB8(char *pos, char *vel, int life, int color, int speed, int alpha, int endAlpha,
                           float size, float endSize, float gravity, int kind);

/* Spawns a flash particle: jitters the position at random within the object's scaled radius, blends a
   random opaque colour toward the record's colour (rec+0x84) by the object's fade factor, and spawns it
   with a random life and speed. */
void func_L14_003E2980(char *obj)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    char *rec = *(char **)(obj + 0x68);
    int argb, color, life, red, green, blue;

    qcopy(pos, obj + 0x10);
    pos[0] += RandomFloatRange(D_L14_001B04BC * -GetStateProgressFraction(obj), D_L14_001B04BC * GetStateProgressFraction(obj));
    pos[1] += RandomFloatRange(D_L14_001B04BC * -GetStateProgressFraction(obj), D_L14_001B04BC * GetStateProgressFraction(obj));
    pos[2] += RandomFloatRange(D_L14_001B04BC * -GetStateProgressFraction(obj), 0.0f);
    qcopy(vel, D_L14_001A8F20);
    red = RandomIntRange(0, D_L14_001B04EC);
    green = RandomIntRange(0, D_L14_001B04E8);
    blue = RandomIntRange(0, D_L14_001B04E4);
    argb = 0xFF000000 | (green << 8);
    color = FastTweenColor((red << 16) | argb | blue, *(int *)(rec + 0x84), GetStateProgressFraction(obj));
    life = RandomIntRange(D_L14_001B04D4 / 2, D_L14_001B04D4);
    SpawnSizeChangingParticle((char *)pos, (char *)vel, life, color, RandomIntRange(0, D_L14_001B04E0), 0x80, 0,
                  D_L14_001B04D8, D_L14_001B04DC, D_L14_001B04F4, D_L14_001B04F0);
}
