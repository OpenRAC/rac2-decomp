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
extern Slot D_L12_002636F0[];
extern Cam D_00189E20;
extern char D_0018A560[];
extern int D_L12_001A8FF0;
extern float D_L12_001A8F20[] MACRO_ADDR;
extern int D_L12_001B3740;
extern short D_L12_001B3748[] MACRO_ADDR;
extern short D_L12_001B3750[] MACRO_ADDR;
extern short D_L12_001B3758[] MACRO_ADDR;
extern short D_L12_001B3760[] MACRO_ADDR;
extern float D_L12_001B9CC0[];
extern char D_L12_001B9E00[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L12_001C0258;
extern Tgt *D_L12_001FBD20[];
extern float D_L12_0023A970[][4], D_L12_0023A980[][4];
extern Vec D_L12_0023A990[2][20];
extern V4 D_L12_0023AAC0;
extern float D_L12_0023AC10[];
extern Vec D_L12_0023AC60[];
extern float D_L12_0023ADA0[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L12_0023ADE0[];
extern Node5 D_L12_0023ADF0[];

extern float D_L12_001AF214 __attribute__((sda));
extern float D_L12_001AF218 __attribute__((sda));
extern float D_L12_001AF21C __attribute__((sda));
extern float D_L12_001AF220 __attribute__((sda));
extern float D_L12_001AF224 __attribute__((sda));
extern float D_L12_001AF228 __attribute__((sda));
extern float D_L12_001AF22C __attribute__((sda));
extern float D_L12_001AF230 __attribute__((sda));
extern float D_L12_001AF234 __attribute__((sda));
extern float D_L12_001AF238 __attribute__((sda));
extern float D_L12_001AF23C __attribute__((sda));
extern float D_L12_001AF240 __attribute__((sda));
extern float D_L12_001AF244 __attribute__((sda));
extern float D_L12_001AF248 __attribute__((sda));
extern float D_L12_001AF24C __attribute__((sda));
extern float D_L12_001AF250 __attribute__((sda));
extern float D_L12_001AF264 __attribute__((sda));
extern float D_L12_001AF268 __attribute__((sda));
extern float D_L12_001AF2A8 __attribute__((sda));
extern float D_L12_001AF2AC __attribute__((sda));
extern int D_L12_001AF278 __attribute__((sda));

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

/* Updates the lock-on tether each frame: picks the best targets in range and lets the chain of
   points hang, swing and snap toward them from the hero's hand. */
void func_L12_00398E50(Moby *self)
{
    int locked = D_L12_002636F0[gItemSlotToRecord.cur].on != 0;
    float reach = D_L12_001AF214 * 0.05f;
    Rope *rope = self->rope;
    float segmentVec[4] __attribute__((aligned(16)));
    float vecA[4] __attribute__((aligned(16)));
    float vecB[4] __attribute__((aligned(16)));
    Hit firstHit __attribute__((aligned(16)));
    float vecC[4] __attribute__((aligned(16)));
    float vecD[4] __attribute__((aligned(16)));
    float vecE[4] __attribute__((aligned(16)));
    float vecF[4] __attribute__((aligned(16)));
    float vecG[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float vecH[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hitBuf __attribute__((aligned(16)));
    float tmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int got, heldCount;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int n;
    Tgt *t;
    int segCount;
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

    D_L12_001AF22C = FastAddRotations(D_L12_001AF22C, D_L12_001AF230);
    D_L12_001AF234 = fast_subtract_rotations(D_L12_001AF234, D_L12_001AF238);
    D_L12_001AF248 = FastAddRotations(D_L12_001AF248, D_L12_001AF24C);

    if (rope->lockA == 0 || (locked && rope->lockB == 0)) {
        if (rope->lockB != 0) {
            rope->lockA = rope->lockB;
            rope->u.s.h40 = rope->u.s.h42;
            rope->lockB = 0;
            rope->u.s.h42 = 0;
        } else {
            segCount = 0;
            for (t = D_L12_001FBD20[0]; t != 0; t = D_L12_001FBD20[++segCount]) {
                if (t != rope->lockA && t != rope->lockB) {
                    if (t != 0 && t->cls != 0 && t->cls->id == 5) {
                        if (t->kind != 0xFE) {
                        if (t->kind != 0xFD) {
                            if (GetMobyPrivateValue0(t) != 0) {
                                FastVecSub(segmentVec, t->pos, rope);
                                if (D_L12_001A8FF0 != 0) {
                                    proj = FastVecDot(segmentVec, gHeroState.ent + 0xE0);
                                    FastVecScale(vecA, gHeroState.ent + 0xE0, proj);
                                    FastVecSub(vecB, segmentVec, vecA);
                                    dist = FastVecLength(vecB);
                                } else {
                                    dist = vec_length_xy(segmentVec);
                                }
                                if (!(D_L12_001AF214 < dist)) {
                                    ang = FastDiffRots(D_L12_001B9CC0[0x158 / 4], FastMatrixHelperA(t->pos[0] - D_L12_001B9CC0[0x140 / 4], t->pos[1] - D_L12_001B9CC0[0x144 / 4]));
                                    if (!(D_L12_001AF21C < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sa2 = 0.0f;
                                        if (D_L12_001A8FF0 != 0) {
                                            FastVecSub(vecA, t->pos, &gHeroState.x);
                                            proj2 = FastVecDot(vecA, gHeroState.ent + 0xE0);
                                            FastVecScale(vecB, gHeroState.ent + 0xE0, proj2);
                                            FastVecSub(vecA, vecA, vecB);
                                            cs = FastVecDot(vecA, gHeroState.ent + 0xC0);
                                            sm = FastVecLength(vecA);
                                            if (sm == 0.0f)
                                                continue;
                                            sa2 = 1.5707964f - FastAngleHelper(cs / sm);
                                        } else {
                                            sa2 = FastDiffRots(FastMatrixHelperA(t->pos[0] - gHeroState.x, t->pos[1] - gHeroState.y), gHeroState.f98);
                                        }
                                            if (!(D_L12_001AF218 < sa2)) {
                                                fa = (D_L12_001AF21C - ang) / D_L12_001AF21C;
                                                fb = (D_L12_001AF214 - dist) / D_L12_001AF214;
                                                score = fa * D_L12_001AF2AC + fb;
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
        if (rope->lockA != 0) {
            second = best;
        } else {
            rope->lockA = best;
            rope->u.s.h40 = 0;
            if (FastFloatHelperD(&D_L12_001B3740) != 0)
                D_L12_001B3740 = 0xA;
        }
    }
    if (second != 0 && locked) {
        d0 = fast_vec_dist(rope, best->pos);
        if (d0 < D_L12_001AF214 && d0 + fast_vec_dist(best->pos, second->pos) < D_L12_001AF214) {
            rope->u.s.h42 = 0;
            rope->lockB = second;
        }
    }
    len = 0.0f;
    if (rope->lockA != 0) {
        ia = GetMobyPrivateValue0(rope->lockA);
        ta = rope->lockA;
        qcopy(segmentVec, ta->pos);
        FastVecScale(vecA, (char *)ta + 0xE0, ia[4]);
        FastVecAdd(segmentVec, segmentVec, vecA);
        len = fast_vec_dist(rope, segmentVec);
        reach = len * 0.05f;
    }
    if (rope->lockB != 0) {
        ib = GetMobyPrivateValue0(rope->lockB);
        tb = rope->lockB;
        qcopy(vecA, tb->pos);
        FastVecScale(vecB, (char *)tb + 0xE0, ib[4]);
        FastVecAdd(vecA, vecA, vecB);
        reach = (fast_vec_dist(segmentVec, vecA) + len) * 0.05f;
    }
    if (locked)
        D_L12_001AF278 = 0x207F20;
    else
        D_L12_001AF278 = 0x7F2020;
    ClearVector128(vecB);
    make_hit_descriptor(&firstHit, self, 0x210000, vecB, (&D_L12_002636F0[gItemSlotToRecord.cur])->f70);
    firstHit.kind = 5;
    firstHit.flag = 1;
    firstHit.tag = self->tag;
    rope->count = 0x14;
    ProcessCollisionHit(rope, 0x10, gHeroState.ent, &firstHit, 0.3f);
    FastVecSub(vecC, rope->b, rope);
    vec_scale_to_length(vecC, vecC, 1.0f);
    if (rope->lockA != 0 || rope->lockB != 0) {
        FastVecCross(vecD, vecC, (char *)&gHeroState + 0x2C0);
        ApplyAxisRotationToQuaternion(vecC, vecC, vecD, 0.17453295f);
    }
    got = 0;
    FastVecScale(vecF, vecC, reach);
    heldCount = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = rope->a;
        qcopy(&D_L12_0023A990[0][0], anchor);
    }
    {
        float *anchor = rope->a;
        qcopy(&D_L12_0023A990[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L12_001AF224 + (D_L12_001AF228 - D_L12_001AF224) * (IntToFloat(i) * 0.05f);
        height = amp * FastSinOrCosB(WrapAngleToPi(D_L12_001AF22C + (float)i * D_L12_001AF220));
        height += RandomSignedFloatRange(D_L12_001AF264, D_L12_001AF268);
        old = D_L12_0023AC10[i];
        D_L12_0023AC10[i] = height;
        D_L12_0023A990[0][i].f[2] = D_L12_0023A990[0][i].f[2] - old;
        TransformVectorOrCopy(&D_L12_0023A990[0][i], &D_L12_0023A990[0][i]);
        FastVecSub(vecD, &D_L12_0023A990[0][i], D_L12_0023A980[i]);
        lerp_vector(vecE, vecD, vecF, 0.85f);
        {
            float cm = FastVecLength(vecE);
            if (cm == 0.0f) {
                prev = &D_L12_0023A990[0][i - 1];
                qcopy(&D_L12_0023A990[0][i], prev);
            } else {
                FastVecScale(vecE, vecE, reach / cm);
                FastVecAdd(&D_L12_0023A990[0][i], D_L12_0023A980[i], vecE);
                qcopy(vecF, vecE);
            }
        }
        D_L12_0023A990[0][i].f[2] = D_L12_0023A990[0][i].f[2] + height;
        FastVecSub(vecD, &D_L12_0023A990[0][i], D_L12_0023A980[i]);
        if (rope->lockA != 0) {
            if (!locked || rope->lockB == 0) {
                FastVecSub(vecH, segmentVec, &D_L12_0023A990[0][i]);
                length = FastVecLength(vecH);
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
                    FastVecScale(vecH, vecH, reach / length);
                    lerp_vector(vecF, vecF, vecH, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(vecH, vecA, &D_L12_0023A990[0][i]);
                else
                    FastVecSub(vecH, segmentVec, &D_L12_0023A990[0][i]);
                length = FastVecLength(vecH);
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
                    FastVecScale(vecH, vecH, reach / length);
                    lerp_vector(vecF, vecF, vecH, blend);
                }
            }
        }
        if (i < 10) {
            angle = WrapAngleToPi(D_L12_001AF234 + (float)i * D_L12_001AF23C);
            amp = D_L12_001AF240 * FastSinOrCosB(WrapAngleToPi(D_L12_001AF248 + (float)i * D_L12_001AF250));
            qcopy(&D_L12_0023A990[1][i], &D_L12_0023A990[0][i]);
            height = amp * FastSinOrCosB(angle) + RandomSignedFloatRange(0.0f, 0.1f);
            D_L12_0023ADA0[i] = height;
            D_L12_0023A990[1][i].f[2] = D_L12_0023A990[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(FastMatrixHelperA(vecD[0], vecD[1]), 1.5707965f);
                {
                    float radial = D_L12_001AF244 * FastSinOrCosA(angle);
                    vecG[0] = FastSinOrCosA(bearing) * radial;
                    vecG[1] = FastSinOrCosB(bearing) * radial;
                    vecG[2] = 0.0f;
                    qcopy_nc(&D_L12_0023AC60[i], vecG);
                }
            }
            FastVecAdd(&D_L12_0023A990[1][i], &D_L12_0023A990[1][i], vecG);
        } else {
            fa2 = 0x15 - i;
            qcopy(&D_L12_0023A990[1][i], &D_L12_0023A990[0][i]);
            D_L12_0023A990[1][i].f[2] = D_L12_0023A990[1][i].f[2] + D_L12_0023ADA0[fa2];
            FastVecAdd(&D_L12_0023A990[1][i], &D_L12_0023A990[1][i], &D_L12_0023AC60[fa2]);
            qcopy(vecG, &D_L12_0023AC60[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(vecB, &D_L12_0023A990[0][i], D_L12_001B9E00);
            if (D_L12_001A8FF0 != 0) {
                float cpj = FastVecDot(vecB, gHeroState.ent + 0xE0);
                {
                    char *ax = gHeroState.ent + 0xE0;
                    FastVecScale(vecH, ax, cpj);
                    FastVecSub(vecB, vecB, vecH);
                }
            } else {
                *(int *)&vecB[2] = 0;
            }
            cm2 = FastVecLength(vecB);
            if (cm2 == 0.0f)
                vecB[2] = 1.0f;
            else
                FastVecScale(vecB, vecB, 1.0f / cm2);
            vecB[3] = 5627.925f;
            qcopy(&firstHit, vecB);
            got = CollLine(D_L12_0023A970[i], &D_L12_0023A990[0][i], 0x10, self, 0);
            if (got != 0) {
                ht = D_L12_001C0258.hit;
                if (ht != 0) {
                    hinfo = GetMobyPrivateValue0(ht);
                    if (hinfo == 0) {
                        QueueMobyImpact(ht, &firstHit);
                    } else if (ht->cls == 0 || ht->cls->id != 5) {
                        QueueMobyImpact(ht, &firstHit);
                    } else {
                        got = 0;
                        held[heldCount++] = ht;
                        ht->f98 = 0;
                    }
                }
                if (got != 0) {
                    qcopy(&D_L12_0023A990[0][i], D_L12_001C0258.pos);
                    {
                        short last = i;
                        rope->count = last;
                    }
                    qcopy(rope->b, D_L12_001C0258.pos);
                    if (D_L12_001C0258.hit == 0) {
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
        held[n]->f98 = held[n]->cls->f10;
    if (got == 0)
        qcopy(rope->b, &D_L12_0023AAC0);
    if (rope->lockA != 0 && (rope->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hitBuf.q;
        FastVecSub(vecH, rope->lockA->pos, D_L12_001B9E00);
        if (D_L12_001A8FF0 != 0) {
            apj = FastVecDot(vecH, gHeroState.ent + 0xE0);
            FastVecScale(tv, gHeroState.ent + 0xE0, apj);
            FastVecSub(vecH, vecH, tv);
        } else {
            *(int *)&vecH[2] = 0;
        }
        vec_scale_to_length(vecH, vecH, 1.0f);
        vecH[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.a.r, self, 0x210000, vecH, (&D_L12_002636F0[gItemSlotToRecord.cur])->f70);
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
        FastVecSub(vecH, rope->lockB->pos, D_L12_001B9E00);
        if (D_L12_001A8FF0 != 0) {
            bpj = FastVecDot(vecH, gHeroState.ent + 0xE0);
            FastVecScale(hitBuf.q, gHeroState.ent + 0xE0, bpj);
            FastVecSub(vecH, vecH, hitBuf.q);
        } else {
            *(int *)&vecH[2] = 0;
        }
        vec_scale_to_length(vecH, vecH, 1.0f);
        vecH[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.b.r, self, 0x210000, vecH, (&D_L12_002636F0[gItemSlotToRecord.cur])->f70);
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
        if (FastDecTimer(&D_L12_001B3748[k]) != 0) {
            D_L12_001B3748[k] = D_L12_001B3758[k];
            D_L12_001B3750[k] = 0;
            angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
            angle1 = RandomFloatRange(-1.0471977f, 0.17453295f);
            FastVecScale(vecH, vecC, ksize);
            ApplyAxisRotationToQuaternion(vecH, vecH, D_0018A560, angle1);
            ApplyAxisRotationToQuaternion(vecH, vecH, D_0018A560 + 0x10, angle0);
            qcopy(&D_L12_0023ADF0[k].v[0], hitBuf.q);
            ks = 1.0f;
            FastVecAdd(&D_L12_0023ADF0[k].v[1], hitBuf.q, vecH);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hitBuf.q + 4, &D_L12_0023ADE0[k].p[j1 - 1], D_L12_001B9E00);
                kf = RandomFloatRange(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                ApplyAxisRotationToQuaternion(vecH, vecH, hitBuf.q + 4, kf);
                FastVecAdd(D_L12_0023ADF0[k].v + j1, &D_L12_0023ADE0[k].p[j1 - 1], vecH);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = tmp[j2];
                FastVecSub(q, D_L12_0023ADF0[k].v + j2, &D_L12_0023ADE0[k].p[j2 - 1]);
                q[0] = q[0] + RandomSignedFloatRange(0.0f, 0.1f);
                q[1] = q[1] + RandomSignedFloatRange(0.0f, 0.1f);
                q[2] = q[2] + RandomSignedFloatRange(0.0f, 0.1f);
            }
            qcopy(&D_L12_0023ADF0[k].v[0], hitBuf.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(D_L12_0023ADF0[k].v + j2, &D_L12_0023ADE0[k].p[j2 - 1], tmp[j2]);
            {
                int x = D_L12_001B3760[k];
                int y = D_L12_001B3748[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                D_L12_001B3750[k] = fade;
            }
        }
    }
    {
        angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
        angle1 = RandomFloatRange(-0.52359885f, 1.0471977f);
        FastVecScale(vecH, vecC, D_L12_001AF2A8);
        ApplyAxisRotationToQuaternion(vecH, vecH, D_0018A560, angle1);
        ApplyAxisRotationToQuaternion(vecH, vecH, D_0018A560 + 0x10, angle0);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.2f, 0.6f);
        SpawnGroundEffectParticle(rope, 0xF, tsize * 0.3f, tsize, D_L12_001AF278 | 0x7F000000, 0, spin, vecH, 1, 0.0f);
        spin = -spin;
        SpawnGroundEffectParticle(rope, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, vecH, 1, 0.0f);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.15f, 3.0f);
        SpawnGroundEffectParticle(rope->b, 0xC, tsize * 0.1f, tsize, D_L12_001AF278 | 0x7F000000, 0, spin, D_L12_001A8F20, 1, 0.0f);
    }
}
