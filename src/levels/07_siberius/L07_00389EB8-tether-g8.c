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
extern Slot D_L07_002628A0[];
extern Cam D_00189E20;
extern char D_0018A560[];
extern int D_L07_001A8FF0;
extern float D_L07_001A8F20[] MACRO_ADDR;
extern int D_L07_001B2BA0;
extern short D_L07_001B2BA8[] MACRO_ADDR;
extern short D_L07_001B2BB0[] MACRO_ADDR;
extern short D_L07_001B2BB8[] MACRO_ADDR;
extern short D_L07_001B2BC0[] MACRO_ADDR;
extern float D_L07_001B90C0[];
extern char D_L07_001B9200[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L07_001BF658;
extern Tgt *D_L07_001FB120[];
extern float D_L07_00239D70[][4], D_L07_00239D80[][4];
extern Vec D_L07_00239D90[2][20];
extern V4 D_L07_00239EC0;
extern float D_L07_0023A010[];
extern Vec D_L07_0023A060[];
extern float D_L07_0023A1A0[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L07_0023A1E0[];
extern Node5 D_L07_0023A1F0[];

extern float D_L07_001AF0E4 __attribute__((sda));
extern float D_L07_001AF0E8 __attribute__((sda));
extern float D_L07_001AF0EC __attribute__((sda));
extern float D_L07_001AF0F0 __attribute__((sda));
extern float D_L07_001AF0F4 __attribute__((sda));
extern float D_L07_001AF0F8 __attribute__((sda));
extern float D_L07_001AF0FC __attribute__((sda));
extern float D_L07_001AF100 __attribute__((sda));
extern float D_L07_001AF104 __attribute__((sda));
extern float D_L07_001AF108 __attribute__((sda));
extern float D_L07_001AF10C __attribute__((sda));
extern float D_L07_001AF110 __attribute__((sda));
extern float D_L07_001AF114 __attribute__((sda));
extern float D_L07_001AF118 __attribute__((sda));
extern float D_L07_001AF11C __attribute__((sda));
extern float D_L07_001AF120 __attribute__((sda));
extern float D_L07_001AF134 __attribute__((sda));
extern float D_L07_001AF138 __attribute__((sda));
extern float D_L07_001AF178 __attribute__((sda));
extern float D_L07_001AF17C __attribute__((sda));
extern int D_L07_001AF148 __attribute__((sda));

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

/* Per-frame update of the lock-on tether: picks up to two targets, lays out the twenty-point
   chain with waves and collision, and spawns sparks. */
void func_L07_00389EB8(Moby *self)
{
    int locked = D_L07_002628A0[gItemSlotToRecord.cur].on != 0;
    float reach = D_L07_001AF0E4 * 0.05f;
    Rope *st = self->rope;
    float targetPointA[4] __attribute__((aligned(16)));
    float targetPointB[4] __attribute__((aligned(16)));
    float scratchVec[4] __attribute__((aligned(16)));
    Hit shotQuery __attribute__((aligned(16)));
    float aimDir[4] __attribute__((aligned(16)));
    float linkOffset[4] __attribute__((aligned(16)));
    float stepVec[4] __attribute__((aligned(16)));
    float chainDir[4] __attribute__((aligned(16)));
    float sideShift[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float tempVec[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hitBuf __attribute__((aligned(16)));
    float jitter[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int hitSomething, heldCount;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int heldIdx;
    Tgt *candidate;
    int scanIdx;
    float dist, ang, sideAngle, cosPart, sideLen, score, proj, fa, fb;
    float distToBest;
    float *infoA, *infoB;
    Tgt *targetA, *targetB;
    float length, blend;
    float amp, height, angle, old, cd;
    int mirrorIdx;
    Tgt *hitTarget;
    float *hitInfo;
    float *projBuf, projA, *classInfoA;
    int hitCodeA;
    float projB, *classInfoB;
    int hitCodeB;
    float ksize, kf, ks;
    int j1, j2;
    float *q;
    int spin;
    float tsize, cd2;
    Vec *prev;
    float proj2, rayLen;
    /* Declared here, not in its block: k's pseudo number sets the bucket of k + 1 in the
       gcse hash, which orders the spill slots at 0x394 and 0x398. */
    short fade;
    int k;

    D_L07_001AF0FC = FastAddRotations(D_L07_001AF0FC, D_L07_001AF100);
    D_L07_001AF104 = fast_subtract_rotations(D_L07_001AF104, D_L07_001AF108);
    D_L07_001AF118 = FastAddRotations(D_L07_001AF118, D_L07_001AF11C);

    if (st->lockA == 0 || (locked && st->lockB == 0)) {
        if (st->lockB != 0) {
            st->lockA = st->lockB;
            st->u.s.h40 = st->u.s.h42;
            st->lockB = 0;
            st->u.s.h42 = 0;
        } else {
            scanIdx = 0;
            for (candidate = D_L07_001FB120[0]; candidate != 0; candidate = D_L07_001FB120[++scanIdx]) {
                if (candidate != st->lockA && candidate != st->lockB) {
                    if (candidate != 0 && candidate->cls != 0 && candidate->cls->id == 5) {
                        if (candidate->kind != 0xFE) {
                        if (candidate->kind != 0xFD) {
                            if (GetMobyPrivateValue0(candidate) != 0) {
                                FastVecSub(targetPointA, candidate->pos, st);
                                if (D_L07_001A8FF0 != 0) {
                                    proj = FastVecDot(targetPointA, gHeroState.ent + 0xE0);
                                    FastVecScale(targetPointB, gHeroState.ent + 0xE0, proj);
                                    FastVecSub(scratchVec, targetPointA, targetPointB);
                                    dist = FastVecLength(scratchVec);
                                } else {
                                    dist = vec_length_xy(targetPointA);
                                }
                                if (!(D_L07_001AF0E4 < dist)) {
                                    ang = FastDiffRots(D_L07_001B90C0[0x158 / 4], FastMatrixHelperA(candidate->pos[0] - D_L07_001B90C0[0x140 / 4], candidate->pos[1] - D_L07_001B90C0[0x144 / 4]));
                                    if (!(D_L07_001AF0EC < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sideAngle = 0.0f;
                                        if (D_L07_001A8FF0 != 0) {
                                            FastVecSub(targetPointB, candidate->pos, &gHeroState.x);
                                            proj2 = FastVecDot(targetPointB, gHeroState.ent + 0xE0);
                                            FastVecScale(scratchVec, gHeroState.ent + 0xE0, proj2);
                                            FastVecSub(targetPointB, targetPointB, scratchVec);
                                            cosPart = FastVecDot(targetPointB, gHeroState.ent + 0xC0);
                                            sideLen = FastVecLength(targetPointB);
                                            if (sideLen == 0.0f)
                                                continue;
                                            sideAngle = 1.5707964f - FastAngleHelper(cosPart / sideLen);
                                        } else {
                                            sideAngle = FastDiffRots(FastMatrixHelperA(candidate->pos[0] - gHeroState.x, candidate->pos[1] - gHeroState.y), gHeroState.f98);
                                        }
                                            if (!(D_L07_001AF0E8 < sideAngle)) {
                                                fa = (D_L07_001AF0EC - ang) / D_L07_001AF0EC;
                                                fb = (D_L07_001AF0E4 - dist) / D_L07_001AF0E4;
                                                score = fa * D_L07_001AF17C + fb;
                                                if (bestScore < score) {
                                                    secondScore = bestScore;
                                                    bestScore = score;
                                                    second = best;
                                                    best = candidate;
                                                } else if (secondScore < score) {
                                                    second = candidate;
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
            if (FastFloatHelperD(&D_L07_001B2BA0) != 0)
                D_L07_001B2BA0 = 0xA;
        }
    }
    if (second != 0 && locked) {
        distToBest = fast_vec_dist(st, best->pos);
        if (distToBest < D_L07_001AF0E4 && distToBest + fast_vec_dist(best->pos, second->pos) < D_L07_001AF0E4) {
            st->u.s.h42 = 0;
            st->lockB = second;
        }
    }
    len = 0.0f;
    if (st->lockA != 0) {
        infoA = GetMobyPrivateValue0(st->lockA);
        targetA = st->lockA;
        qcopy(targetPointA, targetA->pos);
        FastVecScale(targetPointB, (char *)targetA + 0xE0, infoA[4]);
        FastVecAdd(targetPointA, targetPointA, targetPointB);
        len = fast_vec_dist(st, targetPointA);
        reach = len * 0.05f;
    }
    if (st->lockB != 0) {
        infoB = GetMobyPrivateValue0(st->lockB);
        targetB = st->lockB;
        qcopy(targetPointB, targetB->pos);
        FastVecScale(scratchVec, (char *)targetB + 0xE0, infoB[4]);
        FastVecAdd(targetPointB, targetPointB, scratchVec);
        reach = (fast_vec_dist(targetPointA, targetPointB) + len) * 0.05f;
    }
    if (locked)
        D_L07_001AF148 = 0x207F20;
    else
        D_L07_001AF148 = 0x7F2020;
    ClearVector128(scratchVec);
    make_hit_descriptor(&shotQuery, self, 0x210000, scratchVec, (&D_L07_002628A0[gItemSlotToRecord.cur])->f70);
    shotQuery.kind = 5;
    shotQuery.flag = 1;
    shotQuery.tag = self->tag;
    st->count = 0x14;
    ProcessCollisionHit(st, 0x10, gHeroState.ent, &shotQuery, 0.3f);
    FastVecSub(aimDir, st->b, st);
    vec_scale_to_length(aimDir, aimDir, 1.0f);
    if (st->lockA != 0 || st->lockB != 0) {
        FastVecCross(linkOffset, aimDir, (char *)&gHeroState + 0x2C0);
        ApplyAxisRotationToQuaternion(aimDir, aimDir, linkOffset, 0.17453295f);
    }
    hitSomething = 0;
    FastVecScale(chainDir, aimDir, reach);
    heldCount = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = st->a;
        qcopy(&D_L07_00239D90[0][0], anchor);
    }
    {
        float *anchor = st->a;
        qcopy(&D_L07_00239D90[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L07_001AF0F4 + (D_L07_001AF0F8 - D_L07_001AF0F4) * (IntToFloat(i) * 0.05f);
        height = amp * FastSinOrCosB(WrapAngleToPi(D_L07_001AF0FC + (float)i * D_L07_001AF0F0));
        height += RandomSignedFloatRange(D_L07_001AF134, D_L07_001AF138);
        old = D_L07_0023A010[i];
        D_L07_0023A010[i] = height;
        D_L07_00239D90[0][i].f[2] = D_L07_00239D90[0][i].f[2] - old;
        TransformVectorOrCopy(&D_L07_00239D90[0][i], &D_L07_00239D90[0][i]);
        FastVecSub(linkOffset, &D_L07_00239D90[0][i], D_L07_00239D80[i]);
        lerp_vector(stepVec, linkOffset, chainDir, 0.85f);
        {
            float chainLen = FastVecLength(stepVec);
            if (chainLen == 0.0f) {
                prev = &D_L07_00239D90[0][i - 1];
                qcopy(&D_L07_00239D90[0][i], prev);
            } else {
                FastVecScale(stepVec, stepVec, reach / chainLen);
                FastVecAdd(&D_L07_00239D90[0][i], D_L07_00239D80[i], stepVec);
                qcopy(chainDir, stepVec);
            }
        }
        D_L07_00239D90[0][i].f[2] = D_L07_00239D90[0][i].f[2] + height;
        FastVecSub(linkOffset, &D_L07_00239D90[0][i], D_L07_00239D80[i]);
        if (st->lockA != 0) {
            if (!locked || st->lockB == 0) {
                FastVecSub(tempVec, targetPointA, &D_L07_00239D90[0][i]);
                length = FastVecLength(tempVec);
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
                    FastVecScale(tempVec, tempVec, reach / length);
                    lerp_vector(chainDir, chainDir, tempVec, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(tempVec, targetPointB, &D_L07_00239D90[0][i]);
                else
                    FastVecSub(tempVec, targetPointA, &D_L07_00239D90[0][i]);
                length = FastVecLength(tempVec);
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
                    FastVecScale(tempVec, tempVec, reach / length);
                    lerp_vector(chainDir, chainDir, tempVec, blend);
                }
            }
        }
        if (i < 10) {
            angle = WrapAngleToPi(D_L07_001AF104 + (float)i * D_L07_001AF10C);
            amp = D_L07_001AF110 * FastSinOrCosB(WrapAngleToPi(D_L07_001AF118 + (float)i * D_L07_001AF120));
            qcopy(&D_L07_00239D90[1][i], &D_L07_00239D90[0][i]);
            height = amp * FastSinOrCosB(angle) + RandomSignedFloatRange(0.0f, 0.1f);
            D_L07_0023A1A0[i] = height;
            D_L07_00239D90[1][i].f[2] = D_L07_00239D90[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(FastMatrixHelperA(linkOffset[0], linkOffset[1]), 1.5707965f);
                {
                    float radial = D_L07_001AF114 * FastSinOrCosA(angle);
                    sideShift[0] = FastSinOrCosA(bearing) * radial;
                    sideShift[1] = FastSinOrCosB(bearing) * radial;
                    sideShift[2] = 0.0f;
                    qcopy_nc(&D_L07_0023A060[i], sideShift);
                }
            }
            FastVecAdd(&D_L07_00239D90[1][i], &D_L07_00239D90[1][i], sideShift);
        } else {
            mirrorIdx = 0x15 - i;
            qcopy(&D_L07_00239D90[1][i], &D_L07_00239D90[0][i]);
            D_L07_00239D90[1][i].f[2] = D_L07_00239D90[1][i].f[2] + D_L07_0023A1A0[mirrorIdx];
            FastVecAdd(&D_L07_00239D90[1][i], &D_L07_00239D90[1][i], &D_L07_0023A060[mirrorIdx]);
            qcopy(sideShift, &D_L07_0023A060[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(scratchVec, &D_L07_00239D90[0][i], D_L07_001B9200);
            if (D_L07_001A8FF0 != 0) {
                float rayProj = FastVecDot(scratchVec, gHeroState.ent + 0xE0);
                {
                    char *upAxis = gHeroState.ent + 0xE0;
                    FastVecScale(tempVec, upAxis, rayProj);
                    FastVecSub(scratchVec, scratchVec, tempVec);
                }
            } else {
                *(int *)&scratchVec[2] = 0;
            }
            rayLen = FastVecLength(scratchVec);
            if (rayLen == 0.0f)
                scratchVec[2] = 1.0f;
            else
                FastVecScale(scratchVec, scratchVec, 1.0f / rayLen);
            scratchVec[3] = 5627.925f;
            qcopy(&shotQuery, scratchVec);
            hitSomething = CollLine(D_L07_00239D70[i], &D_L07_00239D90[0][i], 0x10, self, 0);
            if (hitSomething != 0) {
                hitTarget = D_L07_001BF658.hit;
                if (hitTarget != 0) {
                    hitInfo = GetMobyPrivateValue0(hitTarget);
                    if (hitInfo == 0) {
                        QueueMobyImpact(hitTarget, &shotQuery);
                    } else if (hitTarget->cls == 0 || hitTarget->cls->id != 5) {
                        QueueMobyImpact(hitTarget, &shotQuery);
                    } else {
                        hitSomething = 0;
                        held[heldCount++] = hitTarget;
                        hitTarget->f98 = 0;
                    }
                }
                if (hitSomething != 0) {
                    qcopy(&D_L07_00239D90[0][i], D_L07_001BF658.pos);
                    {
                        short last = i;
                        st->count = last;
                    }
                    qcopy(st->b, D_L07_001BF658.pos);
                    if (D_L07_001BF658.hit == 0) {
                        st->lockA = 0;
                        st->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (heldIdx = 0; heldIdx < heldCount; heldIdx++)
        held[heldIdx]->f98 = held[heldIdx]->cls->f10;
    if (hitSomething == 0)
        qcopy(st->b, &D_L07_00239EC0);
    if (st->lockA != 0 && (st->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        projBuf = hitBuf.q;
        FastVecSub(tempVec, st->lockA->pos, D_L07_001B9200);
        if (D_L07_001A8FF0 != 0) {
            projA = FastVecDot(tempVec, gHeroState.ent + 0xE0);
            FastVecScale(projBuf, gHeroState.ent + 0xE0, projA);
            FastVecSub(tempVec, tempVec, projBuf);
        } else {
            *(int *)&tempVec[2] = 0;
        }
        vec_scale_to_length(tempVec, tempVec, 1.0f);
        tempVec[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.a.r, self, 0x210000, tempVec, (&D_L07_002628A0[gItemSlotToRecord.cur])->f70);
        hitBuf.a.r.kind = 5;
        hitBuf.a.r.flag = 3;
        hitBuf.a.r.tag = self->tag;
        hitCodeA = 5;
        QueueMobyImpact(st->lockA, &hitBuf.a.r);
        classInfoA = GetMobyPrivateValue0(st->lockA);
        if (classInfoA != 0) {
            if (((short *)classInfoA)[2] == 1)
                hitCodeA = 1;
        }
        {
            short result = hitCodeA;
            st->u.s.h44 = result;
        }
    }
    if (st->lockB != 0 && (st->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(tempVec, st->lockB->pos, D_L07_001B9200);
        if (D_L07_001A8FF0 != 0) {
            projB = FastVecDot(tempVec, gHeroState.ent + 0xE0);
            FastVecScale(hitBuf.q, gHeroState.ent + 0xE0, projB);
            FastVecSub(tempVec, tempVec, hitBuf.q);
        } else {
            *(int *)&tempVec[2] = 0;
        }
        vec_scale_to_length(tempVec, tempVec, 1.0f);
        tempVec[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.b.r, self, 0x210000, tempVec, (&D_L07_002628A0[gItemSlotToRecord.cur])->f70);
        hitBuf.b.r.kind = 5;
        hitBuf.b.r.flag = 3;
        hitBuf.b.r.tag = self->tag;
        hitCodeB = 5;
        QueueMobyImpact(st->lockB, &hitBuf.b.r);
        classInfoB = GetMobyPrivateValue0(st->lockB);
        if (classInfoB != 0) {
            if (((short *)classInfoB)[2] == 1)
                hitCodeB = 1;
        }
        {
            short result = hitCodeB;
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
        if (FastDecTimer(&D_L07_001B2BA8[k]) != 0) {
            D_L07_001B2BA8[k] = D_L07_001B2BB8[k];
            D_L07_001B2BB0[k] = 0;
            angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
            angle1 = RandomFloatRange(-1.0471977f, 0.17453295f);
            FastVecScale(tempVec, aimDir, ksize);
            ApplyAxisRotationToQuaternion(tempVec, tempVec, D_0018A560, angle1);
            ApplyAxisRotationToQuaternion(tempVec, tempVec, D_0018A560 + 0x10, angle0);
            qcopy(&D_L07_0023A1F0[k].v[0], hitBuf.q);
            ks = 1.0f;
            FastVecAdd(&D_L07_0023A1F0[k].v[1], hitBuf.q, tempVec);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hitBuf.q + 4, &D_L07_0023A1E0[k].p[j1 - 1], D_L07_001B9200);
                kf = RandomFloatRange(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                ApplyAxisRotationToQuaternion(tempVec, tempVec, hitBuf.q + 4, kf);
                FastVecAdd(D_L07_0023A1F0[k].v + j1, &D_L07_0023A1E0[k].p[j1 - 1], tempVec);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = jitter[j2];
                FastVecSub(q, D_L07_0023A1F0[k].v + j2, &D_L07_0023A1E0[k].p[j2 - 1]);
                q[0] = q[0] + RandomSignedFloatRange(0.0f, 0.1f);
                q[1] = q[1] + RandomSignedFloatRange(0.0f, 0.1f);
                q[2] = q[2] + RandomSignedFloatRange(0.0f, 0.1f);
            }
            qcopy(&D_L07_0023A1F0[k].v[0], hitBuf.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(D_L07_0023A1F0[k].v + j2, &D_L07_0023A1E0[k].p[j2 - 1], jitter[j2]);
            {
                int x = D_L07_001B2BC0[k];
                int y = D_L07_001B2BA8[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                D_L07_001B2BB0[k] = fade;
            }
        }
    }
    {
        angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
        angle1 = RandomFloatRange(-0.52359885f, 1.0471977f);
        FastVecScale(tempVec, aimDir, D_L07_001AF178);
        ApplyAxisRotationToQuaternion(tempVec, tempVec, D_0018A560, angle1);
        ApplyAxisRotationToQuaternion(tempVec, tempVec, D_0018A560 + 0x10, angle0);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.2f, 0.6f);
        SpawnGroundEffectParticle(st, 0xF, tsize * 0.3f, tsize, D_L07_001AF148 | 0x7F000000, 0, spin, tempVec, 1, 0.0f);
        spin = -spin;
        SpawnGroundEffectParticle(st, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, tempVec, 1, 0.0f);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.15f, 3.0f);
        SpawnGroundEffectParticle(st->b, 0xC, tsize * 0.1f, tsize, D_L07_001AF148 | 0x7F000000, 0, spin, D_L07_001A8F20, 1, 0.0f);
    }
}
