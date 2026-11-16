#include "names.h"
/* The state timer is a 16-bit field incremented through a wider local; its old value decides
   case 4. The rest is the door pair: a child object at index s+8 and an optional push volume. */
#include "common.h"
extern u8 *g_moby_record_base[] MACRO_ADDR;
extern u8 *D_L03_001B2A1C_gp SDATA(D_L03_001B2A1C);
typedef struct { u8 pad[0x2294]; int state; } PlayerState;
extern PlayerState g_hero_state;
extern u8 g_game_flag_table[];
extern int g_current_map_index[] MACRO_ADDR;
extern int g_pad_held_flags __attribute__((nosda));
extern int g_hero_l03_mode[] MACRO_ADDR;
extern int g_game_mode __attribute__((nosda));
extern u8 g_str_clank_scene_key[];
typedef struct { u8 pad[0x158]; float yaw; u8 pad2[0x34]; u8 *camera; } CameraState;
extern CameraState g_hero_l03_state_alias;
extern void moby_set_state(u8 *,int,int);
extern void level_set_bit_in_flag_table(int,int);
extern int IsPointInCuboid(u8 *,int);
extern int TryClaimNotice(int,int,int);
extern int hero_is_allowed_for_mode(int);
extern int req_push_queue(u8 *,int);
extern s32 req_launch_queued(u8 *);
extern int flag_set_first_pending(u8 *);
extern void vec_scale_to_length(float *,u8 *,float);
extern void FastVecAdd(void *,void *,void *);
extern float FastAddRotations(float,float);
extern void hero_start_target_state(float *,int,float);
extern float mat_fast_helper_a(float,float);
extern float fast_subtract_rotations(float,float);
extern float math_approach_target_with_direction_mode(float *,float,float *,int,float,float,float);
extern float FastDiffRots(float,float);
extern void moby_start_drop(u8 *,int);
extern int hero_get_target_state_kind(void);
extern int moby_is_at_stored_height(u8 *);
extern void hero_start_loader_state(int);
extern int request_begin_slot(int,int,u8 *,int,int);
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *);
extern void vec_fast_divide_helper(void *,void *,float);
/* Runs the Slim Cognito button that opens a door: it watches the player, plays the camera when pressed, and opens the linked door. */
void slim_cognito_button_update(u8 *moby) {
 float vec[4], angle, delta, interpolated[4];
 u8 *vars=*(u8 **)(moby+0x68), *other, *camera_block, *camera_record;
 int link_index;
 switch(moby[0x20]) {
 case 0:
  if (*(int *)vars) {moby_set_state(moby,3,-1);break;}
  moby_set_state(moby,1,-1);
  {u8 *base=g_moby_record_base[0]; u8 *child;
  *(int *)(moby+0x98)=0; *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xefff;
  child=base+(*(int *)(vars+8)<<8);
  *(int *)(child+0x98)=0; *(u16 *)(child+0x34)=(*(u16 *)(child+0x34)|0x41)&0xefff;}
  break;
 case 1:
  level_set_bit_in_flag_table(g_current_map_index[0],1);
  if (g_hero_state.state!=0x31) {
   if(IsPointInCuboid((u8 *)&g_hero_state+0x80,*(int *)(vars+4))) {
    TryClaimNotice(1,0x2799,1);
    if(hero_is_allowed_for_mode(1) && (g_pad_held_flags&0x10)) moby_set_state(moby,2,-1);
   }
   if(!g_game_flag_table[0x8c] && IsPointInCuboid((u8 *)&g_hero_state+0x80,*(int *)(vars+0xc))) {
    link_index=-1;
    switch(g_current_map_index[0]) {case 3:link_index=0x35;break;case 8:link_index=0x5c;break;case 13:link_index=0x79;break;}
    if(link_index!=-1 && req_push_queue(g_str_clank_scene_key,link_index)) {req_launch_queued(g_str_clank_scene_key);g_game_flag_table[0x8c]=1;moby_set_state(moby,4,-1);}
   }
  }
  *(int *)(moby+0x98)=0; *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xefff;
  break;
 case 2:
  if(flag_set_first_pending(moby)) {
   vec_scale_to_length(vec,moby+0xc0,3.0f);FastVecAdd(vec,vec,moby+0x10);
   angle=FastAddRotations(*(float *)(moby+0xf8),3.1415927f);hero_start_target_state(vec,0,angle);
  }
  camera_record=*(u8 **)(g_hero_l03_state_alias.camera+0x70);camera_block=camera_record+0x1c0;
  *(int *)(camera_block+0x10)|=3;
  angle=mat_fast_helper_a(*(float *)(camera_record+0x160),*(float *)(camera_record+0x164));
  interpolated[0]=fast_subtract_rotations(*(float *)(moby+0xf8),angle);
  math_approach_target_with_direction_mode(interpolated,0.0f,(float *)(vars+0x10),0,0.00096962746f,0.00096962746f,0.05817765f);
  *(float *)(camera_block+0x1c)=1.0f;*(float *)(camera_block+0x14)=-*(float *)(vars+0x10);
  delta=FastDiffRots(g_hero_l03_state_alias.yaw,*(float *)(moby+0xf8));
  other=g_moby_record_base[0]+(*(int *)(vars+8)<<8);
  if(delta>1.5707964f)moby_start_drop(other,0);
  if(hero_get_target_state_kind()==2 && delta>3.135f && moby_is_at_stored_height(other)) {
   moby_set_state(moby,1,-1);hero_start_loader_state(0);request_begin_slot(5,1,moby,0,0);
  } else if((unsigned)(g_game_mode-0x62)>=3)moby_set_state(moby,1,-1);
  break;
 case 4:
  {unsigned timer=*(u16 *)(moby+0x96),old=timer++;
  *(u16 *)(moby+0x96)=timer;
  if(old>20 && !g_hero_l03_mode[0]) {
   moby_start_drop(g_moby_record_base[0]+(*(int *)(vars+8)<<8),1);request_begin_slot(5,1,moby,0,0);
  }}break;
 case 3:
  if(g_hero_l03_mode[0]==2){moby[0x31]=0;*(u16 *)(moby+0x34)|=1;}
  else {moby[0x31]=1;*(u16 *)(moby+0x34)&=0xfffe;}
  break;
 }
 link_index=*(int *)(vars+0x14);
 if(link_index!=-1 && g_game_mode!=0x31) {
  other=D_L03_001B2A1C_gp+(link_index<<8)+0x10;
  FastVecSub(vec,other,moby+0x10);
  if(FastVecLength(vec)<20.0f){if(vec[0]!=0.0f)vec[0]=20.0f/vec[0];if(vec[1]!=0.0f)vec[1]=20.0f/vec[1];vec[2]=0.0f;vec_fast_divide_helper(vec,vec,1.0f/6.0f);FastVecAdd(other,other,vec);}
 }
}
