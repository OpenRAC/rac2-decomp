#include "include_asm.h"
#include "names.h"

struct RouteNode {
    int path;
    unsigned char neighbors[4];
    unsigned char portals[4];
    unsigned short flags;
    unsigned char unused[18];
};
extern char *D_L02_001FF1C0[];
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern int func_L02_0032EDD8(void *, struct RouteNode *, int, int *);
extern float func_L02_0032EC98(void *, void *, void *, float, float);


/* func_L02_002DCEA0 is matched in its own unit, src/levels/shared/L02_002DCEA0.c (-g). */


/* func_L02_002EF968 is defined in L02_002EF968-helpers.c. */

/* func_L02_002EFB60 is defined in L02_002EFB60-g8.c. */


/* Subtracts one 4-number vector from another and stores the result. */
ASM_FUNC("asm/levels", func_L02_002F1FB8);

/* Returns the squared flat distance between two points. */
ASM_FUNC("asm/levels", func_L02_002F21C0);

float func_L02_0031E918(float scale)
{
  float r = ((float) (0xFFF & (Rand() >> 16))) * (1.0f / 4096.0f);
  float new_var;
  new_var = r * r;
  new_var = 1.0f - new_var;
  return new_var * scale;
}


extern float func_L02_0031E918(float scale);
extern float func_002A7940(void);
extern float func_00283180(float x);
extern float func_00283198(float x);
extern void func_00282C88(void *target);

/* Makes a flat offset of random length that points in a random direction. */
void func_L02_0031E9E8(float *outVec, float radius) {
    float angle = RandomAngle();
    float length = RandomCurvedScale(radius);

    ClearVector128(outVec);
    outVec[0] = FastSinOrCosA(angle) * length;
    outVec[1] = FastSinOrCosB(angle) * length;
}

extern unsigned int D_L02_001FC060[];
extern char *D_L02_001B359C __attribute__((section(".sdata")));
extern void func_L00_003294F0(unsigned char *entity, int enabled);

/* Walk the 16-bit stream the table entry points at; a negative word ends it. */
/* Applies an on or off setting to every object in a group's list. */
void func_L02_0031F858(int groupId, int enabled) {
    short *entry;

    if (gEntityGroupLists[groupId] != 0) {
        entry = (short *)gEntityGroupLists[groupId];
        do {
            SetObjectFlagBit((unsigned char *)(gMobyPool_L02 + ((*(unsigned short *)entry & 0x7FFF) << 8)), enabled);
        } while (*entry++ >= 0);
    }
}


extern void func_002A04B8(char *object, int *out0, int *out4, int *out8);

/* Pack the three words the callee fills in behind a marker bit. */
/* Packs three numbers describing an object into one handle number. */
int func_L02_003272D8(char *object) {
    int w0;
    int w4;
    int w8;
    int packed;

    get_moby_color(object, &w0, &w4, &w8);
    packed = (w4 << 8) | 0x80000000;
    return (w8 << 16) | packed | w0;
}

extern char *D_L02_001B368C __attribute__((section(".sdata")));
extern void func_L02_00327390(char *arg0, char *arg1, int arg2);

/* Index -1 means "no record". */
/* Starts an effect for a record by its index, and does nothing if the index is empty. */
void func_L02_00327350(int index, int param) {
    char *record;

    if (index != -1) {
        record = D_L02_001B368C + (index << 7);
        StartRecordEffectByLevelKind(record + 0x30, record + 0x70, param);
    }
}

extern unsigned char D_0018C0D4;
extern void func_L00_002B9D60(int a0, int a1, int a2, int a3);
extern void func_L00_0042A500(int arg0);

/* Starts an effect whose variant depends on the current setting, then runs an optional follow-up. */
void func_L02_00327390(char *first, char *second, int extra) {
    int variant = 0;

    switch (D_0018C0D4) {
    case 1:
        variant = 0x3F;
        break;
    case 2:
        variant = 0x56;
        break;
    }
    ResetHeroPositionAndDirection((int)first, (int)second, variant, 1);
    if (extra != -1)
        ResetCameraEntry(extra);
}

/* func_L02_00329410 is matched in its own unit, L02_00329410.c. */

extern void func_00282C88(void *target);
extern void func_00283098(float *out, const float *a, const float *b);

/* Makes a vector of the given length that points the way the object faces. */
void func_L02_003294D8(char *object, float *outVec, float length) {
    float *out = outVec;
    char *obj = object;

    ClearVector128(out);
    *out = length;
    matrix_mul_vec3(out, out, (const float *)(obj + 0xC0));
}

typedef int TI128 __attribute__((mode(TI)));

extern float func_002B04E0(char *arg0, float *arg1, char *transform);
extern float func_00282C48(float t);

/* Copy the incoming 16-byte record to a local, hand both to the two calls. */
/* Checks how far the object would move from the given position and returns a clamped result. */
float func_L02_00329C48(char *object, TI128 *input, char *transform) {
    TI128 localCopy = *input;

    return FloatAbs(GetHeadingAngleOfVector(object, (float *)&localCopy, transform));
}

/* func_L02_0032B468 is defined in L02_0032B468.c. */

extern int func_L02_0032E3B0(void *a0, float *a1, int a2);

/* The shared lookup takes the record index as a third argument; the retail wrapper hands it
   only two, so the call goes through a two-parameter prototype. */
/* Counts which side of the object its group members are on, looking toward the other object. */
void func_L02_0032E390(void *object, void *other) {
    ((int (*)(void *, void *))CountGroupSideTowardTarget)(object, (char *)other + 0x10);
}

extern void func_00283410(float *matrix, float *quat);
extern void func_00283698(void *dst, void *src);
extern void func_00282CF0(float *out, const float *a, const float *b);
extern float func_00283248(float a, float b);

