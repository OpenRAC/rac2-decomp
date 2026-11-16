#include "include_asm.h"

#include "common.h"
extern int g_active_rider_count;
extern int g_enemy_spawn_enabled;
extern char g_hero_l11_position[];
extern float coll_probe_ground_height_below(void *, int, float);
extern int FloatToInt(float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int math_random_int_range(int, int);
extern void moby_set_state(void *, int, int);
extern void anim_play_on_self_and_owner(void *, int, int, int, int);
extern float math_random_float_range(float, float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object_pal(void *, void *, int);
extern void gfx_free_point_light(int);
extern void anim_start_blended_pal(void *, int, int, int);
extern void saur_beast_flag_id_list(void *);
extern int hero_check_distance_zones(void *, void *, int, int, float, float, int);
#define I(o) (*(int *)(d+(o)))
#define F(o) (*(float *)(d+(o)))
#define B(o) (*(u8 *)(d+(o)))

/* Runs the Saur-Beast's basic setup and per-frame checks: sets its stats on the first frame,
   keeps it on the ground, and reacts when it is hit (PAL: 50 Hz timings). */
void saur_beast_update_base_pal(u8 *moby) {
 u8 *d=*(u8 **)(moby+0x68); int hit_state; u8 *target_moby;
 if (!moby[0x20]) {
  float height;
  g_active_rider_count++;
  height=coll_probe_ground_height_below(moby+0x10,0,0.5f);
  *(void **)(d+0x18)=d+0x140;
  *(float *)(moby+0x18)=height;
  I(0x2a0)=0;
  B(0x48)=FloatToInt(20.0f);
  B(0x4a)=FloatToInt(12.8f);
  B(0x70)=26; B(0x71)=11; B(0x72)=11; B(0x76)=13;
  F(0x7c)=0.120000005f; F(0x80)=0.080000006f; F(0x84)=0.006f;
  F(0x88)=0.012f; F(0x8c)=0.006f;
  I(0xa8)=3; F(0x90)=0.5f; F(0x94)=0.5f; F(0x9c)=0.4f;
  *(s8 *)(d+0xcc)=-1; *(s8 *)(d+0xcd)=-1; *(s8 *)(d+0xce)=-1; *(s8 *)(d+0xcf)=-1;
  *(s8 *)(d+0xd2)=-1; *(s8 *)(d+0xd3)=-1; B(0xd7)=1;
  F(0x140)=1; F(0x144)=0.25f; F(0x148)=0.6f; F(0x14c)=0.6f; F(0x150)=1.48353004f;
  F(0x170)=1.48353004f; F(0x16c)=0.002f;
  moby_set_controller_speed_limits(moby,0.0032000002f,0.080000006f,0.0016755164f,0.12566373f);
  qcopy(d+0x110,moby+0x10);
  F(0x120)=1.25f; F(0x12c)=F(0x290); F(0x130)=10;
  I(0x28c)=math_random_int_range(100,583);
  B(0x28)=3; B(0x29)=1; F(0x2b4)=B(0x34); F(0x2b8)=B(0x36); F(0x30)=0.75f;
  moby_set_state(moby,1,0); anim_play_on_self_and_owner(moby,4,1,0,0);
  *(float *)(moby+0x48)=math_random_float_range(0.5f,1.25f);
  if (I(0x2bc)!=-1) moby_set_state(moby,2,-1);
 }
 if(moby[0x31] && fast_vec_dist(moby+0x10,g_hero_l11_position)<24.0f) {moby_update_ground_check(moby);moby[0x6f]=22;}
 if(moby[0x95]!=3) {
  float height=coll_probe_ground_height_below(moby+0x10,0,0.5f);
  *(float *)(moby+0x18)-=1.3760002f;
  if(*(float *)(moby+0x18)<height) *(float *)(moby+0x18)=height;
 }
 hit_state=moby_apply_damage_to_object_pal(moby,d+0x60,0);
 if(hit_state) {
  target_moby=*(u8 **)(d+0x38);
  if(target_moby) {int type=*(short *)(target_moby+0xaa); if(type!=0x47 && type!=0xdd9 && type!=0xd1b && type!=0xce7 && type!=MOBY_CLASS_JOBIAN_SAUR_BEAST && type) g_enemy_spawn_enabled=0;}
  I(0x2a0)=0;
  if(I(0x2b0)>=0) {gfx_free_point_light(I(0x2b0));I(0x2b0)=-1;}
  if(hit_state==5) {I(0xf0)=0;F(0xf4)=1.0053098f;}
  if(I(0x27c)) {
   switch(hit_state) {
   case 1: break;
   case 2: case 3: anim_start_blended_pal(*(void **)(d+0x27c),8,0,2);break;
   case 4: case 5: anim_start_blended_pal(*(void **)(d+0x27c),9,0,2); *(int *)(*(u8 **)(*(u8 **)(d+0x27c)+0x68)+0x26c)=0;break;
   }
  }
  saur_beast_flag_id_list(moby);
  if(!moby[0x95]) {
   if(I(0x29c)!=-1) {moby_set_state(moby,12,1);anim_play_on_self_and_owner(moby,4,3,0,10);}
   else {moby_set_state(moby,11,1);*(short *)(d+0x270)=((s32)(math_random_int_range(580,600)) * 5 + 2) / 6;anim_play_on_self_and_owner(moby,6,5,0,8);}
  }
 }
 *(short *)(d+0x274)=hero_check_distance_zones(moby,d+0x278,I(0x260),I(0x264),F(0x268),F(0x26c),0);
}
