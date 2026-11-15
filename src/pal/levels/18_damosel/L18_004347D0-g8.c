#include "include_asm.h"

#include "common.h"
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern float FastVecLength(void *);
extern float math_random_float_range(float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void vec_add_random_offset(void *,float);
extern int math_random_int_below(int);
extern void *enemy_spawn_record(void *,void *,void *,int,int);
extern float D_L18_001B1460 __attribute__((sda));
extern short D_L18_001B14E8 __attribute__((sda));
extern short D_L18_001B14B8 __attribute__((sda));
extern float D_L18_001B1510 __attribute__((sda));
extern float D_L18_001B1514 __attribute__((sda));
extern float D_L18_001B151C __attribute__((sda));
extern int D_L18_001B1518 __attribute__((sda));
extern float D_L18_001B14A0 __attribute__((sda));
extern float D_L18_001B14A4 __attribute__((sda));
extern float D_L18_001B14AC __attribute__((sda));
extern int D_L18_001B14A8 __attribute__((sda));
extern u8 D_L18_001B14F8[16] __attribute__((sda));
extern u8 D_L18_001B14C8[16] __attribute__((sda));

void func_PAL_L18_004347D0(u8 *a,void *offset) {
 float direction[4],velocity[4],position[4],drift[4];
 float speed;
 int i;
 matrix_mul_vec3(position,offset,a+0xc0);
 FastVecAdd(position,a+0x10,position);
 qcopy(direction,a+0xc0);
 speed=FastVecLength(*(u8 **)(a+0x68)+0x80);
 { float r=math_random_float_range(0.0f,0.1f); speed*=5.0f; speed/=D_L18_001B1460*0.020000001f; speed+=r; }
 if(speed>1.0f) speed=1.0f;
 else if(speed<0.0f) speed=0.0f;
 vec_scale_to_length(drift,direction,-D_L18_001B14E8*0.0002f);
 for(i=0;i<D_L18_001B1518;i++) {
  vec_scale_to_length(velocity,direction,-((D_L18_001B1510+math_random_float_range(0.0f,speed*D_L18_001B1514))*0.020000001f));
  vec_add_random_offset(position,D_L18_001B151C);
  FastVecAdd(position,position,drift);
  enemy_spawn_record(position,velocity,D_L18_001B14F8,math_random_int_below(2),1);
 }
 vec_scale_to_length(drift,direction,-D_L18_001B14B8*0.0002f);
 for(i=0;(float)i<speed*(float)D_L18_001B14A8+2.0f;i++) {
  vec_scale_to_length(velocity,direction,-((D_L18_001B14A0+math_random_float_range(0.0f,speed*D_L18_001B14A4))*0.020000001f));
  vec_add_random_offset(position,D_L18_001B14AC);
  FastVecAdd(position,position,drift);
  enemy_spawn_record(position,velocity,D_L18_001B14C8,math_random_int_below(2),1);
 }
}