/* Counts the group members on each side of the line toward the target and returns the difference. */
int func_L02_0032E3B0(void *object, float *target, int index) {
    float quat[4];
    float vec[4];
    float mat[16];
    float best;
    int count;
    short *p;
    char *entity;

    if (index == -1) {
        index = (int)(unsigned char)*(char *)((char *)object + 0x21);
        if (index == -1)
            return 0;
    }
    best = 0.0f;
    count = 0;
    ClearVector128(quat);
    quat[2] = FastMatrixHelperA(target[0] - *(float *)((char *)object + 0x10),
                                   target[1] - *(float *)((char *)object + 0x14));
    euler_to_matrix(mat, quat);
    matrix_from_basis_rows(mat, mat);
    p = (short *)gEntityGroupLists[index];
    do {
        entity = gMobyPool_L02 + ((*(unsigned short *)p & 0x7FFF) << 8);
        if (entity[0x20] >= 0 && entity != (char *)object) {
            FastVecSub(vec, (float *)(entity + 0x10), (float *)((char *)object + 0x10));
            matrix_mul_vec3(vec, vec, mat);
            if (best < vec[1])
                count--;
            else
                count++;
        }
    } while (*p++ >= 0);
    return count;
}

/* func_L02_0032E508 is matched in its own unit, src/levels/shared/L02_0032E508.c (-g). */

/* Finds a route through linked areas to the target and turns the heading toward the next gap. */
int func_L02_0032E998(float *position, float *target, float *heading, struct RouteNode *nodes, int count, int *sourceNode, int *targetNode, float override, float margin) {
    unsigned char visited[256];
    int i, j, found, portal, step, routeDepth;
    int layer;
    char *path;
    float angle;
    *heading = FastMatrixHelperA(target[0] - position[0], target[1] - position[1]);
    if (override != 0.0f)
        *heading = FastAddRotations(override, *heading);
    if (!FindRouteNodeContainingPoint(position, nodes, count, sourceNode))
        return 0;
    if (!FindRouteNodeContainingPoint(target, nodes, count, targetNode))
        return 0;
    if (nodes[*targetNode].flags & 1)
        return 0;
    if (*sourceNode == *targetNode)
        return 1;
    {
        int clear;
        for (clear = 0; clear < count; clear++)
            visited[clear] = 0;
    }
    found = -1;
    portal = -1;
    visited[*targetNode] = 1;
    for (layer = 1; layer < 50; layer++) {
        for (i = 0; i < count; i++) {
            if (visited[i] == layer) {
                for (j = 0; j < 4; j++) {
                    unsigned int neighbor = nodes[i].neighbors[j];
                    if (!(neighbor & 0x80) && !visited[neighbor] && ((nodes[neighbor].flags ^ 1) & 1)) {
                        visited[neighbor] = layer + 1;
                        if (neighbor == *sourceNode) {
                            portal = nodes[i].portals[j];
                            found = i;
                        }
                    }
                }
            }
            if (found != -1)
                break;
        }
        if (found != -1)
            break;
    }
    if (found == -1)
        return 0;
    path = gRoutePolygons[nodes[found].path];
    angle = *heading;
    routeDepth = visited[found];
    if (routeDepth >= 3) {
        int edge;
        step = routeDepth - 1;
        for (edge = 0; edge < 4; edge++) {
            if (visited[nodes[found].neighbors[edge]] == step) {
                int offset = nodes[found].portals[edge] * 16;
                angle = ClampHeadingToGap(path + (offset + 0x10), path + (offset + 0x20), position, angle, margin);
                break;
            }
        }
    }
    *heading = ClampHeadingToGap(path + (portal * 16 + 0x10), path + (portal * 16 + 0x20), position, angle, margin);
    return 1;
}

extern void func_00282F20(float *out, const float *in, float s);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern void func_00282CF0(float *out, const float *a, const float *b);
extern float func_00283248(float a, float b);
extern float func_00282C48(float t);
extern float func_00283BE0(float a, float b);
extern float func_00283B98(float a, float b);

/* Clamps a heading towards the gap between two points as seen from the position: its
   difference from the middle direction is limited by func_00282C48 of half the gap's angle.
   The heading argument itself holds the clamped difference, so it lives across blocks and is
   allocated globally, after the block-local first direction has taken $f21, as in retail. */
/* Turns a heading toward a gap between two points without turning too far. */
float func_L02_0032EC98(void *gapStart, void *gapEnd, void *position, float angle, float margin) {
    float gapDir[4];
    float leftPoint[4];
    float rightPoint[4];
    float half;
    float start;
    float mid;
    float limit;

    FastVecSub(gapDir, (float *)gapEnd, (float *)gapStart);
    vec_scale_to_length(gapDir, gapDir, margin);
    FastVecAdd(leftPoint, gapStart, gapDir);
    FastVecSub(rightPoint, (float *)gapEnd, gapDir);

    start = FastMatrixHelperA(leftPoint[0] - *(float *)position, leftPoint[1] - *(float *)((char *)position + 4));
    half = fast_subtract_rotations(FastMatrixHelperA(rightPoint[0] - *(float *)position,
                                       rightPoint[1] - *(float *)((char *)position + 4)), start) * 0.5f;
    mid = FastAddRotations(half, start);
    angle = fast_subtract_rotations(angle, mid);
    limit = FloatAbs(half);
    if (limit < angle)
        angle = limit;
    limit = -limit;
    if (angle < limit)
        angle = limit;
    return FastAddRotations(angle, mid);
}

extern int func_002A8AF0(float *p, float *v, int n);
extern float func_00282E80(void *a, void *b);

