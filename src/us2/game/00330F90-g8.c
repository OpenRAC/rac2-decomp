#include "include_asm.h"
#include "common.h"

/* func_US2_00330F90, the v2.00 copy of func_00330150: the same C without the
   24-byte copy of D_001B09B0. It reads two small-data constants $gp-relative,
   so it needs -G8. */

typedef struct {
    char pad[0x18];
    char *object;
    int unknown;
    float position[4];
    float point[4];
    float normal[4];
} SweepHit;

extern float g_ridden_vehicle_probe_lift __attribute__((sda));
extern float g_ridden_vehicle_probe_radius __attribute__((sda));
extern float g_vehicle_gravity_direction[4] __attribute__((sda));
extern int g_vehicle_probe_skip;
extern float g_coll_hit_point[4];
extern SweepHit g_collision_hit;
extern float math_fabs(float);
extern void vec_clear_128(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void divide_vector_xyz(void *, void *, float);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float);
extern void multiply_quaternions(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_process_triangles(void *, float);

/* Casts 32 rays over a quarter turn about the row at +0xE0, in the direction
   of the sign of the state's +0x58. Each hit adds its correction to a sum,
   and the mean of the sum moves the position at +0x10. A hit on a surface of
   type 5 sets object state 9 and the state word at +0x60 to 10.

   The two copies of the object give the order of the spill slots at
   0xBC..0xCC. gcse numbers its reaching registers in hash-bucket order, and
   the bucket of an address includes the number of its base register, so with
   87 buckets retail's order needs a base of pseudo 118 to 134, set before the
   block that holds the first object + 0x10. GCSE copy propagation goes one
   copy deep per pass, so PRE sees self's offsets based on moby. moby has to
   stay in use beyond the block, and the copies must not be adjacent, or cse
   collapses them. moby's number follows the declarations before it, so the
   function's named scalars are what bring it to that pseudo; type and surface
   add no insn at gcse, which keeps the 87 buckets. */
void func_US2_00330F90(char *object)
{
    float base[4], sum[4], axis[4], first[4], rotated[4], temporary[4], inverse[4];
    float endpoint[4], opposite[4], normal[4], correction[4];
    char *state = *(char **)(object + 0x68);
    int negative, hits, i, hit, last, type, surface;
    float angle, sine, cosine;
    float speed, threshold, radius, zero, lift, drop;
    float step, span, quarter, x, y, z, nx, ny, nz;
    float down, unit, one, total;
    char *other, *info;

    speed = math_fabs(*(float *)(state + 0x58));
    threshold = 0.0001f;
    if (speed < threshold) return;
    {
        char *self;
        char *moby = object;

        negative = 1;
        self = moby;
        radius = *(float *)(state + 0x58);
        zero = 0.0f;
        if (!(radius <= zero)) negative = 0;
        vec_clear_128(sum);
        hits = 0;
        lift = g_ridden_vehicle_probe_lift;
        drop = -lift;
        vec_scale_to_length(base, g_vehicle_gravity_direction, drop);
        FastVecAdd(base, base, self + 0x10);
        if (!g_vehicle_probe_skip && coll_process_triangles(base, g_ridden_vehicle_probe_radius)) {
            FastVecSub(axis, g_coll_hit_point, base);
            FastVecAdd(self + 0x10, axis, self + 0x10);
        }
        for (i = 0; i < 32; i++) {
            step = IntToFloat(i);
            last = 31;
            span = IntToFloat(last);
            angle = step / span;
            vec_scale_to_length(axis, self + 0xD0, g_ridden_vehicle_probe_radius);
            quarter = 1.57079637f;
            angle *= quarter;
            sine = math_fast_sin_or_cos_b(angle);
            if (!negative) sine = -sine;
            FastVecScale(rotated, self + 0xE0, sine);
            cosine = math_fast_sin_or_cos_a(angle);
            rotated[3] = cosine;
            x = rotated[0];
            nx = -x;
            inverse[0] = nx;
            y = rotated[1];
            ny = -y;
            inverse[1] = ny;
            z = rotated[2];
            nz = -z;
            inverse[2] = nz;
            inverse[3] = cosine;
            multiply_quaternions(temporary, rotated, axis);
            multiply_quaternions(first, temporary, inverse);
            FastVecAdd(endpoint, first, base);
            hit = CollLine(base, endpoint, 0, moby, 0);
            if (hit) {
                hits++;
                down = -1.0f;
                FastVecScale(opposite, g_vehicle_gravity_direction, down);
                unit = 0.0009765625f;
                FastVecScale(normal, g_collision_hit.normal, unit);
                one = 1.0f;
                vec_scale_to_length(normal, normal, one);
                FastVecSub(correction, g_collision_hit.position, endpoint);
                FastVecAdd(sum, sum, correction);
                other = g_collision_hit.object;
                if (other) {
                    info = *(char **)(other + 0x24);
                    type = *(short *)(info + 0x46);
                    surface = 5;
                    if (type == surface) {
                        self[0x20] = 9;
                        *(int *)(state + 0x60) = 10;
                    }
                }
            }
        }
        if (hits) {
            total = (float)hits;
            divide_vector_xyz(sum, sum, total);
            FastVecAdd(self + 0x10, self + 0x10, sum);
        }
    }
}
