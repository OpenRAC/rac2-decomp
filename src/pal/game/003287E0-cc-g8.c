#include "names.h"
/* func_PAL_003287E0, the PAL copy of func_00327038: the same C. */
#include "common.h"

/* The two small constants this probe reads through $gp, and the world axis
   beside them, which is too large for $gp and is reached with a full address. */
extern float g_vehicle_probe_lift __attribute__((sda)), g_vehicle_probe_radius __attribute__((sda));
extern float g_gravity_direction[4] __attribute__((sda));
extern int g_surface_probe_skip;
/* The collision result: the object hit at +0x18, then vectors at +0x20 (the
   hit point), +0x30 and +0x40. */
extern char g_collision_hit[32];
extern float g_coll_hit_position[12], g_coll_hit_point[4];

extern float math_fabs(float);
extern void vec_clear_128(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void divide_vector_xyz(void *, void *, float);
extern int coll_process_triangles(void *, float);
extern float IntToFloat(int), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void multiply_quaternions(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);

/* The thirty-two-step probe of an object: sweeps a quarter turn, casting a
   line from a point offset along the world axis at each step, and moves the
   object by the average of the hits. A hit on an object whose record has type
   5 changes both states. Keep the pointer locals, in this order: spilled, they
   take the stack slots after count, and only the position's address is left
   to gcse. */
void moby_probe_surface_and_move_pal(char *self)
{
    float origin[4], total[4], offset[4], rotated[4], quat[4], temp[4];
    float inverse[4], end[4], opposite[4], normal[4], hit[4];
    char *state = *(char **)(self + 0x68);
    int negative, count;
    char *rowD, *rowE;
    float *inverse_ptr, *end_ptr;
    char *result;
    int i;
    float angle, sine;

    if (math_fabs(*(float *)(state + 0x18)) < 0.0001f)
        return;
    negative = *(float *)(state + 0x18) <= 0.0f;
    vec_clear_128(total);
    vec_scale_to_length(origin, g_gravity_direction, -g_vehicle_probe_lift);
    count = 0;
    FastVecAdd(origin, origin, self + 0x10);
    if (!g_surface_probe_skip && coll_process_triangles(origin, g_vehicle_probe_radius)) {
        FastVecSub(offset, g_coll_hit_point, origin);
        FastVecAdd(self + 0x10, offset, self + 0x10);
    }
    end_ptr = end;
    rowD = self + 0xD0;
    rowE = self + 0xE0;
    inverse_ptr = inverse;
    for (i = 0; i < 32; i++) {
        angle = IntToFloat(i);
        angle /= IntToFloat(31);
        vec_scale_to_length(offset, rowD, g_vehicle_probe_radius);
        angle *= 1.57079637f;
        sine = math_fast_sin_or_cos_b(angle);
        if (!negative)
            sine = -sine;
        FastVecScale(quat, rowE, sine);
        quat[3] = math_fast_sin_or_cos_a(angle);
        inverse[0] = -quat[0];
        inverse[1] = -quat[1];
        inverse[2] = -quat[2];
        inverse[3] = quat[3];
        multiply_quaternions(temp, quat, offset);
        multiply_quaternions(rotated, temp, inverse_ptr);
        FastVecAdd(end, rotated, origin);
        if (CollLine(origin, end, 0, self, 0)) {
            count++;
            FastVecScale(opposite, g_gravity_direction, -1.0f);
            FastVecScale(normal, g_coll_hit_position + 8, 0.0009765625f);
            vec_scale_to_length(normal, normal, 1.0f);
            FastVecSub(hit, g_coll_hit_position, end_ptr);
            FastVecAdd(total, total, hit);
            result = g_collision_hit;
            if (*(char **)(result + 0x18) != 0
                && *(short *)(*(char **)(*(char **)(result + 0x18) + 0x24) + 0x46) == 5) {
                *(unsigned char *)(self + 0x20) = 9;
                *(int *)(state + 0x20) = 8;
            }
        }
    }
    if (count) {
        divide_vector_xyz(total, total, (float)count);
        FastVecAdd(self + 0x10, self + 0x10, total);
    }
}
