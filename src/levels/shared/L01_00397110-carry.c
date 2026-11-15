#include "common.h"
extern int g_current_map_index __attribute__((sda));
extern char D_0019B4A8[];
extern void moby_increment_saved_switch_counter(char *), moby_hide_with_linked_parts(char *);
extern void moby_set_state_in_list(int,int);
extern struct { char pad[0x464]; unsigned char disabled[0]; } D_L01_0021E4B0;
extern char g_hero_position[];
typedef struct {
 char pad0[0x33C];
 char *linked;
 char pad340[0xE];
 short control;
 char pad350[0x1F40];
 char *model;
 int busy;
 char pad2298[0x1C];
 unsigned char mode;
} CarryHero;
extern CarryHero g_hero_state;
extern unsigned char D_0019B2E8[];
extern u8 D_001A7A00[] __attribute__((sda));
extern int CarryLevelIndex SDATA(D_001A79F0);
extern int D_L01_001A8FF4 MACRO_ADDR;
extern int CarryMode SDATA(D_L01_001A8FF4) __attribute__((sda));
extern int D_L01_001A8FF0 SDATA(D_L01_001A8FF0);
extern int D_00138324;
extern char *g_moby_l01_table MACRO_ADDR;
extern float D_L01_001AF588 SDATA(D_L01_001AF588);
extern float D_L01_001AF58C SDATA(D_L01_001AF58C);
extern float D_L01_001AF590 SDATA(D_L01_001AF590);
extern void DrawShrinkingMobyRings(char *);
extern int IsPointInCuboid(void *, int);
extern void moby_show_with_linked_parts(char *), level_apply_table_entry(char *), moby_position_carried_objects(char *);
extern void moby_set_state(char *, int, int);
extern char *CreateMoby(int);
extern float FastAddRotations(float, float);
extern void PlayMobySound(int, int, char *);
extern void hero_start_target_state(void *, int, float);
extern int coll_sweep_from_object(char *, void *, int, int, int, int, float, float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern int hero_get_target_state_kind(void);
extern void hero_set_move_state_by_speed(void);
extern void gfx_add_draw_callback_first(void *, char *);
extern float ApproachValue(void *, float, float);
extern void load_scene_chunk(int, int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void cam_reset_entry(int);
extern void script_queue_keyed_request(int, int);
extern int flag_set_first_pending(char *);
typedef struct {
 int target, event, unlock, unk0C, unk10;
 char *children[3];
 float x20, x24, x28, x2C;
 int x30;
 float x34;
 int x38, x3C, x40, x44, x48, x4C, x50;
} CarryData;
/* Updates the Teleporter: spawns three spinning child objects, waits for the hero to press the button at the pad, then moves the hero to the linked teleporter. */
void teleporter_l01_update(char *moby)
{
 CarryData *vars = *(CarryData **)(moby+0x68);
 int done=0, i, result;
 char **p;
 float v[4];
 unsigned short flags = *(u16 *)(moby+0xB2);
 if (D_L01_0021E4B0.disabled[(short)flags]) goto completed;
 {
  int savedBits = (u8)D_0019B4A8[((short)flags>>1)+(g_current_map_index<<10)];
  if (flags&1) { if ((savedBits>>4)&7) goto completed; }
  else if(savedBits&7) goto completed;
  goto flags_checked;
completed:
  done=1;
 }
flags_checked:
 done=!!done;
 if (vars->event!=-1 && !done && IsPointInCuboid(g_hero_position,vars->event)) {
  done=1; moby_increment_saved_switch_counter(moby); moby_show_with_linked_parts(moby);
  if (*(u8 *)(moby+0x20)==5) moby_set_state(moby,1,-1);
 }
 if (vars->x3C) {
  if (!D_001A7A00[0xA]) {
   *(u16 *)(moby+0x34)|=0x41;
   *(int *)(moby+0x98)=0;
   return;
  }
  *(int *)(moby+0x98)=*(int *)(*(char **)(moby+0x24)+0x10);
  *(u16 *)(moby+0x34)&=0xFFBE;
 }
 if (*(u16 *)(moby+0x96)<0x7FFD) ++*(u16 *)(moby+0x96);
 switch (*(u8 *)(moby+0x20)) {
 case 0: {
  int i;
  char **p;
  *(u8 *)(moby+0x30)=255;
  for(i=0;i<3;i++) {
   char **p=vars->children+i;
   *p=CreateMoby(0x13B /* moby class 315 */);
   if(*p) {
    *(u16 *)(*p+0x32)=0x40; *(u8 *)(*p+0x31)=1;
    *(u64 *)(*p+0x38)=*(u64 *)(g_hero_state.model+0x38);
    *(u16 *)(*p+0x34)=*(u16 *)(moby+0x34);
    qcopy_nc(*p+0x10, moby+0x10);
    qcopy_nc(*p+0xF0, moby+0xF0);
    *(u8 *)(*p+0x30)=*(u8 *)(moby+0x30);
    if(*(char **)(*p+0x68)) **(char ***)(*p+0x68)=moby;
    *(float *)(*p+0xF8)=FastAddRotations(*(float *)(*p+0xF8),i*2.0943954f);
   }
  }
  if(vars->x38||done) moby_set_state(moby,6,-1);
  else { moby_set_state(moby,5,-1); moby_hide_with_linked_parts(moby); }
  {
  moby_position_carried_objects(moby);
  break;
}
 }
 case 6:
  if(*(u8 *)(moby+0x21)!=255) moby_set_state_in_list(*(u8 *)(moby+0x21),1);
  moby_set_state(moby,1,-1);
  
 case 1:
  if(vars->unlock>=0 && !(D_0019B2E8[vars->unlock+(CarryLevelIndex<<4)]&0x80)) break;
  if(vars->target==-1 || g_hero_state.mode==2 || g_hero_state.linked!=moby || g_hero_state.control) break;
  if(vars->x50) {
   vars->x50=!g_hero_state.busy;
   D_L01_001A8FF4=4; D_L01_001A8FF0=2;
  } else level_apply_table_entry(moby);
  if(!(D_00138324&0x10)) break;
  PlayMobySound(0,0,moby); moby_set_state(moby,2,-1);
  vars->x2C=0; vars->x30=-1; vars->x28=0;
  hero_start_target_state(moby+0x10,0,*(float *)(moby+0xF8));
  coll_sweep_from_object(moby,moby+0x10,0x10000,0,1,0,1.5f,20.0f,1.0f);
  break;
 case 7:
  if(vars->x20<1.0f) {
   math_step_value_toward_target(&vars->x20,&vars->x28,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else if(vars->x24<1.0f) {
   math_step_value_toward_target(&vars->x24,&vars->x2C,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else {
   PlayMobySound(1,0,moby); moby_set_state(moby,8,-1); vars->x34=0;
  }
  {
  moby_position_carried_objects(moby);
  break;
}
 case 2:
  result=hero_get_target_state_kind();
  if(vars->x20<1.0f) {
   math_step_value_toward_target(&vars->x20,&vars->x28,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else {
   int mode = CarryMode;
   if(vars->x24<1.0f) {
   math_step_value_toward_target(&vars->x24,&vars->x2C,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else if(!(mode==4 && vars->x20>0.25f)) {
   if(result==2) { vars->x34=1.95f; moby_set_state(moby,3,-1); }
   else if(!result) moby_set_state(moby,4,-1);
   else if(*(u16 *)(moby+0x96)>=361) { hero_set_move_state_by_speed(); vars->x34=1.95f; moby_set_state(moby,3,-1); }
   }
  }
  moby_position_carried_objects(moby);
  break;
 case 3:
  if(vars->x34!=0) {
   gfx_add_draw_callback_first(DrawShrinkingMobyRings,moby); ApproachValue(&vars->x34,0.0f,0.06666667f); break;
  } else {
   char *linkedMoby=g_moby_l01_table+(vars->target<<8);
   CarryData *linkedVars=*(CarryData **)(linkedMoby+0x68);
   qcopy_nc(v, linkedMoby+0x10); v[2]+=0.2f;
   if(vars->x4C!=-1) load_scene_chunk(vars->x4C,linkedVars->x40);
   hero_reset_position_and_direction(v,linkedMoby+0xF0,0,1);
   if(linkedVars->x48!=-1) cam_reset_entry(linkedVars->x48);
   script_queue_keyed_request(linkedVars->x40,linkedVars->x44);
   moby_set_state(linkedMoby,4,-1);
   linkedVars->x28=0; linkedVars->x2C=0; linkedVars->x34=0;
   linkedVars->x24=linkedVars->x20=1; linkedVars->x50=1;
   PlayMobySound(1,0,linkedMoby); moby_set_state(moby,1,-1);
   vars->x2C=vars->x28=vars->x24=vars->x20=0;
   vars->x34=1.95f; moby_position_carried_objects(moby);
  }
  break;
 case 4: case 8:
  if(flag_set_first_pending(moby)) {
   p=vars->children;
   for(i=2;i>=0;i--,p++) if(*p) *(u16 *)(*p+0x34)&=0xFF7F;
  }
  if(vars->x34<1.95f) {
   gfx_add_draw_callback_first(DrawShrinkingMobyRings,moby); ApproachValue(&vars->x34,1.95f,0.06666667f);
  } else if(vars->x24>0) {
   math_step_value_toward_target(&vars->x24,&vars->x28,0.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else if(vars->x20>0) {
   math_step_value_toward_target(&vars->x20,&vars->x2C,0.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else moby_set_state(moby,1,-1);
  moby_position_carried_objects(moby);
 }
 ;
}

