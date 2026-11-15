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
extern void func_PAL_L07_00414008(void *);
extern void vec_transform_by_object_or_given(void *,void *,void *,s32);
extern void func_PAL_L00_002B3000(void);
extern s32 *D_L07_001FDEC0[];
extern u8 *D_L07_001ADAAC MACRO_ADDR;
extern u8 g_sound_state[];
extern u8 D_001886F0[];
extern u8 D_L07_001B9200[];
extern f32 D_L07_001B1784 __attribute__((sda));
extern f32 D_L07_001B1788 __attribute__((sda));
extern f32 D_L07_001B1708 __attribute__((sda));
typedef struct {u8 pad[0x80];f32 pos[4];u8 rest[0x31c-0x90];f32 health;u8 pad320[0x33c-0x320];s32 mode;u8 pad340[0x3a0-0x340];u8 *object;} Player;
extern Player g_hero_state;
typedef struct {u8 pad[0xe0];f32 pathpos[5];u8 *objects[5];u8 pad108[0x1a0-0x108];f32 target;f32 speed;} State;
void func_PAL_L07_00413B40(u8 *obj)
{
 f32 oldpos[4],oldrot[4],delta[4],relative[4];
 s32 j,id;
 f32 step,target,speed,bend;
 u8 *child,*state;
 u8 *p=*(u8 **)(obj+0x68),*sound;
 s32 pathid=*(s32 *)(p+0x90);
 s32 *path;
 State *ps=(State *)p;
 D_L07_001ADAAC=0;
 path=D_L07_001FDEC0[pathid];
 target=ps->target;
 speed=ps->speed;
 ApproachValue(p+0x11c,target,speed);
 sound=g_sound_state+*(s32 *)(p+0x1ac)*0x70;
 if(*(u8 **)(sound+0x88)!=obj || !sound[0x74]) *(s32 *)(p+0x1ac)=PlayMobySound(2,12,obj);
 id=*(s32 *)(p+0x1ac);
 if(id!=-1) qcopy(D_001886F0+id*0x70,D_L07_001B9200);
 {
 s32 i;
 for(i=0;i<5;i++) {
  child=ps->objects[i];
  state=*(u8 **)(child+0x68);
  qcopy_nc(oldpos,child+0x10);
  qcopy_nc(oldrot,child+0xf0);
  path_sample_position(path,1,child+0x10,child+0xf0,0,ps->pathpos[i]);
  bend=D_L07_001B1708;
  *(f32 *)(child+0x18)+=D_L07_001B1784;
  path_compute_heading_and_tilt(path,ps->pathpos[i],child+0xf0,bend);
  func_002A0F48(child);
  ps->pathpos[i]+=*(f32 *)(p+0x11c);
  if(ps->pathpos[i]>=(f32)path[0]) ps->pathpos[i]-=(f32)path[0];
  step=D_L07_001B1788*0.0003490659f;
  for(j=0;j<8;j++) *(f32 *)(state+0x15b4+j*0x20)=FastAddRotations(*(f32 *)(state+0x15b4+j*0x20),step);
  FastVecSub(delta,child+0x10,oldpos);
  mat_combine_and_store(state+0x20,delta,oldrot,child+0xf0);
  if(g_hero_state.object==child || (*(u8 **)(state+0x108) && g_hero_state.object==*(u8 **)(state+0x108)) || (*(u8 **)(state+0x10c) && g_hero_state.object==*(u8 **)(state+0x10c))) {
   D_L07_001ADAAC=child;
   snow_emitter_update_effect(ps->pathpos[i]);
  }
  cam_mode_noop(child);
  swingshot_nodes_update_attached(child);
  path_upload_points_to_world(child,i);
  moby_build_matrix(child);
  if(*(s16 *)(child+0xaa)==0x11d9 || *(s16 *)(child+0xaa)==0x11db) func_PAL_L07_00414008(child);
  if(D_L07_001ADAAC) {
   FastVecSub(relative,g_hero_state.pos,D_L07_001ADAAC+0x10);
   vec_transform_by_object_or_given(D_L07_001ADAAC,relative,relative,0);
   if(relative[2]<-3.0f && g_hero_state.mode==0) func_PAL_L00_002B3000();
  }
  if(g_hero_state.mode==0 && g_hero_state.health<1.0f) func_PAL_L00_002B3000();
 }
}
}