/* Finds the route node whose path polygon holds the point: the cached node *index first, then
   every other node whose position (+0x10) is within its radius (+0x1C) of the point. The
   position's address is a single-use giv, which loop.c never combines with the node's own
   address, so retail walks two pointers; walking them by hand lets them fold into one. */
int func_L02_0032EDD8(void *point, struct RouteNode *nodes, int count, int *index) {
    int i;

    if (*index != -1) {
        char *entry;
        int n;
        entry = gRoutePolygons[nodes[*index].path];
        n = *(int *)entry;
        entry += 0x10;
        if (point_in_path_xy(point, (float *)entry, n) != 0)
            return 1;
    }
    for (i = 0; i < count; i++) {
        if (i != *index
            && vec_distance_xy(point, (char *)&nodes[i] + 0x10) <= *(float *)((char *)&nodes[i] + 0x1C)) {
            char *entry;
            int n;
            entry = gRoutePolygons[nodes[i].path];
            n = *(int *)entry;
            entry += 0x10;
            if (point_in_path_xy(point, (float *)entry, n) != 0) {
                *index = i;
                return 1;
            }
        }
    }
    *index = -1;
    return 0;
}

/* func_L02_0032EF10 is defined in L02_0032EF10-helpers.c. */


extern void *func_L00_0032C638(char *a0);
extern int func_002B50E0(void *a0, void *a1, float f12);

/* Set the record's fields for the call, then put the old ones back. */
int func_L02_00331440(void *a0, void *a1, int a2, float f12, float f13, float f14) {
    char *rec;
    int old38;
    float old28;
    float old20;
    int ret;

    rec = (char *)GetObjectVarsWord18((char *)a0);
    if (rec == 0)
        return 8;
    old38 = *(int *)(rec + 0x38);
    old28 = *(float *)(rec + 0x28);
    *(int *)(rec + 0x38) = a2;
    if (0.0f < f13)
        *(float *)(rec + 0x28) = f13;
    old20 = *(float *)(rec + 0x20);
    if (0.0f < f14)
        *(float *)(rec + 0x20) = f14;
    ret = StepMovementController(a0, a1, f12);
    *(int *)(rec + 0x38) = old38;
    *(float *)(rec + 0x28) = old28;
    *(float *)(rec + 0x20) = old20;
    return ret;
}

extern void func_00282CF0(float *out, const float *a, const float *b);
extern int func_L02_00332668(char *arg0, char *arg1);

/* Works out the offset from the object to a point and checks it. */
int func_L02_00332630(char *object, void *target) {
    int offset[4];

    FastVecSub((float *)offset, (const float *)target, (const float *)(object + 0x10));
    return CheckMoveTargetReachable(object, (char *)offset);
}

extern int D_L02_001A8FF0 __attribute__((sda));
extern float func_00283248(float a, float b);
extern int func_L01_00322288(char *a0, float f12);
extern void *func_L00_0032C638(char *a0);
extern float func_L00_003BFF68(char *a0, void *a1, char *a2, int a3);

/* Pick a target from the shape, or answer whether its height still fits. */
int func_L02_00332668(char *arg0, char *arg1) {
    void *rec;
    float h;

    if (D_L02_001A8FF0 == 0)
        return StartMobyEffectFromEntry(arg0, FastMatrixHelperA(*(float *)(arg1), *(float *)(arg1 + 4)));

    rec = GetObjectVarsWord18(arg0);
    if (rec == 0)
        return 0;
    h = AimMobyAtTarget(arg0, rec, arg1, 0);
    if (*(float *)((char *)rec + 0x30) < h)
        return 0;
    return 1;
}



extern void func_00282F20(float *out, const float *in, float s);
extern void *func_L00_0032C638(char *a0);
extern float func_L00_0031CDD0(char *a0, char *a1, int a2, float f12, float f13);

/* Aim the record at the shape the caller found. */
int func_L02_003329C8(char *a0, char *a1, float f12, float f13) {
    char *rec = GetObjectVarsWord18(a0);

    if (rec == 0)
        return 0;
    *(float *)(rec + 0x2C) = f13;
    FastVecSub((float *)(rec + 0xA0), (const float *)a1, (const float *)(a0 + 0x10));
    *(int *)(rec + 0xA8) = 0;
    vec_scale_to_length((float *)(rec + 0xA0), (const float *)(rec + 0xA0), f12);
    *(float *)(rec + 0xA8) = ComputeShotLaunchSpeed(a0 + 0x10, a1, 0, f12, -f13);
    return 1;
}


#include "common.h"

typedef union { TI128 q; float f[4]; } MotionVector;
extern float func_L02_00329C48(char *, TI128 *, char *);

