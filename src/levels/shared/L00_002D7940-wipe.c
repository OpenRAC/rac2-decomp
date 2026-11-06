#include "common.h"

/* Draws the screen wipe: per-strip fade (mode 0) or staggered strips (modes 1, 2). */
typedef struct { int key, base, a08, a0c, width, top, mode, count, step, duration; } DrawRec_2958;
typedef struct { int buffers[7]; short buffer, pad1e, index, pad22, active; short pad26; int timer; char pad2c[0x36c-0x2c]; int delay, fade; char pad374[0x384-0x374]; int style; } DrawState_2958;
extern DrawState_2958 D_L00_001BC200;
extern DrawRec_2958 D_L00_001BC588[];
extern void func_0027C540(int);
/* The upload helper (src/game/002FC8D0.c) returns a packed 64-bit texture descriptor. */
extern long long func_002FCB00(int,int,int,int);
extern int D_001A72DC __attribute__((section(".sdata")));
extern float ref_L00_001B18E0_00 __attribute__((section(".sdata")));
extern void func_L00_002E2C30(int,float);
extern void func_L00_002E3340(int,float);
extern void func_L00_002E3520(void);
extern void func_0027C660(void);
extern int func_00283CF0(float);
extern void func_0027DDC0(int,int,int,int);
void func_L00_002E2958(void) {
 int i; float alpha;
 if(D_L00_001BC200.active) {
  func_0027C540(0);
  func_002FCB00((int)((char *)D_L00_001BC200.buffers[(short)(D_L00_001BC200.buffer^1)]+16),D_001A72DC,512,416);
  func_L00_002E3520();
  switch(D_L00_001BC588[D_L00_001BC200.index].mode) {
  case 0:
   for(i=0;i<D_L00_001BC588[D_L00_001BC200.index].count;i++) {
    if(D_L00_001BC588[D_L00_001BC200.index].duration<D_L00_001BC200.timer*2)
     alpha=(1.0f-(float)D_L00_001BC200.timer/(float)D_L00_001BC588[D_L00_001BC200.index].duration)*2.0f;
    else alpha=1.0f;
    func_L00_002E3340(i,alpha);
   }
   break;
  case 1: case 2:
   {
   int j=0;
   if(j<D_L00_001BC588[D_L00_001BC200.index].count) do {
    int next=j+1;
    func_L00_002E2C30(j,1.0f-((float)D_L00_001BC200.timer-(float)(D_L00_001BC588[D_L00_001BC200.index].count-next)*(float)D_L00_001BC200.delay)/(float)D_L00_001BC200.fade);
    j=next;
   } while(j<D_L00_001BC588[D_L00_001BC200.index].count);
   }
   break;
  }
  func_0027C660();
 }
 func_0027DDC0(0,0,0,func_00283CF0(ref_L00_001B18E0_00*128.0f));
}
