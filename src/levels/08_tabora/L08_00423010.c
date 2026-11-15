#include "common.h"
typedef struct { float f0, f4, f8, fC; } Quad;
extern float vec_distance_xy(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern f32 D_00189EA8;
extern char g_hero_position[];
extern f32 coll_find_ground_height(Quad *, f32, f32, f32, f32);
extern void FastVecSub(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float vec_length_xy(void *);
/* The EE ABI assigns integer and FP argument registers independently. */
extern float MobySpringTurn(void *, float, float, float, float, void *);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int moby_move_and_collide(void *, void *, int, float, float, float);
extern float math_turn_angle_toward_target(void *, float, float, float, float, float);

/* Steer toward the selected target, adjust elevation, and apply movement. */
/* Moves the sandfly toward its target: it turns, speeds up and slows down, follows the ground height and reports if it arrived. */
int sandfly_move_toward_target(char *object, float turn, float turnAccel, float turnDamp,
                     float accel, float friction, float maxSpeed, float rise, float stop) {
    float delta[4], point[4];
    char *state = *(char **)(object + 0x68);
    float heading, distance, acceleration, speed, limit, height, pitch;
    float scaledDistance;
    int result = 0;
    heading=mat_fast_helper_a(*(float *)(state+0x160)-*(float *)(object+0x10),
                          *(float *)(state+0x164)-*(float *)(object+0x14));
    FastVecSub(delta,state+0x160,object+0x10);
    distance = vec_length_xy(delta);
    distance -= stop;
    if (distance < 0)
        distance = 0;
    scaledDistance = distance * 0.00027777778450399637f;
    acceleration = accel;
    acceleration *= scaledDistance;
    if (acceleration > accel * 0.00027777778450399637f)
        acceleration = accel * 0.00027777778450399637f;
    speed = *(float *)(state + 0x1C0);
    speed += acceleration;
    if (distance < speed * 10.0f)
        speed -= friction * speed;
    if (distance < stop)
        result = 8;
    limit = maxSpeed * 0.01666666753590107f;
    if (speed > limit)
        speed = limit;
    else if (speed < -limit)
        speed = -limit;
    MobySpringTurn(object,heading,turn*4.848137450608192e-06f,
                  turnAccel*4.848137450608192e-06f,turnDamp*0.0002908882452175021f,state+0x1C4);
    point[0]=math_fast_sin_or_cos_a(heading)*speed*10.0f;
    point[1]=math_fast_sin_or_cos_b(heading)*speed*10.0f;
    point[2]=0;
    FastVecAdd(point,point,object+0x10);
    height=*(float *)(state+0x1D4);
    if ((unsigned char)object[0x20] == 8)
        height = height > D_00189EA8 ? height : D_00189EA8;
    point[2]=coll_find_ground_height((Quad *)point,*(float *)(state+0x158)+3.0f,
                              *(float *)(state+0x158)-10.0f,height,*(float *)(state+0x1D0));
    if (vec_distance_xy(object+0x10,g_hero_position)<5.0f && point[2]>*(float *)(g_hero_position+8))
        point[2]=*(float *)(g_hero_position+8);
    point[2]+=rise;
    pitch=mat_fast_helper_a(vec_distance_xy(object+0x10,point),point[2]-*(float *)(object+0x18));
    vec_build_spherical_offset(state+0x170,speed,*(float *)(object+0xF8),pitch);
    *(float *)(object+0x18)+=0.4f;
    result |= moby_move_and_collide(object,state+0x170,0,0.0f,0.75f,0.0f);
    *(float *)(object+0x18)-=0.4f;
    *(float *)(object+0xF4)=math_turn_angle_toward_target(state+0x1C8,*(float *)(object+0xF4),pitch,
                                          0.0017453294713050127f,0.0008726647356525064f,0.0008726647356525064f);
    if (result&7) MobySpringTurn(object,heading,turn*1.4544411897077225e-05f,
                                turnAccel*4.848137450608192e-06f,turnDamp*0.0008726647356525064f,state+0x1C4);
    *(float *)(state+0x1C0)=speed;
    return result;
}
