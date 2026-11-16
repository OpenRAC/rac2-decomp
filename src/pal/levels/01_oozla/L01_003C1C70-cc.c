#include "names.h"
/* func_PAL_L01_003C1C70, the PAL copy of func_L01_003BE058: the same C, where lit 0.0008726647356525064f becomes 0.0012566373f; lit 0.0008726647356525064f becomes 0.0012566373f. */
#include "common.h"

#define I32(p,o) (*(int *)((p)+(o)))
#define F32(p,o) (*(float *)((p)+(o)))
extern float mat_fast_helper_a(float,float),vec_length_xy(void *),vec_distance_xy(void *,void *);
extern void FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *);
struct family_27f9_object;
extern float MobySpringTurn(struct family_27f9_object *,float,float *,float,float,float);
extern float math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern float coll_get_ground_height_with_limit(void *,float,float,float,float);
extern float g_hero_position[];
/* Scalar view of D_00189EA0[2] (its z): retail addresses it on its own. */
extern float g_hero_height_limit;
extern void vec_build_spherical_offset(float *,float,float,float);
extern int moby_move_and_collide(void *,void *,int,float,float,float);
extern float math_turn_angle_toward_target(float *,float,float,float,float,float);
extern int coll_test_point_against_shapes(void *,int,int,int,int);
static __inline__ float ScaleAcceleration(float acceleration, float distance)
{
    return acceleration * distance;
}

/* Steers a flying moby towards a target point. It speeds up and slows down with distance, turns smoothly, follows the ground height and returns flags when it arrives or hits something (PAL version). */
int moby_l01_steer_toward_target_pal(u8 *moby,float turn,float turn2,float rate,float acceleration,float brake,float maxspeed,float altitude,float deadzone)
{
    u8 *state=*(u8 **)(moby+0x68);
    float direction[4] __attribute__((aligned(16)));
    float proposed[4] __attribute__((aligned(16)));
    float angle, distance, step, cap, limit, pitch, height;
    int flags=0;
    angle=mat_fast_helper_a(F32(state,0x1e0)-F32(moby,0x10),F32(state,0x1e4)-F32(moby,0x14));
    FastVecSub(direction,state+0x1e0,moby+0x10);
    distance=vec_length_xy(direction)-deadzone;
    if(distance<0.0f) distance=0.0f;
    cap=ScaleAcceleration(acceleration,0.00040000002f);
    step=ScaleAcceleration(acceleration,distance*0.00040000002f);
    if(cap<step) step=cap;
    F32(state,0x240)+=step;
    if(distance<F32(state,0x240)*10.0f)
        F32(state,0x240)-=brake*F32(state,0x240);
    if(distance<deadzone) flags=8;
    limit=maxspeed*F32(state,0x28c)*0.020000001f;
    if(limit<F32(state,0x240)) F32(state,0x240)=limit;
    else if(F32(state,0x240)<-limit) F32(state,0x240)=-limit;
    MobySpringTurn((struct family_27f9_object *)moby,angle,(float *)(state+0x244),
        turn*6.981318e-06f,turn2*6.981318e-06f,rate*0.0003490659f);
    proposed[0]=math_fast_sin_or_cos_a(angle)*F32(state,0x240)*10.0f;
    proposed[1]=math_fast_sin_or_cos_b(angle)*F32(state,0x240)*10.0f;
    proposed[2]=0.0f;
    FastVecAdd(proposed,proposed,moby+0x10);
    height=F32(state,0x27c);
    if(moby[0x20]==8) height = height > g_hero_height_limit ? height : g_hero_height_limit;
    proposed[2]=coll_get_ground_height_with_limit(proposed,F32(state,0x1d8)+2.0f,F32(state,0x1d8)-3.0f,height,F32(state,0x288));
    if(vec_distance_xy(moby+0x10,g_hero_position)<5.0f && g_hero_position[2]<proposed[2]) proposed[2]=g_hero_position[2];
    proposed[2]+=altitude;
    pitch=mat_fast_helper_a(vec_distance_xy(moby+0x10,proposed),proposed[2]-F32(moby,0x18));
    vec_build_spherical_offset((float *)(state+0x1f0),F32(state,0x240),F32(moby,0xf8),pitch);
    if(moby[0x20]!=8) F32(state,0x1f8)*=0.4f;
    else if((unsigned int)(moby[0x95]-1)<2) {
        I32(state,0x1f0)=0;
        I32(state,0x1f4)=0;
    }
    flags|=moby_move_and_collide(moby,state+0x1f0,0,0.0f,0.3f,0.0f);
    F32(moby,0xf4)=math_turn_angle_toward_target((float *)(state+0x248),F32(moby,0xf4),-pitch,
        0.0025132746f,0.0012566373f,0.0012566373f);
    if(I32(state,0x238)>0 && coll_test_point_against_shapes((char *)(moby+0x10),I32(state,0x210),I32(state,0x218),I32(state,0x21c),-1)==0) flags|=7;
    if(flags&7) MobySpringTurn((struct family_27f9_object *)moby,angle,(float *)(state+0x244),
        turn*2.0943955e-05f,turn2*6.981318e-06f,rate*0.0010471977f);
    return flags;
}
