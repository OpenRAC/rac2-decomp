#include "include_asm.h"
#include "names.h"

/* Big level-side array: keep the absolute materialisation (`lui+addiu`), never $gp. */
extern unsigned char D_L03_00189E20[] __attribute__((nosda));

extern float D_L03_001AEF64 __attribute__((sda));

extern int D_L03_001B2548;
extern int D_L03_001A9028;
extern int D_L03_001A9024;
extern int D_L03_001C63A8[] __attribute__((nosda));

extern void func_2EF020(unsigned char *, unsigned char *, float);

extern void func_2EEFB0(unsigned char *, unsigned char *, unsigned char *);

/* Finds a point in front of an object: its facing direction scaled by a level constant, added to its position. */
void func_L03_0038A9D0(unsigned char *object, unsigned char *outPoint) {
    unsigned char *point = outPoint;
    unsigned char *self = object;

    func_2EF020(point, self + 0xC0, D_L03_001AEF64);
    func_2EEFB0(point, point, self + 0x10);
}

extern int D_L03_001AEF60 __attribute__((sda));

extern float D_L03_00237F40[] __attribute__((nosda));

extern float func_31BAE8(float, float);

/* Once per frame, refills a table of 16 random vectors. */
void func_L03_0038B238(void) {
    float *vectors;
    int i;

    if (D_L03_001AEF60 >= gFrameCounter_L03)
        return;
    vectors = D_L03_00237F40;
    for (i = 15; i >= 0; i--) {
        vectors[0] = func_31BAE8(0.0f, 1.0f);
        vectors[1] = func_31BAE8(0.0f, 1.0f);
        vectors[2] = func_31BAE8(0.0f, 1.0f);
        vectors[3] = 1.0f;
        vectors += 4;
    }
    D_L03_001AEF60 = gFrameCounter_L03;
}

/* Remembers an id in a list of up to 32 entries. The list starts over when the frame number changes. */
void func_L03_0032AD10(int value) {
    if (gFrameCounter_L03 != D_L03_001A9028) {
        D_L03_001A9028 = gFrameCounter_L03;
        D_L03_001A9024 = 0;
    }
    if (D_L03_001A9024 < 0x20) {
        D_L03_001C63A8[D_L03_001A9024] = value;
        D_L03_001A9024 = D_L03_001A9024 + 1;
    }
}

/* A 16-byte vector: the engine's VU0 helpers take and return these. */
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec4;

