#include "include_asm.h"
#include "common.h"

typedef int V4 __attribute__((mode(TI)));
typedef union { V4 q; float f[4]; } Vec;

/* The lock-on tether: a chain of twenty points that hangs from the player's hand to up to two
   locked targets, its glow spots and sparks. Only the fields this function touches are named. */
typedef struct Tgt {
    char pad0[0x10];
    float pos[4];                       /* 0x10 */
    unsigned char kind;                 /* 0x20 */
    char pad1[3];
    struct TgtClass *cls;               /* 0x24 */
    char pad2[0x98 - 0x28];
    int f98;                            /* 0x98 */
} Tgt;

typedef struct TgtClass {
    char pad0[0x10];
    int f10;                            /* 0x10 */
    char pad1[0x46 - 0x14];
    short id;                           /* 0x46 */
} TgtClass;

typedef struct Rope {
    float a[4];                         /* 0x00 */
    float b[4];                         /* 0x10 */
    Tgt *lockA;                         /* 0x20 */
    char pad1[0x38 - 0x24];
    Tgt *lockB;                         /* 0x38 */
    short pad2;
    short count;                        /* 0x3E */
    union {
        struct {
            unsigned short h40, h42, h44, h46;
        } s;
        unsigned long q;                /* 0x40 */
    } u;
} Rope;

typedef struct Moby {
    char pad0[0x68];
    Rope *rope;                         /* 0x68 */
    char pad1[0xAA - 0x6C];
    unsigned short tag;                 /* 0xAA */
} Moby;

typedef struct Hit {
    float dir[4];                       /* 0x00 */
    char pad0[0x18 - 0x10];
    unsigned char kind;                 /* 0x18 */
    unsigned char flag;                 /* 0x19 */
    unsigned short tag;                 /* 0x1A */
    char pad1[0x30 - 0x1C];
} Hit;

typedef struct Cam {
    char pad0[0x80];
    float x, y;
    char pad1[0x98 - 0x88];
    float f98;
    char pad2[0x2290 - 0x9C];
    char *ent;
} Cam;

typedef struct Level { char pad0[0x12]; unsigned char cur; } Level;
typedef struct Slot { char pad0[4]; unsigned char on; char pad1[0x70 - 5]; float f70; char pad2[0xE0 - 0x74]; } Slot;

