#include "include_asm.h"

extern void func_00282CF0(char *, char *, char *);
extern void func_002830C0(float *, float *, char *);
extern void func_00283098(float *, float *, char *);
extern float func_002A7798(float);
extern float func_00282C48(float);
extern void func_002A8240(char *, float *, int, float, float, float);
extern void func_002A7CA0(char *, float, char *, float, float, float);

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
    func_00282CF0((char *)delta, st + 0x220, obj + 0x10);
    func_002830C0(delta, delta, inv);
    func_002830C0(vel, (float *)(st + 0x230), inv);
    if (delta[0] > 0.0f) {
        speed = posSpeed * 0.020000001f;
        accel = posAccel * 0.00040000002f;
    } else {
        speed = negSpeed * 0.020000001f;
        accel = negAccel * 0.00040000002f;
    }
    dist = func_00282C48(delta[0]);
    value = func_00282C48(vel[0]);
    if (dist < value * (value / accel)) {
        value -= accel;
        done = 1;
    } else {
        value += accel * func_002A7798((speed - value) / speed);
    }
    if (delta[0] < 0.0f) delta[0] = -value;
    else delta[0] = value;
    vel[0] = vel[0] * blend + (delta[0] *= 1.0f - blend);
    ySpeed = sideSpeed * 0.020000001f;
    yAccel = sideAccel * 0.00040000002f;
    yDist = func_00282C48(delta[1]);
    yValue = func_00282C48(vel[1]);
    if (yDist < yValue * (yValue / yAccel)) {
        yValue -= yAccel;
        done++;
    } else {
        yValue += yAccel * func_002A7798((ySpeed - yValue) / ySpeed);
    }
    if (delta[1] < 0.0f) delta[1] = -yValue;
    else delta[1] = yValue;
    vel[1] = vel[1] * blend + (delta[1] *= 1.0f - blend);
    func_00283098((float *)(st + 0x230), vel, mat);
    func_00283098(delta, delta, mat);
    limit = verticalLimit * 0.020000001f;
    if (delta[2] > limit) delta[2] = limit;
    else if (delta[2] < -limit) delta[2] = -limit;
    *(float *)(st + 0x238) += (delta[2] - *(float *)(st + 0x238)) * verticalBlend;
    delta[2] = 0;
    func_002A8240(obj, (float *)(st + 0x230), 0, delta[2], 1.5f, delta[2]);
    func_002A7CA0(obj, yaw, st + 0x25C, 0.0008377582f, 0.0025132746f, 0.04188791f);
    return done == 2;
}
