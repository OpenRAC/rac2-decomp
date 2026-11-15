#include "include_asm.h"
#include "names.h"

extern void FastVecSub(float *, const float *, const float *);
extern float vec_length_xy(const float *);

/* Works out how long a shot takes to reach a target and the upward speed it needs to get there. */
float weapon_compute_shot_launch_speed(const float *pos, const float *target, float *outTime, float speed, float gravity) {
    float delta[4];
    float time;
    float distance;

    FastVecSub(delta, target, pos);
    distance = vec_length_xy(delta);
    time = distance / speed;
    if (outTime != 0)
        *outTime = time;
    if (time == 0.0f)
        return 0.0f;
    return -((pos[2] - target[2]) + gravity * (time * time) * 0.5f) / time;
}
