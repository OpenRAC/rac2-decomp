#include "names.h"
/* func_PAL_L07_003FC8D0, the PAL copy of func_L07_003F80B8: the same C, where func_L07_003F8430
   becomes func_PAL_L07_003FCC48; 0.0034906589426100254f becomes 0.005026549f; 0.20943955f becomes
   0.25132746f; 0.00027777778f becomes 0.00040000002f; 1.0f / 60.0f becomes 0.020000001f;
   0.0000048481375f becomes 6.981318e - 06f; 0.000290888245f becomes 0.0003490659f. */
#include "include_asm.h"

#include "common.h"

extern void flyer_steer_pal(u8 *);
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
void boss_move_toward_target_pal(u8 *moby,f32 limit)
{
 f32 target[4],delta[4],move[4],correction[4];
 u8 *vars=*(u8 **)(moby+0x68);
 u8 *target_moby;
 f32 rate,speed,length,amount,angle,bank,turn_rate,turn_speed;
 f32 *yaw;
 flyer_steer_pal(moby);
 if(!moby[0x95]) {
  func_2E47D0(target,vars+0x3e0,*(u8 **)(vars+0x418)+0xc0);
  func_2E4310(target,target,*(u8 **)(vars+0x418)+0x10);
  target_moby=func_316FD8(*(u8 **)(vars+0x418));
  if(limit>=0.0f) {
   qcopy(delta,target_moby+0x10);
   func_316638(delta,limit);
   func_2E4310(moby+0x10,moby+0x10,delta);
  } else func_2E4310(moby+0x10,moby+0x10,target_moby+0x10);
  *(f32 *)(moby+0xf8)=func_2E5318(*(f32 *)(*(u8 **)(vars+0x418)+0xf8),3.1415927f);
 } else {
  qcopy(target,vars+0x3e0);
  yaw=(f32 *)(moby+0xf8);
  angle=func_2E49C8(g_hero_state.pos[0]-*(f32 *)(moby+0x10),g_hero_state.pos[1]-*(f32 *)(moby+0x14));
  func_3144F0(yaw,vars+0x424,angle,0.005026549f,0.005026549f,0.25132746f,0);
 }
 func_2E4340(delta,target,moby+0x10);
 rate=(moby[0x95]?g_boss_rate_alt:g_boss_rate_normal)*0.00040000002f;
 speed=(moby[0x95]?g_boss_speed_alt:g_boss_speed_normal)*(0.020000001f);
 length=func_2E4458(delta);
 amount=func_2E4248(length*rate*0.5f);
 if(limit>=0.0f && limit<speed) speed=limit;
 if(speed<amount) amount=speed;
 if(amount<length) func_2E45F0(move,delta,amount);
 else qcopy(move,delta);
 func_2E4340(correction,move,vars+0x3f0);
 func_316638(correction,rate);
 func_2E4310(vars+0x3f0,vars+0x3f0,correction);
 func_2E4310(moby+0x10,moby+0x10,vars+0x3f0);
 angle=func_2E4418(moby+0xd0,vars+0x3f0)*g_boss_angle_scale;
 if(angle>1.5707965f) angle=1.5707965f;
 else if(angle< -1.5707965f) angle= -1.5707965f;
 turn_rate=g_boss_l07_turn_rate;
 turn_speed=g_boss_turn_speed;
 turn_rate*=6.981318e-06f;
 turn_speed*=0.0003490659f;
 func_314038((f32 *)(moby+0xf0),(f32 *)(vars+0x428),angle,turn_rate,turn_rate,turn_speed);
 bank=*(f32 *)(moby+0xf0)*g_boss_bank_scale;
 if(moby[0x43]>=8) *(f32 *)(vars+0x2c0)=bank;
 else *(f32 *)(vars+0x2c4)=bank;
}
