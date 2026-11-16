#include "common.h"
extern void func_2E4340(void *,void *,void *);
extern void func_31B090(void *,void *,void *,s32);
extern void func_313DD8(void *,f32,f32);
extern f32 func_2E4508(void *,void *);
extern s32 func_2E3F80(s32 *);
extern f32 math_interpolate_between_limits(s32,s32,f32,f32);
extern s32 func_2E5470(f32);
extern s32 func_310AD8(s32,s32);
extern f32 func_310B30(f32,f32);
extern f32 func_2E49C8(f32,f32);
extern f32 func_2E5360(f32,f32);
extern f32 func_2E5318(f32,f32);
extern f32 func_2E4900(f32);
extern f32 func_2E4918(f32);
extern void func_2E4310(void *,void *,void *);
extern f32 g_flyer_offset_range __attribute__((sda));
extern f32 g_flyer_velocity_max;
extern f32 g_boss_move_tier_table __attribute__((sda));
extern f32 g_flyer_min_distance __attribute__((sda));
extern f32 g_flyer_max_distance __attribute__((sda));
extern f32 g_flyer_l07_speed __attribute__((sda));
extern f32 g_flyer_height_offset __attribute__((sda));
extern f32 g_flyer_height_angle_scale __attribute__((sda));
extern f32 g_flyer_turn_rate __attribute__((sda));
extern s32 g_flyer_interp_min __attribute__((sda));
extern s32 g_flyer_interp_max;
typedef struct { u8 pad[0x140]; f32 pos[6]; f32 angle; } Target;
extern Target g_hero_l07_state_block;
typedef struct {u8 pad[0x38];f32 value;u8 rest[0x80-0x3c];} Record;
extern Record *g_shooter_mount_table;
/* Works out where a flying enemy should drift next. In one mode it follows its parent; in the other it picks a new circling direction around the player every so often and bobs up and down. */
void flyer_steer(u8 *moby)
{
 f32 offset[4];
 u8 *vars=*(u8 **)(moby+0x68);
 s32 needs_new_heading;
 f32 distance,angle,turn_step;
 if (!moby[0x95]) {
  func_2E4340(offset,vars+0x140,*(u8 **)(vars+0x418)+0x10);
  func_31B090(*(u8 **)(vars+0x418),offset,offset,0);
  if (*(s32 *)(vars+0x420)) func_313DD8(vars+0x3e0,offset[0]-g_flyer_offset_range,1.0f/6.0f);
  else func_313DD8(vars+0x3e0,offset[0]+g_flyer_offset_range,1.0f/6.0f);
  if (*(f32 *)(vars+0x3e0)>g_flyer_velocity_max) *(f32 *)(vars+0x3e0)=g_flyer_velocity_max;
  else if (*(f32 *)(vars+0x3e0)<g_boss_move_tier_table) *(f32 *)(vars+0x3e0)=g_boss_move_tier_table;
  func_313DD8(vars+0x3e4,offset[1],1.0f/6.0f);
  if (*(f32 *)(vars+0x3e4)>5.0f) *(f32 *)(vars+0x3e4)=5.0f;
  else if (*(f32 *)(vars+0x3e4)<-5.0f) *(f32 *)(vars+0x3e4)=-5.0f;
 } else {
  if (*(s32 *)(vars+0x440)<0) *(s32 *)(vars+0x440)=-*(s32 *)(vars+0x440);
  else if (func_2E4508(moby+0x10,vars+0x3e0)<2.0f) {
   needs_new_heading=0;
   distance=func_2E4508(vars+0x140,moby+0x10);
   if(distance<g_flyer_min_distance) needs_new_heading=1;
   else if(distance>g_flyer_max_distance) needs_new_heading=1;
   if(func_2E3F80((s32 *)(vars+0x440))) {
    needs_new_heading=1;
    *(s32 *)(vars+0x440)=func_2E5470(math_interpolate_between_limits(5,15,(f32)g_flyer_interp_min,(f32)g_flyer_interp_max));
    *(s32 *)(vars+0x440)+=func_310AD8(0,60);
   }
   if(needs_new_heading) {
    turn_step=func_310B30(10.0f,40.0f)*0.017453294f;
    angle=func_2E49C8(*(f32 *)(moby+0x10)-g_hero_l07_state_block.pos[0],*(f32 *)(moby+0x14)-g_hero_l07_state_block.pos[1]);
    if(func_2E5360(angle,g_hero_l07_state_block.angle)*turn_step>0.0f) turn_step=-turn_step;
    angle=func_2E5318(g_hero_l07_state_block.angle,turn_step);
    *(f32 *)(vars+0x3e0)=func_2E4900(angle)*g_flyer_l07_speed;
    *(f32 *)(vars+0x3e4)=func_2E4918(angle)*g_flyer_l07_speed;
    *(f32 *)(vars+0x3e8)=0.0f;
    func_2E4310(vars+0x3e0,vars+0x3e0,vars+0x140);
   }
  }
  *(f32 *)(vars+0x454)=func_2E5318(*(f32 *)(vars+0x454),g_flyer_turn_rate*0.000290888245f);
  angle=func_2E4918(*(f32 *)(vars+0x454));
  *(f32 *)(vars+0x3e8)=g_shooter_mount_table[*(s32 *)(vars+0x174)].value+g_flyer_height_offset+g_flyer_height_angle_scale*angle;
 }
}
