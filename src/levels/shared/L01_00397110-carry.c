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
void func_L01_003980D0(char *m)
{
 CarryData *d = *(CarryData **)(m+0x68);
 int done=0, i, result;
 char **p;
 float v[4];
 unsigned short flags = *(u16 *)(m+0xB2);
 if (D_L01_0021E4B0.disabled[(short)flags]) goto completed;
 {
  int c = (u8)D_0019B4A8[((short)flags>>1)+(D_001A79F0<<10)];
  if (flags&1) { if ((c>>4)&7) goto completed; }
  else if(c&7) goto completed;
  goto flags_checked;
completed:
  done=1;
 }
flags_checked:
 done=!!done;
 if (d->event!=-1 && !done && func_002ACBC8(D_00189EA0,d->event)) {
  done=1; func_L01_00398008(m); func_L01_003990E8(m);
  if (*(u8 *)(m+0x20)==5) func_002A7750(m,1,-1);
 }
 if (d->x3C) {
  if (!D_001A7A00[0xA]) {
   *(u16 *)(m+0x34)|=0x41;
   *(int *)(m+0x98)=0;
   return;
  }
  *(int *)(m+0x98)=*(int *)(*(char **)(m+0x24)+0x10);
  *(u16 *)(m+0x34)&=0xFFBE;
 }
 if (*(u16 *)(m+0x96)<0x7FFD) ++*(u16 *)(m+0x96);
 switch (*(u8 *)(m+0x20)) {
 case 0: {
  int i;
  char **p;
  *(u8 *)(m+0x30)=255;
  for(i=0;i<3;i++) {
   char **p=d->children+i;
   *p=func_0029EFD0(0x13B);
   if(*p) {
    *(u16 *)(*p+0x32)=0x40; *(u8 *)(*p+0x31)=1;
    *(u64 *)(*p+0x38)=*(u64 *)(D_00189E20.model+0x38);
    *(u16 *)(*p+0x34)=*(u16 *)(m+0x34);
    qcopy_nc(*p+0x10, m+0x10);
    qcopy_nc(*p+0xF0, m+0xF0);
    *(u8 *)(*p+0x30)=*(u8 *)(m+0x30);
    if(*(char **)(*p+0x68)) **(char ***)(*p+0x68)=m;
    *(float *)(*p+0xF8)=func_00283B98(*(float *)(*p+0xF8),i*2.0943954f);
   }
  }
  if(d->x38||done) func_002A7750(m,6,-1);
  else { func_002A7750(m,5,-1); func_L01_00399098(m); }
  {
  func_L01_00398938(m);
  break;
}
 }
 case 6:
  if(*(u8 *)(m+0x21)!=255) func_L01_003115E8(*(u8 *)(m+0x21),1);
  func_002A7750(m,1,-1);
  
 case 1:
  if(d->unlock>=0 && !(D_0019B2E8[d->unlock+(CarryLevelIndex<<4)]&0x80)) break;
  if(d->target==-1 || D_00189E20.mode==2 || D_00189E20.linked!=m || D_00189E20.control) break;
  if(d->x50) {
   d->x50=!D_00189E20.busy;
   D_L01_001A8FF4=4; D_L01_001A8FF0=2;
  } else func_L01_00398A90(m);
  if(!(D_00138324&0x10)) break;
  func_002E5CF8(0,0,m); func_002A7750(m,2,-1);
  d->x2C=0; d->x30=-1; d->x28=0;
  func_L00_002D40A0(m+0x10,0,*(float *)(m+0xF8));
  func_002A8C28(m,m+0x10,0x10000,0,1,0,1.5f,20.0f,1.0f);
  break;
 case 7:
  if(d->x20<1.0f) {
   func_002AA548(&d->x20,&d->x28,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else if(d->x24<1.0f) {
   func_002AA548(&d->x24,&d->x2C,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else {
   func_002E5CF8(1,0,m); func_002A7750(m,8,-1); d->x34=0;
  }
  {
  func_L01_00398938(m);
  break;
}
 case 2:
  result=func_L00_002D40F0();
  if(d->x20<1.0f) {
   func_002AA548(&d->x20,&d->x28,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else {
   int mode = CarryMode;
   if(d->x24<1.0f) {
   func_002AA548(&d->x24,&d->x2C,1.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else if(!(mode==4 && d->x20>0.25f)) {
   if(result==2) { d->x34=1.95f; func_002A7750(m,3,-1); }
   else if(!result) func_002A7750(m,4,-1);
   else if(*(u16 *)(m+0x96)>=361) { func_L01_002C98B8(); d->x34=1.95f; func_002A7750(m,3,-1); }
   }
  }
  func_L01_00398938(m);
  break;
 case 3:
  if(d->x34!=0) {
   func_L00_002E6CF0(func_L01_00398B50,m); func_002AA2E8(&d->x34,0.0f,0.06666667f); break;
  } else {
   char *other=D_L01_001B255C+(d->target<<8);
   CarryData *od=*(CarryData **)(other+0x68);
   qcopy_nc(v, other+0x10); v[2]+=0.2f;
   if(d->x4C!=-1) func_L00_00303530(d->x4C,od->x40);
   func_L00_002B9D60(v,other+0xF0,0,1);
   if(od->x48!=-1) func_L00_0042A500(od->x48);
   func_L01_00323310(od->x40,od->x44);
   func_002A7750(other,4,-1);
   od->x28=0; od->x2C=0; od->x34=0;
   od->x24=od->x20=1; od->x50=1;
   func_002E5CF8(1,0,other); func_002A7750(m,1,-1);
   d->x2C=d->x28=d->x24=d->x20=0;
   d->x34=1.95f; func_L01_00398938(m);
  }
  break;
 case 4: case 8:
  if(func_002B3868(m)) {
   p=d->children;
   for(i=2;i>=0;i--,p++) if(*p) *(u16 *)(*p+0x34)&=0xFF7F;
  }
  if(d->x34<1.95f) {
   func_L00_002E6CF0(func_L01_00398B50,m); func_002AA2E8(&d->x34,1.95f,0.06666667f);
  } else if(d->x24>0) {
   func_002AA548(&d->x24,&d->x28,0.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else if(d->x20>0) {
   func_002AA548(&d->x20,&d->x2C,0.0f,D_L01_001AF588*0.0002777777845f,D_L01_001AF58C*0.0002777777845f,D_L01_001AF590*0.016666668f);
  } else func_002A7750(m,1,-1);
  func_L01_00398938(m);
 }
 ;
}