extern float func_00282E48(void *, void *);
extern float func_00282C10(float);
extern void func_L02_003294D8(char *, float *, float);
extern void func_002AFEB8(char *, char *, char *, float, char *);
extern float func_00282DB0(void *, void *);
extern void func_002AC9F8(float *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AFF08(char *, char *, char *);
extern float func_002B0360(char *);
/* This wrapper forwards its live a1/a2/f12 into func_002B00D8. */
extern void func_L00_003253A0(u8 *, float *, float *, float);
extern float func_002AFF38(char *, char *, char *);
extern void func_002AAC80(float *, float, float, float, float);

/* Moves the object toward its target, speeding up and slowing down smoothly, and keeps it at the right height. */
void func_L02_00332A80(char *object, char *data, void *target, TI128 *input, void *unused0, void *unused1, char *transform) {
    MotionVector desired, change;
    float vertical;
    float heading, distance, speed, height, drop;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        AimMobyAtTarget(object, data, (char *)input, (int)transform);
    heading = 0.0f;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        heading = MeasureStepAngle(object, input, transform);
    if (*(float *)(data + 0x30) < heading) {
        ClearVector128(&desired.q);
    } else {
        float gap;
        distance = fast_vec_dist(object + 0x10, target);
        *(float *)(data + 0xCC) = distance;
        gap = *(float *)(data + 0x34);
        if (distance <= gap) {
            qzero(&desired);
        } else {
            gap = distance - gap;
            speed = square_root((gap + gap) * *(float *)(data + 0x24));
            if (*(float *)(data + 0x28) < speed)
                speed = *(float *)(data + 0x28);
            BuildForwardVector(object, desired.f, speed);
        }
    }
    FastVecSub(change.f, desired.f, (float *)(data + 0xA0));
    TransformAndSetHeight(object, (char *)&change, (char *)&change, 0.0f, transform);
    if (FastVecDot(&desired, data + 0xA0) > 0.0f)
        ClampVectorLength(change.f, *(float *)(data + 0x20));
    else
        ClampVectorLength(change.f, *(float *)(data + 0x24));
    FastVecAdd(data + 0xA0, data + 0xA0, &change);
    *(float *)(data + 0xB0) = GetHorizontalOffsetLength(object, data + 0xA0, transform);
    if (!(*(unsigned int *)(data + 0x38) & 4)) {
        height = GetDistanceFromGravityCenter(object + 0x10);
        if (*(float *)(data + 0x90) < height) {
            MixOnInnerData((u8 *)object, (float *)(data + 0xA0), (float *)(data + 0xA0), *(float *)(data + 0x2C));
            if (*(short *)(data + 0xC0) == 0)
                *(unsigned int *)(data + 0x94) |= 0x20;
        } else {
            vertical = GetVerticalOffset(object, data + 0xA0, transform);
            drop = vertical;
            if (*(float *)(data + 0x90) - height < drop)
                vertical = *(float *)(data + 0x90) - height;
            else if (vertical < 0.0f)
                vertical = 0.0f;
            ApproachTargetWithBraking(&vertical, *(float *)(data + 0x90) - height, 0.011111111380159855f, 0.011111111380159855f, 1.0f);
            TransformAndSetHeight(object, data + 0xA0, data + 0xA0, vertical, transform);
        }
    }
}



/* func_L02_00333218 is defined in L02_00333218.c. */

extern void func_002AFFD8(char *a0, char *a1, int a2);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern int func_002761F8(char *a0, char *a1, int mode, char *self, int flag);
extern float func_002B0360(char *p);
extern char D_L02_001C0960;

/* Scale the shape's two axes, compare them with the record and copy the
   result into the second argument. */
void func_L02_00333300(char *a0, char *a1) {
    float buf0[4];
    float buf1[4];
    float buf2[4];
    char *obj;
    char *sub;

    ComputeViewDirection(a0 + 0x10, (char *)buf0, 1);
    vec_scale_to_length(buf1, buf0, *(float *)(a1 + 8) + 0.1f);
    vec_scale_to_length(buf2, buf0, -*(float *)(a1 + 0xC) - 0.1f);
    FastVecAdd((char *)buf1, (char *)buf1, a0 + 0x10);
    FastVecAdd((char *)buf2, (char *)buf2, a0 + 0x10);
    if (CollLine((char *)buf1, (char *)buf2, 0, a0, 0)) {
        obj = &D_L02_001C0960;
        *(float *)(a1 + 0x90) = GetDistanceFromGravityCenter(obj);
        sub = obj - 0x20;
        *(int *)(a1 + 0x88) = *(int *)(sub + 0x18);
        *(int *)(a1 + 0x8C) = *(int *)(sub + 0x1C);
        vec_scale_to_length((float *)(a1 + 0x50), (float *)(obj + 0x20), 1.0f);
    } else {
        *(int *)(a1 + 0x90) = 0;
        *(int *)(a1 + 0x88) = 0;
        *(int *)(a1 + 0x8C) = 0;
        ClearVector128(a1 + 0x50);
    }
}

extern void func_L02_00333480(char *arg0, char *arg1, void *arg2);

/* Works out the offset from the object to a point and aims at it. */
void func_L02_00333438(char *object, char *target) {
    int offset[4];

    FastVecSub((float *)offset, (const float *)target, (const float *)(object + 0x10));
    UpdateObjectController(object, target, offset);
}

/* func_L02_00333480 is matched in its own unit, L02_00333480.c. */

extern void *func_002B9030(int kind);
extern int func_00283CF0(float f);
extern float func_002A7878(float a, float b);
extern float func_00283CE0(int n);
extern int func_L00_0031C998(int a0, int a1, float f12);
extern void func_00282D30(void *a0, void *a1, float f12);
extern unsigned char *D_L02_002001D8;
extern int func_001163B0(void);

/* Build one enemy record: pick its kind, place it, and aim it. */
void *func_L02_003449D8(void *origin, void *direction, void *config, void *flag, int extra) {
    float offset[4];
    unsigned char *rec;
    unsigned char *aim;
    short *range;
    short *values;
    int *pair;
    float roll;
    float fraction;

    rec = (unsigned char *)AllocParticle(0x56);
    if (rec != 0) {
        rec[9] = (unsigned char)(FloatToInt(0.04f) - 0x60);
        rec[3] = (flag != 0) ? 0x48 : 0x44;
        rec[1] = 0;
        rec[2] = *D_L02_002001D8;
        rec[8] = (unsigned char)Rand();
        roll = RandomFloatRange(0.0f, 1.0f);

        range = *(short **)((char *)config + 8);
        fraction = roll / IntToFloat(range[1] - range[0]);

        pair = *(int **)((char *)config + 0);
        *(int *)(rec + 4) = LerpIntegerFraction(pair[0], pair[1], fraction);

        values = *(short **)((char *)config + 4);
        *(float *)(rec + 0xC) = ((float)values[0] + fraction * (float)(values[1] - values[0])) * 1000.0f;

        FastVecScale(offset, direction, roll);
        FastVecAdd(rec + 0x10, origin, offset);

        *(short *)(rec + 0xA) = (short)(*(int *)((char *)config + 0x10) - (roll > 0.5f));

        aim = rec + 0x20;
        FastVecScale(aim, direction, roll * *(float *)((char *)config + 0x14));
        *(int *)(aim + 0x18) = extra;
        *(void **)(aim + 0x10) = config;
        *(short *)(aim + 0x14) = 0;
    }

    return rec;
}

/* func_L02_00348420 is defined in L02_00348420-helpers.c. */

/* func_L02_00349BD8 is matched in its own unit, L02_00349BD8.c. */

/* func_L02_00389F70 is matched in its own unit, L02_00389F70.c. */

/* func_L02_0038A008 is matched in its own unit, L02_0038A008.c. */

/* Two fields of the resident record at 0x189E20; retail shares its base between them. */
typedef struct {
    unsigned char pad00[0x88];
    float f88;
    unsigned char pad8C[0x2294 - 0x8C];
    int f2294;
} View_00189E20;

extern View_00189E20 D_00189E20;
/* sda: the bare load `lui $v1 ; lw $v1,%lo($v1)` retail has twice; a plain extern keeps the %hi
   in a saved register across the calls. */
extern int D_001A79F0 __attribute__((sda));
extern int D_L02_001CAA80;
extern char D_L02_001BA500[];
extern int D_L02_001B35B8 __attribute__((sda));
extern int func_L00_00329520(void *a0, int a1);
extern void func_002A7750(void *a0, int a1, int a2);
extern void func_L02_0038BD00(unsigned char *a0, int a1);
extern void func_L00_002E6CF0(void *a0, void *a1);
extern void func_L02_0038C998(unsigned char *a0);
extern void func_L02_0038DA00(void *arg0);

/* State machine of the controller object that owns a group id list. On level 13 it retires
   itself (+0x30 = 0xFF, bits 0 and 6 of +0x34 set, bit 12 cleared) once the resident float is
   past 89 or the resident word is 0x74. State 0 runs func_L02_0038BD00; state 1 switches the
   whole group off (+0x31 cleared, bit 0 of +0x34 set) when the record test passes, then runs
   func_L02_0038C998 and queues func_L02_0038DA00; state 2 switches the group back on. */
void func_L02_0038BA28(unsigned char *controller) {
    unsigned char *vars = *(unsigned char **)(controller + 0x68);

    if (gCurrentMapIndex == 13) {
        if (89.0f < gHeroState.f88 || gHeroState.f2294 == 0x74) {
            controller[0x30] = 0xFF;
            *(unsigned short *)(controller + 0x34) = (*(unsigned short *)(controller + 0x34) | 0x41) & 0xEFFF;
            *(int *)(controller + 0x98) = 0;
            return;
        }
        *(unsigned short *)(controller + 0x34) = (*(unsigned short *)(controller + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(controller + 0x98) = *(int *)(*(char **)(controller + 0x24) + 0x10);
    }
    if (*(unsigned short *)(controller + 0x34) & 2)
        return;
    if (D_L02_001CAA80 != 0)
        return;
    switch (controller[0x20]) {
    case 0:
        InitRailGroupMembers(controller, controller[0x21]);
        break;
    case 1:
        /* each walk has its own idPtr and entity: retail gives the two walks different registers */
        if (*(int *)(vars + 0xC) != -1 && IsPointInsideRegion(gCameraPosition_L02, *(int *)(vars + 0xC)) != 0) {
            unsigned short *idPtr;
            unsigned char *entity;

            idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
            while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
                   ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
                entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
                if (entity == 0)
                    break;
                entity[0x31] = 0;
                *(unsigned short *)(entity + 0x34) |= 1;
                idPtr++;
            }
            SetMobyState(controller, 2, -1);
        }
        UpdateMovingTargetsOnPath(controller);
        if (gCurrentMapIndex != 13 || !(89.0f < gHeroState.f88))
            AddDrawCallbackToList1(DrawAllLampGlows, controller);
        break;
    case 2:
        if (IsPointInsideRegion(gCameraPosition_L02, *(int *)(vars + 0xC)) == 0) {
            unsigned short *idPtr;
            unsigned char *entity;

            idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
            while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
                   ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
                entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
                if (entity == 0)
                    break;
                entity[0x31] = 1;
                *(unsigned short *)(entity + 0x34) &= 0xFFFE;
                idPtr++;
            }
            SetMobyState(controller, 1, -1);
        }
        break;
    }
}

/* func_L02_0038BD00 is defined in L02_0038BD00-g8.c. */

/* func_L02_0038C998 is defined in L02_002B5F50-g8.c (it reads $gp data). */

/* func_L02_0038CDE8 is defined in L02_002B5F50-lamps.c. */

extern int func_00282978(void *p);
extern int func_00283D38(int a0, int a1, float f12);

/* Toggle the lamp and hand the new state to the colour routine. */
void func_L02_0038D978(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (*(short *)(moby + 0xAA) != 0x9B0 /* moby class 2480 */)
        return;
    if (FastDecTimer(vars + 0x74) != 0) {
        *(unsigned short *)(vars + 0x74) = 0x32;
        *(unsigned int *)(vars + 0x8C) = (*(unsigned int *)(vars + 0x8C) == 0);
    }
    *(int *)(moby + 0x78) = FastTweenColor(*(int *)(moby + 0x78),
        *(unsigned int *)(vars + 0x8C) != 0 ? 0x50787878 : 0x50141414, 0.15f);
}


extern void func_L02_0038DA60(unsigned char *arg0);
extern void func_L02_0038DC68(unsigned char *arg0);
extern void func_L02_0038DE58(unsigned char *arg0);
extern void func_L02_0038E048(unsigned char *arg0);
extern void func_L02_0038E250(unsigned char *arg0);
extern void func_L02_0038E430(unsigned char *arg0);
extern void func_L02_0038E610(unsigned char *arg0);
extern void func_L02_0038E838(unsigned char *arg0);

/* Draws the glow effects of every kind of lamp in the controller's group. */
void func_L02_0038DA00(void *controller) {
    DrawGroupGlowsClass2480(controller);
    DrawGroupGlowsSceneryShip(controller);
    DrawGroupGlowsClass2837(controller);
    DrawGroupGlowsClass4939(controller);
    DrawGroupGlowsClass4733(controller);
    DrawGroupGlowsClass4747(controller);
    DrawGroupGlowsClass4752(controller);
    DrawGroupGlowsClass4928(controller);
}

extern void func_00282D60(void *buf, void *value, float scale);
extern int func_00283DB8(void *buf, float value);
extern void func_L00_002ECFE8(void *a0, void *a1, int a2, unsigned int a3,
                              float f12, float f13, float f14, int t0, int t1);
extern char *D_L02_001FBFC0[];
extern int func_L02_002F1658(void);

/* Walks the object's group id list: every entity of kind 0x9B0 in state 1 that passes the
   visibility test gets its phase at +0x1C advanced (while the flag word is clear) and one effect
   call. */
void func_L02_0038DA60(unsigned char *controller) {
    unsigned short *idPtr;
    unsigned char *entity;
    char *vars;
    float bounds[4];
    int animate;

    if (controller[0x21] == 0xFF)
        return;
    animate = IsResidentFlagClear();
    idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
    while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
           ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
        entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            break;
        vars = *(char **)(entity + 0x68);
        if (entity[0x31] != 0) {
            scale_vector(bounds, entity, 0.0009765625f);
            bounds[3] *= 1.1f;
            if (FastMathHelperA(bounds, (float)*(int *)(vars + 0x98)) != -1 &&
                (*(unsigned short *)(entity + 0x34) & 1) == 0 && *(short *)(entity + 0xAA) == 0x9B0 /* moby class 2480 */ &&
                entity[0x20] == 1) {
                if (animate != 0) {
                    *(float *)(vars + 0x1C) -= 0.1f;
                    if (*(float *)(vars + 0x1C) <= -8.0f)
                        *(float *)(vars + 0x1C) += 8.0f;
                }
                DrawOrientedQuadsAtPoints(entity, vars + 0xA0, 3, 0x60804040, *(float *)(vars + 0x78) * 0.8f,
                                  *(float *)(vars + 0x78) * 5.0f, *(float *)(vars + 0x1C), 0x204090, 0x17);
            }
        }
        idPtr++;
    }
}

