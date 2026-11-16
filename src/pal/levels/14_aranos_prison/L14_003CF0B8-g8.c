#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *);
extern int flag_set_first_pending(void *);
extern int flag_is_third_pending_set(void *);
extern void moby_set_flag_bit(void *, int);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void lift_clamp_group_riders_wide_pal(void *);
extern void UpdateLaunchVolume_pal(void *);
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

void swing_update_pal(char *self) {
 char *s = *(char **)(self+0x68);
 char *e;
 float b,delta,velocity,position,restitution;
 switch ((unsigned char)self[0x20]) {
 case 0:
  moby_set_state(self,1,-1);
  *(int *)(s+0x5C) |= 1;
  qcopy(s+0x70,self+0x10);
  *(float *)(s+0x78) += g_swing_offset;
  e=CreateMoby(0xF4D);
  if(e) {
   unsigned short flags,link;
   moby_init_child_from_parent(e,self);
   flags=*(unsigned short *)(e+0x34);
   link=*(unsigned short *)(self+0x32);
   *(unsigned short *)(e+0x32)=link;
   *(unsigned short *)(e+0x34)=flags|2;
   *(int *)(e+0x9C)=0x80000001;
   e[0x30]=0;
   *(unsigned short *)(e+0x7C)=0x8001;
   *(int *)(self+0x9C)=6;
  }
  break;
 case 1:
  if(flag_set_first_pending(self))mat_combine_and_store(s+0x20,g_identity_l14_matrix,self+0xF0,self+0xF0);
  if(g_platform_actor_ref==self)lift_clamp_group_riders_wide_pal(self);
  if(flag_is_third_pending_set(self)) {
   moby_set_state(self,2,-1);
   moby_set_flag_bit(self,0);
   UpdateLaunchVolume_pal(self);
  }
  break;
 case 2:
  if(flag_set_first_pending(self))*(float *)(s+0x84)=g_swing_start_angle*0.0003490659f;
  delta=g_swing_angle_speed*6.981318e-06f;
  velocity=*(float *)(s+0x84)-delta;
  b=g_swing_max_angle*0.01745329424738884f;
  position=*(float *)(s+0x80);
  position+=velocity;
  *(float *)(s+0x84)=velocity;
  *(float *)(s+0x80)=position;
  if(*(float *)(s+0x80)>b) {
   restitution=g_swing_restitution;
   *(float *)(s+0x80)=b;
   *(float *)(s+0x84)*=restitution;
   PlayMobySound(0,0,self);
  } else if(*(float *)(s+0x80)<0.0f) {
   restitution=g_swing_restitution;
   *(float *)(s+0x80)=0.0f;
   *(float *)(s+0x84)*=restitution;
   PlayMobySound(0,0,self);
   if(*(float *)(s+0x84)<=g_swing_stop_angle*0.0003490659f)moby_set_state(self,1,-1);
  }
  g_swing_id=-1;
  swing_apply_to_object(self);
  break;
 }
}
