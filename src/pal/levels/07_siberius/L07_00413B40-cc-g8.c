#include "names.h"
/* func_PAL_L07_00413B40, the PAL copy of func_L07_0040EC08: the same C, where rename func_L07_0040F0D0 becomes func_PAL_L07_00414008; rename func_L00_002B30E8 becomes func_PAL_L00_002B3000. */
/* func_PAL_L07_00413B40: the five path riders' update (Siberius). A unit of its own for -G8 and
 * -frac2-frame-pointer-liveness (config/cflags.txt): without the option flow keeps $fp, which
 * holds the rider index here, live after the loop, and reorg annuls the slot of the first
 * player-mode test (bnel where retail has bne, docs/build/compiler-notes.md). */
#include "common.h"
extern f32 ApproachValue(void *,f32,f32);
extern s32 PlayMobySound(s32,s32,void *);
extern void path_sample_position(void *,s32,void *,void *,s32,f32);
extern void path_compute_heading_and_tilt(void *,f32,void *,f32);
extern void func_002A0F48(void *);
extern f32 FastAddRotations(f32,f32);
extern void FastVecSub(void *,void *,void *);
extern void mat_combine_and_store(void *,void *,void *,void *);
extern void snow_emitter_update_effect(f32);
extern void cam_mode_noop(void *);
extern void swingshot_nodes_update_attached(void *);
extern void path_upload_points_to_world(void *,s32);
extern void moby_build_matrix(void *);
extern void ship_update_attached_parts_pal(void *);
extern void vec_transform_by_object_or_given(void *,void *,void *,s32);
extern void hero_record_play_counters_pal(void);
extern s32 *g_path_l07_table[];
extern u8 *g_snowfall_target_moby MACRO_ADDR;
extern u8 g_sound_state[];
extern u8 g_ship_sound_table[];
extern u8 g_hero_position_block[];
extern f32 g_ship_rider_height_step __attribute__((sda));
extern f32 g_ship_rider_turn_step __attribute__((sda));
extern f32 g_ship_rider_bend __attribute__((sda));
typedef struct {u8 pad[0x80];f32 pos[4];u8 rest[0x31c-0x90];f32 health;u8 pad320[0x33c-0x320];s32 mode;u8 pad340[0x3a0-0x340];u8 *object;} Player;
extern Player g_hero_state;
typedef struct {u8 pad[0xe0];f32 pathpos[5];u8 *objects[5];u8 pad108[0x1a0-0x108];f32 target;f32 speed;} State;
/* Moves the five path riders along their path every frame and updates their sounds and effects. Also handles the player standing on one of them (PAL: 50 Hz timings). */
void ship_move_riders_along_path_pal(u8 *moby)
{
 f32 old_position[4],old_rotation[4],delta[4],relative[4];
 s32 wheel,sound_id;
 f32 step,target,speed,bend;
 u8 *child,*child_vars;
 u8 *vars=*(u8 **)(moby+0x68),*sound_slot;
 s32 path_id=*(s32 *)(vars+0x90);
 s32 *path;
 State *ship_state=(State *)vars;
 g_snowfall_target_moby=0;
 path=g_path_l07_table[path_id];
 target=ship_state->target;
 speed=ship_state->speed;
 ApproachValue(vars+0x11c,target,speed);
 sound_slot=g_sound_state+*(s32 *)(vars+0x1ac)*0x70;
 if(*(u8 **)(sound_slot+0x88)!=moby || !sound_slot[0x74]) *(s32 *)(vars+0x1ac)=PlayMobySound(2,12,moby);
 sound_id=*(s32 *)(vars+0x1ac);
 if(sound_id!=-1) qcopy(g_ship_sound_table+sound_id*0x70,g_hero_position_block);
 {
 s32 i;
 for(i=0;i<5;i++) {
  child=ship_state->objects[i];
  child_vars=*(u8 **)(child+0x68);
  qcopy_nc(old_position,child+0x10);
  qcopy_nc(old_rotation,child+0xf0);
  path_sample_position(path,1,child+0x10,child+0xf0,0,ship_state->pathpos[i]);
  bend=g_ship_rider_bend;
  *(f32 *)(child+0x18)+=g_ship_rider_height_step;
  path_compute_heading_and_tilt(path,ship_state->pathpos[i],child+0xf0,bend);
  func_002A0F48(child);
  ship_state->pathpos[i]+=*(f32 *)(vars+0x11c);
  if(ship_state->pathpos[i]>=(f32)path[0]) ship_state->pathpos[i]-=(f32)path[0];
  step=g_ship_rider_turn_step*0.0003490659f;
  for(wheel=0;wheel<8;wheel++) *(f32 *)(child_vars+0x15b4+wheel*0x20)=FastAddRotations(*(f32 *)(child_vars+0x15b4+wheel*0x20),step);
  FastVecSub(delta,child+0x10,old_position);
  mat_combine_and_store(child_vars+0x20,delta,old_rotation,child+0xf0);
  if(g_hero_state.object==child || (*(u8 **)(child_vars+0x108) && g_hero_state.object==*(u8 **)(child_vars+0x108)) || (*(u8 **)(child_vars+0x10c) && g_hero_state.object==*(u8 **)(child_vars+0x10c))) {
   g_snowfall_target_moby=child;
   snow_emitter_update_effect(ship_state->pathpos[i]);
  }
  cam_mode_noop(child);
  swingshot_nodes_update_attached(child);
  path_upload_points_to_world(child,i);
  moby_build_matrix(child);
  if(*(s16 *)(child+0xaa)==0x11d9 || *(s16 *)(child+0xaa)==0x11db) ship_update_attached_parts_pal(child);
  if(g_snowfall_target_moby) {
   FastVecSub(relative,g_hero_state.pos,g_snowfall_target_moby+0x10);
   vec_transform_by_object_or_given(g_snowfall_target_moby,relative,relative,0);
   if(relative[2]<-3.0f && g_hero_state.mode==0) hero_record_play_counters_pal();
  }
  if(g_hero_state.mode==0 && g_hero_state.health<1.0f) hero_record_play_counters_pal();
 }
}
}
