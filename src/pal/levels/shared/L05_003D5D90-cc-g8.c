#include "names.h"
/* func_PAL_L05_003D5D90, the PAL copy of func_L05_003D2048: the same C, where rename func_L05_003D33E8 becomes func_PAL_L05_003D7130; rename-macro func_002BDCE8 becomes func_PAL_002BE9A8; rename-macro func_002BCB00 becomes func_PAL_002BD790; rename func_003067D8 becomes func_00282E48; rename func_003719A8 becomes func_002E5DA0; rename func_003062A0 becomes func_00282948; rename func_003068F8 becomes func_00282F20; rename func_00306630 becomes func_00282CC0; rename func_00332B50 becomes func_002A7878; rename func_00332AF8 becomes func_002A7820; rename func_00347040 becomes func_PAL_002BE9A8; rename func_00332AB8 becomes func_002A77E0; .... */
#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef union { BurstQuad q; float f[4]; } BurstVector;
extern void func_PAL_L05_003D7130(char *);
extern float fast_vec_dist(void *,void *);
extern int snd_play_from_class_bank(int,int,void *,int);
extern int math_fast_float_d(void *);
extern void vec_scale_to_length(void *,void *,float),FastVecAdd(void *,void *,void *);
extern float math_random_float_range(float,float),math_random_angle(void);
extern int math_random_int_range(int,int),math_random_int_below(int);
extern char *func_PAL_002BE9A8(void *,int,float,void *,int,int,float,float,float);
extern char *part_spawn_streak_effect(void *,void *);
extern void vec_build_spherical_offset(void *,float,float,float);
extern int gfx_swap_packed_color_channels(int,int);
extern char *func_PAL_002BD790(void *,void *,int,int,int,int,int,int,int,float);
extern void gfx_add_draw_callback_third(void *,void *),DrawAnimatedMeshAndGlowEffect(void);
extern int D_L05_001B3000[] __attribute__((sda));
extern char D_L05_001B96C0[],D_L05_001B98F0[],D_L05_0024D020[];
extern float D_L05_001AFC94 __attribute__((sda));
void func_PAL_L05_003D5D90(char *obj)
{
 BurstVector v,small,offset,pos,velocity;
 char *s=*(char **)(obj+0x68);
 int *timers=D_L05_001B3000;
 int color1,color2,duration;
 float scale,a,b;
 if (*(unsigned char *)(obj+0x20)==0) {
  func_PAL_L05_003D7130(obj);*(unsigned char *)(obj+0x20)=1;
  timers[*(int *)s]=4;
  if(fast_vec_dist(obj+0x10,D_L05_001B96C0)>200.0f) *(float *)(s+4)=4;
  else if(fast_vec_dist(obj+0x10,D_L05_001B96C0)>100.0f) *(float *)(s+4)=2;
  else if(fast_vec_dist(obj+0x10,D_L05_001B96C0)>25.0f) *(float *)(s+4)=1;
  else if(fast_vec_dist(obj+0x10,D_L05_001B96C0)>0.0f) *(float *)(s+4)=0.5f;
  snd_play_from_class_bank(10,0,obj,0xFBF);
 }
 if(!math_fast_float_d(&D_L05_001B3000[*(int *)s]) && !*(int *)(s+8)) {
  int i;
  void *smallp=&small,*posp=&pos;
  for(i=0;i<4;i++) {
   int j;
   char *effect,*record;
   float lim;
   scale=D_L05_001AFC94*8.0f;
   qcopy(&v,D_L05_0024D020+*(int *)s*64+i*16);
   v.f[0]+=0.1f;
   vec_scale_to_length(smallp,D_L05_001B98F0,0.24000001f);
   vec_scale_to_length(&offset,D_L05_001B98F0,0.5f);
   FastVecAdd(&v,&v,&offset);
   scale*=3.0f;
   lim=10.0f;
   for(j=0;(float)j<(lim=10.0f);j++) {
    pos.f[0]=v.f[0];pos.f[1]=v.f[1];pos.f[2]=v.f[2];
    velocity.f[0]=(math_random_float_range(0,0.1f)+ -0.05f)**(float *)(s+4);
    velocity.f[1]=(math_random_float_range(0,0.1f)+ -0.05f)**(float *)(s+4);
    velocity.f[2]=(math_random_float_range(0,0.1f)+ -0.05f)**(float *)(s+4);
    duration=math_random_int_range(-3,3);
    effect=func_PAL_002BE9A8(posp,duration,0,&velocity,0x7F204080,0,1,1.02f,scale*210000.0f);
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
  if(!*(int *)(s+8)) {
   int k;
   for(k=0;k<10;k++) {
    char *effect,*record;
    float lim;
    v.f[0]=math_random_float_range(-0.3f,0.3f)**(float *)(s+4);
    v.f[1]=math_random_float_range(-0.3f,0.3f)**(float *)(s+4);
    v.f[2]=math_random_float_range(-0.3f,0.3f)**(float *)(s+4);v.f[3]=0;
    effect=part_spawn_streak_effect(obj+0x10,&v);
    if(effect) {
     record=effect+0x30;
     vec_scale_to_length(&v,&v,1.0f);FastVecAdd(effect+0x10,obj+0x10,&v);
     qcopy(effect+0x20,obj+0x10);
     *(float *)(record+0xC)=1;*(float *)(effect+0x1C)=0.05f;*(float *)(effect+0x2C)=0.25f;
    }
   }
   for(k=0;k<10;k++) {
    char *effect;
    a=math_random_angle();b=math_random_angle();
    vec_build_spherical_offset(&v,math_random_float_range(7,10.5f)*(*(float *)(s+4)*0.020000001f),b,a);
    v.f[2]+=0.060000002f;
    color1=gfx_swap_packed_color_channels(0x4F007FFF,0);color2=gfx_swap_packed_color_channels(0x1F00007F,0);
    duration=math_random_int_range(50,100);
    effect=func_PAL_002BD790(obj+0x10,&v,color1,color2,duration,1,-1,-1,0,40000.0f);
    if(effect) *(int *)(effect+0x2C)=0;
   }
  }
 }
 gfx_add_draw_callback_third(DrawAnimatedMeshAndGlowEffect,obj);
}
