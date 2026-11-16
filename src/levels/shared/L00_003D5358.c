#include "names.h"
/* func_L00_003D5358 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections). */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern float math_random_float_range(float low, float high);
extern void moby_transform_joint_to_world(char *object, int joint, void *out);
extern void *part_spawn_object_relative_particle(char *object, void *position, void *velocity, void *parameters, int mode);
extern char g_drift_particle_desc_a __attribute__((sda));
extern char g_drift_particle_desc_b __attribute__((sda));
extern char g_drift_particle_desc_c __attribute__((sda));


extern char g_hero_state[] __attribute__((nosda));
extern float IntToFloat(int value);
extern float math_fast_sin_or_cos_a(float angle);
extern float math_fast_sin_or_cos_b(float angle);
extern float math_fast_angle_helper(float value);
extern void vec_scale_to_length(void *out, void *vector, float scale);
extern void FastVecAdd(void *out, void *left, void *right);
extern void FastVecSub(void *out, void *left, void *right);
extern void FastVecScale(void *out, void *vector, float scale);
extern float FastVecDot(void *left, void *right);
extern float FastVecLength(void *vector);
extern float math_approach_with_velocity(float *position, float target, float *velocity, float acceleration, float damping, float limit, int direction);


extern float g_unused_level_float_a __attribute__((sda));
extern float g_unused_level_float_b __attribute__((sda));
extern float g_unused_level_float_c __attribute__((sda));
extern float g_direction_step_scale __attribute__((sda));
extern char *SelectBestEligibleTarget(void *axis, int mode, int flag, float value, float z, float low, float high);
extern void CalculateAimedLaunchVelocity(void *velocity, void *position, int handle, int mode, float a, float b, float c, float d);
extern void math_apply_axis_rotation_to_quat(void *out, void *source, void *axis, float angle);

/* Turns the object toward a target point, easing its angle with the given speed, damping and limit. */
void moby_l00_turn_toward_target(char *object, void *target, float *velocity, float acceleration, float damping, float limit)
{
    Vector difference, projection;
    char *base;
    float angle, magnitude;
    float zero;
    FastVecSub(&difference, target, object + 0x10);
    base = g_hero_state;
    zero = 0.0f;
    angle = FastVecDot(&difference, *(char **)(base + 0x2290) + 0xe0);
    FastVecScale(&projection, *(char **)(base + 0x2290) + 0xe0, angle);
    FastVecSub(&difference, &difference, &projection);
    angle = FastVecDot(&difference, *(char **)(base + 0x2290) + 0xc0);
    magnitude = FastVecLength(&difference);
    if (magnitude != zero) {
        angle = math_fast_angle_helper(angle / magnitude);
        angle = 1.5707964f - angle;
        if (FastVecDot(&difference, *(char **)(base + 0x2290) + 0xd0) < zero)
            angle = -angle;
        math_approach_with_velocity((float *)(object + 0xf8), angle, velocity, acceleration, damping, limit, 0);
    }
}
