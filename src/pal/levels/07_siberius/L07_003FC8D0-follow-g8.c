/* func_PAL_L07_003FC8D0, the PAL copy of func_L07_003F80B8: the same C, where func_L07_003F8430
   becomes func_PAL_L07_003FCC48; 0.0034906589426100254f becomes 0.005026549f; 0.20943955f becomes
   0.25132746f; 0.00027777778f becomes 0.00040000002f; 1.0f / 60.0f becomes 0.020000001f;
   0.0000048481375f becomes 6.981318e - 06f; 0.000290888245f becomes 0.0003490659f. */
#include "include_asm.h"

#include "common.h"

extern void func_PAL_L07_003FCC48(u8 *);
extern void func_2E47D0(void *,void *,void *);
extern void func_2E4310(void *,void *,void *);
extern u8 *func_316FD8(void *);
extern void func_316638(void *,f32);
extern f32 func_2E5318(f32,f32);
extern f32 func_2E49C8(f32,f32);
extern void func_3144F0(void *,void *,f32,f32,f32,f32,s32);
extern void func_2E4340(void *,void *,void *);
extern f32 func_2E4458(void *);
extern f32 func_2E4248(f32);
extern void func_2E45F0(void *,void *,f32);
extern f32 func_2E4418(void *,void *);
extern f32 func_314038(f32 *,f32 *,f32,f32,f32,f32);
typedef struct {u8 pad[0x80];f32 pos[4];} Player;
extern Player D_00189E20;
extern f32 D_L07_001B1070 __attribute__((sda));
extern f32 D_L07_001B1074 __attribute__((sda));
extern f32 D_L07_001B1078 __attribute__((sda));
extern f32 D_L07_001B107C __attribute__((sda));
extern f32 D_L07_001B1080 __attribute__((sda));
extern f32 D_L07_001B1084 __attribute__((sda));
extern f32 D_L07_001B1088 __attribute__((sda));
extern f32 D_L07_001B108C __attribute__((sda));
void func_PAL_L07_003FC8D0(u8 *obj,f32 limit)
{
 f32 target[4],delta[4],move[4],accel[4];
 u8 *p=*(u8 **)(obj+0x68);
 u8 *other;
 f32 rate,speed,len,amount,angle,bank,turnRate,turnSpeed;
 f32 *yaw;
 func_PAL_L07_003FCC48(obj);
 if(!obj[0x95]) {
  func_2E47D0(target,p+0x3e0,*(u8 **)(p+0x418)+0xc0);
  func_2E4310(target,target,*(u8 **)(p+0x418)+0x10);
  other=func_316FD8(*(u8 **)(p+0x418));
  if(limit>=0.0f) {
   qcopy(delta,other+0x10);
   func_316638(delta,limit);
   func_2E4310(obj+0x10,obj+0x10,delta);
  } else func_2E4310(obj+0x10,obj+0x10,other+0x10);
  *(f32 *)(obj+0xf8)=func_2E5318(*(f32 *)(*(u8 **)(p+0x418)+0xf8),3.1415927f);
 } else {
  qcopy(target,p+0x3e0);
  yaw=(f32 *)(obj+0xf8);
  angle=func_2E49C8(D_00189E20.pos[0]-*(f32 *)(obj+0x10),D_00189E20.pos[1]-*(f32 *)(obj+0x14));
  func_3144F0(yaw,p+0x424,angle,0.005026549f,0.005026549f,0.25132746f,0);
 }
 func_2E4340(delta,target,obj+0x10);
 rate=(obj[0x95]?D_L07_001B1078:D_L07_001B1070)*0.00040000002f;
 speed=(obj[0x95]?D_L07_001B107C:D_L07_001B1074)*(0.020000001f);
 len=func_2E4458(delta);
 amount=func_2E4248(len*rate*0.5f);
 if(limit>=0.0f && limit<speed) speed=limit;
 if(speed<amount) amount=speed;
 if(amount<len) func_2E45F0(move,delta,amount);
 else qcopy(move,delta);
 func_2E4340(accel,move,p+0x3f0);
 func_316638(accel,rate);
 func_2E4310(p+0x3f0,p+0x3f0,accel);
 func_2E4310(obj+0x10,obj+0x10,p+0x3f0);
 angle=func_2E4418(obj+0xd0,p+0x3f0)*D_L07_001B1080;
 if(angle>1.5707965f) angle=1.5707965f;
 else if(angle< -1.5707965f) angle= -1.5707965f;
 turnRate=D_L07_001B1084;
 turnSpeed=D_L07_001B1088;
 turnRate*=6.981318e-06f;
 turnSpeed*=0.0003490659f;
 func_314038((f32 *)(obj+0xf0),(f32 *)(p+0x428),angle,turnRate,turnRate,turnSpeed);
 bank=*(f32 *)(obj+0xf0)*D_L07_001B108C;
 if(obj[0x43]>=8) *(f32 *)(p+0x2c0)=bank;
 else *(f32 *)(p+0x2c4)=bank;
}
