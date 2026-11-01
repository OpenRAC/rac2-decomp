#include "include_asm.h"

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

void func_PAL_L18_004347D0(u8 *a,void *offset) {
 float direction[4],velocity[4],position[4],drift[4];
 float speed;
 int i;
 func_00283098(position,offset,a+0xc0);
 func_00282CC0(position,a+0x10,position);
 qcopy(direction,a+0xc0);
 speed=func_00282DF0(*(u8 **)(a+0x68)+0x80);
 { float r=func_002A7878(0.0f,0.1f); speed*=5.0f; speed/=D_L18_001B1460*0.020000001f; speed+=r; }
 if(speed>1.0f) speed=1.0f;
 else if(speed<0.0f) speed=0.0f;
 func_00282F20(drift,direction,-D_L18_001B14E8*0.0002f);
 for(i=0;i<D_L18_001B1518;i++) {
  func_00282F20(velocity,direction,-((D_L18_001B1510+func_002A7878(0.0f,speed*D_L18_001B1514))*0.020000001f));
  func_002ACB48(position,D_L18_001B151C);
  func_00282CC0(position,position,drift);
  func_L02_003449D8(position,velocity,D_L18_001B14F8,func_002A77E0(2),1);
 }
 func_00282F20(drift,direction,-D_L18_001B14B8*0.0002f);
 for(i=0;(float)i<speed*(float)D_L18_001B14A8+2.0f;i++) {
  func_00282F20(velocity,direction,-((D_L18_001B14A0+func_002A7878(0.0f,speed*D_L18_001B14A4))*0.020000001f));
  func_002ACB48(position,D_L18_001B14AC);
  func_00282CC0(position,position,drift);
  func_L02_003449D8(position,velocity,D_L18_001B14C8,func_002A77E0(2),1);
 }
}
