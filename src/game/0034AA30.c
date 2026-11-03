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
void func_0034AA30(char *o)
{
 UiCoordinates *out=func_00335E10(o+0xf4);
 if(D_001A7A00<80) {
  struct { int a,b,c; } range;
  float y, scale, offsetY;
  int iy;
  int mode;
  func_00335E68(o+0xf4,1);
  range.c=0;range.a=D_00189E20.start;range.b=D_00189E20.end;
  if(!range.a)func_0026F808(&range.a,&range.b,&range.c);
  func_00336B90(o+0xf4,range.b-range.a);
  func_00336B98(o+0xf4,(D_001A7A0C>>5)-range.a);
  out->x=ref_L00_0034AA30_00+(*(UiCoordinates **)(o+8))->x;
  scale=ref_L00_0034AA30_02;
  mode=ref_L00_0034AA30_03;
  offsetY=ref_L00_0034AA30_01;
  y=(offsetY+(*(UiCoordinates **)(o+8))->y)*scale+0.5f;
  if(mode==1)iy=(int)(y+-5.0f);
  else iy=(int)y;
  out->y=iy;
  if(D_00189E20.mode==1) {
   func_00336498(o+0xf4,0x60808080,0x60808080);
   func_003364B0(o+0xf4,0x40808080,0x40808080);
  } else {
   func_00336498(o+0xf4,0x8049c1ff,0x80001eff);
   func_003364B0(o+0xf4,0x50f0c070,0x50f0c070);
  }
 } else func_00335E68(o+0xf4,0);
}
