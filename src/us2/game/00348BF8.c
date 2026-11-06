#include "include_asm.h"

extern int func_00336E40(void *);
extern void *func_00336DA8(int, int);
extern void *func_US2_003377B0(void *, void *, void *);
extern char D_001AE5A8[];

/* func_US2_00348BF8, the USA v2.00 copy of func_00347EC8: the same C, where the fields move 0x10 on
   and the new field at 0x54 is cleared too. */
void func_US2_00348BF8(char *object, void *data)
{
    int *position;
    *(int *)(object + 0x60) = 0;
    *(int *)(object + 0xC0) = 0;
    *(void **)(object + 0x58) = data;
    if (data) {
        position = func_00336DA8(16, func_00336E40(data));
        *(int **)(object + 0x5C) = position;
        position[1] = 0; position[2] = 0; position[3] = 0; position[0] = 0;
    }
    func_US2_003377B0(object, D_001AE5A8, data);
    *(int *)(object + 0xAC) = 0x70FFFEED;
    *(int *)(object + 0xB0) = 0x80F0F0F0;
    *(int *)(object + 0xB4) = 0x80808080;
    *(int *)(object + 0xBC) = 32;
    *(int *)(object + 0x54) = 0;
    *(int *)(object + 0xB8) = 0;
    *(int *)(object + 0xC4) = 0;
    *(int *)(object + 0xC8) = 0;
    *(int *)(object + 0xCC) = -1;
}

INCLUDE_ASM("asm/us2/game", func_US2_003492A8);

INCLUDE_ASM("asm/us2/game", func_US2_003492B0);

INCLUDE_ASM("asm/us2/game", func_US2_00348E50);

INCLUDE_ASM("asm/us2/game", func_US2_00348E58);

INCLUDE_ASM("asm/us2/game", func_US2_00348E60);

INCLUDE_ASM("asm/us2/game", func_US2_00348E68);


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






/* func_US2_00348E70 is built from 00348E70-menu.c. */

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



