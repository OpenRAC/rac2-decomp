#include "include_asm.h"

#include "common.h"
extern float level_interpolate_by_counter(int,int,float,float);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern float coll_probe_ground_height_below(char *,int,float);
extern void yeedil_boss_init_group(char *);
extern void yeedil_boss_disable_hazards(char *,int);
extern void moby_set_state(char *,int,int);
extern void anim_start_blended_pal(char *,int,int,int);
extern char *part_find_owned_effect_slot(char *,int,int);
extern float moby_update_aim_target_strength_pal(char *,char *);
extern f32 ApproachValue(char *,float,float);
extern int req_push_queue(char *,int);
extern s32 req_launch_queued(char *);
extern void SetDeathBits_pal(char *,int,int);
extern void game_set_stored_value_pair(void (*)(int),char *);
extern void moby_start_screen_effect_state(int);
extern void group_activate_waiting_members(int,float);
extern int weapon_select_aim_target(char *,int,float,float,int,int);
extern void euler_rotation_basis(char *,char *);
extern const float g_yeedil_boss_scale __attribute__((sda));
extern const float g_yeedil_boss_init_value __attribute__((sda));
extern char g_request_l20_queue[];

/* Sets up the big enemy when it first appears and handles its health. It reacts to hits, switches phase at low health and starts the death sequence. (PAL) */
void yeedil_boss_init_damage_pal(char *obj) {
 char *vars=*(char **)(obj+0x68), *effect;
 float health, strength;
 if (*(u8 *)(obj+0x20)==0) {
  *(int *)(vars+0x1854)=-1;
  *(short *)(obj+0x32)=255; *(u8 *)(obj+0x30)=255;
  { float scale=level_interpolate_by_counter(5,20,1.0f,0.5f);
  *(float *)(vars+0x20)=*(float *)(vars+0x20)*scale;
  *(short *)(vars+0x24)=FloatToInt((float)*(short *)(vars+0x24)*scale); }
  *(float *)(vars+0x54)=0.5f; *(float *)(vars+0x50)=4.0f;
  *(float *)(vars+0xE0)=coll_probe_ground_height_below(obj+0x10,0,0.5f);
  *(float *)(vars+0x58)=2.0f; *(float *)(vars+0x5C)=2.0f;
  *(float *)(vars+0x60)=3.1415927f; *(int *)(vars+0x184C)=15;
  health=IntToFloat(*(short *)(vars+0x24));
  *(float *)(vars+0x1828)=(2.0f-(float)*(int *)(vars+0x182C))*(health*0.33333f);
  yeedil_boss_init_group(obj); yeedil_boss_disable_hazards(obj,0);
  *(float *)(obj+0x18)+=5.0f;
  *(float *)(obj+0x18)=coll_probe_ground_height_below(obj+0x10,0,0.5f);
  *(u16 *)(obj+0x34)|=0x400; *(int *)(obj+0x9C)=2;
  moby_set_state(obj,24,6);
  if (*(u8 *)(obj+0x43)!=1) anim_start_blended_pal(obj,1,0,0);
  *(u8 *)(vars+0x48)=FloatToInt(15.0f);
  *(u8 *)(vars+0x4A)=FloatToInt(12.8f);
  *(u16 *)(obj+0x34)|=0x1000;
  qcopy(vars+0x17E0,obj+0x10);
 }
 if (*(u8 *)(obj+0x95)==6) return;
 *(float *)(obj+0x2C)=*(float *)(*(char **)(obj+0x24)+0x24)*g_yeedil_boss_scale;
 *(float *)(vars+0x30)=g_yeedil_boss_init_value;
 effect=part_find_owned_effect_slot(obj,0x10000,0);
 if(effect && (effect=*(char **)(effect+0x20))) {
  switch (*(short *)(effect+0xAA)) { case 0x5DE: case 0x3A6: case 0xD0F: *(u8 *)(obj+0xA8)=255; }
 }
 strength=moby_update_aim_target_strength_pal(obj,part_find_owned_effect_slot(obj,0x10000,0));
 ApproachValue(vars+0x20,0.0f,strength); *(u8 *)(obj+0xA8)=255;
 health=*(float *)(vars+0x20);
 if(health<=0.0f || *(u8 *)(vars+0x2E)==2) {
  *(float *)(vars+0x20)=0.0f;
  if(!req_push_queue(g_request_l20_queue,0xA1)) goto done;
  if(*(u8 *)(vars+0x2E)!=2) SetDeathBits_pal(obj,0,3);
  req_push_queue(g_request_l20_queue,0xA0); req_launch_queued(g_request_l20_queue);
  moby_set_state(obj,17,6); game_set_stored_value_pair(moby_start_screen_effect_state,obj);
 } else if(health<=*(float *)(vars+0x1828)) {
  moby_set_state(obj,15,5); ++*(int *)(vars+0x182C);
  health=IntToFloat(*(short *)(vars+0x24));
  *(float *)(vars+0x1804)=0.0f; *(float *)(vars+0x1800)=0.0f;
  *(float *)(vars+0x1828)=(2.0f-(float)*(int *)(vars+0x182C))*(health*0.33333f);
  if(*(int *)(vars+0x182C)==2) group_activate_waiting_members(*(int *)(vars+0x244),-1.0f);
 } else if(strength!=0.0f && (effect=*(char **)(vars+0x38)) && *(short *)(effect+0xAA)==0x12D3) {
  moby_set_state(obj,15,5); *(float *)(vars+0x1804)=0.0f; *(float *)(vars+0x1800)=0.0f; *(u8 *)(obj+0xBC)=1;
 }
done:
 *(u8 *)(vars+0x2E)=1;
 weapon_select_aim_target(obj,*(int *)(vars+0x220),64.0f,0.0f,0,0);
 qcopy(obj+0x10,vars+0x17E0);
 if(*(float *)(obj+0xF0)!=0.0f || *(float *)(obj+0xF4)!=0.0f) {
  *(float *)(obj+0xF4)=0.0f; *(float *)(obj+0xF0)=0.0f; euler_rotation_basis(obj+0xC0,obj+0xF0);
 }
}
