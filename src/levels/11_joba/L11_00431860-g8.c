#include "common.h"
extern int D_L11_001AED04;
extern int D_L11_001AED00;
extern char D_L11_001BA8C0[];
extern float coll_probe_ground_height_below(void *, int, float);
extern int FloatToInt(float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int math_random_int_range(int, int);
extern void moby_set_state(void *, int, int);
extern void anim_play_on_self_and_owner(void *, int, int, int, int);
extern float math_random_float_range(float, float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern void gfx_free_point_light(int);
extern void anim_start_blended(void *, int, int, int);
extern void saur_beast_flag_id_list(void *);
extern int hero_check_distance_zones(void *, void *, int, int, float, float, int);
#define I(o) (*(int *)(d+(o)))
#define F(o) (*(float *)(d+(o)))
#define B(o) (*(u8 *)(d+(o)))
/* Runs the Saur-Beast's basic setup and per-frame checks: sets its stats on the first frame, keeps it on the ground, and reacts when it is hit. */
void saur_beast_update_base(u8 *obj) {
 u8 *d=*(u8 **)(obj+0x68); int hitResult; u8 *attacker;
 if (!obj[0x20]) {
  float height;
  D_L11_001AED04++;
  height=coll_probe_ground_height_below(obj+0x10,0,0.5f);
  *(void **)(d+0x18)=d+0x140;
  *(float *)(obj+0x18)=height;
  I(0x2a0)=0;
  B(0x48)=FloatToInt(20.0f);
  B(0x4a)=FloatToInt(12.8f);
  B(0x70)=26; B(0x71)=11; B(0x72)=11; B(0x76)=13;
  F(0x7c)=0.10000000894f; F(0x80)=0.0666666701f; F(0x84)=0.00416666688f;
  F(0x88)=0.00833333377f; F(0x8c)=0.00416666688f;
  I(0xa8)=3; F(0x90)=0.5f; F(0x94)=0.5f; F(0x9c)=0.4f;
  *(s8 *)(d+0xcc)=-1; *(s8 *)(d+0xcd)=-1; *(s8 *)(d+0xce)=-1; *(s8 *)(d+0xcf)=-1;
  *(s8 *)(d+0xd2)=-1; *(s8 *)(d+0xd3)=-1; B(0xd7)=1;
  F(0x140)=1; F(0x144)=0.25f; F(0x148)=0.6f; F(0x14c)=0.6f; F(0x150)=1.48353004f;
  F(0x170)=1.48353004f; F(0x16c)=0.00138888892f;
  moby_set_controller_speed_limits(obj,0.00222222228f,0.0666666701f,0.0011635529808700085f,0.10471977293491364f);
  qcopy(d+0x110,obj+0x10);
  F(0x120)=1.25f; F(0x12c)=F(0x290); F(0x130)=10;
  I(0x28c)=math_random_int_range(120,700);
  B(0x28)=3; B(0x29)=1; F(0x2b4)=B(0x34); F(0x2b8)=B(0x36); F(0x30)=0.75f;
  moby_set_state(obj,1,0); anim_play_on_self_and_owner(obj,4,1,0,0);
  *(float *)(obj+0x48)=math_random_float_range(0.5f,1.25f);
  if (I(0x2bc)!=-1) moby_set_state(obj,2,-1);
 }
 if(obj[0x31] && fast_vec_dist(obj+0x10,D_L11_001BA8C0)<24.0f) {moby_update_ground_check(obj);obj[0x6f]=22;}
 if(obj[0x95]!=3) {
  float height=coll_probe_ground_height_below(obj+0x10,0,0.5f);
  *(float *)(obj+0x18)-=1.146666765f;
  if(*(float *)(obj+0x18)<height) *(float *)(obj+0x18)=height;
 }
 hitResult=moby_apply_damage_to_object(obj,d+0x60,0);
 if(hitResult) {
  attacker=*(u8 **)(d+0x38);
  if(attacker) {int attackerClass=*(short *)(attacker+0xaa); if(attackerClass!=0x47 /* moby class 71 */ && attackerClass!=0xdd9 /* moby class 3545 */ && attackerClass!=0xd1b /* moby class 3355 */ && attackerClass!=0xce7 /* moby class 3303 */ && attackerClass!=0xd07 /* Jobian Saur-Beast */ && attackerClass) D_L11_001AED00=0;}
  I(0x2a0)=0;
  if(I(0x2b0)>=0) {gfx_free_point_light(I(0x2b0));I(0x2b0)=-1;}
  if(hitResult==5) {I(0xf0)=0;F(0xf4)=0.837758183f;}
  if(I(0x27c)) {
   switch(hitResult) {
   case 1: break;
   case 2: case 3: anim_start_blended(*(void **)(d+0x27c),8,0,3);break;
   case 4: case 5: anim_start_blended(*(void **)(d+0x27c),9,0,3); *(int *)(*(u8 **)(*(u8 **)(d+0x27c)+0x68)+0x26c)=0;break;
   }
  }
  saur_beast_flag_id_list(obj);
  if(!obj[0x95]) {
   if(I(0x29c)!=-1) {moby_set_state(obj,12,1);anim_play_on_self_and_owner(obj,4,3,0,12);}
   else {moby_set_state(obj,11,1);*(short *)(d+0x270)=math_random_int_range(580,600);anim_play_on_self_and_owner(obj,6,5,0,10);}
  }
 }
 *(short *)(d+0x274)=hero_check_distance_zones(obj,d+0x278,I(0x260),I(0x264),F(0x268),F(0x26c),0);
}
