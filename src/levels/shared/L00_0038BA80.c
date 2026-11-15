#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float FastVecDot(void *,void *);
extern float FastVecLength(void *);
extern float math_fabs(float);
extern float FastDiffRots(float,float);
extern float math_fast_float_g(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_random_float_range(float,float);
extern float math_random_signed_float_range(float,float);
extern float math_random_angle(void);
extern int math_random_int_below(int);
extern void vec_build_spherical_offset(float *,float,float,float);
extern char *part_spawn_ground_effect(void *,int,unsigned int,int,int,void *,int,float,float,float);
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(void *,void *);
extern void anim_start_immediate(signed char *,int,int);
extern void moby_set_light_color(void *,int);
extern void euler_rotation_basis(void *,void *);
extern void moby_get_facing_direction(void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern float math_fast_sin_or_cos_b(float);
extern void quaternion_to_rotation_basis(void *,void *);
extern void multiply_matrix3x3(void *,void *,void *);
extern void vec_clear_128(void *);
extern int slot_alloc_for_object(unsigned char *,unsigned int);
extern int part_alloc_effect_slot(void *,void *,float,float,float);
extern void moby_mark_spawned(void *);
extern void func_002A0F48(void *);
extern int math_random_int_range(int,int);
extern float mat_fast_helper_a(float,float);
extern float vec_length_xy(void *);
extern float vec_distance_xy(void *,void *);
extern float FastAddRotations(float,float);
extern char *part_spawn_streak_effect(void *,void *);
extern char *part_spawn_trailing_spark(void *,void *,unsigned int,unsigned int,int,int,float);
extern void part_l00_spawn_spark_pairs(Vector4 *,int);
extern unsigned long GetEffectTextureDescriptor(int);
extern void euler_to_matrix(void *,void *);
extern void draw_world_quad(void *,void *,int);
extern unsigned char D_001B8C80[];
extern void gfx_l00_init_default_block(char *);
extern void gfx_l00_init_default_block_2(char *);
typedef struct { char pad[0x20]; Vector4 position; } CollisionResult;
extern CollisionResult g_collision_result;
extern Vector4 g_camera_l00_position;
/* Throws a burst of sparks and puffs from the spot where the weapon hit something. */
void part_spawn_weapon_impact_sparks(char *owner)
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
        part_spawn_trailing_spark(&position,&velocity,0x4F007FFF,0x1FFFFFFF,math_random_int_range(10,20),1,20000);
    }
    if(FIELD(short,FIELD(char *,owner,0x68),0x78)==43) part_l00_spawn_spark_pairs(&g_collision_result.position,10);
}