extern void func_00282CF0(void *, void *, void *);
extern void func_00283698(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00282E20(void *);

extern float D_L03_001B0040 __attribute__((sda));
extern float D_L03_001B0044 __attribute__((sda));
extern float D_L03_001B0048 __attribute__((sda));
extern float D_L03_001B004C __attribute__((sda));

/* Builds a vector with the engine's VU0 helpers, trims its z by the constant the state at
   0xAA names, and stores the two clamped, halved angles in the moby at 0x68. */
void func_L03_003C4A10(unsigned char *object, void *target) {
    Vec4 toTarget;
    Vec4 inverseFrame[4];
    float pitch;
    float yaw;
    void *vars;

    if (*(short *)(object + 0xAA) == 0x93C /* moby class 2364 */) {
        if (object[0x43] == 1)
            return;
    }

    vars = *(void **)(object + 0x68);

    FastVecSub(&toTarget, target, object + 0x10);
    matrix_from_basis_rows(inverseFrame, object + 0xC0);
    matrix_mul_vec3(&toTarget, &toTarget, inverseFrame);

    switch (*(short *)(object + 0xAA)) {
    case 0x964 /* Gadgebot */:
        toTarget.z -= D_L03_001B0040;
        break;
    case 0x93C /* moby class 2364 */:
        toTarget.z -= D_L03_001B0044;
        break;
    case 0x940 /* Bridgebot */:
        toTarget.z -= D_L03_001B0048;
        break;
    case 0xA59 /* moby class 2649 */:
        toTarget.z -= D_L03_001B004C;
        break;
    }

    yaw = FastMatrixHelperA(toTarget.x, toTarget.y);
    pitch = -FastMatrixHelperA(vec_length_xy(&toTarget), toTarget.z);

    if (yaw > 1.5707964f)
        yaw = 1.5707964f;
    else if (yaw < -1.5707964f)
        yaw = -1.5707964f;
    if (pitch > 0.7853982f)
        pitch = 0.7853982f;
    else if (pitch < -0.7853982f)
        pitch = -0.7853982f;

    yaw = yaw * 0.5f;
    pitch = pitch * 0.5f;

    *(float *)(vars + 0x2A8) = yaw;
    *(float *)(vars + 0x2A4) = pitch;
    *(float *)(vars + 0x324) = pitch;
    *(float *)(vars + 0x328) = yaw;
}

/* The group count is read through $gp here; the group table is absolute and the entity base is
   the bare `lui`/`lw` pair (`sda` sized over 8 bytes in a -G8 unit). */
extern int D_L03_001B2A38 __attribute__((sda));

extern unsigned char *D_L03_001B2A1C[3] __attribute__((sda));

extern unsigned short *D_L03_001FB5A0[];

extern void func_00282C88(void *);

extern void func_00283410(void *, void *);

/* Walks the entities of the object's group (the others of its team at +0x95, not in state 0xFE or
   0xFD), puts each one's offset from the object into the frame that faces the point a1, and
   counts -1 when its y is then positive, +1 otherwise; returns the sum clamped to -5..5. */
int func_L03_003C58F0(unsigned char *object, float *point) {
    float angles[4];
    float offset[4];
    float frame[16];
    int score;
    unsigned short *entryList;
    unsigned char *other;

    if (object[0x21] == 0xFF)
        return 0;
    ClearVector128(angles);
    score = 0;
    angles[2] = FastMatrixHelperA(point[0] - *(float *)(object + 0x10), point[1] - *(float *)(object + 0x14));
    euler_to_matrix(frame, angles);
    matrix_from_basis_rows(frame, frame);
    for (entryList = D_L03_001FB5A0[object[0x21]];
         object[0x21] != 0xFF && object[0x21] <= D_L03_001B2A38 && entryList != 0 &&
         ((entryList != 0 && (short)entryList[-1] >= 0) || entryList == D_L03_001FB5A0[object[0x21]]);
         entryList++) {
        other = D_L03_001B2A1C[0] + ((*entryList & 0x7FFF) << 8);
        if (other == 0)
            break;
        if (other[0x20] == 0xFE)
            continue;
        if (other[0x20] == 0xFD)
            continue;
        if (other == object)
            continue;
        if (other[0x95] != object[0x95])
            continue;
        FastVecSub(offset, other + 0x10, object + 0x10);
        matrix_mul_vec3(offset, offset, frame);
        if (offset[1] > 0.0f)
            score--;
        else
            score++;
    }
    if (score >= 6)
        score = 5;
    else if (score <= -6)
        score = -5;
    return score;
}

extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L03_003C4800(unsigned char *);

/* This function is in levels 3 and 14, which keep the data it reads at other addresses: none of
   it is named by an address. _00 is the level's jump table for the object kind (nine words), _01
   to _18 the pairs of ids and the scales of the kinds, _19 the frame counter, _20 to _22 the group
   walk's tables. */
extern void *ref_L03_003C4578_00[];
extern int ref_L03_003C4578_01 __attribute__((sda));
extern int ref_L03_003C4578_02[3] __attribute__((sda));
extern float ref_L03_003C4578_03 __attribute__((sda));
extern int ref_L03_003C4578_04 __attribute__((sda));
extern int ref_L03_003C4578_05[3] __attribute__((sda));
extern float ref_L03_003C4578_06 __attribute__((sda));
extern float ref_L03_003C4578_07 __attribute__((sda));
extern int ref_L03_003C4578_08 __attribute__((sda));
extern int ref_L03_003C4578_09[3] __attribute__((sda));
extern int ref_L03_003C4578_10 __attribute__((sda));
extern int ref_L03_003C4578_11[3] __attribute__((sda));
extern int ref_L03_003C4578_12 __attribute__((sda));
extern int ref_L03_003C4578_13[3] __attribute__((sda));
extern int ref_L03_003C4578_14 __attribute__((sda));
extern int ref_L03_003C4578_15[3] __attribute__((sda));
extern int ref_L03_003C4578_16 __attribute__((sda));
extern int ref_L03_003C4578_17[3] __attribute__((sda));
extern float ref_L03_003C4578_18 __attribute__((sda));
extern int ref_L03_003C4578_19;
extern unsigned short *ref_L03_003C4578_20[];
extern int ref_L03_003C4578_21 __attribute__((sda));
extern unsigned char *ref_L03_003C4578_22[3] __attribute__((sda));

/* The parts of the object and of its state block (at +0x68) that this function reads. */
typedef struct {
    unsigned char pad0[0x35C];
    float phase;
    unsigned char pad1[0x378 - 0x360];
    int stamp;
} L03State;

typedef struct {
    unsigned char pad0[0x21];
    unsigned char group;
    unsigned char pad1[0x31 - 0x22];
    unsigned char live;
    unsigned char pad2[0x68 - 0x32];
    L03State *state;
    unsigned char pad3[0x78 - 0x6C];
    int tint;
    unsigned char pad4[0x95 - 0x7C];
    unsigned char kind;
} L03Obj;

/* Per object kind (a0->kind: 1 and 7, 8, 2..6, else) it picks a pair of ids and a scale, turns
   the object's phase (the float at 0x35C of its state) by that scale, stores the result of
   func_00283D38 on the pair in a0->tint, and, when the state's stamp is not the frame counter,
   stamps the counter into the state of every entity of its group and registers
   func_L03_003C4800 for the object with func_L00_002E6CF0. The kind selects its arm through the
   level's jump table; `cases` only keeps the labels alive, and the labels are named after the
   kind that reaches them. */
void func_L03_003C4578(L03Obj *object) {
    static void *cases[9] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c1, &&c8};
    L03State *vars = object->state;
    int pair[2];
    float scale;
    float newPhase;
    float wave;
    unsigned short *entryList;
    L03Obj *other;
    unsigned int kind;

    if (object->live != 0) {
        kind = object->kind;
        if (kind < 9)
            goto *ref_L03_003C4578_00[kind];
        goto c0;
c1:
        pair[0] = ref_L03_003C4578_01;
        pair[1] = ref_L03_003C4578_02[0];
        scale = ref_L03_003C4578_03 * 0.00029088825f;
        goto join;
c8:
        pair[0] = ref_L03_003C4578_04;
        pair[1] = ref_L03_003C4578_05[0];
        scale = ref_L03_003C4578_06 * 0.00029088825f;
        goto join;
c2:
        pair[0] = ref_L03_003C4578_04;
        pair[1] = ref_L03_003C4578_05[0];
        scale = ref_L03_003C4578_07 * 0.00029088825f;
        goto join;
c3:
        pair[0] = ref_L03_003C4578_08;
        pair[1] = ref_L03_003C4578_09[0];
        scale = ref_L03_003C4578_07 * 0.00029088825f;
        goto join;
c4:
        pair[0] = ref_L03_003C4578_10;
        pair[1] = ref_L03_003C4578_11[0];
        scale = ref_L03_003C4578_07 * 0.00029088825f;
        goto join;
c5:
        pair[0] = ref_L03_003C4578_12;
        pair[1] = ref_L03_003C4578_13[0];
        scale = ref_L03_003C4578_07 * 0.00029088825f;
        goto join;
c6:
        pair[0] = ref_L03_003C4578_14;
        pair[1] = ref_L03_003C4578_15[0];
        scale = ref_L03_003C4578_07 * 0.00029088825f;
        goto join;
c0:
        pair[0] = ref_L03_003C4578_16;
        pair[1] = ref_L03_003C4578_17[0];
        scale = ref_L03_003C4578_18 * 0.00029088825f;
join:
        newPhase = FastAddRotations(vars->phase, scale);
        vars->phase = newPhase;
        wave = FastSinOrCosB(newPhase);
        object->tint = FastTweenColor(pair[0], pair[1], wave * 0.5f + 0.5f);
        if (vars->stamp != ref_L03_003C4578_19) {
            for (entryList = ref_L03_003C4578_20[object->group];
                 object->group != 0xFF && object->group <= ref_L03_003C4578_21 && entryList != 0 &&
                 ((entryList != 0 && (short)entryList[-1] >= 0) || entryList == ref_L03_003C4578_20[object->group]);
                 entryList++) {
                other = (L03Obj *)(ref_L03_003C4578_22[0] + ((*entryList & 0x7FFF) << 8));
                if (other == 0)
                    break;
                other->state->stamp = ref_L03_003C4578_19;
            }
            AddDrawCallbackToList1(SpawnEffectsAtAttachmentPoints, object);
        }
    }
}