/* Walk the object's group list: every entity of kind 0x9B7 in state 1 that is in view gets one
   effect call. While the resident flag word is clear, its object's phase (+0x1C) first steps
   down by 0.1, and up by 8 once it reaches -8. */
void func_L02_0038DC68(unsigned char *controller) {
    float bounds[4];
    unsigned short *idPtr;
    unsigned char *entity;
    char *vars;
    int animate;

    if (controller[0x21] == 0xFF)
        return;
    animate = IsResidentFlagClear();
    idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
    while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
           ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
        entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            break;
        vars = *(char **)(entity + 0x68);
        if (entity[0x31] != 0) {
            scale_vector(bounds, entity, 0.0009765625f);
            bounds[3] *= 1.1f;
            if (FastMathHelperA(bounds, (float)*(int *)(vars + 0x98)) != -1 &&
                !(*(unsigned short *)(entity + 0x34) & 1) && *(short *)(entity + 0xAA) == 0x9B7 /* Scenery Ship */ &&
                entity[0x20] == 1) {
                if (animate != 0) {
                    *(float *)(vars + 0x1C) -= 0.1f;
                    if (*(float *)(vars + 0x1C) <= -8.0f)
                        *(float *)(vars + 0x1C) += 8.0f;
                }
                DrawOrientedQuadsAtPoints(entity, vars + 0xA0, 2, 0x605696FF, *(float *)(vars + 0x78),
                                  *(float *)(vars + 0x78) * 7.0f, *(float *)(vars + 0x1C), 0xC0, 0x17);
            }
        }
        idPtr++;
    }
}

