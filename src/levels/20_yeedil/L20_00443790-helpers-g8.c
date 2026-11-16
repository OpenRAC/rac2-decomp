#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_yeedil_lobbed_speed __attribute__((sda));
extern float g_yeedil_lobbed_accel __attribute__((sda));
extern float g_yeedil_lobbed_angle __attribute__((sda));

extern void *CreateMoby(int);
extern void moby_init_child_from_parent(char *, char *);
extern void euler_rotation_basis(char *, char *);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecCross(char *, char *, char *);
extern float math_fast_sin_or_cos_b(float);
extern void vec_set_direction_with_complement(float *, float *, float);
extern float weapon_compute_shot_launch_speed(char *, char *, float *, float, float);
extern int FloatToInt(float);
extern void tumbling_debris_update(char *);

/* Creates an object of the given class at the owner and throws it in an arc toward the target. Returns the new object. */
char *yeedil_boss_spawn_lobbed_object(char *owner, int class_id, char *aim_target) {
    char *obj = (char *)CreateMoby(class_id);
    char *state;
    char *velocity;
    float speed;
    float acceleration;
    float flight_time;
    unsigned short flags;

    if (obj != 0) {
        moby_init_child_from_parent(obj, owner);
        qcopy(obj + 0xF0, owner + 0xF0);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        flags = *(unsigned short *)(obj + 0x34);
        flags |= 0x100;
        flags &= 0xEFDF;
        state = *(char **)(obj + 0x68);
        speed = g_yeedil_lobbed_speed * 0.0166666675f;
        acceleration = g_yeedil_lobbed_accel * 0.000277777785f;
        velocity = state + 0x10;
        *(unsigned short *)(obj + 0x34) = flags;
        flight_time = 0.0f;
        FastVecSub(state, aim_target, obj + 0x10);
        *(float *)(state + 8) = 0.0f;
        vec_scale_to_length(state, state, speed);
        FastVecCross(velocity, state, obj + 0xE0);
        vec_set_direction_with_complement((float *)velocity, (float *)velocity, math_fast_sin_or_cos_b(g_yeedil_lobbed_angle * 0.000290888245f));
        *(float *)(state + 8) = weapon_compute_shot_launch_speed(obj + 0x10, aim_target, &flight_time, speed, -acceleration);
        *(float *)(state + 0x20) = acceleration;
        *(int *)(state + 0x24) = FloatToInt(flight_time);
        *(void (**)(char *))(obj + 0x64) = tumbling_debris_update;
    }
    return obj;
}
