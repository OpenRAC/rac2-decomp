#include "include_asm.h"

#include "common.h"
typedef int Vector __attribute__((mode(TI)));
extern int g_blade_trail_count __attribute__((sda));
extern float D_L02_001B0338 __attribute__((sda));
extern float D_L02_001B033C __attribute__((sda));
extern float D_L02_001B0340 __attribute__((sda));
extern float D_L02_001B0350 __attribute__((sda));
extern float D_L02_001B0354;
extern float D_L02_001B0358;
extern float D_L02_001B0360 __attribute__((sda));
extern float D_L02_001B0364;
extern float D_L02_001B0368;
extern Vector g_blade_trail_end_points[];
extern Vector g_blade_trail_base_points[];
extern void moby_transform_joint_to_world(char *, int, char *);
extern void moby_transform_joint_point(char *, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern float math_fabs(float);

/* Only table-row stores use the non-clobbering copy: the surrounding scalar
 * accesses and live stack vectors occupy distinct storage. */
void func_PAL_L02_003DA778(char *self, int joint) {
    float origin[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float previous_end[4] __attribute__((aligned(16)));
    float previous_origin[4] __attribute__((aligned(16)));
    float error;
    int sample;
    if (g_blade_trail_count >= 50)
        return;
    moby_transform_joint_to_world(self, joint, (char *)origin);
    moby_transform_joint_point(self, joint, (char *)matrix);
    qcopy(direction, matrix);
    error = 100.0f;
    vec_scale_to_length(direction, direction, 5.3f);
    FastVecAdd(endpoint, origin, direction);
    sample = g_blade_trail_count;
    if (sample > 0) {
        qcopy(previous_end, &g_blade_trail_end_points[sample]);
        qcopy(previous_origin, &g_blade_trail_base_points[sample]);
        error = fast_vec_dist(previous_end, endpoint);
        error += fast_vec_dist(previous_origin, origin);
        if (error > 0.01f) {
            do {
                int next;
                error = math_fabs(math_step_value_toward_target(previous_end, &D_L02_001B0350, endpoint[0],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                error += math_fabs(math_step_value_toward_target(previous_end + 1, &D_L02_001B0354, endpoint[1],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                error += math_fabs(math_step_value_toward_target(previous_end + 2, &D_L02_001B0358, endpoint[2],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                qcopy_nc(g_blade_trail_end_points + 1 + g_blade_trail_count, previous_end);
                error += math_fabs(math_step_value_toward_target(previous_origin, &D_L02_001B0360, origin[0],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                error += math_fabs(math_step_value_toward_target(previous_origin + 1, &D_L02_001B0364, origin[1],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                error += math_fabs(math_step_value_toward_target(previous_origin + 2, &D_L02_001B0368, origin[2],
                    D_L02_001B0338 * 0.00040000002f, D_L02_001B033C * 0.00040000002f, D_L02_001B0340 * 0.020000001f));
                qcopy_nc(g_blade_trail_base_points + 1 + g_blade_trail_count, previous_origin);
                next = g_blade_trail_count;
                if (next >= 50)
                    return;
                g_blade_trail_count = next + 1;
            } while (error > 0.01f);
        }
    }
    if (error > 0.01f) {
        qcopy_nc(g_blade_trail_end_points + 1 + g_blade_trail_count, endpoint);
        qcopy_nc(g_blade_trail_base_points + 1 + g_blade_trail_count, origin);
        g_blade_trail_count++;
    }
}
