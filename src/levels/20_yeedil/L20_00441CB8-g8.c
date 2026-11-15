#include "common.h"
extern float level_interpolate_by_counter(int,int,float,float);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern float coll_probe_ground_height_below(char *,int,float);
extern void yeedil_boss_init_group(char *);
extern void yeedil_boss_disable_hazards(char *,int);
extern void moby_set_state(char *,int,int);
extern void anim_start_blended(char *,int,int,int);
extern char *part_find_owned_effect_slot(char *,int,int);
extern float moby_update_aim_target_strength(char *,char *);
extern f32 ApproachValue(char *,float,float);
extern int req_push_queue(char *,int);
extern s32 req_launch_queued(char *);
extern void SetDeathBits(char *,int,int);
extern void game_set_stored_value_pair(void (*)(int),char *);
extern void moby_start_screen_effect_state(int);
extern void group_activate_waiting_members(int,float);
/* EE keeps integer and floating arguments in independent register banks. */
extern int weapon_select_aim_target(char *,int,float,float,int,int);
extern void euler_rotation_basis(char *,char *);
extern const float D_L20_001B2030 __attribute__((sda));
extern const float D_L20_001B2034 __attribute__((sda));
extern char D_L20_001C01C0[];
/* Sets up the big enemy when it first appears and handles its health. It reacts to hits, switches phase at low health and starts the death sequence. */
void yeedil_boss_init_damage(char *obj) {
 char *st=*(char **)(obj+0x68), *p;
 float f, h;
 if (*(u8 *)(obj+0x20)==0) {
  *(int *)(st+0x1854)=-1;
  *(short *)(obj+0x32)=255; *(u8 *)(obj+0x30)=255;
  { float scale=level_interpolate_by_counter(5,20,1.0f,0.5f);
  *(float *)(st+0x20)=*(float *)(st+0x20)*scale;
  *(short *)(st+0x24)=FloatToInt((float)*(short *)(st+0x24)*scale); }
  *(float *)(st+0x54)=0.5f; *(float *)(st+0x50)=4.0f;
  *(float *)(st+0xE0)=coll_probe_ground_height_below(obj+0x10,0,0.5f);
  *(float *)(st+0x58)=2.0f; *(float *)(st+0x5C)=2.0f;
  *(float *)(st+0x60)=3.1415927f; *(int *)(st+0x184C)=15;
  f=IntToFloat(*(short *)(st+0x24));
  *(float *)(st+0x1828)=(2.0f-(float)*(int *)(st+0x182C))*(f*0.33333f);
  yeedil_boss_init_group(obj); yeedil_boss_disable_hazards(obj,0);
  *(float *)(obj+0x18)+=5.0f;
  *(float *)(obj+0x18)=coll_probe_ground_height_below(obj+0x10,0,0.5f);
  *(u16 *)(obj+0x34)|=0x400; *(int *)(obj+0x9C)=2;
  moby_set_state(obj,24,6);
  if (*(u8 *)(obj+0x43)!=1) anim_start_blended(obj,1,0,0);
  *(u8 *)(st+0x48)=FloatToInt(15.0f);
  *(u8 *)(st+0x4A)=FloatToInt(12.8f);
  *(u16 *)(obj+0x34)|=0x1000;
  qcopy(st+0x17E0,obj+0x10);
 }
 if (*(u8 *)(obj+0x95)==6) return;
 *(float *)(obj+0x2C)=*(float *)(*(char **)(obj+0x24)+0x24)*D_L20_001B2030;
 *(float *)(st+0x30)=D_L20_001B2034;
 p=part_find_owned_effect_slot(obj,0x10000,0);
 if(p && (p=*(char **)(p+0x20))) {
  switch (*(short *)(p+0xAA)) { case 0x5DE: case 0x3A6: case MOBY_CLASS_MEGACORP_TROOPER_LEGS: *(u8 *)(obj+0xA8)=255; }
 }
 h=moby_update_aim_target_strength(obj,part_find_owned_effect_slot(obj,0x10000,0));
 ApproachValue(st+0x20,0.0f,h); *(u8 *)(obj+0xA8)=255;
 f=*(float *)(st+0x20);
 if(f<=0.0f || *(u8 *)(st+0x2E)==2) {
  *(float *)(st+0x20)=0.0f;
  if(!req_push_queue(D_L20_001C01C0,0xA1)) goto done;
  if(*(u8 *)(st+0x2E)!=2) SetDeathBits(obj,0,3);
  req_push_queue(D_L20_001C01C0,0xA0); req_launch_queued(D_L20_001C01C0);
  moby_set_state(obj,17,6); game_set_stored_value_pair(moby_start_screen_effect_state,obj);
 } else if(f<=*(float *)(st+0x1828)) {
  moby_set_state(obj,15,5); ++*(int *)(st+0x182C);
  f=IntToFloat(*(short *)(st+0x24));
  *(float *)(st+0x1804)=0.0f; *(float *)(st+0x1800)=0.0f;
  *(float *)(st+0x1828)=(2.0f-(float)*(int *)(st+0x182C))*(f*0.33333f);
  if(*(int *)(st+0x182C)==2) group_activate_waiting_members(*(int *)(st+0x244),-1.0f);
 } else if(h!=0.0f && (p=*(char **)(st+0x38)) && *(short *)(p+0xAA)==0x12D3) {
  moby_set_state(obj,15,5); *(float *)(st+0x1804)=0.0f; *(float *)(st+0x1800)=0.0f; *(u8 *)(obj+0xBC)=1;
 }
done:
 *(u8 *)(st+0x2E)=1;
 weapon_select_aim_target(obj,*(int *)(st+0x220),64.0f,0.0f,0,0);
 qcopy(obj+0x10,st+0x17E0);
 if(*(float *)(obj+0xF0)!=0.0f || *(float *)(obj+0xF4)!=0.0f) {
  *(float *)(obj+0xF4)=0.0f; *(float *)(obj+0xF0)=0.0f; euler_rotation_basis(obj+0xC0,obj+0xF0);
 }
}
