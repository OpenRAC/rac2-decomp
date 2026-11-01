#include "include_asm.h"

#include "common.h"
extern unsigned int D_00139768[];
extern char D_0018B020[], D_001B1450[] MACRO_ADDR, D_001B1390[] MACRO_ADDR, D_001B2980[], D_001B13D0[] MACRO_ADDR, D_001B1410[] MACRO_ADDR;
extern int D_001A8BB0 MACRO_ADDR, D_001B15A8 MACRO_ADDR, D_001B15AC MACRO_ADDR;
extern float D_001B15A0 MACRO_ADDR, D_001A8C74 MACRO_ADDR, D_001A8C78 MACRO_ADDR;
extern int D_001B15A4 __attribute__((sda));
extern int func_002EF010(int);
extern void func_00282A60(void *, int, int);
extern void func_0027D330(int), func_002EB598(void), func_002ED058(void), func_PAL_002E5898(void);
extern short func_PAL_002B8898(int);
extern int func_002B6D28(void);
typedef struct { char pad[0x30]; int selected, frame, tick, chunk; short end, h42, count, h46, wait; char pad4a[0x2]; int p4c; char pad50[8]; int done; char pad5c[0x10]; int start, dest; char pad74[0x118]; char *objects[17]; } Scene;
extern Scene D_001B8840;
typedef struct { char pad[0x6C]; int arena; } Archive;
extern Archive D_001BAEC0;
typedef struct { char pad0[4]; short mode; char pad6[0x1e]; int destination, count; char pad2c[0x40]; short progress; char pad6e[4]; short state; } Transition;
extern Transition D_001A63A8_3;
extern int func_PAL_002EC070(int), func_001261F0(int);

/* Scene start for `id`: sets its bit in D_00139768, maps it to an index
   (func_002EF010, nothing if negative), clears the scene buffers, places the
   start and destination windows 0x80000 and 0x100000 below the arena, resets
   the fade and control words, waits until the transition reaches state 3
   below progress 6000, then sets the wait word to -3, calls func_002B6D28
   and func_PAL_002EC070(1) and waits a frame per step while it stays below the
   count.

   The stores after the clears are written in the order that gives the
   scheduler retail's register-pressure ties (a store whose register dies
   is issued first, then the rest in source order). The do { } while (0)
   around the two calls leaves loop notes in the block, which the
   scheduler treats as a barrier: the scene address is then computed
   ahead of the -3, as in retail (compare func_00124818). */
void func_PAL_002EC700(unsigned int id) {
 int index, count, dest, start;


 if (id < 0xB1) *(unsigned int *)((id >> 2) * 4 + (int)D_00139768) |= 1 << (id & 31);
 index = func_002EF010(id);
 if (index < 0) return;
 func_00282A60(D_0018B020,0,0x230);
 func_00282A60(&D_001B8840,0,0x1D0);
 func_00282A60(D_001B1450,0,0x40);
 func_00282A60(D_001B1390,0,0x40);
 func_00282A60(D_001B2980,0,0x40);
 func_00282A60(D_001B2980+0x40,0,0x40);
 func_00282A60(D_001B13D0,0,0x40);
 func_00282A60(D_001B1410,0,0x40);
 start=D_001BAEC0.arena - 0x80000;
 dest=D_001BAEC0.arena - 0x100000;
 D_001A8C74=1.0f;
 D_001A8C78=0.0f;
 D_001B8840.frame=0;
 D_001B8840.chunk=0;
 D_001B8840.selected=index;
 D_001B8840.start=start;
 D_001B8840.dest=dest;
 D_001B15A0=1.0f;
 D_001A8BB0=2;
 D_001B15A8=1;
 D_001B15AC=0x34;
 D_001B15A4=0;
 if(D_001A63A8_3.mode) {
  func_0027D330(5); func_PAL_002B8898(1); func_PAL_002EC070(0);
 } else { func_PAL_002EC070(0); func_0027D330(5); }
 if(D_001A63A8_3.mode) func_PAL_002B8898(1);
 func_002EB598(); func_002ED058();
 D_001A63A8_3.count=0;
 D_001A63A8_3.destination=D_001B8840.selected+4000;
 while(!(D_001A63A8_3.state==3 && D_001A63A8_3.progress<6000)) { func_PAL_002E5898(); func_001261F0(0); }
 D_001B8840.wait=-3;
 count=0;
 do { func_002B6D28(); func_PAL_002EC070(1); } while (0);
 while(D_001B8840.wait<count) { func_001261F0(0); count--; }
}
