#include "include_asm.h"
#include "names.h"

extern void FastVecSub(char *, char *, char *);
extern void transform_vector(float *, float *, char *);
extern void matrix_mul_vec3(float *, float *, char *);
extern float math_ease_out_quad(float);
extern float math_fabs(float);
extern int moby_move_and_collide(char *, float *, int, float, float, float);
extern float MobySpringTurn(char *, float, char *, float, float, float);

int func_PAL_L06_00424AE0(char *obj, char *unused, char *mat, char *inv,
                        float yaw, float blend, float posSpeed, float posAccel,
                        float negSpeed, float negAccel, float sideSpeed, float sideAccel,
                        float verticalBlend, float verticalLimit)
{
    float delta[4], vel[4];
    char *st = *(char **)(obj + 0x68);
    float accel = 0.0f, speed, value, dist, limit;
    float yAccel, ySpeed, yValue, yDist;
    int done = 0;
    FastVecSub((char *)delta, st + 0x220, obj + 0x10);
    transform_vector(delta, delta, inv);
    transform_vector(vel, (float *)(st + 0x230), inv);
    if (delta[0] > 0.0f) {
        speed = posSpeed * 0.020000001f;
        accel = posAccel * 0.00040000002f;
    } else {
        speed = negSpeed * 0.020000001f;
        accel = negAccel * 0.00040000002f;
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
    ySpeed = sideSpeed * 0.020000001f;
    yAccel = sideAccel * 0.00040000002f;
    yDist = math_fabs(delta[1]);
    yValue = math_fabs(vel[1]);
    if (yDist < yValue * (yValue / yAccel)) {
        yValue -= yAccel;
        done++;
    } else {
        yValue += yAccel * math_ease_out_quad((ySpeed - yValue) / ySpeed);
    }
    if (delta[1] < 0.0f) delta[1] = -yValue;
    else delta[1] = yValue;
    vel[1] = vel[1] * blend + (delta[1] *= 1.0f - blend);
    matrix_mul_vec3((float *)(st + 0x230), vel, mat);
    matrix_mul_vec3(delta, delta, mat);
    limit = verticalLimit * 0.020000001f;
    if (delta[2] > limit) delta[2] = limit;
    else if (delta[2] < -limit) delta[2] = -limit;
    *(float *)(st + 0x238) += (delta[2] - *(float *)(st + 0x238)) * verticalBlend;
    delta[2] = 0;
    moby_move_and_collide(obj, (float *)(st + 0x230), 0, delta[2], 1.5f, delta[2]);
    MobySpringTurn(obj, yaw, st + 0x25C, 0.0008377582f, 0.0025132746f, 0.04188791f);
    return done == 2;
}
