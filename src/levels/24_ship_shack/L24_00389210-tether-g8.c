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
extern Slot D_L24_00261E70[];
extern Cam D_00189E20;
extern char D_0018A560[];
extern int D_L24_001A8FF0;
extern float D_L24_001A8F20[] MACRO_ADDR;
extern int D_L24_001B2040;
extern short D_L24_001B2048[] MACRO_ADDR;
extern short D_L24_001B2050[] MACRO_ADDR;
extern short D_L24_001B2058[] MACRO_ADDR;
extern short D_L24_001B2060[] MACRO_ADDR;
extern float D_L24_001B8580[];
extern char D_L24_001B86C0[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L24_001BEB18;
extern Tgt *D_L24_001FA5E0[];
extern float D_L24_00239230[][4], D_L24_00239240[][4];
extern Vec D_L24_00239250[2][20];
extern V4 D_L24_00239380;
extern float D_L24_002394D0[];
extern Vec D_L24_00239520[];
extern float D_L24_00239660[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L24_002396A0[];
extern Node5 D_L24_002396B0[];

extern float D_L24_001AEFC4 __attribute__((sda));
extern float D_L24_001AEFC8 __attribute__((sda));
extern float D_L24_001AEFCC __attribute__((sda));
extern float D_L24_001AEFD0 __attribute__((sda));
extern float D_L24_001AEFD4 __attribute__((sda));
extern float D_L24_001AEFD8 __attribute__((sda));
extern float D_L24_001AEFDC __attribute__((sda));
extern float D_L24_001AEFE0 __attribute__((sda));
extern float D_L24_001AEFE4 __attribute__((sda));
extern float D_L24_001AEFE8 __attribute__((sda));
extern float D_L24_001AEFEC __attribute__((sda));
extern float D_L24_001AEFF0 __attribute__((sda));
extern float D_L24_001AEFF4 __attribute__((sda));
extern float D_L24_001AEFF8 __attribute__((sda));
extern float D_L24_001AEFFC __attribute__((sda));
extern float D_L24_001AF000 __attribute__((sda));
extern float D_L24_001AF014 __attribute__((sda));
extern float D_L24_001AF018 __attribute__((sda));
extern float D_L24_001AF058 __attribute__((sda));
extern float D_L24_001AF05C __attribute__((sda));
extern int D_L24_001AF028 __attribute__((sda));

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

/* Updates the lock-on tether: picks up to two targets, bends the chain of points from the hand toward them, and makes the glow spots and sparks. */
void func_L24_00389210(Moby *self)
{
    int locked = D_L24_00261E70[gItemSlotToRecord.cur].on != 0;
    float reach = D_L24_001AEFC4 * 0.05f;
    Rope *rope = self->rope;
    float vecA[4] __attribute__((aligned(16)));
    float vecB[4] __attribute__((aligned(16)));
    float vecC[4] __attribute__((aligned(16)));
    Hit firstHit __attribute__((aligned(16)));
    float aimDir[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float pull[4] __attribute__((aligned(16)));
    float drift[4] __attribute__((aligned(16)));
    float sway[4] __attribute__((aligned(16)));
    Tgt *disabledTargets[128];
    float scratch[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hitBuf __attribute__((aligned(16)));
    float jitter[5][4] __attribute__((aligned(16)));
    Tgt *bestTarget = 0, *secondTarget = 0;
    int hitSomething, heldCount;
    float bestScore = 0.0f, secondScore = 0.0f;
    float lockALength;
    float angle0, angle1;
    int n;
    Tgt *target;
    int targetIndex;
    float dist, ang, sa2, cs, sm, score, proj, fa, fb;
    float d0;
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

    D_L24_001AEFDC = FastAddRotations(D_L24_001AEFDC, D_L24_001AEFE0);
    D_L24_001AEFE4 = fast_subtract_rotations(D_L24_001AEFE4, D_L24_001AEFE8);
    D_L24_001AEFF8 = FastAddRotations(D_L24_001AEFF8, D_L24_001AEFFC);

    if (rope->lockA == 0 || (locked && rope->lockB == 0)) {
        if (rope->lockB != 0) {
            rope->lockA = rope->lockB;
            rope->u.s.h40 = rope->u.s.h42;
            rope->lockB = 0;
            rope->u.s.h42 = 0;
        } else {
            targetIndex = 0;
            for (target = D_L24_001FA5E0[0]; target != 0; target = D_L24_001FA5E0[++targetIndex]) {
                if (target != rope->lockA && target != rope->lockB) {
                    if (target != 0 && target->cls != 0 && target->cls->id == 5) {
                        if (target->kind != 0xFE) {
                        if (target->kind != 0xFD) {
                            if (GetMobyPrivateValue0(target) != 0) {
                                FastVecSub(vecA, target->pos, rope);
                                if (D_L24_001A8FF0 != 0) {
                                    proj = FastVecDot(vecA, gHeroState.ent + 0xE0);
                                    FastVecScale(vecB, gHeroState.ent + 0xE0, proj);
                                    FastVecSub(vecC, vecA, vecB);
                                    dist = FastVecLength(vecC);
                                } else {
                                    dist = vec_length_xy(vecA);
                                }
                                if (!(D_L24_001AEFC4 < dist)) {
                                    ang = FastDiffRots(D_L24_001B8580[0x158 / 4], FastMatrixHelperA(target->pos[0] - D_L24_001B8580[0x140 / 4], target->pos[1] - D_L24_001B8580[0x144 / 4]));
                                    if (!(D_L24_001AEFCC < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sa2 = 0.0f;
                                        if (D_L24_001A8FF0 != 0) {
                                            FastVecSub(vecB, target->pos, &gHeroState.x);
                                            proj2 = FastVecDot(vecB, gHeroState.ent + 0xE0);
                                            FastVecScale(vecC, gHeroState.ent + 0xE0, proj2);
                                            FastVecSub(vecB, vecB, vecC);
                                            cs = FastVecDot(vecB, gHeroState.ent + 0xC0);
                                            sm = FastVecLength(vecB);
                                            if (sm == 0.0f)
                                                continue;
                                            sa2 = 1.5707964f - FastAngleHelper(cs / sm);
                                        } else {
                                            sa2 = FastDiffRots(FastMatrixHelperA(target->pos[0] - gHeroState.x, target->pos[1] - gHeroState.y), gHeroState.f98);
                                        }
                                            if (!(D_L24_001AEFC8 < sa2)) {
                                                fa = (D_L24_001AEFCC - ang) / D_L24_001AEFCC;
                                                fb = (D_L24_001AEFC4 - dist) / D_L24_001AEFC4;
                                                score = fa * D_L24_001AF05C + fb;
                                                if (bestScore < score) {
                                                    secondScore = bestScore;
                                                    bestScore = score;
                                                    secondTarget = bestTarget;
                                                    bestTarget = target;
                                                } else if (secondScore < score) {
                                                    secondTarget = target;
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

    if (bestTarget != 0) {
        if (rope->lockA != 0) {
            secondTarget = bestTarget;
        } else {
            rope->lockA = bestTarget;
            rope->u.s.h40 = 0;
            if (FastFloatHelperD(&D_L24_001B2040) != 0)
                D_L24_001B2040 = 0xA;
        }
    }
    if (secondTarget != 0 && locked) {
        d0 = fast_vec_dist(rope, bestTarget->pos);
        if (d0 < D_L24_001AEFC4 && d0 + fast_vec_dist(bestTarget->pos, secondTarget->pos) < D_L24_001AEFC4) {
            rope->u.s.h42 = 0;
            rope->lockB = secondTarget;
        }
    }
    lockALength = 0.0f;
    if (rope->lockA != 0) {
        ia = GetMobyPrivateValue0(rope->lockA);
        ta = rope->lockA;
        qcopy(vecA, ta->pos);
        FastVecScale(vecB, (char *)ta + 0xE0, ia[4]);
        FastVecAdd(vecA, vecA, vecB);
        lockALength = fast_vec_dist(rope, vecA);
        reach = lockALength * 0.05f;
    }
    if (rope->lockB != 0) {
        ib = GetMobyPrivateValue0(rope->lockB);
        tb = rope->lockB;
        qcopy(vecB, tb->pos);
        FastVecScale(vecC, (char *)tb + 0xE0, ib[4]);
        FastVecAdd(vecB, vecB, vecC);
        reach = (fast_vec_dist(vecA, vecB) + lockALength) * 0.05f;
    }
    if (locked)
        D_L24_001AF028 = 0x207F20;
    else
        D_L24_001AF028 = 0x7F2020;
    ClearVector128(vecC);
    make_hit_descriptor(&firstHit, self, 0x210000, vecC, (&D_L24_00261E70[gItemSlotToRecord.cur])->f70);
    firstHit.kind = 5;
    firstHit.flag = 1;
    firstHit.tag = self->tag;
    rope->count = 0x14;
    ProcessCollisionHit(rope, 0x10, gHeroState.ent, &firstHit, 0.3f);
    FastVecSub(aimDir, rope->b, rope);
    vec_scale_to_length(aimDir, aimDir, 1.0f);
    if (rope->lockA != 0 || rope->lockB != 0) {
        FastVecCross(offset, aimDir, (char *)&gHeroState + 0x2C0);
        ApplyAxisRotationToQuaternion(aimDir, aimDir, offset, 0.17453295f);
    }
    hitSomething = 0;
    FastVecScale(drift, aimDir, reach);
    heldCount = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = rope->a;
        qcopy(&D_L24_00239250[0][0], anchor);
    }
    {
        float *anchor = rope->a;
        qcopy(&D_L24_00239250[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L24_001AEFD4 + (D_L24_001AEFD8 - D_L24_001AEFD4) * (IntToFloat(i) * 0.05f);
        height = amp * FastSinOrCosB(WrapAngleToPi(D_L24_001AEFDC + (float)i * D_L24_001AEFD0));
        height += RandomSignedFloatRange(D_L24_001AF014, D_L24_001AF018);
        old = D_L24_002394D0[i];
        D_L24_002394D0[i] = height;
        D_L24_00239250[0][i].f[2] = D_L24_00239250[0][i].f[2] - old;
        TransformVectorOrCopy(&D_L24_00239250[0][i], &D_L24_00239250[0][i]);
        FastVecSub(offset, &D_L24_00239250[0][i], D_L24_00239240[i]);
        lerp_vector(pull, offset, drift, 0.85f);
        {
            float cm = FastVecLength(pull);
            if (cm == 0.0f) {
                prev = &D_L24_00239250[0][i - 1];
                qcopy(&D_L24_00239250[0][i], prev);
            } else {
                FastVecScale(pull, pull, reach / cm);
                FastVecAdd(&D_L24_00239250[0][i], D_L24_00239240[i], pull);
                qcopy(drift, pull);
            }
        }
        D_L24_00239250[0][i].f[2] = D_L24_00239250[0][i].f[2] + height;
        FastVecSub(offset, &D_L24_00239250[0][i], D_L24_00239240[i]);
        if (rope->lockA != 0) {
            if (!locked || rope->lockB == 0) {
                FastVecSub(scratch, vecA, &D_L24_00239250[0][i]);
                length = FastVecLength(scratch);
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
                    FastVecScale(scratch, scratch, reach / length);
                    lerp_vector(drift, drift, scratch, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(scratch, vecB, &D_L24_00239250[0][i]);
                else
                    FastVecSub(scratch, vecA, &D_L24_00239250[0][i]);
                length = FastVecLength(scratch);
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
                    FastVecScale(scratch, scratch, reach / length);
                    lerp_vector(drift, drift, scratch, blend);
                }
            }
        }
        if (i < 10) {
            angle = WrapAngleToPi(D_L24_001AEFE4 + (float)i * D_L24_001AEFEC);
            amp = D_L24_001AEFF0 * FastSinOrCosB(WrapAngleToPi(D_L24_001AEFF8 + (float)i * D_L24_001AF000));
            qcopy(&D_L24_00239250[1][i], &D_L24_00239250[0][i]);
            height = amp * FastSinOrCosB(angle) + RandomSignedFloatRange(0.0f, 0.1f);
            D_L24_00239660[i] = height;
            D_L24_00239250[1][i].f[2] = D_L24_00239250[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(FastMatrixHelperA(offset[0], offset[1]), 1.5707965f);
                {
                    float radial = D_L24_001AEFF4 * FastSinOrCosA(angle);
                    sway[0] = FastSinOrCosA(bearing) * radial;
                    sway[1] = FastSinOrCosB(bearing) * radial;
                    sway[2] = 0.0f;
                    qcopy_nc(&D_L24_00239520[i], sway);
                }
            }
            FastVecAdd(&D_L24_00239250[1][i], &D_L24_00239250[1][i], sway);
        } else {
            fa2 = 0x15 - i;
            qcopy(&D_L24_00239250[1][i], &D_L24_00239250[0][i]);
            D_L24_00239250[1][i].f[2] = D_L24_00239250[1][i].f[2] + D_L24_00239660[fa2];
            FastVecAdd(&D_L24_00239250[1][i], &D_L24_00239250[1][i], &D_L24_00239520[fa2]);
            qcopy(sway, &D_L24_00239520[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(vecC, &D_L24_00239250[0][i], D_L24_001B86C0);
            if (D_L24_001A8FF0 != 0) {
                float cpj = FastVecDot(vecC, gHeroState.ent + 0xE0);
                {
                    char *ax = gHeroState.ent + 0xE0;
                    FastVecScale(scratch, ax, cpj);
                    FastVecSub(vecC, vecC, scratch);
                }
            } else {
                *(int *)&vecC[2] = 0;
            }
            cm2 = FastVecLength(vecC);
            if (cm2 == 0.0f)
                vecC[2] = 1.0f;
            else
                FastVecScale(vecC, vecC, 1.0f / cm2);
            vecC[3] = 5627.925f;
            qcopy(&firstHit, vecC);
            hitSomething = CollLine(D_L24_00239230[i], &D_L24_00239250[0][i], 0x10, self, 0);
            if (hitSomething != 0) {
                ht = D_L24_001BEB18.hit;
                if (ht != 0) {
                    hinfo = GetMobyPrivateValue0(ht);
                    if (hinfo == 0) {
                        QueueMobyImpact(ht, &firstHit);
                    } else if (ht->cls == 0 || ht->cls->id != 5) {
                        QueueMobyImpact(ht, &firstHit);
                    } else {
                        hitSomething = 0;
                        disabledTargets[heldCount++] = ht;
                        ht->f98 = 0;
                    }
                }
                if (hitSomething != 0) {
                    qcopy(&D_L24_00239250[0][i], D_L24_001BEB18.pos);
                    {
                        short last = i;
                        rope->count = last;
                    }
                    qcopy(rope->b, D_L24_001BEB18.pos);
                    if (D_L24_001BEB18.hit == 0) {
                        rope->lockA = 0;
                        rope->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (n = 0; n < heldCount; n++)
        disabledTargets[n]->f98 = disabledTargets[n]->cls->f10;
    if (hitSomething == 0)
        qcopy(rope->b, &D_L24_00239380);
    if (rope->lockA != 0 && (rope->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hitBuf.q;
        FastVecSub(scratch, rope->lockA->pos, D_L24_001B86C0);
        if (D_L24_001A8FF0 != 0) {
            apj = FastVecDot(scratch, gHeroState.ent + 0xE0);
            FastVecScale(tv, gHeroState.ent + 0xE0, apj);
            FastVecSub(scratch, scratch, tv);
        } else {
            *(int *)&scratch[2] = 0;
        }
        vec_scale_to_length(scratch, scratch, 1.0f);
        scratch[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.a.r, self, 0x210000, scratch, (&D_L24_00261E70[gItemSlotToRecord.cur])->f70);
        hitBuf.a.r.kind = 5;
        hitBuf.a.r.flag = 3;
        hitBuf.a.r.tag = self->tag;
        an = 5;
        QueueMobyImpact(rope->lockA, &hitBuf.a.r);
        ainfo = GetMobyPrivateValue0(rope->lockA);
        if (ainfo != 0) {
            if (((short *)ainfo)[2] == 1)
                an = 1;
        }
        {
            short result = an;
            rope->u.s.h44 = result;
        }
    }
    if (rope->lockB != 0 && (rope->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(scratch, rope->lockB->pos, D_L24_001B86C0);
        if (D_L24_001A8FF0 != 0) {
            bpj = FastVecDot(scratch, gHeroState.ent + 0xE0);
            FastVecScale(hitBuf.q, gHeroState.ent + 0xE0, bpj);
            FastVecSub(scratch, scratch, hitBuf.q);
        } else {
            *(int *)&scratch[2] = 0;
        }
        vec_scale_to_length(scratch, scratch, 1.0f);
        scratch[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.b.r, self, 0x210000, scratch, (&D_L24_00261E70[gItemSlotToRecord.cur])->f70);
        hitBuf.b.r.kind = 5;
        hitBuf.b.r.flag = 3;
        hitBuf.b.r.tag = self->tag;
        bn = 5;
        QueueMobyImpact(rope->lockB, &hitBuf.b.r);
        binfo = GetMobyPrivateValue0(rope->lockB);
        if (binfo != 0) {
            if (((short *)binfo)[2] == 1)
                bn = 1;
        }
        {
            short result = bn;
            rope->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = rope->a;
                qcopy(hitBuf.q, from);
            }
            ksize = 0.4f;
        } else {
            qcopy(hitBuf.q, rope->b);
            ksize = 0.5f;
        }
        if (FastDecTimer(&D_L24_001B2048[k]) != 0) {
            D_L24_001B2048[k] = D_L24_001B2058[k];
            D_L24_001B2050[k] = 0;
            angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
            angle1 = RandomFloatRange(-1.0471977f, 0.17453295f);
            FastVecScale(scratch, aimDir, ksize);
            ApplyAxisRotationToQuaternion(scratch, scratch, D_0018A560, angle1);
            ApplyAxisRotationToQuaternion(scratch, scratch, D_0018A560 + 0x10, angle0);
            qcopy(&D_L24_002396B0[k].v[0], hitBuf.q);
            ks = 1.0f;
            FastVecAdd(&D_L24_002396B0[k].v[1], hitBuf.q, scratch);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hitBuf.q + 4, &D_L24_002396A0[k].p[j1 - 1], D_L24_001B86C0);
                kf = RandomFloatRange(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                ApplyAxisRotationToQuaternion(scratch, scratch, hitBuf.q + 4, kf);
                FastVecAdd(D_L24_002396B0[k].v + j1, &D_L24_002396A0[k].p[j1 - 1], scratch);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = jitter[j2];
                FastVecSub(q, D_L24_002396B0[k].v + j2, &D_L24_002396A0[k].p[j2 - 1]);
                q[0] = q[0] + RandomSignedFloatRange(0.0f, 0.1f);
                q[1] = q[1] + RandomSignedFloatRange(0.0f, 0.1f);
                q[2] = q[2] + RandomSignedFloatRange(0.0f, 0.1f);
            }
            qcopy(&D_L24_002396B0[k].v[0], hitBuf.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(D_L24_002396B0[k].v + j2, &D_L24_002396A0[k].p[j2 - 1], jitter[j2]);
            {
                int x = D_L24_001B2060[k];
                int y = D_L24_001B2048[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                D_L24_001B2050[k] = fade;
            }
        }
    }
    {
        angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
        angle1 = RandomFloatRange(-0.52359885f, 1.0471977f);
        FastVecScale(scratch, aimDir, D_L24_001AF058);
        ApplyAxisRotationToQuaternion(scratch, scratch, D_0018A560, angle1);
        ApplyAxisRotationToQuaternion(scratch, scratch, D_0018A560 + 0x10, angle0);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.2f, 0.6f);
        SpawnGroundEffectParticle(rope, 0xF, tsize * 0.3f, tsize, D_L24_001AF028 | 0x7F000000, 0, spin, scratch, 1, 0.0f);
        spin = -spin;
        SpawnGroundEffectParticle(rope, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, scratch, 1, 0.0f);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.15f, 3.0f);
        SpawnGroundEffectParticle(rope->b, 0xC, tsize * 0.1f, tsize, D_L24_001AF028 | 0x7F000000, 0, spin, D_L24_001A8F20, 1, 0.0f);
    }
}
