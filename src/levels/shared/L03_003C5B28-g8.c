#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

typedef struct {
    u32 field00;
    u32 field04;
    f32 field08;
    f32 field0C;
} NativeCallbackTimer;

extern NativeCallbackTimer D_L04_001B98E0;
extern f32 D_L04_001B1C88 __attribute__((sda));

/* The group count is read through $gp here; the group table and the resident word are
   absolute, and the entity base (D_L03_001B2A1C in the -G0 sibling) is the bare `lui`/`lw` pair,
   a second name sized over 8 bytes with `sda` in this -G8 unit. */
extern int D_0018A15C __attribute__((nosda));

extern int D_L03_001B2A38 __attribute__((sda));

extern u8 *D_L03_001B2A1C_1[3] __attribute__((sda));

extern unsigned short *D_L03_001FB5A0[];

extern void FastVecSub(float *, u8 *, u8 *);

extern void vec_transform_by_object_or_given(u8 *, float *, float *, int);

extern float math_fabs(float);

extern void moby_set_state(u8 *, int, int);

/* Puts into state 5 every entity of the object's group (state byte other than 1, kind byte
   below 2) that lies in front of it, within 1.0 ahead, 0.7 sideways and 0.5 up or down in the
   object's own frame, storing a1 at +0x374 of its state and clearing its halfword at +0x96. */
void entity_stun_in_front(u8 *obj, float value) {
    float offset[4];
    unsigned short *idPtr;
    u8 *entity;
    u8 *entityVars;

    if (obj[0x21] == 0xFF)
        return;
    for (idPtr = D_L03_001FB5A0[obj[0x21]];
         obj[0x21] != 0xFF && obj[0x21] <= D_L03_001B2A38 && idPtr != 0 &&
         ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == D_L03_001FB5A0[obj[0x21]]);
         idPtr++) {
        entity = D_L03_001B2A1C_1[0] + ((*idPtr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x20] == 1)
            continue;
        if (entity[0x95] < 2) {
            FastVecSub(offset, entity + 0x10, obj + 0x10);
            vec_transform_by_object_or_given(obj, offset, offset, 0);
            if (offset[0] > 0.0f && offset[0] < 1.0f && math_fabs(offset[1]) < 0.7f &&
                math_fabs(offset[2]) < 0.5f) {
                entityVars = *(u8 **)(entity + 0x68);
                moby_set_state(entity, 5, 1);
                *(float *)(entityVars + 0x374) = value;
                *(short *)(entity + 0x96) = 0;
            }
        }
    }
}

/* Answers 1 when the resident word at 0x18A15C equals the object's state word at +0x358, or
   when the state of an entity of the object's group holds it at +0x198; 0 otherwise. */
