/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 1452/1452 bytes, 0/28 placements; first difference 0x4c.
 * Profile: -O2 -G8 -ffunction-sections.
 * Stored-address getters follow their matched signed32 return contracts, with explicit pointer
 * casts at the actual uses. Physical EE widths and argument-bank order are preserved; this
 * repair leaves the retained allocation/scheduling residual unchanged.
 * Earlier measurements below are historical where superseded by this note.
 */
/* sol-high, USA v1.01, game -O2 -G8 -ffunction-sections.
 * Best: 1452/1452 bytes, 0/28 places; first mismatch +0x4C.
 * Retail 0xE0 frame and saved-register assignments are reproduced. Explicit
 * branch-local weapon/slot table bases recover s4/s5/s6 and spill the shared
 * colour constant, matching most of the central call sequence. Inline position
 * reads reproduce the short-lived pointer allocation. Reading the four layout
 * scalars before the first colour store reproduces its instruction scheduling.
 * Remaining: pointer spill slots, row address formation, first coordinate FPR
 * coalescing, operand registers in bar positioning, and branch-edge address setup.
 * A separate final table lookup preserves retail's rematerialisation boundary;
 * retaining the first table locals there instead shrinks the body to 1436 bytes.
 * -G0, -fno-strength-reduce and -mno-split-addresses did not improve the result.
 * No linked validation. All needed declarations follow; compile in a G8 unit.
 */
#include "include_asm.h"
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
extern MenuWeaponRecord D_L00_00239BA0[];
extern void func_00336B90(void *,int),func_00336B98(void *,int);
extern void func_00336F20(int,int *,int *,int *);
extern void func_00336498(void *,int,int);
extern void func_00336548(void *);
extern int func_0026F7A0(void *);
extern void *D_L00_001F2880[];
extern void func_003472B8(void *),func_00347468(void *);
extern int D_L00_001AE750,D_L00_001AE754,D_L00_001AE748,D_L00_001AE74C;
extern float D_L00_001AE758,D_L00_001AE75C;
extern MenuIntegerPair D_L00_001AE588[],D_L00_001AE590[];
typedef struct {float x,y;} MenuFloatPair;
extern MenuFloatPair D_L00_001AE598[],D_L00_001AE5A0[];
void func_003478F0(char *o)
{
 if(*(int *)(o+0x4f8)) {
  int row,col;

  func_00336320(o);func_00336320(o+0x4c);func_00336320(o+0x130);
  for(row=0;row<6;row++) {
   short *ids=&ref_00347468_10[0].id;
   short *id=ids+(row<<2)*5;
   for(col=0;col<4;col++,id+=5) {

    { int *color=((int *)func_00335E20(o+0x3b4));
      float x=D_L00_001AE758*(float)col+(float)D_L00_001AE750;
      float y=D_L00_001AE75C*(float)row+(float)D_L00_001AE754;
      *color=0x60241700;
      func_00335E38(o+0x3b4,x+(*(float **)(o+0x498))[0],y+(*(float **)(o+0x498))[1],0.0f,0.0f);
    }
    *((int *)func_00335E20(o+0x98))=0x30f0c070;
    *((int *)func_00335E20((o+0x3b4)))=0x60241700;
    func_00335E68((o+0x1c8),0);func_00335E68((o+0x378),0);
    if(D_001A7AF8[*id]) {
     MenuWeaponRecord *weapons=D_L00_00239BA0;
     unsigned char *slots=D_00139568;
     MenuWeaponRecord *record=&weapons[slots[*id]];
     func_00336920((o+0x378),record->icon,0);

     func_00335E38((o+0x378),(53.5f*(float)col+(float)D_L00_001AE748)+(*(float **)(o+0x498))[0],(47.0f*(float)row+(float)D_L00_001AE74C)+(*(float **)(o+0x498))[1],0.0f,0.0f);
     if(weapons[slots[*id]].icon==0xea7e) {
      *((int *)func_00335E20((o+0x378)))=0x80808080;
     } else {
      MenuIntegerPair base=D_L00_001AE588[0],stride=D_L00_001AE590[0];
      int a,b,color;
      func_00336B90((o+0x1c8),weapons[slots[*id]].max);
      func_00336B98((o+0x1c8),D_00139868[*id]>>5);

      func_00335E38((o+0x1c8),(float)(base.x+stride.x*col)+(*(float **)(o+0x498))[0],(float)(base.y+stride.y*row)+(*(float **)(o+0x498))[1],0.0f,0.0f);
      func_00335E68((o+0x1c8),1);
      a=0;b=0;color=0;
      func_00336F20(*id,&a,&b,&color);func_00336498((o+0x1c8),a,b);
      *((int *)func_00335E20((o+0x378)))=color;
      if(weapons[slots[*id]].max<=0) {func_00336B90((o+0x1c8),100);func_00336B98((o+0x1c8),100);}
     }
     if(D_00139688[*id]==0) {
      unsigned char *currentSlots=D_00139568;
      MenuWeaponRecord *currentWeapons=D_L00_00239BA0;
      if(currentWeapons[currentSlots[*id]].ammo!=0) *((int *)func_00335E20(o+0x3b4))=0x60202080;
     }
     func_00335E68((o+0x378),1);
     if(func_0026F7A0(D_L00_001F2880[0])==*id) *((int *)func_00335E20(o+0x98))=0x80ffde8d;
    }
    {
     MenuFloatPair stride=D_L00_001AE598[0],base=D_L00_001AE5A0[0];

     func_00335E38(o+0x98,(stride.x*(float)col+base.x)+(*(float **)(o+0x498))[0],(stride.y*(float)row+base.y)+(*(float **)(o+0x498))[0],0.0f,0.0f);
    }
    func_00336320((o+0x3b4));func_00336828((o+0x378));func_00336548((o+0x1c8));func_00336320(o+0x98);
   }
  }
  func_00336320(o+0xe4);func_00336320(o+0x17c);func_00336A78(o+0x210);func_00336A78(o+0x258);func_00336A78(o+0x2a0);
  func_003472B8(o);func_00347468(o);
 }
}
