/* func_US2_00348628 (1,444 bytes): the USA v2.00 copy of func_003478F0 (src/game/003478F0-grid-g8.c), the
 * menu grid, with the release's menu object layout (fields from 0x258 on moved) and without
 * the closing func_003472B8 call. Same unit flags as the v1.01 copy (config/cflags.txt); its
 * row-address pointer cast is allowed by the same owner ruling (13 November 2026).
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
extern MenuWeaponRecord ref_US2_00348628_04[];
extern void func_00336B90(void *,int),func_00336B98(void *,int);
extern void func_00336F20(int,int *,int *,int *);
extern void func_00336498(void *,int,int);
extern void func_00336548(void *);
extern int func_0026F7A0(void *);
extern void *ref_US2_00348628_05[];
extern void func_003472B8(void *),func_00347468(void *);
extern int ref_US2_00348628_00,ref_US2_00348628_01,ref_US2_00348628_02,ref_US2_00348628_03;
extern float ref_US2_00348628_06,ref_US2_00348628_07;
extern MenuIntegerPair ref_US2_00348628_08[],ref_US2_00348628_09[];
typedef struct {float x,y;} MenuFloatPair;
extern MenuFloatPair ref_US2_00348628_10[],ref_US2_00348628_11[];
void func_US2_00348628(char *o)
{
 if(*(int *)(o+0x4c0)) {
  int row,col;
  MenuGridEntry *t=ref_00347468_10;

  func_00336320(o);func_00336320(o+0x4c);func_00336320(o+0x130);
  for(row=0;row<6;row++) {
   short *ids=&t->id;
   short *id=(short *)((row<<2)*10+(int)ids);
   for(col=0;col<4;col++,id+=5) {

    { int *color=((int *)func_00335E20(o+0x354));
      float yb=(float)ref_US2_00348628_01;
      float xs=ref_US2_00348628_06;
      float xb=(float)ref_US2_00348628_00;
      float ys=ref_US2_00348628_07;
      *color=0x60241700;
      func_00335E38(o+0x354,(xs*(float)col+xb)+(*(float **)(o+0x438))[0],(ys*(float)row+yb)+(*(float **)(o+0x438))[1],0.0f,0.0f);
    }
    *((int *)func_00335E20(o+0x98))=0x30f0c070;
    *((int *)func_00335E20((o+0x354)))=0x60241700;
    func_00335E68((o+0x1c8),0);func_00335E68((o+0x318),0);
    if(D_001A7AF8[*id]) {
     MenuWeaponRecord *weapons=ref_US2_00348628_04;
     unsigned char *slots=D_00139568;
     func_00336920((o+0x318),weapons[slots[*id]].icon,0);

     func_00335E38((o+0x318),(53.5f*(float)col+(float)ref_US2_00348628_02)+(*(float **)(o+0x438))[0],(47.0f*(float)row+(float)ref_US2_00348628_03)+(*(float **)(o+0x438))[1],0.0f,0.0f);
     if(weapons[slots[*id]].icon==0xea7e) {
      *((int *)func_00335E20((o+0x318)))=0x80808080;
     } else {
      MenuIntegerPair base=ref_US2_00348628_08[0],stride=ref_US2_00348628_09[0];
      int a,b,color;
      func_00336B90((o+0x1c8),weapons[slots[*id]].max);
      func_00336B98((o+0x1c8),D_00139868[*id]>>5);

      func_00335E38((o+0x1c8),(float)(stride.x*col+base.x)+(*(float **)(o+0x438))[0],(float)(stride.y*row+base.y)+(*(float **)(o+0x438))[1],0.0f,0.0f);
      func_00335E68((o+0x1c8),1);
      a=0;b=0;color=0;
      func_00336F20(*id,&a,&b,&color);func_00336498((o+0x1c8),a,b);
      *((int *)func_00335E20((o+0x318)))=color;
      if(weapons[slots[*id]].max<=0) {func_00336B90((o+0x1c8),100);func_00336B98((o+0x1c8),100);}
     }
     if(D_00139688[*id]==0) {
      unsigned char *currentSlots=D_00139568;
      MenuWeaponRecord *currentWeapons=ref_US2_00348628_04;
      if(currentWeapons[currentSlots[*id]].ammo!=0) *((int *)func_00335E20(o+0x354))=0x60202080;
     }
     func_00335E68((o+0x318),1);
     if(func_0026F7A0(ref_US2_00348628_05[0])==*id) *((int *)func_00335E20(o+0x98))=0x80ffde8d;
    }
    {
     MenuFloatPair stride=ref_US2_00348628_10[0],base=ref_US2_00348628_11[0];

     func_00335E38(o+0x98,(stride.x*(float)col+base.x)+(*(float **)(o+0x438))[0],(stride.y*(float)row+base.y)+(*(float **)(o+0x438))[0],0.0f,0.0f);
    }
    func_00336320((o+0x354));func_00336828((o+0x318));func_00336548((o+0x1c8));func_00336320(o+0x98);
   }
  }
  func_00336320(o+0xe4);func_00336320(o+0x17c);func_00336A78(o+0x210);func_00336A78(o+0x268);func_00336A78(o+0x2c0);
  func_00347468(o);
 }
}
