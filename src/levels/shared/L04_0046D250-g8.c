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
extern CameraEntry *g_moby_definition_table;
extern CameraRecord *g_moby_l04_pool;
extern float g_cam_offset_x __attribute__((sda));
extern float g_cam_offset_y __attribute__((sda));
extern float g_cam_offset_z __attribute__((sda));
extern float g_cam_smoothing __attribute__((sda));
extern int g_cam_side_flip __attribute__((sda));
extern int g_cam_boost_timer __attribute__((sda));
extern float g_cam_boost_zoom __attribute__((sda));
extern CameraPlayer g_hero_state;
extern CameraCollision g_probe_hit;
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern f32 ApproachValue(float *, float, float);
extern float vec_length_xy(void *);
extern int math_fast_float_d(int *);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, int, int);
extern int coll_test_point(void *, int, int, float);
/* Smooth a player-relative camera offset, then resolve movement collisions.
 * Debug line labels preserve the horizontal scaling division's padding. */
void UpdatePlayerRelativeCameraPosition(CameraObject *obj) {
    CameraVector old, offset, negative, projection, axis, center, velocity, rotated, delta;
    char *entry, *state, *hit;
    CameraVector *motion;
    float scale;
    float smoothing;
    old.q = obj->position.q;
    entry = (char *)&g_moby_l04_pool[*(int *)(g_moby_definition_table[obj->index].definition + 0x60)];
    state = *(char **)(entry + 0x68);
    smoothing = g_cam_smoothing;
    motion = (CameraVector *)(obj->motion + 0x70);
    offset.f[0] = g_cam_offset_x;
    offset.f[1] = g_cam_offset_y;
    offset.f[2] = g_cam_offset_z;
    offset.f[3] = 1.0f;
    if (*(unsigned char *)(entry + 0x20) == 3) {
        offset.f[0] += offset.f[0];
        if (g_cam_side_flip) offset.f[0] = -offset.f[0];
        g_cam_boost_timer = -1;
        offset.f[2] *= 1.5f;
    } else {
        if (g_cam_boost_timer == -1 && (*(int *)(state + 0x278) > 0 || *(int *)(state + 0x338) > 0)) g_cam_boost_timer = 90;
        if (*(int *)(state + 0x278) <= 0 && *(int *)(state + 0x338) <= 0) g_cam_boost_timer = -1;
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
    if (g_cam_boost_timer > 0) {
        if (g_cam_boost_timer >= 76) ApproachValue(&g_cam_boost_zoom, 1.0f, 0.0416666679f);
        else ApproachValue(&g_cam_boost_zoom, 0.0f, 0.0125000011f);
        if (g_cam_boost_zoom > 0) {
            scale = vec_length_xy(&velocity);
            scale = (scale + g_cam_boost_zoom) / scale;
            velocity.f[0] *= scale;
            velocity.f[1] *= scale;
        }
        math_fast_float_d(&g_cam_boost_timer);
    }
    FastVecAdd(&obj->position, &g_hero_state.position, &velocity);
    if (CollLine(&old, &obj->position, 4, 0, 0)) {
        hit = g_probe_hit.hit;
        if (!hit || (*(short *)(hit + 0xAA) != MOBY_CLASS_ENEMY_HOVERBIKE && *(short *)(hit + 0xAA) != 0xBBC /* moby class 3004 */ && *(short *)(hit + 0xAA) != 0xA1F /* moby class 2591 */)) {
            FastVecSub(&rotated, &g_probe_hit.point, &old);
            FastVecScale(&velocity, &rotated, 0.95f);
            FastVecAdd(&obj->position, &old, &velocity);
        }
    }
    if (CollLine(&g_hero_state.position, &obj->position, 2, 0, 0)) {
        hit = g_probe_hit.hit;
        if (!hit || (*(short *)(hit + 0xAA) != MOBY_CLASS_ENEMY_HOVERBIKE && *(short *)(hit + 0xAA) != 0xBBC /* moby class 3004 */ && *(short *)(hit + 0xAA) != 0xA1F /* moby class 2591 */)) {
            FastVecSub(&rotated, &g_probe_hit.point, &g_hero_state.position);
            FastVecScale(&velocity, &rotated, 0.95f);
            FastVecAdd(&obj->position, &g_hero_state.position, &velocity);
        }
    }
    if (coll_test_point(&obj->position, 4, 0, 0.15f)) {
        hit = g_probe_hit.hit;
        if (!hit || (*(short *)(hit + 0xAA) != MOBY_CLASS_ENEMY_HOVERBIKE && *(short *)(hit + 0xAA) != 0xBBC /* moby class 3004 */)) obj->position.q = g_probe_hit.position.q;
    }
}
