#include "include_asm.h"

#include "common.h"

extern void flyer_steer(u8 *);
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
/* Level-07 copy of func_002AA548, which returns float (result unused here). */
extern f32 func_314038(f32 *,f32 *,f32,f32,f32,f32);
typedef struct {u8 pad[0x80];f32 pos[4];} Player;
extern Player g_hero_state;
extern f32 g_boss_rate_normal __attribute__((sda));
extern f32 g_boss_speed_normal __attribute__((sda));
extern f32 g_boss_rate_alt __attribute__((sda));
extern f32 g_boss_speed_alt __attribute__((sda));
extern f32 g_boss_angle_scale __attribute__((sda));
extern f32 g_boss_l07_turn_rate __attribute__((sda));
extern f32 g_boss_turn_speed __attribute__((sda));
extern f32 g_boss_bank_scale __attribute__((sda));
/* Moves the boss toward its target point, either riding its platform or facing the player, with limited speed. It also tilts the boss as it moves. */
void boss_move_toward_target(u8 *obj,f32 limit)
{
 f32 target[4],delta[4],move[4],accel[4];
 u8 *vars=*(u8 **)(obj+0x68);
 u8 *platform_root;
 f32 rate,speed,distance,step_length,angle,bank,turnRate,turnSpeed;
 f32 *yaw;
 flyer_steer(obj);
 if(!obj[0x95]) {
  func_2E47D0(target,vars+0x3e0,*(u8 **)(vars+0x418)+0xc0);
  func_2E4310(target,target,*(u8 **)(vars+0x418)+0x10);
  platform_root=func_316FD8(*(u8 **)(vars+0x418));
  if(limit>=0.0f) {
   qcopy(delta,platform_root+0x10);
   func_316638(delta,limit);
   func_2E4310(obj+0x10,obj+0x10,delta);
  } else func_2E4310(obj+0x10,obj+0x10,platform_root+0x10);
  *(f32 *)(obj+0xf8)=func_2E5318(*(f32 *)(*(u8 **)(vars+0x418)+0xf8),3.1415927f);
 } else {
  qcopy(target,vars+0x3e0);
  yaw=(f32 *)(obj+0xf8);
  angle=func_2E49C8(g_hero_state.pos[0]-*(f32 *)(obj+0x10),g_hero_state.pos[1]-*(f32 *)(obj+0x14));
  func_3144F0(yaw,vars+0x424,angle,0.0034906589426100254f,0.0034906589426100254f,0.20943955f,0);
 }
 func_2E4340(delta,target,obj+0x10);
 rate=(obj[0x95]?g_boss_rate_alt:g_boss_rate_normal)*0.00027777778f;
 speed=(obj[0x95]?g_boss_speed_alt:g_boss_speed_normal)*(1.0f/60.0f);
 distance=func_2E4458(delta);
 step_length=func_2E4248(distance*rate*0.5f);
 if(limit>=0.0f && limit<speed) speed=limit;
 if(speed<step_length) step_length=speed;
 if(step_length<distance) func_2E45F0(move,delta,step_length);
 else qcopy(move,delta);
 func_2E4340(accel,move,vars+0x3f0);
 func_316638(accel,rate);
 func_2E4310(vars+0x3f0,vars+0x3f0,accel);
 func_2E4310(obj+0x10,obj+0x10,vars+0x3f0);
 angle=func_2E4418(obj+0xd0,vars+0x3f0)*g_boss_angle_scale;
 if(angle>1.5707965f) angle=1.5707965f;
 else if(angle< -1.5707965f) angle= -1.5707965f;
 turnRate=g_boss_l07_turn_rate;
 turnSpeed=g_boss_turn_speed;
 turnRate*=0.0000048481375f;
 turnSpeed*=0.000290888245f;
 func_314038((f32 *)(obj+0xf0),(f32 *)(vars+0x428),angle,turnRate,turnRate,turnSpeed);
 bank=*(f32 *)(obj+0xf0)*g_boss_bank_scale;
 if(obj[0x43]>=8) *(f32 *)(vars+0x2c0)=bank;
 else *(f32 *)(vars+0x2c4)=bank;
}
