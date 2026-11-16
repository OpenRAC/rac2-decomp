#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef int s32;

extern u8 g_attachment_records[];

extern void *attachment_get_owner_by_kind(short);

extern void moby_detach_manipulator(void *, void *);

extern void vec_clear_128(void *);

/* Detaches every active attachment record from its owner and resets its blend and rotation values. */
void attachment_reset_all(void) {
 u8 *records=g_attachment_records;
 u8 *rotPtr=records+0x40;
 u8 *posVelPtr=records+0x90;
 u8 *rotVelPtr=records+0x60;
 u8 *p=records;
 u8 *endPtr=p+0x1bc0;
 do {
  if(p[1]!=0) {
   void *owner=attachment_get_owner_by_kind(*(short *)(p+0xA2));
   if(owner!=0) moby_detach_manipulator(owner,p);
  }
  vec_clear_128(rotPtr);rotPtr+=0xb0;
  vec_clear_128(rotVelPtr);rotVelPtr+=0xb0;
  vec_clear_128(posVelPtr);posVelPtr+=0xb0;
  *(float *)(p+0xAC)=1.0f;
  p+=0xb0;
 } while((s32)rotPtr<(s32)endPtr);
}
