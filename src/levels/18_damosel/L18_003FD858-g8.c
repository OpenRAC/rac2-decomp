#include "common.h"
extern int D_L18_001B2348[] __attribute__((sda));
extern u8 *D_L18_001B281C;
extern u8 D_00189EA0[];
extern void func_00282F20(void *,void *,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_002A7750(void *,int,int);
extern int func_002B38B8(void *);
extern int func_L18_003FDAB8(u8 *,u8 *);
extern int func_L18_003FDD68(u8 *,u8 *);
#define W(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
/* Slides the object along a straight line in one of two directions, switching
   direction when a trigger fires or the hero's presence changes. */
void func_L18_003FD858(u8 *moby) {
 u8 *vars=*(u8 **)(moby+0x68);
 switch(moby[0x20]) {
 case 0:
  qcopy(vars+0x40,moby+0x10);
  W(vars,0x6c)=(int)(F(vars,0x60)/(F(vars,0x64)*0.0166666675f));
  vec_scale_to_length(vars+0x50,vars+0x30,F(vars,0x60)/(float)W(vars,0x6c));
  SetMobyState(moby,1,-1);
  W(vars,0x68)=0; W(vars,0x74)=0;
  break;
 case 1:
  if(W(vars,0x68)>=2) {
   FastVecSub(moby+0x10,moby+0x10,vars+0x50);
   W(vars,0x68)--;
  } else if(W(vars,0x68)>0) {
   qcopy_nc(moby+0x10,vars+0x40); W(vars,0x68)--;
  }
  if(!(D_L18_001B2348[0]&15)) {
   if(CheckDoorOpenCondition(moby,W(vars,0x70)!=-1?gMobyTable_L18+(W(vars,0x70)<<8)+0x10:gHeroPosition))
    SetMobyState(moby,2,-1);
  }
  if(IsThirdPendingFlagSet(moby)) { moby[0xbe]&=0xfb; SetMobyState(moby,2,-1); }
  break;
 case 2:
  if(W(vars,0x68)<W(vars,0x6c)) {
   FastVecAdd(moby+0x10,moby+0x10,vars+0x50); W(vars,0x68)++;
  }
  if(!(D_L18_001B2348[0]&15)) {
   if(CheckDoorCloseCondition(moby,W(vars,0x70)!=-1?gMobyTable_L18+(W(vars,0x70)<<8)+0x10:gHeroPosition))
    SetMobyState(moby,1,-1);
  }
  if(IsThirdPendingFlagSet(moby)) { moby[0xbe]&=0xfb; SetMobyState(moby,1,-1); }
  break;
 }
 if(*(u16 *)(moby+0x96)<=0xfffe) ++*(u16 *)(moby+0x96);
}
