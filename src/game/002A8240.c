#include "common.h"

extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(float, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void FastVecSub(void *, void *, void *);
extern int coll_test_point(void *, float, int, void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern float g_coll_hit_position[];
extern float g_coll_hit_point[];
extern char g_collision_hit[];

/* Moves an object by a step, pushing it out of walls and down onto the floor, and reports what it touched. */
int moby_move_and_collide(char *object, float *movement, int flags,
                  float height, float radius, float offset)
{
    float previous[4] __attribute__((aligned(16)));
    float from[4] __attribute__((aligned(16)));
    float to[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float *position = (float *)(object + 0x10);
    int mask = (flags << 1) & 0x20;
    int result = 0;
    int retries;
    float base;
    char *hit;

    qcopy(previous, position);
    FastVecAdd(position, position, movement);
    if (FastVecLength(movement) > radius) {
        qcopy(from, previous);
        from[2] += height;
        vec_scale_to_length(radius, scaled, movement);
        FastVecAdd(to, scaled, position);
        to[2] += height;
        if (CollLine(from, to, mask, object, 0)) {
            FastVecSub(position, g_coll_hit_position, scaled);
            result = 1;
            *(float *)(object + 0x18) -= height;
        }
    }
    retries = 0;
    position = (float *)(object + 0x10);

    for (;;) {
        qcopy(from, position);
        from[2] += height;
        if (!coll_test_point(from, radius, mask | 4, object))
            break;
        qcopy(position, g_coll_hit_point);
        ++retries;
        result |= 1;
        *(float *)(object + 0x18) -= height;
        if (retries >= 6)
            break;
    }
    base = *(float *)(object + 0x18) - offset;
    qcopy(from, position);
    qcopy(to, position);
    from[2] += height;
    to[2] = base - 0.05f;
    if (CollLine(from, to, mask | 2, object, 0)) {
        hit = g_collision_hit;
        if (*(int *)(hit + 0x1C) > 0) {
            float normal;
            result |= 2;
            normal = vec_length_xy(hit + 0x40);
            if (mat_fast_helper_a(*(float *)(hit + 0x48), normal) > 0.5f)
                result |= 4;
            if (base < *(float *)(hit + 0x28))
                *(float *)(object + 0x18) += (*(float *)(hit + 0x28) - base) * 0.3f;
        }
    }
    FastVecSub(movement, position, previous);
    return result;
}
