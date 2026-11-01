#include "include_asm.h"

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

void func_PAL_L18_00401AE0(u8 *a) {
 u8 *s=*(u8 **)(a+0x68);
 switch(a[0x20]) {
 case 0:
  qcopy(s+0x40,a+0x10);
  W(s,0x6c)=(int)(F(s,0x60)/(F(s,0x64)*0.020000001f));
  func_00282F20(s+0x50,s+0x30,F(s,0x60)/(float)W(s,0x6c));
  func_002A7750(a,1,-1);
  W(s,0x68)=0; W(s,0x74)=0;
  break;
 case 1:
  if(W(s,0x68)>=2) {
   func_00282CF0(a+0x10,a+0x10,s+0x50);
   W(s,0x68)--;
  } else if(W(s,0x68)>0) {
   qcopy_nc(a+0x10,s+0x40); W(s,0x68)--;
  }
  if(!(D_L18_001B2348[0]&15)) {
   if(func_L18_003FDAB8(a,W(s,0x70)!=-1?D_L18_001B281C+(W(s,0x70)<<8)+0x10:D_00189EA0))
    func_002A7750(a,2,-1);
  }
  if(func_002B38B8(a)) { a[0xbe]&=0xfb; func_002A7750(a,2,-1); }
  break;
 case 2:
  if(W(s,0x68)<W(s,0x6c)) {
   func_00282CC0(a+0x10,a+0x10,s+0x50); W(s,0x68)++;
  }
  if(!(D_L18_001B2348[0]&15)) {
   if(func_L18_003FDD68(a,W(s,0x70)!=-1?D_L18_001B281C+(W(s,0x70)<<8)+0x10:D_00189EA0))
    func_002A7750(a,1,-1);
  }
  if(func_002B38B8(a)) { a[0xbe]&=0xfb; func_002A7750(a,1,-1); }
  break;
 }
 if(*(u16 *)(a+0x96)<=0xfffe) ++*(u16 *)(a+0x96);
}
