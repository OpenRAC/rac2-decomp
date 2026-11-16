#include "names.h"
/* func_PAL_L01_004221D8, the PAL copy of func_L01_0041C970: the same C, with 50 Hz timestep and angle constants. */
#include "common.h"

extern s32 moby_is_in_selected_zone(void *);
extern f32 func_PAL_L01_003BEB40(void);
extern f32 math_random_angle(void);
extern void moby_set_state(void *,s32,s32);
extern f32 math_ease_out_quad(f32);
extern void moby_scale_owner_words_by_angles(void *,void *,void *,f32,f32,f32);
extern void FastVecSub(void *,void *,void *);
extern void mat_combine_and_store(void *,void *,void *,void *);
extern f32 FastAddRotations(f32,f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 FastTweenColor(u32,u32,f32);
extern f32 FastVecDot(void *,void *);
extern f32 math_approach_with_velocity(void *,f32,void *,f32,f32,f32,s32);
extern void mat_transform_offset_two_matrices(void *,void *,void *,void *,void *);
typedef struct {
 u8 pad0[0x80]; f32 position[4];
 u8 pad90[0x33C-0x90]; void *platform;
 u8 pad340[0xE]; s16 flag34E;
 u8 pad350[0x229C-0x350]; s32 mode;
} UpdateHero;
extern UpdateHero g_hero_state NOT_SDA;
typedef int UpdateQuad __attribute__((mode(TI)));
extern f32 g_muckdweller_ease_offset __attribute__((sda));
extern f32 g_muckdweller_back_speed __attribute__((sda));
extern f32 g_muckdweller_forward_speed __attribute__((sda));
extern f32 g_muckdweller_unused_float_a __attribute__((sda));
extern f32 g_muckdweller_unused_float_b __attribute__((sda));
extern f32 g_muckdweller_scale_param __attribute__((sda));
extern f32 g_muckdweller_angle_x_degrees __attribute__((sda));
extern f32 g_muckdweller_angle_y_degrees __attribute__((sda));
extern f32 g_muckdweller_tilt_gain __attribute__((sda));
extern f32 g_muckdweller_side_gain __attribute__((sda));
extern f32 g_muckdweller_approach_accel_a __attribute__((sda));
extern f32 g_muckdweller_approach_accel_b __attribute__((sda));
extern f32 g_muckdweller_approach_accel_c __attribute__((sda));
extern f32 g_muckdweller_settle_accel_a __attribute__((sda));
extern f32 g_muckdweller_settle_accel_b __attribute__((sda));
extern f32 g_muckdweller_settle_accel_c __attribute__((sda));
typedef struct {
 u8 pad0[0x60];
 f32 field60;
 f32 field64;
 f32 field68;
 f32 field6C;
 u8 pad70[0x8];
 f32 field78;
 f32 field7C;
 f32 field80;
 f32 field84;
 u8 pad88[0x18];
 s32 fieldA0;
 u8 padA4[0x8];
 f32 fieldAC;
} State0041C970;
typedef struct {
 u8 pad0[0x10]; f32 position[4];
 u8 state; u8 slot; u8 pad22[2];
 struct ObjectClass0041C970 { u8 pad0[0x10]; s32 flags; } *classData;
 u8 pad28[4]; f32 field2C;
 u8 pad30; u8 field31; u8 pad32[2]; u16 flags34;
 u8 pad36[0xD]; u8 animation;
 u8 pad44[0x24]; State0041C970 *stateData;
 u8 pad6C[0xC]; u32 color;
 u8 pad7C[0x1C]; s32 collisionFlags;
 u8 pad9C[0x24]; f32 matrix[12]; f32 rotation[4];
} Object0041C970;
/* Tilting lift: initializes its height range, moves while the hero rides it,
 * and tilts toward the hero's offset projected on the object's axes. */
void func_PAL_L01_004221D8(Object0041C970 *obj) {
 f32 oldpos[4] __attribute__((aligned(16)));
 f32 oldrot[4] __attribute__((aligned(16)));
 f32 delta[4] __attribute__((aligned(16)));
 f32 local[4] __attribute__((aligned(16)));
 f32 oldstate[4] __attribute__((aligned(16)));
 f32 current[4] __attribute__((aligned(16)));
 f32 out[4] __attribute__((aligned(16)));
 State0041C970 *p;
 f32 height0, height1, height2, x, y, speed, scaledX;
 f32 timestep;
 s32 trigger;
 if(!moby_is_in_selected_zone(obj->position)) return;
 p=obj->stateData;
 qcopy(oldpos,obj->position);
 qcopy(oldrot,obj->rotation);
 switch(obj->state) {
 case 0:
  height0=func_PAL_L01_003BEB40();
  *(s32 *)((u8 *)p+0xAC)=0;
  if(height0>100.0f) {
   p->field78=math_random_angle();
   p->field7C=math_random_angle();
   p->field6C=obj->position[2]-height0;
   p->field60=p->field6C;
   p->field64=p->field6C-g_muckdweller_ease_offset;
   p->field68=0;
   qcopy((u8 *)p+0x80,obj->rotation);
   qzero((u8 *)p+0x90);
   if(!p->fieldA0) moby_set_state(obj,2,-1);
   else moby_set_state(obj,1,-1);
  }
  break;
 case 1:
  height1=func_PAL_L01_003BEB40();
  trigger=0;
  if(g_hero_state.mode==25 && p->field68<0.0f &&
     g_hero_state.position[2]>obj->position[2]-0.2f &&
     obj->position[2]<height1+0.1f) trigger=1;
  if((g_hero_state.platform==obj && !g_hero_state.flag34E) || trigger) {
   if(trigger) obj->collisionFlags=0;
   else obj->collisionFlags=obj->classData->flags;
   x=math_ease_out_quad((p->field6C-p->field64)/g_muckdweller_ease_offset);
   timestep=0.020000001f;
   p->field68=-(g_muckdweller_back_speed*timestep)*x;
  } else {
   obj->collisionFlags=obj->classData->flags;
   x=math_ease_out_quad((g_muckdweller_ease_offset-(p->field6C-p->field64))/g_muckdweller_ease_offset);
   timestep=0.020000001f;
   p->field68=g_muckdweller_forward_speed*(x*timestep);
  }
  p->field6C+=p->field68;
  obj->position[2]=height1+p->field6C;
  moby_scale_owner_words_by_angles(obj,(u8 *)p+0x78,(u8 *)p+0x7C,g_muckdweller_scale_param,g_muckdweller_angle_x_degrees*0.0003490659f,g_muckdweller_angle_y_degrees*0.0003490659f);
  FastVecSub(delta,obj->position,oldpos);
  mat_combine_and_store((u8 *)p+0x20,delta,oldrot,obj->rotation);
  break;
 case 2:
  if(obj->field31) {
   p->fieldAC=FastAddRotations(p->fieldAC,0.062831864f);
   obj->color=FastTweenColor(0xFFEEFC0E,0xF03B4004,math_fast_sin_or_cos_b(p->fieldAC)*0.5f+0.5f);
  }
  height2=func_PAL_L01_003BEB40();
  if(!g_hero_state.flag34E && g_hero_state.platform==obj) {
   FastVecSub(local,g_hero_state.position,obj->position);
   x=FastVecDot(local,obj->matrix);
   y=-g_muckdweller_tilt_gain * FastVecDot(local,obj->matrix+4);
   scaledX=g_muckdweller_side_gain*x;
   *(UpdateQuad *)oldstate=*(UpdateQuad *)((u8 *)p+0x80);
   *(UpdateQuad *)current=*(UpdateQuad *)(obj->position);
   math_approach_with_velocity((u8 *)p+0x80,y,(u8 *)p+0x90,g_muckdweller_approach_accel_a*1.44f,g_muckdweller_approach_accel_b*1.44f,g_muckdweller_approach_accel_c*1.2f,0);
   math_approach_with_velocity((u8 *)p+0x84,scaledX,(u8 *)p+0x94,g_muckdweller_approach_accel_a*1.44f,g_muckdweller_approach_accel_b*1.44f,g_muckdweller_approach_accel_c*1.2f,0);
   mat_transform_offset_two_matrices(g_hero_state.position,out,obj->position,oldstate,(u8 *)p+0x80);
  } else {
   math_approach_with_velocity((u8 *)p+0x80,0.0f,(u8 *)p+0x90,g_muckdweller_settle_accel_a*1.44f,g_muckdweller_settle_accel_b*1.44f,g_muckdweller_settle_accel_c*1.2f,0);
   math_approach_with_velocity((u8 *)p+0x84,0.0f,(u8 *)p+0x94,g_muckdweller_settle_accel_a*1.44f,g_muckdweller_settle_accel_b*1.44f,g_muckdweller_settle_accel_c*1.2f,0);
  }
  obj->position[2]=height2+p->field6C;
  moby_scale_owner_words_by_angles(obj,(u8 *)p+0x78,(u8 *)p+0x7C,g_muckdweller_scale_param,g_muckdweller_angle_x_degrees*0.0003490659f,g_muckdweller_angle_y_degrees*0.0003490659f);
  obj->rotation[0]=FastAddRotations(p->field80,obj->rotation[0]);
  obj->rotation[1]=FastAddRotations(p->field84,obj->rotation[1]);
  FastVecSub(delta,obj->position,oldpos);
  mat_combine_and_store((u8 *)p+0x20,delta,oldrot,obj->rotation);
  break;
 }
}
