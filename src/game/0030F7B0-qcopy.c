#include "include_asm.h"
#include "names.h"

/* func_00313678 - 84 bytes, 28 places.  qcopy needs the copy source kept in a
 * char * local while the call passes the same pointer; folding the load made
 * the source address a constant offset.  Matches in all three releases. */

typedef int TI128 __attribute__((mode(TI)));

extern void gravity_offset_position(void *p, float *a1, float *a2, float f);
extern int CollLine(void *a, void *b, int mode, void *self, int flag);
extern char D_00189F00[];

/* Checks that nothing blocks the line from a nanotech ball to its target. Returns 1 when the way is clear. */
int is_nanotech_ball_target_line_clear(char *x)
{
    char local[16];
    char *p = x + 0x10;

    *(TI128 *)local = *(TI128 *)p;
    gravity_offset_position(p, (float *)local, (float *)local, -0.5f);
    return CollLine(local, D_00189F00, 0x12, 0, 0) == 0;
}

/* func_00314E28: the distance test passes target and origin straight through from $a0/$a1. */
extern float fast_vec_dist(float *, float *);
extern void FastVecSub(float *, float *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern float vec_distance_xy(float *, float *);
extern float mat_fast_helper_a(float, float);
extern float square_root(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);

/* Works out the launch speed needed to throw an item from the origin to the target, never aiming farther than the limit. */
void moby_compute_throw_velocity(float *target, float *origin, float *out, float g, float min_range, float limit) {
    float d[4] __attribute__((aligned(16)));
    float half = g * limit * 0.5f;
    float range;
    float rise;
    float yaw;
    float v;
    float t;

    if (limit < fast_vec_dist(target, origin)) {
        FastVecSub(d, origin, target);
        vec_scale_to_length(d, d, limit - 0.01f);
        FastVecAdd(d, d, target);
    } else {
        *(TI128 *)d = *(TI128 *)origin;
    }
    range = vec_distance_xy(target, d);
    rise = d[2] - target[2];
    yaw = mat_fast_helper_a(d[0] - target[0], d[1] - target[1]);
    if (range < min_range) {
        range = min_range;
    }
    if (range <= rise) {
        rise = range - 0.01f;
    }
    t = g * range * range / (2.0f * (range - rise));
    if (half < t) {
        t = half;
    }
    v = square_root(t);
    out[0] = math_fast_sin_or_cos_a(yaw) * v;
    out[1] = math_fast_sin_or_cos_b(yaw) * v;
    out[2] = v;
}
