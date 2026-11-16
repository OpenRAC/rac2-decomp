#include "common.h"

typedef int Vector __attribute__((mode(TI)));
extern int g_blade_trail_count __attribute__((sda));
extern float g_trail_sample_unit_x __attribute__((sda));
extern float g_trail_sample_unit_y __attribute__((sda));
extern float g_trail_sample_unit_z __attribute__((sda));
extern float g_trail_end_state_x __attribute__((sda));
extern float g_trail_end_state_y;
extern float g_trail_end_state_z;
extern float g_trail_origin_state_x __attribute__((sda));
extern float g_trail_origin_state_y;
extern float g_trail_origin_state_z;
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
/* Records the blade's end and base positions each frame into a trail history of up to 50 samples, smoothing towards the new positions. */
void chainblade_record_trail_sample(char *self, int joint) {
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
                error = math_fabs(math_step_value_toward_target(previous_end, &g_trail_end_state_x, endpoint[0],
                    g_trail_sample_unit_x * 0.00027777778f, g_trail_sample_unit_y * 0.00027777778f, g_trail_sample_unit_z * 0.016666668f));
                error += math_fabs(math_step_value_toward_target(previous_end + 1, &g_trail_end_state_y, endpoint[1],
                    g_trail_sample_unit_x * 0.00027777778f, g_trail_sample_unit_y * 0.00027777778f, g_trail_sample_unit_z * 0.016666668f));
                error += math_fabs(math_step_value_toward_target(previous_end + 2, &g_trail_end_state_z, endpoint[2],
                    g_trail_sample_unit_x * 0.00027777778f, g_trail_sample_unit_y * 0.00027777778f, g_trail_sample_unit_z * 0.016666668f));
                qcopy_nc(g_blade_trail_end_points + 1 + g_blade_trail_count, previous_end);
                error += math_fabs(math_step_value_toward_target(previous_origin, &g_trail_origin_state_x, origin[0],
                    g_trail_sample_unit_x * 0.00027777778f, g_trail_sample_unit_y * 0.00027777778f, g_trail_sample_unit_z * 0.016666668f));
                error += math_fabs(math_step_value_toward_target(previous_origin + 1, &g_trail_origin_state_y, origin[1],
                    g_trail_sample_unit_x * 0.00027777778f, g_trail_sample_unit_y * 0.00027777778f, g_trail_sample_unit_z * 0.016666668f));
                error += math_fabs(math_step_value_toward_target(previous_origin + 2, &g_trail_origin_state_z, origin[2],
                    g_trail_sample_unit_x * 0.00027777778f, g_trail_sample_unit_y * 0.00027777778f, g_trail_sample_unit_z * 0.016666668f));
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
