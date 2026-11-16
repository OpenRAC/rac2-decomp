#include "include_asm.h"
#include "names.h"

extern void vec_clear_128(void *target);
extern void vec_clear_128(void *target);
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecSub(float *out, const float *a, const float *b);
extern void FastVecSub(float *out, const float *a, const float *b);
extern float moby_aim_at_target(char *a0, void *a1, char *a2, int a3);
#include "common.h"
typedef union { TI128 q; float f[4]; } MotionVector;
extern float moby_measure_step_angle(char *, TI128 *, char *);
extern float fast_vec_dist(void *, void *);
extern float square_root(float);
extern void moby_build_forward_vector(char *, float *, float);
extern void vec_transform_and_set_height(char *, char *, char *, float, char *);
extern float FastVecDot(void *, void *);
extern void vec_clamp_length(float *, float);
extern void FastVecAdd(void *, void *, void *);
extern float vec_get_horizontal_offset_length(char *, char *, char *);
extern float gravity_get_center_distance(char *);
extern void moby_mix_on_inner_data(u8 *, float *, float *, float);
extern float vec_get_vertical_offset(char *, char *, char *);
extern void math_approach_target_with_braking(float *, float, float, float, float);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern float gravity_get_center_distance(char *p);

/* Steers the moby toward the target: aims it, works out the wanted speed from the distance and
   limits, eases the current velocity toward it and keeps the moby near the ground (PAL: 50 Hz
   timings). */
void moby_l02_steer_toward_target_pal(char *object, char *data, void *target, TI128 *input, void *unused0, void *unused1, char *transform) {
    MotionVector desired, change;
    float vertical;
    float heading, distance, speed, height, drop;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        moby_aim_at_target(object, data, (char *)input, (int)transform);
    heading = 0.0f;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        heading = moby_measure_step_angle(object, input, transform);
    if (*(float *)(data + 0x30) < heading) {
        vec_clear_128(&desired.q);
    } else {
        float gap;
        distance = fast_vec_dist(object + 0x10, target);
        *(float *)(data + 0xCC) = distance;
        gap = *(float *)(data + 0x34);
        if (distance <= gap) {
            qzero(&desired);
        } else {
            gap = distance - gap;
            speed = square_root((gap + gap) * *(float *)(data + 0x24));
            if (*(float *)(data + 0x28) < speed)
                speed = *(float *)(data + 0x28);
            moby_build_forward_vector(object, desired.f, speed);
        }
    }
    FastVecSub(change.f, desired.f, (float *)(data + 0xA0));
    vec_transform_and_set_height(object, (char *)&change, (char *)&change, 0.0f, transform);
    if (FastVecDot(&desired, data + 0xA0) > 0.0f)
        vec_clamp_length(change.f, *(float *)(data + 0x20));
    else
        vec_clamp_length(change.f, *(float *)(data + 0x24));
    FastVecAdd(data + 0xA0, data + 0xA0, &change);
    *(float *)(data + 0xB0) = vec_get_horizontal_offset_length(object, data + 0xA0, transform);
    if (!(*(unsigned int *)(data + 0x38) & 4)) {
        height = gravity_get_center_distance(object + 0x10);
        if (*(float *)(data + 0x90) < height) {
            moby_mix_on_inner_data((u8 *)object, (float *)(data + 0xA0), (float *)(data + 0xA0), *(float *)(data + 0x2C));
            if (*(short *)(data + 0xC0) == 0)
                *(unsigned int *)(data + 0x94) |= 0x20;
        } else {
            vertical = vec_get_vertical_offset(object, data + 0xA0, transform);
            drop = vertical;
            if (*(float *)(data + 0x90) - height < drop)
                vertical = *(float *)(data + 0x90) - height;
            else if (vertical < 0.0f)
                vertical = 0.0f;
            math_approach_target_with_braking(&vertical, *(float *)(data + 0x90) - height, 0.016f, 0.016f, 1.0f);
            vec_transform_and_set_height(object, data + 0xA0, data + 0xA0, vertical, transform);
        }
    }
}

