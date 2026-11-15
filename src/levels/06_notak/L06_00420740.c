#include "include_asm.h"
#include "names.h"
extern void func_00282CF0(char *, char *, char *);
extern void func_002830C0(float *, float *, char *);
extern void func_00283098(float *, float *, char *);
extern float func_002A7798(float);
extern float func_00282C48(float);
extern void func_002A8240(char *, float *, int, float, float, float);
/* The integer and FP argument banks keep their own order in the EE ABI. */
extern void func_002A7CA0(char *, float, char *, float, float, float);
/* Moves the actor toward its goal using the given side-to-side and forward limits, and turns it to face the yaw; returns 1 when both directions have slowed to a stop. */
int func_L06_00420740(char *moby, char *unused, char *mat, char *inv,
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
    dist = FloatAbs(delta[0]);
    value = FloatAbs(vel[0]);
    if (dist < value * (value / accel)) {
        value -= accel;
        done = 1;
    } else {
        value += accel * EaseOutQuad((speed - value) / speed);
    }
    if (delta[0] < 0.0f) delta[0] = -value;
    else delta[0] = value;
    vel[0] = vel[0] * blend + (delta[0] *= 1.0f - blend);
    ySpeed = sideSpeed * 0.01666666753590107f;
    yAccel = sideAccel * 0.00027777778450399637f;
    yDist = FloatAbs(delta[1]);
    yValue = FloatAbs(vel[1]);
    if (yDist < yValue * (yValue / yAccel)) {
        yValue -= yAccel;
        done++;
    } else {
        yValue += yAccel * EaseOutQuad((ySpeed - yValue) / ySpeed);
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
    MoveAndCollideObject(moby, (float *)(vars + 0x230), 0, delta[2], 1.5f, delta[2]);
    MobySpringTurn(moby, yaw, vars + 0x25C, 0.0005817764904350042f, 0.0017453294713050127f, 0.03490659222006798f);
    return done == 2;
}

