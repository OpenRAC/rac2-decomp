#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef int s32;

extern u8 D_L24_0025B710[];

extern void *func_L00_002A4FE8(short);

extern void func_0029F9F0(void *, void *);

extern void func_00282C88(void *);

/* Detaches every active attachment record from its owner and resets its blend and rotation values. */
void func_L00_002A53B8(void) {
 u8 *records=D_L24_0025B710;
 u8 *rotPtr=records+0x40;
 u8 *posVelPtr=records+0x90;
 u8 *rotVelPtr=records+0x60;
 u8 *p=records;
 u8 *endPtr=p+0x1bc0;
 do {
  if(p[1]!=0) {
   void *owner=GetAttachmentOwnerByKind(*(short *)(p+0xA2));
   if(owner!=0) DetachManipulator(owner,p);
  }
  ClearVector128(rotPtr);rotPtr+=0xb0;
  ClearVector128(rotVelPtr);rotVelPtr+=0xb0;
  ClearVector128(posVelPtr);posVelPtr+=0xb0;
  *(float *)(p+0xAC)=1.0f;
  p+=0xb0;
 } while((s32)rotPtr<(s32)endPtr);
}
