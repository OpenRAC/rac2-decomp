#include "include_asm.h"
/* Twin beam strips, the resident copy of func_L00_0038ADD0 (same body, its own point
   helpers and up vector). */
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
extern void matrix_mul_vec3(void *,void *,void *);
extern void transform_vector(void *,void *,void *);
extern int math_random_int_range(int,int);
extern unsigned long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *,void *,int);
extern void gfx_l00_init_default_block(char *);
extern void gfx_init_effect_packet_2(char *);
extern void part_l00_draw_camera_facing_flash(void *,Vector4 *);
extern void gfx_draw_facing_glow_2(void *,Vector4 *);
extern void moby_transform_joint_to_world(char *,int,char *);
extern int func_001163B0(void);
extern int math_fast_float_d(int *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float fast_vec_dist(void *,void *);
extern Vector4 g_camera_eye_state;
typedef struct {
    Vector4 point[4];
    unsigned int color[4];
    float uv[8];
    unsigned long tag, tex, alpha, test;
} Beam;
/* Draws a flickering energy beam as two glowing strips from the object to a random point in front of it. */
void gfx_draw_twin_beam_strips_2(char *object)
{
    Beam first,second;
    Vector4 basis[4],start,end,origin,nearSize,farSize;
    char *work=FIELD(char *,object,0x68);
    float width;
    moby_transform_joint_to_world(object,1,(char *)&origin);
    start.bits=origin.bits;
    vec_scale_to_length(&end,work+0x30,math_random_float_range(2,4));
    matrix_mul_vec3(&end,&end,object+0xC0);
    FastVecAdd(&end,&end,&origin);
    gfx_draw_facing_glow_2(object,&start);
    first.tex=GetEffectTextureDescriptor(23);
    first.tag=0;
    first.alpha=0xFF9000000260UL;
    first.color[0]=first.color[1]=0x7F103080;
    first.test=0x8000000048UL;
    first.color[2]=first.color[3]=0x103080;
    second.tex=GetEffectTextureDescriptor(23);
    nearSize.bits=0;
    farSize.bits=0;
    second.test=0x8000000048UL;
    second.tag=0;
    second.color[2]=second.color[3]=0x103080;
    second.color[0]=second.color[1]=0x3F103080;
    nearSize.f[3]=1;
    farSize.f[3]=1;
    second.alpha=0xFF9000000260UL;
    width=math_random_float_range(0.1f,0.3f);nearSize.f[2]=width;farSize.f[2]=width+width;
    gfx_init_effect_packet_2((char *)&first);gfx_init_effect_packet_2((char *)&second);
    if(!(func_001163B0()&1)) {
        first.uv[0]=0;first.uv[1]=0;first.uv[2]=0;first.uv[3]=1;
        first.uv[4]=1;first.uv[5]=0;first.uv[6]=1;first.uv[7]=1;
        second.uv[0]=0;second.uv[1]=0;second.uv[2]=0;second.uv[3]=1;
        second.uv[4]=1;second.uv[5]=0;second.uv[6]=1;second.uv[7]=1;
    } else {
        first.uv[0]=0;first.uv[1]=1;first.uv[2]=0;first.uv[3]=0;
        first.uv[4]=1;first.uv[5]=1;first.uv[6]=1;first.uv[7]=0;
        second.uv[0]=0;second.uv[1]=1;second.uv[2]=0;second.uv[3]=0;
        second.uv[4]=1;second.uv[5]=1;second.uv[6]=1;second.uv[7]=0;
    }
    FastVecSub(&basis[0],&end,&start);vec_scale_to_length(&basis[0],&basis[0],1);
    FastVecSub(&basis[1],&g_camera_eye_state,&start);FastVecCross(&basis[2],&basis[1],&basis[0]);
    vec_scale_to_length(&basis[2],&basis[2],1);FastVecCross(&basis[1],&basis[0],&basis[2]);
    basis[3].bits=start.bits;
    first.point[0].bits=nearSize.bits;second.point[0].bits=farSize.bits;
    FastVecScale(&first.point[1],&first,-1);FastVecScale(&second.point[1],&second,-1);
    transform_vector(&first,&first,basis);transform_vector(&first.point[1],&first.point[1],basis);
    transform_vector(&second,&second,basis);transform_vector(&second.point[1],&second.point[1],basis);
    basis[3].bits=end.bits; nearSize.f[2]*=0.15f;farSize.f[2]=nearSize.f[2]+nearSize.f[2];
    first.point[2].bits=nearSize.bits;second.point[2].bits=farSize.bits;
    FastVecScale(&first.point[3],&first.point[2],-1);FastVecScale(&second.point[3],&second.point[2],-1);
    transform_vector(&first.point[2],&first.point[2],basis);transform_vector(&first.point[3],&first.point[3],basis);
    transform_vector(&second.point[2],&second.point[2],basis);transform_vector(&second.point[3],&second.point[3],basis);
    draw_world_quad(&first,0,0);draw_world_quad(&second,0,0);
}
