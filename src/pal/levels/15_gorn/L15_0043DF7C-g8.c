#include "include_asm.h"

#include "common.h"
extern int g_backdrop_grid_enabled __attribute__((sda));
extern char *g_moby_base __attribute__((sda));
extern void DrawScrollingGridLayers(void *,int);
extern int math_fast_float_d(void *);
extern float math_random_float_range(float,float);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern char *func_PAL_L15_00437CD0(void *,void *);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern void gorn_part_spawn_spark_burst_pal(void *,int,int);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void hero_apply_damage_pal(float);

void func_PAL_L15_0043DF7C(char *self) {
 char *state=*(char **)(self+0x68);
 char *obj,*basis,*pos,*axis;
 float a[4],b[4],c[4];
 float distance;
 if(!g_backdrop_grid_enabled) return;
 DrawScrollingGridLayers(self,0);
 if(!math_fast_float_d(state+0xC)) return;
 obj=g_moby_base+(*(int *)state<<8);
 basis=obj+0xC0;
 qcopy(a,basis);
 axis=obj+0xE0;
 pos=obj+0x10;
 distance=800.0f;
 math_apply_axis_rotation_to_quat(a,a,axis,math_random_float_range(-20.0f,20.0f)*0.01745329424738884f);
 vec_scale_to_length(a,a,distance);
 FastVecAdd(a,a,pos);
 a[2]=distance;
 qcopy(b,a);
 b[2]=400.0f;
 func_PAL_L15_00437CD0(a,b);
 if(math_random_int_below(2)) func_PAL_L15_00437CD0(a,b);
 *(int *)(state+0xC)=((s32)(FloatToInt(math_random_float_range(90.0f,350.0f))) * 5 + 2) / 6;
 if(*(float *)(obj+0x18)>=565.0f) {
  qcopy(a,pos); qcopy(b,a);
  a[2]=distance;
  b[2]=*(float *)(obj+0x18)-100.0f;
  func_PAL_L15_00437CD0(a,b);
  qcopy(c,basis);
  vec_scale_to_length(c,c,10.0f);
  FastVecAdd(c,pos,c);
  c[2]-=1.25f;
  gorn_part_spawn_spark_burst_pal(c,40,0);
  snd_play_from_class_bank(16,0,self,0xFBF);
  hero_apply_damage_pal(40.0f);
 }
 if(*(float *)(obj+0x18)<=415.0f) {
  qcopy(c,basis);
  vec_scale_to_length(c,c,10.0f);
  FastVecAdd(c,pos,c);
  c[2]-=1.25f;
  gorn_part_spawn_spark_burst_pal(c,40,0);
  snd_play_from_class_bank(16,0,self,0xFBF);
  hero_apply_damage_pal(40.0f);
 }
}
