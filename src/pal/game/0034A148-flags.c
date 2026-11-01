#include "include_asm.h"

typedef int s32;
typedef unsigned char u8;
typedef float f32;
extern void func_00348068(unsigned char *owner, float *records);
extern u8 D_001A7AF8[] __attribute__((section(".sdata")));
extern u8 D_001A7A80[] __attribute__((section(".sdata")));

/* func_00347F80 is built from 00345358-wrap.c. */


void func_PAL_0034A230(u8 *a0,f32 *a1) {
 f32 *end;
 *(f32 **)(a0+0x68)=a1;
 *(s32 *)(a0+0xC0)=0;
 end=a1+0x50;
 if(a1[0]>0.0f) {
  do {
   a1+=5;
   (*(s32 *)(a0+0xC0))++;
  } while(*a1>0.0f && (s32)a1<(s32)end);
 }
 if(*(s32 *)(a0+0x60)>=*(s32 *)(a0+0xC0)) *(s32 *)(a0+0x60)=0;
}
