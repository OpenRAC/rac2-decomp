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

extern Level g_item_slot_to_record;
extern Slot D_L17_00263470[];
extern Cam g_hero_state;
extern char D_0018A560[];
extern int D_L17_001A8FF0;
extern float D_L17_001A8F20[] MACRO_ADDR;
extern int D_L17_001B34C0;
extern short D_L17_001B34C8[] MACRO_ADDR;
extern short D_L17_001B34D0[] MACRO_ADDR;
extern short D_L17_001B34D8[] MACRO_ADDR;
extern short D_L17_001B34E0[] MACRO_ADDR;
extern float D_L17_001B9A80[];
extern char D_L17_001B9BC0[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L17_001C0018;
extern Tgt *D_L17_001FBAE0[];
extern float D_L17_0023A730[][4], D_L17_0023A740[][4];
extern Vec D_L17_0023A750[2][20];
extern V4 D_L17_0023A880;
extern float D_L17_0023A9D0[];
extern Vec D_L17_0023AA20[];
extern float D_L17_0023AB60[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L17_0023ABA0[];
extern Node5 D_L17_0023ABB0[];

extern float D_L17_001AF014 __attribute__((sda));
extern float D_L17_001AF018 __attribute__((sda));
extern float D_L17_001AF01C __attribute__((sda));
extern float D_L17_001AF020 __attribute__((sda));
extern float D_L17_001AF024 __attribute__((sda));
extern float D_L17_001AF028 __attribute__((sda));
extern float D_L17_001AF02C __attribute__((sda));
extern float D_L17_001AF030 __attribute__((sda));
extern float D_L17_001AF034 __attribute__((sda));
extern float D_L17_001AF038 __attribute__((sda));
extern float D_L17_001AF03C __attribute__((sda));
extern float D_L17_001AF040 __attribute__((sda));
extern float D_L17_001AF044 __attribute__((sda));
extern float D_L17_001AF048 __attribute__((sda));
extern float D_L17_001AF04C __attribute__((sda));
extern float D_L17_001AF050 __attribute__((sda));
extern float D_L17_001AF064 __attribute__((sda));
extern float D_L17_001AF068 __attribute__((sda));
extern float D_L17_001AF0A8 __attribute__((sda));
extern float D_L17_001AF0AC __attribute__((sda));
extern int D_L17_001AF078 __attribute__((sda));

extern int CollLine(void *, void *, int, void *, void *);
extern int coll_process_hit(void *, int, char *, void *, float);
extern int math_fast_float_d(void *);
extern int FastDecTimer(void *);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecLength(void *);
extern float vec_length_xy(void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_angle_helper(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastDiffRots(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern float *moby_get_private_value_0(void *);
extern float math_wrap_angle_to_pi(float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern void vec_transform_or_copy(void *, void *);

/* Updates the lock-on tether. It picks up to two nearby targets in front of the player and
   hangs a wobbling chain of twenty points from the player's hand to them. The chain stops where
   it hits something. It also spawns the glow spots and sparks along the way. */
void gadget_l17_update_lock_on_tether(Moby *self)
{
    int locked = D_L17_00263470[g_item_slot_to_record.cur].on != 0;
    float reach = D_L17_001AF014 * 0.05f;
    Rope *rope = self->rope;
    float vecA[4] __attribute__((aligned(16)));
    float vecB[4] __attribute__((aligned(16)));
    float vecC[4] __attribute__((aligned(16)));
    Hit hit1 __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float segment[4] __attribute__((aligned(16)));
    float pull[4] __attribute__((aligned(16)));
    float drift[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float scratch[4] __attribute__((aligned(16)));
    union {
        float raw[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hb __attribute__((aligned(16)));
    float tmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int hitFound, heldCount;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int heldIndex;
    Tgt *target;
    int targetIndex;
    float dist, ang, aimAngle, sideDot, sideLength, score, proj, angleScore, distScore;
    float firstDist;
    float *infoA, *infoB;
    Tgt *targetA, *targetB;
    float length, blend;
    float amp, height, angle, old, divisor;
    int mirrorIndex;
    Tgt *hitTarget;
    float *hitInfo;
    float *tempVec, projA, *infoAHit;
    int kindA;
    float projB, *infoBHit;
    int kindB;
    float sparkSize, sparkAmount, sparkSign;
    int linkIndex, pointIndex;
    float *raw;
    int spin;
    float flareSize, divisorB;
    Vec *prev;
    float projAim, segLength;
    /* Declared here, not in its block: k's pseudo number sets the bucket of k + 1 in the
       gcse hash, which orders the spill slots at 0x394 and 0x398. */
    short fade;
    int k;

    D_L17_001AF02C = FastAddRotations(D_L17_001AF02C, D_L17_001AF030);
    D_L17_001AF034 = fast_subtract_rotations(D_L17_001AF034, D_L17_001AF038);
    D_L17_001AF048 = FastAddRotations(D_L17_001AF048, D_L17_001AF04C);

    if (rope->lockA == 0 || (locked && rope->lockB == 0)) {
        if (rope->lockB != 0) {
            rope->lockA = rope->lockB;
            rope->u.s.h40 = rope->u.s.h42;
            rope->lockB = 0;
            rope->u.s.h42 = 0;
        } else {
            targetIndex = 0;
            for (target = D_L17_001FBAE0[0]; target != 0; target = D_L17_001FBAE0[++targetIndex]) {
                if (target != rope->lockA && target != rope->lockB) {
                    if (target != 0 && target->cls != 0 && target->cls->id == 5) {
                        if (target->kind != 0xFE) {
                        if (target->kind != 0xFD) {
                            if (moby_get_private_value_0(target) != 0) {
                                FastVecSub(vecA, target->pos, rope);
                                if (D_L17_001A8FF0 != 0) {
                                    proj = FastVecDot(vecA, g_hero_state.ent + 0xE0);
                                    FastVecScale(vecB, g_hero_state.ent + 0xE0, proj);
                                    FastVecSub(vecC, vecA, vecB);
                                    dist = FastVecLength(vecC);
                                } else {
                                    dist = vec_length_xy(vecA);
                                }
                                if (!(D_L17_001AF014 < dist)) {
                                    ang = FastDiffRots(D_L17_001B9A80[0x158 / 4], mat_fast_helper_a(target->pos[0] - D_L17_001B9A80[0x140 / 4], target->pos[1] - D_L17_001B9A80[0x144 / 4]));
                                    if (!(D_L17_001AF01C < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sideLength` test below ($f21, c.eq.s). */
                                        aimAngle = 0.0f;
                                        if (D_L17_001A8FF0 != 0) {
                                            FastVecSub(vecB, target->pos, &g_hero_state.x);
                                            projAim = FastVecDot(vecB, g_hero_state.ent + 0xE0);
                                            FastVecScale(vecC, g_hero_state.ent + 0xE0, projAim);
                                            FastVecSub(vecB, vecB, vecC);
                                            sideDot = FastVecDot(vecB, g_hero_state.ent + 0xC0);
                                            sideLength = FastVecLength(vecB);
                                            if (sideLength == 0.0f)
                                                continue;
                                            aimAngle = 1.5707964f - math_fast_angle_helper(sideDot / sideLength);
                                        } else {
                                            aimAngle = FastDiffRots(mat_fast_helper_a(target->pos[0] - g_hero_state.x, target->pos[1] - g_hero_state.y), g_hero_state.f98);
                                        }
                                            if (!(D_L17_001AF018 < aimAngle)) {
                                                angleScore = (D_L17_001AF01C - ang) / D_L17_001AF01C;
                                                distScore = (D_L17_001AF014 - dist) / D_L17_001AF014;
                                                score = angleScore * D_L17_001AF0AC + distScore;
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
            if (math_fast_float_d(&D_L17_001B34C0) != 0)
                D_L17_001B34C0 = 0xA;
        }
    }
    if (second != 0 && locked) {
        firstDist = fast_vec_dist(rope, best->pos);
        if (firstDist < D_L17_001AF014 && firstDist + fast_vec_dist(best->pos, second->pos) < D_L17_001AF014) {
            rope->u.s.h42 = 0;
            rope->lockB = second;
        }
    }
    len = 0.0f;
    if (rope->lockA != 0) {
        infoA = moby_get_private_value_0(rope->lockA);
        targetA = rope->lockA;
        qcopy(vecA, targetA->pos);
        FastVecScale(vecB, (char *)targetA + 0xE0, infoA[4]);
        FastVecAdd(vecA, vecA, vecB);
        len = fast_vec_dist(rope, vecA);
        reach = len * 0.05f;
    }
    if (rope->lockB != 0) {
        infoB = moby_get_private_value_0(rope->lockB);
        targetB = rope->lockB;
        qcopy(vecB, targetB->pos);
        FastVecScale(vecC, (char *)targetB + 0xE0, infoB[4]);
        FastVecAdd(vecB, vecB, vecC);
        reach = (fast_vec_dist(vecA, vecB) + len) * 0.05f;
    }
    if (locked)
        D_L17_001AF078 = 0x207F20;
    else
        D_L17_001AF078 = 0x7F2020;
    vec_clear_128(vecC);
    make_hit_descriptor(&hit1, self, 0x210000, vecC, (&D_L17_00263470[g_item_slot_to_record.cur])->f70);
    hit1.kind = 5;
    hit1.flag = 1;
    hit1.tag = self->tag;
    rope->count = 0x14;
    coll_process_hit(rope, 0x10, g_hero_state.ent, &hit1, 0.3f);
    FastVecSub(direction, rope->b, rope);
    vec_scale_to_length(direction, direction, 1.0f);
    if (rope->lockA != 0 || rope->lockB != 0) {
        FastVecCross(segment, direction, (char *)&g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(direction, direction, segment, 0.17453295f);
    }
    hitFound = 0;
    FastVecScale(drift, direction, reach);
    heldCount = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = rope->a;
        qcopy(&D_L17_0023A750[0][0], anchor);
    }
    {
        float *anchor = rope->a;
        qcopy(&D_L17_0023A750[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L17_001AF024 + (D_L17_001AF028 - D_L17_001AF024) * (IntToFloat(i) * 0.05f);
        height = amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L17_001AF02C + (float)i * D_L17_001AF020));
        height += math_random_signed_float_range(D_L17_001AF064, D_L17_001AF068);
        old = D_L17_0023A9D0[i];
        D_L17_0023A9D0[i] = height;
        D_L17_0023A750[0][i].f[2] = D_L17_0023A750[0][i].f[2] - old;
        vec_transform_or_copy(&D_L17_0023A750[0][i], &D_L17_0023A750[0][i]);
        FastVecSub(segment, &D_L17_0023A750[0][i], D_L17_0023A740[i]);
        lerp_vector(pull, segment, drift, 0.85f);
        {
            float cm = FastVecLength(pull);
            if (cm == 0.0f) {
                prev = &D_L17_0023A750[0][i - 1];
                qcopy(&D_L17_0023A750[0][i], prev);
            } else {
                FastVecScale(pull, pull, reach / cm);
                FastVecAdd(&D_L17_0023A750[0][i], D_L17_0023A740[i], pull);
                qcopy(drift, pull);
            }
        }
        D_L17_0023A750[0][i].f[2] = D_L17_0023A750[0][i].f[2] + height;
        FastVecSub(segment, &D_L17_0023A750[0][i], D_L17_0023A740[i]);
        if (rope->lockA != 0) {
            if (!locked || rope->lockB == 0) {
                FastVecSub(scratch, vecA, &D_L17_0023A750[0][i]);
                length = FastVecLength(scratch);
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
                    FastVecScale(scratch, scratch, reach / length);
                    lerp_vector(drift, drift, scratch, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(scratch, vecB, &D_L17_0023A750[0][i]);
                else
                    FastVecSub(scratch, vecA, &D_L17_0023A750[0][i]);
                length = FastVecLength(scratch);
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
                        divisorB = IntToFloat(0x13 - i);
                        reach = length / divisorB;
                    } else {
                        blend = 0.2f;
                    }
                    FastVecScale(scratch, scratch, reach / length);
                    lerp_vector(drift, drift, scratch, blend);
                }
            }
        }
        if (i < 10) {
            angle = math_wrap_angle_to_pi(D_L17_001AF034 + (float)i * D_L17_001AF03C);
            amp = D_L17_001AF040 * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L17_001AF048 + (float)i * D_L17_001AF050));
            qcopy(&D_L17_0023A750[1][i], &D_L17_0023A750[0][i]);
            height = amp * math_fast_sin_or_cos_b(angle) + math_random_signed_float_range(0.0f, 0.1f);
            D_L17_0023AB60[i] = height;
            D_L17_0023A750[1][i].f[2] = D_L17_0023A750[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(mat_fast_helper_a(segment[0], segment[1]), 1.5707965f);
                {
                    float radial = D_L17_001AF044 * math_fast_sin_or_cos_a(angle);
                    offset[0] = math_fast_sin_or_cos_a(bearing) * radial;
                    offset[1] = math_fast_sin_or_cos_b(bearing) * radial;
                    offset[2] = 0.0f;
                    qcopy_nc(&D_L17_0023AA20[i], offset);
                }
            }
            FastVecAdd(&D_L17_0023A750[1][i], &D_L17_0023A750[1][i], offset);
        } else {
            mirrorIndex = 0x15 - i;
            qcopy(&D_L17_0023A750[1][i], &D_L17_0023A750[0][i]);
            D_L17_0023A750[1][i].f[2] = D_L17_0023A750[1][i].f[2] + D_L17_0023AB60[mirrorIndex];
            FastVecAdd(&D_L17_0023A750[1][i], &D_L17_0023A750[1][i], &D_L17_0023AA20[mirrorIndex]);
            qcopy(offset, &D_L17_0023AA20[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(vecC, &D_L17_0023A750[0][i], D_L17_001B9BC0);
            if (D_L17_001A8FF0 != 0) {
                float cpj = FastVecDot(vecC, g_hero_state.ent + 0xE0);
                {
                    char *ax = g_hero_state.ent + 0xE0;
                    FastVecScale(scratch, ax, cpj);
                    FastVecSub(vecC, vecC, scratch);
                }
            } else {
                *(int *)&vecC[2] = 0;
            }
            segLength = FastVecLength(vecC);
            if (segLength == 0.0f)
                vecC[2] = 1.0f;
            else
                FastVecScale(vecC, vecC, 1.0f / segLength);
            vecC[3] = 5627.925f;
            qcopy(&hit1, vecC);
            hitFound = CollLine(D_L17_0023A730[i], &D_L17_0023A750[0][i], 0x10, self, 0);
            if (hitFound != 0) {
                hitTarget = D_L17_001C0018.hit;
                if (hitTarget != 0) {
                    hitInfo = moby_get_private_value_0(hitTarget);
                    if (hitInfo == 0) {
                        QueueMobyImpact(hitTarget, &hit1);
                    } else if (hitTarget->cls == 0 || hitTarget->cls->id != 5) {
                        QueueMobyImpact(hitTarget, &hit1);
                    } else {
                        hitFound = 0;
                        held[heldCount++] = hitTarget;
                        hitTarget->f98 = 0;
                    }
                }
                if (hitFound != 0) {
                    qcopy(&D_L17_0023A750[0][i], D_L17_001C0018.pos);
                    {
                        short last = i;
                        rope->count = last;
                    }
                    qcopy(rope->b, D_L17_001C0018.pos);
                    if (D_L17_001C0018.hit == 0) {
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
    if (hitFound == 0)
        qcopy(rope->b, &D_L17_0023A880);
    if (rope->lockA != 0 && (rope->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tempVec = hb.raw;
        FastVecSub(scratch, rope->lockA->pos, D_L17_001B9BC0);
        if (D_L17_001A8FF0 != 0) {
            projA = FastVecDot(scratch, g_hero_state.ent + 0xE0);
            FastVecScale(tempVec, g_hero_state.ent + 0xE0, projA);
            FastVecSub(scratch, scratch, tempVec);
        } else {
            *(int *)&scratch[2] = 0;
        }
        vec_scale_to_length(scratch, scratch, 1.0f);
        scratch[3] = 5627.925f;
        make_hit_descriptor(&hb.a.r, self, 0x210000, scratch, (&D_L17_00263470[g_item_slot_to_record.cur])->f70);
        hb.a.r.kind = 5;
        hb.a.r.flag = 3;
        hb.a.r.tag = self->tag;
        kindA = 5;
        QueueMobyImpact(rope->lockA, &hb.a.r);
        infoAHit = moby_get_private_value_0(rope->lockA);
        if (infoAHit != 0) {
            if (((short *)infoAHit)[2] == 1)
                kindA = 1;
        }
        {
            short result = kindA;
            rope->u.s.h44 = result;
        }
    }
    if (rope->lockB != 0 && (rope->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(scratch, rope->lockB->pos, D_L17_001B9BC0);
        if (D_L17_001A8FF0 != 0) {
            projB = FastVecDot(scratch, g_hero_state.ent + 0xE0);
            FastVecScale(hb.raw, g_hero_state.ent + 0xE0, projB);
            FastVecSub(scratch, scratch, hb.raw);
        } else {
            *(int *)&scratch[2] = 0;
        }
        vec_scale_to_length(scratch, scratch, 1.0f);
        scratch[3] = 5627.925f;
        make_hit_descriptor(&hb.b.r, self, 0x210000, scratch, (&D_L17_00263470[g_item_slot_to_record.cur])->f70);
        hb.b.r.kind = 5;
        hb.b.r.flag = 3;
        hb.b.r.tag = self->tag;
        kindB = 5;
        QueueMobyImpact(rope->lockB, &hb.b.r);
        infoBHit = moby_get_private_value_0(rope->lockB);
        if (infoBHit != 0) {
            if (((short *)infoBHit)[2] == 1)
                kindB = 1;
        }
        {
            short result = kindB;
            rope->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = rope->a;
                qcopy(hb.raw, from);
            }
            sparkSize = 0.4f;
        } else {
            qcopy(hb.raw, rope->b);
            sparkSize = 0.5f;
        }
        if (FastDecTimer(&D_L17_001B34C8[k]) != 0) {
            D_L17_001B34C8[k] = D_L17_001B34D8[k];
            D_L17_001B34D0[k] = 0;
            angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
            angle1 = math_random_float_range(-1.0471977f, 0.17453295f);
            FastVecScale(scratch, direction, sparkSize);
            math_apply_axis_rotation_to_quat(scratch, scratch, D_0018A560, angle1);
            math_apply_axis_rotation_to_quat(scratch, scratch, D_0018A560 + 0x10, angle0);
            qcopy(&D_L17_0023ABB0[k].v[0], hb.raw);
            sparkSign = 1.0f;
            FastVecAdd(&D_L17_0023ABB0[k].v[1], hb.raw, scratch);
            for (linkIndex = 2; linkIndex < 5; linkIndex++) {
                FastVecSub(hb.raw + 4, &D_L17_0023ABA0[k].p[linkIndex - 1], D_L17_001B9BC0);
                sparkAmount = math_random_float_range(0.17453295f, 0.9599312f) * sparkSign;
                sparkSign = -sparkSign;
                math_apply_axis_rotation_to_quat(scratch, scratch, hb.raw + 4, sparkAmount);
                FastVecAdd(D_L17_0023ABB0[k].v + linkIndex, &D_L17_0023ABA0[k].p[linkIndex - 1], scratch);
            }
        } else {
            for (pointIndex = 1; pointIndex < 5; pointIndex++) {
                raw = tmp[pointIndex];
                FastVecSub(raw, D_L17_0023ABB0[k].v + pointIndex, &D_L17_0023ABA0[k].p[pointIndex - 1]);
                raw[0] = raw[0] + math_random_signed_float_range(0.0f, 0.1f);
                raw[1] = raw[1] + math_random_signed_float_range(0.0f, 0.1f);
                raw[2] = raw[2] + math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&D_L17_0023ABB0[k].v[0], hb.raw);
            for (pointIndex = 1; pointIndex < 5; pointIndex++)
                FastVecAdd(D_L17_0023ABB0[k].v + pointIndex, &D_L17_0023ABA0[k].p[pointIndex - 1], tmp[pointIndex]);
            {
                int x = D_L17_001B34E0[k];
                int y = D_L17_001B34C8[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                sparkAmount = IntToFloat(x);
                sparkAmount = sparkAmount / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - sparkAmount) * 32.0f);
                D_L17_001B34D0[k] = fade;
            }
        }
    }
    {
        angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
        angle1 = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(scratch, direction, D_L17_001AF0A8);
        math_apply_axis_rotation_to_quat(scratch, scratch, D_0018A560, angle1);
        math_apply_axis_rotation_to_quat(scratch, scratch, D_0018A560 + 0x10, angle0);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        flareSize = math_random_float_range(0.2f, 0.6f);
        part_spawn_ground_effect(rope, 0xF, flareSize * 0.3f, flareSize, D_L17_001AF078 | 0x7F000000, 0, spin, scratch, 1, 0.0f);
        spin = -spin;
        part_spawn_ground_effect(rope, 0xF, flareSize * 0.15f, flareSize * 0.5f, 0x307F7F7F, 0, spin, scratch, 1, 0.0f);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        flareSize = math_random_float_range(0.15f, 3.0f);
        part_spawn_ground_effect(rope->b, 0xC, flareSize * 0.1f, flareSize, D_L17_001AF078 | 0x7F000000, 0, spin, D_L17_001A8F20, 1, 0.0f);
    }
}
