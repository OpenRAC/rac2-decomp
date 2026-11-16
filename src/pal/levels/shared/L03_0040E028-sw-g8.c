#include "include_asm.h"

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
extern void moby_start_drop_pal(u8 *,int);
extern int hero_get_target_state_kind(void);
extern int moby_is_at_stored_height(u8 *);
extern void hero_start_loader_state(int);
extern int request_begin_slot(int,int,u8 *,int,int);
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *);
extern void vec_fast_divide_helper(void *,void *,float);

void slim_cognito_button_update_pal(u8 *e) {
 float v[4], angle, delta, interpolated[4];
 u8 *s=*(u8 **)(e+0x68), *other, *p, *cam;
 int n;
 switch(e[0x20]) {
 case 0:
  if (*(int *)s) {moby_set_state(e,3,-1);break;}
  moby_set_state(e,1,-1);
  {u8 *base=g_moby_record_base[0]; u8 *child;
  *(int *)(e+0x98)=0; *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)|0x41)&0xefff;
  child=base+(*(int *)(s+8)<<8);
  *(int *)(child+0x98)=0; *(u16 *)(child+0x34)=(*(u16 *)(child+0x34)|0x41)&0xefff;}
  break;
 case 1:
  level_set_bit_in_flag_table(g_current_map_index[0],1);
  if (g_hero_state.state!=0x31) {
   if(IsPointInCuboid((u8 *)&g_hero_state+0x80,*(int *)(s+4))) {
    TryClaimNotice(1,0x12EB,1);
    if(hero_is_allowed_for_mode(1) && (g_pad_held_flags&0x10)) moby_set_state(e,2,-1);
   }
   if(!g_game_flag_table[0x8c] && IsPointInCuboid((u8 *)&g_hero_state+0x80,*(int *)(s+0xc))) {
    n=-1;
    switch(g_current_map_index[0]) {case 3:n=0x35;break;case 8:n=0x5c;break;case 13:n=0x79;break;}
    if(n!=-1 && req_push_queue(g_str_clank_scene_key,n)) {req_launch_queued(g_str_clank_scene_key);g_game_flag_table[0x8c]=1;moby_set_state(e,4,-1);}
   }
  }
  *(int *)(e+0x98)=0; *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)|0x41)&0xefff;
  break;
 case 2:
  if(flag_set_first_pending(e)) {
   vec_scale_to_length(v,e+0xC0,3.0f);FastVecAdd(v,v,e+0x10);
   angle=FastAddRotations(*(float *)(e+0xf8),3.1415927f);hero_start_target_state(v,0,angle);
  }
  cam=*(u8 **)(g_hero_l03_state_alias.camera+0x70);p=cam+0x1c0;
  *(int *)(p+0x10)|=3;
  angle=mat_fast_helper_a(*(float *)(cam+0x160),*(float *)(cam+0x164));
  interpolated[0]=fast_subtract_rotations(*(float *)(e+0xf8),angle);
  math_approach_target_with_direction_mode(interpolated,0.0f,(float *)(s+0x10),0,0.0013962636f,0.0013962636f,0.06981318f);
  *(float *)(p+0x1c)=1.0f;*(float *)(p+0x14)=-*(float *)(s+0x10);
  delta=FastDiffRots(g_hero_l03_state_alias.yaw,*(float *)(e+0xf8));
  other=g_moby_record_base[0]+(*(int *)(s+8)<<8);
  if(delta>1.5707964f)moby_start_drop_pal(other,0);
  if(hero_get_target_state_kind()==2 && delta>3.135f && moby_is_at_stored_height(other)) {
   moby_set_state(e,1,-1);hero_start_loader_state(0);request_begin_slot(5,1,e,0,0);
  } else if((unsigned)(g_game_mode-0x62)>=3)moby_set_state(e,1,-1);
  break;
 case 4:
  {unsigned timer=*(u16 *)(e+0x96),old=timer++;
  *(u16 *)(e+0x96)=timer;
  if(old>17 && !g_hero_l03_mode[0]) {
   moby_start_drop_pal(g_moby_record_base[0]+(*(int *)(s+8)<<8),1);request_begin_slot(5,1,e,0,0);
  }}break;
 case 3:
  if(g_hero_l03_mode[0]==2){e[0x31]=0;*(u16 *)(e+0x34)|=1;}
  else {e[0x31]=1;*(u16 *)(e+0x34)&=0xfffe;}
  break;
 }
 n=*(int *)(s+0x14);
 if(n!=-1 && g_game_mode!=0x31) {
  other=D_L03_001B2A1C_gp+(n<<8)+0x10;
  FastVecSub(v,other,e+0x10);
  if(FastVecLength(v)<20.0f){if(v[0]!=0.0f)v[0]=20.0f/v[0];if(v[1]!=0.0f)v[1]=20.0f/v[1];v[2]=0.0f;vec_fast_divide_helper(v,v,0.20000002f);FastVecAdd(other,other,v);}
 }
}
