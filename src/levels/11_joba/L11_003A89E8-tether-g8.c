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
extern Slot D_L11_00279BA0[];
extern Cam D_00189E20;
extern char D_0018A560[];
extern int D_L11_001A8FF0;
extern float D_L11_001A8F20[] MACRO_ADDR;
extern int D_L11_001B3E40;
extern short D_L11_001B3E48[] MACRO_ADDR;
extern short D_L11_001B3E50[] MACRO_ADDR;
extern short D_L11_001B3E58[] MACRO_ADDR;
extern short D_L11_001B3E60[] MACRO_ADDR;
extern float D_L11_001BA780[];
extern char D_L11_001BA8C0[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L11_001C0D18;
extern Tgt *D_L11_001FC7E0[];
extern float D_L11_0023B430[][4], D_L11_0023B440[][4];
extern Vec D_L11_0023B450[2][20];
extern V4 D_L11_0023B580;
extern float D_L11_0023B6D0[];
extern Vec D_L11_0023B720[];
extern float D_L11_0023B860[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L11_0023B8A0[];
extern Node5 D_L11_0023B8B0[];

extern float D_L11_001AF164 __attribute__((sda));
extern float D_L11_001AF168 __attribute__((sda));
extern float D_L11_001AF16C __attribute__((sda));
extern float D_L11_001AF170 __attribute__((sda));
extern float D_L11_001AF174 __attribute__((sda));
extern float D_L11_001AF178 __attribute__((sda));
extern float D_L11_001AF17C __attribute__((sda));
extern float D_L11_001AF180 __attribute__((sda));
extern float D_L11_001AF184 __attribute__((sda));
extern float D_L11_001AF188 __attribute__((sda));
extern float D_L11_001AF18C __attribute__((sda));
extern float D_L11_001AF190 __attribute__((sda));
extern float D_L11_001AF194 __attribute__((sda));
extern float D_L11_001AF198 __attribute__((sda));
extern float D_L11_001AF19C __attribute__((sda));
extern float D_L11_001AF1A0 __attribute__((sda));
extern float D_L11_001AF1B4 __attribute__((sda));
extern float D_L11_001AF1B8 __attribute__((sda));
extern float D_L11_001AF1F8 __attribute__((sda));
extern float D_L11_001AF1FC __attribute__((sda));
extern int D_L11_001AF1C8 __attribute__((sda));

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

/* Updates the lock-on tether. It picks up to two targets, bends a chain of twenty points
   from the player's hand to them, and spawns sparks. */
void func_L11_003A89E8(Moby *self)
{
    int locked = D_L11_00279BA0[gItemSlotToRecord.cur].on != 0;
    float reach = D_L11_001AF164 * 0.05f;
    Rope *st = self->rope;
    float lockPointA[4] __attribute__((aligned(16)));
    float va[4] __attribute__((aligned(16)));
    float vb[4] __attribute__((aligned(16)));
    Hit hit1 __attribute__((aligned(16)));
    float chainDirection[4] __attribute__((aligned(16)));
    float segmentDelta[4] __attribute__((aligned(16)));
    float segmentStep[4] __attribute__((aligned(16)));
    float pullVector[4] __attribute__((aligned(16)));
    float sparkOffset[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float tempVector[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hb __attribute__((aligned(16)));
    float tmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int got, nheld;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int n;
    Tgt *candidate;
    int sn;
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

    D_L11_001AF17C = FastAddRotations(D_L11_001AF17C, D_L11_001AF180);
    D_L11_001AF184 = fast_subtract_rotations(D_L11_001AF184, D_L11_001AF188);
    D_L11_001AF198 = FastAddRotations(D_L11_001AF198, D_L11_001AF19C);

    if (st->lockA == 0 || (locked && st->lockB == 0)) {
        if (st->lockB != 0) {
            st->lockA = st->lockB;
            st->u.s.h40 = st->u.s.h42;
            st->lockB = 0;
            st->u.s.h42 = 0;
        } else {
            sn = 0;
            for (candidate = D_L11_001FC7E0[0]; candidate != 0; candidate = D_L11_001FC7E0[++sn]) {
                if (candidate != st->lockA && candidate != st->lockB) {
                    if (candidate != 0 && candidate->cls != 0 && candidate->cls->id == 5) {
                        if (candidate->kind != 0xFE) {
                        if (candidate->kind != 0xFD) {
                            if (GetMobyPrivateValue0(candidate) != 0) {
                                FastVecSub(lockPointA, candidate->pos, st);
                                if (D_L11_001A8FF0 != 0) {
                                    proj = FastVecDot(lockPointA, gHeroState.ent + 0xE0);
                                    FastVecScale(va, gHeroState.ent + 0xE0, proj);
                                    FastVecSub(vb, lockPointA, va);
                                    dist = FastVecLength(vb);
                                } else {
                                    dist = vec_length_xy(lockPointA);
                                }
                                if (!(D_L11_001AF164 < dist)) {
                                    ang = FastDiffRots(D_L11_001BA780[0x158 / 4], FastMatrixHelperA(candidate->pos[0] - D_L11_001BA780[0x140 / 4], candidate->pos[1] - D_L11_001BA780[0x144 / 4]));
                                    if (!(D_L11_001AF16C < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sa2 = 0.0f;
                                        if (D_L11_001A8FF0 != 0) {
                                            FastVecSub(va, candidate->pos, &gHeroState.x);
                                            proj2 = FastVecDot(va, gHeroState.ent + 0xE0);
                                            FastVecScale(vb, gHeroState.ent + 0xE0, proj2);
                                            FastVecSub(va, va, vb);
                                            cs = FastVecDot(va, gHeroState.ent + 0xC0);
                                            sm = FastVecLength(va);
                                            if (sm == 0.0f)
                                                continue;
                                            sa2 = 1.5707964f - FastAngleHelper(cs / sm);
                                        } else {
                                            sa2 = FastDiffRots(FastMatrixHelperA(candidate->pos[0] - gHeroState.x, candidate->pos[1] - gHeroState.y), gHeroState.f98);
                                        }
                                            if (!(D_L11_001AF168 < sa2)) {
                                                fa = (D_L11_001AF16C - ang) / D_L11_001AF16C;
                                                fb = (D_L11_001AF164 - dist) / D_L11_001AF164;
                                                score = fa * D_L11_001AF1FC + fb;
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
            if (FastFloatHelperD(&D_L11_001B3E40) != 0)
                D_L11_001B3E40 = 0xA;
        }
    }
    if (second != 0 && locked) {
        d0 = fast_vec_dist(st, best->pos);
        if (d0 < D_L11_001AF164 && d0 + fast_vec_dist(best->pos, second->pos) < D_L11_001AF164) {
            st->u.s.h42 = 0;
            st->lockB = second;
        }
    }
    len = 0.0f;
    if (st->lockA != 0) {
        ia = GetMobyPrivateValue0(st->lockA);
        ta = st->lockA;
        qcopy(lockPointA, ta->pos);
        FastVecScale(va, (char *)ta + 0xE0, ia[4]);
        FastVecAdd(lockPointA, lockPointA, va);
        len = fast_vec_dist(st, lockPointA);
        reach = len * 0.05f;
    }
    if (st->lockB != 0) {
        ib = GetMobyPrivateValue0(st->lockB);
        tb = st->lockB;
        qcopy(va, tb->pos);
        FastVecScale(vb, (char *)tb + 0xE0, ib[4]);
        FastVecAdd(va, va, vb);
        reach = (fast_vec_dist(lockPointA, va) + len) * 0.05f;
    }
    if (locked)
        D_L11_001AF1C8 = 0x207F20;
    else
        D_L11_001AF1C8 = 0x7F2020;
    ClearVector128(vb);
    make_hit_descriptor(&hit1, self, 0x210000, vb, (&D_L11_00279BA0[gItemSlotToRecord.cur])->f70);
    hit1.kind = 5;
    hit1.flag = 1;
    hit1.tag = self->tag;
    st->count = 0x14;
    ProcessCollisionHit(st, 0x10, gHeroState.ent, &hit1, 0.3f);
    FastVecSub(chainDirection, st->b, st);
    vec_scale_to_length(chainDirection, chainDirection, 1.0f);
    if (st->lockA != 0 || st->lockB != 0) {
        FastVecCross(segmentDelta, chainDirection, (char *)&gHeroState + 0x2C0);
        ApplyAxisRotationToQuaternion(chainDirection, chainDirection, segmentDelta, 0.17453295f);
    }
    got = 0;
    FastVecScale(pullVector, chainDirection, reach);
    nheld = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = st->a;
        qcopy(&D_L11_0023B450[0][0], anchor);
    }
    {
        float *anchor = st->a;
        qcopy(&D_L11_0023B450[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L11_001AF174 + (D_L11_001AF178 - D_L11_001AF174) * (IntToFloat(i) * 0.05f);
        height = amp * FastSinOrCosB(WrapAngleToPi(D_L11_001AF17C + (float)i * D_L11_001AF170));
        height += RandomSignedFloatRange(D_L11_001AF1B4, D_L11_001AF1B8);
        old = D_L11_0023B6D0[i];
        D_L11_0023B6D0[i] = height;
        D_L11_0023B450[0][i].f[2] = D_L11_0023B450[0][i].f[2] - old;
        TransformVectorOrCopy(&D_L11_0023B450[0][i], &D_L11_0023B450[0][i]);
        FastVecSub(segmentDelta, &D_L11_0023B450[0][i], D_L11_0023B440[i]);
        lerp_vector(segmentStep, segmentDelta, pullVector, 0.85f);
        {
            float cm = FastVecLength(segmentStep);
            if (cm == 0.0f) {
                prev = &D_L11_0023B450[0][i - 1];
                qcopy(&D_L11_0023B450[0][i], prev);
            } else {
                FastVecScale(segmentStep, segmentStep, reach / cm);
                FastVecAdd(&D_L11_0023B450[0][i], D_L11_0023B440[i], segmentStep);
                qcopy(pullVector, segmentStep);
            }
        }
        D_L11_0023B450[0][i].f[2] = D_L11_0023B450[0][i].f[2] + height;
        FastVecSub(segmentDelta, &D_L11_0023B450[0][i], D_L11_0023B440[i]);
        if (st->lockA != 0) {
            if (!locked || st->lockB == 0) {
                FastVecSub(tempVector, lockPointA, &D_L11_0023B450[0][i]);
                length = FastVecLength(tempVector);
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
                    FastVecScale(tempVector, tempVector, reach / length);
                    lerp_vector(pullVector, pullVector, tempVector, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(tempVector, va, &D_L11_0023B450[0][i]);
                else
                    FastVecSub(tempVector, lockPointA, &D_L11_0023B450[0][i]);
                length = FastVecLength(tempVector);
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
                    FastVecScale(tempVector, tempVector, reach / length);
                    lerp_vector(pullVector, pullVector, tempVector, blend);
                }
            }
        }
        if (i < 10) {
            angle = WrapAngleToPi(D_L11_001AF184 + (float)i * D_L11_001AF18C);
            amp = D_L11_001AF190 * FastSinOrCosB(WrapAngleToPi(D_L11_001AF198 + (float)i * D_L11_001AF1A0));
            qcopy(&D_L11_0023B450[1][i], &D_L11_0023B450[0][i]);
            height = amp * FastSinOrCosB(angle) + RandomSignedFloatRange(0.0f, 0.1f);
            D_L11_0023B860[i] = height;
            D_L11_0023B450[1][i].f[2] = D_L11_0023B450[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(FastMatrixHelperA(segmentDelta[0], segmentDelta[1]), 1.5707965f);
                {
                    float radial = D_L11_001AF194 * FastSinOrCosA(angle);
                    sparkOffset[0] = FastSinOrCosA(bearing) * radial;
                    sparkOffset[1] = FastSinOrCosB(bearing) * radial;
                    sparkOffset[2] = 0.0f;
                    qcopy_nc(&D_L11_0023B720[i], sparkOffset);
                }
            }
            FastVecAdd(&D_L11_0023B450[1][i], &D_L11_0023B450[1][i], sparkOffset);
        } else {
            fa2 = 0x15 - i;
            qcopy(&D_L11_0023B450[1][i], &D_L11_0023B450[0][i]);
            D_L11_0023B450[1][i].f[2] = D_L11_0023B450[1][i].f[2] + D_L11_0023B860[fa2];
            FastVecAdd(&D_L11_0023B450[1][i], &D_L11_0023B450[1][i], &D_L11_0023B720[fa2]);
            qcopy(sparkOffset, &D_L11_0023B720[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(vb, &D_L11_0023B450[0][i], D_L11_001BA8C0);
            if (D_L11_001A8FF0 != 0) {
                float cpj = FastVecDot(vb, gHeroState.ent + 0xE0);
                {
                    char *ax = gHeroState.ent + 0xE0;
                    FastVecScale(tempVector, ax, cpj);
                    FastVecSub(vb, vb, tempVector);
                }
            } else {
                *(int *)&vb[2] = 0;
            }
            cm2 = FastVecLength(vb);
            if (cm2 == 0.0f)
                vb[2] = 1.0f;
            else
                FastVecScale(vb, vb, 1.0f / cm2);
            vb[3] = 5627.925f;
            qcopy(&hit1, vb);
            got = CollLine(D_L11_0023B430[i], &D_L11_0023B450[0][i], 0x10, self, 0);
            if (got != 0) {
                ht = D_L11_001C0D18.hit;
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
                    qcopy(&D_L11_0023B450[0][i], D_L11_001C0D18.pos);
                    {
                        short last = i;
                        st->count = last;
                    }
                    qcopy(st->b, D_L11_001C0D18.pos);
                    if (D_L11_001C0D18.hit == 0) {
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
        qcopy(st->b, &D_L11_0023B580);
    if (st->lockA != 0 && (st->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hb.q;
        FastVecSub(tempVector, st->lockA->pos, D_L11_001BA8C0);
        if (D_L11_001A8FF0 != 0) {
            apj = FastVecDot(tempVector, gHeroState.ent + 0xE0);
            FastVecScale(tv, gHeroState.ent + 0xE0, apj);
            FastVecSub(tempVector, tempVector, tv);
        } else {
            *(int *)&tempVector[2] = 0;
        }
        vec_scale_to_length(tempVector, tempVector, 1.0f);
        tempVector[3] = 5627.925f;
        make_hit_descriptor(&hb.a.r, self, 0x210000, tempVector, (&D_L11_00279BA0[gItemSlotToRecord.cur])->f70);
        hb.a.r.kind = 5;
        hb.a.r.flag = 3;
        hb.a.r.tag = self->tag;
        an = 5;
        QueueMobyImpact(st->lockA, &hb.a.r);
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
        FastVecSub(tempVector, st->lockB->pos, D_L11_001BA8C0);
        if (D_L11_001A8FF0 != 0) {
            bpj = FastVecDot(tempVector, gHeroState.ent + 0xE0);
            FastVecScale(hb.q, gHeroState.ent + 0xE0, bpj);
            FastVecSub(tempVector, tempVector, hb.q);
        } else {
            *(int *)&tempVector[2] = 0;
        }
        vec_scale_to_length(tempVector, tempVector, 1.0f);
        tempVector[3] = 5627.925f;
        make_hit_descriptor(&hb.b.r, self, 0x210000, tempVector, (&D_L11_00279BA0[gItemSlotToRecord.cur])->f70);
        hb.b.r.kind = 5;
        hb.b.r.flag = 3;
        hb.b.r.tag = self->tag;
        bn = 5;
        QueueMobyImpact(st->lockB, &hb.b.r);
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
                qcopy(hb.q, from);
            }
            ksize = 0.4f;
        } else {
            qcopy(hb.q, st->b);
            ksize = 0.5f;
        }
        if (FastDecTimer(&D_L11_001B3E48[k]) != 0) {
            D_L11_001B3E48[k] = D_L11_001B3E58[k];
            D_L11_001B3E50[k] = 0;
            angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
            angle1 = RandomFloatRange(-1.0471977f, 0.17453295f);
            FastVecScale(tempVector, chainDirection, ksize);
            ApplyAxisRotationToQuaternion(tempVector, tempVector, D_0018A560, angle1);
            ApplyAxisRotationToQuaternion(tempVector, tempVector, D_0018A560 + 0x10, angle0);
            qcopy(&D_L11_0023B8B0[k].v[0], hb.q);
            ks = 1.0f;
            FastVecAdd(&D_L11_0023B8B0[k].v[1], hb.q, tempVector);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hb.q + 4, &D_L11_0023B8A0[k].p[j1 - 1], D_L11_001BA8C0);
                kf = RandomFloatRange(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                ApplyAxisRotationToQuaternion(tempVector, tempVector, hb.q + 4, kf);
                FastVecAdd(D_L11_0023B8B0[k].v + j1, &D_L11_0023B8A0[k].p[j1 - 1], tempVector);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = tmp[j2];
                FastVecSub(q, D_L11_0023B8B0[k].v + j2, &D_L11_0023B8A0[k].p[j2 - 1]);
                q[0] = q[0] + RandomSignedFloatRange(0.0f, 0.1f);
                q[1] = q[1] + RandomSignedFloatRange(0.0f, 0.1f);
                q[2] = q[2] + RandomSignedFloatRange(0.0f, 0.1f);
            }
            qcopy(&D_L11_0023B8B0[k].v[0], hb.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(D_L11_0023B8B0[k].v + j2, &D_L11_0023B8A0[k].p[j2 - 1], tmp[j2]);
            {
                int x = D_L11_001B3E60[k];
                int y = D_L11_001B3E48[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                D_L11_001B3E50[k] = fade;
            }
        }
    }
    {
        angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
        angle1 = RandomFloatRange(-0.52359885f, 1.0471977f);
        FastVecScale(tempVector, chainDirection, D_L11_001AF1F8);
        ApplyAxisRotationToQuaternion(tempVector, tempVector, D_0018A560, angle1);
        ApplyAxisRotationToQuaternion(tempVector, tempVector, D_0018A560 + 0x10, angle0);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.2f, 0.6f);
        SpawnGroundEffectParticle(st, 0xF, tsize * 0.3f, tsize, D_L11_001AF1C8 | 0x7F000000, 0, spin, tempVector, 1, 0.0f);
        spin = -spin;
        SpawnGroundEffectParticle(st, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, tempVector, 1, 0.0f);
        spin = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spin = -spin;
        tsize = RandomFloatRange(0.15f, 3.0f);
        SpawnGroundEffectParticle(st->b, 0xC, tsize * 0.1f, tsize, D_L11_001AF1C8 | 0x7F000000, 0, spin, D_L11_001A8F20, 1, 0.0f);
    }
}