/* The same walk as func_L02_0038DC68, for the entities of kind 0xB15. */
void func_L02_0038DE58(unsigned char *controller) {
    float bounds[4];
    unsigned short *idPtr;
    unsigned char *entity;
    char *vars;
    int animate;

    if (controller[0x21] == 0xFF)
        return;
    animate = IsResidentFlagClear();
    idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
    while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
           ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
        entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            break;
        vars = *(char **)(entity + 0x68);
        if (entity[0x31] != 0) {
            scale_vector(bounds, entity, 0.0009765625f);
            bounds[3] *= 1.1f;
            if (FastMathHelperA(bounds, (float)*(int *)(vars + 0x98)) != -1 &&
                !(*(unsigned short *)(entity + 0x34) & 1) && *(short *)(entity + 0xAA) == 0xB15 /* moby class 2837 */ &&
                entity[0x20] == 1) {
                if (animate != 0) {
                    *(float *)(vars + 0x1C) -= 0.1f;
                    if (*(float *)(vars + 0x1C) <= -8.0f)
                        *(float *)(vars + 0x1C) += 8.0f;
                }
                DrawOrientedQuadsAtPoints(entity, vars + 0xA0, 2, 0x605696FF, *(float *)(vars + 0x78),
                                  *(float *)(vars + 0x78) * 7.0f, *(float *)(vars + 0x1C), 0xC0, 0x17);
            }
        }
        idPtr++;
    }
}

