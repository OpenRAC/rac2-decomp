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
extern char *part_spawn_timed_effect_between_points_pal(void *,void *);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern void gorn_part_spawn_spark_burst_pal(void *,int,int);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void hero_apply_damage_pal(float);

/* Updates the scrolling grid backdrop: on a timer spawns effects around the tracked object, and hurts the hero with sparks and a sound when the object is at either edge of its range. */
void gorn_backdrop_grid_update_pal(char *self) {
 char *state=*(char **)(self+0x68);
 char *target_moby,*basis,*pos,*axis;
 float start_pos[4],end_pos[4],hit_pos[4];
 float distance;
 if(!g_backdrop_grid_enabled) return;
 DrawScrollingGridLayers(self,0);
 if(!math_fast_float_d(state+0xC)) return;
 target_moby=g_moby_base+(*(int *)state<<8);
 basis=target_moby+0xC0;
 qcopy(start_pos,basis);
 axis=target_moby+0xE0;
 pos=target_moby+0x10;
 distance=800.0f;
 math_apply_axis_rotation_to_quat(start_pos,start_pos,axis,math_random_float_range(-20.0f,20.0f)*0.01745329424738884f);
 vec_scale_to_length(start_pos,start_pos,distance);
 FastVecAdd(start_pos,start_pos,pos);
 start_pos[2]=distance;
 qcopy(end_pos,start_pos);
 end_pos[2]=400.0f;
 part_spawn_timed_effect_between_points_pal(start_pos,end_pos);
 if(math_random_int_below(2)) part_spawn_timed_effect_between_points_pal(start_pos,end_pos);
 *(int *)(state+0xC)=((s32)(FloatToInt(math_random_float_range(90.0f,350.0f))) * 5 + 2) / 6;
 if(*(float *)(target_moby+0x18)>=565.0f) {
  qcopy(start_pos,pos); qcopy(end_pos,start_pos);
  start_pos[2]=distance;
  end_pos[2]=*(float *)(target_moby+0x18)-100.0f;
  part_spawn_timed_effect_between_points_pal(start_pos,end_pos);
  qcopy(hit_pos,basis);
  vec_scale_to_length(hit_pos,hit_pos,10.0f);
  FastVecAdd(hit_pos,pos,hit_pos);
  hit_pos[2]-=1.25f;
  gorn_part_spawn_spark_burst_pal(hit_pos,40,0);
  snd_play_from_class_bank(16,0,self,0xFBF);
  hero_apply_damage_pal(40.0f);
 }
 if(*(float *)(target_moby+0x18)<=415.0f) {
  qcopy(hit_pos,basis);
  vec_scale_to_length(hit_pos,hit_pos,10.0f);
  FastVecAdd(hit_pos,pos,hit_pos);
  hit_pos[2]-=1.25f;
  gorn_part_spawn_spark_burst_pal(hit_pos,40,0);
  snd_play_from_class_bank(16,0,self,0xFBF);
  hero_apply_damage_pal(40.0f);
 }
}
