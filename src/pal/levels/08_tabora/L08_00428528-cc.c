/* func_PAL_L08_00428528, the PAL copy of func_L08_00423010: the same C, where lit 0.0008726647356525064f becomes 0.0010471977f. */
#include "common.h"
typedef struct { float f0, f4, f8, fC; } Quad;
extern float func_00282E80(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern f32 D_00189EA8;
extern char D_00189EA0[];
extern f32 func_L08_00422850(Quad *, f32, f32, f32, f32);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00282E20(void *);
/* The EE ABI assigns integer and FP argument registers independently. */
extern float func_002A7CA0(void *, float, float, float, float, void *);
extern void func_002AF000(void *, float, float, float);
extern int func_002A8240(void *, void *, int, float, float, float);
extern float func_L01_00310BC0(void *, float, float, float, float, float);

/* Steer toward the selected target, adjust elevation, and apply movement. */
int func_PAL_L08_00428528(char *object, float turn, float turnAccel, float turnDamp,
                     float accel, float friction, float maxSpeed, float rise, float stop) {
    float delta[4], point[4];
    char *state = *(char **)(object + 0x68);
    float heading, distance, acceleration, speed, limit, height, pitch;
    float scaledDistance;
    int result = 0;
    heading=func_00283248(*(float *)(state+0x160)-*(float *)(object+0x10),
                          *(float *)(state+0x164)-*(float *)(object+0x14));
    func_00282CF0(delta,state+0x160,object+0x10);
    distance = func_00282E20(delta);
    distance -= stop;
    if (distance < 0)
        distance = 0;
    scaledDistance = distance * 0.00040000002f;
    acceleration = accel;
    acceleration *= scaledDistance;
    if (acceleration > accel * 0.00040000002f)
        acceleration = accel * 0.00040000002f;
    speed = *(float *)(state + 0x1C0);
    speed += acceleration;
    if (distance < speed * 10.0f)
        speed -= friction * speed;
    if (distance < stop)
        result = 8;
    limit = maxSpeed * 0.020000001f;
    if (speed > limit)
        speed = limit;
    else if (speed < -limit)
        speed = -limit;
    func_002A7CA0(object,heading,turn*6.981318e-06f,
                  turnAccel*6.981318e-06f,turnDamp*0.0003490659f,state+0x1C4);
    point[0]=func_00283180(heading)*speed*10.0f;
    point[1]=func_00283198(heading)*speed*10.0f;
    point[2]=0;
    func_00282CC0(point,point,object+0x10);
    height=*(float *)(state+0x1D4);
    if ((unsigned char)object[0x20] == 8)
        height = height > D_00189EA8 ? height : D_00189EA8;
    point[2]=func_L08_00422850((Quad *)point,*(float *)(state+0x158)+3.0f,
                              *(float *)(state+0x158)-10.0f,height,*(float *)(state+0x1D0));
    if (func_00282E80(object+0x10,D_00189EA0)<5.0f && point[2]>*(float *)(D_00189EA0+8))
        point[2]=*(float *)(D_00189EA0+8);
    point[2]+=rise;
    pitch=func_00283248(func_00282E80(object+0x10,point),point[2]-*(float *)(object+0x18));
    func_002AF000(state+0x170,speed,*(float *)(object+0xF8),pitch);
    *(float *)(object+0x18)+=0.4f;
    result |= func_002A8240(object,state+0x170,0,0.0f,0.75f,0.0f);
    *(float *)(object+0x18)-=0.4f;
    *(float *)(object+0xF4)=func_L01_00310BC0(state+0x1C8,*(float *)(object+0xF4),pitch,
                                          0.0025132746f,0.0012566373f,0.0012566373f);
    if (result&7) func_002A7CA0(object,heading,turn*2.0943955e-05f,
                                turnAccel*6.981318e-06f,turnDamp*0.0010471977f,state+0x1C4);
    *(float *)(state+0x1C0)=speed;
    return result;
}
