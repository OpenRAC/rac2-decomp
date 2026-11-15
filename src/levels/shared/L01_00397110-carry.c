#include "common.h"
extern int D_001A79F0 __attribute__((sda));
extern char D_0019B4A8[];
extern void func_L01_00398008(char *), func_L01_00399098(char *);
extern void func_L01_003115E8(int,int);
extern struct { char pad[0x464]; unsigned char disabled[0]; } D_L01_0021E4B0;
extern char D_00189EA0[];
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
extern CarryHero D_00189E20;
extern unsigned char D_0019B2E8[];
extern u8 D_001A7A00[] __attribute__((sda));
extern int CarryLevelIndex SDATA(D_001A79F0);
extern int D_L01_001A8FF4 MACRO_ADDR;
extern int CarryMode SDATA(D_L01_001A8FF4) __attribute__((sda));
extern int D_L01_001A8FF0 SDATA(D_L01_001A8FF0);
extern int D_00138324;
extern char *D_L01_001B255C MACRO_ADDR;
extern float D_L01_001AF588 SDATA(D_L01_001AF588);
extern float D_L01_001AF58C SDATA(D_L01_001AF58C);
extern float D_L01_001AF590 SDATA(D_L01_001AF590);
extern void func_L01_00398B50(char *);
extern int func_002ACBC8(void *, int);
extern void func_L01_003990E8(char *), func_L01_00398A90(char *), func_L01_00398938(char *);
extern void func_002A7750(char *, int, int);
extern char *func_0029EFD0(int);
extern float func_00283B98(float, float);
extern void func_002E5CF8(int, int, char *);
extern void func_L00_002D40A0(void *, int, float);
extern int func_002A8C28(char *, void *, int, int, int, int, float, float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern int func_L00_002D40F0(void);
extern void func_L01_002C98B8(void);
extern void func_L00_002E6CF0(void *, char *);
extern float func_002AA2E8(void *, float, float);
extern void func_L00_00303530(int, int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L00_0042A500(int);
extern void func_L01_00323310(int, int);
extern int func_002B3868(char *);
typedef struct {
 int target, event, unlock, unk0C, unk10;
 char *children[3];
 float x20, x24, x28, x2C;
 int x30;
 float x34;
 int x38, x3C, x40, x44, x48, x4C, x50;
} CarryData;
/* Updates the Teleporter: spawns three spinning child objects, waits for the hero to press the button at the pad, then moves the hero to the linked teleporter. */
void func_L01_003980D0(char *moby)
{
 CarryData *vars = *(CarryData **)(moby+0x68);
 int done=0, i, result;
 char **p;
 float v[4];
 unsigned short flags = *(u16 *)(moby+0xB2);
 if (D_L01_0021E4B0.disabled[(short)flags]) goto completed;
 {
  int savedBits = (u8)D_0019B4A8[((short)flags>>1)+(gCurrentMapIndex<<10)];
  if (flags&1) { if ((savedBits>>4)&7) goto completed; }
  else if(savedBits&7) goto completed;
  goto flags_checked;
completed:
  done=1;
 }
flags_checked:
 done=!!done;
 if (vars->event!=-1 && !done && IsPointInCuboid(gHeroPosition,vars->event)) {
  done=1; IncrementSavedSwitchCounter(moby); ShowMobyAndLinkedParts(moby);
  if (*(u8 *)(moby+0x20)==5) SetMobyState(moby,1,-1);
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
    *(u64 *)(*p+0x38)=*(u64 *)(gHeroState.model+0x38);
    *(u16 *)(*p+0x34)=*(u16 *)(moby+0x34);
    qcopy_nc(*p+0x10, moby+0x10);
    qcopy_nc(*p+0xF0, moby+0xF0);
    *(u8 *)(*p+0x30)=*(u8 *)(moby+0x30);
    if(*(char **)(*p+0x68)) **(char ***)(*p+0x68)=moby;
    *(float *)(*p+0xF8)=FastAddRotations(*(float *)(*p+0xF8),i*2.0943954f);
   }
  }
  if(vars->x38||done) SetMobyState(moby,6,-1);
  else { SetMobyState(moby,5,-1); HideMobyAndLinkedParts(moby); }
  {
  PositionCarriedObjects(moby);
  break;
}
 }
 case 6:
  if(*(u8 *)(moby+0x21)!=255) SetMobyStateInList(*(u8 *)(moby+0x21),1);
  SetMobyState(moby,1,-1);
  
 case 1:
  if(vars->unlock>=0 && !(D_0019B2E8[vars->unlock+(CarryLevelIndex<<4)]&0x80)) break;
  if(vars->target==-1 || gHeroState.mode==2 || gHeroState.linked!=moby || gHeroState.control) break;
  if(vars->x50) {
   vars->x50=!gHeroState.busy;
   D_L01_001A8FF4=4; D_L01_001A8FF0=2;
  } else ApplyLevelTableEntry(moby);
  if(!(D_00138324&0x10)) break;
  PlayMobySound(0,0,moby); SetMobyState(moby,2,-1);
  vars->x2C=0; vars->x30=-1; vars->x28=0;
  StartHeroTargetState(moby+0x10,0,*(float *)(moby+0xF8));
  SweepCollisionFromObject(moby,moby+0x10,0x10000,0,1,0,1.5f,20.0f,1.0f);
  break;
 case 7:
  if(vars->x20<1.0f) {
   StepValueTowardTarget(&vars->x20,&vars->x28,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else if(vars->x24<1.0f) {
   StepValueTowardTarget(&vars->x24,&vars->x2C,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else {
   PlayMobySound(1,0,moby); SetMobyState(moby,8,-1); vars->x34=0;
  }
  {
  PositionCarriedObjects(moby);
  break;
}
 case 2:
  result=GetHeroTargetStateKind();
  if(vars->x20<1.0f) {
   StepValueTowardTarget(&vars->x20,&vars->x28,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else {
   int mode = CarryMode;
   if(vars->x24<1.0f) {
   StepValueTowardTarget(&vars->x24,&vars->x2C,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else if(!(mode==4 && vars->x20>0.25f)) {
   if(result==2) { vars->x34=1.95f; SetMobyState(moby,3,-1); }
   else if(!result) SetMobyState(moby,4,-1);
   else if(*(u16 *)(moby+0x96)>=361) { SetHeroMoveStateBySpeed(); vars->x34=1.95f; SetMobyState(moby,3,-1); }
   }
  }
  PositionCarriedObjects(moby);
  break;
 case 3:
  if(vars->x34!=0) {
   AddDrawCallbackToList1(DrawShrinkingMobyRings,moby); ApproachValue(&vars->x34,0.0f,0.06666667f); break;
  } else {
   char *linkedMoby=gMobyTable_L01+(vars->target<<8);
   CarryData *linkedVars=*(CarryData **)(linkedMoby+0x68);
   qcopy_nc(v, linkedMoby+0x10); v[2]+=0.2f;
   if(vars->x4C!=-1) LoadSceneChunk(vars->x4C,linkedVars->x40);
   ResetHeroPositionAndDirection(v,linkedMoby+0xF0,0,1);
   if(linkedVars->x48!=-1) ResetCameraEntry(linkedVars->x48);
   QueueKeyedRequest(linkedVars->x40,linkedVars->x44);
   SetMobyState(linkedMoby,4,-1);
   linkedVars->x28=0; linkedVars->x2C=0; linkedVars->x34=0;
   linkedVars->x24=linkedVars->x20=1; linkedVars->x50=1;
   PlayMobySound(1,0,linkedMoby); SetMobyState(moby,1,-1);
   vars->x2C=vars->x28=vars->x24=vars->x20=0;
   vars->x34=1.95f; PositionCarriedObjects(moby);
  }
  break;
 case 4: case 8:
  if(SetFirstPendingFlag(moby)) {
   p=vars->children;
   for(i=2;i>=0;i--,p++) if(*p) *(u16 *)(*p+0x34)&=0xFF7F;
  }
  if(vars->x34<1.95f) {
   AddDrawCallbackToList1(DrawShrinkingMobyRings,moby); ApproachValue(&vars->x34,1.95f,0.06666667f);
  } else if(vars->x24>0) {
   StepValueTowardTarget(&vars->x24,&vars->x28,0.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else if(vars->x20>0) {
   StepValueTowardTarget(&vars->x20,&vars->x2C,0.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else SetMobyState(moby,1,-1);
  PositionCarriedObjects(moby);
 }
 ;
}