int group_is_state_word_matching(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    unsigned short *idPtr;
    u8 *entity;

    if (D_0018A15C == *(int *)(vars + 0x358))
        return 1;
    if (obj[0x21] == 0xFF)
        return 0;
    for (idPtr = D_L03_001FB5A0[obj[0x21]];
         obj[0x21] != 0xFF && obj[0x21] <= D_L03_001B2A38 && idPtr != 0 &&
         ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == D_L03_001FB5A0[obj[0x21]]);
         idPtr++) {
        entity = D_L03_001B2A1C_1[0] + ((*idPtr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (*(int *)(*(u8 **)(entity + 0x68) + 0x198) == *(int *)(vars + 0x358))
            return 1;
    }
    return 0;
}

extern float vec_distance_xy(u8 *, u8 *);

/* Answers 0 when another entity of the object's group, whose state holds the same word at
   +0x358, is nearer to a1 than the object is; 1 otherwise. */
int group_is_nearest_to_target(u8 *obj, u8 *target) {
    u8 *vars = *(u8 **)(obj + 0x68);
    float ownDist;
    unsigned short *idPtr;
    u8 *entity;

    ownDist = vec_distance_xy(obj + 0x10, target);
    for (idPtr = D_L03_001FB5A0[obj[0x21]];
         obj[0x21] != 0xFF && obj[0x21] <= D_L03_001B2A38 && idPtr != 0 &&
         ((idPtr != 0 && (short)idPtr[-1] >= 0) || idPtr == D_L03_001FB5A0[obj[0x21]]);
         idPtr++) {
        entity = D_L03_001B2A1C_1[0] + ((*idPtr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity == obj)
            continue;
        if (*(int *)(*(u8 **)(entity + 0x68) + 0x358) == *(int *)(vars + 0x358) &&
            vec_distance_xy(entity + 0x10, target) < ownDist)
            return 0;
    }
    return 1;
}

typedef struct { u8 b[0x10]; } Local16;

extern f32 D_L03_001B0344 __attribute__((sda));

extern f32 D_L03_001B0CA0 __attribute__((sda));

extern u8 D_L03_001B9BB0[] __attribute__((nosda));

extern void vec_scale_to_length(u8 *, u8 *, f32);

extern void FastVecScale(u8 *, u8 *, f32);

extern void FastVecAdd(u8 *, u8 *, u8 *);

extern void func_002A0F48(u8 *);

/* Computes two points on opposite sides of the object, one along its direction and one against it. */
void moby_compute_opposite_points(u8 *obj, u8 *outA, u8 *outB) {
    Local16 dirA;
    Local16 dirB;

    vec_scale_to_length(dirA.b, obj + 0xC0, D_L03_001B0344);
    FastVecScale(dirB.b, dirA.b, -1.0f);
    FastVecAdd(outA, dirA.b, obj + 0x10);
    FastVecAdd(outB, dirB.b, obj + 0x10);
}

/* Moves the attached child object to a fixed spot, runs its callback if it has one, then refreshes it. */
void moby_update_attached_child(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    u8 *child = *(u8 **)(vars + 0x58);

    vec_scale_to_length(child + 0x10, D_L03_001B9BB0, D_L03_001B0CA0);
    FastVecAdd(child + 0x10, child + 0x10, D_L03_001B9BB0 - 0x230);
    if (*(u32 *)(child + 0x64) != 0)
        (*(void (**)(u8 *))(*(u8 **)(vars + 0x58) + 0x64))(child);
    func_002A0F48(*(u8 **)(vars + 0x58));
}

/* updates the registered countdown state and clears its original completion flags */
void timer_tick_countdown(void) {
    NativeCallbackTimer *timer = &D_L04_001B98E0;
    u32 mode = timer->field04;
    timer->field08 = 10000.0f;
    if (mode == 0) {
        timer->field0C -= D_L04_001B1C88;
        if (timer->field0C < 0.0f) timer->field0C = 0.0f;
    } else {
        timer->field04 = 0;
    }
    timer->field00 = 0;
}

/* The $gp float each of the two mutual twins reads (3.0f and 1.0f). */
extern f32 D_L03_001B02F0 __attribute__((sda));

extern f32 D_L03_001B1A90 __attribute__((sda));

/* Places a point at the object's position plus its direction scaled by a fixed amount. */
void moby_compute_point_ahead_scaled(u8 *obj, u8 *out) {
    FastVecScale(out, obj + 0xC0, D_L03_001B02F0);
    FastVecAdd(out, out, obj + 0x10);
}

/* The same body with func_00282F20 and 1.0f. */
void moby_compute_point_ahead_unit(u8 *obj, u8 *out) {
    vec_scale_to_length(out, obj + 0xC0, D_L03_001B1A90);
    FastVecAdd(out, out, obj + 0x10);
}

extern f32 D_L03_001B1FC4 __attribute__((sda));

extern f32 FastAddRotations(f32, f32);

extern void moby_mark_spawned(u8 *);

/* Ages one entity: scales the rate the owner record holds by the shared $gp factor, drops
   the entity's own 1/240 timer, blends two matrix columns and then the three angles, and
   releases the entity when its 0xBC countdown runs out. */
void entity_age_and_blend(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    u8 *owner = *(u8 **)(obj + 0x24);

    *(f32 *)(obj + 0x2C) = *(f32 *)(owner + 0x24) * D_L03_001B1FC4;
    *(f32 *)(vars + 0x8) = *(f32 *)(vars + 0x8) - 0.0041666669f;
    FastVecAdd(obj + 0x10, obj + 0x10, vars);
    FastVecAdd(obj + 0xF0, obj + 0xF0, vars + 0x10);
    *(f32 *)(obj + 0xF0) = FastAddRotations(*(f32 *)(obj + 0xF0), *(f32 *)(vars + 0x10));
    *(f32 *)(obj + 0xF4) = FastAddRotations(*(f32 *)(obj + 0xF4), *(f32 *)(vars + 0x14));
    *(f32 *)(obj + 0xF8) = FastAddRotations(*(f32 *)(obj + 0xF8), *(f32 *)(vars + 0x18));
    obj[0xBC] = obj[0xBC] - 1;
    if (obj[0xBC] == 0)
        moby_mark_spawned(obj);
}

/* One sixteen-byte entry per path step: the step's type and the two nodes chosen for it. */
typedef struct {
    s32 type;
    s32 first;
    s32 second;
    s32 flag;
} PathEntry;

typedef struct {
    u8 order[16];
    u8 visited[16];
    u8 path[16];
} PathState;

extern PathEntry D_L03_0029BCD0[];

extern s32 D_L03_001B0B50 __attribute__((sda));

extern s32 SelectUnusedTableEntry(u8 *, u32, s32, u32 *, s32);

/* Clears the entries of the first D_L03_001B0B50 path steps and refills them by type, with
   func_L03_003E2D98 (a neighbour of a node that is not on the path): type 1 picks one
   neighbour of the step's path node, type 2 also a neighbour of that pick, type 3 a second
   neighbour of the path node other than the first. */
/* Fills in the path choices for each step: picks one or two neighbouring nodes depending on the step type. */
void SelectPathStepNodes(u8 *obj) {
    PathState *state = *(PathState **)(obj + 0x68);
    s32 i;
    u32 node, prev, prev2;

    for (i = 0; i < D_L03_001B0B50; i++) {
        D_L03_0029BCD0[i].first = -1;
        D_L03_0029BCD0[i].second = -1;
        D_L03_0029BCD0[i].flag = -1;
        node = state->path[i];
        switch (D_L03_0029BCD0[i].type) {
        case 1:
            D_L03_0029BCD0[i].first = SelectUnusedTableEntry(obj, node, i, 0, 0);
            break;
        case 2:
            D_L03_0029BCD0[i].first = SelectUnusedTableEntry(obj, node, i, 0, 0);
            prev = D_L03_0029BCD0[i].first;
            D_L03_0029BCD0[i].second = SelectUnusedTableEntry(obj, prev, i, &prev, 1);
            break;
        case 3:
            D_L03_0029BCD0[i].first = SelectUnusedTableEntry(obj, node, i, 0, 0);
            prev2 = D_L03_0029BCD0[i].first;
            D_L03_0029BCD0[i].second = SelectUnusedTableEntry(obj, node, i, &prev2, 1);
            break;
        }
    }
}
