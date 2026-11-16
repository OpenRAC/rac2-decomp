#include "include_asm.h"
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
extern void gfx_l00_init_default_block_2(char *);
extern void part_l00_draw_camera_facing_flash(void *,Vector4 *);
extern void part_l00_draw_camera_facing_flash_2(void *,Vector4 *);
extern void moby_transform_joint_to_world(char *,int,char *);
extern int func_001163B0(void);
extern int math_fast_float_d(int *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float fast_vec_dist(void *,void *);
extern void surface_grid_build_control(void *);
extern void surface_grid_update_wave_tables(void *);
extern void surface_grid_update_heights(void *);
extern void surface_grid_update(void *);
extern void surface_grid_spawn_effect(void *);
extern void surface_grid_draw(void *);
extern void gfx_add_draw_callback_second(void (*)(void *),void *);
extern void moby_set_state(unsigned char *,unsigned char,int);
extern int flag_set_first_pending(unsigned char *);
extern float math_step_value_toward_target(float *,float *,float,float,float,float);
typedef struct { float x,y,a,b; float pad[4]; } Spark;
extern Spark g_rise_fall_sparks[];
/* Runs the five-step cycle that makes the object rise, hold, fall and rest, then redraws it. */
void rise_fall_moby_update(unsigned char *object)
{
    char *work=FIELD(char *,object,0x68);
    int i,ticks;
    switch(object[0x20]) {
    case 0:
        if(FIELD(int,work,0x1C)<=0)FIELD(int,work,0x1C)=20;
        ticks=FIELD(int,work,0x1C);
        FIELD(int,work,4)=0;
        FIELD(float,work,0x14)=(FIELD(float,work,0x18)+FIELD(float,work,0x18))/(float)ticks;
        FIELD(float,work,0)=FIELD(float,work,0x18)*4/(float)(ticks*ticks);
        surface_grid_build_control(object);
        FIELD(float,work,0x30)=1/FIELD(float,work,0x30);
        FIELD(int,work,0x8C)=FIELD(int,work,0x84);FIELD(int,work,0x98)=-1;
        if(!FIELD(int,work,0x40)) {
            object[0x30]=255;
            for(i=0;i<64;++i) {
                g_rise_fall_sparks[i].a=math_random_float_range(0.5f,2);
                g_rise_fall_sparks[i].b=math_random_float_range(0.002f,0.006f);
            }
        }
        moby_set_state(object,1,-1);return;
    case 1:
        if(flag_set_first_pending(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,2,-1);
        math_step_value_toward_target((float *)(work+4),(float *)(work+8),FIELD(float,work,0x18),FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 2:
        if(flag_set_first_pending(object)){FIELD(int,work,0x20)=FIELD(int,work,12);FIELD(float,work,4)=FIELD(float,work,0x18);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,3,-1);
        break;
    case 3:
        if(flag_set_first_pending(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,4,-1);
        math_step_value_toward_target((float *)(work+4),(float *)(work+8),0,FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 4:
        if(flag_set_first_pending(object)){FIELD(int,work,4)=0;FIELD(int,work,0x20)=FIELD(int,work,16);}
        if(math_fast_float_d((int *)(work+0x20)))moby_set_state(object,1,-1);
        break;
    case 5:break;
    default:break;
    }
    if(!FIELD(int,work,0x40))surface_grid_update_wave_tables(object);
    surface_grid_update_heights(object);surface_grid_update(object);surface_grid_spawn_effect(object);
    gfx_add_draw_callback_second(surface_grid_draw,object);
}
