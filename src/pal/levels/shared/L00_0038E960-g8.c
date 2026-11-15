#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float math_random_float_range(float,float);
extern float math_random_signed_float_range(float,float);
extern void vec_build_spherical_offset(float *,float,float,float);
extern int math_random_int_range(int,int);
extern float mat_fast_helper_a(float,float);
extern float vec_length_xy(void *);
extern float FastAddRotations(float,float);
extern char *part_spawn_streak_effect(void *,void *);
extern char *part_spawn_trailing_spark(void *,void *,unsigned int,unsigned int,int,int,float);
extern void func_PAL_L00_0038E960(Vector4 *,int);
typedef struct { char pad[0x20]; Vector4 position; } CollisionResult;
extern CollisionResult g_collision_result;
extern Vector4 g_camera_l00_position;

void func_PAL_L00_0038EB58(char *owner)
{
    Vector4 velocity,position;
    float tilt,unusedHeading,angle;
    int i;
    FastVecSub(&velocity,&g_camera_l00_position,&g_collision_result.position);
    tilt=-mat_fast_helper_a(vec_length_xy(&velocity),velocity.f[2]);
    unusedHeading=mat_fast_helper_a(velocity.f[0],velocity.f[1]);
    for(i=19;i>=0;--i) {
        angle=FastAddRotations(math_random_signed_float_range(0,3.1415927f),tilt);
        vec_build_spherical_offset(velocity.f,0.2f,FastAddRotations(math_random_signed_float_range(0,3.1415927f),tilt),angle);
        FastVecScale(&position,&velocity,math_random_float_range(1,3));
        FastVecAdd(&position,&position,&g_collision_result.position);
        part_spawn_streak_effect(&position,&velocity);
    }
    for(i=9;i>=0;--i) {
        position.f[0]=g_collision_result.position.f[0]+math_random_signed_float_range(0,0.1f);
        position.f[1]=g_collision_result.position.f[1]+math_random_signed_float_range(0,0.1f);
        position.f[2]=g_collision_result.position.f[2]+math_random_signed_float_range(0,0.1f);
        angle=FastAddRotations(math_random_signed_float_range(0,3.1415927f),tilt);
        vec_build_spherical_offset(velocity.f,0.05f,FastAddRotations(math_random_signed_float_range(0,3.1415927f),tilt),angle);
        part_spawn_trailing_spark(&position,&velocity,0x4F007FFF,0x1FFFFFFF,math_random_int_range(8,17),1,20000);
    }
    if(FIELD(short,FIELD(char *,owner,0x68),0x78)==43) func_PAL_L00_0038E960(&g_collision_result.position,10);
}
