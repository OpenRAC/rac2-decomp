#include "common.h"

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, float, int, void *);
extern float g_collision_hit[], g_coll_hit_position[], g_coll_hit_point[];
extern float coll_get_ground_height_under_object(void *);
extern float math_fabs(float);
extern float vec_distance_xy(void *, void *);
extern void func_001290E0(void *, void *);
extern void FastVecScale(void *, void *, float);

/* Keeps a proposed movement over ground and resolves steep walls and spheres. */
/* Keeps a proposed movement over ground and resolves steep walls and spheres. */
int moby_move_over_ground(void *o, float *old, float *pos, int flags,
                  float height, float radius, float maxstep, float slope)
{
    float delta[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    union {
        int q __attribute__((mode(TI)));
        float f[4];
    } up __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float z, dot, angle, offset;
    int mask = flags & 2;
    int result = 1, i;

    pos[2] += height;
    z = coll_get_ground_height_under_object(pos);
    pos[2] -= height;
    if (maxstep < math_fabs(z - old[2])) {
        if ((((flags ^ 1) & 1) && z < old[2]) || old[2] < z) {
            qcopy(pos, old);
            result = 0;
        }
    }
    FastVecSub(delta, pos, old);
    vec_scale_to_length(scaled, delta, radius * 1.2f);
    up.q = 0;
    up.f[2] = height;
    FastVecAdd(start, old, &up);
    FastVecAdd(end, start, scaled);
    if (result && CollLine(start, end, mask | 0x24, o, 0)) {
        float *hit = g_collision_hit;
        if (((int *)hit)[7] > 0) {
            angle = mat_fast_helper_a(hit[18], vec_length_xy(hit + 16));
            if (slope <= angle) {
                hit[18] = 0;
                func_001290E0(hit + 16, hit + 16);
                dot = (-delta[0]) * hit[16] - delta[1] * hit[17];
                if (dot > 0) {
                    FastVecScale(hit + 16, hit + 16, dot);
                    result = 0;
                    FastVecAdd(delta, delta, hit + 16);
                }
            }
            FastVecAdd(pos, old, delta);
        }
    }
    if (!(flags & 2)) {
        float *point = g_coll_hit_position;
        float *hit = point - 8;
        offset = height + radius;
        i = 0;
        do {
            qcopy(probe, pos);
            probe[2] += offset;
            if (!coll_test_point(probe, radius, 0x24, o))
                break;
            angle = mat_fast_helper_a(vec_distance_xy(pos, point), hit[10] - pos[2]);
            if (((int *)hit)[6] != 0 || slope < angle) {
                qcopy(pos, g_coll_hit_point);
                pos[2] -= offset;
                result = 0;
            }
            i++;
        } while (i < 6);
    }
    pos[2] += height;
    z = coll_get_ground_height_under_object(pos);
    pos[2] -= height;
    if (maxstep < math_fabs(z - old[2])) {
        if ((((flags ^ 1) & 1) && z < old[2]) || old[2] < z) {
            qcopy(pos, old);
            result = 0;
        }
    }
    old[0] = pos[0];
    old[1] = pos[1];
    return result;
}
