/* func_003478F0 (1,452 bytes, 28 places): the menu grid. The layout scalars are declared yb, xs,
 * xb, ys; the row address is `(short *)((row << 2) * 10 + (int)ids)`, a pointer cast that only
 * sets one addu's operand order (allowed by owner ruling, 13 November 2026).
 * Own unit: -O2 -G8 -ffunction-sections -fno-rerun-loop-opt -frac2-pseudo-base -frac2-gcse-hash-171 -frac2-sched-elapsed-latency
 * (config/cflags.txt; docs/build/compiler-notes.md). Owner standard of 12 November 2026 for
 * the switches.
 */
#include "include_asm.h"
#include "names.h"
extern void func_00335E68(void *,int);
extern int func_00335E20(void *);
extern void func_00335E38(void *,float,float,float,float);
extern void func_00336320(void *),func_00336A78(void *),func_00336828(void *);
extern void func_00336920(void *,int,int);
typedef struct {int x,y;} MenuIntegerPair;
typedef struct {short a,b,c,id,e;} MenuGridEntry;
extern MenuGridEntry ref_00347468_10[];
extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_00139568[];
extern int D_00139868[],D_00139688[];
typedef struct { char pad0[0x3c]; unsigned short icon; char pad3e[0x2e]; int max; char pad70[0x18]; unsigned short ammo; char pad8a[0x56]; } MenuWeaponRecord;
extern MenuWeaponRecord ref_003478F0_04[];
extern void func_00336B90(void *,int),func_00336B98(void *,int);
extern void func_00336F20(int,int *,int *,int *);
extern void func_00336498(void *,int,int);
extern void func_00336548(void *);
extern int func_0026F7A0(void *);
extern void *ref_003478F0_05[];
extern void func_003472B8(void *),func_00347468(void *);
extern int ref_003478F0_00,ref_003478F0_01,ref_003478F0_02,ref_003478F0_03;
extern float ref_003478F0_06,ref_003478F0_07;
extern MenuIntegerPair ref_003478F0_08[],ref_003478F0_09[];
typedef struct {float x,y;} MenuFloatPair;
extern MenuFloatPair ref_003478F0_10[],ref_003478F0_11[];
/* Draws every slot of the item grid menu: the backdrop, the weapon icon, the ammo bar and the highlight on the selected item. */
void func_003478F0(char *menu)
{
 if(*(int *)(menu+0x4f8)) {
  int row,col;
  MenuGridEntry *gridEntries=ref_00347468_10;

  DrawScreenElementAtStoredPosition(menu);DrawScreenElementAtStoredPosition(menu+0x4c);DrawScreenElementAtStoredPosition(menu+0x130);
  for(row=0;row<6;row++) {
   short *idField=&gridEntries->id;
   short *idPtr=(short *)((row<<2)*10+(int)idField);
   for(col=0;col<4;col++,idPtr+=5) {

    { int *color=((int *)GetFieldC(menu+0x3b4));
      float yb=(float)ref_003478F0_01;
      float xs=ref_003478F0_06;
      float xb=(float)ref_003478F0_00;
      float ys=ref_003478F0_07;
      *color=0x60241700;
      SetFirstFloat4(menu+0x3b4,(xs*(float)col+xb)+(*(float **)(menu+0x498))[0],(ys*(float)row+yb)+(*(float **)(menu+0x498))[1],0.0f,0.0f);
    }
    *((int *)GetFieldC(menu+0x98))=0x30f0c070;
    *((int *)GetFieldC((menu+0x3b4)))=0x60241700;
    SetFlagValue((menu+0x1c8),0);SetFlagValue((menu+0x378),0);
    if(gItemOwnedFlags[*idPtr]) {
     MenuWeaponRecord *weapons=ref_003478F0_04;
     unsigned char *slots=gItemSlotToRecord;
     SetWidgetValuePair((menu+0x378),weapons[slots[*idPtr]].icon,0);

     SetFirstFloat4((menu+0x378),(53.5f*(float)col+(float)ref_003478F0_02)+(*(float **)(menu+0x498))[0],(47.0f*(float)row+(float)ref_003478F0_03)+(*(float **)(menu+0x498))[1],0.0f,0.0f);
     if(weapons[slots[*idPtr]].icon==0xea7e) {
      *((int *)GetFieldC((menu+0x378)))=0x80808080;
     } else {
      MenuIntegerPair base=ref_003478F0_08[0],stride=ref_003478F0_09[0];
      int barColorA,barColorB,color;
      SetMeterMaximum((menu+0x1c8),weapons[slots[*idPtr]].max);
      SetMeterValue((menu+0x1c8),D_00139868[*idPtr]>>5);

      SetFirstFloat4((menu+0x1c8),(float)(stride.x*col+base.x)+(*(float **)(menu+0x498))[0],(float)(stride.y*row+base.y)+(*(float **)(menu+0x498))[1],0.0f,0.0f);
      SetFlagValue((menu+0x1c8),1);
      barColorA=0;barColorB=0;color=0;
      ChooseItemColors(*idPtr,&barColorA,&barColorB,&color);SetFirstPair((menu+0x1c8),barColorA,barColorB);
      *((int *)GetFieldC((menu+0x378)))=color;
      if(weapons[slots[*idPtr]].max<=0) {SetMeterMaximum((menu+0x1c8),100);SetMeterValue((menu+0x1c8),100);}
     }
     if(gItemAmmoCounts[*idPtr]==0) {
      unsigned char *currentSlots=gItemSlotToRecord;
      MenuWeaponRecord *currentWeapons=ref_003478F0_04;
      if(currentWeapons[currentSlots[*idPtr]].ammo!=0) *((int *)GetFieldC(menu+0x3b4))=0x60202080;
     }
     SetFlagValue((menu+0x378),1);
     if(EmptyStubF7A0(ref_003478F0_05[0])==*idPtr) *((int *)GetFieldC(menu+0x98))=0x80ffde8d;
    }
    {
     MenuFloatPair stride=ref_003478F0_10[0],base=ref_003478F0_11[0];

     SetFirstFloat4(menu+0x98,(stride.x*(float)col+base.x)+(*(float **)(menu+0x498))[0],(stride.y*(float)row+base.y)+(*(float **)(menu+0x498))[0],0.0f,0.0f);
    }
    DrawScreenElementAtStoredPosition((menu+0x3b4));DrawColoredQuadWidget((menu+0x378));DrawProgressBar((menu+0x1c8));DrawScreenElementAtStoredPosition(menu+0x98);
   }
  }
  DrawScreenElementAtStoredPosition(menu+0xe4);DrawScreenElementAtStoredPosition(menu+0x17c);DrawAlignedTextLabel(menu+0x210);DrawAlignedTextLabel(menu+0x258);DrawAlignedTextLabel(menu+0x2a0);
  UpdateMenuGridLabels(menu);UpdateItemDetailPanel(menu);
 }
}
