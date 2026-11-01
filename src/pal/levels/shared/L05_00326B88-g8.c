#include "include_asm.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001A9A54 __attribute__((sda));
extern char D_001A9A60 __attribute__((sda));
extern char D_001A9AB8 __attribute__((sda));
extern char D_00256418[];
extern int func_L00_002D6728(void), func_L00_002D6768(void);
extern void func_0029BCC8(void), func_PAL_L05_00326B88(void);
extern void func_00349490(void *, int);
extern void func_PAL_0033C928(void *,void *,void *);
extern void func_PAL_0033C8F0(void *,float);
extern void func_PAL_0033C908(void *,int);

void func_PAL_L05_00326CA0(void) {
 int enabled;
 if (D_001A8CFC[0] != 0) {
  enabled=0;
  if(func_L00_002D6728()) enabled=func_L00_002D6768()!=0;
  if(D_001A9A54 != enabled) {
   func_0029BCC8();
   D_001A9A54=enabled;
   if(enabled==1) {
    func_00349490(D_001A8CFC[0]+0x3CDF8,(int)&D_001A9A60);
    func_PAL_0033C928(D_001A8CFC[0]+0x3F860,&D_001A9AB8,D_00256418);
    func_PAL_0033C8F0(D_001A8CFC[0]+0x3F860,36.0f);
    func_PAL_0033C908(D_001A8CFC[0]+0x3F860,-1);
    func_PAL_L05_00326B88();
   }
  }
 }
}
