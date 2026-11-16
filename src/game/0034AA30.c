#include "names.h"
/* Updates the HUD bar range, position, visibility and colors. */
#include "common.h"
extern void object_set_flag_value(char *,int);
typedef struct { float x, y, z, w; } UiCoordinates;
extern UiCoordinates *object_get_first_field(char *);
extern void meter_set_max(char *,int),meter_set_value(char *,int);
extern void object_set_first_pair(char *,unsigned,unsigned),object_set_second_pair(char *,unsigned,unsigned);
extern void stub_empty_31(int *,int *,int *);
extern int g_player_stats MACRO_ADDR, g_experience_points MACRO_ADDR;
typedef struct { char pad[0x22b4]; unsigned char mode; char gap[0x277]; int end, start; } StatusGlobals;
extern StatusGlobals g_hero_state;
extern float ref_L00_0034AA30_00 MACRO_ADDR,ref_L00_0034AA30_02 MACRO_ADDR;
extern const float ref_L00_0034AA30_01 MACRO_ADDR;
extern int ref_L00_0034AA30_03 MACRO_ADDR;
void hud_meter_bar_update(char *hud)
{
 UiCoordinates *out=object_get_first_field(hud+0xf4);
 if(g_player_stats<80) {
  struct { int a,b,c; } range;
  float y, scale, offsetY;
  int iy;
  int mode;
  object_set_flag_value(hud+0xf4,1);
  range.c=0;range.a=g_hero_state.start;range.b=g_hero_state.end;
  if(!range.a)stub_empty_31(&range.a,&range.b,&range.c);
  meter_set_max(hud+0xf4,range.b-range.a);
  meter_set_value(hud+0xf4,(g_experience_points>>5)-range.a);
  out->x=ref_L00_0034AA30_00+(*(UiCoordinates **)(hud+8))->x;
  scale=ref_L00_0034AA30_02;
  mode=ref_L00_0034AA30_03;
  offsetY=ref_L00_0034AA30_01;
  y=(offsetY+(*(UiCoordinates **)(hud+8))->y)*scale+0.5f;
  if(mode==1)iy=(int)(y+-5.0f);
  else iy=(int)y;
  out->y=iy;
  if(g_hero_state.mode==1) {
   object_set_first_pair(hud+0xf4,0x60808080,0x60808080);
   object_set_second_pair(hud+0xf4,0x40808080,0x40808080);
  } else {
   object_set_first_pair(hud+0xf4,0x8049c1ff,0x80001eff);
   object_set_second_pair(hud+0xf4,0x50f0c070,0x50f0c070);
  }
 } else object_set_flag_value(hud+0xf4,0);
}
