#include "common.h"
extern int g_current_map_index __attribute__((sda));
extern char g_moby_nibble_table[];
extern void moby_increment_saved_switch_counter(char *), moby_hide_with_linked_parts(char *);
extern void moby_set_state_in_list(int,int);
extern struct { char pad[0x464]; unsigned char disabled[0]; } g_level_save_state_backup;
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
extern unsigned char g_moby_group_flags[];
extern u8 g_player_stats[] __attribute__((sda));
extern int CarryLevelIndex SDATA(D_001A79F0);
extern int g_teleporter_timer MACRO_ADDR;
extern int CarryMode SDATA(D_L01_001A8FF4) __attribute__((sda));
extern int g_teleporter_mode SDATA(D_L01_001A8FF0);
extern int g_pad_held_flags;
extern char *g_moby_l01_table MACRO_ADDR;
extern float g_teleporter_step_rate_a SDATA(D_L01_001AF588);
extern float g_teleporter_step_rate_b SDATA(D_L01_001AF58C);
extern float g_teleporter_step_rate_c SDATA(D_L01_001AF590);
extern void DrawShrinkingMobyRings(char *);
extern int IsPointInCuboid(void *, int);
extern void moby_show_with_linked_parts(char *), level_apply_table_entry(char *), moby_position_carried_objects(char *);
extern void moby_set_state(char *, int, int);
extern char *CreateMoby(int);
extern float FastAddRotations(float, float);
extern int PlayMobySound(int, int, char *);
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
void teleporter_l01_update_pal(char *m)
{
 CarryData *d = *(CarryData **)(m+0x68);
 int done=0, i, result;
 char **p;
 float v[4];
 unsigned short flags = *(u16 *)(m+0xB2);
 if (g_level_save_state_backup.disabled[(short)flags]) goto completed;
 {
  int c = (u8)g_moby_nibble_table[((short)flags>>1)+(g_current_map_index<<10)];
  if (flags&1) { if ((c>>4)&7) goto completed; }
  else if(c&7) goto completed;
  goto flags_checked;
completed:
  done=1;
 }
flags_checked:
 done=!!done;
 if (d->event!=-1 && !done && IsPointInCuboid(g_hero_position,d->event)) {
  done=1; moby_increment_saved_switch_counter(m); moby_show_with_linked_parts(m);
  if (*(u8 *)(m+0x20)==5) moby_set_state(m,1,-1);
 }
 if (d->x3C) {
  if (!g_player_stats[0xA]) {
   *(u16 *)(m+0x34)|=0x41;
   *(int *)(m+0x98)=0;
   return;
  }
  *(int *)(m+0x98)=*(int *)(*(char **)(m+0x24)+0x10);
  *(u16 *)(m+0x34)&=0xFFBE;
 }
 if (*(u16 *)(m+0x96)<0x7FFD) ++*(u16 *)(m+0x96);
 switch (*(u8 *)(m+0x20)) {
 case 0: {
  int i;
  char **p;
  *(u8 *)(m+0x30)=255;
  for(i=0;i<3;i++) {
   char **p=d->children+i;
   *p=CreateMoby(0x13B);
   if(*p) {
    *(u16 *)(*p+0x32)=0x40; *(u8 *)(*p+0x31)=1;
    *(u64 *)(*p+0x38)=*(u64 *)(g_hero_state.model+0x38);
    *(u16 *)(*p+0x34)=*(u16 *)(m+0x34);
    qcopy_nc(*p+0x10, m+0x10);
    qcopy_nc(*p+0xF0, m+0xF0);
    *(u8 *)(*p+0x30)=*(u8 *)(m+0x30);
    if(*(char **)(*p+0x68)) **(char ***)(*p+0x68)=m;
    *(float *)(*p+0xF8)=FastAddRotations(*(float *)(*p+0xF8),i*2.0943954f);
   }
  }
  if(d->x38||done) moby_set_state(m,6,-1);
  else { moby_set_state(m,5,-1); moby_hide_with_linked_parts(m); }
  {
  moby_position_carried_objects(m);
  break;
}
 }
 case 6:
  if(*(u8 *)(m+0x21)!=255) moby_set_state_in_list(*(u8 *)(m+0x21),1);
  moby_set_state(m,1,-1);
  
 case 1:
  if(d->unlock>=0 && !(g_moby_group_flags[d->unlock+(CarryLevelIndex<<4)]&0x80)) break;
  if(d->target==-1 || g_hero_state.mode==2 || g_hero_state.linked!=m || g_hero_state.control) break;
  if(d->x50) {
   d->x50=!g_hero_state.busy;
   g_teleporter_timer=4; g_teleporter_mode=2;
  } else level_apply_table_entry(m);
  if(!(g_pad_held_flags&0x10)) break;
  PlayMobySound(0,0,m); moby_set_state(m,2,-1);
  d->x2C=0; d->x30=-1; d->x28=0;
  hero_start_target_state(m+0x10,0,*(float *)(m+0xF8));
  coll_sweep_from_object(m,m+0x10,0x10000,0,1,0,1.5f,20.0f,1.0f);
  break;
 case 7:
  if(d->x20<1.0f) {
   math_step_value_toward_target(&d->x20,&d->x28,1.0f,g_teleporter_step_rate_a*0.000400000019f,g_teleporter_step_rate_b*0.000400000019f,g_teleporter_step_rate_c*0.0200000014f);
  } else if(d->x24<1.0f) {
   math_step_value_toward_target(&d->x24,&d->x2C,1.0f,g_teleporter_step_rate_a*0.000400000019f,g_teleporter_step_rate_b*0.000400000019f,g_teleporter_step_rate_c*0.0200000014f);
  } else {
   PlayMobySound(1,0,m); moby_set_state(m,8,-1); d->x34=0;
  }
  {
  moby_position_carried_objects(m);
  break;
}
 case 2:
  result=hero_get_target_state_kind();
  if(d->x20<1.0f) {
   math_step_value_toward_target(&d->x20,&d->x28,1.0f,g_teleporter_step_rate_a*0.000400000019f,g_teleporter_step_rate_b*0.000400000019f,g_teleporter_step_rate_c*0.0200000014f);
  } else {
   int mode = CarryMode;
   if(d->x24<1.0f) {
   math_step_value_toward_target(&d->x24,&d->x2C,1.0f,g_teleporter_step_rate_a*0.000400000019f,g_teleporter_step_rate_b*0.000400000019f,g_teleporter_step_rate_c*0.0200000014f);
  } else if(!(mode==4 && d->x20>0.25f)) {
   if(result==2) { d->x34=1.95f; moby_set_state(m,3,-1); }
   else if(!result) moby_set_state(m,4,-1);
   else if(*(u16 *)(m+0x96)>=301) { hero_set_move_state_by_speed(); d->x34=1.95f; moby_set_state(m,3,-1); }
   }
  }
  moby_position_carried_objects(m);
  break;
 case 3:
  if(d->x34!=0) {
   gfx_add_draw_callback_first(DrawShrinkingMobyRings,m); ApproachValue(&d->x34,0.0f,0.0800000057f); break;
  } else {
   char *other=g_moby_l01_table+(d->target<<8);
   CarryData *od=*(CarryData **)(other+0x68);
   qcopy_nc(v, other+0x10); v[2]+=0.2f;
   if(d->x4C!=-1) load_scene_chunk(d->x4C,od->x40);
   hero_reset_position_and_direction(v,other+0xF0,0,1);
   if(od->x48!=-1) cam_reset_entry(od->x48);
   script_queue_keyed_request(od->x40,od->x44);
   moby_set_state(other,4,-1);
   od->x28=0; od->x2C=0; od->x34=0;
   od->x24=od->x20=1; od->x50=1;
   PlayMobySound(1,0,other); moby_set_state(m,1,-1);
   d->x2C=d->x28=d->x24=d->x20=0;
   d->x34=1.95f; moby_position_carried_objects(m);
  }
  break;
 case 4: case 8:
  if(flag_set_first_pending(m)) {
   p=d->children;
   for(i=2;i>=0;i--,p++) if(*p) *(u16 *)(*p+0x34)&=0xFF7F;
  }
  if(d->x34<1.95f) {
   gfx_add_draw_callback_first(DrawShrinkingMobyRings,m); ApproachValue(&d->x34,1.95f,0.0800000057f);
  } else if(d->x24>0) {
   math_step_value_toward_target(&d->x24,&d->x28,0.0f,g_teleporter_step_rate_a*0.000400000019f,g_teleporter_step_rate_b*0.000400000019f,g_teleporter_step_rate_c*0.0200000014f);
  } else if(d->x20>0) {
   math_step_value_toward_target(&d->x20,&d->x2C,0.0f,g_teleporter_step_rate_a*0.000400000019f,g_teleporter_step_rate_b*0.000400000019f,g_teleporter_step_rate_c*0.0200000014f);
  } else moby_set_state(m,1,-1);
  moby_position_carried_objects(m);
 }
 ;
}

