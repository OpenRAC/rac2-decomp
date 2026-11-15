#include "common.h"
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_00282DF0(void *);
extern float func_002A7878(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_002ACB48(void *,float);
extern int func_002A77E0(int);
extern void *func_L02_003449D8(void *,void *,void *,int,int);
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
/* Sprays two kinds of exhaust particles from a spot on the object; the faster it
   moves, the more it makes. */
void func_L18_0042F7B8(u8 *moby,void *offset) {
 float direction[4],velocity[4],position[4],drift[4];
 float speed;
 int i;
 matrix_mul_vec3(position,offset,moby+0xc0);
 FastVecAdd(position,moby+0x10,position);
 qcopy(direction,moby+0xc0);
 speed=FastVecLength(*(u8 **)(moby+0x68)+0x80);
 { float r=RandomFloatRange(0.0f,0.1f); speed*=5.0f; speed/=D_L18_001B1460*0.0166666675f; speed+=r; }
 if(speed>1.0f) speed=1.0f;
 else if(speed<0.0f) speed=0.0f;
 vec_scale_to_length(drift,direction,-D_L18_001B14E8*0.0002f);
 for(i=0;i<D_L18_001B1518;i++) {
  vec_scale_to_length(velocity,direction,-((D_L18_001B1510+RandomFloatRange(0.0f,speed*D_L18_001B1514))*0.0166666675f));
  AddRandomOffsetToVector(position,D_L18_001B151C);
  FastVecAdd(position,position,drift);
  SpawnEnemyRecord(position,velocity,D_L18_001B14F8,RandomIntBelow(2),1);
 }
 vec_scale_to_length(drift,direction,-D_L18_001B14B8*0.0002f);
 for(i=0;(float)i<speed*(float)D_L18_001B14A8+2.0f;i++) {
  vec_scale_to_length(velocity,direction,-((D_L18_001B14A0+RandomFloatRange(0.0f,speed*D_L18_001B14A4))*0.0166666675f));
  AddRandomOffsetToVector(position,D_L18_001B14AC);
  FastVecAdd(position,position,drift);
  SpawnEnemyRecord(position,velocity,D_L18_001B14C8,RandomIntBelow(2),1);
 }
}
