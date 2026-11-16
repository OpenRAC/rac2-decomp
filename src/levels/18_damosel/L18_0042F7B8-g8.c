#include "common.h"
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern float FastVecLength(void *);
extern float math_random_float_range(float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void vec_add_random_offset(void *,float);
extern int math_random_int_below(int);
extern void *enemy_spawn_record(void *,void *,void *,int,int);
extern float g_leader_exhaust_speed __attribute__((sda));
extern short g_exhaust_drift_scale_alt __attribute__((sda));
extern short g_exhaust_drift_scale __attribute__((sda));
extern float g_exhaust_alt_speed_base __attribute__((sda));
extern float g_exhaust_alt_speed_random __attribute__((sda));
extern float g_exhaust_alt_jitter __attribute__((sda));
extern int g_exhaust_alt_count __attribute__((sda));
extern float g_exhaust_speed_base __attribute__((sda));
extern float g_exhaust_speed_random __attribute__((sda));
extern float g_exhaust_position_jitter __attribute__((sda));
extern int g_exhaust_count_scale __attribute__((sda));
extern u8 g_exhaust_particle_settings_alt[16] __attribute__((sda));
extern u8 g_exhaust_particle_settings[16] __attribute__((sda));
/* Sprays two kinds of exhaust particles from a spot on the object; the faster it
   moves, the more it makes. */
void part_l18_spawn_exhaust(u8 *moby,void *offset) {
 float direction[4],velocity[4],position[4],drift[4];
 float speed;
 int i;
 matrix_mul_vec3(position,offset,moby+0xc0);
 FastVecAdd(position,moby+0x10,position);
 qcopy(direction,moby+0xc0);
 speed=FastVecLength(*(u8 **)(moby+0x68)+0x80);
 { float r=math_random_float_range(0.0f,0.1f); speed*=5.0f; speed/=g_leader_exhaust_speed*0.0166666675f; speed+=r; }
 if(speed>1.0f) speed=1.0f;
 else if(speed<0.0f) speed=0.0f;
 vec_scale_to_length(drift,direction,-g_exhaust_drift_scale_alt*0.0002f);
 for(i=0;i<g_exhaust_alt_count;i++) {
  vec_scale_to_length(velocity,direction,-((g_exhaust_alt_speed_base+math_random_float_range(0.0f,speed*g_exhaust_alt_speed_random))*0.0166666675f));
  vec_add_random_offset(position,g_exhaust_alt_jitter);
  FastVecAdd(position,position,drift);
  enemy_spawn_record(position,velocity,g_exhaust_particle_settings_alt,math_random_int_below(2),1);
 }
 vec_scale_to_length(drift,direction,-g_exhaust_drift_scale*0.0002f);
 for(i=0;(float)i<speed*(float)g_exhaust_count_scale+2.0f;i++) {
  vec_scale_to_length(velocity,direction,-((g_exhaust_speed_base+math_random_float_range(0.0f,speed*g_exhaust_speed_random))*0.0166666675f));
  vec_add_random_offset(position,g_exhaust_position_jitter);
  FastVecAdd(position,position,drift);
  enemy_spawn_record(position,velocity,g_exhaust_particle_settings,math_random_int_below(2),1);
 }
}
