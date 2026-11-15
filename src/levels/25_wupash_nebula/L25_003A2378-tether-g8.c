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
extern Slot D_L25_002735F0[];
extern Cam D_00189E20;
extern char D_0018A560[];
extern int D_L25_001A8FF0;
extern float D_L25_001A8F20[] MACRO_ADDR;
extern int D_L25_001B2940;
extern short D_L25_001B2948[] MACRO_ADDR;
extern short D_L25_001B2950[] MACRO_ADDR;
extern short D_L25_001B2958[] MACRO_ADDR;
extern short D_L25_001B2960[] MACRO_ADDR;
extern float D_L25_001B90C0[];
extern char D_L25_001B9200[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L25_001BF658;
extern Tgt *D_L25_001FB120[];
extern float D_L25_0023AFF0[][4], D_L25_0023B000[][4];
extern Vec D_L25_0023B010[2][20];
extern V4 D_L25_0023B140;
extern float D_L25_0023B290[];
extern Vec D_L25_0023B2E0[];
extern float D_L25_0023B420[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L25_0023B460[];
extern Node5 D_L25_0023B470[];

extern float D_L25_001AEFF4 __attribute__((sda));
extern float D_L25_001AEFF8 __attribute__((sda));
extern float D_L25_001AEFFC __attribute__((sda));
extern float D_L25_001AF000 __attribute__((sda));
extern float D_L25_001AF004 __attribute__((sda));
extern float D_L25_001AF008 __attribute__((sda));
extern float D_L25_001AF00C __attribute__((sda));
extern float D_L25_001AF010 __attribute__((sda));
extern float D_L25_001AF014 __attribute__((sda));
extern float D_L25_001AF018 __attribute__((sda));
extern float D_L25_001AF01C __attribute__((sda));
extern float D_L25_001AF020 __attribute__((sda));
extern float D_L25_001AF024 __attribute__((sda));
extern float D_L25_001AF028 __attribute__((sda));
extern float D_L25_001AF02C __attribute__((sda));
extern float D_L25_001AF030 __attribute__((sda));
extern float D_L25_001AF044 __attribute__((sda));
extern float D_L25_001AF048 __attribute__((sda));
extern float D_L25_001AF088 __attribute__((sda));
extern float D_L25_001AF08C __attribute__((sda));
extern int D_L25_001AF058 __attribute__((sda));

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

/* Updates the lock-on tether: picks up to two targets, swings the chain of points toward them and spawns sparks. */
void func_L25_003A2378(Moby *tetherMoby)
{
    int locked = D_L25_002735F0[gItemSlotToRecord.cur].on != 0;
    float reach = D_L25_001AEFF4 * 0.05f;
    Rope *rope = tetherMoby->rope;
    float aimPointA[4] __attribute__((aligned(16)));
    float aimPointB[4] __attribute__((aligned(16)));
    float scratchVec[4] __attribute__((aligned(16)));
    Hit hitInfo __attribute__((aligned(16)));
    float ropeDir[4] __attribute__((aligned(16)));
    float linkOffset[4] __attribute__((aligned(16)));
    float pull[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float sparkOffset[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float tmpVec[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hitBuf __attribute__((aligned(16)));
    float sparkTmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int hitSomething, heldCount;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int heldIndex;
    Tgt *target;
    int targetIndex;
    float dist, ang, camAngle, sideDot, flatLength, score, projection, angleFactor, distFactor;
    float distToBest;
    float *infoA, *infoB;
    Tgt *targetA, *targetB;
    float length, blend;
    float amp, height, angle, oldHeight, divisor;
    int mirrorIndex;
    Tgt *hitTarget;
    float *hitInfoPtr;
    float *tempPtr, projectionA, *infoPtrA;
    int hitKindA;
    float projectionB, *infoPtrB;
    int hitKindB;
    float sparkSize, sparkFactor, sparkSign;
    int newIndex, updateIndex;
    float *diffVec;
    int spinSpeed;
    float glowSize, divisor2;
    Vec *prevPoint;
    float projection2, dirLength;
    /* Declared here, not in its block: k's pseudo number sets the bucket of k + 1 in the
       gcse hash, which orders the spill slots at 0x394 and 0x398. */
    short fade;
    int k;

    D_L25_001AF00C = FastAddRotations(D_L25_001AF00C, D_L25_001AF010);
    D_L25_001AF014 = fast_subtract_rotations(D_L25_001AF014, D_L25_001AF018);
    D_L25_001AF028 = FastAddRotations(D_L25_001AF028, D_L25_001AF02C);

    if (rope->lockA == 0 || (locked && rope->lockB == 0)) {
        if (rope->lockB != 0) {
            rope->lockA = rope->lockB;
            rope->u.s.h40 = rope->u.s.h42;
            rope->lockB = 0;
            rope->u.s.h42 = 0;
        } else {
            targetIndex = 0;
            for (target = D_L25_001FB120[0]; target != 0; target = D_L25_001FB120[++targetIndex]) {
                if (target != rope->lockA && target != rope->lockB) {
                    if (target != 0 && target->cls != 0 && target->cls->id == 5) {
                        if (target->kind != 0xFE) {
                        if (target->kind != 0xFD) {
                            if (GetMobyPrivateValue0(target) != 0) {
                                FastVecSub(aimPointA, target->pos, rope);
                                if (D_L25_001A8FF0 != 0) {
                                    projection = FastVecDot(aimPointA, gHeroState.ent + 0xE0);
                                    FastVecScale(aimPointB, gHeroState.ent + 0xE0, projection);
                                    FastVecSub(scratchVec, aimPointA, aimPointB);
                                    dist = FastVecLength(scratchVec);
                                } else {
                                    dist = vec_length_xy(aimPointA);
                                }
                                if (!(D_L25_001AEFF4 < dist)) {
                                    ang = FastDiffRots(D_L25_001B90C0[0x158 / 4], FastMatrixHelperA(target->pos[0] - D_L25_001B90C0[0x140 / 4], target->pos[1] - D_L25_001B90C0[0x144 / 4]));
                                    if (!(D_L25_001AEFFC < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `flatLength` test below ($f21, c.eq.s). */
                                        camAngle = 0.0f;
                                        if (D_L25_001A8FF0 != 0) {
                                            FastVecSub(aimPointB, target->pos, &gHeroState.x);
                                            projection2 = FastVecDot(aimPointB, gHeroState.ent + 0xE0);
                                            FastVecScale(scratchVec, gHeroState.ent + 0xE0, projection2);
                                            FastVecSub(aimPointB, aimPointB, scratchVec);
                                            sideDot = FastVecDot(aimPointB, gHeroState.ent + 0xC0);
                                            flatLength = FastVecLength(aimPointB);
                                            if (flatLength == 0.0f)
                                                continue;
                                            camAngle = 1.5707964f - FastAngleHelper(sideDot / flatLength);
                                        } else {
                                            camAngle = FastDiffRots(FastMatrixHelperA(target->pos[0] - gHeroState.x, target->pos[1] - gHeroState.y), gHeroState.f98);
                                        }
                                            if (!(D_L25_001AEFF8 < camAngle)) {
                                                angleFactor = (D_L25_001AEFFC - ang) / D_L25_001AEFFC;
                                                distFactor = (D_L25_001AEFF4 - dist) / D_L25_001AEFF4;
                                                score = angleFactor * D_L25_001AF08C + distFactor;
                                                if (bestScore < score) {
                                                    secondScore = bestScore;
                                                    bestScore = score;
                                                    second = best;
                                                    best = target;
                                                } else if (secondScore < score) {
                                                    second = target;
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
            if (FastFloatHelperD(&D_L25_001B2940) != 0)
                D_L25_001B2940 = 0xA;
        }
    }
    if (second != 0 && locked) {
        distToBest = fast_vec_dist(rope, best->pos);
        if (distToBest < D_L25_001AEFF4 && distToBest + fast_vec_dist(best->pos, second->pos) < D_L25_001AEFF4) {
            rope->u.s.h42 = 0;
            rope->lockB = second;
        }
    }
    len = 0.0f;
    if (rope->lockA != 0) {
        infoA = GetMobyPrivateValue0(rope->lockA);
        targetA = rope->lockA;
        qcopy(aimPointA, targetA->pos);
        FastVecScale(aimPointB, (char *)targetA + 0xE0, infoA[4]);
        FastVecAdd(aimPointA, aimPointA, aimPointB);
        len = fast_vec_dist(rope, aimPointA);
        reach = len * 0.05f;
    }
    if (rope->lockB != 0) {
        infoB = GetMobyPrivateValue0(rope->lockB);
        targetB = rope->lockB;
        qcopy(aimPointB, targetB->pos);
        FastVecScale(scratchVec, (char *)targetB + 0xE0, infoB[4]);
        FastVecAdd(aimPointB, aimPointB, scratchVec);
        reach = (fast_vec_dist(aimPointA, aimPointB) + len) * 0.05f;
    }
    if (locked)
        D_L25_001AF058 = 0x207F20;
    else
        D_L25_001AF058 = 0x7F2020;
    ClearVector128(scratchVec);
    make_hit_descriptor(&hitInfo, tetherMoby, 0x210000, scratchVec, (&D_L25_002735F0[gItemSlotToRecord.cur])->f70);
    hitInfo.kind = 5;
    hitInfo.flag = 1;
    hitInfo.tag = tetherMoby->tag;
    rope->count = 0x14;
    ProcessCollisionHit(rope, 0x10, gHeroState.ent, &hitInfo, 0.3f);
    FastVecSub(ropeDir, rope->b, rope);
    vec_scale_to_length(ropeDir, ropeDir, 1.0f);
    if (rope->lockA != 0 || rope->lockB != 0) {
        FastVecCross(linkOffset, ropeDir, (char *)&gHeroState + 0x2C0);
        ApplyAxisRotationToQuaternion(ropeDir, ropeDir, linkOffset, 0.17453295f);
    }
    hitSomething = 0;
    FastVecScale(velocity, ropeDir, reach);
    heldCount = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = rope->a;
        qcopy(&D_L25_0023B010[0][0], anchor);
    }
    {
        float *anchor = rope->a;
        qcopy(&D_L25_0023B010[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L25_001AF004 + (D_L25_001AF008 - D_L25_001AF004) * (IntToFloat(i) * 0.05f);
        height = amp * FastSinOrCosB(WrapAngleToPi(D_L25_001AF00C + (float)i * D_L25_001AF000));
        height += RandomSignedFloatRange(D_L25_001AF044, D_L25_001AF048);
        oldHeight = D_L25_0023B290[i];
        D_L25_0023B290[i] = height;
        D_L25_0023B010[0][i].f[2] = D_L25_0023B010[0][i].f[2] - oldHeight;
        TransformVectorOrCopy(&D_L25_0023B010[0][i], &D_L25_0023B010[0][i]);
        FastVecSub(linkOffset, &D_L25_0023B010[0][i], D_L25_0023B000[i]);
        lerp_vector(pull, linkOffset, velocity, 0.85f);
        {
            float chainLength = FastVecLength(pull);
            if (chainLength == 0.0f) {
                prevPoint = &D_L25_0023B010[0][i - 1];
                qcopy(&D_L25_0023B010[0][i], prevPoint);
            } else {
                FastVecScale(pull, pull, reach / chainLength);
                FastVecAdd(&D_L25_0023B010[0][i], D_L25_0023B000[i], pull);
                qcopy(velocity, pull);
            }
        }
        D_L25_0023B010[0][i].f[2] = D_L25_0023B010[0][i].f[2] + height;
        FastVecSub(linkOffset, &D_L25_0023B010[0][i], D_L25_0023B000[i]);
        if (rope->lockA != 0) {
            if (!locked || rope->lockB == 0) {
                FastVecSub(tmpVec, aimPointA, &D_L25_0023B010[0][i]);
                length = FastVecLength(tmpVec);
                if (length != 0.0f) {
                    if (i == 0x13) {
                        blend = 0.5f;
                        reach = length;
                    } else if (i >= 0x10) {
                        blend = 0.5f;
                        divisor = IntToFloat(0x13 - i);
                        reach = length / divisor;
                    } else {
                        blend = 0.1f;
                    }
                    FastVecScale(tmpVec, tmpVec, reach / length);
                    lerp_vector(velocity, velocity, tmpVec, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(tmpVec, aimPointB, &D_L25_0023B010[0][i]);
                else
                    FastVecSub(tmpVec, aimPointA, &D_L25_0023B010[0][i]);
                length = FastVecLength(tmpVec);
                if (length != 0.0f) {
                    if (i == 9 || i == 0x13) {
                        blend = 0.7f;
                        reach = length;
                    } else if (i >= 5 && i < 10) {
                        blend = 0.7f;
                        divisor = IntToFloat(9 - i);
                        reach = length / divisor;
                    } else if (i >= 0xF) {
                        blend = 0.7f;
                        divisor2 = IntToFloat(0x13 - i);
                        reach = length / divisor2;
                    } else {
                        blend = 0.2f;
                    }
                    FastVecScale(tmpVec, tmpVec, reach / length);
                    lerp_vector(velocity, velocity, tmpVec, blend);
                }
            }
        }
        if (i < 10) {
            angle = WrapAngleToPi(D_L25_001AF014 + (float)i * D_L25_001AF01C);
            amp = D_L25_001AF020 * FastSinOrCosB(WrapAngleToPi(D_L25_001AF028 + (float)i * D_L25_001AF030));
            qcopy(&D_L25_0023B010[1][i], &D_L25_0023B010[0][i]);
            height = amp * FastSinOrCosB(angle) + RandomSignedFloatRange(0.0f, 0.1f);
            D_L25_0023B420[i] = height;
            D_L25_0023B010[1][i].f[2] = D_L25_0023B010[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(FastMatrixHelperA(linkOffset[0], linkOffset[1]), 1.5707965f);
                {
                    float radial = D_L25_001AF024 * FastSinOrCosA(angle);
                    sparkOffset[0] = FastSinOrCosA(bearing) * radial;
                    sparkOffset[1] = FastSinOrCosB(bearing) * radial;
                    sparkOffset[2] = 0.0f;
                    qcopy_nc(&D_L25_0023B2E0[i], sparkOffset);
                }
            }
            FastVecAdd(&D_L25_0023B010[1][i], &D_L25_0023B010[1][i], sparkOffset);
        } else {
            mirrorIndex = 0x15 - i;
            qcopy(&D_L25_0023B010[1][i], &D_L25_0023B010[0][i]);
            D_L25_0023B010[1][i].f[2] = D_L25_0023B010[1][i].f[2] + D_L25_0023B420[mirrorIndex];
            FastVecAdd(&D_L25_0023B010[1][i], &D_L25_0023B010[1][i], &D_L25_0023B2E0[mirrorIndex]);
            qcopy(sparkOffset, &D_L25_0023B2E0[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(scratchVec, &D_L25_0023B010[0][i], D_L25_001B9200);
            if (D_L25_001A8FF0 != 0) {
                float projectionC = FastVecDot(scratchVec, gHeroState.ent + 0xE0);
                {
                    char *upAxis = gHeroState.ent + 0xE0;
                    FastVecScale(tmpVec, upAxis, projectionC);
                    FastVecSub(scratchVec, scratchVec, tmpVec);
                }
            } else {
                *(int *)&scratchVec[2] = 0;
            }
            dirLength = FastVecLength(scratchVec);
            if (dirLength == 0.0f)
                scratchVec[2] = 1.0f;
            else
                FastVecScale(scratchVec, scratchVec, 1.0f / dirLength);
            scratchVec[3] = 5627.925f;
            qcopy(&hitInfo, scratchVec);
            hitSomething = CollLine(D_L25_0023AFF0[i], &D_L25_0023B010[0][i], 0x10, tetherMoby, 0);
            if (hitSomething != 0) {
                hitTarget = D_L25_001BF658.hit;
                if (hitTarget != 0) {
                    hitInfoPtr = GetMobyPrivateValue0(hitTarget);
                    if (hitInfoPtr == 0) {
                        QueueMobyImpact(hitTarget, &hitInfo);
                    } else if (hitTarget->cls == 0 || hitTarget->cls->id != 5) {
                        QueueMobyImpact(hitTarget, &hitInfo);
                    } else {
                        hitSomething = 0;
                        held[heldCount++] = hitTarget;
                        hitTarget->f98 = 0;
                    }
                }
                if (hitSomething != 0) {
                    qcopy(&D_L25_0023B010[0][i], D_L25_001BF658.pos);
                    {
                        short last = i;
                        rope->count = last;
                    }
                    qcopy(rope->b, D_L25_001BF658.pos);
                    if (D_L25_001BF658.hit == 0) {
                        rope->lockA = 0;
                        rope->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (heldIndex = 0; heldIndex < heldCount; heldIndex++)
        held[heldIndex]->f98 = held[heldIndex]->cls->f10;
    if (hitSomething == 0)
        qcopy(rope->b, &D_L25_0023B140);
    if (rope->lockA != 0 && (rope->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tempPtr = hitBuf.q;
        FastVecSub(tmpVec, rope->lockA->pos, D_L25_001B9200);
        if (D_L25_001A8FF0 != 0) {
            projectionA = FastVecDot(tmpVec, gHeroState.ent + 0xE0);
            FastVecScale(tempPtr, gHeroState.ent + 0xE0, projectionA);
            FastVecSub(tmpVec, tmpVec, tempPtr);
        } else {
            *(int *)&tmpVec[2] = 0;
        }
        vec_scale_to_length(tmpVec, tmpVec, 1.0f);
        tmpVec[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.a.r, tetherMoby, 0x210000, tmpVec, (&D_L25_002735F0[gItemSlotToRecord.cur])->f70);
        hitBuf.a.r.kind = 5;
        hitBuf.a.r.flag = 3;
        hitBuf.a.r.tag = tetherMoby->tag;
        hitKindA = 5;
        QueueMobyImpact(rope->lockA, &hitBuf.a.r);
        infoPtrA = GetMobyPrivateValue0(rope->lockA);
        if (infoPtrA != 0) {
            if (((short *)infoPtrA)[2] == 1)
                hitKindA = 1;
        }
        {
            short result = hitKindA;
            rope->u.s.h44 = result;
        }
    }
    if (rope->lockB != 0 && (rope->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(tmpVec, rope->lockB->pos, D_L25_001B9200);
        if (D_L25_001A8FF0 != 0) {
            projectionB = FastVecDot(tmpVec, gHeroState.ent + 0xE0);
            FastVecScale(hitBuf.q, gHeroState.ent + 0xE0, projectionB);
            FastVecSub(tmpVec, tmpVec, hitBuf.q);
        } else {
            *(int *)&tmpVec[2] = 0;
        }
        vec_scale_to_length(tmpVec, tmpVec, 1.0f);
        tmpVec[3] = 5627.925f;
        make_hit_descriptor(&hitBuf.b.r, tetherMoby, 0x210000, tmpVec, (&D_L25_002735F0[gItemSlotToRecord.cur])->f70);
        hitBuf.b.r.kind = 5;
        hitBuf.b.r.flag = 3;
        hitBuf.b.r.tag = tetherMoby->tag;
        hitKindB = 5;
        QueueMobyImpact(rope->lockB, &hitBuf.b.r);
        infoPtrB = GetMobyPrivateValue0(rope->lockB);
        if (infoPtrB != 0) {
            if (((short *)infoPtrB)[2] == 1)
                hitKindB = 1;
        }
        {
            short result = hitKindB;
            rope->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = rope->a;
                qcopy(hitBuf.q, from);
            }
            sparkSize = 0.4f;
        } else {
            qcopy(hitBuf.q, rope->b);
            sparkSize = 0.5f;
        }
        if (FastDecTimer(&D_L25_001B2948[k]) != 0) {
            D_L25_001B2948[k] = D_L25_001B2958[k];
            D_L25_001B2950[k] = 0;
            angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
            angle1 = RandomFloatRange(-1.0471977f, 0.17453295f);
            FastVecScale(tmpVec, ropeDir, sparkSize);
            ApplyAxisRotationToQuaternion(tmpVec, tmpVec, D_0018A560, angle1);
            ApplyAxisRotationToQuaternion(tmpVec, tmpVec, D_0018A560 + 0x10, angle0);
            qcopy(&D_L25_0023B470[k].v[0], hitBuf.q);
            sparkSign = 1.0f;
            FastVecAdd(&D_L25_0023B470[k].v[1], hitBuf.q, tmpVec);
            for (newIndex = 2; newIndex < 5; newIndex++) {
                FastVecSub(hitBuf.q + 4, &D_L25_0023B460[k].p[newIndex - 1], D_L25_001B9200);
                sparkFactor = RandomFloatRange(0.17453295f, 0.9599312f) * sparkSign;
                sparkSign = -sparkSign;
                ApplyAxisRotationToQuaternion(tmpVec, tmpVec, hitBuf.q + 4, sparkFactor);
                FastVecAdd(D_L25_0023B470[k].v + newIndex, &D_L25_0023B460[k].p[newIndex - 1], tmpVec);
            }
        } else {
            for (updateIndex = 1; updateIndex < 5; updateIndex++) {
                diffVec = sparkTmp[updateIndex];
                FastVecSub(diffVec, D_L25_0023B470[k].v + updateIndex, &D_L25_0023B460[k].p[updateIndex - 1]);
                diffVec[0] = diffVec[0] + RandomSignedFloatRange(0.0f, 0.1f);
                diffVec[1] = diffVec[1] + RandomSignedFloatRange(0.0f, 0.1f);
                diffVec[2] = diffVec[2] + RandomSignedFloatRange(0.0f, 0.1f);
            }
            qcopy(&D_L25_0023B470[k].v[0], hitBuf.q);
            for (updateIndex = 1; updateIndex < 5; updateIndex++)
                FastVecAdd(D_L25_0023B470[k].v + updateIndex, &D_L25_0023B460[k].p[updateIndex - 1], sparkTmp[updateIndex]);
            {
                int x = D_L25_001B2960[k];
                int y = D_L25_001B2948[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                sparkFactor = IntToFloat(x);
                sparkFactor = sparkFactor / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - sparkFactor) * 32.0f);
                D_L25_001B2950[k] = fade;
            }
        }
    }
    {
        angle0 = RandomSignedFloatRange(0.52359885f, 1.0471977f);
        angle1 = RandomFloatRange(-0.52359885f, 1.0471977f);
        FastVecScale(tmpVec, ropeDir, D_L25_001AF088);
        ApplyAxisRotationToQuaternion(tmpVec, tmpVec, D_0018A560, angle1);
        ApplyAxisRotationToQuaternion(tmpVec, tmpVec, D_0018A560 + 0x10, angle0);
        spinSpeed = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spinSpeed = -spinSpeed;
        glowSize = RandomFloatRange(0.2f, 0.6f);
        SpawnGroundEffectParticle(rope, 0xF, glowSize * 0.3f, glowSize, D_L25_001AF058 | 0x7F000000, 0, spinSpeed, tmpVec, 1, 0.0f);
        spinSpeed = -spinSpeed;
        SpawnGroundEffectParticle(rope, 0xF, glowSize * 0.15f, glowSize * 0.5f, 0x307F7F7F, 0, spinSpeed, tmpVec, 1, 0.0f);
        spinSpeed = RandomIntRange(1, 8);
        if (RandomIntBelow(2) != 0)
            spinSpeed = -spinSpeed;
        glowSize = RandomFloatRange(0.15f, 3.0f);
        SpawnGroundEffectParticle(rope->b, 0xC, glowSize * 0.1f, glowSize, D_L25_001AF058 | 0x7F000000, 0, spinSpeed, D_L25_001A8F20, 1, 0.0f);
    }
}
