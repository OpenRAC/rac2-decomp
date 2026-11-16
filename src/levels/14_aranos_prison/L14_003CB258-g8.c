#include "common.h"

/* func_L14_003CB258: a three-state moby update (spawn and link a 0xF4D moby, wait for the
   animation, then swing through a bounded angle with restitution). Its tuning floats are
   read through $gp, and its switch table and float constants are this unit's .rodata. */
extern void moby_set_state(void *, int, int);
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *);
extern int flag_set_first_pending(void *);
extern int flag_is_third_pending_set(void *);
extern void moby_set_flag_bit(void *, int);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void lift_clamp_group_riders_wide(void *);
extern void UpdateLaunchVolume(void *);
extern void swing_apply_to_object(void *);
extern int PlayMobySound(int, int, void *);
extern char *g_platform_actor_ref NOT_SDA;
extern unsigned short g_swing_id NOT_SDA;
extern char g_identity_l14_matrix[] __attribute__((sda));
extern float g_swing_angle_speed __attribute__((sda));
extern float g_swing_start_angle __attribute__((sda));
extern float g_swing_restitution __attribute__((sda));
extern float g_swing_max_angle __attribute__((sda));
extern float g_swing_stop_angle __attribute__((sda));
extern float g_swing_offset __attribute__((sda));
void swing_update(char *self) {
 char *vars = *(char **)(self+0x68);
 char *child;
 float max_angle,delta,velocity,angle,restitution;
 switch ((unsigned char)self[0x20]) {
 case 0:
  moby_set_state(self,1,-1);
  *(int *)(vars+0x5C) |= 1;
  qcopy(vars+0x70,self+0x10);
  *(float *)(vars+0x78) += g_swing_offset;
  child=CreateMoby(0xF4D /* moby class 3917 */);
  if(child) {
   unsigned short flags,link;
   moby_init_child_from_parent(child,self);
   flags=*(unsigned short *)(child+0x34);
   link=*(unsigned short *)(self+0x32);
   *(unsigned short *)(child+0x32)=link;
   *(unsigned short *)(child+0x34)=flags|2;
   *(int *)(child+0x9C)=0x80000001;
   child[0x30]=0;
   *(unsigned short *)(child+0x7C)=0x8001;
   *(int *)(self+0x9C)=6;
  }
  break;
 case 1:
  if(flag_set_first_pending(self))mat_combine_and_store(vars+0x20,g_identity_l14_matrix,self+0xF0,self+0xF0);
  if(g_platform_actor_ref==self)lift_clamp_group_riders_wide(self);
  if(flag_is_third_pending_set(self)) {
   moby_set_state(self,2,-1);
   moby_set_flag_bit(self,0);
   UpdateLaunchVolume(self);
  }
  break;
 case 2:
  if(flag_set_first_pending(self))*(float *)(vars+0x84)=g_swing_start_angle*0.0002908882452175021f;
  delta=g_swing_angle_speed*4.848137450608192e-06f;
  velocity=*(float *)(vars+0x84)-delta;
  max_angle=g_swing_max_angle*0.01745329424738884f;
  angle=*(float *)(vars+0x80);
  angle+=velocity;
  *(float *)(vars+0x84)=velocity;
  *(float *)(vars+0x80)=angle;
  if(*(float *)(vars+0x80)>max_angle) {
   restitution=g_swing_restitution;
   *(float *)(vars+0x80)=max_angle;
   *(float *)(vars+0x84)*=restitution;
   PlayMobySound(0,0,self);
  } else if(*(float *)(vars+0x80)<0.0f) {
   restitution=g_swing_restitution;
   *(float *)(vars+0x80)=0.0f;
   *(float *)(vars+0x84)*=restitution;
   PlayMobySound(0,0,self);
   if(*(float *)(vars+0x84)<=g_swing_stop_angle*0.0002908882452175021f)moby_set_state(self,1,-1);
  }
  g_swing_id=-1;
  swing_apply_to_object(self);
  break;
 }
}
