#include "names.h"
/* func_L07_002E2090 (112 bytes): spawns a record through func_L04_0030C4C0 (here
   ref_L07_002E2090_00) with two zeroed vectors whose z is +-0.4 of the z distance
   between the two points, and returns what the spawner returns. */
#include "common.h"

extern void *ref_L07_002E2090_00(void *, void *, void *, void *, void *, void *, int, void *, unsigned int);

/* Spawns an effect between two points, pushing it forward and back along the depth axis by 40
   percent of the gap between them. */
void *part_spawn_between_points_depth_push(void *owner, float *start_pos, float *end_pos, void *extra, int option, void *extra_data, unsigned int extra_flags) {
    float start_velocity[4];
    float end_velocity[4];
    float depth_speed;
    qzero_nc(start_velocity);
    qzero_nc(end_velocity);
    depth_speed = (end_pos[2] - start_pos[2]) * 0.4f;
    start_velocity[2] = depth_speed;
    end_velocity[2] = -depth_speed;
    return ref_L07_002E2090_00(owner, start_pos, start_velocity, end_pos, end_velocity, extra, option, extra_data, extra_flags);
}