/* Like func_L02_0038DA60 for kind 0x134B: one effect call, with the scale 2.1000001f
   (0x40066667, one above 2.1f). */
void func_L02_0038E048(unsigned char *controller) {
    unsigned short *idPtr;
    unsigned char *entity;
    char *vars;
    float bounds[4];
    int animate;

    if (controller[0x21] == 0xFF)
        return;
    animate = IsResidentFlagClear();
    idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
    while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
           ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
        entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            break;
        vars = *(char **)(entity + 0x68);
        if (entity[0x31] != 0) {
            scale_vector(bounds, entity, 0.0009765625f);
            bounds[3] *= 1.1f;
            if (FastMathHelperA(bounds, (float)*(int *)(vars + 0x98)) != -1 &&
                (*(unsigned short *)(entity + 0x34) & 1) == 0 && *(short *)(entity + 0xAA) == 0x134B /* moby class 4939 */ &&
                entity[0x20] == 1) {
                if (animate != 0) {
                    *(float *)(vars + 0x1C) -= 0.1f;
                    if (*(float *)(vars + 0x1C) <= -8.0f)
                        *(float *)(vars + 0x1C) += 8.0f;
                }
                DrawOrientedQuadsAtPoints(entity, vars + 0xA0, 2, 0x60804040, *(float *)(vars + 0x78) * 0.3f,
                                  *(float *)(vars + 0x78) * 2.1000001f, *(float *)(vars + 0x1C), 0x204090, 0x17);
            }
        }
        idPtr++;
    }
}

/* Walk the object's group list: every entity of kind 0x127D in state 1 that is in view has its
   object's phase (+0x1C) stepped down by 0.1 (and up by 8 once it reaches -8), and gets one
   effect call. */
void func_L02_0038E250(unsigned char *controller) {
    float bounds[4];
    unsigned short *idPtr;
    unsigned char *entity;
    char *vars;

    if (controller[0x21] == 0xFF)
        return;
    idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
    while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
           ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
        entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            break;
        vars = *(char **)(entity + 0x68);
        if (entity[0x31] != 0) {
            scale_vector(bounds, entity, 0.0009765625f);
            bounds[3] *= 1.1f;
            if (FastMathHelperA(bounds, (float)*(int *)(vars + 0x98)) != -1 &&
                !(*(unsigned short *)(entity + 0x34) & 1) && *(short *)(entity + 0xAA) == 0x127D /* moby class 4733 */ &&
                entity[0x20] == 1) {
                *(float *)(vars + 0x1C) -= 0.1f;
                if (*(float *)(vars + 0x1C) <= -8.0f)
                    *(float *)(vars + 0x1C) += 8.0f;
                DrawOrientedQuadsAtPoints(entity, vars + 0xA0, 2, 0x605696FF, *(float *)(vars + 0x78) * 0.4f,
                                  *(float *)(vars + 0x78) * 4.0f, *(float *)(vars + 0x1C), 0xC0, 0x17);
            }
        }
        idPtr++;
    }
}

/* The same walk as func_L02_0038E250, for the entities of kind 0x128B (the effect's second
   scale is 3 times the object's +0x78 instead of 4 times). */
void func_L02_0038E430(unsigned char *controller) {
    float bounds[4];
    unsigned short *idPtr;
    unsigned char *entity;
    char *vars;

    if (controller[0x21] == 0xFF)
        return;
    idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
    while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
           ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
        entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            break;
        vars = *(char **)(entity + 0x68);
        if (entity[0x31] != 0) {
            scale_vector(bounds, entity, 0.0009765625f);
            bounds[3] *= 1.1f;
            if (FastMathHelperA(bounds, (float)*(int *)(vars + 0x98)) != -1 &&
                !(*(unsigned short *)(entity + 0x34) & 1) && *(short *)(entity + 0xAA) == 0x128B /* moby class 4747 */ &&
                entity[0x20] == 1) {
                *(float *)(vars + 0x1C) -= 0.1f;
                if (*(float *)(vars + 0x1C) <= -8.0f)
                    *(float *)(vars + 0x1C) += 8.0f;
                DrawOrientedQuadsAtPoints(entity, vars + 0xA0, 2, 0x605696FF, *(float *)(vars + 0x78) * 0.4f,
                                  *(float *)(vars + 0x78) * 3.0f, *(float *)(vars + 0x1C), 0xC0, 0x17);
            }
        }
        idPtr++;
    }
}

/* Like func_L02_0038DA60 for kind 0x1290, without the flag word: the phase always advances
   and two effect calls follow, the second one at +0xC0 with both scales times 1.5. */
void func_L02_0038E610(unsigned char *controller) {
    unsigned short *idPtr;
    unsigned char *entity;
    char *vars;
    float bounds[4];
    float scaleA;
    float scaleB;

    if (controller[0x21] == 0xFF)
        return;
    idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
    while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
           ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
        entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            break;
        vars = *(char **)(entity + 0x68);
        if (entity[0x31] != 0) {
            scale_vector(bounds, entity, 0.0009765625f);
            bounds[3] *= 1.1f;
            if (FastMathHelperA(bounds, (float)*(int *)(vars + 0x98)) != -1 &&
                (*(unsigned short *)(entity + 0x34) & 1) == 0 && *(short *)(entity + 0xAA) == 0x1290 /* moby class 4752 */ &&
                entity[0x20] == 1) {
                *(float *)(vars + 0x1C) -= 0.1f;
                if (*(float *)(vars + 0x1C) <= -8.0f)
                    *(float *)(vars + 0x1C) += 8.0f;
                scaleA = *(float *)(vars + 0x78) * 0.4f;
                scaleB = *(float *)(vars + 0x78) * 3.0f;
                DrawOrientedQuadsAtPoints(entity, vars + 0xA0, 2, 0x60804020, scaleA, scaleB, *(float *)(vars + 0x1C), 0xC00000, 0x17);
                DrawOrientedQuadsAtPoints(entity, vars + 0xC0, 1, 0x60804020, scaleA * 1.5f, scaleB * 1.5f, *(float *)(vars + 0x1C), 0xC00000,
                                  0x17);
            }
        }
        idPtr++;
    }
}

