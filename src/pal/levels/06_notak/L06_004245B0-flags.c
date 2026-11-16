#include "include_asm.h"
#include "names.h"

extern void FastVecSub(char *, char *, char *);
extern void transform_vector(float *, float *, char *);
extern void matrix_mul_vec3(float *, float *, char *);
extern float math_ease_out_quad(float);
extern float math_fabs(float);
extern int moby_move_and_collide(char *, float *, int, float, float, float);
extern float MobySpringTurn(char *, float, char *, float, float, float);

/* Moves the actor toward its goal using the given side-to-side and forward limits, and turns it to face the yaw; returns 1 when both directions have slowed to a stop (PAL: 50 Hz timings). */
int actor_move_local_axes_pal(char *obj, char *unused, char *mat, char *inv,
                        float yaw, float blend, float pos_speed, float pos_accel,
                        float neg_speed, float neg_accel, float side_speed, float side_accel,
                        float vertical_blend, float vertical_limit)
{
    float delta[4], vel[4];
    char *state = *(char **)(obj + 0x68);
    float accel = 0.0f, speed, value, dist, limit;
    float y_accel, y_speed, y_value, y_dist;
    int done = 0;
    FastVecSub((char *)delta, state + 0x220, obj + 0x10);
    transform_vector(delta, delta, inv);
    transform_vector(vel, (float *)(state + 0x230), inv);
    if (delta[0] > 0.0f) {
        speed = pos_speed * 0.020000001f;
        accel = pos_accel * 0.00040000002f;
    } else {
        speed = neg_speed * 0.020000001f;
        accel = neg_accel * 0.00040000002f;
    }
    dist = math_fabs(delta[0]);
    value = math_fabs(vel[0]);
    if (dist < value * (value / accel)) {
        value -= accel;
        done = 1;
    } else {
        value += accel * math_ease_out_quad((speed - value) / speed);
    }
    if (delta[0] < 0.0f) delta[0] = -value;
    else delta[0] = value;
    vel[0] = vel[0] * blend + (delta[0] *= 1.0f - blend);
    y_speed = side_speed * 0.020000001f;
    y_accel = side_accel * 0.00040000002f;
    y_dist = math_fabs(delta[1]);
    y_value = math_fabs(vel[1]);
    if (y_dist < y_value * (y_value / y_accel)) {
        y_value -= y_accel;
        done++;
    } else {
        y_value += y_accel * math_ease_out_quad((y_speed - y_value) / y_speed);
    }
    if (delta[1] < 0.0f) delta[1] = -y_value;
    else delta[1] = y_value;
    vel[1] = vel[1] * blend + (delta[1] *= 1.0f - blend);
    matrix_mul_vec3((float *)(state + 0x230), vel, mat);
    matrix_mul_vec3(delta, delta, mat);
    limit = vertical_limit * 0.020000001f;
    if (delta[2] > limit) delta[2] = limit;
    else if (delta[2] < -limit) delta[2] = -limit;
    *(float *)(state + 0x238) += (delta[2] - *(float *)(state + 0x238)) * vertical_blend;
    delta[2] = 0;
    moby_move_and_collide(obj, (float *)(state + 0x230), 0, delta[2], 1.5f, delta[2]);
    MobySpringTurn(obj, yaw, state + 0x25C, 0.0008377582f, 0.0025132746f, 0.04188791f);
    return done == 2;
}