extern Level D_00139568;
extern Slot D_L18_0026BCF0[];
extern Cam D_00189E20;
extern char D_0018A560[];
extern int D_L18_001A8FF0;
extern float D_L18_001A8F20[] MACRO_ADDR;
extern int D_L18_001B30C0;
extern short D_L18_001B30C8[] MACRO_ADDR;
extern short D_L18_001B30D0[] MACRO_ADDR;
extern short D_L18_001B30D8[] MACRO_ADDR;
extern short D_L18_001B30E0[] MACRO_ADDR;
extern float D_L18_001B9680[];
extern char D_L18_001B97C0[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L18_001BFC18;
extern Tgt *D_L18_001FB6E0[];
extern float D_L18_0023A330[][4], D_L18_0023A340[][4];
extern Vec D_L18_0023A350[2][20];
extern V4 D_L18_0023A480;
extern float D_L18_0023A5D0[];
extern Vec D_L18_0023A620[];
extern float D_L18_0023A760[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L18_0023A7A0[];
extern Node5 D_L18_0023A7B0[];

extern float D_L18_001AF014 __attribute__((sda));
extern float D_L18_001AF018 __attribute__((sda));
extern float D_L18_001AF01C __attribute__((sda));
extern float D_L18_001AF020 __attribute__((sda));
extern float D_L18_001AF024 __attribute__((sda));
extern float D_L18_001AF028 __attribute__((sda));
extern float D_L18_001AF02C __attribute__((sda));
extern float D_L18_001AF030 __attribute__((sda));
extern float D_L18_001AF034 __attribute__((sda));
extern float D_L18_001AF038 __attribute__((sda));
extern float D_L18_001AF03C __attribute__((sda));
extern float D_L18_001AF040 __attribute__((sda));
extern float D_L18_001AF044 __attribute__((sda));
extern float D_L18_001AF048 __attribute__((sda));
extern float D_L18_001AF04C __attribute__((sda));
extern float D_L18_001AF050 __attribute__((sda));
extern float D_L18_001AF064 __attribute__((sda));
extern float D_L18_001AF068 __attribute__((sda));
extern float D_L18_001AF0A8 __attribute__((sda));
extern float D_L18_001AF0AC __attribute__((sda));
extern int D_L18_001AF078 __attribute__((sda));

extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277F48(void *, int, char *, void *, float);
extern int func_00282948(void *);
extern int func_00282978(void *);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E20(void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002831B0(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern float *func_002AB1F0(void *);
extern float func_002ABB18(float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern void func_00300190(void *, void *);

/* Updates the lock-on tether each frame: picks up to two targets in front of the player, swings a chain of points between the player and them, and spawns the glow and spark effects. */
void func_L18_003B12C0(Moby *self)
{
    int locked = D_L18_0026BCF0[gItemSlotToRecord.cur].on != 0;
    float reach = D_L18_001AF014 * 0.05f;
    Rope *st = self->rope;
    float aimPointA[4] __attribute__((aligned(16)));
    float tempVecA[4] __attribute__((aligned(16)));
    float tempVecB[4] __attribute__((aligned(16)));
    Hit hit1 __attribute__((aligned(16)));
    float ropeDir[4] __attribute__((aligned(16)));
    float segDelta[4] __attribute__((aligned(16)));
    float segStep[4] __attribute__((aligned(16)));
    float segCarry[4] __attribute__((aligned(16)));
    float sparkOffset[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float scratchVec[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hitBuf __attribute__((aligned(16)));
    float jitter[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int got, nheld;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int n;
    Tgt *t;
    int sn;
    float dist, ang, sa2, cs, sm, score, proj, fa, fb;
    float distToLockA;
    float *ia, *ib;
    Tgt *ta, *tb;
    float length, blend;
    float amp, height, angle, old, cd;
    int fa2;
    Tgt *ht;
    float *hinfo;
    float *tv, apj, *ainfo;
    int an;
    float bpj, *binfo;
    int bn;
    float ksize, kf, ks;
    int j1, j2;
    float *q;
    int spin;
    float tsize, cd2;
    Vec *prev;
    float proj2, cm2;
    /* Declared here, not in its block: k's pseudo number sets the bucket of k + 1 in the
       gcse hash, which orders the spill slots at 0x394 and 0x398. */
    short fade;
    int k;

    D_L18_001AF02C = FastAddRotations(D_L18_001AF02C, D_L18_001AF030);
    D_L18_001AF034 = fast_subtract_rotations(D_L18_001AF034, D_L18_001AF038);
    D_L18_001AF048 = FastAddRotations(D_L18_001AF048, D_L18_001AF04C);

    if (st->lockA == 0 || (locked && st->lockB == 0)) {
        if (st->lockB != 0) {
            st->lockA = st->lockB;
            st->u.s.h40 = st->u.s.h42;
            st->lockB = 0;
            st->u.s.h42 = 0;
        } else {
            sn = 0;
            for (t = D_L18_001FB6E0[0]; t != 0; t = D_L18_001FB6E0[++sn]) {
                if (t != st->lockA && t != st->lockB) {
                    if (t != 0 && t->cls != 0 && t->cls->id == 5) {
                        if (t->kind != 0xFE) {
                        if (t->kind != 0xFD) {
                            if (GetMobyPrivateValue0(t) != 0) {
                                FastVecSub(aimPointA, t->pos, st);
                                if (D_L18_001A8FF0 != 0) {
                                    proj = FastVecDot(aimPointA, gHeroState.ent + 0xE0);
                                    FastVecScale(tempVecA, gHeroState.ent + 0xE0, proj);
                                    FastVecSub(tempVecB, aimPointA, tempVecA);
                                    dist = FastVecLength(tempVecB);
                                } else {
                                    dist = vec_length_xy(aimPointA);
                                }
                                if (!(D_L18_001AF014 < dist)) {
                                    ang = FastDiffRots(D_L18_001B9680[0x158 / 4], FastMatrixHelperA(t->pos[0] - D_L18_001B9680[0x140 / 4], t->pos[1] - D_L18_001B9680[0x144 / 4]));
                                    if (!(D_L18_001AF01C < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sa2 = 0.0f;
                                        if (D_L18_001A8FF0 != 0) {
                                            FastVecSub(tempVecA, t->pos, &gHeroState.x);
                                            proj2 = FastVecDot(tempVecA, gHeroState.ent + 0xE0);
                                            FastVecScale(tempVecB, gHeroState.ent + 0xE0, proj2);
                                            FastVecSub(tempVecA, tempVecA, tempVecB);
                                            cs = FastVecDot(tempVecA, gHeroState.ent + 0xC0);
                                            sm = FastVecLength(tempVecA);
                                            if (sm == 0.0f)
                                                continue;
                                            sa2 = 1.5707964f - FastAngleHelper(cs / sm);
                                        } else {
                                            sa2 = FastDiffRots(FastMatrixHelperA(t->pos[0] - gHeroState.x, t->pos[1] - gHeroState.y), gHeroState.f98);
                                        }
                                            if (!(D_L18_001AF018 < sa2)) {
                                                fa = (D_L18_001AF01C - ang) / D_L18_001AF01C;
                                                fb = (D_L18_001AF014 - dist) / D_L18_001AF014;
                                                score = fa * D_L18_001AF0AC + fb;
                                                if (bestScore < score) {
                                                    secondScore = bestScore;
                                                    bestScore = score;
                                                    second = best;
                                                    best = t;
                                                } else if (secondScore < score) {
                                                    second = t;
                                                    secondScore = score;
                                                }
                                            }
                                    }
                                }
                            }
                        }
                        }
                    }
                }
            }
        }
    }

    if (best != 0) {
        if (st->lockA != 0) {
            second = best;
        } else {
            st->lockA = best;
            st->u.s.h40 = 0;
            if (FastFloatHelperD(&D_L18_001B30C0) != 0)
                D_L18_001B30C0 = 0xA;
        }
    }
    if (second != 0 && locked) {
        distToLockA = fast_vec_dist(st, best->pos);
        if (distToLockA < D_L18_001AF014 && distToLockA + fast_vec_dist(best->pos, second->pos) < D_L18_001AF014) {
            st->u.s.h42 = 0;
            st->lockB = second;
        }
    }
    len = 0.0f;
    if (st->lockA != 0) {
        ia = GetMobyPrivateValue0(st->lockA);
        ta = st->lockA;
        qcopy(aimPointA, ta->pos);
        FastVecScale(tempVecA, (char *)ta + 0xE0, ia[4]);
        FastVecAdd(aimPointA, aimPointA, tempVecA);
        len = fast_vec_dist(st, aimPointA);
        reach = len * 0.05f;
    }
    if (st->lockB != 0) {
        ib = GetMobyPrivateValue0(st->lockB);
        tb = st->lockB;
        qcopy(tempVecA, tb->pos);
        FastVecScale(tempVecB, (char *)tb + 0xE0, ib[4]);
        FastVecAdd(tempVecA, tempVecA, tempVecB);
        reach = (fast_vec_dist(aimPointA, tempVecA) + len) * 0.05f;
    }
    if (locked)
        D_L18_001AF078 = 0x207F20;
    else
        D_L18_001AF078 = 0x7F2020;
    ClearVector128(tempVecB);
    make_hit_descriptor(&hit1, self, 0x210000, tempVecB, (&D_L18_0026BCF0[gItemSlotToRecord.cur])->f70);
    hit1.kind = 5;
    hit1.flag = 1;
    hit1.tag = self->tag;
    st->count = 0x14;
    ProcessCollisionHit(st, 0x10, gHeroState.ent, &hit1, 0.3f);
    FastVecSub(ropeDir, st->b, st);
    vec_scale_to_length(ropeDir, ropeDir, 1.0f);
    if (st->lockA != 0 || st->lockB != 0) {
        FastVecCross(segDelta, ropeDir, (char *)&gHeroState + 0x2C0);
        ApplyAxisRotationToQuaternion(ropeDir, ropeDir, segDelta, 0.17453295f);
    }
    got = 0;
    FastVecScale(segCarry, ropeDir, reach);
    nheld = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = st->a;
        qcopy(&D_L18_0023A350[0][0], anchor);
    }
    {
        float *anchor = st->a;
        qcopy(&D_L18_0023A350[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L18_001AF024 + (D_L18_001AF028 - D_L18_001AF024) * (IntToFloat(i) * 0.05f);
        height = amp * FastSinOrCosB(WrapAngleToPi(D_L18_001AF02C + (float)i * D_L18_001AF020));
        height += RandomSignedFloatRange(D_L18_001AF064, D_L18_001AF068);
        old = D_L18_0023A5D0[i];
        D_L18_0023A5D0[i] = height;
        D_L18_0023A350[0][i].f[2] = D_L18_0023A350[0][i].f[2] - old;
        TransformVectorOrCopy(&D_L18_0023A350[0][i], &D_L18_0023A350[0][i]);
        FastVecSub(segDelta, &D_L18_0023A350[0][i], D_L18_0023A340[i]);
        lerp_vector(segStep, segDelta, segCarry, 0.85f);
        {
            float cm = FastVecLength(segStep);
            if (cm == 0.0f) {
                prev = &D_L18_0023A350[0][i - 1];
                qcopy(&D_L18_0023A350[0][i], prev);
            } else {
                FastVecScale(segStep, segStep, reach / cm);
                FastVecAdd(&D_L18_0023A350[0][i], D_L18_0023A340[i], segStep);
                qcopy(segCarry, segStep);
            }
        }
        D_L18_0023A350[0][i].f[2] = D_L18_0023A350[0][i].f[2] + height;
        FastVecSub(segDelta, &D_L18_0023A350[0][i], D_L18_0023A340[i]);
        if (st->lockA != 0) {
            if (!locked || st->lockB == 0) {
                FastVecSub(scratchVec, aimPointA, &D_L18_0023A350[0][i]);
                length = FastVecLength(scratchVec);
                if (length != 0.0f) {
                    if (i == 0x13) {
                        blend = 0.5f;
                        reach = length;
                    } else if (i >= 0x10) {
                        blend = 0.5f;
                        cd = IntToFloat(0x13 - i);
                        reach = length / cd;
                    } else {
                        blend = 0.1f;
                    }
                    FastVecScale(scratchVec, scratchVec, reach / length);
                    lerp_vector(segCarry, segCarry, scratchVec, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(scratchVec, tempVecA, &D_L18_0023A350[0][i]);
                else
                    FastVecSub(scratchVec, aimPointA, &D_L18_0023A350[0][i]);
                length = FastVecLength(scratchVec);
                if (length != 0.0f) {
                    if (i == 9 || i == 0x13) {
                        blend = 0.7f;
                        reach = length;
                    } else if (i >= 5 && i < 10) {
                        blend = 0.7f;
                        cd = IntToFloat(9 - i);
                        reach = length / cd;
                    } else if (i >= 0xF) {
                        blend = 0.7f;
                        cd2 = IntToFloat(0x13 - i);
                        reach = length / cd2;
                    } else {
                        blend = 0.2f;
                    }
                    FastVecScale(scratchVec, scratchVec, reach / length);
                    lerp_vector(segCarry, segCarry, scratchVec, blend);
                }
            }
        }
        if (i < 10) {
            angle = WrapAngleToPi(D_L18_001AF034 + (float)i * D_L18_001AF03C);
            amp = D_L18_001AF040 * FastSinOrCosB(WrapAngleToPi(D_L18_001AF048 + (float)i * D_L18_001AF050));
            qcopy(&D_L18_0023A350[1][i], &D_L18_0023A350[0][i]);
            height = amp * FastSinOrCosB(angle) + RandomSignedFloatRange(0.0f, 0.1f);
            D_L18_0023A760[i] = height;
            D_L18_0023A350[1][i].f[2] = D_L18_0023A350[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(FastMatrixHelperA(segDelta[0], segDelta[1]), 1.5707965f);
                {
                    float radial = D_L18_001AF044 * FastSinOrCosA(angle);
                    sparkOffset[0] = FastSinOrCosA(bearing) * radial;
                    sparkOffset[1] = FastSinOrCosB(bearing) * radial;
                    sparkOffset[2] = 0.0f;
                    qcopy_nc(&D_L18_0023A620[i], sparkOffset);
                }
            }
            FastVecAdd(&D_L18_0023A350[1][i], &D_L18_0023A350[1][i], sparkOffset);
        } else {
            fa2 = 0x15 - i;
            qcopy(&D_L18_0023A350[1][i], &D_L18_0023A350[0][i]);
            D_L18_0023A350[1][i].f[2] = D_L18_0023A350[1][i].f[2] + D_L18_0023A760[fa2];
            FastVecAdd(&D_L18_0023A350[1][i], &D_L18_0023A350[1][i], &D_L18_0023A620[fa2]);
            qcopy(sparkOffset, &D_L18_0023A620[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(tempVecB, &D_L18_0023A350[0][i], gCameraPosition_L18);
            if (D_L18_001A8FF0 != 0) {
                float cpj = FastVecDot(tempVecB, gHeroState.ent + 0xE0);
                {
                    char *ax = gHeroState.ent + 0xE0;
                    FastVecScale(scratchVec, ax, cpj);
                    FastVecSub(tempVecB, tempVecB, scratchVec);
                }
            } else {
                *(int *)&tempVecB[2] = 0;
            }
            cm2 = FastVecLength(tempVecB);
            if (cm2 == 0.0f)
                tempVecB[2] = 1.0f;
            else
                FastVecScale(tempVecB, tempVecB, 1.0f / cm2);
            tempVecB[3] = 5627.925f;
            qcopy(&hit1, tempVecB);
            got = CollLine(D_L18_0023A330[i], &D_L18_0023A350[0][i], 0x10, self, 0);
            if (got != 0) {
                ht = D_L18_001BFC18.hit;
                if (ht != 0) {
                    hinfo = GetMobyPrivateValue0(ht);
                    if (hinfo == 0) {
                        QueueMobyImpact(ht, &hit1);
                    } else if (ht->cls == 0 || ht->cls->id != 5) {
                        QueueMobyImpact(ht, &hit1);
                    } else {
                        got = 0;
                        held[nheld++] = ht;
                        ht->f98 = 0;
                    }
                }
                if (got != 0) {
                    qcopy(&D_L18_0023A350[0][i], D_L18_001BFC18.pos);
                    {
                        short last = i;
                        st->count = last;
                    }
                    qcopy(st->b, D_L18_001BFC18.pos);
                    if (D_L18_001BFC18.hit == 0) {
                        st->lockA = 0;
                        st->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (n = 0; n < nheld; n++)
        held[n]->f98 = held[n]->cls->f10;
    if (got == 0)
        qcopy(st->b, &D_L18_0023A480);
    if (st->lockA != 0 && (st->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hitBuf.q;
        FastVecSub(scratchVec, st->lockA->pos, gCameraPosition_L18);
        if (D_L18_001A8FF0 != 0) {
            apj = FastVecDot(scratchVec, gHeroState.ent + 0xE0);
            FastVecScale(tv, gHeroState.ent + 0xE0, apj);
            FastVecSub(scratchVec, scratchVec, tv);
        } else {
            *(int *)&scratchVec[2] = 0;
        }
        vec_scale_to_length(scratchVec, scratchVec, 1.0f);
        scratchVec[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.a.r, self, 0x210000, scratchVec, (&D_L18_0026BCF0[gItemSlotToRecord.cur])->f70);
        hitBuf.a.r.kind = 5;
        hitBuf.a.r.flag = 3;
        hitBuf.a.r.tag = self->tag;
        an = 5;
        QueueMobyImpact(st->lockA, &hitBuf.a.r);
        ainfo = GetMobyPrivateValue0(st->lockA);
        if (ainfo != 0) {
            if (((short *)ainfo)[2] == 1)
                an = 1;
        }
        {
            short result = an;
            st->u.s.h44 = result;
        }
    }
    if (st->lockB != 0 && (st->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(scratchVec, st->lockB->pos, gCameraPosition_L18);
        if (D_L18_001A8FF0 != 0) {
            bpj = FastVecDot(scratchVec, gHeroState.ent + 0xE0);
            FastVecScale(hitBuf.q, gHeroState.ent + 0xE0, bpj);
            FastVecSub(scratchVec, scratchVec, hitBuf.q);
        } else {
            *(int *)&scratchVec[2] = 0;
        }
        vec_scale_to_length(scratchVec, scratchVec, 1.0f);
        scratchVec[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.b.r, self, 0x210000, scratchVec, (&D_L18_0026BCF0[gItemSlotToRecord.cur])->f70);
        hitBuf.b.r.kind = 5;
        hitBuf.b.r.flag = 3;
        hitBuf.b.r.tag = self->tag;
        bn = 5;
        QueueMobyImpact(st->lockB, &hitBuf.b.r);
        binfo = GetMobyPrivateValue0(st->lockB);
        if (binfo != 0) {
            if (((short *)binfo)[2] == 1)
                bn = 1;
        }
        {
            short result = bn;
            st->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = st->a;
                qcopy(hitBuf.q, from);
            }
            ksize = 0.4f;
        } else {
            qcopy(hitBuf.q, st->b);
            ksize = 0.5f;
        }
        if (FastDecTimer(&D_L18_001B30C8[k]) != 0) {
            D_L18_001B30C8[k] = D_L18_001B30D8[k];
            D_L18_001B30D0[k] = 0;
            angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
            angle1 = RandomFloatRange(-1.0471977f, 0.17453295f);
            FastVecScale(scratchVec, ropeDir, ksize);
            ApplyAxisRotationToQuaternion(scratchVec, scratchVec, D_0018A560, angle1);
            ApplyAxisRotationToQuaternion(scratchVec, scratchVec, D_0018A560 + 0x10, angle0);
            qcopy(&D_L18_0023A7B0[k].v[0], hitBuf.q);
            ks = 1.0f;
            FastVecAdd(&D_L18_0023A7B0[k].v[1], hitBuf.q, scratchVec);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hitBuf.q + 4, &D_L18_0023A7A0[k].p[j1 - 1], gCameraPosition_L18);
                kf = RandomFloatRange(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                ApplyAxisRotationToQuaternion(scratchVec, scratchVec, hitBuf.q + 4, kf);
                FastVecAdd(D_L18_0023A7B0[k].v + j1, &D_L18_0023A7A0[k].p[j1 - 1], scratchVec);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = jitter[j2];
                FastVecSub(q, D_L18_0023A7B0[k].v + j2, &D_L18_0023A7A0[k].p[j2 - 1]);
                q[0] = q[0] + RandomSignedFloatRange(0.0f, 0.1f);
                q[1] = q[1] + RandomSignedFloatRange(0.0f, 0.1f);
                q[2] = q[2] + RandomSignedFloatRange(0.0f, 0.1f);
            }
            qcopy(&D_L18_0023A7B0[k].v[0], hitBuf.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(D_L18_0023A7B0[k].v + j2, &D_L18_0023A7A0[k].p[j2 - 1], jitter[j2]);
            {
                int x = D_L18_001B30E0[k];
                int y = D_L18_001B30C8[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                D_L18_001B30D0[k] = fade;
            }
        }
    }
    {
        angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
        angle1 = RandomFloatRange(-0.52359885f, 1.0471977f);
        FastVecScale(scratchVec, ropeDir, D_L18_001AF0A8);
        ApplyAxisRotationToQuaternion(scratchVec, scratchVec, D_0018A560, angle1);
        ApplyAxisRotationToQuaternion(scratchVec, scratchVec, D_0018A560 + 0x10, angle0);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.2f, 0.6f);
        SpawnGroundEffectParticle(st, 0xF, tsize * 0.3f, tsize, D_L18_001AF078 | 0x7F000000, 0, spin, scratchVec, 1, 0.0f);
        spin = -spin;
        SpawnGroundEffectParticle(st, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, scratchVec, 1, 0.0f);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.15f, 3.0f);
        SpawnGroundEffectParticle(st->b, 0xC, tsize * 0.1f, tsize, D_L18_001AF078 | 0x7F000000, 0, spin, D_L18_001A8F20, 1, 0.0f);
    }
}
