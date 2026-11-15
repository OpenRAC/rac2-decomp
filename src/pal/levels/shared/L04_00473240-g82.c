#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} CameraVector;
typedef struct {
    char pad[0x30];
    CameraVector position;
    char pad40[0x30];
    char *motion;
    char pad74[0x10];
    short index;
} CameraObject;
typedef struct {
    CameraVector basis[8];
    CameraVector position;
} CameraPlayer;
typedef struct {
    char pad[0x18];
    char *hit;
    int count;
    CameraVector point, position;
} CameraCollision;
typedef struct {
    char pad[0x1C];
    char *definition;
} CameraEntry;
typedef struct {
    char bytes[0x100];
} CameraRecord;
extern CameraEntry *D_L04_001B1E84;
extern CameraRecord *g_moby_l04_pool;
extern float D_L04_001B1C8C __attribute__((sda));
extern float D_L04_001B1C90 __attribute__((sda));
extern float D_L04_001B1C94 __attribute__((sda));
extern float D_L04_001B1CAC __attribute__((sda));
extern int D_L04_001B1CC4 __attribute__((sda));
extern int D_L04_001B1CCC __attribute__((sda));
extern float D_L04_001B1CD0 __attribute__((sda));
extern CameraPlayer g_hero_state;
extern CameraCollision D_L04_001BFAC0;
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void ApproachValue(float *, float, float);
extern float vec_length_xy(void *);
extern void math_fast_float_d(int *);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, int, int);
extern int coll_test_point(void *, int, int, float);

/* Smooth a player-relative camera offset, then resolve movement collisions.
 * Debug line labels preserve the horizontal scaling division's padding. */
void func_PAL_L04_004734D8(CameraObject *obj) {
    CameraVector old, offset, negative, projection, axis, center, velocity, rotated, delta;
    char *entry, *state, *hit;
    CameraVector *motion;
    float scale;
    float smoothing;
    old.q = obj->position.q;
    entry = (char *)&g_moby_l04_pool[*(int *)(D_L04_001B1E84[obj->index].definition + 0x60)];
    state = *(char **)(entry + 0x68);
    smoothing = D_L04_001B1CAC;
    motion = (CameraVector *)(obj->motion + 0x70);
    offset.f[0] = D_L04_001B1C8C;
    offset.f[1] = D_L04_001B1C90;
    offset.f[2] = D_L04_001B1C94;
    offset.f[3] = 1.0f;
    if (*(unsigned char *)(entry + 0x20) == 3) {
        offset.f[0] += offset.f[0];
        if (D_L04_001B1CC4) offset.f[0] = -offset.f[0];
        D_L04_001B1CCC = -1;
        offset.f[2] *= 1.5f;
    } else {
        if (D_L04_001B1CCC == -1 && (*(int *)(state + 0x278) > 0 || *(int *)(state + 0x338) > 0)) D_L04_001B1CCC = 75;
        if (*(int *)(state + 0x278) <= 0 && *(int *)(state + 0x338) <= 0) D_L04_001B1CCC = -1;
    }
    FastVecScale(&negative, &g_hero_state, -1.0f);
    qcopy(&center, &g_hero_state.position);
    velocity.q = 0;
    velocity.f[2] = 1.0f;
    velocity.f[3] = 1.0f;
    qcopy(&axis, &velocity);
    FastVecCross(&projection, &negative, &velocity);
    vec_scale_to_length(&projection, &projection, 1.0f);
    FastVecCross(&negative, &axis, &projection);
    transform_vector(&rotated, &offset, &negative);
    FastVecSub(&delta, &rotated, &g_hero_state.position);
    lerp_vector(motion, motion, &delta, smoothing);
    velocity.q = motion->q;
    if (D_L04_001B1CCC > 0) {
        if (D_L04_001B1CCC >= 63) ApproachValue(&D_L04_001B1CD0, 1.0f, 0.050000004f);
        else ApproachValue(&D_L04_001B1CD0, 0.0f, 0.015000001f);
        if (D_L04_001B1CD0 > 0) {
            scale = vec_length_xy(&velocity);
            scale = (scale + D_L04_001B1CD0) / scale;
            velocity.f[0] *= scale;
            velocity.f[1] *= scale;
        }
        math_fast_float_d(&D_L04_001B1CCC);
    }
    FastVecAdd(&obj->position, &g_hero_state.position, &velocity);
    if (CollLine(&old, &obj->position, 4, 0, 0)) {
        hit = D_L04_001BFAC0.hit;
        if (!hit || (*(short *)(hit + 0xAA) != 0xB2D && *(short *)(hit + 0xAA) != 0xBBC && *(short *)(hit + 0xAA) != 0xA1F)) {
            FastVecSub(&rotated, &D_L04_001BFAC0.point, &old);
            FastVecScale(&velocity, &rotated, 0.95f);
            FastVecAdd(&obj->position, &old, &velocity);
        }
    }
    if (CollLine(&g_hero_state.position, &obj->position, 2, 0, 0)) {
        hit = D_L04_001BFAC0.hit;
        if (!hit || (*(short *)(hit + 0xAA) != 0xB2D && *(short *)(hit + 0xAA) != 0xBBC && *(short *)(hit + 0xAA) != 0xA1F)) {
            FastVecSub(&rotated, &D_L04_001BFAC0.point, &g_hero_state.position);
            FastVecScale(&velocity, &rotated, 0.95f);
            FastVecAdd(&obj->position, &g_hero_state.position, &velocity);
        }
    }
    if (coll_test_point(&obj->position, 4, 0, 0.15f)) {
        hit = D_L04_001BFAC0.hit;
        if (!hit || (*(short *)(hit + 0xAA) != 0xB2D && *(short *)(hit + 0xAA) != 0xBBC)) obj->position.q = D_L04_001BFAC0.position.q;
    }
}