extern float func_00282DF0(float *);

extern float func_00283248(float, float);

extern float func_00283B98(float, float);

/* The level's own copies of the helpers this function calls, at another address in every level
   that has them. */
extern void ref_L03_003C4240_00(unsigned char *, float);

extern void ref_L03_003C4240_01(unsigned char *, void *, int, float, float, float);

extern int ref_L03_003C4240_02(void *, void *, void *);

extern void ref_L03_003C4240_03(void *, void *);

/* Two level constants read through $gp: they sit in the resident image at another address in
   every level that has this function. */
extern float ref_L03_003C4240_04 __attribute__((sda));

extern float ref_L03_003C4240_05 __attribute__((sda));

/* Turns the object with its state: it stops when the state has no time left, otherwise it
   spreads the turn over the frame and lets the state and the object react to it. */
void func_L03_003C4240(unsigned char *object) {
    unsigned char *vars = *(unsigned char **)(object + 0x68);
    unsigned char *target;
    float turnValue;
    float turnSize;

    turnValue = FastVecLength((float *)(vars + 0x1B0));
    if (turnValue <= 0.0f)
        return;
    turnSize = FastVecLength((float *)(vars + 0x1B0));
    if (turnSize > 0.016666668f) {
        turnValue = FastMatrixHelperA(*(float *)(vars + 0x1B0), *(float *)(vars + 0x1B4));
        turnValue = FastAddRotations(turnValue, 3.14159274f);
        ref_L03_003C4240_00(object, turnValue);
    }
    ref_L03_003C4240_01(object, object + 0x10, 0x10, *(float *)(object + 0xF8),
                        ref_L03_003C4240_05 * 0.016666668f,
                        ref_L03_003C4240_04 * 0.00027777778f);
    ref_L03_003C4240_02(*(void **)(vars + 0x220), object + 0x10, vars + 0x368);
    target = *(unsigned char **)(vars + 0x194);
    if (target != 0) {
        if (*(short *)(target + 0xAA) == 0x940 /* Bridgebot */ || *(short *)(target + 0xAA) == 0x93C /* moby class 2364 */ ||
            *(short *)(target + 0xAA) == 0x964)
            ref_L03_003C4240_03(*(unsigned char **)(vars + 0x194), object + 0x10);
    }
}
