/* func_L09_003E3288 -- NOT MATCHING. Tier opus-1 (Claude Opus 5.5, xhigh), 3 November 2026.
 * Best check.py: us 09_dobbo 1220 bytes, expected 1216; 0/1 places. Every register, the preheader
 * (count-up loop puts the 0x27 counter init after the hoisted 0xD0F/0xD30/5) and everything after the
 * scan loop match. Only difference: the moby state byte is read twice. Retail: bne oClass,$s3 /
 * lbu v1 (one load) ; bne v1,$s4 / sll v0,v1,24. Here: bnel / lbu v1 ; lbu v0 ; bne v0,$s4 /
 * daddu v1,v0. gcse PRE inserts the sign-test QI load before the ==5 branch (this is what gives the
 * constant 5 loop life 2, so it is hoisted), but the compare keeps its own load. Reading the state
 * once into a local (old 1208-byte form) loads once but leaves 5 unhoisted (life 1, $s6 unsaved).
 * Declarations: typed structs below; D_L09_001B285C/2860 must stay scalar MACRO_ADDR pointers
 * (struct-member stores then do not block their loads); D_001A7A60/7B08/7A10 read at nonzero sda
 * offsets (no $gp delay-slot loads); D_001A7A10[4] as in src/game/00344478-g8.c.
 */
#include "common.h"
extern unsigned char D_001395B8[];
typedef struct { char pad[0x1bc]; unsigned short flag; char pad2[2]; unsigned int time; } DobboClock;
extern DobboClock D_0018C750;
typedef struct { char pad[0x2c0]; int first; char pad2[0x11c]; int second; char pad3[0x20]; int third; char pad4[0x24]; unsigned short flag; } DobboDialogue;
extern DobboDialogue D_0018C958;
typedef struct { char pad[0x80]; char position[0x10]; char pad2[0x128]; int field1b8; char pad3[0x20d8]; int field2294; } DobboPlayer;
extern DobboPlayer D_00189E20;
extern int D_001397C4;
extern unsigned char D_001A7A60[] __attribute__((sda)), D_001A7B08[] __attribute__((sda));
extern short D_001A7A10[] __attribute__((sda));
extern unsigned int D_001A7390;
extern int D_L09_001A9040[] __attribute__((sda)), D_L09_001A903C[] __attribute__((sda));
typedef struct {
    int region[4];
    int entered;
    int hint14;
    int hint18;
    int hint1c;
    char pad20[0xc];
    int f2c;
    char pad30[0x28];
    int scan;
    int count;
} RegionState;
typedef struct { char pad[0x3d6]; short busy; } ScanVars;
typedef struct {
    char pad00[0x20];
    unsigned char state;
    char pad21[0xf];
    unsigned char alpha;
    char pad31[0x37];
    ScanVars *vars;
    char pad6c[0x3e];
    short oClass;
    char padac[0x54];
} ScanMoby;
extern ScanMoby *D_L09_001B285C MACRO_ADDR, *D_L09_001B2860 MACRO_ADDR;
extern int func_002ACBC8(void *, int);
extern void func_00288E18(int, int);
extern void func_002B0A18(int, int);
extern void func_002E5E58(int, int, int);
void func_L09_003E3288(unsigned char *object)
{
 RegionState *s = *(RegionState **)(object+0x68);
 ScanMoby *m;
 int i;
 if (!object[0x20]) {
  object[0x20]=1; object[0x30]=255; s->entered=0;
  if(D_001395B8[0x7a]>=126) D_001395B8[0x7a]=125;
  if(D_001395B8[0x79]>=126) D_001395B8[0x79]=125;
  s->f2c=0;
 }
 if(object[0x20]!=1) return;
 if(D_L09_001A9040[0] && !D_001A7A60[12]) {
  for(i=0;i<40;i++) {
   m=&D_L09_001B285C[s->scan];
   if(m->oClass==0xd0f || m->oClass==0xd57 || m->oClass==0xd30 || m->oClass==0xcbc || m->oClass==0xd90) {
    if(m->oClass==0xd30 && m->vars->busy) {s->scan++;continue;}
    if(m->oClass==0xd0f && m->state==5) {s->scan++;continue;}
    if((signed char)m->state>=0) s->count++;
   }
   s->scan++;
   if(&D_L09_001B285C[s->scan]>=D_L09_001B2860) {
    if(!s->count && !D_001A7A60[12]) {
     D_001A7A60[12]=1; func_002E5E58(1,0,0);func_002B0A18(0x1233,-1);D_L09_001A903C[0]=1;
    }
    s->scan=0; s->count=0;
   }
  }
 }
 if(!D_0018C958.flag && D_001397C4<0 && !D_001A7B08[5]) {
  if(func_002ACBC8(D_00189E20.position,s->region[0])) func_00288E18(0xa02,0x59);
 }
 if(func_002ACBC8(D_00189E20.position,s->region[1])) s->entered=1;
 if(D_00189E20.field2294==0x39 && !D_00189E20.field1b8 && s->entered) D_001395B8[0x7a]++;
 if(D_001A7A10[4]<=0 && func_002ACBC8(D_00189E20.position,s->region[1])) {
  if(D_001395B8[0x7a]%5==4 && !s->hint1c && D_00189E20.field2294!=0x39) {
   if(D_0018C958.second>=0) func_00288E18(0x9fb,0x52);
   s->hint1c=1;D_001395B8[0x7a]++;
  }
 }
 if(func_002ACBC8(D_00189E20.position,s->region[2])) {
  if(D_00189E20.field2294==0x39 && !D_00189E20.field1b8) D_001395B8[0x79]++;
 }
 if(!D_001A7B08[7] && func_002ACBC8(D_00189E20.position,s->region[2])) {
  if(D_001395B8[0x79]%5==4 && !s->hint18 && D_00189E20.field2294!=0x39) {
   if(D_0018C958.third>=0) func_00288E18(0x9fe,0x55);
   s->hint18=1; D_001395B8[0x79]++;
  }
 }
 if(func_002ACBC8(D_00189E20.position,s->region[3])) {
  if((!D_0018C750.flag || D_001A7390-D_0018C750.time>432000) && D_001395B8[0x7d]<3 && !s->hint14) {
   if(D_0018C958.first>=0) func_00288E18(0x9e3,0x3a);
   D_001395B8[0x7d]++;s->hint14=1;
  }
 }
}
