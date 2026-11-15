#include "include_asm.h"
#include "names.h"
extern void FastVecSub(char *, char *, char *);
extern void transform_vector(float *, float *, char *);
extern void matrix_mul_vec3(float *, float *, char *);
extern float math_ease_out_quad(float);
extern float math_fabs(float);
extern void moby_move_and_collide(char *, float *, int, float, float, float);
/* The integer and FP argument banks keep their own order in the EE ABI. */
extern void MobySpringTurn(char *, float, char *, float, float, float);
/* Moves the actor toward its goal using the given side-to-side and forward limits, and turns it to face the yaw; returns 1 when both directions have slowed to a stop. */
int actor_move_local_axes(char *moby, char *unused, char *mat, char *inv,
                        float yaw, float blend, float posSpeed, float posAccel,
                        float negSpeed, float negAccel, float sideSpeed, float sideAccel,
                        float verticalBlend, float verticalLimit)
{
    float delta[4], vel[4];
    char *vars = *(char **)(moby + 0x68);
    float accel = 0.0f, speed, value, dist, limit;
    float yAccel, ySpeed, yValue, yDist;
    int done = 0;
    FastVecSub((char *)delta, vars + 0x220, moby + 0x10);
    transform_vector(delta, delta, inv);
    transform_vector(vel, (float *)(vars + 0x230), inv);
    if (delta[0] > 0.0f) {
        speed = posSpeed * 0.01666666753590107f;
        accel = posAccel * 0.00027777778450399637f;
    } else {
        speed = negSpeed * 0.01666666753590107f;
        accel = negAccel * 0.00027777778450399637f;
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
    ySpeed = sideSpeed * 0.01666666753590107f;
    yAccel = sideAccel * 0.00027777778450399637f;
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
    matrix_mul_vec3((float *)(vars + 0x230), vel, mat);
    matrix_mul_vec3(delta, delta, mat);
    limit = verticalLimit * 0.01666666753590107f;
    if (delta[2] > limit) delta[2] = limit;
    else if (delta[2] < -limit) delta[2] = -limit;
    *(float *)(vars + 0x238) += (delta[2] - *(float *)(vars + 0x238)) * verticalBlend;
    delta[2] = 0;
    moby_move_and_collide(moby, (float *)(vars + 0x230), 0, delta[2], 1.5f, delta[2]);
    MobySpringTurn(moby, yaw, vars + 0x25C, 0.0005817764904350042f, 0.0017453294713050127f, 0.03490659222006798f);
    return done == 2;
}

