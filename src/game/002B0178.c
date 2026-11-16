#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int g_ground_check_inhibit[] __attribute__((sda));
extern int g_hero_effect_inhibit[] __attribute__((sda));
extern Vector g_camera_vector_scratch;
extern Vector g_coll_hit_position;
extern float g_coll_ground_height;
extern int CollLine(void *, void *, int, void *, int);
extern void gravity_offset_position(void *, float *, float *, float);
extern float fast_vec_dist(void *, void *);

/* Finds the ground below a position and returns the height or distance to it, also giving the spot that was hit. */
float coll_get_ground_distance_below(Vector *position, void *owner, Vector *output)
{
    Vector low, high;
    float distance, result;
    if (g_ground_check_inhibit[0] == 0) {
        qcopy(&low, position);
        low.f[2] = 0.01f;
        qcopy(&high, position);
        high.f[2] += 0.5f;
        if (CollLine(&high, &low, 2, owner, 0)) {
            if (output != 0)
                qcopy(output, &g_coll_hit_position);
            return position->f[2] - g_coll_ground_height;
        }
        if (output != 0)
            qcopy(output, position);
        return position->f[2];
    }
    qcopy(&low, &g_camera_vector_scratch);
    if (g_hero_effect_inhibit[0] != 0) {
        qcopy(&low, position);
        gravity_offset_position(&low, low.f, low.f, -10.0f);
    }
    gravity_offset_position(position, high.f, position->f, -0.5f);
    distance = fast_vec_dist(position, &low);
    if (CollLine(&high, &low, 2, owner, 0)) {
        if (output != 0)
            qcopy(output, &g_coll_hit_position);
        result = fast_vec_dist(position, &g_coll_hit_position);
        if (distance < fast_vec_dist(&g_coll_hit_position, &low))
            result = -result;
        return result;
    }
    if (output != 0)
        qcopy(output, position);
    return distance;
}
