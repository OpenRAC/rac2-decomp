#include "names.h"
/* func_PAL_L05_003D5D90, the PAL copy of func_L05_003D2048: the same C, where rename func_L05_003D33E8 becomes func_PAL_L05_003D7130; rename-macro func_002BDCE8 becomes func_PAL_002BE9A8; rename-macro func_002BCB00 becomes func_PAL_002BD790; rename func_003067D8 becomes func_00282E48; rename func_003719A8 becomes func_002E5DA0; rename func_003062A0 becomes func_00282948; rename func_003068F8 becomes func_00282F20; rename func_00306630 becomes func_00282CC0; rename func_00332B50 becomes func_002A7878; rename func_00332AF8 becomes func_002A7820; rename func_00347040 becomes func_PAL_002BE9A8; rename func_00332AB8 becomes func_002A77E0; .... */
#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef union { BurstQuad q; float f[4]; } BurstVector;
extern void part_reset_emitter_slot_effect_pal(char *);
extern float fast_vec_dist(void *,void *);
extern int snd_play_from_class_bank(int,int,void *,int);
extern int math_fast_float_d(void *);
extern void vec_scale_to_length(void *,void *,float),FastVecAdd(void *,void *,void *);
extern float math_random_float_range(float,float),math_random_angle(void);
extern int math_random_int_range(int,int),math_random_int_below(int);
extern char *part_spawn_spinning_spark_pal(void *,int,float,void *,int,int,float,float,float);
extern char *part_spawn_streak_effect(void *,void *);
extern void vec_build_spherical_offset(void *,float,float,float);
extern int gfx_swap_packed_color_channels(int,int);
extern char *part_spawn_spark_pal(void *,void *,int,int,int,int,int,int,int,float);
extern void gfx_add_draw_callback_third(void *,void *),DrawAnimatedMeshAndGlowEffect(void);
extern int g_effect_timers[] __attribute__((sda));
extern char g_origin_vec[],g_unit_dir_vec[],g_emitter_group_positions[];
extern float g_effect_scale_base __attribute__((sda));
/* Updates the glow burst: on its first frame it starts the emitters and picks a strength from the distance to the hero, then throws sparks and streaks and queues the draw callback (PAL: 50 Hz timings). */
void glow_burst_update_pal(char *obj)
{
 BurstVector base,step,offset,pos,velocity;
 char *state=*(char **)(obj+0x68);
 int *timers=g_effect_timers;
 int color1,color2,duration;
 float scale,angle_a,angle_b;
 if (*(unsigned char *)(obj+0x20)==0) {
  part_reset_emitter_slot_effect_pal(obj);*(unsigned char *)(obj+0x20)=1;
  timers[*(int *)state]=4;
  if(fast_vec_dist(obj+0x10,g_origin_vec)>200.0f) *(float *)(state+4)=4;
  else if(fast_vec_dist(obj+0x10,g_origin_vec)>100.0f) *(float *)(state+4)=2;
  else if(fast_vec_dist(obj+0x10,g_origin_vec)>25.0f) *(float *)(state+4)=1;
  else if(fast_vec_dist(obj+0x10,g_origin_vec)>0.0f) *(float *)(state+4)=0.5f;
  snd_play_from_class_bank(10,0,obj,0xFBF);
 }
 if(!math_fast_float_d(&g_effect_timers[*(int *)state]) && !*(int *)(state+8)) {
  int i;
  void *step_ptr=&step,*pos_ptr=&pos;
  for(i=0;i<4;i++) {
   int j;
   char *effect,*record;
   float lim;
   scale=g_effect_scale_base*8.0f;
   qcopy(&base,g_emitter_group_positions+*(int *)state*64+i*16);
   base.f[0]+=0.1f;
   vec_scale_to_length(step_ptr,g_unit_dir_vec,0.24000001f);
   vec_scale_to_length(&offset,g_unit_dir_vec,0.5f);
   FastVecAdd(&base,&base,&offset);
   scale*=3.0f;
   lim=10.0f;
   for(j=0;(float)j<(lim=10.0f);j++) {
    pos.f[0]=base.f[0];pos.f[1]=base.f[1];pos.f[2]=base.f[2];
    velocity.f[0]=(math_random_float_range(0,0.1f)+ -0.05f)**(float *)(state+4);
    velocity.f[1]=(math_random_float_range(0,0.1f)+ -0.05f)**(float *)(state+4);
    velocity.f[2]=(math_random_float_range(0,0.1f)+ -0.05f)**(float *)(state+4);
    duration=math_random_int_range(-3,3);
    effect=part_spawn_spinning_spark_pal(pos_ptr,duration,0,&velocity,0x7F204080,0,1,1.02f,scale*210000.0f);
    if(effect) {
     record=effect+0x20;
     *(unsigned short *)(effect+0xA)=83;
     *(unsigned char *)(effect+8)=math_random_int_below(255);
     *(unsigned char *)(effect+3)=0x48;
     *(int *)(record+4)=2;*(unsigned char *)(record+0xA)=127;
     *(unsigned char *)(record+0xB)=*(unsigned char *)(effect+0xA);
    }
   }
  }
  if(!*(int *)(state+8)) {
   int k;
   for(k=0;k<10;k++) {
    char *effect,*record;
    float lim;
    base.f[0]=math_random_float_range(-0.3f,0.3f)**(float *)(state+4);
    base.f[1]=math_random_float_range(-0.3f,0.3f)**(float *)(state+4);
    base.f[2]=math_random_float_range(-0.3f,0.3f)**(float *)(state+4);base.f[3]=0;
    effect=part_spawn_streak_effect(obj+0x10,&base);
    if(effect) {
     record=effect+0x30;
     vec_scale_to_length(&base,&base,1.0f);FastVecAdd(effect+0x10,obj+0x10,&base);
     qcopy(effect+0x20,obj+0x10);
     *(float *)(record+0xC)=1;*(float *)(effect+0x1C)=0.05f;*(float *)(effect+0x2C)=0.25f;
    }
   }
   for(k=0;k<10;k++) {
    char *effect;
    angle_a=math_random_angle();angle_b=math_random_angle();
    vec_build_spherical_offset(&base,math_random_float_range(7,10.5f)*(*(float *)(state+4)*0.020000001f),angle_b,angle_a);
    base.f[2]+=0.060000002f;
    color1=gfx_swap_packed_color_channels(0x4F007FFF,0);color2=gfx_swap_packed_color_channels(0x1F00007F,0);
    duration=math_random_int_range(50,100);
    effect=part_spawn_spark_pal(obj+0x10,&base,color1,color2,duration,1,-1,-1,0,40000.0f);
    if(effect) *(int *)(effect+0x2C)=0;
   }
  }
 }
 gfx_add_draw_callback_third(DrawAnimatedMeshAndGlowEffect,obj);
}
