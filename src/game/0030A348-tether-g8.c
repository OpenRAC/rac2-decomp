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
extern Slot D_00239BA0[];
extern Cam D_00189E20;
extern char D_0018A560[];
extern int D_001A8CA0;
extern float D_001A8BD0[] MACRO_ADDR;
extern int D_001B23E0;
extern short D_001B23E8[] MACRO_ADDR;
extern short D_001B23F0[] MACRO_ADDR;
extern short D_001B23F8[] MACRO_ADDR;
extern short D_001B2400[] MACRO_ADDR;
extern float D_001B5200[];
extern char D_001B5340[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_001BAF98;
extern Tgt *D_001EE960[];
extern float D_00229150[][4], D_00229160[][4];
extern Vec D_00229170[2][20];
extern V4 D_002292A0;
extern float D_002293F0[];
extern Vec D_00229440[];
extern float D_00229580[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_002295C0[];
extern Node5 D_002295D0[];

extern float D_001AEDF4 __attribute__((sda));
extern float D_001AEDF8 __attribute__((sda));
extern float D_001AEDFC __attribute__((sda));
extern float D_001AEE00 __attribute__((sda));
extern float D_001AEE04 __attribute__((sda));
extern float D_001AEE08 __attribute__((sda));
extern float D_001AEE0C __attribute__((sda));
extern float D_001AEE10 __attribute__((sda));
extern float D_001AEE14 __attribute__((sda));
extern float D_001AEE18 __attribute__((sda));
extern float D_001AEE1C __attribute__((sda));
extern float D_001AEE20 __attribute__((sda));
extern float D_001AEE24 __attribute__((sda));
extern float D_001AEE28 __attribute__((sda));
extern float D_001AEE2C __attribute__((sda));
extern float D_001AEE30 __attribute__((sda));
extern float D_001AEE44 __attribute__((sda));
extern float D_001AEE48 __attribute__((sda));
extern float D_001AEE88 __attribute__((sda));
extern float D_001AEE8C __attribute__((sda));
extern int D_001AEE58 __attribute__((sda));

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

/* Moves the tether chain from the player's hand to the best locked-on target, or two targets. Also updates the glow spots and sparks. */
void func_0030A348(Moby *self)
{
    int locked = gWeaponTable_00239BA0[gItemSlotToRecord.cur].on != 0;
    float reach = D_001AEDF4 * 0.05f;
    Rope *chain = self->rope;
    float lockPointA[4] __attribute__((aligned(16)));
    float lockPointB[4] __attribute__((aligned(16)));
    float scratchB[4] __attribute__((aligned(16)));
    Hit hitInfo __attribute__((aligned(16)));
    float tetherDir[4] __attribute__((aligned(16)));
    float segmentDelta[4] __attribute__((aligned(16)));
    float stepVec[4] __attribute__((aligned(16)));
    float lastStep[4] __attribute__((aligned(16)));
    float radialOffset[4] __attribute__((aligned(16)));
    Tgt *heldTargets[128];
    float scratchA[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hitBuffer __attribute__((aligned(16)));
    float tmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int hitSomething, heldCount;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int n;
    Tgt *candidate;
    int scanIndex;
    float dist, ang, sa2, cs, sm, score, proj, angleScore, distanceScore;
    float d0;
    float *infoA, *infoB;
    Tgt *targetA, *targetB;
    float length, blend;
    float amp, height, angle, old, cd;
    int mirrorIndex;
    Tgt *hitTarget;
    float *hitTargetInfo;
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

    D_001AEE0C = FastAddRotations(D_001AEE0C, D_001AEE10);
    D_001AEE14 = fast_subtract_rotations(D_001AEE14, D_001AEE18);
    D_001AEE28 = FastAddRotations(D_001AEE28, D_001AEE2C);

    if (chain->lockA == 0 || (locked && chain->lockB == 0)) {
        if (chain->lockB != 0) {
            chain->lockA = chain->lockB;
            chain->u.s.h40 = chain->u.s.h42;
            chain->lockB = 0;
            chain->u.s.h42 = 0;
        } else {
            scanIndex = 0;
            for (candidate = D_001EE960[0]; candidate != 0; candidate = D_001EE960[++scanIndex]) {
                if (candidate != chain->lockA && candidate != chain->lockB) {
                    if (candidate != 0 && candidate->cls != 0 && candidate->cls->id == 5) {
                        if (candidate->kind != 0xFE) {
                        if (candidate->kind != 0xFD) {
                            if (GetMobyPrivateValue0(candidate) != 0) {
                                FastVecSub(lockPointA, candidate->pos, chain);
                                if (D_001A8CA0 != 0) {
                                    proj = FastVecDot(lockPointA, gHeroState.ent + 0xE0);
                                    FastVecScale(lockPointB, gHeroState.ent + 0xE0, proj);
                                    FastVecSub(scratchB, lockPointA, lockPointB);
                                    dist = FastVecLength(scratchB);
                                } else {
                                    dist = vec_length_xy(lockPointA);
                                }
                                if (!(D_001AEDF4 < dist)) {
                                    ang = FastDiffRots(gActiveCamera[0x158 / 4], FastMatrixHelperA(candidate->pos[0] - gActiveCamera[0x140 / 4], candidate->pos[1] - gActiveCamera[0x144 / 4]));
                                    if (!(D_001AEDFC < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sa2 = 0.0f;
                                        if (D_001A8CA0 != 0) {
                                            FastVecSub(lockPointB, candidate->pos, &gHeroState.x);
                                            proj2 = FastVecDot(lockPointB, gHeroState.ent + 0xE0);
                                            FastVecScale(scratchB, gHeroState.ent + 0xE0, proj2);
                                            FastVecSub(lockPointB, lockPointB, scratchB);
                                            cs = FastVecDot(lockPointB, gHeroState.ent + 0xC0);
                                            sm = FastVecLength(lockPointB);
                                            if (sm == 0.0f)
                                                continue;
                                            sa2 = 1.5707964f - FastAngleHelper(cs / sm);
                                        } else {
                                            sa2 = FastDiffRots(FastMatrixHelperA(candidate->pos[0] - gHeroState.x, candidate->pos[1] - gHeroState.y), gHeroState.f98);
                                        }
                                            if (!(D_001AEDF8 < sa2)) {
                                                angleScore = (D_001AEDFC - ang) / D_001AEDFC;
                                                distanceScore = (D_001AEDF4 - dist) / D_001AEDF4;
                                                score = angleScore * D_001AEE8C + distanceScore;
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
        if (chain->lockA != 0) {
            second = best;
        } else {
            chain->lockA = best;
            chain->u.s.h40 = 0;
            if (FastFloatHelperD(&D_001B23E0) != 0)
                D_001B23E0 = 0xA;
        }
    }
    if (second != 0 && locked) {
        d0 = fast_vec_dist(chain, best->pos);
        if (d0 < D_001AEDF4 && d0 + fast_vec_dist(best->pos, second->pos) < D_001AEDF4) {
            chain->u.s.h42 = 0;
            chain->lockB = second;
        }
    }
    len = 0.0f;
    if (chain->lockA != 0) {
        infoA = GetMobyPrivateValue0(chain->lockA);
        targetA = chain->lockA;
        qcopy(lockPointA, targetA->pos);
        FastVecScale(lockPointB, (char *)targetA + 0xE0, infoA[4]);
        FastVecAdd(lockPointA, lockPointA, lockPointB);
        len = fast_vec_dist(chain, lockPointA);
        reach = len * 0.05f;
    }
    if (chain->lockB != 0) {
        infoB = GetMobyPrivateValue0(chain->lockB);
        targetB = chain->lockB;
        qcopy(lockPointB, targetB->pos);
        FastVecScale(scratchB, (char *)targetB + 0xE0, infoB[4]);
        FastVecAdd(lockPointB, lockPointB, scratchB);
        reach = (fast_vec_dist(lockPointA, lockPointB) + len) * 0.05f;
    }
    if (locked)
        D_001AEE58 = 0x207F20;
    else
        D_001AEE58 = 0x7F2020;
    ClearVector128(scratchB);
    make_hit_descriptor(&hitInfo, self, 0x210000, scratchB, (&gWeaponTable_00239BA0[gItemSlotToRecord.cur])->f70);
    hitInfo.kind = 5;
    hitInfo.flag = 1;
    hitInfo.tag = self->tag;
    chain->count = 0x14;
    ProcessCollisionHit(chain, 0x10, gHeroState.ent, &hitInfo, 0.3f);
    FastVecSub(tetherDir, chain->b, chain);
    vec_scale_to_length(tetherDir, tetherDir, 1.0f);
    if (chain->lockA != 0 || chain->lockB != 0) {
        FastVecCross(segmentDelta, tetherDir, (char *)&gHeroState + 0x2C0);
        ApplyAxisRotationToQuaternion(tetherDir, tetherDir, segmentDelta, 0.17453295f);
    }
    hitSomething = 0;
    FastVecScale(lastStep, tetherDir, reach);
    heldCount = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = chain->a;
        qcopy(&D_00229170[0][0], anchor);
    }
    {
        float *anchor = chain->a;
        qcopy(&D_00229170[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_001AEE04 + (D_001AEE08 - D_001AEE04) * (IntToFloat(i) * 0.05f);
        height = amp * FastSinOrCosB(WrapAngleToPi(D_001AEE0C + (float)i * D_001AEE00));
        height += RandomSignedFloatRange(D_001AEE44, D_001AEE48);
        old = D_002293F0[i];
        D_002293F0[i] = height;
        D_00229170[0][i].f[2] = D_00229170[0][i].f[2] - old;
        TransformVectorOrCopy(&D_00229170[0][i], &D_00229170[0][i]);
        FastVecSub(segmentDelta, &D_00229170[0][i], D_00229160[i]);
        lerp_vector(stepVec, segmentDelta, lastStep, 0.85f);
        {
            float cm = FastVecLength(stepVec);
            if (cm == 0.0f) {
                prev = &D_00229170[0][i - 1];
                qcopy(&D_00229170[0][i], prev);
            } else {
                FastVecScale(stepVec, stepVec, reach / cm);
                FastVecAdd(&D_00229170[0][i], D_00229160[i], stepVec);
                qcopy(lastStep, stepVec);
            }
        }
        D_00229170[0][i].f[2] = D_00229170[0][i].f[2] + height;
        FastVecSub(segmentDelta, &D_00229170[0][i], D_00229160[i]);
        if (chain->lockA != 0) {
            if (!locked || chain->lockB == 0) {
                FastVecSub(scratchA, lockPointA, &D_00229170[0][i]);
                length = FastVecLength(scratchA);
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
                    FastVecScale(scratchA, scratchA, reach / length);
                    lerp_vector(lastStep, lastStep, scratchA, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(scratchA, lockPointB, &D_00229170[0][i]);
                else
                    FastVecSub(scratchA, lockPointA, &D_00229170[0][i]);
                length = FastVecLength(scratchA);
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
                    FastVecScale(scratchA, scratchA, reach / length);
                    lerp_vector(lastStep, lastStep, scratchA, blend);
                }
            }
        }
        if (i < 10) {
            angle = WrapAngleToPi(D_001AEE14 + (float)i * D_001AEE1C);
            amp = D_001AEE20 * FastSinOrCosB(WrapAngleToPi(D_001AEE28 + (float)i * D_001AEE30));
            qcopy(&D_00229170[1][i], &D_00229170[0][i]);
            height = amp * FastSinOrCosB(angle) + RandomSignedFloatRange(0.0f, 0.1f);
            D_00229580[i] = height;
            D_00229170[1][i].f[2] = D_00229170[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(FastMatrixHelperA(segmentDelta[0], segmentDelta[1]), 1.5707965f);
                {
                    float radial = D_001AEE24 * FastSinOrCosA(angle);
                    radialOffset[0] = FastSinOrCosA(bearing) * radial;
                    radialOffset[1] = FastSinOrCosB(bearing) * radial;
                    radialOffset[2] = 0.0f;
                    qcopy_nc(&D_00229440[i], radialOffset);
                }
            }
            FastVecAdd(&D_00229170[1][i], &D_00229170[1][i], radialOffset);
        } else {
            mirrorIndex = 0x15 - i;
            qcopy(&D_00229170[1][i], &D_00229170[0][i]);
            D_00229170[1][i].f[2] = D_00229170[1][i].f[2] + D_00229580[mirrorIndex];
            FastVecAdd(&D_00229170[1][i], &D_00229170[1][i], &D_00229440[mirrorIndex]);
            qcopy(radialOffset, &D_00229440[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(scratchB, &D_00229170[0][i], gCameraState_001B5340);
            if (D_001A8CA0 != 0) {
                float cpj = FastVecDot(scratchB, gHeroState.ent + 0xE0);
                {
                    char *ax = gHeroState.ent + 0xE0;
                    FastVecScale(scratchA, ax, cpj);
                    FastVecSub(scratchB, scratchB, scratchA);
                }
            } else {
                *(int *)&scratchB[2] = 0;
            }
            cm2 = FastVecLength(scratchB);
            if (cm2 == 0.0f)
                scratchB[2] = 1.0f;
            else
                FastVecScale(scratchB, scratchB, 1.0f / cm2);
            scratchB[3] = 5627.925f;
            qcopy(&hitInfo, scratchB);
            hitSomething = CollLine(D_00229150[i], &D_00229170[0][i], 0x10, self, 0);
            if (hitSomething != 0) {
                hitTarget = D_001BAF98.hit;
                if (hitTarget != 0) {
                    hitTargetInfo = GetMobyPrivateValue0(hitTarget);
                    if (hitTargetInfo == 0) {
                        QueueMobyImpact(hitTarget, &hitInfo);
                    } else if (hitTarget->cls == 0 || hitTarget->cls->id != 5) {
                        QueueMobyImpact(hitTarget, &hitInfo);
                    } else {
                        hitSomething = 0;
                        heldTargets[heldCount++] = hitTarget;
                        hitTarget->f98 = 0;
                    }
                }
                if (hitSomething != 0) {
                    qcopy(&D_00229170[0][i], D_001BAF98.pos);
                    {
                        short last = i;
                        chain->count = last;
                    }
                    qcopy(chain->b, D_001BAF98.pos);
                    if (D_001BAF98.hit == 0) {
                        chain->lockA = 0;
                        chain->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (n = 0; n < heldCount; n++)
        heldTargets[n]->f98 = heldTargets[n]->cls->f10;
    if (hitSomething == 0)
        qcopy(chain->b, &D_002292A0);
    if (chain->lockA != 0 && (chain->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hitBuffer.q;
        FastVecSub(scratchA, chain->lockA->pos, gCameraState_001B5340);
        if (D_001A8CA0 != 0) {
            apj = FastVecDot(scratchA, gHeroState.ent + 0xE0);
            FastVecScale(tv, gHeroState.ent + 0xE0, apj);
            FastVecSub(scratchA, scratchA, tv);
        } else {
            *(int *)&scratchA[2] = 0;
        }
        vec_scale_to_length(scratchA, scratchA, 1.0f);
        scratchA[3] = 5627.925f;
        make_hit_descriptor(&hitBuffer.a.r, self, 0x210000, scratchA, (&gWeaponTable_00239BA0[gItemSlotToRecord.cur])->f70);
        hitBuffer.a.r.kind = 5;
        hitBuffer.a.r.flag = 3;
        hitBuffer.a.r.tag = self->tag;
        an = 5;
        QueueMobyImpact(chain->lockA, &hitBuffer.a.r);
        ainfo = GetMobyPrivateValue0(chain->lockA);
        if (ainfo != 0) {
            if (((short *)ainfo)[2] == 1)
                an = 1;
        }
        {
            short result = an;
            chain->u.s.h44 = result;
        }
    }
    if (chain->lockB != 0 && (chain->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(scratchA, chain->lockB->pos, gCameraState_001B5340);
        if (D_001A8CA0 != 0) {
            bpj = FastVecDot(scratchA, gHeroState.ent + 0xE0);
            FastVecScale(hitBuffer.q, gHeroState.ent + 0xE0, bpj);
            FastVecSub(scratchA, scratchA, hitBuffer.q);
        } else {
            *(int *)&scratchA[2] = 0;
        }
        vec_scale_to_length(scratchA, scratchA, 1.0f);
        scratchA[3] = 5627.925f;
        make_hit_descriptor(&hitBuffer.b.r, self, 0x210000, scratchA, (&gWeaponTable_00239BA0[gItemSlotToRecord.cur])->f70);
        hitBuffer.b.r.kind = 5;
        hitBuffer.b.r.flag = 3;
        hitBuffer.b.r.tag = self->tag;
        bn = 5;
        QueueMobyImpact(chain->lockB, &hitBuffer.b.r);
        binfo = GetMobyPrivateValue0(chain->lockB);
        if (binfo != 0) {
            if (((short *)binfo)[2] == 1)
                bn = 1;
        }
        {
            short result = bn;
            chain->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = chain->a;
                qcopy(hitBuffer.q, from);
            }
            ksize = 0.4f;
        } else {
            qcopy(hitBuffer.q, chain->b);
            ksize = 0.5f;
        }
        if (FastDecTimer(&D_001B23E8[k]) != 0) {
            D_001B23E8[k] = D_001B23F8[k];
            D_001B23F0[k] = 0;
            angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
            angle1 = RandomFloatRange(-1.0471977f, 0.17453295f);
            FastVecScale(scratchA, tetherDir, ksize);
            ApplyAxisRotationToQuaternion(scratchA, scratchA, D_0018A560, angle1);
            ApplyAxisRotationToQuaternion(scratchA, scratchA, D_0018A560 + 0x10, angle0);
            qcopy(&D_002295D0[k].v[0], hitBuffer.q);
            ks = 1.0f;
            FastVecAdd(&D_002295D0[k].v[1], hitBuffer.q, scratchA);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hitBuffer.q + 4, &D_002295C0[k].p[j1 - 1], gCameraState_001B5340);
                kf = RandomFloatRange(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                ApplyAxisRotationToQuaternion(scratchA, scratchA, hitBuffer.q + 4, kf);
                FastVecAdd(D_002295D0[k].v + j1, &D_002295C0[k].p[j1 - 1], scratchA);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = tmp[j2];
                FastVecSub(q, D_002295D0[k].v + j2, &D_002295C0[k].p[j2 - 1]);
                q[0] = q[0] + RandomSignedFloatRange(0.0f, 0.1f);
                q[1] = q[1] + RandomSignedFloatRange(0.0f, 0.1f);
                q[2] = q[2] + RandomSignedFloatRange(0.0f, 0.1f);
            }
            qcopy(&D_002295D0[k].v[0], hitBuffer.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(D_002295D0[k].v + j2, &D_002295C0[k].p[j2 - 1], tmp[j2]);
            {
                int x = D_001B2400[k];
                int y = D_001B23E8[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                D_001B23F0[k] = fade;
            }
        }
    }
    {
        angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
        angle1 = RandomFloatRange(-0.52359885f, 1.0471977f);
        FastVecScale(scratchA, tetherDir, D_001AEE88);
        ApplyAxisRotationToQuaternion(scratchA, scratchA, D_0018A560, angle1);
        ApplyAxisRotationToQuaternion(scratchA, scratchA, D_0018A560 + 0x10, angle0);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.2f, 0.6f);
        SpawnGroundEffectParticle(chain, 0xF, tsize * 0.3f, tsize, D_001AEE58 | 0x7F000000, 0, spin, scratchA, 1, 0.0f);
        spin = -spin;
        SpawnGroundEffectParticle(chain, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, scratchA, 1, 0.0f);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.15f, 3.0f);
        SpawnGroundEffectParticle(chain->b, 0xC, tsize * 0.1f, tsize, D_001AEE58 | 0x7F000000, 0, spin, D_001A8BD0, 1, 0.0f);
    }
}
