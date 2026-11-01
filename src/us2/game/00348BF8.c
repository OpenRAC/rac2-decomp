#include "include_asm.h"

INCLUDE_ASM("asm/us2/game", func_US2_00348BF8);


typedef int s32;
typedef unsigned char u8;
typedef float f32;
extern void func_00348068(unsigned char *owner, float *records);
extern u8 D_001A7AF8[] __attribute__((section(".sdata")));
extern u8 D_001A7A80[] __attribute__((section(".sdata")));

/* func_00347F80 is built from 00345358-wrap.c. */


void func_US2_00348DA0(u8 *a0,f32 *a1) {
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


void func_US2_00348E10(u8 *a0, s32 a1, s32 a2) { *(s32 *)(a0 + 0xB8) = a1; *(s32 *)(a0 + 0xBC) = a2; }


INCLUDE_ASM("asm/us2/game", func_US2_00348E20);

void func_US2_00348E28(u8 *a0,f32 f0,f32 f1) {
 (*(f32 **)(a0+0x5C))[0]=f0;
 (*(f32 **)(a0+0x5C))[1]=f1;
 (*(s32 **)(a0+0x5C))[2]=0;
 (*(s32 **)(a0+0x5C))[3]=0;
}


INCLUDE_ASM("asm/us2/game", func_US2_00348E50);

INCLUDE_ASM("asm/us2/game", func_US2_00348E58);

INCLUDE_ASM("asm/us2/game", func_US2_00348E60);

INCLUDE_ASM("asm/us2/game", func_US2_00348E68);

INCLUDE_ASM("asm/us2/game", func_US2_00348E70);

extern void Faac80289_FUN_003361A8(char *p);
extern void Faac80289_FUN_00336968(char *p);

/* func_00348138 is built from 00345358-menu.c. */

char *func_US2_00349200(char *a0)
{
    char *p = a0 + 536;
    int i;

    Faac80289_FUN_003361A8(a0);
    Faac80289_FUN_003361A8(a0 + 76);
    Faac80289_FUN_003361A8(a0 + 152);
    Faac80289_FUN_003361A8(a0 + 228);
    Faac80289_FUN_003361A8(a0 + 304);
    Faac80289_FUN_003361A8(a0 + 380);
    Faac80289_FUN_003361A8(a0 + 456);

    for (i = 6; i != -1; i--) {
        Faac80289_FUN_00336968(p);
        p += 88;
    }
    return a0;
}


INCLUDE_ASM("asm/us2/game", func_US2_003492A8);

INCLUDE_ASM("asm/us2/game", func_US2_003492B0);
