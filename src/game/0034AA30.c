/* Updates the HUD bar range, position, visibility and colors. */
#include "common.h"
extern void func_00335E68(char *,int);
typedef struct { float x, y, z, w; } UiCoordinates;
extern UiCoordinates *func_00335E10(char *);
extern void func_00336B90(char *,int),func_00336B98(char *,int);
extern void func_00336498(char *,unsigned,unsigned),func_003364B0(char *,unsigned,unsigned);
extern void func_0026F808(int *,int *,int *);
extern int D_001A7A00 MACRO_ADDR, D_001A7A0C MACRO_ADDR;
typedef struct { char pad[0x22b4]; unsigned char mode; char gap[0x277]; int end, start; } StatusGlobals;
extern StatusGlobals D_00189E20;
extern float ref_L00_0034AA30_00 MACRO_ADDR,ref_L00_0034AA30_02 MACRO_ADDR;
extern const float ref_L00_0034AA30_01 MACRO_ADDR;
extern int ref_L00_0034AA30_03 MACRO_ADDR;
void func_0034AA30(char *hud)
{
 UiCoordinates *out=GetFirstField(hud+0xf4);
 if(D_001A7A00<80) {
  struct { int a,b,c; } range;
  float y, scale, offsetY;
  int iy;
  int mode;
  SetFlagValue(hud+0xf4,1);
  range.c=0;range.a=gHeroState.start;range.b=gHeroState.end;
  if(!range.a)EmptyStubF808(&range.a,&range.b,&range.c);
  SetMeterMaximum(hud+0xf4,range.b-range.a);
  SetMeterValue(hud+0xf4,(D_001A7A0C>>5)-range.a);
  out->x=ref_L00_0034AA30_00+(*(UiCoordinates **)(hud+8))->x;
  scale=ref_L00_0034AA30_02;
  mode=ref_L00_0034AA30_03;
  offsetY=ref_L00_0034AA30_01;
  y=(offsetY+(*(UiCoordinates **)(hud+8))->y)*scale+0.5f;
  if(mode==1)iy=(int)(y+-5.0f);
  else iy=(int)y;
  out->y=iy;
  if(gHeroState.mode==1) {
   SetFirstPair(hud+0xf4,0x60808080,0x60808080);
   SetSecondPair(hud+0xf4,0x40808080,0x40808080);
  } else {
   SetFirstPair(hud+0xf4,0x8049c1ff,0x80001eff);
   SetSecondPair(hud+0xf4,0x50f0c070,0x50f0c070);
  }
 } else SetFlagValue(hud+0xf4,0);
}