/* Like func_L02_0038DA60 for kind 0x1340: one effect call whose first scale is the +0x78
   field itself and the second is seven times it. */
void func_L02_0038E838(unsigned char *controller) {
    unsigned short *idPtr;
    unsigned char *entity;
    char *vars;
    float bounds[4];
    int animate;

    if (controller[0x21] == 0xFF)
        return;
    animate = IsResidentFlagClear();
    idPtr = (unsigned short *)gEntityGroupLists[controller[0x21]];
    while (controller[0x21] != 0xFF && controller[0x21] <= D_L02_001B35B8 && idPtr != 0 &&
           ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == (unsigned short *)gEntityGroupLists[controller[0x21]])) {
        entity = (unsigned char *)(gMobyPool_L02 + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            break;
        vars = *(char **)(entity + 0x68);
        if (entity[0x31] != 0) {
            scale_vector(bounds, entity, 0.0009765625f);
            bounds[3] *= 1.1f;
            if (FastMathHelperA(bounds, (float)*(int *)(vars + 0x98)) != -1 &&
                (*(unsigned short *)(entity + 0x34) & 1) == 0 && *(short *)(entity + 0xAA) == 0x1340 /* moby class 4928 */ &&
                entity[0x20] == 1) {
                if (animate != 0) {
                    *(float *)(vars + 0x1C) -= 0.1f;
                    if (*(float *)(vars + 0x1C) <= -8.0f)
                        *(float *)(vars + 0x1C) += 8.0f;
                }
                DrawOrientedQuadsAtPoints(entity, vars + 0xA0, 2, 0x605696FF, *(float *)(vars + 0x78), *(float *)(vars + 0x78) * 7.0f,
                                  *(float *)(vars + 0x1C), 0xC0, 0x17);
            }
        }
        idPtr++;
    }
}

/* Raise the byte field to eight when it is below. */
void func_L02_00392C70(unsigned char *moby) {
    if (moby[0x20] < 8) {
        moby[0x20] = 8;
    }
}

/* Raise the byte field to eight when it is below. */
void func_L02_003948D0(unsigned char *moby) {
    if (moby[0x20] < 8) {
        moby[0x20] = 8;
    }
}

extern void func_L02_003AA650(char *arg0);

/* Puts the object into its final state and lets go of the child object it holds. */
void func_L02_003A6F78(char *moby) {
    unsigned char *vars;
    unsigned char *child;

    moby[0x20] = 6;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    *(int *)(moby + 0x98) = 0;
    vars = *(unsigned char **)(moby + 0x68);
    vars[0xC8] = 1;
    vars[0xC9] = 0xFF;
    child = *(unsigned char **)(vars + 0xFC);
    if (child != 0) {
        if (*(short *)(child + 0xAA) == 0x326 /* moby class 806 */) {
            ReleaseSlotsAndRetireObject(child);
            *(unsigned char **)(vars + 0xFC) = 0;
        } else {
            *(unsigned char **)(vars + 0xFC) = 0;
        }
    }
}

/* Raises the object's flag word, copies a context field in and dispatches on the
   two-byte kind code. */
extern int func_00312E20(void *, int);

/* Sets up a crate object and attaches the child object for its class. */
void func_L02_003A6FE8(char *moby) {
    char *vars;
    short classId;

    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
    vars = *(char **)(moby + 0x68);
    *(unsigned int *)(moby + 0x98) = *(unsigned int *)(*(unsigned int *)(moby + 0x24) + 0x10);
    moby[0x20] = 1;
    *(unsigned int *)(vars + 0x100) = 0;
    classId = *(short *)(moby + 0xAA);
    if (classId == 0x1F5 /* Nanotech Crate */) {
        *(unsigned int *)(vars + 0xFC) = SpawnLinkedChildMoby(moby, 0);
    } else if (classId == 0x200 /* Purple Nanotech Crate */) {
        *(unsigned int *)(vars + 0xFC) = SpawnLinkedChildMoby(moby, 1);
    }
    moby[0x7F] = 0;
}

/* func_L02_003A8770 is defined in L02_002B5F50-quad.c. */

extern void func_002B9180(void *p);
extern void func_0029F338(void *e);
extern void *D_L02_001B31EC __attribute__((sda));

/* Release the eight slots behind the entity, then retire it. */
void func_L02_003AA650(char *moby) {
    void **slot;
    int i;

    slot = (void **)(*(char **)(moby + 0x68) + 0x30);
    for (i = 7; i >= 0; i--) {
        if (slot[0] != 0) {
            KillParticle(slot[0]);
            slot[0] = 0;
        }
        slot++;
    }
    if (D_L02_001B31EC == moby)
        moby[0x20] = 4;
    else
        MarkMobySpawned(moby);
}



/* func_L02_003C0890 is defined in L02_003C0890-helpers.c. */


/* func_L02_003C4068 is defined in L02_003C4068.c. */

/* func_L02_003C4280 is defined in L02_003C4280.c. */
